name = "Gate"
hero = {left=30, top=100, width=40, height=16}

function corner(bottom, offset)
	ret = { cycle=600, blendmode="ADD", route = {
		{ time=0,   rect={640,bottom*480, 0,  0  }, dimfade="FADE", twolor={195,30} },
		{ time=180, rect={360,bottom*80,  280,400}, dimfade="FADE" },
		{ time=320, rect={60, bottom*320, 480,160}, dimfade="FADE" },
		{ time=480, rect={160,bottom*180, 480,300}, dimfade="FADE" },
		},	offset=offset}
	return ret
end
boxes = 
{
	--the four corner zones
	corner(0, 0),
	corner(0, 320),
	corner(1, 480),
	corner(1, 180),
	--the two central rectangles
	{ cycle=360, blendmode="SUB", route = {
		{ time = 0,   rect={560,120,80,240}, dimfade="FADE", twolor={170,190} },
		{ time = 240, rect={360,120,80,240}, dimfade="FADE" },
		}	},
	{ cycle=120, blendmode="ADD", route = {
		{ time = 0,   rect={540,100,100,280}, dimfade="FADE", twolor={85,190} },
		{ time = 80,  rect={340,100,100,280}, dimfade="FADE" },
		}	},
}