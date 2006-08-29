textures/common/nolightmap
{
	surfaceparm		nolightmap
}

textures/common/nodrawnonsolid
{
	surfaceparm		nonsolid
	surfaceparm		nodraw
}

textures/common/invisible
{
	surfaceparm nolightmap			
	{
		map		textures/common/invisible.tga
		alphaFunc	GE128
		depthWrite
		rgbGen	vertex
	}
}

textures/common/nodrop
{
	qer_nocarve
	qer_trans		0.5
	surfaceparm		trans
	surfaceparm		nonsolid
	surfaceparm		nomarks
	surfaceparm		nodrop
	surfaceparm		nolightmap
	surfaceparm		nodraw
	cull			disable
}

textures/common/weapclip
{
	qer_trans		0.40
	surfaceparm		trans
	surfaceparm		nomarks
	surfaceparm		nodraw
}

textures/common/clip
{
	qer_trans		0.40
	surfaceparm 	nolightmap
	surfaceparm		nomarks
	surfaceparm		nodraw
	surfaceparm		nonsolid
	surfaceparm		playerclip
	surfaceparm		noimpact
}

textures/common/full_clip
{
	qer_trans		0.40
	surfaceparm		nodraw
	surfaceparm		playerclip
}

textures/common/missileclip
{
	qer_trans		0.40
	surfaceparm		nodamage
	surfaceparm		nomarks
	surfaceparm		nodraw
	surfaceparm		playerclip
}

textures/common/cushion
{
	qer_nocarve
	qer_trans		0.50
	surfaceparm		nodraw
	surfaceparm		nomarks
	surfaceparm		nodamage
	surfaceparm		trans
}

textures/common/hint
{
	qer_nocarve
	qer_trans		0.30
	surfaceparm		nodraw
	surfaceparm		nonsolid
	surfaceparm		structural
	surfaceparm		trans
	surfaceparm		noimpact
}

textures/common/skip
{
	qer_nocarve
	qer_trans		0.40
	surfaceparm		nodraw
	surfaceparm		nonsolid
	surfaceparm		structural
	surfaceparm		trans
}

textures/common/slick
{
	qer_trans		0.50
	surfaceparm		nodraw
	surfaceparm 	nomarks
	surfaceparm 	trans
	surfaceparm 	slick
}

textures/common/origin
{
	qer_nocarve
	surfaceparm		nodraw
	surfaceparm		nonsolid
	surfaceparm		origin
}

textures/common/noimpact
{
	surfaceparm		noimpact
}

textures/common/areaportal
{
	qer_trans		0.50
	surfaceparm		nodraw
	surfaceparm		nonsolid
	surfaceparm		structural
	surfaceparm		trans
	surfaceparm		nomarks
	surfaceparm		areaportal
}

textures/common/clusterportal
{
	qer_trans		0.50
	surfaceparm		nodraw
	surfaceparm		nonsolid
	surfaceparm		trans
	surfaceparm		nomarks
	surfaceparm		detail
	surfaceparm		clusterportal
}

textures/common/donotenter
{
	qer_trans		0.50
	surfaceparm		nodraw
	surfaceparm		nonsolid
	surfaceparm		trans
	surfaceparm		nomarks
	surfaceparm		detail
	surfaceparm		donotenter
}

textures/common/trigger
{
	qer_nocarve
	qer_trans		0.50
	surfaceparm		nodraw
}

textures/common/caulk
{
	surfaceparm		nodraw
	surfaceparm		nomarks
	surfaceparm		nolightmap
}

textures/common/nodraw
{
	surfaceparm		nodraw
	surfaceparm		nonsolid
	surfaceparm		trans
	surfaceparm		nomarks
}
