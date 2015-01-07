BLUE = {0,255}
RED = {255,0}
MAG = {255,255}
function box(x,y,w,h, col)
	return { cycle=60, blendmode="OVR", route = {
		{ time =  0, rect = {x,y[1],w,h[1]}, dimfade="FADE", twolor=col, colfade="SNAP" },
		{ time = 30, rect = {x,y[2],w,h[2]}, dimfade="FADE", },
		}	}
end

name = "Power Pistons"
hero = { left=30, top=225, width=40, height=64 }
boxes =
{
	box(160,	{0,0},		160,	{0,240},	MAG),
	box(160,	{0,240},	160,	{240,240},	BLUE),
	box(160,	{240,480},	160,	{240,0},	MAG),
	box(320,	{0,0},		160,	{240,0},	MAG),
	box(320,	{240,0},	160,	{240,240},	RED),
	box(320,	{480,240},	160,	{0,240},	MAG),
			
	--sweeping safezone
	{ cycle=120, blendmode="SUB", route = {
		{ time = 0, 	rect={480,0,160,480}, 	dimfade="FADE", twolor={120,120} },
		{ time = 119, 	rect={0,0,160,480}, 	dimfade="SNAP", },
		}	},
}
