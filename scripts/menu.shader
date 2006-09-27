console
{
	nopicmip
	nomipmaps
	{
		tgmap		hud\2d\conback.tex cloud1
		tcmod		scroll .02 0
		tcmod		turb 0 .1 0 .05
		tcmod		transform 0.877582562 -0.479425539 0.479425539 0.877582562 0.4 0.6
	}
	{
		tgmap		hud\2d\conback.tex cloud2
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
		map		menu\art\stars.jpg
		tcmod		scroll .0025 0
		tcmod		scale 8 6
	}
	{
		map		menu\art\menuback.tga
		tcmod		scroll .01 0
		blendfunc	blend
	}
}
