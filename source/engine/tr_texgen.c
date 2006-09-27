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
// tr_image.c
#include "tr_local.h"
#include "../texgen/tg_shared.h"

static tg_interface_t tgi;
static qboolean _inited = qfalse;
static DYNLIBTYPE lib;
static const char *lastScriptUsed;

static cvar_t *r_texgen_detail;

qboolean DynlibOpen(DYNLIBTYPE *lib, const char *name);
void *DynlibGetAddress(DYNLIBTYPE lib, const char *name);

void MyLogError(const char *format, ...)
{
}

void MyLogMessage(const char *format, ...)
{
}

void InitTexgenModule(void)
{
    PFNTEXGENLIBEXPORTPROC TexgenLibExport;

    if(_inited || 1)
        return;

    r_texgen_detail = Cvar_Get("r_texgen_detail", "9", CVAR_ARCHIVE);

    tgi.Error = MyLogError;
    tgi.Print = MyLogMessage;
    tgi.Malloc = CL_RefMalloc;

    Com_Printf("trying to load %s:", LIBTEXGEN);
    if(DynlibOpen(&lib, LIBTEXGEN))
    {
        TexgenLibExport = (PFNTEXGENLIBEXPORTPROC)DynlibGetAddress(lib, "TexgenLibExport");
        TexgenLibExport(&tgi);

        lastScriptUsed = NULL;

        _inited = qtrue;

        Com_Printf("success\n");
        return;
    }
    Com_Printf("failure\n");
}

void LoadTexgenImages(const char *name, const char *slots[], byte **pics[], int numSlots, int *width, int *height)
{
    char *script;
    int length, size, i;
    fileHandle_t	f;

    for(i=0; i<numSlots; i++)
        *(pics[i]) = NULL;

    InitTexgenModule();
    if(!_inited)
        return; // falure

    size = (1 << ((r_texgen_detail->integer > 8) ? r_texgen_detail->integer : 8));

    if(width)
        *width = size;
    if(height)
        *height = size;

    if(Q_stricmp(name, lastScriptUsed))
    {
        length = FS_FOpenFileByMode(name, &f, FS_READ);
        if(length == -1)
            return;

        script = (char *)malloc(sizeof(char) * length);

        FS_Read2(script, length, f);
        FS_FCloseFile(f);

        tgi.BuildTextureFromScript(script, length, size, size); // does the commands

        lastScriptUsed = name;
    }

    for(i=0; i<numSlots; i++)
    {
        tgi.bind(slots[i]);
        tgi.getImage(TG_COLOR, TG_BYTE, (void**)pics[i]);
    }
}

void LoadTexGenImage(const char *name, byte **pic, int *width, int *height)
{
    const char *names[1];
    byte **pics[1];

    names[0] = "output";
    pics[0] = pic;

    LoadTexgenImages(name, names, pics, 1, width, height);
}

image_t *R_FindTexgenImage(const char *name, const char *slot, qboolean mipmap, qboolean allowPicmip, int glWrapClampMode)
{
    image_t	*image;
    int		width, height;
    char altname[MAX_QPATH];
    const char *slots[1];
    byte **pics[1], *pic;

    if (!name)
        return NULL;

    strcpy(altname, name);
    strcat(altname, slot);

    image = R_FindImageFile(altname, mipmap, allowPicmip, glWrapClampMode);
    if(image)
        return image;

    slots[0] = slot;
    pics[0] = &pic;

    LoadTexgenImages(name, slots, pics, 1, &width, &height);

    if(pic)
    {
        image = R_CreateImage((char *)altname, (byte *)pic, width, height, mipmap, allowPicmip, glWrapClampMode);
        Z_Free( pic );
        return image;
    }

    return NULL;
}
