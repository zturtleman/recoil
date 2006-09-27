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
/*
=======================================================================
 
MAIN MENU
 
=======================================================================
*/


#include "ui_local.h"


#define ID_SINGLEPLAYER			10
#define ID_MULTIPLAYER			11
#define ID_SETUP				12
#define ID_DEMOS				13
#define ID_EXIT					14

static  menuframework_s     Menu;
static  menubitmap_s        Singleplayer;
static  menubitmap_s        Multiplayer;
static  menubitmap_s        Setup;
static  menubitmap_s        Demos;
static  menubitmap_s        Exit;

static  char                errorMessage[4096];

/* ==================
  MainMenu_ExitAction
================== */
static void MainMenu_ExitAction( qboolean result )
{
    if( !result )
        return;
    UI_PopMenu();
    UI_CreditMenu();
}

/* =============
  Main_MenuEvent
============= */
void Main_MenuEvent (void* ptr, int event)
{
    if( event != QM_ACTIVATED )
        return;

    switch( ((menucommon_s*)ptr)->id )
    {
    case ID_SINGLEPLAYER:
        UI_SPLevelMenu();
        break;

    case ID_MULTIPLAYER:
        UI_ArenaServersMenu();
        break;

    case ID_SETUP:
        UI_SetupMenu();
        break;

    case ID_DEMOS:
        UI_DemosMenu();
        break;

    case ID_EXIT:
        UI_ConfirmMenu( "EXIT GAME?", NULL, MainMenu_ExitAction );
        break;
    }
}

/* =============
  MainMenu_Cache
============= */
void MainMenu_Cache( void )
{
}

sfxHandle_t ErrorMessage_Key(int key)
{
    Cvar_Set( "com_errorMessage", "" );
    UI_MainMenu();
    return (menu_null_sound);
}

/*
===============
Main_MenuDraw
TTimo: this function is common to the main menu and errorMessage menu
===============
*/

static void Main_MenuDraw( void )
{
    if (strlen(errorMessage))
        UI_DrawProportionalString_AutoWrapped( 320, 192, 600, 20, errorMessage, UI_CENTER|UI_SMALLFONT|UI_DROPSHADOW, menu_text_color );
    else
        Menu_Draw( &Menu );
}

/*
===============
UI_MainMenu
 
The main menu only comes up when not in a game,
so make sure that the attract loop server is down
and that local cinematics are killed
===============
*/
void UI_MainMenu( void )
{
    Cvar_Set( "sv_killserver", "1" );

    memset(&Menu, 0, sizeof(menuframework_s));
    memset(&Singleplayer, 0, sizeof(menubitmap_s));
    memset(&Multiplayer, 0, sizeof(menubitmap_s));
    memset(&Setup, 0, sizeof(menubitmap_s));
    memset(&Demos, 0, sizeof(menubitmap_s));
    memset(&Exit, 0, sizeof(menubitmap_s));

    memset(&errorMessage, 0, sizeof(errorMessage));

    // com_errorMessage would need that too
    MainMenu_Cache();

    Menu.draw = Main_MenuDraw;
    Menu.fullscreen = qtrue;
    Menu.wrapAround = qtrue;

    Cvar_VariableStringBuffer( "com_errorMessage", errorMessage, sizeof(errorMessage) );
    if (strlen(errorMessage))
        Menu.key = ErrorMessage_Key;
    else
    {
        int x = 8;

        NewBitmap(Singleplayer, 0, x, 176, ID_SINGLEPLAYER, Main_MenuEvent, 112, 112, "menu/art/menu_sp", "menu/art/menu_sp");
        Singleplayer.generic.statusText = "Single player - best way to learn.";
        x += 128;

        NewBitmap(Multiplayer, 0, x, 176, ID_MULTIPLAYER, Main_MenuEvent, 112, 112, "menu/art/menu_mp", "menu/art/menu_mp");
        Multiplayer.generic.statusText = "Multi-player - show your skills.";
        x += 128;

        NewBitmap(Demos, 0, x, 176, ID_DEMOS, Main_MenuEvent, 112, 112, "menu/art/menu_mv", "menu/art/menu_mv");
        Demos.generic.statusText = "Learn from others, see highlights from your matches.";
        x += 128;

        NewBitmap(Setup, 0, x, 176, ID_SETUP, Main_MenuEvent, 112, 112, "menu/art/menu_st", "menu/art/menu_st");
        Setup.generic.statusText = "Look good or play better, take your pick.";
        x += 128;

        NewBitmap(Exit, 0, x, 176, ID_EXIT, Main_MenuEvent, 112, 112, "menu/art/menu_ex", "menu/art/menu_ex");
        Exit.generic.statusText = "Okay, fine. leave.";
        x += 128;

        Menu_AddItem(&Menu,	&Singleplayer);
        Menu_AddItem(&Menu,	&Multiplayer);
        Menu_AddItem(&Menu,	&Setup);
        Menu_AddItem(&Menu,	&Demos);
        Menu_AddItem(&Menu,	&Exit);
    }

    Key_SetCatcher(KEYCATCH_UI);
    uis.menusp = 0;
    UI_PushMenu(&Menu);
}
