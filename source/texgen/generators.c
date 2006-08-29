#include "htexgen.h"

void tgClear(float cr, float cg, float cb, float ca, float cd)
{
	int i;
	texpixel *pix;
	pix = currentSlot->data;

    tgClearError();

	currentSlot->type = TG_TYPE_FULL;

	for (i = 0;i < tex_width*tex_height;i++)
	{
		pix[i][0] = cr;
		pix[i][1] = cg;
		pix[i][2] = cb;
		pix[i][3] = ca;
		pix[i][4] = cd;
	}
}

void tgBrickMask(float brickwidth_, float brickheight_, float mortarthickness_, float bevelthickness_)
{
	int brickwidth = (int)(brickwidth_ * tex_width);
	int brickheight = (int)(brickheight_ * tex_height);
	int mortarthickness = (int)(mortarthickness_ * tex_size);
	int bevelthickness = (int)(bevelthickness_ * tex_size);
	float *p = (float *)currentSlot->data;
	int halfbrickwidth, x, y, c, basex, basey, ox, oy;

    tgClearError();

	currentSlot->type = TG_TYPE_MASK;

	if (mortarthickness > brickwidth || mortarthickness > brickheight)
		tgError("brickwall: mortarthickness is bigger than the bricks");

	halfbrickwidth = brickwidth>>1;

	if ((bevelthickness*2) > (brickwidth - mortarthickness) || (bevelthickness*2) > (brickheight - mortarthickness))
		tgError("brickwall: bevelthickness is bigger than the bricks");

	basex = basey = mortarthickness/2;
	for (y = 0;y < tex_height;y++)
	for (x = 0;x < tex_width;x++)
	{
		c = 0;
		oy = (y+basey) % brickheight;
		if (oy < mortarthickness)
			c = 1;
		else
		{
			if (((y+basey) / brickheight) & 1) // odd row
				ox = ((x+basex)+halfbrickwidth) % brickwidth;
			else // even row
				ox =  (x+basex)                 % brickwidth;
			if (ox < mortarthickness)
				c = 1;
		}

		if (c)
		{
			*p++ = 0.0;
			*p++ = 0.0;
		}
		else
		{
			*p++ = 1.0;
			if (bevelthickness > 0)
			{
				int dx, dy, d;
				ox -= mortarthickness;
				oy -= mortarthickness;
				if (ox < bevelthickness)
					dx = bevelthickness - ox;
				else if (ox >= (brickwidth - bevelthickness - mortarthickness))
					dx = ox - (brickwidth - bevelthickness - mortarthickness);
				else
					dx = 0;
				if (oy < bevelthickness)
					dy = bevelthickness - oy;
				else if (oy >= (brickheight - bevelthickness - mortarthickness))
					dy = oy - (brickheight - bevelthickness - mortarthickness);
				else
					dy = 0;
				d = dx;
				if (d < dy)
					d = dy;
				*p++ = 1.0f - ((float)d / (float)bevelthickness);
			}
			else
				*p++ = 1.0;
		}
	}
}

void tgNoiseMask(int grid, float min, float max)
{
	int i;
	float range;
	float *pix;
	unsigned short *temp;

    tgClearError();

	pix = (float*)currentSlot->data;
	currentSlot->type = TG_TYPE_MASK;

	temp = noise(tex_width, tex_height, tex_size / (1 << grid));

	min *= 65536.0f;
	max *= 65536.0f;

	range = 1.0f / (float)(max - min);

	for (i = 0;i < tex_width*tex_height;i++)
	{
		if(temp[i] > min)
		{
			*pix++ = (temp[i] < max) ? (temp[i] - min) * range : 1.0f;
			*pix++ = (temp[i] < max) ? (temp[i] - min) * range : 1.0f;
		}
		else
		{
			*pix++ = 0.0;
			*pix++ = 0.0;
		}
	}

	free(temp);
}
