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
/*
** QGL.H
*/

#ifndef __QGL_H__
#define __QGL_H__

#define qglExtern(p, name) extern p q ## name
#define qglDeclare(p, name) p q ## name
#define qglGetFunction(p, name) do { q ## name = (p)qwglGetProcAddress( #name ); if( q ## name == NULL ) CL_RefPrintf( PRINT_ALL, "...!q" #name "\n"); } while(0)
extern void (*qwglGetProcAddress)(char *symbol);

#if defined( __LINT__ )
#   include <GL/gl.h>
#   include "glext.h"
#elif defined( _WIN32 )
#   if defined(MSVC)
#       pragma warning (disable: 4201)
#       pragma warning (disable: 4214)
#       pragma warning (disable: 4514)
#       pragma warning (disable: 4032)
#       pragma warning (disable: 4201)
#       pragma warning (disable: 4214)
#   endif
#   include <windows.h>
#   include <GL/gl.h>
#   include "glext.h"
#   include "wglext.h"
#elif defined(MACOS_X)
#   include "macosx_glimp.h"
#elif ( defined( __linux__ ) || defined( __FreeBSD__ ) )
#   include <GL/gl.h>
#   include <GL/glx.h>
#else
#   include <gl.h>
#endif

#ifndef APIENTRY
#   define APIENTRY
#endif

#ifndef WINAPI
#   define WINAPI
#endif

//===========================================================================

// non-windows systems will just redefine qgl* to gl*
#if !defined( _WIN32 ) && !defined(MACOS_X) && !defined( __linux__ ) && !defined( __FreeBSD__ ) // rb010123
#   include "qgl_linked.h"
#elif defined(MACOS_X)
#   include "macosx_qgl.h"
#else

#if defined( _WIN32 )
extern  int   ( WINAPI * qwglChoosePixelFormat )(HDC, CONST PIXELFORMATDESCRIPTOR *);
extern  int   ( WINAPI * qwglDescribePixelFormat) (HDC, int, UINT, LPPIXELFORMATDESCRIPTOR);
extern  int   ( WINAPI * qwglGetPixelFormat)(HDC);
extern  BOOL  ( WINAPI * qwglSetPixelFormat)(HDC, int, CONST PIXELFORMATDESCRIPTOR *);
extern  BOOL  ( WINAPI * qwglSwapBuffers)(HDC);
extern	BOOL  ( WINAPI * qwglGetDeviceGammaRamp3DFX)( HDC, LPVOID );
extern	BOOL  ( WINAPI * qwglSetDeviceGammaRamp3DFX)( HDC, LPVOID );
extern BOOL  ( WINAPI * qwglCopyContext)(HGLRC, HGLRC, UINT);
extern HGLRC ( WINAPI * qwglCreateContext)(HDC);
extern HGLRC ( WINAPI * qwglCreateLayerContext)(HDC, int);
extern BOOL  ( WINAPI * qwglDeleteContext)(HGLRC);
extern HGLRC ( WINAPI * qwglGetCurrentContext)(VOID);
extern HDC   ( WINAPI * qwglGetCurrentDC)(VOID);
extern BOOL  ( WINAPI * qwglMakeCurrent)(HDC, HGLRC);
extern BOOL  ( WINAPI * qwglShareLists)(HGLRC, HGLRC);
extern BOOL  ( WINAPI * qwglUseFontBitmaps)(HDC, DWORD, DWORD, DWORD);
extern BOOL  ( WINAPI * qwglUseFontOutlines)(HDC, DWORD, DWORD, DWORD, FLOAT, FLOAT, int, LPGLYPHMETRICSFLOAT);
extern BOOL ( WINAPI * qwglDescribeLayerPlane)(HDC, int, int, UINT, LPLAYERPLANEDESCRIPTOR);
extern int  ( WINAPI * qwglSetLayerPaletteEntries)(HDC, int, int, int, CONST COLORREF *);
extern int  ( WINAPI * qwglGetLayerPaletteEntries)(HDC, int, int, int, COLORREF *);
extern BOOL ( WINAPI * qwglRealizeLayerPalette)(HDC, int, BOOL);
extern BOOL ( WINAPI * qwglSwapLayerBuffers)(HDC, UINT);
extern BOOL ( WINAPI * qwglSwapIntervalEXT)( int interval );

// WGL_ARB_extensions_string
extern qboolean WGL_ARB_extensions_string_supported;
extern PFNWGLGETEXTENSIONSSTRINGARBPROC qwglGetExtensionsStringARB;

// WGL_ARB_pixel_format
extern qboolean WGL_ARB_pixel_format_supported;
extern PFNWGLGETPIXELFORMATATTRIBIVARBPROC qwglGetPixelFormatAttribivARB;
extern PFNWGLGETPIXELFORMATATTRIBFVARBPROC qwglGetPixelFormatAttribfvARB;
extern PFNWGLCHOOSEPIXELFORMATARBPROC qwglChoosePixelFormatARB;

// WGL_ARB_pixel_format_float
extern qboolean WGL_ARB_pixel_format_float_supported;

// WGL_ARB_pbuffer
extern qboolean WGL_ARB_pbuffer_supported;
extern PFNWGLCREATEPBUFFERARBPROC qwglCreatePbufferARB;
extern PFNWGLGETPBUFFERDCARBPROC qwglGetPbufferDCARB;
extern PFNWGLRELEASEPBUFFERDCARBPROC qwglReleasePbufferDCARB;
extern PFNWGLDESTROYPBUFFERARBPROC qwglDestroyPbufferARB;
extern PFNWGLQUERYPBUFFERARBPROC qwglQueryPbufferARB;

// WGL_ARB_render_texture
extern qboolean WGL_ARB_render_texture_supported;
extern PFNWGLBINDTEXIMAGEARBPROC qwglBindTexImageARB;
extern PFNWGLRELEASETEXIMAGEARBPROC qwglReleaseTexImageARB;
extern PFNWGLSETPBUFFERATTRIBARBPROC qwglSetPbufferAttribARB;
#endif	// _WIN32

#if ( (defined __linux__ )  || (defined __FreeBSD__ ) ) // rb010123
typedef XVisualInfo *(APIENTRY * PNFGLXCHOOSEVISUALPROC)( Display *dpy, int screen, int *attribList );
typedef GLXContext   (APIENTRY * PNFGLXCREATECONTEXTPROC)( Display *dpy, XVisualInfo *vis, GLXContext shareList, Bool direct );
typedef void         (APIENTRY * PNFGLXDESTROYCONTEXTPROC)( Display *dpy, GLXContext ctx );
typedef Bool         (APIENTRY * PNFGLXMAKECURRENTPROC)( Display *dpy, GLXDrawable drawable, GLXContext ctx);
typedef void         (APIENTRY * PNFGLXSWAPBUFFERSPROC)( Display *dpy, GLXDrawable drawable );

qglExtern(PNFGLXDESTROYCONTEXTPROC, glXDestroyContext);
qglExtern(PNFGLXCHOOSEVISUALPROC, glXChooseVisual);
qglExtern(PNFGLXCREATECONTEXTPROC, glXCreateContext);
qglExtern(PNFGLXMAKECURRENTPROC, glXMakeCurrent);
qglExtern(PNFGLXSWAPBUFFERSPROC, glXSwapBuffers);
#endif
#endif

typedef void (APIENTRY * PNFGLBINDTEXTUREPROC)(GLenum target, GLuint texture);
typedef void (APIENTRY * PNFGLDISABLEPROC)(GLenum cap);
typedef void (APIENTRY * PNFGLENABLEPROC)(GLenum cap);
typedef void (APIENTRY * PNFGLCULLFACEPROC)(GLenum mode);
typedef void (APIENTRY * PNFGLTEXENVFPROC)(GLenum target, GLenum pname, GLfloat param);
typedef void (APIENTRY * PNFGLDEPTHFUNCPROC)(GLenum func);
typedef void (APIENTRY * PNFGLDEPTHMASKPROC)(GLboolean flag);
typedef void (APIENTRY * PNFGLPOLYGONMODEPROC)(GLenum face, GLenum mode);
typedef void (APIENTRY * PNFGLALPHAFUNCPROC)(GLenum func, GLclampf ref);
typedef void (APIENTRY * PNFGLCLEARCOLORPROC)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
typedef void (APIENTRY * PNFGLCLEARPROC)(GLbitfield mask);
typedef void (APIENTRY * PNFGLMATRIXMODEPROC)(GLenum mode);
typedef void (APIENTRY * PNFGLLOADMATRIXFPROC)(const GLfloat *m);
typedef void (APIENTRY * PNFGLVIEWPORTPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRY * PNFGLSCISSORPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRY * PNFGLFINISHPROC)(void);
typedef void (APIENTRY * PNFGLCLIPPLANEPROC)(GLenum plane, const GLdouble *equation);
typedef void (APIENTRY * PNFGLDEPTHRANGEPROC)(GLclampd zNear, GLclampd zFar);
typedef void (APIENTRY * PNFGLBEGINPROC)(GLenum mode);
typedef void (APIENTRY * PNFGLVERTEX2FPROC)(GLfloat x, GLfloat y);
typedef void (APIENTRY * PNFGLENDPROC)(void);
typedef void (APIENTRY * PNFGLLOADIDENTITYPROC)(void);
typedef void (APIENTRY * PNFGLORTHOPROC)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far);
typedef void (APIENTRY * PNFGLTEXIMAGE2DPROC)(GLenum target, GLint level, GLint components, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (APIENTRY * PNFGLTEXPARAMETERFPROC)(GLenum target, GLenum pname, GLfloat param);
typedef void (APIENTRY * PNFGLTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei	width, GLsizei	height, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (APIENTRY * PNFGLCOLOR3FPROC)(GLfloat r, GLfloat g, GLfloat b);
typedef void (APIENTRY * PNFGLTEXCOORD2FPROC)(GLfloat s, GLfloat t);
typedef void (APIENTRY * PNFGLDRAWBUFFERPROC)(GLenum mode);
typedef void (APIENTRY * PNFGLREADPIXELSPROC)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);
typedef void (APIENTRY * PNFGLGENTEXTURESPROC)(GLsizei n, GLuint *textures);
typedef void (APIENTRY * PNFGLTEXPARAMETERFVPROC)(GLenum target, GLenum pname, const GLfloat *params);
typedef void (APIENTRY * PNFGLDELETETEXTURESPROC)(GLsizei n, const GLuint *textures);
typedef void (APIENTRY * PNFGLVERTEX3FVPROC)(const GLfloat *v);
typedef void (APIENTRY * PNFGLLINEWIDTHPROC)(GLfloat width);
typedef void (APIENTRY * PNFGLVERTEX3FPROC)(GLfloat x, GLfloat y, GLfloat z);
typedef void (APIENTRY * PNFGLCALLLISTPROC)(GLuint list);
typedef void (APIENTRY * PNFGLSTENCILMASKPROC)(GLuint mask);
typedef void (APIENTRY * PNFGLCLEARSTENCILPROC)(GLint s);
typedef void (APIENTRY * PNFGLSTENCILFUNCPROC)(GLenum func, GLint ref, GLuint mask);
typedef void (APIENTRY * PNFGLSTENCILOPPROC)(GLenum fail, GLenum zfail, GLenum zpass);
typedef GLenum (APIENTRY * PNFGLGETERRORPROC)(void);
typedef void (APIENTRY * PNFGLPUSHMATRIXPROC)(void);
typedef void (APIENTRY * PNFGLPOPMATRIXPROC)(void);
typedef void (APIENTRY * PNFGLTEXPARAMETERIPROC)(GLenum target, GLenum pname, GLint param);
typedef void (APIENTRY * PNFGLGETINTEGERVPROC)(GLenum pname, GLint *params);
typedef void (APIENTRY * PNFGLCLEARDEPTHPROC)(GLclampd depth);
typedef void (APIENTRY * PNFGLCOLOR4FPROC)(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
typedef void (APIENTRY * PNFGLSHADEMODELPROC)(GLenum mode);
typedef void (APIENTRY * PNFGLENABLECLIENTSTATEPROC)(GLenum cap);
typedef void (APIENTRY * PNFGLCOLOR4FVPROC)(const GLfloat *v);
typedef void (APIENTRY * PNFGLTEXCOORD2FVPROC)(const GLfloat *v);
typedef void (APIENTRY * PNFGLDRAWELEMENTSPROC)(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);
typedef void (APIENTRY * PNFGLDISABLECLIENTSTATEPROC)(GLenum cap);
typedef void (APIENTRY * PNFGLVERTEXPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (APIENTRY * PNFGLTEXCOORDPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (APIENTRY * PNFGLCOLORPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (APIENTRY * PNFGLPOLYGONOFFSETPROC)(GLfloat factor, GLfloat units);
typedef void (APIENTRY * PNFGLNORMALPOINTERPROC)(GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (APIENTRY * PNFGLTRANSLATEFPROC)(GLfloat x, GLfloat y, GLfloat z);
typedef void (APIENTRY * PNFGLCOLORMASKPROC)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
typedef const GLubyte *(APIENTRY * PNFGLGETSTRINGPROC)(GLenum name);
typedef void (APIENTRY * PNFGLARRAYELEMENTPROC)(GLint i);

// GL_VERSION_1_1 (only the used stuff)
qglExtern(PNFGLARRAYELEMENTPROC, glArrayElement);
qglExtern(PNFGLBINDTEXTUREPROC, glBindTexture);
qglExtern(PNFGLDISABLEPROC, glDisable);
qglExtern(PNFGLENABLEPROC, glEnable);
qglExtern(PNFGLCULLFACEPROC, glCullFace);
qglExtern(PNFGLTEXENVFPROC, glTexEnvf);
qglExtern(PNFGLDEPTHFUNCPROC, glDepthFunc);
qglExtern(PNFGLDEPTHMASKPROC, glDepthMask);
qglExtern(PNFGLPOLYGONMODEPROC, glPolygonMode);
qglExtern(PNFGLALPHAFUNCPROC, glAlphaFunc);
qglExtern(PNFGLCLEARCOLORPROC, glClearColor);
qglExtern(PNFGLCLEARPROC, glClear);
qglExtern(PNFGLMATRIXMODEPROC, glMatrixMode);
qglExtern(PNFGLLOADMATRIXFPROC, glLoadMatrixf);
qglExtern(PNFGLVIEWPORTPROC, glViewport);
qglExtern(PNFGLSCISSORPROC, glScissor);
qglExtern(PNFGLFINISHPROC, glFinish);
qglExtern(PNFGLCLIPPLANEPROC, glClipPlane);
qglExtern(PNFGLDEPTHRANGEPROC, glDepthRange);
qglExtern(PNFGLBEGINPROC, glBegin);
qglExtern(PNFGLVERTEX2FPROC, glVertex2f);
qglExtern(PNFGLENDPROC, glEnd);
qglExtern(PNFGLLOADIDENTITYPROC, glLoadIdentity);
qglExtern(PNFGLORTHOPROC, glOrtho);
qglExtern(PNFGLTEXIMAGE2DPROC, glTexImage2D);
qglExtern(PNFGLTEXPARAMETERFPROC, glTexParameterf);
qglExtern(PNFGLTEXSUBIMAGE2DPROC, glTexSubImage2D);
qglExtern(PNFGLCOLOR3FPROC, glColor3f);
qglExtern(PNFGLTEXCOORD2FPROC, glTexCoord2f);
qglExtern(PNFGLDRAWBUFFERPROC, glDrawBuffer);
qglExtern(PNFGLREADPIXELSPROC, glReadPixels);
qglExtern(PNFGLGENTEXTURESPROC, glGenTextures);
qglExtern(PNFGLTEXPARAMETERFVPROC, glTexParameterfv);
qglExtern(PNFGLDELETETEXTURESPROC, glDeleteTextures);
qglExtern(PNFGLVERTEX3FVPROC, glVertex3fv);
qglExtern(PNFGLLINEWIDTHPROC, glLineWidth);
qglExtern(PNFGLVERTEX3FPROC, glVertex3f);
qglExtern(PNFGLCALLLISTPROC, glCallList);
qglExtern(PNFGLSTENCILMASKPROC, glStencilMask);
qglExtern(PNFGLCLEARSTENCILPROC, glClearStencil);
qglExtern(PNFGLSTENCILFUNCPROC, glStencilFunc);
qglExtern(PNFGLSTENCILOPPROC, glStencilOp);
qglExtern(PNFGLGETERRORPROC, glGetError);
qglExtern(PNFGLPUSHMATRIXPROC, glPushMatrix);
qglExtern(PNFGLPOPMATRIXPROC, glPopMatrix);
qglExtern(PNFGLTEXPARAMETERIPROC, glTexParameteri);
qglExtern(PNFGLGETINTEGERVPROC, glGetIntegerv);
qglExtern(PNFGLCLEARDEPTHPROC, glClearDepth);
qglExtern(PNFGLCOLOR4FPROC, glColor4f);
qglExtern(PNFGLSHADEMODELPROC, glShadeModel);
qglExtern(PNFGLENABLECLIENTSTATEPROC, glEnableClientState);
qglExtern(PNFGLCOLOR4FVPROC, glColor4fv);
qglExtern(PNFGLTEXCOORD2FVPROC, glTexCoord2fv);
qglExtern(PNFGLDRAWELEMENTSPROC, glDrawElements);
qglExtern(PNFGLDISABLECLIENTSTATEPROC, glDisableClientState);
qglExtern(PNFGLVERTEXPOINTERPROC, glVertexPointer);
qglExtern(PNFGLTEXCOORDPOINTERPROC, glTexCoordPointer);
qglExtern(PNFGLCOLORPOINTERPROC, glColorPointer);
qglExtern(PNFGLPOLYGONOFFSETPROC, glPolygonOffset);
qglExtern(PNFGLNORMALPOINTERPROC, glNormalPointer);
qglExtern(PNFGLTRANSLATEFPROC, glTranslatef);
qglExtern(PNFGLCOLORMASKPROC, glColorMask);
qglExtern(PNFGLGETSTRINGPROC, glGetString);

// GL_VERSION_1_2
extern qboolean GL_VERSION_1_2_supported;
qglExtern(PFNGLBLENDCOLORPROC, qglBlendColor);
qglExtern(PFNGLBLENDEQUATIONPROC, qglBlendEquation);
qglExtern(PFNGLDRAWRANGEELEMENTSPROC, qglDrawRangeElements);
qglExtern(PFNGLCOLORTABLEPROC, qglColorTable);
qglExtern(PFNGLCOLORTABLEPARAMETERFVPROC, qglColorTableParameterfv);
qglExtern(PFNGLCOLORTABLEPARAMETERIVPROC, qglColorTableParameteriv);
qglExtern(PFNGLCOPYCOLORTABLEPROC, qglCopyColorTable);
qglExtern(PFNGLGETCOLORTABLEPROC, qglGetColorTable);
qglExtern(PFNGLGETCOLORTABLEPARAMETERFVPROC, qglGetColorTableParameterfv);
qglExtern(PFNGLGETCOLORTABLEPARAMETERIVPROC, qglGetColorTableParameteriv);
qglExtern(PFNGLCOLORSUBTABLEPROC, qglColorSubTable);
qglExtern(PFNGLCOPYCOLORSUBTABLEPROC, qglCopyColorSubTable);
qglExtern(PFNGLCONVOLUTIONFILTER1DPROC, qglConvolutionFilter1D);
qglExtern(PFNGLCONVOLUTIONFILTER2DPROC, qglConvolutionFilter2D);
qglExtern(PFNGLCONVOLUTIONPARAMETERFPROC, qglConvolutionParameterf);
qglExtern(PFNGLCONVOLUTIONPARAMETERFVPROC, qglConvolutionParameterfv);
qglExtern(PFNGLCONVOLUTIONPARAMETERIPROC, qglConvolutionParameteri);
qglExtern(PFNGLCONVOLUTIONPARAMETERIVPROC, qglConvolutionParameteriv);
qglExtern(PFNGLCOPYCONVOLUTIONFILTER1DPROC, qglCopyConvolutionFilter1D);
qglExtern(PFNGLCOPYCONVOLUTIONFILTER2DPROC, qglCopyConvolutionFilter2D);
qglExtern(PFNGLGETCONVOLUTIONFILTERPROC, qglGetConvolutionFilter);
qglExtern(PFNGLGETCONVOLUTIONPARAMETERFVPROC, qglGetConvolutionParameterfv);
qglExtern(PFNGLGETCONVOLUTIONPARAMETERIVPROC, qglGetConvolutionParameteriv);
qglExtern(PFNGLGETSEPARABLEFILTERPROC, qglGetSeparableFilter);
qglExtern(PFNGLSEPARABLEFILTER2DPROC, qglSeparableFilter2D);
qglExtern(PFNGLGETHISTOGRAMPROC, qglGetHistogram);
qglExtern(PFNGLGETHISTOGRAMPARAMETERFVPROC, qglGetHistogramParameterfv);
qglExtern(PFNGLGETHISTOGRAMPARAMETERIVPROC, qglGetHistogramParameteriv);
qglExtern(PFNGLGETMINMAXPROC, qglGetMinmax);
qglExtern(PFNGLGETMINMAXPARAMETERFVPROC, qglGetMinmaxParameterfv);
qglExtern(PFNGLGETMINMAXPARAMETERIVPROC, qglGetMinmaxParameteriv);
qglExtern(PFNGLHISTOGRAMPROC, qglHistogram);
qglExtern(PFNGLMINMAXPROC, qglMinmax);
qglExtern(PFNGLRESETHISTOGRAMPROC, qglResetHistogram);
qglExtern(PFNGLRESETMINMAXPROC, qglResetMinmax);
qglExtern(PFNGLTEXIMAGE3DPROC, qglTexImage3D);
qglExtern(PFNGLTEXSUBIMAGE3DPROC, qglTexSubImage3D);
qglExtern(PFNGLCOPYTEXSUBIMAGE3DPROC, qglCopyTexSubImage3D);

// GL_VERSION_1_3
extern qboolean GL_VERSION_1_3_supported;
qglExtern(PFNGLACTIVETEXTUREPROC, glActiveTexture);
qglExtern(PFNGLCLIENTACTIVETEXTUREPROC, glClientActiveTexture);
qglExtern(PFNGLMULTITEXCOORD1DPROC, glMultiTexCoord1d);
qglExtern(PFNGLMULTITEXCOORD1DVPROC, glMultiTexCoord1dv);
qglExtern(PFNGLMULTITEXCOORD1FPROC, glMultiTexCoord1f);
qglExtern(PFNGLMULTITEXCOORD1FVPROC, glMultiTexCoord1fv);
qglExtern(PFNGLMULTITEXCOORD1IPROC, glMultiTexCoord1i);
qglExtern(PFNGLMULTITEXCOORD1IVPROC, glMultiTexCoord1iv);
qglExtern(PFNGLMULTITEXCOORD1SPROC, glMultiTexCoord1s);
qglExtern(PFNGLMULTITEXCOORD1SVPROC, glMultiTexCoord1sv);
qglExtern(PFNGLMULTITEXCOORD2DPROC, glMultiTexCoord2d);
qglExtern(PFNGLMULTITEXCOORD2DVPROC, glMultiTexCoord2dv);
qglExtern(PFNGLMULTITEXCOORD2FPROC, glMultiTexCoord2f);
qglExtern(PFNGLMULTITEXCOORD2FVPROC, glMultiTexCoord2fv);
qglExtern(PFNGLMULTITEXCOORD2IPROC, glMultiTexCoord2i);
qglExtern(PFNGLMULTITEXCOORD2IVPROC, glMultiTexCoord2iv);
qglExtern(PFNGLMULTITEXCOORD2SPROC, glMultiTexCoord2s);
qglExtern(PFNGLMULTITEXCOORD2SVPROC, glMultiTexCoord2sv);
qglExtern(PFNGLMULTITEXCOORD3DPROC, glMultiTexCoord3d);
qglExtern(PFNGLMULTITEXCOORD3DVPROC, glMultiTexCoord3dv);
qglExtern(PFNGLMULTITEXCOORD3FPROC, glMultiTexCoord3f);
qglExtern(PFNGLMULTITEXCOORD3FVPROC, glMultiTexCoord3fv);
qglExtern(PFNGLMULTITEXCOORD3IPROC, glMultiTexCoord3i);
qglExtern(PFNGLMULTITEXCOORD3IVPROC, glMultiTexCoord3iv);
qglExtern(PFNGLMULTITEXCOORD3SPROC, glMultiTexCoord3s);
qglExtern(PFNGLMULTITEXCOORD3SVPROC, glMultiTexCoord3sv);
qglExtern(PFNGLMULTITEXCOORD4DPROC, glMultiTexCoord4d);
qglExtern(PFNGLMULTITEXCOORD4DVPROC, glMultiTexCoord4dv);
qglExtern(PFNGLMULTITEXCOORD4FPROC, glMultiTexCoord4f);
qglExtern(PFNGLMULTITEXCOORD4FVPROC, glMultiTexCoord4fv);
qglExtern(PFNGLMULTITEXCOORD4IPROC, glMultiTexCoord4i);
qglExtern(PFNGLMULTITEXCOORD4IVPROC, glMultiTexCoord4iv);
qglExtern(PFNGLMULTITEXCOORD4SPROC, glMultiTexCoord4s);
qglExtern(PFNGLMULTITEXCOORD4SVPROC, glMultiTexCoord4sv);
qglExtern(PFNGLLOADTRANSPOSEMATRIXFPROC, glLoadTransposeMatrixf);
qglExtern(PFNGLLOADTRANSPOSEMATRIXDPROC, glLoadTransposeMatrixd);
qglExtern(PFNGLMULTTRANSPOSEMATRIXFPROC, glMultTransposeMatrixf);
qglExtern(PFNGLMULTTRANSPOSEMATRIXDPROC, glMultTransposeMatrixd);
qglExtern(PFNGLSAMPLECOVERAGEPROC, glSampleCoverage);
qglExtern(PFNGLCOMPRESSEDTEXIMAGE3DPROC, glCompressedTexImage3D);
qglExtern(PFNGLCOMPRESSEDTEXIMAGE2DPROC, glCompressedTexImage2D);
qglExtern(PFNGLCOMPRESSEDTEXIMAGE1DPROC, glCompressedTexImage1D);
qglExtern(PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC, glCompressedTexSubImage3D);
qglExtern(PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC, glCompressedTexSubImage2D);
qglExtern(PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC, glCompressedTexSubImage1D);
qglExtern(PFNGLGETCOMPRESSEDTEXIMAGEPROC, glGetCompressedTexImage);

// GL_VERSION_1_4
extern qboolean GL_VERSION_1_4_supported;
qglExtern(PFNGLBLENDFUNCSEPARATEPROC, glBlendFuncSeparate);
qglExtern(PFNGLFOGCOORDFPROC, glFogCoordf);
qglExtern(PFNGLFOGCOORDFVPROC, glFogCoordfv);
qglExtern(PFNGLFOGCOORDDPROC, glFogCoordd);
qglExtern(PFNGLFOGCOORDDVPROC, glFogCoorddv);
qglExtern(PFNGLFOGCOORDPOINTERPROC, glFogCoordPointer);
qglExtern(PFNGLMULTIDRAWARRAYSPROC, glMultiDrawArrays);
qglExtern(PFNGLMULTIDRAWELEMENTSPROC, glMultiDrawElements);
qglExtern(PFNGLPOINTPARAMETERFPROC, glPointParameterf);
qglExtern(PFNGLPOINTPARAMETERFVPROC, glPointParameterfv);
qglExtern(PFNGLPOINTPARAMETERIPROC, glPointParameteri);
qglExtern(PFNGLPOINTPARAMETERIVPROC, glPointParameteriv);
qglExtern(PFNGLSECONDARYCOLOR3BPROC, glSecondaryColor3b);
qglExtern(PFNGLSECONDARYCOLOR3BVPROC, glSecondaryColor3bv);
qglExtern(PFNGLSECONDARYCOLOR3DPROC, glSecondaryColor3d);
qglExtern(PFNGLSECONDARYCOLOR3DVPROC, glSecondaryColor3dv);
qglExtern(PFNGLSECONDARYCOLOR3FPROC, glSecondaryColor3f);
qglExtern(PFNGLSECONDARYCOLOR3FVPROC, glSecondaryColor3fv);
qglExtern(PFNGLSECONDARYCOLOR3IPROC, glSecondaryColor3i);
qglExtern(PFNGLSECONDARYCOLOR3IVPROC, glSecondaryColor3iv);
qglExtern(PFNGLSECONDARYCOLOR3SPROC, glSecondaryColor3s);
qglExtern(PFNGLSECONDARYCOLOR3SVPROC, glSecondaryColor3sv);
qglExtern(PFNGLSECONDARYCOLOR3UBPROC, glSecondaryColor3ub);
qglExtern(PFNGLSECONDARYCOLOR3UBVPROC, glSecondaryColor3ubv);
qglExtern(PFNGLSECONDARYCOLOR3UIPROC, glSecondaryColor3ui);
qglExtern(PFNGLSECONDARYCOLOR3UIVPROC, glSecondaryColor3uiv);
qglExtern(PFNGLSECONDARYCOLOR3USPROC, glSecondaryColor3us);
qglExtern(PFNGLSECONDARYCOLOR3USVPROC, glSecondaryColor3usv);
qglExtern(PFNGLSECONDARYCOLORPOINTERPROC, glSecondaryColorPointer);
qglExtern(PFNGLWINDOWPOS2DPROC, glWindowPos2d);
qglExtern(PFNGLWINDOWPOS2DVPROC, glWindowPos2dv);
qglExtern(PFNGLWINDOWPOS2FPROC, glWindowPos2f);
qglExtern(PFNGLWINDOWPOS2FVPROC, glWindowPos2fv);
qglExtern(PFNGLWINDOWPOS2IPROC, glWindowPos2i);
qglExtern(PFNGLWINDOWPOS2IVPROC, glWindowPos2iv);
qglExtern(PFNGLWINDOWPOS2SPROC, glWindowPos2s);
qglExtern(PFNGLWINDOWPOS2SVPROC, glWindowPos2sv);
qglExtern(PFNGLWINDOWPOS3DPROC, glWindowPos3d);
qglExtern(PFNGLWINDOWPOS3DVPROC, glWindowPos3dv);
qglExtern(PFNGLWINDOWPOS3FPROC, glWindowPos3f);
qglExtern(PFNGLWINDOWPOS3FVPROC, glWindowPos3fv);
qglExtern(PFNGLWINDOWPOS3IPROC, glWindowPos3i);
qglExtern(PFNGLWINDOWPOS3IVPROC, glWindowPos3iv);
qglExtern(PFNGLWINDOWPOS3SPROC, glWindowPos3s);
qglExtern(PFNGLWINDOWPOS3SVPROC, glWindowPos3sv);

// GL_VERSION_1_5
extern qboolean GL_VERSION_1_5_supported;
qglExtern(PFNGLGENQUERIESPROC, glGenQueries);
qglExtern(PFNGLDELETEQUERIESPROC, glDeleteQueries);
qglExtern(PFNGLISQUERYPROC, glIsQuery);
qglExtern(PFNGLBEGINQUERYPROC, glBeginQuery);
qglExtern(PFNGLENDQUERYPROC, glEndQuery);
qglExtern(PFNGLGETQUERYIVPROC, glGetQueryiv);
qglExtern(PFNGLGETQUERYOBJECTIVPROC, glGetQueryObjectiv);
qglExtern(PFNGLGETQUERYOBJECTUIVPROC, glGetQueryObjectuiv);
qglExtern(PFNGLBINDBUFFERPROC, glBindBuffer);
qglExtern(PFNGLDELETEBUFFERSPROC, glDeleteBuffers);
qglExtern(PFNGLGENBUFFERSPROC, glGenBuffers);
qglExtern(PFNGLISBUFFERPROC, glIsBuffer);
qglExtern(PFNGLBUFFERDATAPROC, glBufferData);
qglExtern(PFNGLBUFFERSUBDATAPROC, glBufferSubData);
qglExtern(PFNGLGETBUFFERSUBDATAPROC, glGetBufferSubData);
qglExtern(PFNGLMAPBUFFERPROC, glMapBuffer);
qglExtern(PFNGLUNMAPBUFFERPROC, glUnmapBuffer);
qglExtern(PFNGLGETBUFFERPARAMETERIVPROC, glGetBufferParameteriv);
qglExtern(PFNGLGETBUFFERPOINTERVPROC, glGetBufferPointerv);

// GL_VERSION_2_0
extern qboolean GL_VERSION_2_0_supported;
qglExtern(PFNGLBLENDEQUATIONSEPARATEPROC, glBlendEquationSeparate);
qglExtern(PFNGLDRAWBUFFERSPROC, glDrawBuffers);
qglExtern(PFNGLSTENCILOPSEPARATEPROC, glStencilOpSeparate);
qglExtern(PFNGLSTENCILFUNCSEPARATEPROC, glStencilFuncSeparate);
qglExtern(PFNGLSTENCILMASKSEPARATEPROC, glStencilMaskSeparate);
qglExtern(PFNGLATTACHSHADERPROC, glAttachShader);
qglExtern(PFNGLBINDATTRIBLOCATIONPROC, glBindAttribLocation);
qglExtern(PFNGLCOMPILESHADERPROC, glCompileShader);
qglExtern(PFNGLCREATEPROGRAMPROC, glCreateProgram);
qglExtern(PFNGLCREATESHADERPROC, glCreateShader);
qglExtern(PFNGLDELETEPROGRAMPROC, glDeleteProgram);
qglExtern(PFNGLDELETESHADERPROC, glDeleteShader);
qglExtern(PFNGLDETACHSHADERPROC, glDetachShader);
qglExtern(PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray);
qglExtern(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray);
qglExtern(PFNGLGETACTIVEATTRIBPROC, glGetActiveAttrib);
qglExtern(PFNGLGETACTIVEUNIFORMPROC, glGetActiveUniform);
qglExtern(PFNGLGETATTACHEDSHADERSPROC, glGetAttachedShaders);
qglExtern(PFNGLGETATTRIBLOCATIONPROC, glGetAttribLocation);
qglExtern(PFNGLGETPROGRAMIVPROC, glGetProgramiv);
qglExtern(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog);
qglExtern(PFNGLGETSHADERIVPROC, glGetShaderiv);
qglExtern(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog);
qglExtern(PFNGLGETSHADERSOURCEPROC, glGetShaderSource);
qglExtern(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation);
qglExtern(PFNGLGETUNIFORMFVPROC, glGetUniformfv);
qglExtern(PFNGLGETUNIFORMIVPROC, glGetUniformiv);
qglExtern(PFNGLGETVERTEXATTRIBDVPROC, glGetVertexAttribdv);
qglExtern(PFNGLGETVERTEXATTRIBFVPROC, glGetVertexAttribfv);
qglExtern(PFNGLGETVERTEXATTRIBIVPROC, glGetVertexAttribiv);
qglExtern(PFNGLGETVERTEXATTRIBPOINTERVPROC, glGetVertexAttribPointerv);
qglExtern(PFNGLISPROGRAMPROC, glIProgram);
qglExtern(PFNGLISSHADERPROC, glIShader);
qglExtern(PFNGLLINKPROGRAMPROC, glLinkProgram);
qglExtern(PFNGLSHADERSOURCEPROC, glShaderSource);
qglExtern(PFNGLUSEPROGRAMPROC, glUseProgram);
qglExtern(PFNGLUNIFORM1FPROC, glUniform1f);
qglExtern(PFNGLUNIFORM2FPROC, glUniform2f);
qglExtern(PFNGLUNIFORM3FPROC, glUniform3f);
qglExtern(PFNGLUNIFORM4FPROC, glUniform4f);
qglExtern(PFNGLUNIFORM1IPROC, glUniform1i);
qglExtern(PFNGLUNIFORM2IPROC, glUniform2i);
qglExtern(PFNGLUNIFORM3IPROC, glUniform3i);
qglExtern(PFNGLUNIFORM4IPROC, glUniform4i);
qglExtern(PFNGLUNIFORM1FVPROC, glUniform1fv);
qglExtern(PFNGLUNIFORM2FVPROC, glUniform2fv);
qglExtern(PFNGLUNIFORM3FVPROC, glUniform3fv);
qglExtern(PFNGLUNIFORM4FVPROC, glUniform4fv);
qglExtern(PFNGLUNIFORM1IVPROC, glUniform1iv);
qglExtern(PFNGLUNIFORM2IVPROC, glUniform2iv);
qglExtern(PFNGLUNIFORM3IVPROC, glUniform3iv);
qglExtern(PFNGLUNIFORM4IVPROC, glUniform4iv);
qglExtern(PFNGLUNIFORMMATRIX2FVPROC, glUniformMatrix2fv);
qglExtern(PFNGLUNIFORMMATRIX3FVPROC, glUniformMatrix3fv);
qglExtern(PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix4fv);
qglExtern(PFNGLVALIDATEPROGRAMPROC, glValidateProgram);
qglExtern(PFNGLVERTEXATTRIB1DPROC, glVertexAttrib1d);
qglExtern(PFNGLVERTEXATTRIB1DVPROC, glVertexAttrib1dv);
qglExtern(PFNGLVERTEXATTRIB1FPROC, glVertexAttrib1f);
qglExtern(PFNGLVERTEXATTRIB1FVPROC, glVertexAttrib1fv);
qglExtern(PFNGLVERTEXATTRIB1SPROC, glVertexAttrib1s);
qglExtern(PFNGLVERTEXATTRIB1SVPROC, glVertexAttrib1sv);
qglExtern(PFNGLVERTEXATTRIB2DPROC, glVertexAttrib2d);
qglExtern(PFNGLVERTEXATTRIB2DVPROC, glVertexAttrib2dv);
qglExtern(PFNGLVERTEXATTRIB2FPROC, glVertexAttrib2f);
qglExtern(PFNGLVERTEXATTRIB2FVPROC, glVertexAttrib2fv);
qglExtern(PFNGLVERTEXATTRIB2SPROC, glVertexAttrib2s);
qglExtern(PFNGLVERTEXATTRIB2SVPROC, glVertexAttrib2sv);
qglExtern(PFNGLVERTEXATTRIB3DPROC, glVertexAttrib3d);
qglExtern(PFNGLVERTEXATTRIB3DVPROC, glVertexAttrib3dv);
qglExtern(PFNGLVERTEXATTRIB3FPROC, glVertexAttrib3f);
qglExtern(PFNGLVERTEXATTRIB3FVPROC, glVertexAttrib3fv);
qglExtern(PFNGLVERTEXATTRIB3SPROC, glVertexAttrib3s);
qglExtern(PFNGLVERTEXATTRIB3SVPROC, glVertexAttrib3sv);
qglExtern(PFNGLVERTEXATTRIB4NBVPROC, glVertexAttrib4Nbv);
qglExtern(PFNGLVERTEXATTRIB4NIVPROC, glVertexAttrib4Niv);
qglExtern(PFNGLVERTEXATTRIB4NSVPROC, glVertexAttrib4Nsv);
qglExtern(PFNGLVERTEXATTRIB4NUBPROC, glVertexAttrib4Nub);
qglExtern(PFNGLVERTEXATTRIB4NUBVPROC, glVertexAttrib4Nubv);
qglExtern(PFNGLVERTEXATTRIB4NUIVPROC, glVertexAttrib4Nuiv);
qglExtern(PFNGLVERTEXATTRIB4NUSVPROC, glVertexAttrib4Nusv);
qglExtern(PFNGLVERTEXATTRIB4BVPROC, glVertexAttrib4bv);
qglExtern(PFNGLVERTEXATTRIB4DPROC, glVertexAttrib4d);
qglExtern(PFNGLVERTEXATTRIB4DVPROC, glVertexAttrib4dv);
qglExtern(PFNGLVERTEXATTRIB4FPROC, glVertexAttrib4f);
qglExtern(PFNGLVERTEXATTRIB4FVPROC, glVertexAttrib4fv);
qglExtern(PFNGLVERTEXATTRIB4IVPROC, glVertexAttrib4iv);
qglExtern(PFNGLVERTEXATTRIB4SPROC, glVertexAttrib4s);
qglExtern(PFNGLVERTEXATTRIB4SVPROC, glVertexAttrib4sv);
qglExtern(PFNGLVERTEXATTRIB4UBVPROC, glVertexAttrib4ubv);
qglExtern(PFNGLVERTEXATTRIB4UIVPROC, glVertexAttrib4uiv);
qglExtern(PFNGLVERTEXATTRIB4USVPROC, glVertexAttrib4usv);
qglExtern(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer);

// GL_multitexture
extern qboolean GL_multitexture;

// GL_S3_s3tc
extern qboolean GL_S3_s3tc_supported;

// GL_EXT_texture_env_add
extern qboolean GL_EXT_texture_env_add_supported;

// GL_EXT_compiled_vertex_array
extern qboolean GL_EXT_compiled_vertex_array_supported;
qglExtern(PFNGLLOCKARRAYSEXTPROC, glLockArraysEXT);
qglExtern(PFNGLUNLOCKARRAYSEXTPROC, glUnlockArraysEXT);

// GL_EXT_framebuffer_object
extern qboolean GL_EXT_framebuffer_object_supported;
qglExtern(PFNGLISRENDERBUFFEREXTPROC, glIsRenderbufferEXT);
qglExtern(PFNGLBINDRENDERBUFFEREXTPROC, glBindRenderbufferEXT);
qglExtern(PFNGLDELETERENDERBUFFERSEXTPROC, glDeleteRenderbuffersEXT);
qglExtern(PFNGLGENRENDERBUFFERSEXTPROC, glGenRenderbuffersEXT);
qglExtern(PFNGLRENDERBUFFERSTORAGEEXTPROC, glRenderbufferStorageEXT);
qglExtern(PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC, glGetRenderbufferParameterivEXT);
qglExtern(PFNGLISFRAMEBUFFEREXTPROC, glIsFramebufferEXT);
qglExtern(PFNGLBINDFRAMEBUFFEREXTPROC, glBindFramebufferEXT);
qglExtern(PFNGLDELETEFRAMEBUFFERSEXTPROC, glDeleteFramebuffersEXT);
qglExtern(PFNGLGENFRAMEBUFFERSEXTPROC, glGenFramebuffersEXT);
qglExtern(PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC, glCheckFramebufferStatusEXT);
qglExtern(PFNGLFRAMEBUFFERTEXTURE1DEXTPROC, glFramebufferTexture1DEXT);
qglExtern(PFNGLFRAMEBUFFERTEXTURE2DEXTPROC, glFramebufferTexture2DEXT);
qglExtern(PFNGLFRAMEBUFFERTEXTURE3DEXTPROC, glFramebufferTexture3DEXT);
qglExtern(PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC, glFramebufferRenderbufferEXT);
qglExtern(PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC, glGetFramebufferAttachmentParameterivEXT);
qglExtern(PFNGLGENERATEMIPMAPEXTPROC, glGenerateMipmapEXT);

void R_InitExtenstions(void);
#endif
