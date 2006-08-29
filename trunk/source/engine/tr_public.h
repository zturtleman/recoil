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
#ifndef __TR_PUBLIC_H
#define __TR_PUBLIC_H

#include "../cgame/tr_types.h"

void RE_StretchRaw(int x, int y, int w, int h, int cols, int rows, const byte *data, int client, qboolean dirty);
void RE_EndRegistration( void );
void RE_UploadCinematic(int w, int h, int cols, int rows, const byte *data, int client, qboolean dirty);
void	RE_SetColor( const float *rgba );
void RE_Shutdown( qboolean destroyWindow );
void RE_BeginRegistration( glconfig_t *glconfigOut );
qhandle_t RE_RegisterShader(const char *name);
void RE_StretchPic(float x, float y, float w, float h, float s1, float t1, float s2, float t2, qhandle_t hShader);
void RE_BeginFrame( stereoFrame_t stereoFrame );
void RE_EndFrame( int *frontEndMsec, int *backEndMsec );

void *CL_RefMalloc( int size );
void QDECL CL_RefPrintf( int print_level, const char *fmt, ...);
int CIN_PlayCinematic( const char *arg, int x, int y, int w, int h, int systemBits );
void CIN_UploadCinematic(int handle);
e_status CIN_RunCinematic (int handle);
int CL_ScaledMilliseconds(void);
void R_DeleteShaders(void);
void R_InitGLShaders(void);

#endif	// __TR_PUBLIC_H
