#include "htexgen.h"

slot_t slots[TEXSLOTS];

void freeSlot(slot_t *slot)
{
    if(slot->name)
        free(slot->name);
    if(slot->data)
        free(slot->data);

    slot->name = NULL;
    slot->data = NULL;
}

slot_t *allocSlot(const char *slotname)
{
    int i, len;

    for(i=0; i<TEXSLOTS; i++)
    {
        if(!slots[i].name)
        {
            slots[i].data = (texpixel *)malloc(tex_width * tex_height * sizeof(texpixel));
            memset(slots[i].data, 0, tex_width * tex_height * sizeof(texpixel));

            len = strlen(slotname);
            slots[i].name = (char *)malloc(len + 1);
            memcpy(slots[i].name, slotname, len + 1);

            return &slots[i];
        }
    }

    return NULL;
}

slot_t *getSlot(const char *slotname, int allocate)
{
    int i;

    for(i=0; i<TEXSLOTS; i++)
    {
        if(slots[i].name && !strcmp(slotname, slots[i].name))
            return &slots[i];
    }

    return (allocate) ? allocSlot(slotname) : NULL;
}

unsigned short *noise(int width, int height, int grid)
{
    unsigned short *out;
    int *data;
    int amp, grid2, nmin, nmax, width1, height1, x, y, i;
    float scale;
    if (width % grid || height % grid)
        tgi->Error("noise: invalid grid (%d) for width (%d) and height (%d)\n", grid, width, height);
    width1 = width - 1;
    height1 = height - 1;
    out = (unsigned short *)malloc(width*height*sizeof(unsigned short));
    data = (int *)malloc(width*height*sizeof(int));
    for (amp = 2;(amp-1) < RAND_MAX;amp<<=1);
    while ((amp-1) > RAND_MAX)
        amp>>=1;
    if (amp > 0x10000000)
        amp = 0x10000000;
    amp--; // bitmask
#define n(x,y) data[((y)&height1)*width+((x)&width1)]
    for (y = 0;y < height;y += grid)
        for (x = 0;x < width;x += grid)
            n(x,y) = rand() & amp;
    while (grid > 1)
    {
        grid2 = grid;
        grid >>= 1;
        amp >>= 1;
        for (y = 0;y < height;y += grid2)
            for (x = 0;x < width;x += grid2)
                n(x+grid,y+grid) = (n(x,y) + n(x+grid2,y) + n(x,y+grid2) + n(x+grid2,y+grid2)) >> 2;
        for (y = 0;y < height;y += grid2)
        {
            for (x = 0;x < width;x += grid2)
            {
                n(x+grid,y) = (n(x,y) + n(x+grid2,y) + n(x+grid,y-grid) + n(x+grid,y+grid)) >> 2;
                n(x,y+grid) = (n(x,y) + n(x,y+grid2) + n(x-grid,y+grid) + n(x+grid,y+grid)) >> 2;
            }
        }
        for (y = 0;y < height;y += grid)
            for (x = 0;x < width;x += grid)
                n(x,y) += rand() & amp;
    }
    nmin = nmax = n(0,0);
    for (i = 0;i < width*height;i++)
    {
        if (data[i] < nmin)
            nmin = data[i];
        else if (data[i] > nmax)
            nmax = data[i];
    }
    scale = (float) 65535.0f / (nmax - nmin);
    for (i = 0;i < width*height;i++)
        out[i] = (unsigned short) ((data[i] - nmin) * scale);
    free(data);
#undef n
    return out;
}

