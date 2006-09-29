#ifndef __cdecl
#define __cdecl
#endif

typedef struct
{
	// generic use
	void (* Error)(const char *message, ...);
	void (* Print)(const char *message, ...);
    void *(* Malloc)(int size);

	void (* bind)(const char *name);
	void (* seed)(int seed);
    const char *(* getString)(int e);

//	void (* setInteger)(int option, int value);
//	void (* setIntegerv)(int option, int *values, int numValues);
//	void (* setFloat)(int option, float value);
//	void (* setFloatv)(int option, float *values, int numValues);

//	void (* getIntegerv)(int option, int *values, int maxValues);
//	void (* getFloatv)(int option, float *values, int maxValues);

	void (* getImage)(int type, int dataType, void **data);
//	void (* getSubImage)(int type, int dataType, void **data, int minx, int miny, int maxx, int maxy);

//	void (* setImage)(int type, int dataType, void *data);
//	void (* setSubImage)(int type, int dataType, void *data, int minx, int miny, int maxx, int maxy);

	void (* newPainting)(int width, int height);

	// generators
	void (* clear)(float cr, float cg, float cb, float ca, float cd);
	void (* brickMask)(float brickwidth_, float brickheight_, float mortarthickness_, float bevelthickness_);
    void (* noiseMask)(int grid, float min, float max);

	// filters
	void (* colorNoise)(int grid, float min, float max);
	void (* bumpNoise)(int grid, float min, float max);
	void (* light)(float light[3], float lightcolor[3]);
	void (* normalmap)(void);
    void (* gaussian)(float pixels);

	// masks
	void (* combineMask)(const char *bottomn, const char *topn, const char *maskn);

	// special tools
	void (* waterErode)(float count, float length, float erode, float size, float minx, float miny, float maxx, float maxy, float color[4]);
	void (* BuildTextureFromScript)(char *buffer, unsigned int script_size, int width, int height);
}
tg_interface_t;

//#define TG_FALSE		0x0000
//#define TG_TRUE			0x0001
//#define TG_FASTEST		0x0002
//#define TG_FAST			0x0003
//#define TG_MODERATE		0x0004
//#define TG_ACCURATE		0x0005
//#define TG_DETAILED		0x0007

#define TG_CHAR			0x0010
#define TG_BYTE			0x0011
#define TG_USHORT		0x0012
#define TG_SHORT		0x0013
#define TG_ULONG		0x0014
#define TG_LONG			0x0015
#define TG_FLOAT		0x0016

//#define TG_NOISE_HINT	0x0020
#define TG_COLOR		0x0021
#define TG_DEPTH		0x0022
#define TG_ERRORSTRING  0x0023

typedef void (__cdecl * PFNTEXGENLIBEXPORTPROC)(tg_interface_t *_tgi);
