function drop(x,y2,off)
	return { cycle=60, blendmode="OVR", route = {
		{ time=0,  rect={x,-30,64,48}, dimfade="FADE", twolor={100,190} },
		{ time=59, rect={x,y2,64,48}, dimfade="SNAP" },
		},	offset=off }
end

name = "Road"
hero = {left=20, top=400, width=40, height=30}
boxes = {
	--road
	{ cycle=99, blendmode="OVR", route = {
		{ time=0, rect={120,0,400,480}, twolor={215,240} },
		}	},
	--left killzone
	{ cycle=99, blendmode="OVR", route = {
		{ time=0, rect={0,0,120,360}, twolor={255,0} },
		}	},
	--right killzone
	{ cycle=99, blendmode="OVR", route = {
		{ time=0, rect={520,120,120,360}, twolor={255,0} },
		}	},
	--Non-overlapping set of drops...
	drop(150,580,0),
	drop(160,680,20),
	drop(170,780,10),
	drop(180,580,48),
	drop(200,780,25),
	drop(220,680,0),
	drop(230,800,30),
	drop(240,630,10),
	drop(260,640,50),
	drop(270,700,23),
	drop(290,680,40),
	drop(320,730,5),
	drop(330,630,32),
	drop(340,500,0),
	drop(350,830,12),
	drop(360,630,45),
	drop(370,730,20),
	drop(390,560,8),
	drop(410,880,25),
	drop(420,500,3),
	drop(430,700,40),
	drop(440,800,20),
}