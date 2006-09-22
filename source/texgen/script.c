
#include "htexgen.h"

int tex_width, tex_height, tex_width1, tex_height1, tex_size;
texpixel *scratch;

static int script_argc;
static char *script_argv[32];

static char temptoken[1024];
static char *curtoken;

#define Float(n) (float)atof(script_argv[n])
#define Integer(n) atoi(script_argv[n])
#define String(n) script_argv[n]

static void script_tokenclear()
{
	curtoken = temptoken;
}

static unsigned char *script_gettoken(char **start, char *end)
{
	char *in = *start, *out, *temp;
	if (in >= end)
		return NULL;
	while (in < end && *in <= ' ' && *in != '\n' && *in != '\r') // whitespace, but not newlines
		in++;
	if (in >= end) // empty
	{
		*start = in;
		return NULL;
	}
	temp = out = curtoken; // place to store the temporary string
	if (*in == '\n' || *in == '\r') // if it's a newline, simply store it off as it's own token, regardless of what was around it
	{
		*out++ = *in++;
		*out++ = 0;
		*start = in;
		curtoken = out;
		return temp;
	}
	while (in < end && *in > ' ') // copy until we hit whitespace again
		*out++ = *in++;
	*out++ = 0;
	*start = in;
	curtoken = out;
	return temp; // return the token
}

static void sc_clear()
{
	tgClear(Float(1), Float(2), Float(3), Float(4), Float(5));
}

static void sc_seed()
{
	tgSeed(Integer(1));
}

static void sc_colornoise()
{
	tgColorNoise(Integer(1), Float(2), Float(3));
}

static void sc_bumpnoise()
{
	tgBumpNoise(Integer(1), Float(2), Float(3));
}

static void sc_brickwall()
{
	tgBrickMask(Float(1), Float(2), Float(3), Float(4));
}

static void sc_watererode()
{
	float color[4];

	color[0] = Float( 9);
	color[1] = Float(10);
	color[2] = Float(11);
	color[3] = Float(12);

	tgWaterErode(Float(1), Float(2), Float(3), Float(4), Float(5), Float(6), Float(7), Float(8), color);
}

static void sc_combineMask()
{
	tgCombineMask(String(1), String(2), String(3));
}

static void sc_light()
{
	float light[3], lcolor[3];

	light[0] = Float(1);
	light[1] = Float(2);
	light[2] = Float(3);
	lcolor[0] = Float(4);
	lcolor[1] = Float(5);
	lcolor[2] = Float(6);
	tgLight(light, lcolor);
}

static void sc_normalmap()
{
	tgNormalmap();
}

static void sc_movezoom()
{
	tgMovezoom(Float(1), Float(2), Float(3), Float(4));
}

static void sc_gaussian()
{
	tgGaussian(Float(1));
}

static void sc_noisemask()
{
	tgNoiseMask(Integer(1), Float(2), Float(3));
}

typedef struct
{
	char *name;
	char *usage;
	void (*code)();
	unsigned short least, most;
} sccommand_t;

static sccommand_t script_command[] =
{
	{"clear", "red green blue alpha depth", sc_clear, 5, 5},
	{"seed", "number", sc_seed, 1, 1},
	{"colornoise", "grid min max [greenmin greenmax bluemin bluemax]", sc_colornoise, 3, 7},
	{"bumpnoise", "grid min max", sc_bumpnoise, 3, 3},
	{"brickmask", "brickwidth brickheight mortarthickness bevelthickness", sc_brickwall, 4, 4},
	{"combinemask", "bottomLayer topLayer mask", sc_combineMask, 3, 3},
	{"watererode", "drips length erode dripsize minx miny maxx maxy (drip discoloration)red green blue alpha", sc_watererode, 12, 12},
	{"light", "anglex angley anglez red green blue", sc_light, 6, 6},
	{"normalmap", "", sc_normalmap, 0, 0},
	{"movezoom", "w h tx ty", sc_movezoom, 4, 4},
	{"gaussian", "pixels", sc_gaussian, 1, 1},
	{"noisemask", "grid min max", sc_noisemask, 3, 3},
	{NULL, NULL, NULL, 0, 0} // end of the list
};

void script_execute(unsigned char *script, unsigned int scriptsize, int width, int height)
{
	int i, len;
	char *in, *end, *token;
	unsigned char *data;

	in = script;
	end = script + scriptsize;

	tgNewPainting(width, height);
	while (in < end)
	{
		if (*in == '\r' || *in == '\n')
		{
			in++;
			continue;
		}
		script_tokenclear();
		script_argv[0] = token = script_gettoken(&in, end);
		script_argc = 1;
		if (!token)
			break;
		if (token[0] == '/' && token[1] == '/') // comment
		{
			while(in < end && *in != '\r' && *in != '\n')
				in++;
			continue;
		}
		len = strlen(token);
		if(token[len-1] == ':')
		{
			script_argv[0][len-1] = 0;
			tgBind(script_argv[0]);
		}
		else
		{
			for (i = 0;;i++)
			{
				if (script_command[i].code == NULL)
                {
					tgi->Error("unknown command \"%s\"", token);
                    return;
                }
				if (!strcmp(token, script_command[i].name))
					break;
			}

			while (1)
			{
				script_argv[script_argc] = token = script_gettoken(&in, end);
				if (!token || token[0] == '\r' || token[0] == '\n')
					break;
				script_argc++;
			}

			if ((script_argc-1) < script_command[i].least)
				tgi->Error("%s: too few parameters (usage: %s %s)\n", script_command[i].name, script_command[i].name, script_command[i].usage);
			if ((script_argc-1) > script_command[i].most)
				tgi->Error("%s: too many parameters (usage: %s %s)\n", script_command[i].name, script_command[i].name, script_command[i].usage);

			script_command[i].code();
		}
	}
}
