name = "Oscilloscope"
hero = {left=50, top=225, width=20, height=15}
boxes =
{
	--background
	{ cycle = 99, blendmode = "OVR", route = {
		{ time= 0, rect={0,0,640,480}, twolor={0,64} },
		}	},
	--obstacle
	{ cycle = 240, blendmode="OVR", route = {
		{ time= 0,   rect={80,0,120,240}, dimfade="FADE", twolor={255,255}, colfade="SNAP"},
		{ time= 120, rect={440,0,120,240}, dimfade="FADE" },
		}	},
	{ cycle = 240, blendmode="OVR", route = {
		{ time= 0,   rect={440,240,120,240}, dimfade="FADE", twolor={255,255}, colfade="SNAP"},
		{ time= 120, rect={80,240,120,240}, dimfade="FADE" },
		}	},
	{ cycle = 240, blendmode="OVR", route = {
		{ time= 0,   rect={80, 200,480,80}, dimfade="FADE", twolor={255,255}, colfade="SNAP"},
		{ time= 60,  rect={260,200,120,80}, dimfade="FADE" },
		{ time= 120, rect={80, 200,480,80}, dimfade="FADE" },
		{ time= 180, rect={260,200,120,80}, dimfade="FADE" },
		}	},
	{ cycle = 240, blendmode="OVR", route = {
		{ time= 0,   rect={120,220,400,40}, dimfade="FADE", twolor={0,255}, colfade="SNAP"},
		{ time= 60,  rect={300,220,40, 40}, dimfade="FADE" },
		{ time= 120, rect={120,220,400,40}, dimfade="FADE" },
		{ time= 180, rect={300,220,40, 40}, dimfade="FADE" },
		}	},
}