textures/manmade/brickwall
{
	{
		tgmap textures/manmade/brick.tex glow
		rgbGen identity
		tcmod scroll 0.01 0.2
	}
	{
		tgmap textures/manmade/brick.tex output
		rgbGen identity
		blendfunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
	{
		map $lightmap
		rgbGen identity
		blendfunc GL_DST_COLOR GL_ZERO
	}

}
