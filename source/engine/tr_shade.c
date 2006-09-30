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
// tr_shade.c

#include "tr_local.h"

/*
 
  THIS ENTIRE FILE IS BACK END
 
  This file deals with applying shaders to surface data in the tess struct.
*/

/*
================
R_ArrayElementDiscrete
 
This is just for OpenGL conformance testing, it should never be the fastest
================
*/
static void APIENTRY R_ArrayElementDiscrete( GLint index )
{
    qglColor4fv( tess.svars.colors[ index ] );
    if ( glState.currenttmu )
    {
        qglMultiTexCoord2f( 0, tess.svars.texcoords[ 0 ][ index ][0], tess.svars.texcoords[ 0 ][ index ][1] );
        qglMultiTexCoord2f( 1, tess.svars.texcoords[ 1 ][ index ][0], tess.svars.texcoords[ 1 ][ index ][1] );
    }
    else
    {
        qglTexCoord2fv( tess.svars.texcoords[ 0 ][ index ] );
    }
    qglVertex3fv( tess.xyz[ index ] );
}

/*
===================
R_DrawStripElements
 
===================
*/
static int		c_vertexes;		// for seeing how long our average strips are
static int		c_begins;
static void R_DrawStripElements( int numIndexes, const glIndex_t *indexes, void ( APIENTRY *element )(GLint) )
{
    int i;
    int last[3] = { -1, -1, -1 };
    qboolean even;

    c_begins++;

    if ( numIndexes <= 0 )
    {
        return;
    }

    qglBegin( GL_TRIANGLE_STRIP );

    // prime the strip
    element( indexes[0] );
    element( indexes[1] );
    element( indexes[2] );
    c_vertexes += 3;

    last[0] = indexes[0];
    last[1] = indexes[1];
    last[2] = indexes[2];

    even = qfalse;

    for ( i = 3; i < numIndexes; i += 3 )
    {
        // odd numbered triangle in potential strip
        if ( !even )
        {
            // check previous triangle to see if we're continuing a strip
            if ( ( indexes[i+0] == last[2] ) && ( indexes[i+1] == last[1] ) )
            {
                element( indexes[i+2] );
                c_vertexes++;
                assert( indexes[i+2] < tess.numVertexes );
                even = qtrue;
            }
            // otherwise we're done with this strip so finish it and start
            // a new one
            else
            {
                qglEnd();

                qglBegin( GL_TRIANGLE_STRIP );
                c_begins++;

                element( indexes[i+0] );
                element( indexes[i+1] );
                element( indexes[i+2] );

                c_vertexes += 3;

                even = qfalse;
            }
        }
        else
        {
            // check previous triangle to see if we're continuing a strip
            if ( ( last[2] == indexes[i+1] ) && ( last[0] == indexes[i+0] ) )
            {
                element( indexes[i+2] );
                c_vertexes++;

                even = qfalse;
            }
            // otherwise we're done with this strip so finish it and start
            // a new one
            else
            {
                qglEnd();

                qglBegin( GL_TRIANGLE_STRIP );
                c_begins++;

                element( indexes[i+0] );
                element( indexes[i+1] );
                element( indexes[i+2] );
                c_vertexes += 3;

                even = qfalse;
            }
        }

        // cache the last three vertices
        last[0] = indexes[i+0];
        last[1] = indexes[i+1];
        last[2] = indexes[i+2];
    }

    qglEnd();
}



/*
==================
R_DrawElements
 
Optionally performs our own glDrawElements that looks for strip conditions
instead of using the single glDrawElements call that may be inefficient
without compiled vertex arrays.
==================
*/
static void R_DrawElements( int numIndexes, const glIndex_t *indexes )
{
    int		primitives;

    primitives = r_primitives->integer;

    // default is to use triangles if compiled vertex arrays are present
    if ( primitives == 0 )
    {
        if ( GL_EXT_compiled_vertex_array_supported )
        {
            primitives = 2;
        }
        else
        {
            primitives = 1;
        }
    }


    if ( primitives == 2 )
    {
        qglDrawElements( GL_TRIANGLES,
                         numIndexes,
                         GL_INDEX_TYPE,
                         indexes );
        return;
    }

    if ( primitives == 1 )
    {
        R_DrawStripElements( numIndexes,  indexes, qglArrayElement );
        return;
    }

    if ( primitives == 3 )
    {
        R_DrawStripElements( numIndexes,  indexes, R_ArrayElementDiscrete );
        return;
    }

    // anything else will cause no drawing
}


/*
=============================================================
 
SURFACE SHADERS
 
=============================================================
*/

shaderCommands_t	tess;
static qboolean	setArraysOnce;

/*
=================
R_BindAnimatedImage
 
=================
*/
static image_t *R_BindAnimatedImage( textureBundle_t *bundle )
{
    int		index;

    if ( bundle->isVideoMap )
    {
        CIN_RunCinematic(bundle->videoMapHandle);
        CIN_UploadCinematic(bundle->videoMapHandle);
        return tr.scratchImage[bundle->videoMapHandle];
    }

    if ( bundle->numImageAnimations <= 1 )
        return bundle->image[0];

    // it is necessary to do this messy calc to make sure animations line up
    // exactly with waveforms of the same frequency
    index = (long)(tess.shaderTime * bundle->imageAnimationSpeed * FUNCTABLE_SIZE) >> FUNCTABLE_SIZE2;

	return bundle->image[(index < 0) ? 0 : index % bundle->numImageAnimations];
}

/*
================
DrawTris
 
Draws triangle outlines for debugging
================
*/
static void DrawTris (shaderCommands_t *input)
{
    GL_Bind( tr.whiteImage );
    qglColor3f (1,1,1);

    GL_State( GLS_POLYMODE_LINE | GLS_DEPTHMASK_TRUE );
    qglDepthRange( 0, 0 );

    qglDisableClientState (GL_COLOR_ARRAY);
    qglDisableClientState (GL_TEXTURE_COORD_ARRAY);

    qglVertexPointer (3, GL_FLOAT, 16, input->xyz);	// padded for SIMD

    if (GL_EXT_compiled_vertex_array_supported)
    {
        qglLockArraysEXT(0, input->numVertexes);
        GLimp_LogComment( "glLockArraysEXT\n" );
    }

    R_DrawElements( input->numIndexes, input->indexes );

    if (GL_EXT_compiled_vertex_array_supported)
    {
        qglUnlockArraysEXT();
        GLimp_LogComment( "glUnlockArraysEXT\n" );
    }
    qglDepthRange( 0, 1 );
}


/*
================
DrawNormals
 
Draws vertex normals for debugging
================
*/
static void DrawNormals (shaderCommands_t *input)
{
    int		i;
    vec3_t	temp;

    GL_Bind( tr.whiteImage );
    qglColor3f (1,1,1);
    qglDepthRange( 0, 0 );	// never occluded
    GL_State( GLS_POLYMODE_LINE | GLS_DEPTHMASK_TRUE );

    qglBegin (GL_LINES);
    for (i = 0 ; i < input->numVertexes ; i++)
    {
        qglVertex3fv (input->xyz[i]);
        VectorMA (input->xyz[i], 2, input->normal[i], temp);
        qglVertex3fv (temp);
    }
    qglEnd ();

    qglDepthRange( 0, 1 );
}

/*
==============
RB_BeginSurface
 
We must set some things up before beginning any tesselation,
because a surface may be forced to perform a RB_End due
to overflow.
==============
*/
void RB_BeginSurface( shader_t *shader, int fogNum )
{

    shader_t *state = (shader->remappedShader) ? shader->remappedShader : shader;

    tess.numIndexes = 0;
    tess.numVertexes = 0;
    tess.shader = state;
    tess.fogNum = fogNum;
    tess.dlightBits = 0;		// will be OR'd in by surface functions
    tess.xstages = state->stages;
    tess.numPasses = state->numUnfoggedPasses;
    tess.currentStageIteratorFunc = state->optimalStageIteratorFunc;
	tess.glShader = shader->glShader;

    tess.shaderTime = backEnd.refdef.floatTime - tess.shader->timeOffset;
    if (tess.shader->clampTime && tess.shaderTime >= tess.shader->clampTime)
    {
        tess.shaderTime = tess.shader->clampTime;
    }


}

/*
===================
DrawMultitextured
 
output = t0 * t1 or t0 + t1
 
t0 = most upstream according to spec
t1 = most downstream according to spec
===================
*/
static void DrawMultitextured( shaderCommands_t *input, int stage )
{
    shaderStage_t	*pStage;

    pStage = tess.xstages[stage];

    GL_State( pStage->stateBits );

    // this is an ugly hack to work around a GeForce driver
    // bug with multitexture and clip planes
    if ( backEnd.viewParms.isPortal )
    {
        qglPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }

    //
    // base
    //
    GL_SelectTexture( 0 );
    qglTexCoordPointer( 2, GL_FLOAT, 0, input->svars.texcoords[0] );
    GL_Bind(R_BindAnimatedImage(&pStage->bundle[0]));

    //
    // lightmap/secondary pass
    //
    GL_SelectTexture( 1 );
    qglEnable( GL_TEXTURE_2D );
    qglEnableClientState( GL_TEXTURE_COORD_ARRAY );

    if ( r_lightmap->integer )
    {
        GL_TexEnv( GL_MODULATE );
    }
    else
    {
        GL_TexEnv(pStage->multitextureEnv );
    }

    qglTexCoordPointer( 2, GL_FLOAT, 0, input->svars.texcoords[1] );

    GL_Bind(R_BindAnimatedImage( &pStage->bundle[1] ));

    R_DrawElements( input->numIndexes, input->indexes );

    //
    // disable texturing on TEXTURE1, then select TEXTURE0
    //
    //qglDisableClientState( GL_TEXTURE_COORD_ARRAY );
    qglDisable( GL_TEXTURE_2D );

    GL_SelectTexture( 0 );
}



/*
===================
ProjectDlightTexture
 
Perform dynamic lighting with another rendering pass
===================
*/
static void ProjectDlightTexture( void )
{
    int		i, l;
#if idppc_altivec
    vec_t	origin0, origin1, origin2;
    float   texCoords0, texCoords1;
    vector float floatColorVec0, floatColorVec1;
    vector float modulateVec, colorVec, zero;
    vector short colorShort;
    vector signed int colorInt;
    vector unsigned char floatColorVecPerm, modulatePerm, colorChar;
    vector unsigned char vSel = (vector unsigned char)(0x00, 0x00, 0x00, 0xff,
                                0x00, 0x00, 0x00, 0xff,
                                0x00, 0x00, 0x00, 0xff,
                                0x00, 0x00, 0x00, 0xff);
#else
    vec3_t	origin;
#endif
    float	*texCoords;
    float	*colors;
    byte	clipBits[SHADER_MAX_VERTEXES];
    MAC_STATIC float	texCoordsArray[SHADER_MAX_VERTEXES][2];
    vec4_t		colorArray[SHADER_MAX_VERTEXES];
    unsigned	hitIndexes[SHADER_MAX_INDEXES];
    int		numIndexes;
    float	scale;
    float	radius;
    vec3_t	floatColor;
    float	modulate;

    if ( !backEnd.refdef.num_dlights )
    {
        return;
    }

#if idppc_altivec
    // There has to be a better way to do this so that floatColor
    // and/or modulate are already 16-byte aligned.
    floatColorVecPerm = vec_lvsl(0,(float *)floatColor);
    modulatePerm = vec_lvsl(0,(float *)&modulate);
    modulatePerm = (vector unsigned char)vec_splat((vector unsigned int)modulatePerm,0);
    zero = (vector float)vec_splat_s8(0);
#endif

    for ( l = 0 ; l < backEnd.refdef.num_dlights ; l++ )
    {
        dlight_t	*dl;

        if ( !( tess.dlightBits & ( 1 << l ) ) )
        {
            continue;	// this surface definately doesn't have any of this light
        }
        texCoords = texCoordsArray[0];
        colors = colorArray[0];

        dl = &backEnd.refdef.dlights[l];
#if idppc_altivec
        origin0 = dl->transformed[0];
        origin1 = dl->transformed[1];
        origin2 = dl->transformed[2];
#else
        VectorCopy( dl->transformed, origin );
#endif
        radius = dl->radius;
        scale = 1.0f / radius;

        floatColor[0] = dl->color[0] * 1.0;
        floatColor[1] = dl->color[1] * 1.0;
        floatColor[2] = dl->color[2] * 1.0;
#if idppc_altivec
        floatColorVec0 = vec_ld(0, floatColor);
        floatColorVec1 = vec_ld(11, floatColor);
        floatColorVec0 = vec_perm(floatColorVec0,floatColorVec0,floatColorVecPerm);
#endif
        for ( i = 0 ; i < tess.numVertexes ; i++, texCoords += 2, colors += 4 )
        {
#if idppc_altivec
            vec_t dist0, dist1, dist2;
#else
            vec3_t	dist;
#endif
            int		clip;

            backEnd.pc.c_dlightVertexes++;

#if idppc_altivec
            //VectorSubtract( origin, tess.xyz[i], dist );
            dist0 = origin0 - tess.xyz[i][0];
            dist1 = origin1 - tess.xyz[i][1];
            dist2 = origin2 - tess.xyz[i][2];
            texCoords0 = 0.5f + dist0 * scale;
            texCoords1 = 0.5f + dist1 * scale;

            clip = 0;
            if ( texCoords0 < 0.0f )
            {
                clip |= 1;
            }
            else if ( texCoords0 > 1.0f )
            {
                clip |= 2;
            }
            if ( texCoords1 < 0.0f )
            {
                clip |= 4;
            }
            else if ( texCoords1 > 1.0f )
            {
                clip |= 8;
            }
            texCoords[0] = texCoords0;
            texCoords[1] = texCoords1;

            // modulate the strength based on the height and color
            if ( dist2 > radius )
            {
                clip |= 16;
                modulate = 0.0f;
            }
            else if ( dist2 < -radius )
            {
                clip |= 32;
                modulate = 0.0f;
            }
            else
            {
                dist2 = Q_fabs(dist2);
                if ( dist2 < radius * 0.5f )
                {
                    modulate = 1.0f;
                }
                else
                {
                    modulate = 2.0f * (radius - dist2) * scale;
                }
            }
            clipBits[i] = clip;

            modulateVec = vec_ld(0,(float *)&modulate);
            modulateVec = vec_perm(modulateVec,modulateVec,modulatePerm);
            colorVec = vec_madd(floatColorVec0,modulateVec,zero);
            colorInt = vec_cts(colorVec,0);	// RGBx
            colorShort = vec_pack(colorInt,colorInt);		// RGBxRGBx
            colorChar = vec_packsu(colorShort,colorShort);	// RGBxRGBxRGBxRGBx
            colorChar = vec_sel(colorChar,vSel,vSel);		// RGBARGBARGBARGBA replace alpha with 255
            vec_ste((vector unsigned int)colorChar,0,(unsigned int *)colors);	// store color
#else
            VectorSubtract( origin, tess.xyz[i], dist );
            texCoords[0] = 0.5f + dist[0] * scale;
            texCoords[1] = 0.5f + dist[1] * scale;

            clip = 0;
            if ( texCoords[0] < 0.0f )
            {
                clip |= 1;
            }
            else if ( texCoords[0] > 1.0f )
            {
                clip |= 2;
            }
            if ( texCoords[1] < 0.0f )
            {
                clip |= 4;
            }
            else if ( texCoords[1] > 1.0f )
            {
                clip |= 8;
            }
            // modulate the strength based on the height and color
            if ( dist[2] > radius )
            {
                clip |= 16;
                modulate = 0.0f;
            }
            else if ( dist[2] < -radius )
            {
                clip |= 32;
                modulate = 0.0f;
            }
            else
            {
                dist[2] = Q_fabs(dist[2]);
                if ( dist[2] < radius * 0.5f )
                {
                    modulate = 1.0f;
                }
                else
                {
                    modulate = 2.0f * (radius - dist[2]) * scale;
                }
            }
            clipBits[i] = clip;

            colors[0] = (floatColor[0] * modulate);
            colors[1] = (floatColor[1] * modulate);
            colors[2] = (floatColor[2] * modulate);
            colors[3] = 1.0;
#endif
        }

        // build a list of triangles that need light
        numIndexes = 0;
        for ( i = 0 ; i < tess.numIndexes ; i += 3 )
        {
            int		a, b, c;

            a = tess.indexes[i];
            b = tess.indexes[i+1];
            c = tess.indexes[i+2];
            if ( clipBits[a] & clipBits[b] & clipBits[c] )
            {
                continue;	// not lighted
            }
            hitIndexes[numIndexes] = a;
            hitIndexes[numIndexes+1] = b;
            hitIndexes[numIndexes+2] = c;
            numIndexes += 3;
        }

        if ( !numIndexes )
        {
            continue;
        }

        qglEnableClientState( GL_TEXTURE_COORD_ARRAY );
        qglTexCoordPointer( 2, GL_FLOAT, 0, texCoordsArray[0] );

        qglEnableClientState( GL_COLOR_ARRAY );
        qglColorPointer( 4, GL_FLOAT, 0, colorArray );

        GL_Bind( tr.dlightImage );
        // include GLS_DEPTHFUNC_EQUAL so alpha tested surfaces don't add light
        // where they aren't rendered
        if ( dl->additive )
        {
            GL_State( GLS_SRCBLEND_ONE | GLS_DSTBLEND_ONE | GLS_DEPTHFUNC_EQUAL );
        }
        else
        {
            GL_State( GLS_SRCBLEND_DST_COLOR | GLS_DSTBLEND_ONE | GLS_DEPTHFUNC_EQUAL );
        }
        R_DrawElements( numIndexes, hitIndexes );
        backEnd.pc.c_totalIndexes += numIndexes;
        backEnd.pc.c_dlightIndexes += numIndexes;
    }
}


/*
===================
RB_FogPass
 
Blends a fog texture on top of everything else
===================
*/
static void RB_FogPass( void )
{
    fog_t		*fog = tr.world->fogs + tess.fogNum, fog2;
    int			i;

    qglEnableClientState( GL_COLOR_ARRAY );
    qglColorPointer( 4, GL_FLOAT, 0, tess.svars.colors );

    qglEnableClientState( GL_TEXTURE_COORD_ARRAY);
    qglTexCoordPointer( 2, GL_FLOAT, 0, tess.svars.texcoords[0] );

    for ( i = 0; i < tess.numVertexes; i++ )
    {
        tess.svars.colors[i][0] = fog->color[0];
        tess.svars.colors[i][1] = fog->color[1];
        tess.svars.colors[i][2] = fog->color[2];
        tess.svars.colors[i][3] = fog->color[3];
    }
    GL_Bind( tr.fogImage );

    if(r_fog_dualpass->integer)
    {
        // darken
        memcpy(&fog2, fog, sizeof(fog_t));
        fog2.tcScale *= 0.75;
        RB_CalcFogTexCoords( ( float * ) tess.svars.texcoords[0], &fog2 );
        if ( tess.shader->fogPass == FP_EQUAL )
        {
            GL_State( GLS_SRCBLEND_SRC_ALPHA | GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA | GLS_DEPTHFUNC_EQUAL );
        }
        else
        {
            GL_State( GLS_SRCBLEND_SRC_ALPHA | GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA );
        }
        R_DrawElements( tess.numIndexes, tess.indexes );

        // lighten
        fog2.tcScale = fog->tcScale * 2;
        for ( i = 0; i < tess.numVertexes; i++ )
        {
            tess.svars.colors[i][0] = fog->color[0] * 0.25;
            tess.svars.colors[i][1] = fog->color[1] * 0.25;
            tess.svars.colors[i][2] = fog->color[2] * 0.25;
            tess.svars.colors[i][3] = fog->color[3] * 0.25;
        }
        RB_CalcFogTexCoords( ( float * ) tess.svars.texcoords[0], &fog2 );
        if ( tess.shader->fogPass == FP_EQUAL )
        {
            GL_State( GLS_SRCBLEND_SRC_ALPHA | GLS_DSTBLEND_ONE | GLS_DEPTHFUNC_EQUAL );
        }
        else
        {
            GL_State( GLS_SRCBLEND_SRC_ALPHA | GLS_DSTBLEND_ONE );
        }
        R_DrawElements( tess.numIndexes, tess.indexes );
    }
    else
    {
        RB_CalcFogTexCoords( ( float * ) tess.svars.texcoords[0], fog );
        if ( tess.shader->fogPass == FP_EQUAL )
        {
            GL_State( GLS_SRCBLEND_SRC_ALPHA | GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA | GLS_DEPTHFUNC_EQUAL );
        }
        else
        {
            GL_State( GLS_SRCBLEND_SRC_ALPHA | GLS_DSTBLEND_ONE_MINUS_SRC_ALPHA );
        }
        R_DrawElements( tess.numIndexes, tess.indexes );
    }
}

/*
===============
ComputeColors
===============
*/
static void ComputeColors( shaderStage_t *pStage )
{
    int		i;

    //
    // rgbGen
    //
    switch ( pStage->rgbGen )
    {
    case CGEN_IDENTITY:
        for ( i = 0; i < tess.numVertexes; i++ )
        {
            tess.svars.colors[i][0] = 1.0;
            tess.svars.colors[i][1] = 1.0;
            tess.svars.colors[i][2] = 1.0;
            tess.svars.colors[i][3] = 1.0;
        }
        break;
    default:
    case CGEN_IDENTITY_LIGHTING:
        for ( i = 0; i < tess.numVertexes; i++ )
        {
            tess.svars.colors[i][0] = tr.identityLight;
            tess.svars.colors[i][1] = tr.identityLight;
            tess.svars.colors[i][2] = tr.identityLight;
            tess.svars.colors[i][3] = 1.0;
        }
        break;
    case CGEN_LIGHTING_DIFFUSE:
        RB_CalcDiffuseColor( tess.svars.colors[0] );
        break;
    case CGEN_EXACT_VERTEX:
        Com_Memcpy(tess.svars.colors, tess.vertexColors, tess.numVertexes * sizeof(vec4_t));
        break;
    case CGEN_CONST:
        for ( i = 0; i < tess.numVertexes; i++ )
        {
            tess.svars.colors[i][0] = pStage->constantColor[0];
            tess.svars.colors[i][1] = pStage->constantColor[1];
            tess.svars.colors[i][2] = pStage->constantColor[2];
            tess.svars.colors[i][3] = pStage->constantColor[3];
        }
        break;
    case CGEN_VERTEX:
        if ( tr.identityLight == 1 )
        {
            Com_Memcpy(tess.svars.colors, tess.vertexColors, tess.numVertexes * sizeof(vec4_t));
        }
        else
        {
            for ( i = 0; i < tess.numVertexes; i++ )
            {
                tess.svars.colors[i][0] = tess.vertexColors[i][0] * tr.identityLight;
                tess.svars.colors[i][1] = tess.vertexColors[i][1] * tr.identityLight;
                tess.svars.colors[i][2] = tess.vertexColors[i][2] * tr.identityLight;
                tess.svars.colors[i][3] = tess.vertexColors[i][3];
            }
        }
        break;
    case CGEN_ONE_MINUS_VERTEX:
        if ( tr.identityLight == 1 )
        {
            for ( i = 0; i < tess.numVertexes; i++ )
            {
                tess.svars.colors[i][0] = 1.0 - tess.vertexColors[i][0];
                tess.svars.colors[i][1] = 1.0 - tess.vertexColors[i][1];
                tess.svars.colors[i][2] = 1.0 - tess.vertexColors[i][2];
            }
        }
        else
        {
            for ( i = 0; i < tess.numVertexes; i++ )
            {
                tess.svars.colors[i][0] = ( 1.0 - tess.vertexColors[i][0] ) * tr.identityLight;
                tess.svars.colors[i][1] = ( 1.0 - tess.vertexColors[i][1] ) * tr.identityLight;
                tess.svars.colors[i][2] = ( 1.0 - tess.vertexColors[i][2] ) * tr.identityLight;
            }
        }
        break;
    case CGEN_FOG:
    {
        fog_t		*fog;

        fog = tr.world->fogs + tess.fogNum;

        for ( i = 0; i < tess.numVertexes; i++ )
        {
            tess.svars.colors[i][0] = fog->color[0];
            tess.svars.colors[i][1] = fog->color[1];
            tess.svars.colors[i][2] = fog->color[2];
            tess.svars.colors[i][3] = fog->color[3];
        }
    }
    break;
    case CGEN_WAVEFORM:
        RB_CalcWaveColor( &pStage->rgbWave, tess.svars.colors[0] );
        break;
    case CGEN_ENTITY:
        RB_CalcColorFromEntity( tess.svars.colors[0] );
        break;
    case CGEN_ONE_MINUS_ENTITY:
        RB_CalcColorFromOneMinusEntity( tess.svars.colors[0] );
        break;
    }

    //
    // alphaGen
    //
    switch ( pStage->alphaGen )
    {
    case AGEN_SKIP:
        break;
    case AGEN_IDENTITY:
        if ( pStage->rgbGen != CGEN_IDENTITY )
        {
            if ( ( pStage->rgbGen == CGEN_VERTEX && tr.identityLight != 1 ) ||
                    pStage->rgbGen != CGEN_VERTEX )
            {
                for ( i = 0; i < tess.numVertexes; i++ )
                {
                    tess.svars.colors[i][3] = 1.0;
                }
            }
        }
        break;
    case AGEN_CONST:
        if ( pStage->rgbGen != CGEN_CONST )
        {
            for ( i = 0; i < tess.numVertexes; i++ )
            {
                tess.svars.colors[i][3] = pStage->constantColor[3];
            }
        }
        break;
    case AGEN_WAVEFORM:
        RB_CalcWaveAlpha( &pStage->alphaWave, tess.svars.colors[0] );
        break;
    case AGEN_LIGHTING_SPECULAR:
        RB_CalcSpecularAlpha( tess.svars.colors[0] );
        break;
    case AGEN_ENTITY:
        RB_CalcAlphaFromEntity( tess.svars.colors[0] );
        break;
    case AGEN_ONE_MINUS_ENTITY:
        RB_CalcAlphaFromOneMinusEntity( tess.svars.colors[0] );
        break;
    case AGEN_VERTEX:
        if ( pStage->rgbGen != CGEN_VERTEX )
        {
            for ( i = 0; i < tess.numVertexes; i++ )
            {
                tess.svars.colors[i][3] = tess.vertexColors[i][3];
            }
        }
        break;
    case AGEN_ONE_MINUS_VERTEX:
        for ( i = 0; i < tess.numVertexes; i++ )
        {
            tess.svars.colors[i][3] = 1.0 - tess.vertexColors[i][3];
        }
        break;
    case AGEN_PORTAL:
    {
        unsigned char alpha;

        for ( i = 0; i < tess.numVertexes; i++ )
        {
            float len;
            vec3_t v;

            VectorSubtract( tess.xyz[i], backEnd.viewParms.ori.origin, v );
            len = VectorLength( v );

            len /= tess.shader->portalRange;

            if ( len < 0 )
            {
                alpha = 0;
            }
            else if ( len > 1 )
            {
                alpha = 1.0;
            }
            else
            {
                alpha = len * 1.0;
            }

            tess.svars.colors[i][3] = alpha;
        }
    }
    break;
    }

    //
    // fog adjustment for colors to fade out as fog increases
    //
    if ( tess.fogNum )
    {
        switch ( pStage->adjustColorsForFog )
        {
        case ACFF_MODULATE_RGB:
            RB_CalcModulateColorsByFog( tess.svars.colors[0] );
            break;
        case ACFF_MODULATE_ALPHA:
            RB_CalcModulateAlphasByFog( tess.svars.colors[0] );
            break;
        case ACFF_MODULATE_RGBA:
            RB_CalcModulateRGBAsByFog( tess.svars.colors[0] );
            break;
        case ACFF_NONE:
            break;
        }
    }
}

/*
===============
ComputeTexCoords
===============
*/
static void ComputeTexCoords( shaderStage_t *pStage )
{
    int		i;
    int		b;

    for ( b = 0; b < NUM_TEXTURE_BUNDLES; b++ )
    {
        int tm;

        //
        // generate the texture coordinates
        //
        switch ( pStage->bundle[b].tcGen )
        {
        case TCGEN_IDENTITY:
            Com_Memset( tess.svars.texcoords[b], 0, sizeof( float ) * 2 * tess.numVertexes );
            break;
        case TCGEN_TEXTURE:
            for ( i = 0 ; i < tess.numVertexes ; i++ )
            {
                tess.svars.texcoords[b][i][0] = tess.texCoords[i][0][0];
                tess.svars.texcoords[b][i][1] = tess.texCoords[i][0][1];
            }
            break;
        case TCGEN_LIGHTMAP:
            for ( i = 0 ; i < tess.numVertexes ; i++ )
            {
                tess.svars.texcoords[b][i][0] = tess.texCoords[i][1][0];
                tess.svars.texcoords[b][i][1] = tess.texCoords[i][1][1];
            }
            break;
        case TCGEN_VECTOR:
            for ( i = 0 ; i < tess.numVertexes ; i++ )
            {
                tess.svars.texcoords[b][i][0] = DotProduct( tess.xyz[i], pStage->bundle[b].tcGenVectors[0] );
                tess.svars.texcoords[b][i][1] = DotProduct( tess.xyz[i], pStage->bundle[b].tcGenVectors[1] );
            }
            break;
        case TCGEN_FOG:
            RB_CalcFogTexCoords( ( float * ) tess.svars.texcoords[b], tr.world->fogs + tess.fogNum );
            break;
        case TCGEN_ENVIRONMENT_MAPPED:
            RB_CalcEnvironmentTexCoords( ( float * ) tess.svars.texcoords[b] );
            break;
        case TCGEN_BAD:
            return;
        }

        //
        // alter texture coordinates
        //
        for ( tm = 0; tm < pStage->bundle[b].numTexMods ; tm++ )
        {
            switch ( pStage->bundle[b].texMods[tm].type )
            {
            case TMOD_NONE:
                tm = TR_MAX_TEXMODS;		// break out of for loop
                break;

            case TMOD_TURBULENT:
                RB_CalcTurbulentTexCoords( &pStage->bundle[b].texMods[tm].wave,
                                           ( float * ) tess.svars.texcoords[b] );
                break;

            case TMOD_ENTITY_TRANSLATE:
                RB_CalcScrollTexCoords( backEnd.currentEntity->e.shaderTexCoord,
                                        ( float * ) tess.svars.texcoords[b] );
                break;

            case TMOD_SCROLL:
                RB_CalcScrollTexCoords( pStage->bundle[b].texMods[tm].scroll,
                                        ( float * ) tess.svars.texcoords[b] );
                break;

            case TMOD_SCALE:
                RB_CalcScaleTexCoords( pStage->bundle[b].texMods[tm].scale,
                                       ( float * ) tess.svars.texcoords[b] );
                break;

            case TMOD_STRETCH:
                RB_CalcStretchTexCoords( &pStage->bundle[b].texMods[tm].wave,
                                         ( float * ) tess.svars.texcoords[b] );
                break;

            case TMOD_TRANSFORM:
                RB_CalcTransformTexCoords( &pStage->bundle[b].texMods[tm],
                                           ( float * ) tess.svars.texcoords[b] );
                break;

            case TMOD_ROTATE:
                RB_CalcRotateTexCoords( pStage->bundle[b].texMods[tm].rotateSpeed,
                                        ( float * ) tess.svars.texcoords[b] );
                break;

            default:
                Com_Error( ERR_DROP, "ERROR: unknown texmod '%d' in shader '%s'\n", pStage->bundle[b].texMods[tm].type, tess.shader->name );
                break;
            }
        }
    }
}

/*
** RB_IterateStagesGeneric
*/
static void RB_IterateStagesGeneric( shaderCommands_t *input )
{
    int stage;

    for ( stage = 0; stage < MAX_SHADER_STAGES; stage++ )
    {
        shaderStage_t *pStage = tess.xstages[stage];

        if ( !pStage )
            break;

        ComputeColors( pStage );
        ComputeTexCoords( pStage );

        if ( !setArraysOnce )
        {
            qglEnableClientState( GL_COLOR_ARRAY );
            qglColorPointer( 4, GL_FLOAT, 0, input->svars.colors );
        }

        // do multitexture
        if ( pStage->bundle[1].image[0] != 0 )
            DrawMultitextured( input, stage );
        else
        {
            if ( !setArraysOnce )
                qglTexCoordPointer( 2, GL_FLOAT, 0, input->svars.texcoords[0] );

            // set state
            if ( pStage->bundle[0].vertexLightmap && ( (r_vertexLight->integer && !r_uiFullScreen->integer) || glConfig.hardwareType == GLHW_PERMEDIA2 ) && r_lightmap->integer )
                GL_Bind( tr.whiteImage );
            else
                GL_Bind(R_BindAnimatedImage( &pStage->bundle[0] ));

            GL_State( pStage->stateBits );



            // draw
            R_DrawElements( input->numIndexes, input->indexes );
        }

        // allow skipping out to show just lightmaps during development
        if ( r_lightmap->integer && ( pStage->bundle[0].isLightmap || pStage->bundle[1].isLightmap || pStage->bundle[0].vertexLightmap ) )
            break;
    }
}

/*
** RB_StageIteratorGeneric
*/
void RB_StageIteratorGeneric( void )
{
    shaderCommands_t *input;

    input = &tess;

    RB_DeformTessGeometry();

    // log this call
    if ( r_logFile->integer )
    {
        // don't just call LogComment, or we will get
        // a call to va() every frame!
        GLimp_LogComment( va("--- RB_StageIteratorGeneric( %s ) ---\n", tess.shader->name) );
    }

    // set face culling appropriately
    GL_Cull( input->shader->cullType );

    // set polygon offset if necessary
    if ( input->shader->polygonOffset )
    {
        qglEnable( GL_POLYGON_OFFSET_FILL );
        qglPolygonOffset( r_offsetFactor->value, r_offsetUnits->value );
    }

    // if there is only a single pass then we can enable color
    // and texture arrays before we compile, otherwise we need
    // to avoid compiling those arrays since they will change
    // during multipass rendering
    if(tess.numPasses > 1)
    {
        setArraysOnce = qfalse;
        qglDisableClientState (GL_COLOR_ARRAY);
        qglDisableClientState (GL_TEXTURE_COORD_ARRAY);
    }
    else
    {
        setArraysOnce = qtrue;

        qglEnableClientState( GL_COLOR_ARRAY);
        qglColorPointer( 4, GL_FLOAT, 0, tess.svars.colors );

        qglEnableClientState( GL_TEXTURE_COORD_ARRAY);
        qglTexCoordPointer( 2, GL_FLOAT, 0, tess.svars.texcoords[0] );
    }

    // lock XYZ
    qglVertexPointer (3, GL_FLOAT, 16, input->xyz);	// padded for SIMD
    if (GL_EXT_compiled_vertex_array_supported)
    {
        qglLockArraysEXT(0, input->numVertexes);
        GLimp_LogComment( "glLockArraysEXT\n" );
    }

    // enable color and texcoord arrays after the lock if necessary
    if ( !setArraysOnce )
    {
        qglEnableClientState( GL_TEXTURE_COORD_ARRAY );
        qglEnableClientState( GL_COLOR_ARRAY );
    }

    // call shader function
    RB_IterateStagesGeneric( input );

    // now do any dynamic lighting needed
    if ( tess.dlightBits && tess.shader->sort <= SS_OPAQUE
            && !(tess.shader->surfaceFlags & (SURF_NODLIGHT | SURF_SKY) ) )
    {
        ProjectDlightTexture();
    }

    // now do fog
    if ( tess.fogNum && tess.shader->fogPass )
        RB_FogPass();

    // unlock arrays
    if (GL_EXT_compiled_vertex_array_supported)
    {
        qglUnlockArraysEXT();
        GLimp_LogComment( "glUnlockArraysEXT\n" );
    }

    // reset polygon offset
    if ( input->shader->polygonOffset )
        qglDisable( GL_POLYGON_OFFSET_FILL );
}

/*
** RB_StageIteratorVertexLitTexture
*/
void RB_StageIteratorVertexLitTexture( void )
{
    shaderCommands_t *input;
    shader_t		*shader;

    input = &tess;

    shader = input->shader;

    // compute colors
    RB_CalcDiffuseColor( tess.svars.colors[0] );

    // log this call
    if ( r_logFile->integer )
    {
        // don't just call LogComment, or we will get
        // a call to va() every frame!
        GLimp_LogComment( va("--- RB_StageIteratorVertexLitTexturedUnfogged( %s ) ---\n", tess.shader->name) );
    }

    // set face culling appropriately
    GL_Cull( input->shader->cullType );

    // set arrays and lock
    qglEnableClientState( GL_COLOR_ARRAY);
    qglEnableClientState( GL_TEXTURE_COORD_ARRAY);

    qglColorPointer( 4, GL_FLOAT, 0, tess.svars.colors );
    qglTexCoordPointer( 2, GL_FLOAT, 16, tess.texCoords[0][0] );
    qglVertexPointer (3, GL_FLOAT, 16, input->xyz);

    if ( GL_EXT_compiled_vertex_array_supported )
    {
        qglLockArraysEXT(0, input->numVertexes);
        GLimp_LogComment( "glLockArraysEXT\n" );
    }

    // call special shade routine
    GL_Bind(R_BindAnimatedImage( &tess.xstages[0]->bundle[0] ));
    GL_State( tess.xstages[0]->stateBits );
    R_DrawElements( input->numIndexes, input->indexes );

    // now do any dynamic lighting needed
    if ( tess.dlightBits && tess.shader->sort <= SS_OPAQUE )
        ProjectDlightTexture();

    // now do fog
    if ( tess.fogNum && tess.shader->fogPass )
        RB_FogPass();

    // unlock arrays
    if (GL_EXT_compiled_vertex_array_supported)
    {
        qglUnlockArraysEXT();
        GLimp_LogComment( "glUnlockArraysEXT\n" );
    }
}

//#define	REPLACE_MODE

void RB_StageIteratorLightmappedMultitexture( void )
{
    shaderCommands_t *input;

    input = &tess;

    // log this call
    if ( r_logFile->integer )
    {
        // don't just call LogComment, or we will get
        // a call to va() every frame!
        GLimp_LogComment( va("--- RB_StageIteratorLightmappedMultitexture( %s ) ---\n", tess.shader->name) );
    }

    // set face culling appropriately
    GL_Cull( input->shader->cullType );

    // set color, pointers, and lock
    GL_State( GLS_DEFAULT );
    qglVertexPointer( 3, GL_FLOAT, 16, input->xyz );

#ifdef REPLACE_MODE
    qglDisableClientState( GL_COLOR_ARRAY );
    qglColor3f( 1, 1, 1 );
    qglShadeModel( GL_FLAT );
#else
    qglEnableClientState( GL_COLOR_ARRAY );
    qglColorPointer( 4, GL_FLOAT, 0, tess.constantColorFull );
#endif

    // select base stage
    GL_SelectTexture( 0 );

    qglEnableClientState( GL_TEXTURE_COORD_ARRAY );
    GL_Bind(R_BindAnimatedImage( &tess.xstages[0]->bundle[0] ));
    qglTexCoordPointer( 2, GL_FLOAT, 16, tess.texCoords[0][0] );

    // configure second stage
    GL_SelectTexture( 1 );
    qglEnable( GL_TEXTURE_2D );
    if ( r_lightmap->integer )
        GL_TexEnv( GL_REPLACE );
    else
        GL_TexEnv( GL_MODULATE );

	GL_Bind(R_BindAnimatedImage( &tess.xstages[0]->bundle[1] ));
    qglEnableClientState( GL_TEXTURE_COORD_ARRAY );
    qglTexCoordPointer( 2, GL_FLOAT, 16, tess.texCoords[0][1] );

    // lock arrays
    if ( GL_EXT_compiled_vertex_array_supported )
    {
        qglLockArraysEXT(0, input->numVertexes);
        GLimp_LogComment( "glLockArraysEXT\n" );
    }

    R_DrawElements( input->numIndexes, input->indexes );

    // disable texturing on TEXTURE1, then select TEXTURE0
    qglDisable( GL_TEXTURE_2D );
    qglDisableClientState( GL_TEXTURE_COORD_ARRAY );

    GL_SelectTexture( 0 );
#ifdef REPLACE_MODE
    GL_TexEnv( GL_MODULATE );
    qglShadeModel( GL_SMOOTH );
#endif

    // now do any dynamic lighting needed
    if ( tess.dlightBits && tess.shader->sort <= SS_OPAQUE )
        ProjectDlightTexture();

    // now do fog
    if ( tess.fogNum && tess.shader->fogPass )
        RB_FogPass();

    // unlock arrays
    if ( GL_EXT_compiled_vertex_array_supported )
    {
        qglUnlockArraysEXT();
        GLimp_LogComment( "glUnlockArraysEXT\n" );
    }
}

/*
** RB_EndSurface
*/
void RB_EndSurface( void )
{
    shaderCommands_t *input;

    input = &tess;

    if (input->numIndexes == 0)
    {
        return;
    }

    if (input->indexes[SHADER_MAX_INDEXES-1] != 0)
    {
        Com_Error (ERR_DROP, "RB_EndSurface() - SHADER_MAX_INDEXES hit");
    }
    if (input->xyz[SHADER_MAX_VERTEXES-1][0] != 0)
    {
        Com_Error (ERR_DROP, "RB_EndSurface() - SHADER_MAX_VERTEXES hit");
    }

    if ( tess.shader == tr.shadowShader )
    {
        RB_ShadowTessEnd();
        return;
    }

    // for debugging of sort order issues, stop rendering after a given sort value
    if ( r_debugSort->integer && r_debugSort->integer < tess.shader->sort )
        return;

    // update performance counters
    backEnd.pc.c_shaders++;
    backEnd.pc.c_vertexes += tess.numVertexes;
    backEnd.pc.c_indexes += tess.numIndexes;
    backEnd.pc.c_totalIndexes += tess.numIndexes * tess.numPasses;

    // call off to shader specific tess end function

	// seems to work best here
	if(!tess.glShader && r_glsl_convert->integer)
	{
		Shader_Convert(tess.shader);
		tess.glShader = tess.shader->glShader;
	}

	if(tess.glShader && r_glsl_render->integer)
	{
		Shader_Use(tess.glShader);
		RB_StageIteratorOpenGLShader();
	}
	else if(!r_showNonGlsl->integer)
		tess.currentStageIteratorFunc();

    // draw debugging stuff
    if ( r_showtris->integer )
        DrawTris (input);

    if ( r_shownormals->integer )
        DrawNormals (input);

    // clear shader so we can tell we don't have any unclosed surfaces
    tess.numIndexes = 0;

    GLimp_LogComment( "----------\n" );
}

/*
** RB_StageIteratorOpenGLShader
*/
void RB_StageIteratorOpenGLShader( void )
{
    shaderCommands_t *input = &tess;
	shader_t *pShader = input->shader;
	glShader_t *glShader = pShader->glShader;
    int stage, cfuncs = glShader->cfuncs, afuncs = glShader->afuncs, tfuncs = glShader->tfuncs, mfuncs = glShader->mfuncs, i, b;

    RB_DeformTessGeometry();

    // log this call
    if ( r_logFile->integer )
        GLimp_LogComment( va("--- RB_StageIteratorOpenGLShader( %s ) ---\n", pShader->name) );

	if(cfuncs & C_Lighting_Diffuse || afuncs & A_Lighting_Specular || tfuncs & T_Enviroment_Mapped)
	{
		qglEnableClientState(GL_NORMAL_ARRAY);
		qglNormalPointer(GL_FLOAT, 16, tess.normal);
	}

    if(cfuncs & (C_Exact_Vertex | C_Vertex | C_One_Minus_Vertex) || afuncs & (A_Vertex | A_One_Minus_Vertex))
	{
		qglEnableClientState( GL_COLOR_ARRAY);
		qglColorPointer( 4, GL_FLOAT, 0, tess.vertexColors );
	}

    if(cfuncs & (C_Vertex | C_One_Minus_Vertex | C_Identity_Lighting) || afuncs & (A_Vertex | A_One_Minus_Vertex))
		Shader_setConstant1f("identityLight", tr.identityLight);

	if(afuncs & (A_Lighting_Specular | A_Portal) || tfuncs & T_Enviroment_Mapped)
		Shader_setConstant3f("viewOrigin", backEnd.ori.viewOrigin[0], backEnd.ori.viewOrigin[1], backEnd.ori.viewOrigin[2]);

	if(tfuncs & (TM_Scroll | TM_Turbulent | TM_Rotate))
		Shader_setConstant1f("shaderTime", tess.shaderTime);

	if(cfuncs & C_Identity_Lighting)
	{
		// ILB
	}
	if(cfuncs & C_Lighting_Diffuse)
	{
		Shader_setConstant3f("ambientLight", backEnd.currentEntity->ambientLight[0], backEnd.currentEntity->ambientLight[1], backEnd.currentEntity->ambientLight[2]);
		Shader_setConstant3f("directedLight", backEnd.currentEntity->directedLight[0], backEnd.currentEntity->directedLight[1], backEnd.currentEntity->directedLight[2]);
		Shader_setConstant3f("lightDir", backEnd.currentEntity->lightDir[0], backEnd.currentEntity->lightDir[1], backEnd.currentEntity->lightDir[2]);
	}
	if(cfuncs & C_Exact_Vertex)
	{
		// ILB
	}
	if(cfuncs & C_Vertex)
	{
		// ILB
	}
	if(cfuncs & C_One_Minus_Vertex)
	{
		// ILB
	}
	if(cfuncs & C_Fog)
	{
		fog_t *fog = tr.world->fogs + tess.fogNum;
		Shader_setConstant4f("C_Fog", fog->color[0], fog->color[1], fog->color[2], fog->color[3]);
	}
	if(cfuncs & C_Entity)
	{
		Shader_setConstant4f("C_Entity",
			backEnd.currentEntity->e.shaderRGBA[0] * (1.0/256.0),
			backEnd.currentEntity->e.shaderRGBA[1] * (1.0/256.0),
			backEnd.currentEntity->e.shaderRGBA[2] * (1.0/256.0),
			backEnd.currentEntity->e.shaderRGBA[3] * (1.0/256.0)
		);
	}
	if(cfuncs & C_One_Minus_Entity)
	{
		Shader_setConstant4f("C_One_Minus_Entity",
			1.0 - (backEnd.currentEntity->e.shaderRGBA[0]  * (1.0/256.0)),
			1.0 - (backEnd.currentEntity->e.shaderRGBA[1]  * (1.0/256.0)),
			1.0 - (backEnd.currentEntity->e.shaderRGBA[2]  * (1.0/256.0)),
			1.0 - (backEnd.currentEntity->e.shaderRGBA[3]  * (1.0/256.0))
		);
	}

	if(afuncs & A_Lighting_Specular)
	{
	}
	if(afuncs & A_Entity)
	{
		Shader_setConstant1f("A_Entity", backEnd.currentEntity->e.shaderRGBA[3] * (1.0/256.0));
	}
	if(afuncs & A_One_Minus_Entity)
	{
		Shader_setConstant1f("A_One_Minus_Entity", 1.0 - (backEnd.currentEntity->e.shaderRGBA[3]  * (1.0/256.0)));
	}
	if(afuncs & A_Vertex)
	{
		// ILB
	}
	if(afuncs & A_One_Minus_Vertex)
	{
		// ILB
	}
	if(afuncs & A_Portal)
	{
		Shader_setConstant1f("portalRange", pShader->portalRange);
	}

	if(tfuncs & T_Texture)
	{
		GL_SelectTexture(0);
		for ( i = 0 ; i < tess.numVertexes ; i++ )
		{
			tess.svars.texcoords[0][i][0] = tess.texCoords[i][0][0];
			tess.svars.texcoords[0][i][1] = tess.texCoords[i][0][1];
		}
		qglEnableClientState(GL_TEXTURE_COORD_ARRAY);
		qglTexCoordPointer( 2, GL_FLOAT, 0, tess.svars.texcoords[0] );
	}
	if(tfuncs & T_LightMap)
	{
		GL_SelectTexture(1);
		for ( i = 0 ; i < tess.numVertexes ; i++ )
		{
			tess.svars.texcoords[1][i][0] = tess.texCoords[i][1][0];
			tess.svars.texcoords[1][i][1] = tess.texCoords[i][1][1];
		}
		qglEnableClientState(GL_TEXTURE_COORD_ARRAY);
		qglTexCoordPointer( 2, GL_FLOAT, 0, tess.svars.texcoords[1] );
	}
	if(tfuncs & T_Enviroment_Mapped)
	{
		// ILB
	}

	if(mfuncs & M_CurrentEntTexCoord)
	{
		Shader_setConstant2f("M_CurrentEntTexCoord", backEnd.currentEntity->e.shaderTexCoord[0], backEnd.currentEntity->e.shaderTexCoord[1]);
	}

	qglVertexPointer(3, GL_FLOAT, 16, input->xyz);
	if (GL_EXT_compiled_vertex_array_supported)
    {
        qglLockArraysEXT(0, input->numVertexes);
        GLimp_LogComment( "glLockArraysEXT\n" );
    }

	memset(glState.currenttextures, 0, sizeof(int) * 32);
    for(stage=0, i=0; stage < MAX_SHADER_STAGES; stage++)
    {
        shaderStage_t *pStage = pShader->stages[stage];
		char iname[] = "Texture^";
		image_t *img;

        if(!pStage)
			break;

		for(b=0; b<NUM_TEXTURE_BUNDLES; b++)
		{
			if(!pStage->bundle[b].image[0])
				break;

			if ( pStage->bundle[b].vertexLightmap && ( (r_vertexLight->integer && !r_uiFullScreen->integer) || glConfig.hardwareType == GLHW_PERMEDIA2 ) && r_lightmap->integer )
				img = tr.whiteImage;
			else
				img = R_BindAnimatedImage(&pStage->bundle[b]);

			iname[7] = '0' + i++;
			Shader_setImage(iname, img);
		}
	}

	GL_State(glShader->statebits);
    GL_Cull( pShader->cullType );
    if(pShader->polygonOffset)
    {
        qglEnable( GL_POLYGON_OFFSET_FILL );
        qglPolygonOffset( r_offsetFactor->value, r_offsetUnits->value );
    }

	R_DrawElements( input->numIndexes, input->indexes );

	if(cfuncs & C_Lighting_Diffuse || afuncs & A_Lighting_Specular || tfuncs & T_Enviroment_Mapped)
		qglDisableClientState(GL_NORMAL_ARRAY);
    if(cfuncs & (C_Exact_Vertex | C_Vertex | C_One_Minus_Vertex) || afuncs & (A_Vertex | A_One_Minus_Vertex))
		qglDisableClientState( GL_COLOR_ARRAY);
	while(i)
	{
		GL_SelectTexture(--i);
		GL_Bind(NULL);
		if((i == 1 && tfuncs & T_LightMap) || (!i && tfuncs & T_Texture))
			qglDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	Shader_Use(NULL);
    if ( tess.dlightBits && tess.shader->sort <= SS_OPAQUE && !(tess.shader->surfaceFlags & (SURF_NODLIGHT | SURF_SKY) ) )
        ProjectDlightTexture();

    if ( tess.fogNum && tess.shader->fogPass )
        RB_FogPass();

    if (GL_EXT_compiled_vertex_array_supported)
    {
        qglUnlockArraysEXT();
        GLimp_LogComment( "glUnlockArraysEXT\n" );
    }

    if ( input->shader->polygonOffset )
        qglDisable( GL_POLYGON_OFFSET_FILL );
}
