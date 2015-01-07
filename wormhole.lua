name = "Worm hole"
hero = {left=296, top=222, width=48, height=36}

function inward(rect1, rect2, offset)
	return { cycle=64, blendmode="OVR", route = {
		{ time = 0, rect=rect1, dimfade="FADE", twolor={255,255} },
		{ time =63, rect=rect2, dimfade="SNAP" },
		}, offset=offset	}
end
function outward(rect1, rect2, offset)
	return { cycle=32, blendmode="SUB", route = {
		{ time = 0, rect=rect1, dimfade="SNAP", twolor={52,12} },
		{ time = 1, rect=rect2, dimfade="FADE" },
		}, offset=offset	}
end

fsx = 640
fsy = 480
hsx = fsx/2
hsy = fsy/2
bx = 160
by = 120
sx = 80
sy = 60
boxes = 
{
	--background
	{ cycle=99, blendmode="OVR", route = {
		{ time = 0, rect={0,0,640,480}, twolor={175,65} },
		}	},
	--hurters
	inward( {-bx,	0,	bx,	fsy}, {hsx,	hsy,	sx,	0}, 0),
	inward( {fsx,	0,	bx,	fsy}, {hsx-sx,hsy,	sx,	0}, 16),
	inward( {0,		-by,fsx,by}, {hsx,	hsy,	0,	sy}, 8),
	inward( {0,		fsy,fsx,by}, {hsx,	hsy-sy,	0,	sy}, 24),
		--(repeated with +32 offset)
	inward( {-bx,	0,	bx,	fsy}, {hsx,	hsy,	sx,	0}, 32),
	inward( {fsx,	0,	bx,	fsy}, {hsx-sx,hsy,	sx,	0}, 48),
	inward( {0,		-by,fsx,by}, {hsx,	hsy,	0,	sy}, 24),
	inward( {0,		fsy,fsx,by}, {hsx,	hsy-sy,	0,	sy}, 56),
	--helpers
	outward( {-sx,	0,	sx,	fsy}, {hsx,		hsy-sy,	bx, by}, 0),
	outward( {fsx,	0,	sx,	fsy}, {bx,		hsy-sy,	bx, by}, 16),
	outward( {0,	-sy,fsx,sy}, {hsx-sx,	hsy,	bx, by}, 8),
	outward( {0,	fsy,fsx,sy}, {hsx-sx,	by,		bx, by}, 24),
}
