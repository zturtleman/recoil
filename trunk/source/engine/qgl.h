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

#if defined( __LINT__ )
#include <GL/gl.h>
#include "glext.h"
#elif defined( _WIN32 )
#pragma warning (disable: 4201)
#pragma warning (disable: 4214)
#pragma warning (disable: 4514)
#pragma warning (disable: 4032)
#pragma warning (disable: 4201)
#pragma warning (disable: 4214)
#include <windows.h>
#include <gl/gl.h>

#include "glext.h"
#include "wglext.h"
#elif defined(MACOS_X)
//	#include "macosx_glimp.h"
#elif defined( __linux__ )
#include <GL/gl.h>
//	#include <GL/glx.h>
// bk001129 - from cvs1.17 (mkv)
#if defined(__FX__)
//	#include <GL/fxmesa.h>
#endif
#elif defined( __FreeBSD__ ) // rb010123
#include <GL/gl.h>
//	#include <GL/glx.h>
#if defined(__FX__)
//		#include <GL/fxmesa.h>
#endif
#else
#include <gl.h>
#endif

#ifndef APIENTRY
#define APIENTRY
#endif
#ifndef WINAPI
#define WINAPI
#endif

//===========================================================================

/*
** multitexture extension definitions
*/

// NOTE: some Linux platforms would need those prototypes
#if defined(MACOS_X)
typedef void (APIENTRY * PFNGLMULTITEXCOORD1DARBPROC) (GLenum target, GLdouble s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1DVARBPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1FARBPROC) (GLenum target, GLfloat s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1FVARBPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1IARBPROC) (GLenum target, GLint s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1IVARBPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1SARBPROC) (GLenum target, GLshort s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1SVARBPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2DARBPROC) (GLenum target, GLdouble s, GLdouble t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2DVARBPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2FARBPROC) (GLenum target, GLfloat s, GLfloat t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2FVARBPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2IARBPROC) (GLenum target, GLint s, GLint t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2IVARBPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2SARBPROC) (GLenum target, GLshort s, GLshort t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2SVARBPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3DARBPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3DVARBPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3FARBPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3FVARBPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3IARBPROC) (GLenum target, GLint s, GLint t, GLint r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3IVARBPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3SARBPROC) (GLenum target, GLshort s, GLshort t, GLshort r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3SVARBPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4DARBPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4DVARBPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4FARBPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4FVARBPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4IARBPROC) (GLenum target, GLint s, GLint t, GLint r, GLint q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4IVARBPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4SARBPROC) (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4SVARBPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLACTIVETEXTUREARBPROC) (GLenum target);
typedef void (APIENTRY * PFNGLCLIENTACTIVETEXTUREARBPROC) (GLenum target);
#endif

// TTimo - VC7 / XP ?
#ifdef WIN32
typedef void (APIENTRY * PFNGLMULTITEXCOORD2FARBPROC) (GLenum target, GLfloat s, GLfloat t);
typedef void (APIENTRY * PFNGLACTIVETEXTUREARBPROC) (GLenum target);
typedef void (APIENTRY * PFNGLCLIENTACTIVETEXTUREARBPROC) (GLenum target);
#endif

//===========================================================================

// non-windows systems will just redefine qgl* to gl*
#if !defined( _WIN32 ) && !defined(MACOS_X) && !defined( __linux__ ) && !defined( __FreeBSD__ ) // rb010123
#include "qgl_linked.h"
#elif defined(MACOS_X)
// This includes #ifdefs for optional logging and GL error checking after every GL call as well as #defines to prevent incorrect usage of the non-'qgl' versions of the GL API.
//	#include "macosx_qgl.h"
#else
// windows systems use a function pointer for each call so we can load minidrivers
extern  void ( APIENTRY * qglAccum )(GLenum op, GLfloat value);
extern  void ( APIENTRY * qglAlphaFunc )(GLenum func, GLclampf ref);
extern  GLboolean ( APIENTRY * qglAreTexturesResident )(GLsizei n, const GLuint *textures, GLboolean *residences);
extern  void ( APIENTRY * qglArrayElement )(GLint i);
extern  void ( APIENTRY * qglBegin )(GLenum mode);
extern  void ( APIENTRY * qglBindTexture )(GLenum target, GLuint texture);
extern  void ( APIENTRY * qglBitmap )(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte *bitmap);
extern  void ( APIENTRY * qglBlendFunc )(GLenum sfactor, GLenum dfactor);
extern  void ( APIENTRY * qglCallList )(GLuint list);
extern  void ( APIENTRY * qglCallLists )(GLsizei n, GLenum type, const GLvoid *lists);
extern  void ( APIENTRY * qglClear )(GLbitfield mask);
extern  void ( APIENTRY * qglClearAccum )(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
extern  void ( APIENTRY * qglClearColor )(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
extern  void ( APIENTRY * qglClearDepth )(GLclampd depth);
extern  void ( APIENTRY * qglClearIndex )(GLfloat c);
extern  void ( APIENTRY * qglClearStencil )(GLint s);
extern  void ( APIENTRY * qglClipPlane )(GLenum plane, const GLdouble *equation);
extern  void ( APIENTRY * qglColor3b )(GLbyte red, GLbyte green, GLbyte blue);
extern  void ( APIENTRY * qglColor3bv )(const GLbyte *v);
extern  void ( APIENTRY * qglColor3d )(GLdouble red, GLdouble green, GLdouble blue);
extern  void ( APIENTRY * qglColor3dv )(const GLdouble *v);
extern  void ( APIENTRY * qglColor3f )(GLfloat red, GLfloat green, GLfloat blue);
extern  void ( APIENTRY * qglColor3fv )(const GLfloat *v);
extern  void ( APIENTRY * qglColor3i )(GLint red, GLint green, GLint blue);
extern  void ( APIENTRY * qglColor3iv )(const GLint *v);
extern  void ( APIENTRY * qglColor3s )(GLshort red, GLshort green, GLshort blue);
extern  void ( APIENTRY * qglColor3sv )(const GLshort *v);
extern  void ( APIENTRY * qglColor3ub )(GLubyte red, GLubyte green, GLubyte blue);
extern  void ( APIENTRY * qglColor3ubv )(const GLubyte *v);
extern  void ( APIENTRY * qglColor3ui )(GLuint red, GLuint green, GLuint blue);
extern  void ( APIENTRY * qglColor3uiv )(const GLuint *v);
extern  void ( APIENTRY * qglColor3us )(GLushort red, GLushort green, GLushort blue);
extern  void ( APIENTRY * qglColor3usv )(const GLushort *v);
extern  void ( APIENTRY * qglColor4b )(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);
extern  void ( APIENTRY * qglColor4bv )(const GLbyte *v);
extern  void ( APIENTRY * qglColor4d )(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
extern  void ( APIENTRY * qglColor4dv )(const GLdouble *v);
extern  void ( APIENTRY * qglColor4f )(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
extern  void ( APIENTRY * qglColor4fv )(const GLfloat *v);
extern  void ( APIENTRY * qglColor4i )(GLint red, GLint green, GLint blue, GLint alpha);
extern  void ( APIENTRY * qglColor4iv )(const GLint *v);
extern  void ( APIENTRY * qglColor4s )(GLshort red, GLshort green, GLshort blue, GLshort alpha);
extern  void ( APIENTRY * qglColor4sv )(const GLshort *v);
extern  void ( APIENTRY * qglColor4ub )(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
extern  void ( APIENTRY * qglColor4ubv )(const GLubyte *v);
extern  void ( APIENTRY * qglColor4ui )(GLuint red, GLuint green, GLuint blue, GLuint alpha);
extern  void ( APIENTRY * qglColor4uiv )(const GLuint *v);
extern  void ( APIENTRY * qglColor4us )(GLushort red, GLushort green, GLushort blue, GLushort alpha);
extern  void ( APIENTRY * qglColor4usv )(const GLushort *v);
extern  void ( APIENTRY * qglColorMask )(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
extern  void ( APIENTRY * qglColorMaterial )(GLenum face, GLenum mode);
extern  void ( APIENTRY * qglColorPointer )(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
extern  void ( APIENTRY * qglCopyPixels )(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
extern  void ( APIENTRY * qglCopyTexImage1D )(GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLint border);
extern  void ( APIENTRY * qglCopyTexImage2D )(GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
extern  void ( APIENTRY * qglCopyTexSubImage1D )(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
extern  void ( APIENTRY * qglCopyTexSubImage2D )(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
extern  void ( APIENTRY * qglCullFace )(GLenum mode);
extern  void ( APIENTRY * qglDeleteLists )(GLuint list, GLsizei range);
extern  void ( APIENTRY * qglDeleteTextures )(GLsizei n, const GLuint *textures);
extern  void ( APIENTRY * qglDepthFunc )(GLenum func);
extern  void ( APIENTRY * qglDepthMask )(GLboolean flag);
extern  void ( APIENTRY * qglDepthRange )(GLclampd zNear, GLclampd zFar);
extern  void ( APIENTRY * qglDisable )(GLenum cap);
extern  void ( APIENTRY * qglDisableClientState )(GLenum array);
extern  void ( APIENTRY * qglDrawArrays )(GLenum mode, GLint first, GLsizei count);
extern  void ( APIENTRY * qglDrawBuffer )(GLenum mode);
extern  void ( APIENTRY * qglDrawElements )(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);
extern  void ( APIENTRY * qglDrawPixels )(GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
extern  void ( APIENTRY * qglEdgeFlag )(GLboolean flag);
extern  void ( APIENTRY * qglEdgeFlagPointer )(GLsizei stride, const GLvoid *pointer);
extern  void ( APIENTRY * qglEdgeFlagv )(const GLboolean *flag);
extern  void ( APIENTRY * qglEnable )(GLenum cap);
extern  void ( APIENTRY * qglEnableClientState )(GLenum array);
extern  void ( APIENTRY * qglEnd )(void);
extern  void ( APIENTRY * qglEndList )(void);
extern  void ( APIENTRY * qglEvalCoord1d )(GLdouble u);
extern  void ( APIENTRY * qglEvalCoord1dv )(const GLdouble *u);
extern  void ( APIENTRY * qglEvalCoord1f )(GLfloat u);
extern  void ( APIENTRY * qglEvalCoord1fv )(const GLfloat *u);
extern  void ( APIENTRY * qglEvalCoord2d )(GLdouble u, GLdouble v);
extern  void ( APIENTRY * qglEvalCoord2dv )(const GLdouble *u);
extern  void ( APIENTRY * qglEvalCoord2f )(GLfloat u, GLfloat v);
extern  void ( APIENTRY * qglEvalCoord2fv )(const GLfloat *u);
extern  void ( APIENTRY * qglEvalMesh1 )(GLenum mode, GLint i1, GLint i2);
extern  void ( APIENTRY * qglEvalMesh2 )(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
extern  void ( APIENTRY * qglEvalPoint1 )(GLint i);
extern  void ( APIENTRY * qglEvalPoint2 )(GLint i, GLint j);
extern  void ( APIENTRY * qglFeedbackBuffer )(GLsizei size, GLenum type, GLfloat *buffer);
extern  void ( APIENTRY * qglFinish )(void);
extern  void ( APIENTRY * qglFlush )(void);
extern  void ( APIENTRY * qglFogf )(GLenum pname, GLfloat param);
extern  void ( APIENTRY * qglFogfv )(GLenum pname, const GLfloat *params);
extern  void ( APIENTRY * qglFogi )(GLenum pname, GLint param);
extern  void ( APIENTRY * qglFogiv )(GLenum pname, const GLint *params);
extern  void ( APIENTRY * qglFrontFace )(GLenum mode);
extern  void ( APIENTRY * qglFrustum )(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
extern  GLuint ( APIENTRY * qglGenLists )(GLsizei range);
extern  void ( APIENTRY * qglGenTextures )(GLsizei n, GLuint *textures);
extern  void ( APIENTRY * qglGetBooleanv )(GLenum pname, GLboolean *params);
extern  void ( APIENTRY * qglGetClipPlane )(GLenum plane, GLdouble *equation);
extern  void ( APIENTRY * qglGetDoublev )(GLenum pname, GLdouble *params);
extern  GLenum ( APIENTRY * qglGetError )(void);
extern  void ( APIENTRY * qglGetFloatv )(GLenum pname, GLfloat *params);
extern  void ( APIENTRY * qglGetIntegerv )(GLenum pname, GLint *params);
extern  void ( APIENTRY * qglGetLightfv )(GLenum light, GLenum pname, GLfloat *params);
extern  void ( APIENTRY * qglGetLightiv )(GLenum light, GLenum pname, GLint *params);
extern  void ( APIENTRY * qglGetMapdv )(GLenum target, GLenum query, GLdouble *v);
extern  void ( APIENTRY * qglGetMapfv )(GLenum target, GLenum query, GLfloat *v);
extern  void ( APIENTRY * qglGetMapiv )(GLenum target, GLenum query, GLint *v);
extern  void ( APIENTRY * qglGetMaterialfv )(GLenum face, GLenum pname, GLfloat *params);
extern  void ( APIENTRY * qglGetMaterialiv )(GLenum face, GLenum pname, GLint *params);
extern  void ( APIENTRY * qglGetPixelMapfv )(GLenum map, GLfloat *values);
extern  void ( APIENTRY * qglGetPixelMapuiv )(GLenum map, GLuint *values);
extern  void ( APIENTRY * qglGetPixelMapusv )(GLenum map, GLushort *values);
extern  void ( APIENTRY * qglGetPointerv )(GLenum pname, GLvoid* *params);
extern  void ( APIENTRY * qglGetPolygonStipple )(GLubyte *mask);
extern  const GLubyte * ( APIENTRY * qglGetString )(GLenum name);
extern  void ( APIENTRY * qglGetTexEnvfv )(GLenum target, GLenum pname, GLfloat *params);
extern  void ( APIENTRY * qglGetTexEnviv )(GLenum target, GLenum pname, GLint *params);
extern  void ( APIENTRY * qglGetTexGendv )(GLenum coord, GLenum pname, GLdouble *params);
extern  void ( APIENTRY * qglGetTexGenfv )(GLenum coord, GLenum pname, GLfloat *params);
extern  void ( APIENTRY * qglGetTexGeniv )(GLenum coord, GLenum pname, GLint *params);
extern  void ( APIENTRY * qglGetTexImage )(GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels);
extern  void ( APIENTRY * qglGetTexLevelParameterfv )(GLenum target, GLint level, GLenum pname, GLfloat *params);
extern  void ( APIENTRY * qglGetTexLevelParameteriv )(GLenum target, GLint level, GLenum pname, GLint *params);
extern  void ( APIENTRY * qglGetTexParameterfv )(GLenum target, GLenum pname, GLfloat *params);
extern  void ( APIENTRY * qglGetTexParameteriv )(GLenum target, GLenum pname, GLint *params);
extern  void ( APIENTRY * qglHint )(GLenum target, GLenum mode);
extern  void ( APIENTRY * qglIndexMask )(GLuint mask);
extern  void ( APIENTRY * qglIndexPointer )(GLenum type, GLsizei stride, const GLvoid *pointer);
extern  void ( APIENTRY * qglIndexd )(GLdouble c);
extern  void ( APIENTRY * qglIndexdv )(const GLdouble *c);
extern  void ( APIENTRY * qglIndexf )(GLfloat c);
extern  void ( APIENTRY * qglIndexfv )(const GLfloat *c);
extern  void ( APIENTRY * qglIndexi )(GLint c);
extern  void ( APIENTRY * qglIndexiv )(const GLint *c);
extern  void ( APIENTRY * qglIndexs )(GLshort c);
extern  void ( APIENTRY * qglIndexsv )(const GLshort *c);
extern  void ( APIENTRY * qglIndexub )(GLubyte c);
extern  void ( APIENTRY * qglIndexubv )(const GLubyte *c);
extern  void ( APIENTRY * qglInitNames )(void);
extern  void ( APIENTRY * qglInterleavedArrays )(GLenum format, GLsizei stride, const GLvoid *pointer);
extern  GLboolean ( APIENTRY * qglIsEnabled )(GLenum cap);
extern  GLboolean ( APIENTRY * qglIsList )(GLuint list);
extern  GLboolean ( APIENTRY * qglIsTexture )(GLuint texture);
extern  void ( APIENTRY * qglLightModelf )(GLenum pname, GLfloat param);
extern  void ( APIENTRY * qglLightModelfv )(GLenum pname, const GLfloat *params);
extern  void ( APIENTRY * qglLightModeli )(GLenum pname, GLint param);
extern  void ( APIENTRY * qglLightModeliv )(GLenum pname, const GLint *params);
extern  void ( APIENTRY * qglLightf )(GLenum light, GLenum pname, GLfloat param);
extern  void ( APIENTRY * qglLightfv )(GLenum light, GLenum pname, const GLfloat *params);
extern  void ( APIENTRY * qglLighti )(GLenum light, GLenum pname, GLint param);
extern  void ( APIENTRY * qglLightiv )(GLenum light, GLenum pname, const GLint *params);
extern  void ( APIENTRY * qglLineStipple )(GLint factor, GLushort pattern);
extern  void ( APIENTRY * qglLineWidth )(GLfloat width);
extern  void ( APIENTRY * qglListBase )(GLuint base);
extern  void ( APIENTRY * qglLoadIdentity )(void);
extern  void ( APIENTRY * qglLoadMatrixd )(const GLdouble *m);
extern  void ( APIENTRY * qglLoadMatrixf )(const GLfloat *m);
extern  void ( APIENTRY * qglLoadName )(GLuint name);
extern  void ( APIENTRY * qglLogicOp )(GLenum opcode);
extern  void ( APIENTRY * qglMap1d )(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble *points);
extern  void ( APIENTRY * qglMap1f )(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points);
extern  void ( APIENTRY * qglMap2d )(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble *points);
extern  void ( APIENTRY * qglMap2f )(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points);
extern  void ( APIENTRY * qglMapGrid1d )(GLint un, GLdouble u1, GLdouble u2);
extern  void ( APIENTRY * qglMapGrid1f )(GLint un, GLfloat u1, GLfloat u2);
extern  void ( APIENTRY * qglMapGrid2d )(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
extern  void ( APIENTRY * qglMapGrid2f )(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
extern  void ( APIENTRY * qglMaterialf )(GLenum face, GLenum pname, GLfloat param);
extern  void ( APIENTRY * qglMaterialfv )(GLenum face, GLenum pname, const GLfloat *params);
extern  void ( APIENTRY * qglMateriali )(GLenum face, GLenum pname, GLint param);
extern  void ( APIENTRY * qglMaterialiv )(GLenum face, GLenum pname, const GLint *params);
extern  void ( APIENTRY * qglMatrixMode )(GLenum mode);
extern  void ( APIENTRY * qglMultMatrixd )(const GLdouble *m);
extern  void ( APIENTRY * qglMultMatrixf )(const GLfloat *m);
extern  void ( APIENTRY * qglNewList )(GLuint list, GLenum mode);
extern  void ( APIENTRY * qglNormal3b )(GLbyte nx, GLbyte ny, GLbyte nz);
extern  void ( APIENTRY * qglNormal3bv )(const GLbyte *v);
extern  void ( APIENTRY * qglNormal3d )(GLdouble nx, GLdouble ny, GLdouble nz);
extern  void ( APIENTRY * qglNormal3dv )(const GLdouble *v);
extern  void ( APIENTRY * qglNormal3f )(GLfloat nx, GLfloat ny, GLfloat nz);
extern  void ( APIENTRY * qglNormal3fv )(const GLfloat *v);
extern  void ( APIENTRY * qglNormal3i )(GLint nx, GLint ny, GLint nz);
extern  void ( APIENTRY * qglNormal3iv )(const GLint *v);
extern  void ( APIENTRY * qglNormal3s )(GLshort nx, GLshort ny, GLshort nz);
extern  void ( APIENTRY * qglNormal3sv )(const GLshort *v);
extern  void ( APIENTRY * qglNormalPointer )(GLenum type, GLsizei stride, const GLvoid *pointer);
extern  void ( APIENTRY * qglOrtho )(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
extern  void ( APIENTRY * qglPassThrough )(GLfloat token);
extern  void ( APIENTRY * qglPixelMapfv )(GLenum map, GLsizei mapsize, const GLfloat *values);
extern  void ( APIENTRY * qglPixelMapuiv )(GLenum map, GLsizei mapsize, const GLuint *values);
extern  void ( APIENTRY * qglPixelMapusv )(GLenum map, GLsizei mapsize, const GLushort *values);
extern  void ( APIENTRY * qglPixelStoref )(GLenum pname, GLfloat param);
extern  void ( APIENTRY * qglPixelStorei )(GLenum pname, GLint param);
extern  void ( APIENTRY * qglPixelTransferf )(GLenum pname, GLfloat param);
extern  void ( APIENTRY * qglPixelTransferi )(GLenum pname, GLint param);
extern  void ( APIENTRY * qglPixelZoom )(GLfloat xfactor, GLfloat yfactor);
extern  void ( APIENTRY * qglPointSize )(GLfloat size);
extern  void ( APIENTRY * qglPolygonMode )(GLenum face, GLenum mode);
extern  void ( APIENTRY * qglPolygonOffset )(GLfloat factor, GLfloat units);
extern  void ( APIENTRY * qglPolygonStipple )(const GLubyte *mask);
extern  void ( APIENTRY * qglPopAttrib )(void);
extern  void ( APIENTRY * qglPopClientAttrib )(void);
extern  void ( APIENTRY * qglPopMatrix )(void);
extern  void ( APIENTRY * qglPopName )(void);
extern  void ( APIENTRY * qglPrioritizeTextures )(GLsizei n, const GLuint *textures, const GLclampf *priorities);
extern  void ( APIENTRY * qglPushAttrib )(GLbitfield mask);
extern  void ( APIENTRY * qglPushClientAttrib )(GLbitfield mask);
extern  void ( APIENTRY * qglPushMatrix )(void);
extern  void ( APIENTRY * qglPushName )(GLuint name);
extern  void ( APIENTRY * qglRasterPos2d )(GLdouble x, GLdouble y);
extern  void ( APIENTRY * qglRasterPos2dv )(const GLdouble *v);
extern  void ( APIENTRY * qglRasterPos2f )(GLfloat x, GLfloat y);
extern  void ( APIENTRY * qglRasterPos2fv )(const GLfloat *v);
extern  void ( APIENTRY * qglRasterPos2i )(GLint x, GLint y);
extern  void ( APIENTRY * qglRasterPos2iv )(const GLint *v);
extern  void ( APIENTRY * qglRasterPos2s )(GLshort x, GLshort y);
extern  void ( APIENTRY * qglRasterPos2sv )(const GLshort *v);
extern  void ( APIENTRY * qglRasterPos3d )(GLdouble x, GLdouble y, GLdouble z);
extern  void ( APIENTRY * qglRasterPos3dv )(const GLdouble *v);
extern  void ( APIENTRY * qglRasterPos3f )(GLfloat x, GLfloat y, GLfloat z);
extern  void ( APIENTRY * qglRasterPos3fv )(const GLfloat *v);
extern  void ( APIENTRY * qglRasterPos3i )(GLint x, GLint y, GLint z);
extern  void ( APIENTRY * qglRasterPos3iv )(const GLint *v);
extern  void ( APIENTRY * qglRasterPos3s )(GLshort x, GLshort y, GLshort z);
extern  void ( APIENTRY * qglRasterPos3sv )(const GLshort *v);
extern  void ( APIENTRY * qglRasterPos4d )(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
extern  void ( APIENTRY * qglRasterPos4dv )(const GLdouble *v);
extern  void ( APIENTRY * qglRasterPos4f )(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
extern  void ( APIENTRY * qglRasterPos4fv )(const GLfloat *v);
extern  void ( APIENTRY * qglRasterPos4i )(GLint x, GLint y, GLint z, GLint w);
extern  void ( APIENTRY * qglRasterPos4iv )(const GLint *v);
extern  void ( APIENTRY * qglRasterPos4s )(GLshort x, GLshort y, GLshort z, GLshort w);
extern  void ( APIENTRY * qglRasterPos4sv )(const GLshort *v);
extern  void ( APIENTRY * qglReadBuffer )(GLenum mode);
extern  void ( APIENTRY * qglReadPixels )(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);
extern  void ( APIENTRY * qglRectd )(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
extern  void ( APIENTRY * qglRectdv )(const GLdouble *v1, const GLdouble *v2);
extern  void ( APIENTRY * qglRectf )(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
extern  void ( APIENTRY * qglRectfv )(const GLfloat *v1, const GLfloat *v2);
extern  void ( APIENTRY * qglRecti )(GLint x1, GLint y1, GLint x2, GLint y2);
extern  void ( APIENTRY * qglRectiv )(const GLint *v1, const GLint *v2);
extern  void ( APIENTRY * qglRects )(GLshort x1, GLshort y1, GLshort x2, GLshort y2);
extern  void ( APIENTRY * qglRectsv )(const GLshort *v1, const GLshort *v2);
extern  GLint ( APIENTRY * qglRenderMode )(GLenum mode);
extern  void ( APIENTRY * qglRotated )(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
extern  void ( APIENTRY * qglRotatef )(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
extern  void ( APIENTRY * qglScaled )(GLdouble x, GLdouble y, GLdouble z);
extern  void ( APIENTRY * qglScalef )(GLfloat x, GLfloat y, GLfloat z);
extern  void ( APIENTRY * qglScissor )(GLint x, GLint y, GLsizei width, GLsizei height);
extern  void ( APIENTRY * qglSelectBuffer )(GLsizei size, GLuint *buffer);
extern  void ( APIENTRY * qglShadeModel )(GLenum mode);
extern  void ( APIENTRY * qglStencilFunc )(GLenum func, GLint ref, GLuint mask);
extern  void ( APIENTRY * qglStencilMask )(GLuint mask);
extern  void ( APIENTRY * qglStencilOp )(GLenum fail, GLenum zfail, GLenum zpass);
extern  void ( APIENTRY * qglTexCoord1d )(GLdouble s);
extern  void ( APIENTRY * qglTexCoord1dv )(const GLdouble *v);
extern  void ( APIENTRY * qglTexCoord1f )(GLfloat s);
extern  void ( APIENTRY * qglTexCoord1fv )(const GLfloat *v);
extern  void ( APIENTRY * qglTexCoord1i )(GLint s);
extern  void ( APIENTRY * qglTexCoord1iv )(const GLint *v);
extern  void ( APIENTRY * qglTexCoord1s )(GLshort s);
extern  void ( APIENTRY * qglTexCoord1sv )(const GLshort *v);
extern  void ( APIENTRY * qglTexCoord2d )(GLdouble s, GLdouble t);
extern  void ( APIENTRY * qglTexCoord2dv )(const GLdouble *v);
extern  void ( APIENTRY * qglTexCoord2f )(GLfloat s, GLfloat t);
extern  void ( APIENTRY * qglTexCoord2fv )(const GLfloat *v);
extern  void ( APIENTRY * qglTexCoord2i )(GLint s, GLint t);
extern  void ( APIENTRY * qglTexCoord2iv )(const GLint *v);
extern  void ( APIENTRY * qglTexCoord2s )(GLshort s, GLshort t);
extern  void ( APIENTRY * qglTexCoord2sv )(const GLshort *v);
extern  void ( APIENTRY * qglTexCoord3d )(GLdouble s, GLdouble t, GLdouble r);
extern  void ( APIENTRY * qglTexCoord3dv )(const GLdouble *v);
extern  void ( APIENTRY * qglTexCoord3f )(GLfloat s, GLfloat t, GLfloat r);
extern  void ( APIENTRY * qglTexCoord3fv )(const GLfloat *v);
extern  void ( APIENTRY * qglTexCoord3i )(GLint s, GLint t, GLint r);
extern  void ( APIENTRY * qglTexCoord3iv )(const GLint *v);
extern  void ( APIENTRY * qglTexCoord3s )(GLshort s, GLshort t, GLshort r);
extern  void ( APIENTRY * qglTexCoord3sv )(const GLshort *v);
extern  void ( APIENTRY * qglTexCoord4d )(GLdouble s, GLdouble t, GLdouble r, GLdouble q);
extern  void ( APIENTRY * qglTexCoord4dv )(const GLdouble *v);
extern  void ( APIENTRY * qglTexCoord4f )(GLfloat s, GLfloat t, GLfloat r, GLfloat q);
extern  void ( APIENTRY * qglTexCoord4fv )(const GLfloat *v);
extern  void ( APIENTRY * qglTexCoord4i )(GLint s, GLint t, GLint r, GLint q);
extern  void ( APIENTRY * qglTexCoord4iv )(const GLint *v);
extern  void ( APIENTRY * qglTexCoord4s )(GLshort s, GLshort t, GLshort r, GLshort q);
extern  void ( APIENTRY * qglTexCoord4sv )(const GLshort *v);
extern  void ( APIENTRY * qglTexCoordPointer )(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
extern  void ( APIENTRY * qglTexEnvf )(GLenum target, GLenum pname, GLfloat param);
extern  void ( APIENTRY * qglTexEnvfv )(GLenum target, GLenum pname, const GLfloat *params);
extern  void ( APIENTRY * qglTexEnvi )(GLenum target, GLenum pname, GLint param);
extern  void ( APIENTRY * qglTexEnviv )(GLenum target, GLenum pname, const GLint *params);
extern  void ( APIENTRY * qglTexGend )(GLenum coord, GLenum pname, GLdouble param);
extern  void ( APIENTRY * qglTexGendv )(GLenum coord, GLenum pname, const GLdouble *params);
extern  void ( APIENTRY * qglTexGenf )(GLenum coord, GLenum pname, GLfloat param);
extern  void ( APIENTRY * qglTexGenfv )(GLenum coord, GLenum pname, const GLfloat *params);
extern  void ( APIENTRY * qglTexGeni )(GLenum coord, GLenum pname, GLint param);
extern  void ( APIENTRY * qglTexGeniv )(GLenum coord, GLenum pname, const GLint *params);
extern  void ( APIENTRY * qglTexImage1D )(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
extern  void ( APIENTRY * qglTexImage2D )(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
extern  void ( APIENTRY * qglTexParameterf )(GLenum target, GLenum pname, GLfloat param);
extern  void ( APIENTRY * qglTexParameterfv )(GLenum target, GLenum pname, const GLfloat *params);
extern  void ( APIENTRY * qglTexParameteri )(GLenum target, GLenum pname, GLint param);
extern  void ( APIENTRY * qglTexParameteriv )(GLenum target, GLenum pname, const GLint *params);
extern  void ( APIENTRY * qglTexSubImage1D )(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels);
extern  void ( APIENTRY * qglTexSubImage2D )(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
extern  void ( APIENTRY * qglTranslated )(GLdouble x, GLdouble y, GLdouble z);
extern  void ( APIENTRY * qglTranslatef )(GLfloat x, GLfloat y, GLfloat z);
extern  void ( APIENTRY * qglVertex2d )(GLdouble x, GLdouble y);
extern  void ( APIENTRY * qglVertex2dv )(const GLdouble *v);
extern  void ( APIENTRY * qglVertex2f )(GLfloat x, GLfloat y);
extern  void ( APIENTRY * qglVertex2fv )(const GLfloat *v);
extern  void ( APIENTRY * qglVertex2i )(GLint x, GLint y);
extern  void ( APIENTRY * qglVertex2iv )(const GLint *v);
extern  void ( APIENTRY * qglVertex2s )(GLshort x, GLshort y);
extern  void ( APIENTRY * qglVertex2sv )(const GLshort *v);
extern  void ( APIENTRY * qglVertex3d )(GLdouble x, GLdouble y, GLdouble z);
extern  void ( APIENTRY * qglVertex3dv )(const GLdouble *v);
extern  void ( APIENTRY * qglVertex3f )(GLfloat x, GLfloat y, GLfloat z);
extern  void ( APIENTRY * qglVertex3fv )(const GLfloat *v);
extern  void ( APIENTRY * qglVertex3i )(GLint x, GLint y, GLint z);
extern  void ( APIENTRY * qglVertex3iv )(const GLint *v);
extern  void ( APIENTRY * qglVertex3s )(GLshort x, GLshort y, GLshort z);
extern  void ( APIENTRY * qglVertex3sv )(const GLshort *v);
extern  void ( APIENTRY * qglVertex4d )(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
extern  void ( APIENTRY * qglVertex4dv )(const GLdouble *v);
extern  void ( APIENTRY * qglVertex4f )(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
extern  void ( APIENTRY * qglVertex4fv )(const GLfloat *v);
extern  void ( APIENTRY * qglVertex4i )(GLint x, GLint y, GLint z, GLint w);
extern  void ( APIENTRY * qglVertex4iv )(const GLint *v);
extern  void ( APIENTRY * qglVertex4s )(GLshort x, GLshort y, GLshort z, GLshort w);
extern  void ( APIENTRY * qglVertex4sv )(const GLshort *v);
extern  void ( APIENTRY * qglVertexPointer )(GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
extern  void ( APIENTRY * qglViewport )(GLint x, GLint y, GLsizei width, GLsizei height);
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
extern PROC  ( WINAPI * qwglGetProcAddress)(LPCSTR);
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
#if defined (__FX__)
//FX Mesa Functions
// bk001129 - from cvs1.17 (mkv)
extern fxMesaContext (*qfxMesaCreateContext)(GLuint win, GrScreenResolution_t, GrScreenRefresh_t, const GLint attribList[]);
extern fxMesaContext (*qfxMesaCreateBestContext)(GLuint win, GLint width, GLint height, const GLint attribList[]);
extern void (*qfxMesaDestroyContext)(fxMesaContext ctx);
extern void (*qfxMesaMakeCurrent)(fxMesaContext ctx);
extern fxMesaContext (*qfxMesaGetCurrentContext)(void);
extern void (*qfxMesaSwapBuffers)(void);
#endif
//GLX Functions
extern XVisualInfo * (*qglXChooseVisual)( Display *dpy, int screen, int *attribList );
extern GLXContext (*qglXCreateContext)( Display *dpy, XVisualInfo *vis, GLXContext shareList, Bool direct );
extern void (*qglXDestroyContext)( Display *dpy, GLXContext ctx );
extern Bool (*qglXMakeCurrent)( Display *dpy, GLXDrawable drawable, GLXContext ctx);
extern void (*qglXCopyContext)( Display *dpy, GLXContext src, GLXContext dst, GLuint mask );
extern void (*qglXSwapBuffers)( Display *dpy, GLXDrawable drawable );
#endif // __linux__ || __FreeBSD__ // rb010123
#endif	// _WIN32 && __linux__

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
extern GL_EXT_compiled_vertex_array_supported;
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
