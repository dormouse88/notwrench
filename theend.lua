    y_margin = 50
    y_space = 40
    x_margin = 55
    x_space = 40
    lw = 150
    lh = 150
    pw = 50
    ph = 30
    col1 = x_margin
    col2 = x_margin + lw + x_space
    col3 = x_margin + (2*lw) + (2*x_space)
    row1 = y_margin
    row2 = y_margin + lh + (2*y_space)
function piece(rect1, xy)
	local rect2 = {rect1[1]+xy[1], rect1[2]+xy[2], rect1[3], rect1[4]}
	return { cycle=1600, blendmode="OVR", route = {
		{ time = 0,    rect=rect2, dimfade="FADE", twolor={0,0} },
		{ time = 600,  rect=rect1, dimfade="SNAP" },
		{ time = 800,  rect=rect1, dimfade="FADE" },
		{ time = 1400, rect=rect2, dimfade="SNAP" },
		}	}
end
name = "The End"
hero = {left=300, top=225, width=40, height=30}
boxes = {
	--background
	{ cycle=99, blendmode="OVR", route = {
		{ time = 0, rect={0,0,640,480}, twolor={0,255} },
		}	},
	--letter pieces ("the end")
	piece( {col1,row1,lw,ph}, {650,40} ), --#T
	piece( {col1+pw, row1, pw, lh}, {-1000,-400} ),
	piece( {col2, row1+2*ph, lw, ph}, {-900,800} ), --#H
	piece( {col2, row1, pw, lh}, {80,-230} ),
	piece( {col2+2*pw, row1, pw, lh}, {500,300} ),
	piece( {col3, row1, lw, ph}, {-900,300} ), --#E
	piece( {col3, row1, pw, lh}, {100,-600} ),
	piece( {col3, row1+4*ph, lw, ph}, {1200,400} ),
	piece( {col3, row1+2*ph, lw, ph}, {-300,-600} ),
	piece( {col1, row2, lw, ph}, {500,500} ), --#E
	piece( {col1, row2, pw, lh}, {-120,-1000} ),
	piece( {col1, row2+4*ph, lw, ph}, {100,300} ),
	piece( {col1, row2+2*ph, lw, ph}, {1200,-100} ),
	piece( {col2, row2, lw, ph}, {-2700,-5500} ), --#N
	piece( {col2, row2, pw, lh}, {-200,-450} ),
	piece( {col2+2*pw, row2, pw, lh}, {400,700} ),
	piece( {col3, row2, 2*pw, ph}, {240,-100} ), --#D
	piece( {col3, row2+4*ph, 2*pw, ph}, {-1200,100} ),
	piece( {col3, row2, pw, lh}, {-200,200} ),
	piece( {col3+2*pw, row2+ph, pw, 3*ph}, {-400,-800} ),
}