


models/players/samus/varia
{	

	{	map models/players/default/shiny.jpg

blendfunc GL_ONE GL_ZERO
		tcGen environment
	}
	{
		map models/players/default/varia.jpg
		blendfunc GL_ONE GL_ONE
		rgbGen lightingDiffuse
	}

}

models/players/samus/normal
{	

	{	map models/players/default/shiny.jpg

blendfunc GL_ONE GL_ZERO
		tcGen environment
	}
	{
		map models/players/default/normal.jpg
		blendfunc GL_ONE GL_ONE
		rgbGen lightingDiffuse
	}

}

models/players/samus/gravity
{	

	{	map models/players/default/shiny.jpg

blendfunc GL_ONE GL_ZERO
		tcGen environment
	}
	{
		map models/players/default/gravity.jpg
		blendfunc GL_ONE GL_ONE
		rgbGen lightingDiffuse
	}

}

models/players/samus/helmet
{	

	{	map models/players/default/shiny.jpg
//		blendfunc GL_DST_COLOR GL_ZERO
blendfunc GL_ONE GL_ZERO
		tcGen environment
	}
	{
		map models/players/default/helmet.jpg
		blendfunc GL_ONE GL_ONE
		rgbGen lightingDiffuse
	}

}

models/players/samus/scan
{
	{	
		map models/players/default/visor_light.tga
		blendfunc add
		rgbGen wave sin 1 1 0 .5


	}

	{
		map models/players/default/scan.jpg
		blendfunc add
		tcMod scroll 1 0
	}

}
