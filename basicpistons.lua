BLUE = {0,255}
RED = {255,0}
function box(x,y,w,h, col)
	return { cycle=60, blendmode="OVR", route = {
		{ time =  0, rect = {x,y[1],w,h[1]}, dimfade="FADE", twolor=col, colfade="SNAP" },
		{ time = 30, rect = {x,y[2],w,h[2]}, dimfade="FADE", },
		}	}
end

name = "Basic Pistons"
hero = { left=20, top=210, width=80, height=48 }
boxes =
{
	box(160,	{0,0},		160,	{480,0},	BLUE),
	box(160,	{480,0},	160,	{0,480},	RED),
	box(320,	{0,0},		160,	{0,480},	BLUE),
	box(320,	{0,480},	160,	{480,0},	RED),
}