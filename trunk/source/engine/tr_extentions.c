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
// tr_extentions.c - all os extention loading
#include "tr_local.h"

// GL_VERSION_1_2
qboolean GL_VERSION_1_2_supported;
qglDeclare(PFNGLBLENDCOLORPROC, glBlendColor);
qglDeclare(PFNGLBLENDEQUATIONPROC, glBlendEquation);
qglDeclare(PFNGLDRAWRANGEELEMENTSPROC, glDrawRangeElements);
qglDeclare(PFNGLCOLORTABLEPROC, glColorTable);
qglDeclare(PFNGLCOLORTABLEPARAMETERFVPROC, glColorTableParameterfv);
qglDeclare(PFNGLCOLORTABLEPARAMETERIVPROC, glColorTableParameteriv);
qglDeclare(PFNGLCOPYCOLORTABLEPROC, glCopyColorTable);
qglDeclare(PFNGLGETCOLORTABLEPROC, glGetColorTable);
qglDeclare(PFNGLGETCOLORTABLEPARAMETERFVPROC, glGetColorTableParameterfv);
qglDeclare(PFNGLGETCOLORTABLEPARAMETERIVPROC, glGetColorTableParameteriv);
qglDeclare(PFNGLCOLORSUBTABLEPROC, glColorSubTable);
qglDeclare(PFNGLCOPYCOLORSUBTABLEPROC, glCopyColorSubTable);
qglDeclare(PFNGLCONVOLUTIONFILTER1DPROC, glConvolutionFilter1D);
qglDeclare(PFNGLCONVOLUTIONFILTER2DPROC, glConvolutionFilter2D);
qglDeclare(PFNGLCONVOLUTIONPARAMETERFPROC, glConvolutionParameterf);
qglDeclare(PFNGLCONVOLUTIONPARAMETERFVPROC, glConvolutionParameterfv);
qglDeclare(PFNGLCONVOLUTIONPARAMETERIPROC, glConvolutionParameteri);
qglDeclare(PFNGLCONVOLUTIONPARAMETERIVPROC, glConvolutionParameteriv);
qglDeclare(PFNGLCOPYCONVOLUTIONFILTER1DPROC, glCopyConvolutionFilter1D);
qglDeclare(PFNGLCOPYCONVOLUTIONFILTER2DPROC, glCopyConvolutionFilter2D);
qglDeclare(PFNGLGETCONVOLUTIONFILTERPROC, glGetConvolutionFilter);
qglDeclare(PFNGLGETCONVOLUTIONPARAMETERFVPROC, glGetConvolutionParameterfv);
qglDeclare(PFNGLGETCONVOLUTIONPARAMETERIVPROC, glGetConvolutionParameteriv);
qglDeclare(PFNGLGETSEPARABLEFILTERPROC, glGetSeparableFilter);
qglDeclare(PFNGLSEPARABLEFILTER2DPROC, glSeparableFilter2D);
qglDeclare(PFNGLGETHISTOGRAMPROC, glGetHistogram);
qglDeclare(PFNGLGETHISTOGRAMPARAMETERFVPROC, glGetHistogramParameterfv);
qglDeclare(PFNGLGETHISTOGRAMPARAMETERIVPROC, glGetHistogramParameteriv);
qglDeclare(PFNGLGETMINMAXPROC, glGetMinmax);
qglDeclare(PFNGLGETMINMAXPARAMETERFVPROC, glGetMinmaxParameterfv);
qglDeclare(PFNGLGETMINMAXPARAMETERIVPROC, glGetMinmaxParameteriv);
qglDeclare(PFNGLHISTOGRAMPROC, glHistogram);
qglDeclare(PFNGLMINMAXPROC, glMinmax);
qglDeclare(PFNGLRESETHISTOGRAMPROC, glResetHistogram);
qglDeclare(PFNGLRESETMINMAXPROC, glResetMinmax);
qglDeclare(PFNGLTEXIMAGE3DPROC, glTexImage3D);
qglDeclare(PFNGLTEXSUBIMAGE3DPROC, glTexSubImage3D);
qglDeclare(PFNGLCOPYTEXSUBIMAGE3DPROC, glCopyTexSubImage3D);

// GL_VERSION_1_3
qboolean GL_VERSION_1_3_supported;
qglDeclare(PFNGLACTIVETEXTUREPROC, glActiveTexture);
qglDeclare(PFNGLCLIENTACTIVETEXTUREPROC, glClientActiveTexture);
qglDeclare(PFNGLMULTITEXCOORD1DPROC, glMultiTexCoord1d);
qglDeclare(PFNGLMULTITEXCOORD1DVPROC, glMultiTexCoord1dv);
qglDeclare(PFNGLMULTITEXCOORD1FPROC, glMultiTexCoord1f);
qglDeclare(PFNGLMULTITEXCOORD1FVPROC, glMultiTexCoord1fv);
qglDeclare(PFNGLMULTITEXCOORD1IPROC, glMultiTexCoord1i);
qglDeclare(PFNGLMULTITEXCOORD1IVPROC, glMultiTexCoord1iv);
qglDeclare(PFNGLMULTITEXCOORD1SPROC, glMultiTexCoord1s);
qglDeclare(PFNGLMULTITEXCOORD1SVPROC, glMultiTexCoord1sv);
qglDeclare(PFNGLMULTITEXCOORD2DPROC, glMultiTexCoord2d);
qglDeclare(PFNGLMULTITEXCOORD2DVPROC, glMultiTexCoord2dv);
qglDeclare(PFNGLMULTITEXCOORD2FPROC, glMultiTexCoord2f);
qglDeclare(PFNGLMULTITEXCOORD2FVPROC, glMultiTexCoord2fv);
qglDeclare(PFNGLMULTITEXCOORD2IPROC, glMultiTexCoord2i);
qglDeclare(PFNGLMULTITEXCOORD2IVPROC, glMultiTexCoord2iv);
qglDeclare(PFNGLMULTITEXCOORD2SPROC, glMultiTexCoord2s);
qglDeclare(PFNGLMULTITEXCOORD2SVPROC, glMultiTexCoord2sv);
qglDeclare(PFNGLMULTITEXCOORD3DPROC, glMultiTexCoord3d);
qglDeclare(PFNGLMULTITEXCOORD3DVPROC, glMultiTexCoord3dv);
qglDeclare(PFNGLMULTITEXCOORD3FPROC, glMultiTexCoord3f);
qglDeclare(PFNGLMULTITEXCOORD3FVPROC, glMultiTexCoord3fv);
qglDeclare(PFNGLMULTITEXCOORD3IPROC, glMultiTexCoord3i);
qglDeclare(PFNGLMULTITEXCOORD3IVPROC, glMultiTexCoord3iv);
qglDeclare(PFNGLMULTITEXCOORD3SPROC, glMultiTexCoord3s);
qglDeclare(PFNGLMULTITEXCOORD3SVPROC, glMultiTexCoord3sv);
qglDeclare(PFNGLMULTITEXCOORD4DPROC, glMultiTexCoord4d);
qglDeclare(PFNGLMULTITEXCOORD4DVPROC, glMultiTexCoord4dv);
qglDeclare(PFNGLMULTITEXCOORD4FPROC, glMultiTexCoord4f);
qglDeclare(PFNGLMULTITEXCOORD4FVPROC, glMultiTexCoord4fv);
qglDeclare(PFNGLMULTITEXCOORD4IPROC, glMultiTexCoord4i);
qglDeclare(PFNGLMULTITEXCOORD4IVPROC, glMultiTexCoord4iv);
qglDeclare(PFNGLMULTITEXCOORD4SPROC, glMultiTexCoord4s);
qglDeclare(PFNGLMULTITEXCOORD4SVPROC, glMultiTexCoord4sv);
qglDeclare(PFNGLLOADTRANSPOSEMATRIXFPROC, glLoadTransposeMatrixf);
qglDeclare(PFNGLLOADTRANSPOSEMATRIXDPROC, glLoadTransposeMatrixd);
qglDeclare(PFNGLMULTTRANSPOSEMATRIXFPROC, glMultTransposeMatrixf);
qglDeclare(PFNGLMULTTRANSPOSEMATRIXDPROC, glMultTransposeMatrixd);
qglDeclare(PFNGLSAMPLECOVERAGEPROC, glSampleCoverage);
qglDeclare(PFNGLCOMPRESSEDTEXIMAGE3DPROC, glCompressedTexImage3D);
qglDeclare(PFNGLCOMPRESSEDTEXIMAGE2DPROC, glCompressedTexImage2D);
qglDeclare(PFNGLCOMPRESSEDTEXIMAGE1DPROC, glCompressedTexImage1D);
qglDeclare(PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC, glCompressedTexSubImage3D);
qglDeclare(PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC, glCompressedTexSubImage2D);
qglDeclare(PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC, glCompressedTexSubImage1D);
qglDeclare(PFNGLGETCOMPRESSEDTEXIMAGEPROC, glGetCompressedTexImage);

// GL_VERSION_1_4
qboolean GL_VERSION_1_4_supported;
qglDeclare(PFNGLBLENDFUNCSEPARATEPROC, glBlendFuncSeparate);
qglDeclare(PFNGLFOGCOORDFPROC, glFogCoordf);
qglDeclare(PFNGLFOGCOORDFVPROC, glFogCoordfv);
qglDeclare(PFNGLFOGCOORDDPROC, glFogCoordd);
qglDeclare(PFNGLFOGCOORDDVPROC, glFogCoorddv);
qglDeclare(PFNGLFOGCOORDPOINTERPROC, glFogCoordPointer);
qglDeclare(PFNGLMULTIDRAWARRAYSPROC, glMultiDrawArrays);
qglDeclare(PFNGLMULTIDRAWELEMENTSPROC, glMultiDrawElements);
qglDeclare(PFNGLPOINTPARAMETERFPROC, glPointParameterf);
qglDeclare(PFNGLPOINTPARAMETERFVPROC, glPointParameterfv);
qglDeclare(PFNGLPOINTPARAMETERIPROC, glPointParameteri);
qglDeclare(PFNGLPOINTPARAMETERIVPROC, glPointParameteriv);
qglDeclare(PFNGLSECONDARYCOLOR3BPROC, glSecondaryColor3b);
qglDeclare(PFNGLSECONDARYCOLOR3BVPROC, glSecondaryColor3bv);
qglDeclare(PFNGLSECONDARYCOLOR3DPROC, glSecondaryColor3d);
qglDeclare(PFNGLSECONDARYCOLOR3DVPROC, glSecondaryColor3dv);
qglDeclare(PFNGLSECONDARYCOLOR3FPROC, glSecondaryColor3f);
qglDeclare(PFNGLSECONDARYCOLOR3FVPROC, glSecondaryColor3fv);
qglDeclare(PFNGLSECONDARYCOLOR3IPROC, glSecondaryColor3i);
qglDeclare(PFNGLSECONDARYCOLOR3IVPROC, glSecondaryColor3iv);
qglDeclare(PFNGLSECONDARYCOLOR3SPROC, glSecondaryColor3s);
qglDeclare(PFNGLSECONDARYCOLOR3SVPROC, glSecondaryColor3sv);
qglDeclare(PFNGLSECONDARYCOLOR3UBPROC, glSecondaryColor3ub);
qglDeclare(PFNGLSECONDARYCOLOR3UBVPROC, glSecondaryColor3ubv);
qglDeclare(PFNGLSECONDARYCOLOR3UIPROC, glSecondaryColor3ui);
qglDeclare(PFNGLSECONDARYCOLOR3UIVPROC, glSecondaryColor3uiv);
qglDeclare(PFNGLSECONDARYCOLOR3USPROC, glSecondaryColor3us);
qglDeclare(PFNGLSECONDARYCOLOR3USVPROC, glSecondaryColor3usv);
qglDeclare(PFNGLSECONDARYCOLORPOINTERPROC, glSecondaryColorPointer);
qglDeclare(PFNGLWINDOWPOS2DPROC, glWindowPos2d);
qglDeclare(PFNGLWINDOWPOS2DVPROC, glWindowPos2dv);
qglDeclare(PFNGLWINDOWPOS2FPROC, glWindowPos2f);
qglDeclare(PFNGLWINDOWPOS2FVPROC, glWindowPos2fv);
qglDeclare(PFNGLWINDOWPOS2IPROC, glWindowPos2i);
qglDeclare(PFNGLWINDOWPOS2IVPROC, glWindowPos2iv);
qglDeclare(PFNGLWINDOWPOS2SPROC, glWindowPos2s);
qglDeclare(PFNGLWINDOWPOS2SVPROC, glWindowPos2sv);
qglDeclare(PFNGLWINDOWPOS3DPROC, glWindowPos3d);
qglDeclare(PFNGLWINDOWPOS3DVPROC, glWindowPos3dv);
qglDeclare(PFNGLWINDOWPOS3FPROC, glWindowPos3f);
qglDeclare(PFNGLWINDOWPOS3FVPROC, glWindowPos3fv);
qglDeclare(PFNGLWINDOWPOS3IPROC, glWindowPos3i);
qglDeclare(PFNGLWINDOWPOS3IVPROC, glWindowPos3iv);
qglDeclare(PFNGLWINDOWPOS3SPROC, glWindowPos3s);
qglDeclare(PFNGLWINDOWPOS3SVPROC, glWindowPos3sv);

// GL_VERSION_1_5
qboolean GL_VERSION_1_5_supported;
qglDeclare(PFNGLGENQUERIESPROC, glGenQueries);
qglDeclare(PFNGLDELETEQUERIESPROC, glDeleteQueries);
qglDeclare(PFNGLISQUERYPROC, glIsQuery);
qglDeclare(PFNGLBEGINQUERYPROC, glBeginQuery);
qglDeclare(PFNGLENDQUERYPROC, glEndQuery);
qglDeclare(PFNGLGETQUERYIVPROC, glGetQueryiv);
qglDeclare(PFNGLGETQUERYOBJECTIVPROC, glGetQueryObjectiv);
qglDeclare(PFNGLGETQUERYOBJECTUIVPROC, glGetQueryObjectuiv);
qglDeclare(PFNGLBINDBUFFERPROC, glBindBuffer);
qglDeclare(PFNGLDELETEBUFFERSPROC, glDeleteBuffers);
qglDeclare(PFNGLGENBUFFERSPROC, glGenBuffers);
qglDeclare(PFNGLISBUFFERPROC, glIsBuffer);
qglDeclare(PFNGLBUFFERDATAPROC, glBufferData);
qglDeclare(PFNGLBUFFERSUBDATAPROC, glBufferSubData);
qglDeclare(PFNGLGETBUFFERSUBDATAPROC, glGetBufferSubData);
qglDeclare(PFNGLMAPBUFFERPROC, glMapBuffer);
qglDeclare(PFNGLUNMAPBUFFERPROC, glUnmapBuffer);
qglDeclare(PFNGLGETBUFFERPARAMETERIVPROC, glGetBufferParameteriv);
qglDeclare(PFNGLGETBUFFERPOINTERVPROC, glGetBufferPointerv);

// GL_VERSION_2_0
qboolean GL_VERSION_2_0_supported;
qglDeclare(PFNGLBLENDEQUATIONSEPARATEPROC, glBlendEquationSeparate);
qglDeclare(PFNGLDRAWBUFFERSPROC, glDrawBuffers);
qglDeclare(PFNGLSTENCILOPSEPARATEPROC, glStencilOpSeparate);
qglDeclare(PFNGLSTENCILFUNCSEPARATEPROC, glStencilFuncSeparate);
qglDeclare(PFNGLSTENCILMASKSEPARATEPROC, glStencilMaskSeparate);
qglDeclare(PFNGLATTACHSHADERPROC, glAttachShader);
qglDeclare(PFNGLBINDATTRIBLOCATIONPROC, glBindAttribLocation);
qglDeclare(PFNGLCOMPILESHADERPROC, glCompileShader);
qglDeclare(PFNGLCREATEPROGRAMPROC, glCreateProgram);
qglDeclare(PFNGLCREATESHADERPROC, glCreateShader);
qglDeclare(PFNGLDELETEPROGRAMPROC, glDeleteProgram);
qglDeclare(PFNGLDELETESHADERPROC, glDeleteShader);
qglDeclare(PFNGLDETACHSHADERPROC, glDetachShader);
qglDeclare(PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray);
qglDeclare(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray);
qglDeclare(PFNGLGETACTIVEATTRIBPROC, glGetActiveAttrib);
qglDeclare(PFNGLGETACTIVEUNIFORMPROC, glGetActiveUniform);
qglDeclare(PFNGLGETATTACHEDSHADERSPROC, glGetAttachedShaders);
qglDeclare(PFNGLGETATTRIBLOCATIONPROC, glGetAttribLocation);
qglDeclare(PFNGLGETPROGRAMIVPROC, glGetProgramiv);
qglDeclare(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog);
qglDeclare(PFNGLGETSHADERIVPROC, glGetShaderiv);
qglDeclare(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog);
qglDeclare(PFNGLGETSHADERSOURCEPROC, glGetShaderSource);
qglDeclare(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation);
qglDeclare(PFNGLGETUNIFORMFVPROC, glGetUniformfv);
qglDeclare(PFNGLGETUNIFORMIVPROC, glGetUniformiv);
qglDeclare(PFNGLGETVERTEXATTRIBDVPROC, glGetVertexAttribdv);
qglDeclare(PFNGLGETVERTEXATTRIBFVPROC, glGetVertexAttribfv);
qglDeclare(PFNGLGETVERTEXATTRIBIVPROC, glGetVertexAttribiv);
qglDeclare(PFNGLGETVERTEXATTRIBPOINTERVPROC, glGetVertexAttribPointerv);
qglDeclare(PFNGLISPROGRAMPROC, glIsProgram);
qglDeclare(PFNGLISSHADERPROC, glIsShader);
qglDeclare(PFNGLLINKPROGRAMPROC, glLinkProgram);
qglDeclare(PFNGLSHADERSOURCEPROC, glShaderSource);
qglDeclare(PFNGLUSEPROGRAMPROC, glUseProgram);
qglDeclare(PFNGLUNIFORM1FPROC, glUniform1f);
qglDeclare(PFNGLUNIFORM2FPROC, glUniform2f);
qglDeclare(PFNGLUNIFORM3FPROC, glUniform3f);
qglDeclare(PFNGLUNIFORM4FPROC, glUniform4f);
qglDeclare(PFNGLUNIFORM1IPROC, glUniform1i);
qglDeclare(PFNGLUNIFORM2IPROC, glUniform2i);
qglDeclare(PFNGLUNIFORM3IPROC, glUniform3i);
qglDeclare(PFNGLUNIFORM4IPROC, glUniform4i);
qglDeclare(PFNGLUNIFORM1FVPROC, glUniform1fv);
qglDeclare(PFNGLUNIFORM2FVPROC, glUniform2fv);
qglDeclare(PFNGLUNIFORM3FVPROC, glUniform3fv);
qglDeclare(PFNGLUNIFORM4FVPROC, glUniform4fv);
qglDeclare(PFNGLUNIFORM1IVPROC, glUniform1iv);
qglDeclare(PFNGLUNIFORM2IVPROC, glUniform2iv);
qglDeclare(PFNGLUNIFORM3IVPROC, glUniform3iv);
qglDeclare(PFNGLUNIFORM4IVPROC, glUniform4iv);
qglDeclare(PFNGLUNIFORMMATRIX2FVPROC, glUniformMatrix2fv);
qglDeclare(PFNGLUNIFORMMATRIX3FVPROC, glUniformMatrix3fv);
qglDeclare(PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix4fv);
qglDeclare(PFNGLVALIDATEPROGRAMPROC, glValidateProgram);
qglDeclare(PFNGLVERTEXATTRIB1DPROC, glVertexAttrib1d);
qglDeclare(PFNGLVERTEXATTRIB1DVPROC, glVertexAttrib1dv);
qglDeclare(PFNGLVERTEXATTRIB1FPROC, glVertexAttrib1f);
qglDeclare(PFNGLVERTEXATTRIB1FVPROC, glVertexAttrib1fv);
qglDeclare(PFNGLVERTEXATTRIB1SPROC, glVertexAttrib1s);
qglDeclare(PFNGLVERTEXATTRIB1SVPROC, glVertexAttrib1sv);
qglDeclare(PFNGLVERTEXATTRIB2DPROC, glVertexAttrib2d);
qglDeclare(PFNGLVERTEXATTRIB2DVPROC, glVertexAttrib2dv);
qglDeclare(PFNGLVERTEXATTRIB2FPROC, glVertexAttrib2f);
qglDeclare(PFNGLVERTEXATTRIB2FVPROC, glVertexAttrib2fv);
qglDeclare(PFNGLVERTEXATTRIB2SPROC, glVertexAttrib2s);
qglDeclare(PFNGLVERTEXATTRIB2SVPROC, glVertexAttrib2sv);
qglDeclare(PFNGLVERTEXATTRIB3DPROC, glVertexAttrib3d);
qglDeclare(PFNGLVERTEXATTRIB3DVPROC, glVertexAttrib3dv);
qglDeclare(PFNGLVERTEXATTRIB3FPROC, glVertexAttrib3f);
qglDeclare(PFNGLVERTEXATTRIB3FVPROC, glVertexAttrib3fv);
qglDeclare(PFNGLVERTEXATTRIB3SPROC, glVertexAttrib3s);
qglDeclare(PFNGLVERTEXATTRIB3SVPROC, glVertexAttrib3sv);
qglDeclare(PFNGLVERTEXATTRIB4NBVPROC, glVertexAttrib4Nbv);
qglDeclare(PFNGLVERTEXATTRIB4NIVPROC, glVertexAttrib4Niv);
qglDeclare(PFNGLVERTEXATTRIB4NSVPROC, glVertexAttrib4Nsv);
qglDeclare(PFNGLVERTEXATTRIB4NUBPROC, glVertexAttrib4Nub);
qglDeclare(PFNGLVERTEXATTRIB4NUBVPROC, glVertexAttrib4Nubv);
qglDeclare(PFNGLVERTEXATTRIB4NUIVPROC, glVertexAttrib4Nuiv);
qglDeclare(PFNGLVERTEXATTRIB4NUSVPROC, glVertexAttrib4Nusv);
qglDeclare(PFNGLVERTEXATTRIB4BVPROC, glVertexAttrib4bv);
qglDeclare(PFNGLVERTEXATTRIB4DPROC, glVertexAttrib4d);
qglDeclare(PFNGLVERTEXATTRIB4DVPROC, glVertexAttrib4dv);
qglDeclare(PFNGLVERTEXATTRIB4FPROC, glVertexAttrib4f);
qglDeclare(PFNGLVERTEXATTRIB4FVPROC, glVertexAttrib4fv);
qglDeclare(PFNGLVERTEXATTRIB4IVPROC, glVertexAttrib4iv);
qglDeclare(PFNGLVERTEXATTRIB4SPROC, glVertexAttrib4s);
qglDeclare(PFNGLVERTEXATTRIB4SVPROC, glVertexAttrib4sv);
qglDeclare(PFNGLVERTEXATTRIB4UBVPROC, glVertexAttrib4ubv);
qglDeclare(PFNGLVERTEXATTRIB4UIVPROC, glVertexAttrib4uiv);
qglDeclare(PFNGLVERTEXATTRIB4USVPROC, glVertexAttrib4usv);
qglDeclare(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer);

qboolean GL_multitexture; // ARB_multitexture gets overloaded by version 1.3

qboolean GL_S3_s3tc_supported;

qboolean GL_EXT_texture_env_add_supported;

qboolean GL_EXT_compiled_vertex_array_supported;
qglDeclare(PFNGLLOCKARRAYSEXTPROC, glLockArraysEXT);
qglDeclare(PFNGLUNLOCKARRAYSEXTPROC, glUnlockArraysEXT);

qboolean GL_EXT_framebuffer_object_supported;
qglDeclare(PFNGLISRENDERBUFFEREXTPROC, glIsRenderbufferEXT);
qglDeclare(PFNGLBINDRENDERBUFFEREXTPROC, glBindRenderbufferEXT);
qglDeclare(PFNGLDELETERENDERBUFFERSEXTPROC, glDeleteRenderbuffersEXT);
qglDeclare(PFNGLGENRENDERBUFFERSEXTPROC, glGenRenderbuffersEXT);
qglDeclare(PFNGLRENDERBUFFERSTORAGEEXTPROC, glRenderbufferStorageEXT);
qglDeclare(PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC, glGetRenderbufferParameterivEXT);
qglDeclare(PFNGLISFRAMEBUFFEREXTPROC, glIsFramebufferEXT);
qglDeclare(PFNGLBINDFRAMEBUFFEREXTPROC, glBindFramebufferEXT);
qglDeclare(PFNGLDELETEFRAMEBUFFERSEXTPROC, glDeleteFramebuffersEXT);
qglDeclare(PFNGLGENFRAMEBUFFERSEXTPROC, glGenFramebuffersEXT);
qglDeclare(PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC, glCheckFramebufferStatusEXT);
qglDeclare(PFNGLFRAMEBUFFERTEXTURE1DEXTPROC, glFramebufferTexture1DEXT);
qglDeclare(PFNGLFRAMEBUFFERTEXTURE2DEXTPROC, glFramebufferTexture2DEXT);
qglDeclare(PFNGLFRAMEBUFFERTEXTURE3DEXTPROC, glFramebufferTexture3DEXT);
qglDeclare(PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC, glFramebufferRenderbufferEXT);
qglDeclare(PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC, glGetFramebufferAttachmentParameterivEXT);
qglDeclare(PFNGLGENERATEMIPMAPEXTPROC, glGenerateMipmapEXT);

#define Load(name, ignore) \
	if(!(ignore)) { \
		name ## _supported = qfalse; \
		CL_RefPrintf( PRINT_ALL, "...%s\n", (strstr(glConfig.extensions_string, #name) != NULL) ? "ignoring " #name : #name " not found" ); \
	} else { \
		name ## _supported = (strstr(glConfig.extensions_string, #name) != NULL); \
		CL_RefPrintf( PRINT_ALL, "...%s\n", name ## _supported ? "using " #name : #name " not found" ); \
		if( name ## _supported ) {
#define EndLoad() \
		} \
	}

void R_InitExtenstions(void)
{
    int version;

    GL_VERSION_1_2_supported = qfalse;
    GL_VERSION_1_3_supported = qfalse;
    GL_VERSION_1_4_supported = qfalse;
    GL_VERSION_1_5_supported = qfalse;
    GL_VERSION_2_0_supported = qfalse;

    GL_multitexture = qfalse;
    GL_S3_s3tc_supported = qfalse;
    GL_EXT_texture_env_add_supported = qfalse;
    GL_EXT_compiled_vertex_array_supported = qfalse;
    GL_EXT_framebuffer_object_supported = qfalse;

    if ( !r_allowExtensions->integer )
    {
        CL_RefPrintf( PRINT_ALL, "*** IGNORING OPENGL EXTENSIONS ***\n" );
        return;
    }

    Q_strncpyz( glConfig.extensions_string, (const char *)qglGetString (GL_EXTENSIONS), sizeof( glConfig.extensions_string ) );
    CL_RefPrintf( PRINT_ALL, "Initializing OpenGL extensions\n" );

    version = ((int)glConfig.version_string[0]-(int)'0')<<8 | ((int)glConfig.version_string[2]-(int)'0');

    if(version>=258)
    {
        GL_VERSION_1_2_supported = qtrue;
        qglGetFunction(PFNGLBLENDCOLORPROC, glBlendColor);
        qglGetFunction(PFNGLBLENDEQUATIONPROC, glBlendEquation);
        qglGetFunction(PFNGLDRAWRANGEELEMENTSPROC, glDrawRangeElements);
        qglGetFunction(PFNGLCOLORTABLEPROC, glColorTable);
        qglGetFunction(PFNGLCOLORTABLEPARAMETERFVPROC, glColorTableParameterfv);
        qglGetFunction(PFNGLCOLORTABLEPARAMETERIVPROC, glColorTableParameteriv);
        qglGetFunction(PFNGLCOPYCOLORTABLEPROC, glCopyColorTable);
        qglGetFunction(PFNGLGETCOLORTABLEPROC, glGetColorTable);
        qglGetFunction(PFNGLGETCOLORTABLEPARAMETERFVPROC, glGetColorTableParameterfv);
        qglGetFunction(PFNGLGETCOLORTABLEPARAMETERIVPROC, glGetColorTableParameteriv);
        qglGetFunction(PFNGLCOLORSUBTABLEPROC, glColorSubTable);
        qglGetFunction(PFNGLCOPYCOLORSUBTABLEPROC, glCopyColorSubTable);
        qglGetFunction(PFNGLCONVOLUTIONFILTER1DPROC, glConvolutionFilter1D);
        qglGetFunction(PFNGLCONVOLUTIONFILTER2DPROC, glConvolutionFilter2D);
        qglGetFunction(PFNGLCONVOLUTIONPARAMETERFPROC, glConvolutionParameterf);
        qglGetFunction(PFNGLCONVOLUTIONPARAMETERFVPROC, glConvolutionParameterfv);
        qglGetFunction(PFNGLCONVOLUTIONPARAMETERIPROC, glConvolutionParameteri);
        qglGetFunction(PFNGLCONVOLUTIONPARAMETERIVPROC, glConvolutionParameteriv);
        qglGetFunction(PFNGLCOPYCONVOLUTIONFILTER1DPROC, glCopyConvolutionFilter1D);
        qglGetFunction(PFNGLCOPYCONVOLUTIONFILTER2DPROC, glCopyConvolutionFilter2D);
        qglGetFunction(PFNGLGETCONVOLUTIONFILTERPROC, glGetConvolutionFilter);
        qglGetFunction(PFNGLGETCONVOLUTIONPARAMETERFVPROC, glGetConvolutionParameterfv);
        qglGetFunction(PFNGLGETCONVOLUTIONPARAMETERIVPROC, glGetConvolutionParameteriv);
        qglGetFunction(PFNGLGETSEPARABLEFILTERPROC, glGetSeparableFilter);
        qglGetFunction(PFNGLSEPARABLEFILTER2DPROC, glSeparableFilter2D);
        qglGetFunction(PFNGLGETHISTOGRAMPROC, glGetHistogram);
        qglGetFunction(PFNGLGETHISTOGRAMPARAMETERFVPROC, glGetHistogramParameterfv);
        qglGetFunction(PFNGLGETHISTOGRAMPARAMETERIVPROC, glGetHistogramParameteriv);
        qglGetFunction(PFNGLGETMINMAXPROC, glGetMinmax);
        qglGetFunction(PFNGLGETMINMAXPARAMETERFVPROC, glGetMinmaxParameterfv);
        qglGetFunction(PFNGLGETMINMAXPARAMETERIVPROC, glGetMinmaxParameteriv);
        qglGetFunction(PFNGLHISTOGRAMPROC, glHistogram);
        qglGetFunction(PFNGLMINMAXPROC, glMinmax);
        qglGetFunction(PFNGLRESETHISTOGRAMPROC, glResetHistogram);
        qglGetFunction(PFNGLRESETMINMAXPROC, glResetMinmax);
        qglGetFunction(PFNGLTEXIMAGE3DPROC, glTexImage3D);
        qglGetFunction(PFNGLTEXSUBIMAGE3DPROC, glTexSubImage3D);
        qglGetFunction(PFNGLCOPYTEXSUBIMAGE3DPROC, glCopyTexSubImage3D);
        if(version>=259)
        {
            GL_VERSION_1_3_supported = qtrue;
            qglGetFunction(PFNGLACTIVETEXTUREPROC, glActiveTexture);
            qglGetFunction(PFNGLCLIENTACTIVETEXTUREPROC, glClientActiveTexture);
            qglGetFunction(PFNGLMULTITEXCOORD1DPROC, glMultiTexCoord1d);
            qglGetFunction(PFNGLMULTITEXCOORD1DVPROC, glMultiTexCoord1dv);
            qglGetFunction(PFNGLMULTITEXCOORD1FPROC, glMultiTexCoord1f);
            qglGetFunction(PFNGLMULTITEXCOORD1FVPROC, glMultiTexCoord1fv);
            qglGetFunction(PFNGLMULTITEXCOORD1IPROC, glMultiTexCoord1i);
            qglGetFunction(PFNGLMULTITEXCOORD1IVPROC, glMultiTexCoord1iv);
            qglGetFunction(PFNGLMULTITEXCOORD1SPROC, glMultiTexCoord1s);
            qglGetFunction(PFNGLMULTITEXCOORD1SVPROC, glMultiTexCoord1sv);
            qglGetFunction(PFNGLMULTITEXCOORD2DPROC, glMultiTexCoord2d);
            qglGetFunction(PFNGLMULTITEXCOORD2DVPROC, glMultiTexCoord2dv);
            qglGetFunction(PFNGLMULTITEXCOORD2FPROC, glMultiTexCoord2f);
            qglGetFunction(PFNGLMULTITEXCOORD2FVPROC, glMultiTexCoord2fv);
            qglGetFunction(PFNGLMULTITEXCOORD2IPROC, glMultiTexCoord2i);
            qglGetFunction(PFNGLMULTITEXCOORD2IVPROC, glMultiTexCoord2iv);
            qglGetFunction(PFNGLMULTITEXCOORD2SPROC, glMultiTexCoord2s);
            qglGetFunction(PFNGLMULTITEXCOORD2SVPROC, glMultiTexCoord2sv);
            qglGetFunction(PFNGLMULTITEXCOORD3DPROC, glMultiTexCoord3d);
            qglGetFunction(PFNGLMULTITEXCOORD3DVPROC, glMultiTexCoord3dv);
            qglGetFunction(PFNGLMULTITEXCOORD3FPROC, glMultiTexCoord3f);
            qglGetFunction(PFNGLMULTITEXCOORD3FVPROC, glMultiTexCoord3fv);
            qglGetFunction(PFNGLMULTITEXCOORD3IPROC, glMultiTexCoord3i);
            qglGetFunction(PFNGLMULTITEXCOORD3IVPROC, glMultiTexCoord3iv);
            qglGetFunction(PFNGLMULTITEXCOORD3SPROC, glMultiTexCoord3s);
            qglGetFunction(PFNGLMULTITEXCOORD3SVPROC, glMultiTexCoord3sv);
            qglGetFunction(PFNGLMULTITEXCOORD4DPROC, glMultiTexCoord4d);
            qglGetFunction(PFNGLMULTITEXCOORD4DVPROC, glMultiTexCoord4dv);
            qglGetFunction(PFNGLMULTITEXCOORD4FPROC, glMultiTexCoord4f);
            qglGetFunction(PFNGLMULTITEXCOORD4FVPROC, glMultiTexCoord4fv);
            qglGetFunction(PFNGLMULTITEXCOORD4IPROC, glMultiTexCoord4i);
            qglGetFunction(PFNGLMULTITEXCOORD4IVPROC, glMultiTexCoord4iv);
            qglGetFunction(PFNGLMULTITEXCOORD4SPROC, glMultiTexCoord4s);
            qglGetFunction(PFNGLMULTITEXCOORD4SVPROC, glMultiTexCoord4sv);
            qglGetFunction(PFNGLLOADTRANSPOSEMATRIXFPROC, glLoadTransposeMatrixf);
            qglGetFunction(PFNGLLOADTRANSPOSEMATRIXDPROC, glLoadTransposeMatrixd);
            qglGetFunction(PFNGLMULTTRANSPOSEMATRIXFPROC, glMultTransposeMatrixf);
            qglGetFunction(PFNGLMULTTRANSPOSEMATRIXDPROC, glMultTransposeMatrixd);
            qglGetFunction(PFNGLSAMPLECOVERAGEPROC, glSampleCoverage);
            qglGetFunction(PFNGLCOMPRESSEDTEXIMAGE3DPROC, glCompressedTexImage3D);
            qglGetFunction(PFNGLCOMPRESSEDTEXIMAGE2DPROC, glCompressedTexImage2D);
            qglGetFunction(PFNGLCOMPRESSEDTEXIMAGE1DPROC, glCompressedTexImage1D);
            qglGetFunction(PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC, glCompressedTexSubImage3D);
            qglGetFunction(PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC, glCompressedTexSubImage2D);
            qglGetFunction(PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC, glCompressedTexSubImage1D);
            qglGetFunction(PFNGLGETCOMPRESSEDTEXIMAGEPROC, glGetCompressedTexImage);
            GL_multitexture = qtrue;
            if(version>=260)
            {
                GL_VERSION_1_4_supported = qtrue;
                qglGetFunction(PFNGLBLENDFUNCSEPARATEPROC, glBlendFuncSeparate);
                qglGetFunction(PFNGLFOGCOORDFPROC, glFogCoordf);
                qglGetFunction(PFNGLFOGCOORDFVPROC, glFogCoordfv);
                qglGetFunction(PFNGLFOGCOORDDPROC, glFogCoordd);
                qglGetFunction(PFNGLFOGCOORDDVPROC, glFogCoorddv);
                qglGetFunction(PFNGLFOGCOORDPOINTERPROC, glFogCoordPointer);
                qglGetFunction(PFNGLMULTIDRAWARRAYSPROC, glMultiDrawArrays);
                qglGetFunction(PFNGLMULTIDRAWELEMENTSPROC, glMultiDrawElements);
                qglGetFunction(PFNGLPOINTPARAMETERFPROC, glPointParameterf);
                qglGetFunction(PFNGLPOINTPARAMETERFVPROC, glPointParameterfv);
                qglGetFunction(PFNGLPOINTPARAMETERIPROC, glPointParameteri);
                qglGetFunction(PFNGLPOINTPARAMETERIVPROC, glPointParameteriv);
                qglGetFunction(PFNGLSECONDARYCOLOR3BPROC, glSecondaryColor3b);
                qglGetFunction(PFNGLSECONDARYCOLOR3BVPROC, glSecondaryColor3bv);
                qglGetFunction(PFNGLSECONDARYCOLOR3DPROC, glSecondaryColor3d);
                qglGetFunction(PFNGLSECONDARYCOLOR3DVPROC, glSecondaryColor3dv);
                qglGetFunction(PFNGLSECONDARYCOLOR3FPROC, glSecondaryColor3f);
                qglGetFunction(PFNGLSECONDARYCOLOR3FVPROC, glSecondaryColor3fv);
                qglGetFunction(PFNGLSECONDARYCOLOR3IPROC, glSecondaryColor3i);
                qglGetFunction(PFNGLSECONDARYCOLOR3IVPROC, glSecondaryColor3iv);
                qglGetFunction(PFNGLSECONDARYCOLOR3SPROC, glSecondaryColor3s);
                qglGetFunction(PFNGLSECONDARYCOLOR3SVPROC, glSecondaryColor3sv);
                qglGetFunction(PFNGLSECONDARYCOLOR3UBPROC, glSecondaryColor3ub);
                qglGetFunction(PFNGLSECONDARYCOLOR3UBVPROC, glSecondaryColor3ubv);
                qglGetFunction(PFNGLSECONDARYCOLOR3UIPROC, glSecondaryColor3ui);
                qglGetFunction(PFNGLSECONDARYCOLOR3UIVPROC, glSecondaryColor3uiv);
                qglGetFunction(PFNGLSECONDARYCOLOR3USPROC, glSecondaryColor3us);
                qglGetFunction(PFNGLSECONDARYCOLOR3USVPROC, glSecondaryColor3usv);
                qglGetFunction(PFNGLSECONDARYCOLORPOINTERPROC, glSecondaryColorPointer);
                qglGetFunction(PFNGLWINDOWPOS2DPROC, glWindowPos2d);
                qglGetFunction(PFNGLWINDOWPOS2DVPROC, glWindowPos2dv);
                qglGetFunction(PFNGLWINDOWPOS2FPROC, glWindowPos2f);
                qglGetFunction(PFNGLWINDOWPOS2FVPROC, glWindowPos2fv);
                qglGetFunction(PFNGLWINDOWPOS2IPROC, glWindowPos2i);
                qglGetFunction(PFNGLWINDOWPOS2IVPROC, glWindowPos2iv);
                qglGetFunction(PFNGLWINDOWPOS2SPROC, glWindowPos2s);
                qglGetFunction(PFNGLWINDOWPOS2SVPROC, glWindowPos2sv);
                qglGetFunction(PFNGLWINDOWPOS3DPROC, glWindowPos3d);
                qglGetFunction(PFNGLWINDOWPOS3DVPROC, glWindowPos3dv);
                qglGetFunction(PFNGLWINDOWPOS3FPROC, glWindowPos3f);
                qglGetFunction(PFNGLWINDOWPOS3FVPROC, glWindowPos3fv);
                qglGetFunction(PFNGLWINDOWPOS3IPROC, glWindowPos3i);
                qglGetFunction(PFNGLWINDOWPOS3IVPROC, glWindowPos3iv);
                qglGetFunction(PFNGLWINDOWPOS3SPROC, glWindowPos3s);
                qglGetFunction(PFNGLWINDOWPOS3SVPROC, glWindowPos3sv);
                if(version>=261)
                {
                    GL_VERSION_1_5_supported = qtrue;
                    qglGetFunction(PFNGLGENQUERIESPROC, glGenQueries);
                    qglGetFunction(PFNGLDELETEQUERIESPROC, glDeleteQueries);
                    qglGetFunction(PFNGLISQUERYPROC, glIsQuery);
                    qglGetFunction(PFNGLBEGINQUERYPROC, glBeginQuery);
                    qglGetFunction(PFNGLENDQUERYPROC, glEndQuery);
                    qglGetFunction(PFNGLGETQUERYIVPROC, glGetQueryiv);
                    qglGetFunction(PFNGLGETQUERYOBJECTIVPROC, glGetQueryObjectiv);
                    qglGetFunction(PFNGLGETQUERYOBJECTUIVPROC, glGetQueryObjectuiv);
                    qglGetFunction(PFNGLBINDBUFFERPROC, glBindBuffer);
                    qglGetFunction(PFNGLDELETEBUFFERSPROC, glDeleteBuffers);
                    qglGetFunction(PFNGLGENBUFFERSPROC, glGenBuffers);
                    qglGetFunction(PFNGLISBUFFERPROC, glIsBuffer);
                    qglGetFunction(PFNGLBUFFERDATAPROC, glBufferData);
                    qglGetFunction(PFNGLBUFFERSUBDATAPROC, glBufferSubData);
                    qglGetFunction(PFNGLGETBUFFERSUBDATAPROC, glGetBufferSubData);
                    qglGetFunction(PFNGLMAPBUFFERPROC, glMapBuffer);
                    qglGetFunction(PFNGLUNMAPBUFFERPROC, glUnmapBuffer);
                    qglGetFunction(PFNGLGETBUFFERPARAMETERIVPROC, glGetBufferParameteriv);
                    qglGetFunction(PFNGLGETBUFFERPOINTERVPROC, glGetBufferPointerv);
                    if(version>=512)
                    {
                        GL_VERSION_2_0_supported = qtrue;
                        qglGetFunction(PFNGLBLENDEQUATIONSEPARATEPROC, glBlendEquationSeparate);
                        qglGetFunction(PFNGLDRAWBUFFERSPROC, glDrawBuffers);
                        qglGetFunction(PFNGLSTENCILOPSEPARATEPROC, glStencilOpSeparate);
                        qglGetFunction(PFNGLSTENCILFUNCSEPARATEPROC, glStencilFuncSeparate);
                        qglGetFunction(PFNGLSTENCILMASKSEPARATEPROC, glStencilMaskSeparate);
                        qglGetFunction(PFNGLATTACHSHADERPROC, glAttachShader);
                        qglGetFunction(PFNGLBINDATTRIBLOCATIONPROC, glBindAttribLocation);
                        qglGetFunction(PFNGLCOMPILESHADERPROC, glCompileShader);
                        qglGetFunction(PFNGLCREATEPROGRAMPROC, glCreateProgram);
                        qglGetFunction(PFNGLCREATESHADERPROC, glCreateShader);
                        qglGetFunction(PFNGLDELETEPROGRAMPROC, glDeleteProgram);
                        qglGetFunction(PFNGLDELETESHADERPROC, glDeleteShader);
                        qglGetFunction(PFNGLDETACHSHADERPROC, glDetachShader);
                        qglGetFunction(PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray);
                        qglGetFunction(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray);
                        qglGetFunction(PFNGLGETACTIVEATTRIBPROC, glGetActiveAttrib);
                        qglGetFunction(PFNGLGETACTIVEUNIFORMPROC, glGetActiveUniform);
                        qglGetFunction(PFNGLGETATTACHEDSHADERSPROC, glGetAttachedShaders);
                        qglGetFunction(PFNGLGETATTRIBLOCATIONPROC, glGetAttribLocation);
                        qglGetFunction(PFNGLGETPROGRAMIVPROC, glGetProgramiv);
                        qglGetFunction(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog);
                        qglGetFunction(PFNGLGETSHADERIVPROC, glGetShaderiv);
                        qglGetFunction(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog);
                        qglGetFunction(PFNGLGETSHADERSOURCEPROC, glGetShaderSource);
                        qglGetFunction(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation);
                        qglGetFunction(PFNGLGETUNIFORMFVPROC, glGetUniformfv);
                        qglGetFunction(PFNGLGETUNIFORMIVPROC, glGetUniformiv);
                        qglGetFunction(PFNGLGETVERTEXATTRIBDVPROC, glGetVertexAttribdv);
                        qglGetFunction(PFNGLGETVERTEXATTRIBFVPROC, glGetVertexAttribfv);
                        qglGetFunction(PFNGLGETVERTEXATTRIBIVPROC, glGetVertexAttribiv);
                        qglGetFunction(PFNGLGETVERTEXATTRIBPOINTERVPROC, glGetVertexAttribPointerv);
                        qglGetFunction(PFNGLISPROGRAMPROC, glIsProgram);
                        qglGetFunction(PFNGLISSHADERPROC, glIsShader);
                        qglGetFunction(PFNGLLINKPROGRAMPROC, glLinkProgram);
                        qglGetFunction(PFNGLSHADERSOURCEPROC, glShaderSource);
                        qglGetFunction(PFNGLUSEPROGRAMPROC, glUseProgram);
                        qglGetFunction(PFNGLUNIFORM1FPROC, glUniform1f);
                        qglGetFunction(PFNGLUNIFORM2FPROC, glUniform2f);
                        qglGetFunction(PFNGLUNIFORM3FPROC, glUniform3f);
                        qglGetFunction(PFNGLUNIFORM4FPROC, glUniform4f);
                        qglGetFunction(PFNGLUNIFORM1IPROC, glUniform1i);
                        qglGetFunction(PFNGLUNIFORM2IPROC, glUniform2i);
                        qglGetFunction(PFNGLUNIFORM3IPROC, glUniform3i);
                        qglGetFunction(PFNGLUNIFORM4IPROC, glUniform4i);
                        qglGetFunction(PFNGLUNIFORM1FVPROC, glUniform1fv);
                        qglGetFunction(PFNGLUNIFORM2FVPROC, glUniform2fv);
                        qglGetFunction(PFNGLUNIFORM3FVPROC, glUniform3fv);
                        qglGetFunction(PFNGLUNIFORM4FVPROC, glUniform4fv);
                        qglGetFunction(PFNGLUNIFORM1IVPROC, glUniform1iv);
                        qglGetFunction(PFNGLUNIFORM2IVPROC, glUniform2iv);
                        qglGetFunction(PFNGLUNIFORM3IVPROC, glUniform3iv);
                        qglGetFunction(PFNGLUNIFORM4IVPROC, glUniform4iv);
                        qglGetFunction(PFNGLUNIFORMMATRIX2FVPROC, glUniformMatrix2fv);
                        qglGetFunction(PFNGLUNIFORMMATRIX3FVPROC, glUniformMatrix3fv);
                        qglGetFunction(PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix4fv);
                        qglGetFunction(PFNGLVALIDATEPROGRAMPROC, glValidateProgram);
                        qglGetFunction(PFNGLVERTEXATTRIB1DPROC, glVertexAttrib1d);
                        qglGetFunction(PFNGLVERTEXATTRIB1DVPROC, glVertexAttrib1dv);
                        qglGetFunction(PFNGLVERTEXATTRIB1FPROC, glVertexAttrib1f);
                        qglGetFunction(PFNGLVERTEXATTRIB1FVPROC, glVertexAttrib1fv);
                        qglGetFunction(PFNGLVERTEXATTRIB1SPROC, glVertexAttrib1s);
                        qglGetFunction(PFNGLVERTEXATTRIB1SVPROC, glVertexAttrib1sv);
                        qglGetFunction(PFNGLVERTEXATTRIB2DPROC, glVertexAttrib2d);
                        qglGetFunction(PFNGLVERTEXATTRIB2DVPROC, glVertexAttrib2dv);
                        qglGetFunction(PFNGLVERTEXATTRIB2FPROC, glVertexAttrib2f);
                        qglGetFunction(PFNGLVERTEXATTRIB2FVPROC, glVertexAttrib2fv);
                        qglGetFunction(PFNGLVERTEXATTRIB2SPROC, glVertexAttrib2s);
                        qglGetFunction(PFNGLVERTEXATTRIB2SVPROC, glVertexAttrib2sv);
                        qglGetFunction(PFNGLVERTEXATTRIB3DPROC, glVertexAttrib3d);
                        qglGetFunction(PFNGLVERTEXATTRIB3DVPROC, glVertexAttrib3dv);
                        qglGetFunction(PFNGLVERTEXATTRIB3FPROC, glVertexAttrib3f);
                        qglGetFunction(PFNGLVERTEXATTRIB3FVPROC, glVertexAttrib3fv);
                        qglGetFunction(PFNGLVERTEXATTRIB3SPROC, glVertexAttrib3s);
                        qglGetFunction(PFNGLVERTEXATTRIB3SVPROC, glVertexAttrib3sv);
                        qglGetFunction(PFNGLVERTEXATTRIB4NBVPROC, glVertexAttrib4Nbv);
                        qglGetFunction(PFNGLVERTEXATTRIB4NIVPROC, glVertexAttrib4Niv);
                        qglGetFunction(PFNGLVERTEXATTRIB4NSVPROC, glVertexAttrib4Nsv);
                        qglGetFunction(PFNGLVERTEXATTRIB4NUBPROC, glVertexAttrib4Nub);
                        qglGetFunction(PFNGLVERTEXATTRIB4NUBVPROC, glVertexAttrib4Nubv);
                        qglGetFunction(PFNGLVERTEXATTRIB4NUIVPROC, glVertexAttrib4Nuiv);
                        qglGetFunction(PFNGLVERTEXATTRIB4NUSVPROC, glVertexAttrib4Nusv);
                        qglGetFunction(PFNGLVERTEXATTRIB4BVPROC, glVertexAttrib4bv);
                        qglGetFunction(PFNGLVERTEXATTRIB4DPROC, glVertexAttrib4d);
                        qglGetFunction(PFNGLVERTEXATTRIB4DVPROC, glVertexAttrib4dv);
                        qglGetFunction(PFNGLVERTEXATTRIB4FPROC, glVertexAttrib4f);
                        qglGetFunction(PFNGLVERTEXATTRIB4FVPROC, glVertexAttrib4fv);
                        qglGetFunction(PFNGLVERTEXATTRIB4IVPROC, glVertexAttrib4iv);
                        qglGetFunction(PFNGLVERTEXATTRIB4SPROC, glVertexAttrib4s);
                        qglGetFunction(PFNGLVERTEXATTRIB4SVPROC, glVertexAttrib4sv);
                        qglGetFunction(PFNGLVERTEXATTRIB4UBVPROC, glVertexAttrib4ubv);
                        qglGetFunction(PFNGLVERTEXATTRIB4UIVPROC, glVertexAttrib4uiv);
                        qglGetFunction(PFNGLVERTEXATTRIB4USVPROC, glVertexAttrib4usv);
                        qglGetFunction(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer);
                        CL_RefPrintf( PRINT_ALL, "...OpenGL 2.0 supported\n");
                    }
                    else
                        CL_RefPrintf( PRINT_ALL, "...OpenGL 1.5 supported\n");
                }
                else
                    CL_RefPrintf( PRINT_ALL, "...OpenGL 1.4 supported\n");
            }
            else
                CL_RefPrintf( PRINT_ALL, "...OpenGL 1.3 supported\n");
        }
        else
            CL_RefPrintf( PRINT_ALL, "...OpenGL 1.2 supported\n");
    }
    else
        CL_RefPrintf( PRINT_ALL, "...OpenGL 1.2 is not supported\n");

    Load(GL_S3_s3tc, r_ext_compressed_textures->integer);
    EndLoad();

    Load(GL_EXT_texture_env_add, r_ext_texture_env_add->integer);
    EndLoad();

    Load(GL_EXT_compiled_vertex_array, r_ext_compiled_vertex_array->integer);
    qglGetFunction(PFNGLLOCKARRAYSEXTPROC, glLockArraysEXT);
    qglGetFunction(PFNGLUNLOCKARRAYSEXTPROC, glUnlockArraysEXT);
    EndLoad();

//	Load(GL_EXT_framebuffer_object, 1);
    GL_EXT_framebuffer_object_supported = qtrue;
    qglGetFunction(PFNGLISRENDERBUFFEREXTPROC, glIsRenderbufferEXT);
    qglGetFunction(PFNGLBINDRENDERBUFFEREXTPROC, glBindRenderbufferEXT);
    qglGetFunction(PFNGLDELETERENDERBUFFERSEXTPROC, glDeleteRenderbuffersEXT);
    qglGetFunction(PFNGLGENRENDERBUFFERSEXTPROC, glGenRenderbuffersEXT);
    qglGetFunction(PFNGLRENDERBUFFERSTORAGEEXTPROC, glRenderbufferStorageEXT);
    qglGetFunction(PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC, glGetRenderbufferParameterivEXT);
    qglGetFunction(PFNGLISFRAMEBUFFEREXTPROC, glIsFramebufferEXT);
    qglGetFunction(PFNGLBINDFRAMEBUFFEREXTPROC, glBindFramebufferEXT);
    qglGetFunction(PFNGLDELETEFRAMEBUFFERSEXTPROC, glDeleteFramebuffersEXT);
    qglGetFunction(PFNGLGENFRAMEBUFFERSEXTPROC, glGenFramebuffersEXT);
    qglGetFunction(PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC, glCheckFramebufferStatusEXT);
    qglGetFunction(PFNGLFRAMEBUFFERTEXTURE1DEXTPROC, glFramebufferTexture1DEXT);
    qglGetFunction(PFNGLFRAMEBUFFERTEXTURE2DEXTPROC, glFramebufferTexture2DEXT);
    qglGetFunction(PFNGLFRAMEBUFFERTEXTURE3DEXTPROC, glFramebufferTexture3DEXT);
    qglGetFunction(PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC, glFramebufferRenderbufferEXT);
    qglGetFunction(PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC, glGetFramebufferAttachmentParameterivEXT);
    qglGetFunction(PFNGLGENERATEMIPMAPEXTPROC, glGenerateMipmapEXT);
//	EndLoad();
}
