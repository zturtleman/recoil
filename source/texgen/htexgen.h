
//#if _MSC_VER
//#pragma warning (disable : 4244)
//#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <math.h>

#include "tg_shared.h"
extern tg_interface_t *tgi;

typedef float texpixel[5];

extern int tex_width, tex_height, tex_width1, tex_height1, tex_size;
texpixel *scratch;

typedef enum
{
	TG_TYPE_FULL,
	TG_TYPE_MASK
} slot_type_e;

typedef struct
{
	char *name;
	slot_type_e type;
	texpixel *data;
} slot_t;

#define TEXSLOTS 26
extern slot_t slots[TEXSLOTS];
extern slot_t *currentSlot;

#define pixel(x,y,c) pix[((y) & tex_height1) * tex_width + ((x) & tex_width1)][c]
#define depth(x,y) pix[((y) & tex_height1) * tex_width + ((x) & tex_width1)][4]
#define lhrandom(minv,maxv) ((float) rand() * ((maxv)-(minv)) / RAND_MAX + (minv))
#define clamp(v, i, a) (((v) <= (i)) ? (i) : ((v) >= (a)) ? (a) : (v))

void freeSlot(slot_t *slot);
slot_t *allocSlot(const char *slotname);
slot_t *getSlot(const char *slotname, int allocate);
unsigned short *noise(int width, int height, int grid);

void script_execute(unsigned char *script, unsigned int scriptsize, int width, int height);

void tgBind(const char *name);
void tgClear(float cr, float cg, float cb, float ca, float cd);
void tgSeed(int seed);
void tgColorNoise(int grid, float min, float max);
void tgBumpNoise(int grid, float min, float max);
void tgBrickMask(float brickwidth_, float brickheight_, float mortarthickness_, float bevelthickness_);
void tgWaterErode(float count, float length, float erode, float size, float minx, float miny, float maxx, float maxy, float color[4]);
void tgCombineMask(const char *bottomn, const char *topn, const char *maskn);
void tgLight(float light[3], float lightcolor[3]);
void tgNormalmap(void);
void tgMovezoom(int w, int h, float tx, float ty);
void tgNoiseMask(int grid, float min, float max);
void tgGaussian(float pixels);
void tgGetImage(int type, int dataType, void **data);
void tgNewPainting(int width, int height);

extern char *ErrorString;
#define tgClearError() (ErrorString = NULL)
#define tgError(str)\
    do {\
        ErrorString = str;\
        tgi->Error(str);\
    } while(0)

