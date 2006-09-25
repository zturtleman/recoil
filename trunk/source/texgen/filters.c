#include "htexgen.h"

void tgColorNoise(int _grid, float min, float max)
{
	int i;
	texpixel *pix;
	float range;
	unsigned short *temp;

    tgClearError();

	pix = currentSlot->data;

	temp = noise(tex_width, tex_height, tex_size / (1 << _grid));
	range = (max - min) / 65536.0f;

	for (i = 0;i < tex_width*tex_height;i++)
	{
		pix[i][0] += temp[i] * range + min;
		pix[i][1] += temp[i] * range + min;
		pix[i][2] += temp[i] * range + min;
	}
	free(temp);
}

void tgBumpNoise(int _grid, float min, float max)
{
	int i, length;
	float range;
	float *p;
	unsigned short *temp;

    tgClearError();

	if(!currentSlot)
	{
		tgError("tgBumpNoise - slot not found");
		return;
	}

	p = (float*)currentSlot->data;
	if(!p)
	{
		tgError("tgBumpNoise - slot has invalid data");
		return;
	}

	length = (currentSlot->type == TG_TYPE_FULL) ? 5 : ((currentSlot->type == TG_TYPE_MASK) ? 2 : 0);
	if(!length)
	{
		tgError("tgBumpNoise - unknown slot type");
		return;
	}

	temp = noise(tex_width, tex_height, tex_size / (1 << _grid));

	min *= tex_size;
	max *= tex_size;
	range = (max - min) / 65536.0f;
	p += (length-1);

	for(i=0; i<tex_width*tex_height; i++)
	{
		p[0] += temp[i] * range + min;
		p += length;
	}

	free(temp);
}

void tgWaterErode(float count_, float length_, float erode, float size, float minx, float miny, float maxx, float maxy, float color[4])
{
	texpixel *pix;
	int i, j, k, l, count, length;
	float cr, cg, cb, ca;
	struct
	{
		int ix, iy;
		float x, y;
		float xv, yv;
	} *drip;

    tgClearError();

	pix = currentSlot->data;

	count = count_ * tex_size;
	length = length_ * tex_size;

	erode *= tex_size;
	size *= tex_size;

	erode /= length;
	size /= length;
	cr = color[0] / 256.0f;
	cg = color[1] / 256.0f;
	cb = color[2] / 256.0f;
	ca = color[3] / 256.0f;

	minx *= tex_width;
	miny *= tex_height;
	maxx *= tex_width;
	maxy *= tex_height;

	drip = malloc(count * sizeof(*drip));
	for (i = 0;i < count;i++)
	{
		drip[i].x = lhrandom(minx, maxx);
		drip[i].y = lhrandom(miny, maxy);
		drip[i].xv = lhrandom(-1,1);
		drip[i].yv = lhrandom(0,1);
		drip[i].ix = (int) drip[i].x;
		drip[i].iy = (int) drip[i].y;
		depth(drip[i].ix,drip[i].iy)+=size;
	}
	k = 0;
	l = 0;
	erode += size;
	for (j = 0;j < length;j++)
	{
		for (i = 0;i < count;i++)
		{
			pixel(drip[i].ix,drip[i].iy,0) *= cr;
			pixel(drip[i].ix,drip[i].iy,1) *= cg;
			pixel(drip[i].ix,drip[i].iy,2) *= cb;
			pixel(drip[i].ix,drip[i].iy,3) *= ca;
			depth(drip[i].ix,drip[i].iy)-=erode;
			if (depth(drip[i].ix,drip[i].iy+1) < depth(drip[i].ix+1,drip[i].iy+1))
			{
				if (depth(drip[i].ix-1,drip[i].iy+1) < depth(drip[i].ix,drip[i].iy+1))
					drip[i].xv -= 0.25f;
				else
				{
					if (drip[i].xv < 0)
						drip[i].xv += 0.25f;
					else
						drip[i].xv -= 0.25f;
				}
			}
			else
			{
				if (depth(drip[i].ix-1,drip[i].iy+1) < depth(drip[i].ix+1,drip[i].iy+1))
					drip[i].xv -= 0.25f;
				else
					drip[i].xv += 0.25f;
			}
			if (depth(drip[i].ix,drip[i].iy) < depth(drip[i].ix, drip[i].iy+1))
				drip[i].yv -= 0.125f;
			else
				drip[i].yv += 0.25f;
			if (drip[i].xv < -1.0f ) drip[i].xv = -1.0f;
			if (drip[i].xv >  1.0f ) drip[i].xv =  1.0f;
			if (drip[i].yv <  0.25f) drip[i].yv =  0.25f;
			if (drip[i].yv >  1.0f ) drip[i].yv =  1.0f;
			drip[i].x += drip[i].xv;
			drip[i].y += drip[i].yv;
			drip[i].ix = (int) drip[i].x;
			drip[i].iy = (int) drip[i].y;
			depth(drip[i].ix,drip[i].iy)+=size;
		}
	}
	for (i = 0;i < count;i++)
		depth(drip[i].ix,drip[i].iy)-=size;
	free(drip);
}

void tgCombineMask(const char *bottomn, const char *topn, const char *maskn)
{
	int i;
	float *bottom, *top, *mask, *out = (float*)currentSlot->data;
	float bf, tf;

    tgClearError();

    if(!getSlot(bottomn, 0) || !getSlot(topn, 0) || !getSlot(maskn, 0))
    {
		tgError("tgCombineMask - could not find a slot");
		return;
    }

	bottom = (float*)getSlot(bottomn, 0)->data;
	top = (float*)getSlot(topn, 0)->data;
	mask = (float*)getSlot(maskn, 0)->data;

    if(!bottom || !top || !mask)
    {
		tgError("tgCombineMask - could not find a slot's data");
		return;
    }

	for (i = 0;i < tex_width*tex_height;i++)
	{
		tf = clamp(mask[0] * top[3], 0.0f, 1.0f);
		bf = 1.0f - tf;

		*out++ = *bottom++ * bf + *top++ * tf;
		*out++ = *bottom++ * bf + *top++ * tf;
		*out++ = *bottom++ * bf + *top++ * tf;
		*out++ = *bottom++ * bf + *top++ * tf;
		*out++ = *bottom++ * (1.0f - mask[1]) + *top++ * mask[1];

		mask += 2;
	}
}

void tgLight(float light[3], float lightcolor[3])
{
	texpixel *pix = currentSlot->data;
	int x, y;
	float normal[3], dot, lcolor[3], ilength;

    tgClearError();

	lcolor[0] = lightcolor[0] / 256.0f;
	lcolor[1] = lightcolor[1] / 256.0f;
	lcolor[2] = lightcolor[2] / 256.0f;
	ilength = 1.0f / (float)sqrt(light[0]*light[0]+light[1]*light[1]+light[2]*light[2]);
	light[0] *= ilength;
	light[1] *= ilength;
	light[2] *= ilength;

	for (y = 0;y < tex_height;y++)
	{
		for (x = 0;x < tex_width;x++)
		{
			// heavily condensed and specialized normal calculation
			normal[0] = (depth(x-1,y) - depth(x+1,y)) * 0.25f;
			normal[1] = (depth(x,y-1) - depth(x,y+1)) * 0.25f;
			ilength = 1.0f / (float)sqrt(normal[0]*normal[0] + normal[1]*normal[1] + 1.0);
			normal[0] *= ilength;
			normal[1] *= ilength;
			normal[2] = ilength;
			dot = (1.0f - (normal[0]*light[0] + normal[1]*light[1] + normal[2]*light[2])) * 0.5f;
			pix[y*tex_width+x][0] *= (float)(lcolor[0] * dot);
			pix[y*tex_width+x][1] *= (float)(lcolor[1] * dot);
			pix[y*tex_width+x][2] *= (float)(lcolor[2] * dot);
		}
	}
}

void tgNormalmap(void)
{
	texpixel *pix = currentSlot->data;
	int x, y;
	double normal[3], ilength;

    tgClearError();

	for (y = 0;y < tex_height;y++)
	{
		for (x = 0;x < tex_width;x++)
		{
			// heavily condensed and specialized normal calculation
			normal[0] = (depth(x-1,y) - depth(x+1,y)) * 0.25;
			normal[1] = (depth(x,y-1) - depth(x,y+1)) * 0.25f;
			ilength = 1.0 / sqrt(normal[0]*normal[0] + normal[1]*normal[1] + 1.0);
			normal[0] *= ilength;
			normal[1] *= ilength;
			normal[2] = ilength;
			pix[y*tex_width+x][0] = (float)(normal[0] * ilength) * 256.0f;
			pix[y*tex_width+x][1] = (float)(normal[1] * ilength) * 256.0f;
			pix[y*tex_width+x][2] = (float)(ilength) * 256.0f;
		}
	}
}

void tgMovezoom(int w, int h, float tx, float ty)
{
	int _x, _y, x, y, offsetIn, offsetOut, size, length;
	float *out, *in;

    tgClearError();

	tx *= tex_size;
	ty *= tex_size;

	out = (float*)scratch;
	in = (float*)currentSlot->data;

	length =	(currentSlot->type == TG_TYPE_FULL) ? 5 :
				(currentSlot->type == TG_TYPE_MASK) ? 2 : 0;
	size = sizeof(float) * length;

	for (_y = 0;_y < tex_height;_y++)
	{
		for (_x = 0;_x < tex_width;_x++)
		{
			x = (int)(_x * w + tx);
			y = (int)(_y * h + ty);

			offsetOut = ((_y & tex_height1) * tex_width + (_x & tex_width1)) * length;
			offsetIn = ((y & tex_height1) * tex_width + (x & tex_width1)) * length;

			memcpy(out + offsetOut, in + offsetIn, size);
		}
	}

	memcpy(currentSlot->data, scratch, sizeof(texpixel) * tex_width * tex_height);
}

static void tgConvolute(float *kernel, int size)
{
    tgClearError();

	if(currentSlot->type == TG_TYPE_FULL)
	{
		int x, y, xx, yy, sizei, xxx, yyy;
		float *p;
		texpixel *pix = currentSlot->data;

		sizei = size - 1;

		for(y = 0;y < tex_height;y++)
		for(x = 0;x < tex_width;x++)
		{
			p = (float*)scratch[y * tex_width + x];
			p[0] = p[1] = p[2] = p[3] = p[4] = 0;

			for(yy = 0; yy<size; yy++)
			for(xx = 0; xx<size; xx++)
			{
				xxx = x + (xx - ((float)sizei / 2.0f));
				yyy = y + (yy - ((float)sizei / 2.0f));

				p[0] += pixel(xxx, yyy, 0) * kernel[yy * size + xx];
				p[1] += pixel(xxx, yyy, 1) * kernel[yy * size + xx];
				p[2] += pixel(xxx, yyy, 2) * kernel[yy * size + xx];
				p[3] += pixel(xxx, yyy, 3) * kernel[yy * size + xx];
				p[4] += pixel(xxx, yyy, 4) * kernel[yy * size + xx];
			}
		}
	}
	else if(currentSlot->type == TG_TYPE_MASK)
	{
		int x, y, xx, yy, sizei, xxx, yyy;
		float *out, *s = (float*)scratch;
		float *in = (float*)currentSlot->data;

		sizei = size - 1;

		for(y = 0;y < tex_height;y++)
		for(x = 0;x < tex_width;x++)
		{
			out = &s[(y * tex_width + x) * 2];
			out[0] = out[1] = 0;

			for(yy = 0; yy<size; yy++)
			for(xx = 0; xx<size; xx++)
			{
				xxx = x + (xx - ((float)sizei / 2.0f));
				yyy = y + (yy - ((float)sizei / 2.0f));

				out[0] += in[((yyy & tex_height1) * tex_width + (xxx & tex_width1)) * 2 + 0] * kernel[yy * size + xx];
				out[1] += in[((yyy & tex_height1) * tex_width + (xxx & tex_width1)) * 2 + 1] * kernel[yy * size + xx];
			}
		}
	}
	else
		tgError("tgConvolute - error: unknown slot type/n");

	memcpy(currentSlot->data, scratch, sizeof(texpixel) * tex_width * tex_height);
}

void tgGaussian(float pixels)
{
	int x, y, msize, msizei;
	float *matrix, exp1, xx, yy, length = 0.0;

    tgClearError();

	pixels *= tex_size;
	msize = msizei = (int)(pixels * 4 + 1);
	msizei--;

	matrix = malloc(sizeof(float) * msize * msize);

	exp1 = 1.0f / (2 * 3.14159265 * pixels * pixels);

	for(y=0; y<msize; y++)
	for(x=0; x<msize; x++)
	{
		xx = x - (float)msizei / 2.0f;
		yy = y - (float)msizei / 2.0f;
		matrix[y * msize + x] = exp1 * pow(2.71828183, -((float)(xx * xx + yy * yy) / (2 * pixels * pixels)));
		length += matrix[y * msize + x];
	}

	for(y=0; y<msize; y++)
	for(x=0; x<msize; x++)
	{
		matrix[y * msize + x] /= length;
	}

	tgConvolute(matrix, msize);
}
