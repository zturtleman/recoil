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

static GLuint fbo = 0;
static fboSet_t currentSet;

void Fbo_Bind(void)
{
    if(GL_EXT_framebuffer_object_supported)
    {
        if(!fbo) qglGenFramebuffersEXT(1, &fbo);
        qglBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
    }
}

qboolean Fbo_Unbind(void)
{
    if(GL_EXT_framebuffer_object_supported)
        qglBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    return GL_EXT_framebuffer_object_supported;
}

qboolean Fbo_IsUsable(void)
{
    if(GL_EXT_framebuffer_object_supported)
    {
        int status;
        status = qglCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
        switch(status)
        {
        case GL_FRAMEBUFFER_COMPLETE_EXT:
            return qtrue;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
            CL_RefPrintf(PRINT_ALL, "FBO Incomlete Attatchment");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
            CL_RefPrintf(PRINT_ALL, "FBO Incomlete Missing Attatchment\n");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DUPLICATE_ATTACHMENT_EXT:
            CL_RefPrintf(PRINT_ALL, "FBO Incomlete Duplicate Attatchment\n");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
            CL_RefPrintf(PRINT_ALL, "FBO Incomlete Dimensions\n");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
            CL_RefPrintf(PRINT_ALL, "FBO Incomlete Formats\n");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
            CL_RefPrintf(PRINT_ALL, "FBO Incomlete Draw Buffer\n");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
            CL_RefPrintf(PRINT_ALL, "FBO Incomlete Read Buffer\n");
            break;
        case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
            CL_RefPrintf(PRINT_ALL, "FBO Unsupported\n");
            break;
        default:
            break;
        }
    }
    Fbo_Unbind();
    return qfalse;
}

image_t *Fbo_genDepthRenderBuffer(int width, int height, int bits)
{
    if(GL_EXT_framebuffer_object_supported)
    {
        GLenum internalFormat = (bits == 16) ? GL_DEPTH_COMPONENT16 :
                                (bits == 24) ? GL_DEPTH_COMPONENT24 :
                                (bits == 32) ? GL_DEPTH_COMPONENT32 : 0;

        if(internalFormat)
        {
            image_t *image;

            image = tr.images[tr.numImages] = (image_t *)Hunk_Alloc( sizeof( image_t ), h_low );
            image->width = width;
            image->height = height;
            image->internalFormat =	internalFormat;
            image->target = GL_RENDERBUFFER_EXT;

            strcpy(image->imgName, "**DepthRenderBuffer");

            qglGenRenderbuffersEXT(1, &image->texnum);

            qglBindRenderbufferEXT(GL_RENDERBUFFER_EXT, image->texnum);
            qglRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, image->internalFormat, image->width, image->height);
            qglBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

            return image;
        }
    }

    return NULL;
}

image_t *Fbo_genStencilRenderBuffer(int width, int height, int bits)
{
    GLenum internalFormat =	(bits == 1) ? GL_STENCIL_INDEX1_EXT :
                            (bits == 4) ? GL_STENCIL_INDEX4_EXT :
                            (bits == 8) ? GL_STENCIL_INDEX8_EXT :
                            (bits == 16) ? GL_STENCIL_INDEX16_EXT : 0;

    if(GL_EXT_framebuffer_object_supported && internalFormat)
    {
        image_t *image;

        image = tr.images[tr.numImages] = (image_t *)Hunk_Alloc( sizeof( image_t ), h_low );
        image->width = width;
        image->height = height;
        image->internalFormat =	internalFormat;
        image->target = GL_RENDERBUFFER_EXT;

        strcpy(image->imgName, "**StencilRenderBuffer");

        qglGenRenderbuffersEXT(1, &image->texnum);

        qglBindRenderbufferEXT(GL_RENDERBUFFER_EXT, image->texnum);
        qglRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, image->internalFormat, image->width, image->height);
        qglBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

        return image;
    }

    return NULL;
}

image_t *Fbo_genRenderTarget(int width, int height, int bits, filter_e filter, int flags)
{
    GLenum internalFormat =	(bits == 32) ? GL_RGBA8 :
                            (bits == 64) ? GL_RGBA16F_ARB : 0;

    if(GL_EXT_framebuffer_object_supported && internalFormat)
    {
        image_t *image;

        image = tr.images[tr.numImages] = (image_t *)Hunk_Alloc( sizeof( image_t ), h_low );
        image->width = width;
        image->height = height;
        image->internalFormat =	internalFormat;
        image->target = GL_TEXTURE_2D;

        strcpy(image->imgName, "**RenderTarget");

        qglGenTextures(1, &image->texnum);
        qglBindTexture(GL_TEXTURE_2D, image->texnum);

        qglTexParameteri(image->target, GL_TEXTURE_WRAP_S, (flags & F_CLAMP_S) ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        qglTexParameteri(image->target, GL_TEXTURE_WRAP_T, (flags & F_CLAMP_T) ? GL_CLAMP_TO_EDGE : GL_REPEAT);

        qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin[filter]);
        qglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax[filter]);

        qglTexImage2D(GL_TEXTURE_2D, 0, image->internalFormat, image->width, image->height, 0, GL_RGB, GL_INT, NULL);

        qglBindTexture( GL_TEXTURE_2D, 0 );

        return image;
    }

    return NULL;
}

void Fbo_clearTexture(image_t *image)
{
    qglBindTexture(GL_TEXTURE_2D, image->texnum);
    qglTexImage2D(GL_TEXTURE_2D, 0, image->internalFormat, image->width, image->height, 0, GL_RGB, GL_INT, NULL);
    qglBindTexture( GL_TEXTURE_2D, 0 );
}

void Fbo_setBuffers(GLuint numberTargets, image_t *targets[], image_t *depth, image_t *stencil)
{
    if(GL_EXT_framebuffer_object_supported)
    {
        GLenum	drawBuffers[16];
        image_t *image;
        int i;

        Fbo_Bind();

        memset(&currentSet, 0, sizeof(fboSet_t));
        for(i=0, image=targets[0]; i<numberTargets; i++, image++)
        {
            if(image)
            {
                qglFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT + i, GL_TEXTURE_2D, image->texnum, 0);
                currentSet.color[i] = image;
                drawBuffers[i] = GL_COLOR_ATTACHMENT0_EXT + i;
            }
            else
                drawBuffers[i] = GL_COLOR_ATTACHMENT0_EXT + i; // todo, find null
        }

        if(currentSet.numColor != numberTargets)
        {
            qglDrawBuffers(numberTargets, drawBuffers);
            currentSet.numColor = numberTargets;
        }

        currentSet.depth = depth;
        currentSet.stencil = stencil;

        qglFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, (depth) ? depth->texnum : 0);
        qglFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, (stencil) ? stencil->texnum : 0);
    }
}

void Fbo_getSet(fboSet_t *set)
{
    memcpy(set, &currentSet, sizeof(fboSet_t));
}

void Fbo_applySet(fboSet_t *set)
{
    Fbo_setBuffers(set->numColor, set->color, set->depth, set->stencil);
}
