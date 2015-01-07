function box(rect_in, col, bm)
	bm = bm or "OVR"
	return { cycle=99, blendmode=bm, route = {
		{ time=0, rect=rect_in, twolor=col },
		}	}
end

RED = {255,0}
BLUE = {0,255}
ADD = "ADD"
barw = 180
barh = 30

name = "Magnet"
hero = {left=300, top=220, width=40, height=40}
boxes =
{
	--magnet
	box( {180,110,180,110}, RED ),
	box( {180,260,180,110}, RED ),
	box( {340,110,120,260}, RED ),
	--bars
	box( {0, 110, barw, barh}, BLUE),
	box( {0, 150, barw, barh}, BLUE),
	box( {0, 190, barw, barh}, BLUE),
	box( {0, 260, barw, barh}, BLUE),
	box( {0, 300, barw, barh}, BLUE),
	box( {0, 340, barw, barh}, BLUE),
	--rectangles
	box( {520, 10, 100, 180}, RED),
	box( {520, 290, 100, 180}, RED),
	box( {540, 0, 100, 140}, BLUE, ADD),
	box( {540, 340, 100, 140}, BLUE, ADD),
}
