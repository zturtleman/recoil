console
{
	nopicmip
	nomipmaps
	{
		tgmap		gfx\2d\conback.tex cloud1
		tcmod		scroll .02 0
		tcmod		turb 0 .1 0 .05
		tcmod		transform 0.877582562 -0.479425539 0.479425539 0.877582562 0.4 0.6
	}
	{
		tgmap		gfx\2d\conback.tex cloud2
		blendFunc	add
		tcmod		turb 0 .1 0 .1
		tcmod		scroll -0.02 .04
	}
}

menuback
{
	nopicmip
	nomipmaps
	{
		map		gfx\2d\menuback.jpg
		tcmod		scroll .01 0
	}
}

menubacknologo
{
	nopicmip
	nomipmaps
	{
		map		gfx\2d\menuback.jpg
		tcmod		scroll .01 0
	}
}