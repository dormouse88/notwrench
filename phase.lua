function slow(offse)
	return { cycle=90, blendmode="SUB", route = {
		{ time=0,  rect={-80,80,80,320}, dimfade="FADE", twolor={255,77} },
		{ time=89, rect={640,80,80,320}, dimfade="SNAP" },
		}, offset=offse	}
end
function fast(offse)
	return { cycle=60, blendmode="ADD", route = {
		{ time=0,  rect={-80,40,80,400}, dimfade="FADE", twolor={148,128} },
		{ time=59, rect={640,40,80,400}, dimfade="SNAP" },
		}, offset=offse	}
end

name = "Phase"
hero = {left=10, top=160, width=40, height=160}
boxes = 
{
	--background
	{ cycle=99, blendmode="OVR", route = {
		{ time=0, rect={0,0,640,480}, twolor={178,255} },
		}	},
	--slow short bars
	slow(0),
	slow(30),
	slow(60),
	--fast long bars
	fast(0),
	fast(20),
	fast(40),
}