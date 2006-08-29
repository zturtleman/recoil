#include "htexgen.h"

char *ErrorString;

const char *tgGetString(int e)
{
    switch(e)
    {
    case TG_ERRORSTRING:
        return ErrorString;
    default:
        tgError("Unkown enum in tgGetString");
        break;
    }

    return NULL;
}

void tgNewPainting(int width, int height)
{
	int i;

    tgClearError();

	tex_width = width;
	tex_height = height;
	tex_width1 = tex_width - 1;
	tex_height1 = tex_height - 1;
	tex_size = (tex_width > tex_height) ? tex_width : tex_height;
	for (i = 4;i < 65536 && (i != tex_width);i+=i);
	if (i >= 65536)
		tgi->Error("init: invalid width, must be power of 2\n");
	for (i = 4;i < 65536 && (i != tex_height);i+=i);
	if (i >= 65536)
		tgi->Error("init: invalid height, must be power of 2\n");
	for (i = 0;i < TEXSLOTS;i++)
		freeSlot(&slots[i]);

	if(scratch)
		free(scratch);

	scratch = malloc(tex_width * tex_height * sizeof(texpixel));
	memset(scratch, 0, tex_width * tex_height * sizeof(texpixel));
}

tg_interface_t *tgi;
void TexgenLibExport(tg_interface_t *_tgi)
{
	tgi = _tgi;

	tgi->bind = tgBind;
	tgi->seed = tgSeed;
    tgi->getString = tgGetString;
	tgi->getImage = tgGetImage;
    tgi->newPainting = tgNewPainting;
	tgi->clear = tgClear;
	tgi->brickMask = tgBrickMask;
    tgi->noiseMask = tgNoiseMask;
	tgi->colorNoise = tgColorNoise;
	tgi->bumpNoise = tgBumpNoise;
	tgi->light = tgLight;
	tgi->normalmap = tgNormalmap;
    tgi->gaussian = tgGaussian;
	tgi->combineMask = tgCombineMask;
	tgi->waterErode = tgWaterErode;
	tgi->BuildTextureFromScript = script_execute;

	memset(slots, 0, sizeof(slot_t) * TEXSLOTS);
	scratch = NULL;
    tgClearError();
}
