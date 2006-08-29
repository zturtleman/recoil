/*
===========================================================================
Copyright(C) 1999-2005 Id Software, Inc.
 
This file is part of Quake III Arena source code.
 
Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or(at your option) any later version.
 
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

backEndData_t	*backEndData[SMP_FRAMES];
backEndState_t	backEnd;


static float	s_flipMatrix[16] = {
                                    // convert from our coordinate system(looking down X)
                                    // to OpenGL's coordinate system(looking down -Z)
                                    0, 0, -1, 0,
                                    -1, 0, 0, 0,
                                    0, 1, 0, 0,
                                    0, 0, 0, 1
                                };

void	RB_SetGL2D(void);
void	RB_SetGL2DSize(int width, int height);

/*
** GL_Bind
*/
void GL_Bind(image_t *image)
{
    int texnum;

    if(!image)
    {
        //CL_RefPrintf(PRINT_WARNING, "GL_Bind: NULL image\n");
        //texnum = 0;
		glState.currenttextures[glState.currenttmu] = 0;
        qglBindTexture(GL_TEXTURE_2D, 0);
        return;
    }
    else
    {
        texnum = image->texnum;
    }

    if(r_nobind->integer && tr.dlightImage)
    {		// performance evaluation option
        texnum = tr.dlightImage->texnum;
    }

    if(glState.currenttextures[glState.currenttmu] != texnum)
    {
        image->frameUsed = tr.frameCount;
        glState.currenttextures[glState.currenttmu] = texnum;
        qglBindTexture(GL_TEXTURE_2D, texnum);
    }
}

/*
** GL_SelectTexture
*/
void GL_SelectTexture(int unit)
{
    if(glState.currenttmu == unit)
        return;

    qglActiveTexture(GL_TEXTURE0 + unit);
    qglClientActiveTexture(GL_TEXTURE0 + unit);

    glState.currenttmu = unit;
}

/*
** GL_Cull
*/
void GL_Cull(int cullType)
{
    if(glState.faceCulling == cullType)
        return;

    glState.faceCulling = cullType;

    if(cullType == CT_TWO_SIDED)
        qglDisable(GL_CULL_FACE);
    else
    {
        qglEnable(GL_CULL_FACE);
        qglCullFace(
            (cullType == CT_BACK_SIDED)
            ? ((backEnd.viewParms.isMirror) ? GL_FRONT : GL_BACK)
                    : ((backEnd.viewParms.isMirror) ? GL_BACK : GL_FRONT)
                );
    }
}

/*
** GL_TexEnv
*/
void GL_TexEnv(int env)
{
    if(env == glState.texEnv[glState.currenttmu])
        return;

    glState.texEnv[glState.currenttmu] = env;

    switch(env)
    {
    case GL_MODULATE:
        case GL_REPLACE:
    case GL_DECAL:
    case GL_ADD:
        qglTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, env);
        break;
    default:
        Com_Error(ERR_DROP, "GL_TexEnv: invalid env '%d' passed\n", env);
        break;
    }
}

/*
** GL_State
**
** This routine is responsible for setting the most commonly changed state
** in Q3.
*/
void GL_State(unsigned long stateBits)
{
    unsigned long diff = stateBits ^ glState.glStateBits;

    if(!diff)
        return;

    //
    // check depthFunc bits
    if(diff & GLS_DEPTHFUNC_EQUAL)
        qglDepthFunc((stateBits & GLS_DEPTHFUNC_EQUAL) ? GL_EQUAL : GL_LEQUAL);

    //
    // check blend bits
    if(diff & (GLS_SRCBLEND_BITS | GLS_DSTBLEND_BITS | GLS_ASRCBLEND_BITS | GLS_ADSTBLEND_BITS))
    {
        if(stateBits & (GLS_SRCBLEND_BITS | GLS_DSTBLEND_BITS | GLS_ASRCBLEND_BITS | GLS_ADSTBLEND_BITS))
        {
            int srcBlend = (stateBits & GLS_SRCBLEND_BITS) ? stateBits & GLS_SRCBLEND_BITS : GLS_SRCBLEND_ONE;
            int dstBlend = (stateBits & GLS_DSTBLEND_BITS) ? stateBits & GLS_DSTBLEND_BITS : GLS_DSTBLEND_ZERO;
            int asrcBlend = (stateBits & GLS_ASRCBLEND_BITS) ? stateBits & GLS_ASRCBLEND_BITS : GLS_ASRCBLEND_ONE;
            int adstBlend = (stateBits & GLS_ADSTBLEND_BITS) ? stateBits & GLS_ADSTBLEND_BITS : GLS_ADSTBLEND_ZERO;

            qglEnable(GL_BLEND);
            qglBlendFuncSeparate(
                (srcBlend==GLS_SRCBLEND_ZERO) ? GL_ZERO :
                (srcBlend==GLS_SRCBLEND_ONE) ? GL_ONE :
                (srcBlend==GLS_SRCBLEND_DST_COLOR) ? GL_DST_COLOR :
                (srcBlend==GLS_SRCBLEND_ONE_MINUS_DST_COLOR) ? GL_ONE_MINUS_DST_COLOR :
                (srcBlend==GLS_SRCBLEND_SRC_ALPHA) ? GL_SRC_ALPHA :
                (srcBlend==GLS_SRCBLEND_ONE_MINUS_SRC_ALPHA) ? GL_ONE_MINUS_SRC_ALPHA :
                (srcBlend==GLS_SRCBLEND_DST_ALPHA) ? GL_DST_ALPHA :
                (srcBlend==GLS_SRCBLEND_ONE_MINUS_DST_ALPHA) ? GL_ONE_MINUS_DST_ALPHA :
                (srcBlend==GLS_SRCBLEND_ALPHA_SATURATE) ? GL_SRC_ALPHA_SATURATE : GL_ONE,
                (dstBlend==GLS_DSTBLEND_ZERO) ? GL_ZERO :
                (dstBlend==GLS_DSTBLEND_ONE) ? GL_ONE :
                (dstBlend==GLS_DSTBLEND_SRC_COLOR) ? GL_SRC_COLOR :
                (dstBlend==GLS_DSTBLEND_ONE_MINUS_SRC_COLOR) ? GL_ONE_MINUS_SRC_COLOR :
                (dstBlend==GLS_DSTBLEND_SRC_ALPHA) ? GL_SRC_ALPHA :
                (dstBlend==GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA) ? GL_ONE_MINUS_SRC_ALPHA :
                (dstBlend==GLS_DSTBLEND_DST_ALPHA) ? GL_DST_ALPHA :
                (dstBlend==GLS_DSTBLEND_ONE_MINUS_DST_ALPHA) ? GL_ONE_MINUS_DST_ALPHA : GL_ZERO,
                (asrcBlend==GLS_ASRCBLEND_ZERO) ? GL_ZERO :
                (asrcBlend==GLS_ASRCBLEND_ONE) ? GL_ONE :
                (asrcBlend==GLS_ASRCBLEND_DST_COLOR) ? GL_DST_COLOR :
                (asrcBlend==GLS_ASRCBLEND_ONE_MINUS_DST_COLOR) ? GL_ONE_MINUS_DST_COLOR :
                (asrcBlend==GLS_ASRCBLEND_SRC_ALPHA) ? GL_SRC_ALPHA :
                (asrcBlend==GLS_ASRCBLEND_ONE_MINUS_SRC_ALPHA) ? GL_ONE_MINUS_SRC_ALPHA :
                (asrcBlend==GLS_ASRCBLEND_DST_ALPHA) ? GL_DST_ALPHA :
                (asrcBlend==GLS_ASRCBLEND_ONE_MINUS_DST_ALPHA) ? GL_ONE_MINUS_DST_ALPHA :
                (asrcBlend==GLS_ASRCBLEND_ALPHA_SATURATE) ? GL_SRC_ALPHA_SATURATE : GL_ONE,
                (adstBlend==GLS_ADSTBLEND_ZERO) ? GL_ZERO :
                (adstBlend==GLS_ADSTBLEND_ONE) ? GL_ONE :
                (adstBlend==GLS_ADSTBLEND_SRC_COLOR) ? GL_SRC_COLOR :
                (adstBlend==GLS_ADSTBLEND_ONE_MINUS_SRC_COLOR) ? GL_ONE_MINUS_SRC_COLOR :
                (adstBlend==GLS_ADSTBLEND_SRC_ALPHA) ? GL_SRC_ALPHA :
                (adstBlend==GLS_ADSTBLEND_ONE_MINUS_SRC_ALPHA) ? GL_ONE_MINUS_SRC_ALPHA :
                (adstBlend==GLS_ADSTBLEND_DST_ALPHA) ? GL_DST_ALPHA :
                (adstBlend==GLS_ADSTBLEND_ONE_MINUS_DST_ALPHA) ? GL_ONE_MINUS_DST_ALPHA : GL_ZERO
            );
        }
        else
            qglDisable(GL_BLEND);
    }

    //
    // check depthmask
    if(diff & GLS_DEPTHMASK_TRUE)
        qglDepthMask((stateBits & GLS_DEPTHMASK_TRUE) ? GL_TRUE : GL_FALSE);

    //
    // fill/line mode
    if(diff & GLS_POLYMODE_LINE)
        qglPolygonMode(GL_FRONT_AND_BACK, (stateBits & GLS_POLYMODE_LINE) ? GL_LINE : GL_FILL);

    //
    // depthtest
    if(diff & GLS_DEPTHTEST_DISABLE)
        (stateBits & GLS_DEPTHTEST_DISABLE) ? qglDisable(GL_DEPTH_TEST) : qglEnable(GL_DEPTH_TEST);

    //
    // alpha test
    if(diff & GLS_ATEST_BITS)
    {
        if(stateBits & GLS_ATEST_BITS)
        {
            int atest = stateBits & GLS_ATEST_BITS;
            qglEnable(GL_ALPHA_TEST);
            qglAlphaFunc(
                (atest==GLS_ATEST_GT_0) ? GL_GREATER : ((atest==GLS_ATEST_LT_80) ? GL_LESS : GL_GEQUAL),
                (atest==GLS_ATEST_GT_0) ? 0.0f : 0.5f
            );
        }
        else
            qglDisable(GL_ALPHA_TEST);
    }

    glState.glStateBits = stateBits;
}

/*
================
RB_Hyperspace
 
A player has predicted a teleport, but hasn't arrived yet
================
*/
static void RB_Hyperspace(void)
{
    float c = (backEnd.refdef.time & 255) / 255.0f;
    qglClearColor(c, c, c, 1);
    qglClear(GL_COLOR_BUFFER_BIT);
    backEnd.isHyperspace = qtrue;
}

static void SetViewportAndScissor(void)
{
    qglMatrixMode(GL_PROJECTION);
    qglLoadMatrixf(backEnd.viewParms.projectionMatrix);
    qglMatrixMode(GL_MODELVIEW);

    // set the window clipping
    qglViewport(backEnd.viewParms.viewportX, backEnd.viewParms.viewportY, backEnd.viewParms.viewportWidth, backEnd.viewParms.viewportHeight);
    qglScissor(backEnd.viewParms.viewportX, backEnd.viewParms.viewportY, backEnd.viewParms.viewportWidth, backEnd.viewParms.viewportHeight);
}

/*
=================
RB_BeginDrawingView
 
Any mirrored or portaled views have already been drawn, so prepare
to actually render the visible surfaces for this view
=================
*/

void RB_BeginDrawingView(void)
{
    int clearBits = 0;

    // sync with gl if needed
    if(r_finish->integer == 1 && !glState.finishCalled)
    {
        qglFinish();
        glState.finishCalled = qtrue;
    }
    if(r_finish->integer == 0)
        glState.finishCalled = qtrue;

    // we will need to change the projection matrix before drawing
    // 2D images again
    backEnd.projection2D = qfalse;

    //
    // set the modelview matrix for the viewer
    SetViewportAndScissor();

    // ensures that depth writes are enabled for the depth clear
    GL_State(GLS_DEFAULT);
    // clear relevant buffers
    clearBits = GL_DEPTH_BUFFER_BIT;

    if(r_measureOverdraw->integer || r_shadows->integer == 2)
        clearBits |= GL_STENCIL_BUFFER_BIT;

    if(r_fastsky->integer && !(backEnd.refdef.rdflags & RDF_NOWORLDMODEL))
    {
        clearBits |= GL_COLOR_BUFFER_BIT;	// FIXME: only if sky shaders have been used
        qglClearColor(0.0f, 0.0f, 0.0f, 1.0f);	// FIXME: get color of sky
    }
    qglClear(clearBits);

    if((backEnd.refdef.rdflags & RDF_HYPERSPACE))
    {
        RB_Hyperspace();
        return;
    }
    else
        backEnd.isHyperspace = qfalse;

    glState.faceCulling = -1;		// force face culling to set next time

    // we will only draw a sun if there was sky rendered in this view
    backEnd.skyRenderedThisView = qfalse;

    // clip to the plane of the portal
    if(backEnd.viewParms.isPortal)
    {
        float	plane[4];
        double	plane2[4];

        plane[0] = backEnd.viewParms.portalPlane.normal[0];
        plane[1] = backEnd.viewParms.portalPlane.normal[1];
        plane[2] = backEnd.viewParms.portalPlane.normal[2];
        plane[3] = backEnd.viewParms.portalPlane.dist;

        plane2[0] = DotProduct(backEnd.viewParms.or.axis[0], plane);
        plane2[1] = DotProduct(backEnd.viewParms.or.axis[1], plane);
        plane2[2] = DotProduct(backEnd.viewParms.or.axis[2], plane);
        plane2[3] = DotProduct(plane, backEnd.viewParms.or.origin) - plane[3];

        qglLoadMatrixf(s_flipMatrix);
        qglClipPlane(GL_CLIP_PLANE0, plane2);
        qglEnable(GL_CLIP_PLANE0);
    }
    else
        qglDisable(GL_CLIP_PLANE0);
}

#define	MAC_EVENT_PUMP_MSEC		5

/*
==================
RB_RenderDrawSurfList
==================
*/
fboSet_t Offscreen;
fboSet_t BlurSet;

glShader_t blurProgram = {
    "varying vec2 texCoord0;\n"
    "varying vec2 texCoord1;\n"
    "varying vec2 texCoord2;\n"
    "varying vec2 texCoord3;\n"
    "\n"
    "uniform vec2 sample0, sample1, sample2, sample3;\n"
    "\n"
    "void main() {\n"
    "	gl_Position = gl_Vertex;\n"
    "\n"
    "	vec2 texCoord = gl_Vertex.xy * 0.5 + 0.5;\n"
    "	texCoord0 = texCoord + sample0;\n"
    "	texCoord1 = texCoord + sample1;\n"
    "	texCoord2 = texCoord + sample2;\n"
    "	texCoord3 = texCoord + sample3;\n"
    "}\n",

    "uniform sampler2D Image;\n"
    "\n"
    "varying vec2 texCoord0;\n"
    "varying vec2 texCoord1;\n"
    "varying vec2 texCoord2;\n"
    "varying vec2 texCoord3;\n"
    "\n"
    "void main() {\n"
    "	vec3 base = texture2D(Image, texCoord0).rgb;\n"
    "	base     += texture2D(Image, texCoord1).rgb;\n"
    "	base     += texture2D(Image, texCoord2).rgb;\n"
    "	base     += texture2D(Image, texCoord3).rgb;\n"
    "\n"
    "	gl_FragColor.rgb = 0.25 * base.rgb;\n"
    "	gl_FragColor.a = 1.0;\n"
    "}\n",
	"blurProgram"
};

glShader_t toneProgram = {
    "varying vec2 texCoord;\n"
    "varying vec4 oNoise;\n"
    "\n"
    "uniform vec4 iNoise;\n"
    "\n"
    "void main() {\n"
    "	gl_Position = gl_Vertex;\n"
    "\n"
    "	texCoord = gl_Vertex.xy * 0.5 + 0.5;\n"
    "	oNoise = vec4(texCoord.x * iNoise.x, texCoord.y * iNoise.y, texCoord.x * iNoise.z, texCoord.y * iNoise.a);\n"
    "}\n",

    "uniform sampler2D Base;\n"
    "uniform sampler2D Blur;\n"
    "\n"
    "uniform float exposure;\n"
    "uniform float range;\n"
    "\n"
    "varying vec2 texCoord;\n"
    "\n"
    "void main() {\n"
    "	vec4 base = texture2D(Base, texCoord);\n"
    "	vec4 blur = texture2D(Blur, texCoord) * range;\n"
    "\n"
    "	vec4 color = base + blur;\n"
    "\n"
    "	gl_FragColor.rgb = (1.0 - exp(-exposure * color.rgb));\n"
    "//	gl_FragColor.g = base.a;\n"
    "	gl_FragColor.a = 1.0;\n"
    "}\n",
	"toneProgram"
};

glShader_t convertProgram = {
    "varying vec2 texCoord0;\n"
    "varying vec2 texCoord1;\n"
    "varying vec2 texCoord2;\n"
    "varying vec2 texCoord3;\n"
    "\n"
    "uniform vec2 halfPixel;\n"
    "\n"
    "void main(){\n"
    "	gl_Position = gl_Vertex;\n"
    "\n"
    "	vec2 texCoord = gl_Vertex.xy * 0.5 + 0.5;\n"
    "\n"
    "	texCoord0 = texCoord + halfPixel * vec2( 1,  1);\n"
    "	texCoord1 = texCoord + halfPixel * vec2(-1,  1);\n"
    "	texCoord2 = texCoord + halfPixel * vec2(-1, -1);\n"
    "	texCoord3 = texCoord + halfPixel * vec2( 1, -1);\n"
    "}\n",

    "uniform sampler2D Image;\n"
    "\n"
    "uniform float invRange;\n"
    "uniform float blurStrength;\n"
    "\n"
    "varying vec2 texCoord0;\n"
    "varying vec2 texCoord1;\n"
    "varying vec2 texCoord2;\n"
    "varying vec2 texCoord3;\n"
    "\n"
    "void main() {\n"
    "	// Downscale and convert to fixed point\n"
    "	vec4 base = texture2D(Image, texCoord0);\n"
    "	base     += texture2D(Image, texCoord1);\n"
    "	base     += texture2D(Image, texCoord2);\n"
    "	base     += texture2D(Image, texCoord3);\n"
    "\n"
    "	base.rgb = pow(base.rgb, vec3(blurStrength));\n"
    "\n"
    "	// Clamp for nvidia ...\n"
    "	gl_FragColor.rgb = max(base.rgb * invRange, 0);\n"
    "	gl_FragColor.a = 1.0;\n"
    "}\n",
	"convertProgram"
};

void RB_RenderDrawSurfList(drawSurf_t *drawSurfs, int numDrawSurfs)
{
    shader_t		*shader, *oldShader;
    int				fogNum, oldFogNum;
    int				entityNum, oldEntityNum;
    int				dlighted, oldDlighted;
    qboolean		depthRange, oldDepthRange;
    int				i;
    drawSurf_t		*drawSurf;
    int				oldSort;
    float			originalTime;
    qboolean		BlurContinue = qfalse;
#ifdef __MACOS__
    int				macEventTime;

    Sys_PumpEvents();		// crutch up the mac's limited buffer queue size

    // we don't want to pump the event loop too often and waste time, so
    // we are going to check every shader change
    macEventTime = CL_ScaledMilliseconds() + MAC_EVENT_PUMP_MSEC;
#endif

    // save original time for entity shader offsets
    originalTime = backEnd.refdef.floatTime;

    if(!(backEnd.refdef.rdflags & RDF_NOWORLDMODEL) && GL_EXT_framebuffer_object_supported && r_blur_enabled->integer)
    {
        Fbo_applySet(&Offscreen);
        BlurContinue = Fbo_IsUsable();
    }

    // clear the z buffer, set the modelview, etc
    RB_BeginDrawingView();

    // draw everything
    oldEntityNum = -1;
    backEnd.currentEntity = &tr.worldEntity;
    oldShader = NULL;
    oldFogNum = -1;
    oldDepthRange = qfalse;
    oldDlighted = qfalse;
    oldSort = -1;
    depthRange = qfalse;

    backEnd.pc.c_surfaces += numDrawSurfs;

    for(i = 0, drawSurf = drawSurfs ; i < numDrawSurfs ; i++, drawSurf++)
    {
        if(drawSurf->sort == oldSort)
        {
            // fast path, same as previous sort
            rb_surfaceTable[ *drawSurf->surface ](drawSurf->surface);
            continue;
        }
        oldSort = drawSurf->sort;
        R_DecomposeSort(drawSurf->sort, &entityNum, &shader, &fogNum, &dlighted);

        //
        // change the tess parameters if needed
        // a "entityMergable" shader is a shader that can have surfaces from seperate
        // entities merged into a single batch, like smoke and blood puff sprites
        if(shader != oldShader || fogNum != oldFogNum || dlighted != oldDlighted ||(entityNum != oldEntityNum && !shader->entityMergable))
        {
            if(oldShader != NULL)
            {
#ifdef __MACOS__	// crutch up the mac's limited buffer queue size
                int		t;

                t = CL_ScaledMilliseconds();
                if(t > macEventTime)
                {
                    macEventTime = t + MAC_EVENT_PUMP_MSEC;
                    Sys_PumpEvents();
                }
#endif
                RB_EndSurface();
            }
            RB_BeginSurface(shader, fogNum);
            oldShader = shader;
            oldFogNum = fogNum;
            oldDlighted = dlighted;
        }

        //
        // change the modelview matrix if needed
        //
        if(entityNum != oldEntityNum)
        {
            depthRange = qfalse;

            if(entityNum != ENTITYNUM_WORLD)
            {
                backEnd.currentEntity = &backEnd.refdef.entities[entityNum];
                backEnd.refdef.floatTime = originalTime - backEnd.currentEntity->e.shaderTime;
                // we have to reset the shaderTime as well otherwise image animations start
                // from the wrong frame
                tess.shaderTime = backEnd.refdef.floatTime - tess.shader->timeOffset;

                // set up the transformation matrix
                R_RotateForEntity(backEnd.currentEntity, &backEnd.viewParms, &backEnd.or);

                // set up the dynamic lighting if needed
                if(backEnd.currentEntity->needDlights)
                {
                    R_TransformDlights(backEnd.refdef.num_dlights, backEnd.refdef.dlights, &backEnd.or);
                }

                if(backEnd.currentEntity->e.renderfx & RF_DEPTHHACK)
                {
                    // hack the depth range to prevent view model from poking into walls
                    depthRange = qtrue;
                }
            }
            else
            {
                backEnd.currentEntity = &tr.worldEntity;
                backEnd.refdef.floatTime = originalTime;
                backEnd.or = backEnd.viewParms.world;
                // we have to reset the shaderTime as well otherwise image animations on
                // the world(like water) continue with the wrong frame
                tess.shaderTime = backEnd.refdef.floatTime - tess.shader->timeOffset;
                R_TransformDlights(backEnd.refdef.num_dlights, backEnd.refdef.dlights, &backEnd.or);
            }

            qglLoadMatrixf(backEnd.or.modelMatrix);

            //
            // change depthrange if needed
            //
            if(oldDepthRange != depthRange)
            {
                qglDepthRange(0, (depthRange) ? 0.3 : 1);
                oldDepthRange = depthRange;
            }

            oldEntityNum = entityNum;
        }

        // add the triangles for this surface
        rb_surfaceTable[ *drawSurf->surface ](drawSurf->surface);
    }

    backEnd.refdef.floatTime = originalTime;

    // draw the contents of the last shader batch
    if(oldShader != NULL)
        RB_EndSurface();

    // go back to the world modelview matrix
    qglLoadMatrixf(backEnd.viewParms.world.modelMatrix);
    if(depthRange)
        qglDepthRange(0, 1);

#if 0
    RB_DrawSun();
#endif
    // darken down any stencil shadows
    RB_ShadowFinish();

    // add light flares on lights that aren't obscured
    RB_RenderFlares();

#ifdef __MACOS__
    Sys_PumpEvents();		// crutch up the mac's limited buffer queue size
#endif

    if(!(backEnd.refdef.rdflags & RDF_NOWORLDMODEL) && GL_EXT_framebuffer_object_supported && BlurContinue)
    {
        float sizew = (1.0f /((float)glConfig.vidWidth)), sizeh = (1.0f /((float)glConfig.vidHeight));

        RB_SetGL2DSize(BlurSet.color[0]->width, BlurSet.color[0]->height);
        Fbo_setBuffers(1, BlurSet.color + 0, NULL, NULL);

        Shader_Use(&convertProgram);
        Shader_setImage("Image", Offscreen.color[0]);
        Shader_setConstant2f("halfPixel", 0.5f * sizew, 0.5f * sizeh);
        Shader_setConstant1f("invRange", 0.25f / r_blur_range->value);
        Shader_setConstant1f("blurStrength", r_blur_strength->value);
        qglBegin(GL_QUADS);
        qglVertex2f(-1,  1);
        qglVertex2f(1,  1);
        qglVertex2f(1, -1);
        qglVertex2f(-1, -1);
        qglEnd();

        RB_SetGL2DSize(BlurSet.color[1]->width, BlurSet.color[1]->height);
        Fbo_setBuffers(1, BlurSet.color + 1, NULL, NULL);

        Shader_Use(&blurProgram);
        Shader_setImage("Image", BlurSet.color[0]);
        Shader_setConstant2f("sample0", sizew * -0.75f, sizeh * 0.25f);
        Shader_setConstant2f("sample1", sizew *  0.25f, sizeh *  0.75f);
        Shader_setConstant2f("sample2", sizew *  0.75f, sizeh * -0.25f);
        Shader_setConstant2f("sample3", sizew * -0.25f, sizeh * -0.75f);
        qglBegin(GL_QUADS);
        qglVertex2f(-1,  1);
        qglVertex2f(1,  1);
        qglVertex2f(1, -1);
        qglVertex2f(-1, -1);
        qglEnd();

        Fbo_setBuffers(1, BlurSet.color + 2, NULL, NULL);

        Shader_setImage("Image", BlurSet.color[1]);
        Shader_setConstant2f("sample0", 2 * sizew * -0.75f, 2 * sizeh * -0.25f);
        Shader_setConstant2f("sample1", 2 * sizew * -0.25f, 2 * sizeh *  0.75f);
        Shader_setConstant2f("sample2", 2 * sizew *  0.75f, 2 * sizeh *  0.25f);
        Shader_setConstant2f("sample3", 2 * sizew *  0.25f, 2 * sizeh * -0.75f);
        qglBegin(GL_QUADS);
        qglVertex2f(-1,  1);
        qglVertex2f(1,  1);
        qglVertex2f(1, -1);
        qglVertex2f(-1, -1);
        qglEnd();

        Fbo_setBuffers(1, BlurSet.color + 1, NULL, NULL);

        Shader_setImage("Image", BlurSet.color[2]);
        Shader_setConstant2f("sample0", 4 * sizew * -0.75f, 4 * sizeh *  0.25f);
        Shader_setConstant2f("sample1", 4 * sizew *  0.25f, 4 * sizeh *  0.75f);
        Shader_setConstant2f("sample2", 4 * sizew *  0.75f, 4 * sizeh * -0.25f);
        Shader_setConstant2f("sample3", 4 * sizew * -0.25f, 4 * sizeh * -0.75f);
        qglBegin(GL_QUADS);
        qglVertex2f(-1,  1);
        qglVertex2f(1,  1);
        qglVertex2f(1, -1);
        qglVertex2f(-1, -1);
        qglEnd();

        Fbo_setBuffers(1, BlurSet.color + 2, NULL, NULL);

        Shader_setImage("Image", BlurSet.color[1]);
        Shader_setConstant2f("sample0", 8 * sizew * -0.75f, 8 * sizeh * -0.25f);
        Shader_setConstant2f("sample1", 8 * sizew * -0.25f, 8 * sizeh *  0.75f);
        Shader_setConstant2f("sample2", 8 * sizew *  0.75f, 8 * sizeh *  0.25f);
        Shader_setConstant2f("sample3", 8 * sizew *  0.25f, 8 * sizeh * -0.75f);
        qglBegin(GL_QUADS);
        qglVertex2f(-1,  1);
        qglVertex2f(1,  1);
        qglVertex2f(1, -1);
        qglVertex2f(-1, -1);
        qglEnd();

        Fbo_Unbind();
        RB_SetGL2D();

        Shader_Use(&toneProgram);
        Shader_setImage("Base", Offscreen.color[0]);
        Shader_setImage("Blur", BlurSet.color[2]);
        Shader_setConstant1f("exposure", r_blur_exposure->value);
        Shader_setConstant1f("range", r_blur_range->value);
        qglBegin(GL_QUADS);
        qglVertex2f(-1,  1);
        qglVertex2f(1,  1);
        qglVertex2f(1, -1);
        qglVertex2f(-1, -1);
        qglEnd();

        Shader_Use(NULL);
    }
}

/*
============================================================================
 
RENDER BACK END THREAD FUNCTIONS
 
============================================================================
*/

/*
================
RB_SetGL2D
 
================
*/
void RB_SetGL2DSize(int width, int height)
{
    backEnd.projection2D = qtrue;

    // set 2D virtual screen size
    qglViewport(0, 0, width, height);
    qglScissor(0, 0, width, height);
    qglMatrixMode(GL_PROJECTION);
    qglLoadIdentity();
    qglOrtho(0, width, height, 0, 0, 1);
    qglMatrixMode(GL_MODELVIEW);
    qglLoadIdentity();

    GL_State(GLS_DEPTHTEST_DISABLE | GLS_SRCBLEND_SRC_ALPHA | GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA);

    qglDisable(GL_CULL_FACE);
    qglDisable(GL_CLIP_PLANE0);

    // set time for 2D shaders
    backEnd.refdef.time = CL_ScaledMilliseconds();
    backEnd.refdef.floatTime = backEnd.refdef.time * 0.001f;
}

void RB_SetGL2D(void)
{
    RB_SetGL2DSize(glConfig.vidWidth, glConfig.vidHeight);
}

/*
=============
RE_StretchRaw
 
FIXME: not exactly backend
Stretches a raw 32 bit power of 2 bitmap image over the given screen rectangle.
Used for cinematics.
=============
*/
void RE_StretchRaw(int x, int y, int w, int h, int cols, int rows, const byte *data, int client, qboolean dirty)
{
    int			i, j;
    int			start, end;

    if(!tr.registered)
    {
        return;
    }
    R_SyncRenderThread();

    // we definately want to sync every frame for the cinematics
    qglFinish();

    start = end = 0;
    if(r_speeds->integer)
    {
        start = CL_ScaledMilliseconds();
    }

    // make sure rows and cols are powers of 2
    for(i = 0 ;(1 << i) < cols ; i++)
    {}
    for(j = 0 ;(1 << j) < rows ; j++)
    {}
    if((1 << i) != cols ||(1 << j) != rows)
    {
        Com_Error(ERR_DROP, "Draw_StretchRaw: size not a power of 2: %i by %i", cols, rows);
    }

    GL_Bind(tr.scratchImage[client]);

    // if the scratchImage isn't in the format we want, specify it as a new texture
    if(cols != tr.scratchImage[client]->width || rows != tr.scratchImage[client]->height)
    {
        tr.scratchImage[client]->width = tr.scratchImage[client]->uploadWidth = cols;
        tr.scratchImage[client]->height = tr.scratchImage[client]->uploadHeight = rows;
        qglTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, cols, rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    }
    else if(dirty)
        // otherwise, just subimage upload it so that drivers can tell we are going to be changing
        // it and don't try and do a texture compression
        qglTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, cols, rows, GL_RGBA, GL_UNSIGNED_BYTE, data);

    if(r_speeds->integer)
    {
        end = CL_ScaledMilliseconds();
        CL_RefPrintf(PRINT_ALL, "qglTexSubImage2D %i, %i: %i msec\n", cols, rows, end - start);
    }

    RB_SetGL2D();

    qglColor3f(tr.identityLight, tr.identityLight, tr.identityLight);

    qglBegin(GL_QUADS);
    qglTexCoord2f(0.5f / cols,  0.5f / rows);
    qglVertex2f(x, y);
    qglTexCoord2f((cols - 0.5f) / cols ,  0.5f / rows);
    qglVertex2f(x+w, y);
    qglTexCoord2f((cols - 0.5f) / cols,(rows - 0.5f) / rows);
    qglVertex2f(x+w, y+h);
    qglTexCoord2f(0.5f / cols,(rows - 0.5f) / rows);
    qglVertex2f(x, y+h);
    qglEnd();
}

void RE_UploadCinematic(int w, int h, int cols, int rows, const byte *data, int client, qboolean dirty)
{
    GL_Bind(tr.scratchImage[client]);

    // if the scratchImage isn't in the format we want, specify it as a new texture
    if(cols != tr.scratchImage[client]->width || rows != tr.scratchImage[client]->height)
    {
        tr.scratchImage[client]->width = tr.scratchImage[client]->uploadWidth = cols;
        tr.scratchImage[client]->height = tr.scratchImage[client]->uploadHeight = rows;
        qglTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, cols, rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    }
    else if(dirty)
        // otherwise, just subimage upload it so that drivers can tell we are going to be changing
        // it and don't try and do a texture compression
        qglTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, cols, rows, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

/*
=============
RB_SetColor
 
=============
*/
const void	*RB_SetColor(const void *data)
{
    const setColorCommand_t	*cmd;

    cmd = (const setColorCommand_t *)data;

    backEnd.color2D[0] = cmd->color[0];
    backEnd.color2D[1] = cmd->color[1];
    backEnd.color2D[2] = cmd->color[2];
    backEnd.color2D[3] = cmd->color[3];

    return (const void *)(cmd + 1);
}

/*
=============
RB_StretchPic
=============
*/
const void *RB_StretchPic(const void *data)
{
    const stretchPicCommand_t	*cmd;
    shader_t *shader;
    int		numVerts, numIndexes;

    cmd = (const stretchPicCommand_t *)data;

    if(!backEnd.projection2D)
        RB_SetGL2D();

    shader = cmd->shader;
    if(shader != tess.shader)
    {
        if(tess.numIndexes)
            RB_EndSurface();

        backEnd.currentEntity = &backEnd.entity2D;
        RB_BeginSurface(shader, 0);
    }

    RB_CHECKOVERFLOW(4, 6);
    numVerts = tess.numVertexes;
    numIndexes = tess.numIndexes;

    tess.numVertexes += 4;
    tess.numIndexes += 6;

    tess.indexes[ numIndexes ] = numVerts + 3;
    tess.indexes[ numIndexes + 1 ] = numVerts + 0;
    tess.indexes[ numIndexes + 2 ] = numVerts + 2;
    tess.indexes[ numIndexes + 3 ] = numVerts + 2;
    tess.indexes[ numIndexes + 4 ] = numVerts + 0;
    tess.indexes[ numIndexes + 5 ] = numVerts + 1;

    tess.xyz[ numVerts ][0] = cmd->x;
    tess.xyz[ numVerts ][1] = cmd->y;
    tess.xyz[ numVerts ][2] = 0;
    tess.vertexColors[numVerts][0] = backEnd.color2D[0];
    tess.vertexColors[numVerts][1] = backEnd.color2D[1];
    tess.vertexColors[numVerts][2] = backEnd.color2D[2];
    tess.vertexColors[numVerts][3] = backEnd.color2D[3];
    tess.texCoords[ numVerts ][0][0] = cmd->s1;
    tess.texCoords[ numVerts ][0][1] = cmd->t1;

    tess.xyz[ numVerts + 1 ][0] = cmd->x + cmd->w;
    tess.xyz[ numVerts + 1 ][1] = cmd->y;
    tess.xyz[ numVerts + 1 ][2] = 0;
    tess.vertexColors[numVerts + 1][0] = backEnd.color2D[0];
    tess.vertexColors[numVerts + 1][1] = backEnd.color2D[1];
    tess.vertexColors[numVerts + 1][2] = backEnd.color2D[2];
    tess.vertexColors[numVerts + 1][3] = backEnd.color2D[3];
    tess.texCoords[ numVerts + 1 ][0][0] = cmd->s2;
    tess.texCoords[ numVerts + 1 ][0][1] = cmd->t1;

    tess.xyz[ numVerts + 2 ][0] = cmd->x + cmd->w;
    tess.xyz[ numVerts + 2 ][1] = cmd->y + cmd->h;
    tess.xyz[ numVerts + 2 ][2] = 0;
    tess.vertexColors[numVerts + 2][0] = backEnd.color2D[0];
    tess.vertexColors[numVerts + 2][1] = backEnd.color2D[1];
    tess.vertexColors[numVerts + 2][2] = backEnd.color2D[2];
    tess.vertexColors[numVerts + 2][3] = backEnd.color2D[3];
    tess.texCoords[ numVerts + 2 ][0][0] = cmd->s2;
    tess.texCoords[ numVerts + 2 ][0][1] = cmd->t2;

    tess.xyz[ numVerts + 3 ][0] = cmd->x;
    tess.xyz[ numVerts + 3 ][1] = cmd->y + cmd->h;
    tess.xyz[ numVerts + 3 ][2] = 0;
    tess.vertexColors[numVerts + 3][0] = backEnd.color2D[0];
    tess.vertexColors[numVerts + 3][1] = backEnd.color2D[1];
    tess.vertexColors[numVerts + 3][2] = backEnd.color2D[2];
    tess.vertexColors[numVerts + 3][3] = backEnd.color2D[3];
    tess.texCoords[ numVerts + 3 ][0][0] = cmd->s1;
    tess.texCoords[ numVerts + 3 ][0][1] = cmd->t2;

    return (const void *)(cmd + 1);
}

/*
=============
RB_DrawSurfs
=============
*/
const void	*RB_DrawSurfs(const void *data)
{
    const drawSurfsCommand_t	*cmd;

    // finish any 2D drawing if needed
    if(tess.numIndexes)
        RB_EndSurface();

    cmd = (const drawSurfsCommand_t *)data;

    backEnd.refdef = cmd->refdef;
    backEnd.viewParms = cmd->viewParms;

    RB_RenderDrawSurfList(cmd->drawSurfs, cmd->numDrawSurfs);

    return (const void *)(cmd + 1);
}

/*
=============
RB_DrawBuffer
=============
*/
const void	*RB_DrawBuffer(const void *data)
{
    const drawBufferCommand_t *cmd;

    cmd = (const drawBufferCommand_t *)data;

    qglDrawBuffer(cmd->buffer);

    // clear screen for debugging
    if(r_clear->integer)
    {
        qglClearColor(1, 0, 0.5, 1);
        qglClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    return (const void *)(cmd + 1);
}

/*
===============
RB_ShowImages
 
Draw all the images to the screen, on top of whatever
was there.  This is used to test for texture thrashing.
 
Also called by RE_EndRegistration
===============
*/
void RB_ShowImages(void)
{
    int		i;
    image_t	*image;
    float	x, y, w, h;
    int		start, end;

    if(!backEnd.projection2D)
        RB_SetGL2D();

    qglClear(GL_COLOR_BUFFER_BIT);

    qglFinish();

    start = CL_ScaledMilliseconds();

    for(i=0 ; i<tr.numImages ; i++)
    {
        image = tr.images[i];

        w = glConfig.vidWidth / 20;
        h = glConfig.vidHeight / 15;
        x = i % 20 * w;
        y = i / 20 * h;

        // show in proportional size in mode 2
        if(r_showImages->integer == 2)
        {
            w *= image->uploadWidth / 512.0f;
            h *= image->uploadHeight / 512.0f;
        }

        GL_Bind(image);
        qglBegin(GL_QUADS);
        qglTexCoord2f(0, 0);
        qglVertex2f(x, y);
        qglTexCoord2f(1, 0);
        qglVertex2f(x + w, y);
        qglTexCoord2f(1, 1);
        qglVertex2f(x + w, y + h);
        qglTexCoord2f(0, 1);
        qglVertex2f(x, y + h);
        qglEnd();
    }

    qglFinish();

    end = CL_ScaledMilliseconds();
    CL_RefPrintf(PRINT_ALL, "%i msec to draw all images\n", end - start);
}

/*
=============
RB_SwapBuffers
=============
*/
const void	*RB_SwapBuffers(const void *data)
{
    const swapBuffersCommand_t	*cmd;

    // finish any 2D drawing if needed
    if(tess.numIndexes)
        RB_EndSurface();

    // texture swapping test
    if(r_showImages->integer)
        RB_ShowImages();

    cmd = (const swapBuffersCommand_t *)data;

    // we measure overdraw by reading back the stencil buffer and
    // counting up the number of increments that have happened
    if(r_measureOverdraw->integer)
    {
        int i;
        long sum = 0;
        unsigned char *stencilReadback;

        stencilReadback = Hunk_AllocateTempMemory(glConfig.vidWidth * glConfig.vidHeight);
        qglReadPixels(0, 0, glConfig.vidWidth, glConfig.vidHeight, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, stencilReadback);

        for(i = 0; i < glConfig.vidWidth * glConfig.vidHeight; i++)
        {
            sum += stencilReadback[i];
        }

        backEnd.pc.c_overDraw += sum;
        Hunk_FreeTempMemory(stencilReadback);
    }


    if(!glState.finishCalled)
        qglFinish();

    GLimp_LogComment("***************** RB_SwapBuffers *****************\n\n\n");

    GLimp_EndFrame();

    backEnd.projection2D = qfalse;

    return (const void *)(cmd + 1);
}

/*
====================
RB_ExecuteRenderCommands
 
This function will be called synchronously if running without
smp extensions, or asynchronously by another thread.
====================
*/
void RB_ExecuteRenderCommands(const void *data)
{
    int		t1, t2;

    t1 = CL_ScaledMilliseconds();

    backEnd.smpFrame = (!r_smp->integer || data == backEndData[0]->commands.cmds) ? 0 : 1;

    while(1)
    {
        switch(*(const int *)data)
        {
        case RC_SET_COLOR:
            data = RB_SetColor(data);
            break;
        case RC_STRETCH_PIC:
            data = RB_StretchPic(data);
            break;
        case RC_DRAW_SURFS:
            data = RB_DrawSurfs(data);
            break;
        case RC_DRAW_BUFFER:
            data = RB_DrawBuffer(data);
            break;
        case RC_SWAP_BUFFERS:
            data = RB_SwapBuffers(data);
            break;
        case RC_SCREENSHOT:
            data = RB_TakeScreenshotCmd(data);
            break;
        case RC_END_OF_LIST:
        default:
            // stop rendering on this thread
            t2 = CL_ScaledMilliseconds();
            backEnd.pc.msec = t2 - t1;
            return;
        }
    }
}

/*
================
RB_RenderThread
================
*/
void RB_RenderThread(void)
{
    const void	*data;

    // wait for either a rendering command or a quit command
    while(1)
    {
        // sleep until we have work to do
        data = GLimp_RendererSleep();

        if(!data)
            return;	// all done, renderer is shutting down

        renderThreadActive = qtrue;

        RB_ExecuteRenderCommands(data);

        renderThreadActive = qfalse;
    }
}

