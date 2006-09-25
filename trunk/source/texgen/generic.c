#include "htexgen.h"
#include "limits.h"

slot_t *currentSlot;

void tgBind(const char *name)
{
    tgClearError();
	currentSlot = getSlot(name, 1);
}

void tgSeed(int seed)
{
    tgClearError();
	srand(seed);
}

void tgGetImage(int type, int dataType, void **data)
{
	int range, c, i;
	float *p = (float*)currentSlot->data;

    tgClearError();

	switch(type)
	{
	case TG_COLOR:
		range = 4;
		break;
	case TG_DEPTH:
		range = 1;
		p += 4;
		break;
	default:
		tgError("tgGetImage - Bad type");
                return;
	}

#define conversion(t, min, max)												\
	{																		\
		t *out;																\
		*data = tgi->Malloc(sizeof(t) * range * tex_width * tex_height);    \
		out = (t*)*data;													\
		if(!data)															\
			tgError("tgGetImage - insufficient memory");					\
		for(i=0;i<tex_width * tex_height;i++)								\
		{																	\
			for(c=0;c<range;c++)											\
				out[c] = (t)clamp(p[c], min, max);							\
			p += 5;															\
			out += range;													\
		}																	\
	}																		\
	break

	switch(dataType)
	{
	case TG_CHAR:
		conversion(char, CHAR_MIN, CHAR_MAX);
	case TG_BYTE:
	//	conversion(unsigned char, 0, UCHAR_MAX);
	    {
		    unsigned char *out;
		    *data = tgi->Malloc(sizeof(unsigned char) * range * tex_width * tex_height);
		    out = (unsigned char*)*data;
		    if(!data)
			    tgError("tgGetImage - insufficient memory");
		    for(i=0;i<tex_width * tex_height;i++)
		    {
			    for(c=0;c<range;c++)
				    out[c] = (unsigned char)clamp(p[c], 0, UCHAR_MAX);
			    p += 5;
			    out += range;
		    }
	    }
        break;
	case TG_USHORT:
		conversion(unsigned short, 0, USHRT_MAX);
	case TG_SHORT:
		conversion(short, SHRT_MIN, SHRT_MAX);
	case TG_ULONG:
		conversion(unsigned long, 0, ULONG_MAX);
	case TG_LONG:
		conversion(long, LONG_MIN, LONG_MAX);
	case TG_FLOAT:
		conversion(float, -1000.0, 1000.0);
	default:
		tgError("tgGetImage - Bad dataType");
	}

#undef conversion
}
