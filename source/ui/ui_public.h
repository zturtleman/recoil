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
//
#ifndef __UI_PUBLIC_H__
#define __UI_PUBLIC_H__

typedef struct {
	connstate_t		connState;
	int				connectPacketCount;
	int				clientNum;
	char			servername[MAX_STRING_CHARS];
	char			updateInfoString[MAX_STRING_CHARS];
	char			messageString[MAX_STRING_CHARS];
} uiClientState_t;

typedef enum {
	UIMENU_NONE,
	UIMENU_MAIN,
	UIMENU_INGAME,
	UIMENU_NEED_CD,
	UIMENU_BAD_CD_KEY,
	UIMENU_TEAM,
	UIMENU_POSTGAME
} uiMenuCommand_t;

#define SORT_HOST			0
#define SORT_MAP			1
#define SORT_CLIENTS		2
#define SORT_GAME			3
#define SORT_PING			4
#define SORT_PUNKBUSTER		5

void UI_SetActiveMenu( uiMenuCommand_t menu );
void UI_KeyEvent( int key, int down );
qboolean UI_ConsoleCommand( int realTime );
void UI_Shutdown( void );
void UI_DrawConnectScreen( qboolean overlay );
void UI_Refresh( int realtime );
qboolean UI_IsFullscreen( void );
void UI_MouseEvent( int dx, int dy );

void Cbuf_ExecuteText (int exec_when, const char *text);
void Cvar_Set( const char *var_name, const char *value);
void Cvar_SetValue( const char *var_name, float value);
qhandle_t RE_RegisterShaderNoMip(const char *name);
int GetConfigString(int index, char *buf, int size);
void GetClientState( uiClientState_t *state );
void Cvar_VariableStringBuffer( const char *var_name, char *buffer, int bufsize );
sfxHandle_t	S_RegisterSound( const char *name, qboolean compressed );
void S_StartLocalSound( sfxHandle_t sfxHandle, int channelNum );
void Key_SetCatcher( int catcher );
void	RE_SetColor( const float *rgba );
void LAN_GetServerAddressString( int source, int n, char *buf, int buflen );
int LAN_GetPingQueueCount( void );
void LAN_ClearPing( int n );
void LAN_GetPingInfo( int n, char *buf, int buflen );
void LAN_GetPing( int n, char *buf, int buflen, int *pingtime );
int LAN_GetServerCount( int source );
void Cvar_Reset( const char *var_name );
qboolean Key_GetOverstrikeMode( void );
void FS_FCloseFile( fileHandle_t f );
int FS_Read2( void *buffer, int len, fileHandle_t f );
int		FS_FOpenFileByMode( const char *qpath, fileHandle_t *f, fsMode_t mode );
qhandle_t RE_RegisterSkin( const char *name );
void RE_RenderScene( const refdef_t *fd );
void RE_AddLightToScene( const vec3_t org, float intensity, float r, float g, float b );
void RE_ClearScene( void );
void RE_AddRefEntityToScene( const refEntity_t *ent );
int R_LerpTag( orientation_t *tag, qhandle_t handle, int startFrame, int endFrame,
               float frac, const char *tagName );
qhandle_t RE_RegisterModel( const char *name );
int	FS_GetFileList(  const char *path, const char *extension, char *listbuf, int bufsize );
int	Hunk_MemoryRemaining( void );
int	FS_GetFileList(  const char *path, const char *extension, char *listbuf, int bufsize );
void Key_SetOverstrikeMode( qboolean state );
qboolean Key_IsDown( int keynum );
void CL_GetClipboardData( char *buf, int buflen );
void Key_SetBinding( int keynum, const char *binding );
void Key_GetBindingBuf( int keynum, char *buf, int buflen );
void Key_KeynumToStringBuf( int keynum, char *buf, int buflen );
void SCR_UpdateScreen( void );
void CL_GetGlconfig( glconfig_t *glconfig );
void	Cmd_ArgvBuffer( int arg, char *buffer, int bufferLength );
void RE_StretchPic ( float x, float y, float w, float h,
                     float s1, float t1, float s2, float t2, qhandle_t hShader );
void Key_ClearStates (void);
void Key_SetCatcher( int catcher );
float Cvar_VariableValue( const char *var_name );
int Key_GetCatcher( void );
cvar_t *Cvar_Get( const char *var_name, const char *var_value, int flags );

#endif
