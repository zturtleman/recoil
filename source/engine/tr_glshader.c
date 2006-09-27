/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.
 
This file is part of Quake III Arena source code.
 
Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.
 
Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
 
You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/
#include "tr_local.h"

// tr_shader_object - this file deals with OpenGL 2.0 shaders, for the blur effect
glShader_t *currentShader = NULL;

static int hashName(const char *name)
{
    int ret = 0;
    const char *c = name;

    while(*c)
    {
        ret += *c++;
    }

    return ret;
}

#define MAX_SHADER_FILES 1024*2

shaderFile_t vertexFiles[MAX_SHADER_FILES];
shaderFile_t fragmentFiles[MAX_SHADER_FILES];

void R_InitGLShaders(void)
{
	memset(vertexFiles, 0, sizeof(shaderFile_t) * MAX_SHADER_FILES);
	memset(fragmentFiles, 0, sizeof(shaderFile_t) * MAX_SHADER_FILES);
}

static shaderFile_t *getShaderFile(const char *text, shaderFile_t *Files, GLuint type)
{
    GLchar infoLog[1024];
    GLint Result;
	GLuint shader;
	int name[4];
	int i = 0, len;

	memset(name, 9, sizeof(int) * 4);
	while(text[i])
	{
		name[(i + text[i+1]) % 3] ^= text[i] << (i % 23);
		i++;
	}

	for(i=0; i<MAX_SHADER_FILES; i++)
	{
		if(Files[i].links && name[0] == Files[i].name[0] && name[1] == Files[i].name[1] && name[2] == Files[i].name[2] && name[3] == Files[i].name[3])
			return &Files[i];
	}

	shader = qglCreateShader(type);
	qglShaderSource(shader, 1, &text, NULL);
	qglCompileShader(shader);
	qglGetShaderiv(shader, GL_COMPILE_STATUS, &Result);
	if (!Result)
	{
		qglGetShaderInfoLog(shader, 1024, &len, infoLog);
		if(len)
			CL_RefPrintf(PRINT_ALL, "Shader log:\n%s\n%s", infoLog, text);
		return NULL;
	}

	for(i=0; i<MAX_SHADER_FILES; i++)
	{
		if(!Files[i].links)
		{
			memcpy(Files[i].name, name, sizeof(int) * 4);
			Files[i].shader = shader;
			Files[i].links = 0;
			return &Files[i];
		}
	}

	return NULL;
}

static shaderFile_t *getVertexShaderFile(const char *text)
{
	return getShaderFile(text, vertexFiles, GL_VERTEX_SHADER);
}

static shaderFile_t *getFragmentShaderFile(const char *text)
{
	return getShaderFile(text, fragmentFiles, GL_FRAGMENT_SHADER);
}

void Shader_Compile(glShader_t *shader)
{
    GLint vsResult = GL_FALSE, fsResult = GL_FALSE, linkResult;
    GLchar infoLog[1024];
    int i;

    if(!GL_VERSION_2_0_supported || (shader->vertexText == NULL && shader->fragmentText == NULL))
        return;

	if(shader->program)
		Shader_Free(shader);

    shader->program = qglCreateProgram();

    // Compile the vertex shader
    if (shader->vertexText != NULL)
    {
        shader->vertex = getVertexShaderFile(shader->vertexText);
        if(shader->vertex)
		{
            qglAttachShader(shader->program, shader->vertex->shader);
			shader->vertex->links++;
			vsResult = GL_TRUE;
		}
    }
    else
        vsResult = GL_TRUE;

    // Compile the fragment shader
    if (shader->fragmentText != NULL)
    {
        shader->fragment = getFragmentShaderFile(shader->fragmentText);
		fsResult = (shader->fragment) ? GL_TRUE : GL_FALSE;
        if (fsResult)
		{
            qglAttachShader(shader->program, shader->fragment->shader);
			shader->fragment->links++;
			fsResult = GL_TRUE;
		}
    }
    else
        fsResult = GL_TRUE;

    // Link the shaders
    if (vsResult && fsResult)
    {
        qglLinkProgram(shader->program);
        qglGetProgramiv(shader->program, GL_LINK_STATUS, &linkResult);
        qglGetProgramInfoLog(shader->program, sizeof(infoLog), &i, infoLog);

        if(i)
            CL_RefPrintf(PRINT_ALL, "Program log:\n%s\n%s%s", infoLog, shader->vertexText, shader->fragmentText);

        if (linkResult)
        {
			glShader_t *last = currentShader;
            GLint nUniforms, maxLength;
			char *name;

            Shader_Use(shader);

            qglGetProgramiv(shader->program, GL_ACTIVE_UNIFORMS, &nUniforms);
            qglGetProgramiv(shader->program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);

            shader->samplers = (int *)malloc(nUniforms * sizeof(int));
			shader->uniforms = (int *)malloc(nUniforms * sizeof(int));
			shader->uniformsValues = (int *)malloc(nUniforms * sizeof(int));
            shader->numSamplers = 0;
			shader->numUniforms = 0;

			name = (char *)malloc(maxLength);
            for(i = 0; i < nUniforms; i++)
            {
                GLint length, size, location;
                GLenum type;

                qglGetActiveUniform(shader->program, i, maxLength, &length, &size, &type, name);
				location = qglGetUniformLocation(shader->program, name);
				if(location != -1)
				{
					if (type >= GL_SAMPLER_1D && type <= GL_SAMPLER_2D_SHADOW)
					{
						qglUniform1i(location, shader->numSamplers);
						shader->samplers[shader->numSamplers++] = hashName(name);
					}
					else
					{
						shader->uniforms[shader->numUniforms] = hashName(name);
						shader->uniformsValues[shader->numUniforms] = location;
						shader->numUniforms++;
					}
				}
            }
			free(name);

            Shader_Use(last);
        }
		else
			Shader_Free(shader);
    }
	else
	{
	    CL_RefPrintf(PRINT_ALL, "Program error:\n%s%s\n", (vsResult) ? "" : " Vertex shader ", (fsResult) ? "" : " Fragment shader ");
		Shader_Free(shader);
	}
}

void Shader_Free(glShader_t *shader)
{
	if(shader == currentShader)
		Shader_Use(NULL);

	if(shader->samplers)
	{
		free(shader->samplers);
		shader->samplers = NULL;
		shader->numSamplers = 0;
	}

	qglDeleteProgram(shader->program);
	shader->program = 0;

	if(shader->fragment && !--shader->fragment->links)
	{
		qglDeleteShader(shader->fragment->shader);
		shader->fragment->shader = 0;
	}
	shader->fragment = NULL;

	if(shader->vertex && !--shader->vertex->links)
	{
		qglDeleteShader(shader->vertex->shader);
		shader->vertex->shader = 0;
	}
	shader->vertex = NULL;
}

void Shader_Use(glShader_t *shader)
{
	if(shader == currentShader)
		return;

    if(shader && !shader->program)
		Shader_Compile(shader);
	else if(currentShader)
	{
		int i;
		for(i=1; i<currentShader->numSamplers; i++)
		{
			GL_SelectTexture(i);
			GL_Bind(NULL);
		}
		GL_SelectTexture(0);
	}

	qglUseProgram((shader) ? shader->program : 0);
	currentShader = shader;
}

void Shader_setImage(const char *name, image_t *image)
{
    int i, hash;

    hash = hashName(name);
    for(i=0; i<currentShader->numSamplers; i++)
    {
        if(currentShader->samplers[i] == hash)
        {
            GL_SelectTexture(i);
            GL_Bind(image);
            break;
        }
    }
}

static int __location;
static qboolean Shader_UniformLocation(const char *name)
{
    int i, hash;

	if(!GL_VERSION_2_0_supported || !(currentShader && currentShader->program))
	{		
		CL_RefPrintf(PRINT_ALL, "Shader_UniformLocation called at a wrong time\n");
		return qfalse;
	}

	hash = hashName(name);
    for(i=0; i<currentShader->numUniforms; i++)
    {
        if(currentShader->uniforms[i] == hash)
        {
            __location = currentShader->uniformsValues[i];
            return qtrue;
        }
    }

	__location = qglGetUniformLocation(currentShader->program, name);
	if(__location == -1)
	{
		CL_RefPrintf(PRINT_ALL, "location %s not found in %s\n", name, currentShader->name);
		return qfalse;
	}
	return qtrue;
}

void Shader_setConstant1i(const char *name, int c1)
{
    if(Shader_UniformLocation(name))
        qglUniform1i(__location, c1);
}

void Shader_setConstant1f(const char *name, float c1)
{
    if(Shader_UniformLocation(name))
        qglUniform1f(__location, c1);
}

void Shader_setConstant2f(const char *name, float c1, float c2)
{
    if(Shader_UniformLocation(name))
        qglUniform2f(__location, c1, c2);
}

void Shader_setConstant3f(const char *name, float c1, float c2, float c3)
{
    if(Shader_UniformLocation(name))
        qglUniform3f(__location, c1, c2, c3);
}

void Shader_setConstant4f(const char *name, float c1, float c2, float c3, float c4)
{
    if(Shader_UniformLocation(name))
        qglUniform4f(__location, c1, c2, c3, c4);
}

void Shader_setConstant3x3f(const char *name, const float *constant)
{
    if(Shader_UniformLocation(name))
        qglUniformMatrix3fv(__location, 1, GL_TRUE, (float *) &constant);
}

void Shader_setConstant4x4f(const char *name, const float *constant)
{
    if(Shader_UniformLocation(name))
        qglUniformMatrix4fv(__location, 1, GL_TRUE, (float *) &constant);
}

void Shader_setConstantArray1f(const char *name, const float *constant, unsigned int count)
{
    if(Shader_UniformLocation(name))
        qglUniform1fv(__location, count, constant);
}

void Shader_setConstantArray2f(const char *name, const float *constant, unsigned int count)
{
    if(Shader_UniformLocation(name))
        qglUniform2fv(__location, count, constant);
}

void Shader_setConstantArray3f(const char *name, const float *constant, unsigned int count)
{
    if(Shader_UniformLocation(name))
        qglUniform3fv(__location, count, constant);
}

void Shader_setConstantArray4f(const char *name, const float *constant, unsigned int count)
{
    if(Shader_UniformLocation(name))
        qglUniform4fv(__location, count, constant);
}

/*
textures/base_wall/comp3c
{
	{
		map textures/base_wall/comp3env.tga
		rgbGen identity
		tcGen environment
	}
	      
	{
		map $lightmap
		tcGen environment
		blendFunc GL_ONE GL_ONE
	}
 
	{
		map textures/base_wall/comp3c.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen identity
	}
 
	{
		map $lightmap
		blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
		rgbGen identity
	}
}
 
vertex:
	uniform vec3 viewOrigin;
 
	vec2 RB_CalcEnvironmentTexCoords( vec3 vertex, vec3 normal ) 
	{
		vec3 viewer = normalize(viewOrigin - gl_Vertex);
		float d = dot(normal, viewer) * 2;
		vec3 reflected = (normal * d - viewer) * 0.5;
		return vec2(0.5 + reflected.y, 0.5 - reflected.z);
	}
 
	void main()
	{
		gl_Position = ftransform();
 
		gl_TexCoord[0] = RB_CalcEnviromentTexCoords(gl_Vertex, gl_Normal);
		gl_TexCoord[1] = gl_MultiTexCoord0;
		gl_TexCoord[2] = gl_MultiTexCoord1;
	}
 
fragment:
	void main()
	{
		vec4 tex0 = texture2D(Image0, gl_TexCoord[0]);
		vec4 tex1 = texture2D(Lightmap, gl_TexCoord[0]);
		vec4 tex2 = texture2D(Image1, gl_TexCoord[1]);
		vec4 tex3 = texture2D(Lightmap, gl_TexCoord[2]);
 
		vec4 color;
 
		color = tex0;
		color = (tex1 * (1)) + (color * (1));
		color = (tex2 * (tex2.a)) + (color * (1.0 - tex2.a));
		color = (tex3 * (color)) + (color * (1.0 - color.a));
 
		gl_FragColor = color;
	}
*/

#define BUILD_STRING_SIZE 1024
static char vuniforms[BUILD_STRING_SIZE], vfunctions[BUILD_STRING_SIZE], vmain[BUILD_STRING_SIZE/2], vmain2[BUILD_STRING_SIZE/2];
static char funiforms[BUILD_STRING_SIZE], ffunctions[BUILD_STRING_SIZE], fmain[BUILD_STRING_SIZE];
static char varying[BUILD_STRING_SIZE];

void Replace_Char(char *str, int look, int set)
{
	char l = (char)look;
	do
	{
		char *pch = strstr(str, &l);
		if(!pch)
			break;
		pch[0] = (char)set;
	}
	while(1);
}

static int countStages(shader_t *pShader)
{
	int i;
	shaderStage_t *pStage;

	for(i=0; i<MAX_SHADER_STAGES; i++)
	{
		pStage = pShader->stages[i];
		if(!pStage)
            break;
	}

	return i - 2;
}

void Shader_Convert(shader_t *pShader)
{
	const char *color, *alpha, *tc, *sblend, *dblend;
	int i, cfuncs = 0, afuncs = 0, tfuncs = 0, topStage = -1, mfuncs = 0;
	int srcBlend, dstBlend, totBlend, tm, b, image;
	shaderStage_t *pStage;
	char *vText, *fText, tct[128];
	glShader_t shader;

	pShader->glShader = NULL;
	if(pShader->sort < SS_OPAQUE || pShader->glShaderFailed || (pShader->stages[0] && (pShader->stages[0]->stateBits & GLS_DSTBLEND_BITS) != GLS_DSTBLEND_ZERO && countStages(pShader)))
	{
		pShader->glShaderFailed = qtrue;
		return;
	}

	memset(&shader, 0, sizeof(glShader_t));

	memset(varying, 0, BUILD_STRING_SIZE);

	memset(vuniforms, 0, BUILD_STRING_SIZE);
	memset(vfunctions, 0, BUILD_STRING_SIZE);
	memset(vmain, 0, BUILD_STRING_SIZE/2);
	memset(vmain2, 0, BUILD_STRING_SIZE/2);

	memset(funiforms, 0, BUILD_STRING_SIZE);
	memset(ffunctions, 0, BUILD_STRING_SIZE);
	memset(fmain, 0, BUILD_STRING_SIZE);

	strcat(vmain,
		"void main()\n"
		"{\n"
		"	gl_Position = ftransform();\n"
	);

	strcat(fmain,
		"void main()\n"
		"{\n"
	);

	image = 0;
	for(i=0; i<MAX_SHADER_STAGES; i++)
	{
		char colorBuf[32], alphaBuf[32];
		pStage = pShader->stages[i];
		if(!pStage)
            break;
		topStage++;

		tc = NULL;
		memset(tct, 0, 128);

		color = NULL;
		alpha = "1.0";

		switch(pStage->rgbGen)
		{
		case CGEN_IDENTITY:
			break;
		default:
		case CGEN_IDENTITY_LIGHTING:
			cfuncs |= C_Identity_Lighting;
			color = "C_Identity_Lighting";
			break;
		case CGEN_LIGHTING_DIFFUSE:
			cfuncs |= C_Lighting_Diffuse;
			color = "C_Lighting_Diffuse";
			break;
		case CGEN_EXACT_VERTEX:
			cfuncs |= C_Exact_Vertex;
			color = "C_Exact_Vertex.rgb";
			alpha = "C_Exact_Vertex.a";
			break;
		case CGEN_CONST:
			sprintf(colorBuf, "vec3(%f, %f, %f)", pStage->constantColor[0], pStage->constantColor[1], pStage->constantColor[2]);
			color = colorBuf;
			sprintf(alphaBuf, "%f", pStage->constantColor[3]);
			alpha = alphaBuf;
			break;
		case CGEN_VERTEX:
			cfuncs |= C_Vertex;
			color = "C_Vertex";
			break;
		case CGEN_ONE_MINUS_VERTEX:
			cfuncs |= C_One_Minus_Vertex;
			color = "C_One_Minus_Vertex";
			break;
		case CGEN_FOG:
			cfuncs |= C_Fog;
			color = "C_Fog.rgb";
			alpha = "C_Fog.a";
			break;
		case CGEN_WAVEFORM:
			return;
		case CGEN_ENTITY:
			cfuncs |= C_Entity;
			color = "C_Entity.rgb";
			alpha = "C_Entity.a";
			break;
		case CGEN_ONE_MINUS_ENTITY:
			cfuncs |= C_One_Minus_Entity;
			color = "C_One_Minus_Entity.rgb";
			alpha = "C_One_Minus_Entity.a";
			break;
		}

		// alphaGen
		switch ( pStage->alphaGen )
		{
		case AGEN_IDENTITY:
		case AGEN_SKIP:
			break;
		case AGEN_CONST:
			sprintf(alphaBuf, "%f", pStage->constantColor[3]);
			alpha = alphaBuf;
			break;
		case AGEN_WAVEFORM:
			return;
		case AGEN_LIGHTING_SPECULAR:
			afuncs |= A_Lighting_Specular;
			alpha = "A_Lighting_Specular";
			break;
		case AGEN_ENTITY:
			afuncs |= A_Entity;
			alpha = "A_Entity";
			break;
		case AGEN_ONE_MINUS_ENTITY:
			afuncs |= A_One_Minus_Entity;
			alpha = "A_One_Minus_Entity";
			break;
		case AGEN_VERTEX:
			afuncs |= A_Vertex;
			alpha = "A_Vertex";
			break;
		case AGEN_ONE_MINUS_VERTEX:
			afuncs |= A_One_Minus_Vertex;
			alpha = "A_One_Minus_Vertex";
			break;
		case AGEN_PORTAL:
			afuncs |= A_Portal;
			alpha = "A_Portal";
			break;
		}

		strcat(fmain, va("	vec4 tUnit# = (", tc));
		if(color)
			strcat(fmain, va("vec4(%s, %s)", color, alpha));

		for(b=0; b<NUM_TEXTURE_BUNDLES; b++)
		{
			if(!pStage->bundle[b].image[0])
				break;

			switch(pStage->bundle[b].tcGen)
			{
			case TCGEN_IDENTITY:
				tc = "vec2(0.0, 0.0)";
				break;
			case TCGEN_TEXTURE:
				tfuncs |= T_Texture;
				tc = "gl_TexCoord[0].xy";
				break;
			case TCGEN_LIGHTMAP:
				tfuncs |= T_LightMap;
				tc = "gl_TexCoord[1].xy";
				break;
			case TCGEN_VECTOR:
				//CL_RefPrintf(PRINT_ALL, "Shader_Convert does not support TGEN_VECTOR\n");
				//return;
				break;
			case TCGEN_FOG:
				//CL_RefPrintf(PRINT_ALL, "Shader_Convert does not support TGEN_FOG\n");
				//return;
				break;
			case TCGEN_ENVIRONMENT_MAPPED:
				tfuncs |= T_Enviroment_Mapped;
				tc = "T_Enviroment_Mapped";
				break;
			case TCGEN_BAD:
				break;
			}

			if(pStage->bundle[b].numTexMods)
			{
				strcpy(tct, tc);
				tc = "TM_Stage^";

				strcat(varying, "varying vec2 TM_Stage^;\n");

				for ( tm = 0; tm < pStage->bundle[b].numTexMods ; tm++ )
				{
					switch ( pStage->bundle[b].texMods[tm].type )
					{
					default:
					case TMOD_NONE:
						tm = TR_MAX_TEXMODS;		// break out of for loop
						break;
					case TMOD_TURBULENT:
						tfuncs |= TM_Turbulent;
						strcpy(tct, va("TM_Turbulent(%s, %f, %f, %f)", tct, pStage->bundle[b].texMods[tm].wave.phase, pStage->bundle[b].texMods[tm].wave.frequency, pStage->bundle[b].texMods[tm].wave.amplitude));
						break;
					case TMOD_ENTITY_TRANSLATE:
						mfuncs |= M_CurrentEntTexCoord;
						tfuncs |= TM_Scroll;
						strcpy(tct, va("TM_Scroll(%s, M_CurrentEntTexCoord)", tct));
						break;
					case TMOD_SCROLL:
						tfuncs |= TM_Scroll;
						strcpy(tct, va("TM_Scroll(%s, vec2(%f, %f))", tct, pStage->bundle[0].texMods[tm].scroll[0], pStage->bundle[0].texMods[tm].scroll[1]));
						break;
					case TMOD_SCALE:
						strcpy(tct, va("%s * vec2(%f, %f)", tct, pStage->bundle[0].texMods[tm].scale[0], pStage->bundle[0].texMods[tm].scale[1]));
						break;
					case TMOD_STRETCH:
						//CL_RefPrintf(PRINT_ALL, "Shader_Convert does not support TMOD_STRETCH\n");
						//return;
						break;
					case TMOD_TRANSFORM:
						tfuncs |= TM_Transform;
						strcpy(tct, va("TM_Transform(%s, mat2(%f,%f,%f,%f), vec2(%f,%f))", tct, pStage->bundle[0].texMods[tm].matrix[0][0], pStage->bundle[0].texMods[tm].matrix[0][1], pStage->bundle[0].texMods[tm].matrix[1][0], pStage->bundle[0].texMods[tm].matrix[1][1], pStage->bundle[0].texMods[tm].translate[0], pStage->bundle[0].texMods[tm].translate[1]));
						return;
					case TMOD_ROTATE:
						tfuncs |= TM_Rotate;
						strcpy(tct, va("TM_Rotate(%s, %f)", tct, pStage->bundle[0].texMods[tm].rotateSpeed));
						return;
					}
				}

				strcat(vmain2, va("	TM_Stage^ = %s;\n", tct));
			}

			strcat(funiforms, "uniform sampler2D Texture^;\n");
			if(b)
				strcat(fmain, va(" %s texture2D(Texture^, %s)", (pStage->multitextureEnv==GL_ADD) ? "+" : "*", tc));
			else
				strcat(fmain, va("%stexture2D(Texture^, %s))", (color) ? " * " : "", tc));

			Replace_Char(varying, '^', '0' + image);
			Replace_Char(vmain2, '^', '0' + image);
			Replace_Char(fmain, '^', '0' + image);
			Replace_Char(funiforms, '^', '0' + image);
			image++;
		}

		strcat(fmain, ";\n");

		Replace_Char(fmain, '#', '0' + i);
	}

	strcat(fmain, "\n");

	for(i=0; i<MAX_SHADER_STAGES; i++)
	{
		pStage = pShader->stages[i];
		if(!pStage)
            break;

		if(i == topStage)
			strcat(fmain, "	gl_FragColor = clamp(");
		else if(i)
			strcat(fmain, "	color = ");
		else
			strcat(fmain, "	vec4 color = ");

		if(pStage->stateBits & GLS_ATEST_BITS)
		{
			int t = pStage->stateBits & GLS_ATEST_BITS;
			mfuncs |=	(t==GLS_ATEST_GT_0) ? M_ATEST_GT_0 :
						(t==GLS_ATEST_LT_80) ? M_ATEST_LT_80 :
						(t==GLS_ATEST_GE_80) ? M_ATEST_GE_80 : 0;
			if(i)
				strcat(fmain,	(t==GLS_ATEST_GT_0) ? "M_ATEST_GT_0(color, tUnit#, " :
								(t==GLS_ATEST_LT_80) ? "M_ATEST_LT_80(color, tUnit#, " :
								(t==GLS_ATEST_GE_80) ? "M_ATEST_GE_80(color, tUnit#, " : ""
				);
			else
				strcat(fmain,	(t==GLS_ATEST_GT_0) ? "M_ATEST_GT_0d(tUnit#, " :
								(t==GLS_ATEST_LT_80) ? "M_ATEST_LT_80d(tUnit#, " :
								(t==GLS_ATEST_GE_80) ? "M_ATEST_GE_80d(tUnit#, " : ""
				);
		}

		dstBlend = (pStage->stateBits & GLS_DSTBLEND_BITS) ? pStage->stateBits & GLS_DSTBLEND_BITS : GLS_DSTBLEND_ZERO;
		srcBlend = (pStage->stateBits & GLS_SRCBLEND_BITS) ? pStage->stateBits & GLS_SRCBLEND_BITS : GLS_SRCBLEND_ONE;

		totBlend = dstBlend + srcBlend;
		if(!i || totBlend == GLS_SRCBLEND_ONE + GLS_DSTBLEND_ZERO)
		{
			strcat(fmain, "tUnit#");
		}
		else if(totBlend == GLS_SRCBLEND_SRC_ALPHA + GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA)
		{
			strcat(fmain, "mix(color, tUnit#, tUnit#.a)");
		}
		else if(totBlend == GLS_SRCBLEND_DST_COLOR + GLS_DSTBLEND_ZERO || totBlend == GLS_SRCBLEND_ZERO + GLS_DSTBLEND_SRC_COLOR)
		{
			strcat(fmain, "tUnit# * color");
		}
		else if(totBlend == GLS_SRCBLEND_ONE + GLS_DSTBLEND_ONE)
		{
			strcat(fmain, "tUnit# + color");
		}
		else
		{
			sblend = NULL;
			switch(srcBlend)
			{
			case GLS_SRCBLEND_ZERO:
				sblend = "vec4(0,0,0,0)";
				break;
			default:
			case GLS_SRCBLEND_ONE:
				sblend = "vec4(1,1,1,1)";
				break;
			case GLS_SRCBLEND_DST_COLOR:
				sblend = "color";
				break;
			case GLS_SRCBLEND_ONE_MINUS_DST_COLOR:
				sblend = "(vec4(1,1,1,1) - clamp(color, 0, 1))";
				break;
			case GLS_SRCBLEND_SRC_ALPHA:
				sblend = "tUnit#.a";
				break;
			case GLS_SRCBLEND_ONE_MINUS_SRC_ALPHA:
				sblend = "(1.0 - clamp(tUnit#.a, 0, 1))";
				break;
			case GLS_SRCBLEND_DST_ALPHA:
				sblend = "color.a";
				break;
			case GLS_SRCBLEND_ONE_MINUS_DST_ALPHA:
				sblend = "(1.0 - clamp(color.a, 0, 1))";
				break;
			}

			dblend = NULL;
			switch(dstBlend)
			{
			default:
			case GLS_DSTBLEND_ZERO:
				dblend = "vec4(0,0,0,0)";
				break;
			case GLS_DSTBLEND_ONE:
				dblend = "vec4(1,1,1,1)";
				break;
			case GLS_DSTBLEND_SRC_COLOR:
				dblend = "tUnit#";
				break;
			case GLS_DSTBLEND_ONE_MINUS_SRC_COLOR:
				dblend = "(vec4(1.0) - clamp(tUnit#, 0, 1))";
				break;
			case GLS_DSTBLEND_SRC_ALPHA:
				dblend = "tUnit#.a";
				break;
			case GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA:
				dblend = "(1.0 - clamp(tUnit#.a, 0, 1))";
				break;
			case GLS_DSTBLEND_DST_ALPHA:
				dblend = "color.a";
				break;
			case GLS_DSTBLEND_ONE_MINUS_DST_ALPHA:
				dblend = "(1.0 - clamp(color.a, 0, 1))";
				break;
			}

			strcat(fmain, va("(tUnit# * %s) + (color * %s)", sblend, dblend));
		}

		if(pStage->stateBits & GLS_ATEST_BITS)
			strcat(fmain, ")");

		if(i == topStage)
			strcat(fmain, ", 0, 500)");
		strcat(fmain, ";\n");

		Replace_Char(fmain, '#', '0' + i);
		Replace_Char(funiforms, '#', '0' + i);
	}

	if(cfuncs & (C_Vertex | C_One_Minus_Vertex | C_Identity_Lighting) || afuncs & (A_Vertex | A_One_Minus_Vertex))
		strcat(vuniforms, "uniform float identityLight;\n");

	if(afuncs & (A_Lighting_Specular | A_Portal) || tfuncs & T_Enviroment_Mapped)
		strcat(vuniforms, "uniform vec3 viewOrigin;\n");

	if(tfuncs & (TM_Scroll | TM_Turbulent | TM_Rotate))
		strcat(vuniforms, "uniform float shaderTime;\n");	

	if(cfuncs & C_Identity_Lighting)
	{
		strcat(varying, "varying vec3 C_Identity_Lighting;\n");
		strcat(vmain, "	C_Identity_Lighting = vec3(identityLight);\n");
	}
	if(cfuncs & C_Lighting_Diffuse)
	{
		strcat(varying, "varying vec3 C_Lighting_Diffuse;\n");
		strcat(vuniforms, "uniform vec3 ambientLight;\n");
		strcat(vuniforms, "uniform vec3 directedLight;\n");
		strcat(vuniforms, "uniform vec3 lightDir;\n");
		strcat(vmain, "	C_Lighting_Diffuse = ambientLight + clamp((dot(gl_Normal, lightDir) * directedLight), 0.0, 1.0);\n");
	}
	if(cfuncs & C_Exact_Vertex)
	{
		strcat(varying, "varying vec4 C_Exact_Vertex;\n");
		strcat(vmain, "	C_Exact_Vertex = gl_Color;\n");
	}
	if(cfuncs & C_Vertex)
	{
		strcat(varying, "varying vec3 C_Vertex;\n");
		strcat(vmain, "	C_Vertex = gl_Color.rgb * identityLight;\n");
	}
	if(cfuncs & C_One_Minus_Vertex)
	{
		strcat(varying, "varying vec3 C_One_Minus_Vertex;\n");
		strcat(vmain, "	C_One_Minus_Vertex = (vec3(1.0) - gl_Color.rgb) * identityLight;\n");
	}
	if(cfuncs & C_Fog)
	{
		strcat(funiforms, "uniform vec4 C_Fog;\n");
	}
	if(cfuncs & C_Entity)
	{
		strcat(funiforms, "uniform vec4 C_Entity;\n");
	}
	if(cfuncs & C_One_Minus_Entity)
	{
		strcat(funiforms, "uniform vec4 C_One_Minus_Entity;\n");
	}

	if(afuncs & A_Lighting_Specular)
	{
		strcat(varying, "varying float A_Lighting_Specular;\n");
		strcat(vfunctions,
			"void RB_CalcSpecularAlpha()\n"
			"{\n"
			"	vec3 light_Origin = vec3(-930, 1980, 96);\n"
			"	vec3 reflection = reflect(normalize(light_Origin - gl_Vertex.xyz), gl_Normal);\n"
			"	vec3 viewer = viewOrigin - gl_Vertex.xyz;\n"
			"	float l = dot(reflection, viewer);\n"
			"	if(l < 0)\n"
			"		A_Lighting_Specular = 0;\n"
			"	else\n"
			"		A_Lighting_Specular = pow(l / length(viewer), 2);\n"
			"}\n"
			"\n"
		);
		strcat(vmain, "	RB_CalcSpecularAlpha();\n");
	}
	if(afuncs & A_Entity)
	{
		strcat(funiforms, "uniform float A_Entity;\n");
	}
	if(afuncs & A_One_Minus_Entity)
	{
		strcat(funiforms, "uniform float A_One_Minus_Entity;\n");
	}
	if(afuncs & A_Vertex)
	{
		strcat(varying, "varying float A_Vertex;\n");
		strcat(vmain, "	A_Vertex = gl_Color.a;\n");
	}
	if(afuncs & A_One_Minus_Vertex)
	{
		strcat(varying, "varying float A_One_Minus_Vertex;\n");
		strcat(vmain, "	A_One_Minus_Vertex = (1.0 - gl_Color.a) * identityLight;\n");
	}
	if(afuncs & A_Portal)
	{
		strcat(varying, "varying float A_Portal;\n");
		strcat(vuniforms, "uniform float portalRange;\n");
		strcat(vmain, "	A_Portal = max(length(viewOrigin - vec3(gl_Vertex)) / portalRange, 0.0);\n");
	}

	if(tfuncs & T_Texture)
	{
		strcat(vmain, "	gl_TexCoord[0] = gl_MultiTexCoord0;\n");
	}
	if(tfuncs & T_LightMap)
	{
		strcat(vmain, "	gl_TexCoord[1] = gl_MultiTexCoord1;\n");
	}
	if(tfuncs & T_Enviroment_Mapped)
	{
		strcat(varying, "varying vec2 T_Enviroment_Mapped;\n");
		strcat(vfunctions,
			"void RB_CalcEnvironmentTexCoords()\n"
			"{\n"
			"	vec3 reflected = reflect(normalize(viewOrigin - gl_Vertex.xyz), gl_Normal);\n"
			"	T_Enviroment_Mapped = vec2(0.5 + reflected.y, 0.5 - reflected.z) * 0.5;\n"
			"}\n"
			"\n"
		);
		strcat(vmain, "	RB_CalcEnvironmentTexCoords();\n");
	}
	if(tfuncs & TM_Scroll)
	{
		strcat(vfunctions,
			"vec2 TM_Scroll(vec2 st, vec2 scroll)\n"
			"{\n"
			"	return st + scroll * shaderTime;\n"
			"}\n"
			"\n"
		);
	}
	if(tfuncs & TM_Transform)
	{
		strcat(vfunctions,
			"vec2 TM_Transform(vec2 st, mat2 matrix, vec2 translate)\n"
			"{\n"
			"	return st * matrix + translate;\n"
			"}\n"
			"\n"
		);
	}
	if(tfuncs & TM_Rotate)
	{
		strcat(vfunctions,
			"vec2 TM_Rotate(vec2 st, float rotate)\n"
			"{\n"
			"	float rsin = sin(-rotate * shaderTime);\n"
			"	float rcos = cos(-rotate * shaderTime);\n"
			"	return st * mat2(rcos, -rsin, rsin, rcos) + vec2(0.5 - 0.5 * rcos - 0.5 * rsin, 0.5 - 0.5 * rsin - 0.5 * rcos);\n"
			"}\n"
			"\n"
		);
	}
	if(tfuncs & TM_Turbulent)
	{
		strcat(vfunctions,
			"vec2 TM_Turbulent(vec2 st, float phase, float frequency, float amplitude)\n"
			"{\n"
			"	float now = phase + shaderTime * frequency;\n"
			"	return st + vec2(cos(st.x + now), sin(st.y + now)) * amplitude;\n"
			"}\n"
			"\n"
		);
	}

	if(mfuncs & M_CurrentEntTexCoord)
	{
		strcat(vuniforms, "uniform vec2 M_CurrentEntTexCoord;\n");
	}
	if(mfuncs & M_ATEST_GT_0)
	{
		strcat(ffunctions,
			"vec4 M_ATEST_GT_0(vec4 oldVal, vec4 incVal, vec4 blendVal) {\n"
			"	return mix(oldVal, blendVal, step(0, incVal.a));\n"
			"}\n"
		);
		strcat(ffunctions,
			"vec4 M_ATEST_GT_0d(vec4 incVal, vec4 blendVal) {\n"
			"	if(incVal.a < 0.0) discard;\n"
			"	return blendVal;\n"
			"}\n"
		);
	}
	if(mfuncs & M_ATEST_LT_80)
	{
		strcat(ffunctions,
			"vec4 M_ATEST_LT_80(vec4 oldVal, vec4 incVal, vec4 blendVal) {\n"
			"	return mix(blendVal, oldVal, step(0.5, incVal.a));\n"
			"}\n"
		);
		strcat(ffunctions,
			"vec4 M_ATEST_LT_80d(vec4 incVal, vec4 blendVal) {\n"
			"	if(incVal.a >= 0.5) discard;\n"
			"	return blendVal;\n"
			"}\n"
		);
	}
	if(mfuncs & M_ATEST_GE_80)
	{
		strcat(ffunctions,
			"vec4 M_ATEST_GE_80(vec4 oldVal, vec4 incVal, vec4 blendVal) {\n"
			"	return mix(oldVal, blendVal, step(0.499, incVal.a));\n"
			"}\n"
		);
		strcat(ffunctions,
			"vec4 M_ATEST_GE_80d(vec4 incVal, vec4 blendVal) {\n"
			"	if(incVal.a < 0.5) discard;\n"
			"	return blendVal;\n"
			"}\n"
		);
	}

	strcat(vmain2,
		"}\n"
	);

	strcat(fmain,
	//	"	gl_FragColor.g = 1;\n"
		"}\n"
	);

	vText = (char *)malloc(strlen(varying) + strlen(vuniforms) + strlen(vfunctions) + strlen(vmain) + strlen(vmain2) + 4);
	memset(vText, 0, strlen(varying) + strlen(vuniforms) + strlen(vfunctions) + strlen(vmain) + strlen(vmain2) + 4);
	sprintf(vText, "%s\n%s\n%s%s%s", varying, vuniforms, vfunctions, vmain, vmain2);
	shader.vertexText = vText;

	fText = (char *)malloc(strlen(varying) + strlen(funiforms) + strlen(ffunctions) + strlen(fmain) + 4);
	memset(fText, 0, strlen(varying) + strlen(funiforms) + strlen(ffunctions) + strlen(fmain) + 4);
	sprintf(fText, "%s\n%s\n%s%s", varying, funiforms, ffunctions, fmain);
	shader.fragmentText = fText;

	Shader_Compile(&shader);

//	if(tfuncs & TM_Turbulent)
//		CL_RefPrintf(PRINT_ALL, "%s%s", vText, fText);

	free(vText);
	shader.vertexText = NULL;
	free(fText);
	shader.fragmentText = NULL;

	CL_RefPrintf(PRINT_DEVELOPER, "conversion of %s ", pShader->name);
	if(shader.program)
	{
		CL_RefPrintf(PRINT_DEVELOPER, "OK\n");
		pShader->glShader = (glShader_t *)Hunk_Alloc(sizeof(glShader_t), h_low);
		Com_Memcpy(pShader->glShader, &shader, sizeof(glShader_t));
		pShader->glShader->name = pShader->name;
		pShader->glShader->cfuncs = cfuncs;
		pShader->glShader->afuncs = afuncs;
		pShader->glShader->tfuncs = tfuncs;
		pShader->glShader->mfuncs = mfuncs;
		pShader->glShader->statebits = (!topStage) ? pShader->stages[0]->stateBits : pShader->stages[0]->stateBits & ~GLS_ATEST_BITS;
	}
	else
	{
		CL_RefPrintf(PRINT_DEVELOPER, "FAILED\n");
		pShader->glShaderFailed = qtrue;
	}
}
