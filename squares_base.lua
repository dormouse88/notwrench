STEP_T = 30
LAST_STEP = 16

function routenode(step, BOX_W, BOX_H, BORDER, x_off, y_off, up_left, is_last)
	t = step * STEP_T
	local x,y,w,h
	if up_left then
		--UL...
		x = math.floor((step+2)/4) *BOX_W *-2
		y = math.floor((step+0)/4) *BOX_H *-1
		w = BOX_W
		h = BOX_H
	else
		--RD...
		x = math.floor((step+2)/4) *BOX_W *1
		y = math.floor((step+0)/4) *BOX_H *1
		w = BOX_W + math.floor(((step+2) % 4)/3) *BOX_W
		h = BOX_H + math.floor(((step+0) % 4)/3) *BOX_H
	end
	--Apply offset...
	x = x + x_off
	y = y + y_off
	--Apply border...
	x = x - BORDER
	y = y - BORDER
	w = w + (BORDER * 2)
	h = h + (BORDER * 2)
	--
	d_fade = "FADE"
	if step ~= 0 then
		c_comp = nil
	elseif up_left then
		c_comp = {165,250}
	else
		c_comp = {250,180}
	end
	if is_last then
		d_fade = "SNAP"
		t = t - 1
	end
	return { time = t, rect={x,y,w,h}, dimfade=d_fade, twolor=c_comp, colfade=nil }
end
function box(boxn, BOX_W, BOX_H, BORDER, up_left)
	local x_adj, y_adj
	if up_left then
		x_adj, y_adj = 0, 1
	else
		x_adj, y_adj = -4, -4
	end
	local y_off = (math.floor(boxn / IN_A_ROW) * BOX_H*2) +(BOX_H * y_adj)  -- +1, -4
	local x_off = ((boxn % IN_A_ROW) * BOX_W*2) + ((math.floor(boxn / IN_A_ROW) % 2) * BOX_W) +(BOX_W*x_adj) -- +0, -4
	local retroute = {}
	for step=0, LAST_STEP do
		table.insert( retroute, routenode(step, BOX_W, BOX_H, BORDER, x_off, y_off, up_left, step==LAST_STEP) )
		if (step+1)%4 == 0 then
			--Insert a duplicate node in the route...
			table.insert( retroute, routenode(step, BOX_W, BOX_H, BORDER, x_off, y_off, up_left, step==LAST_STEP) )
			if up_left then
				if  step>0 then
					--shift 1st of the two earlier
					retroute[#retroute - 1].time = retroute[#retroute - 1].time - (STEP_T/2)
				end
			else
				if step ~= LAST_STEP then
					--shift 2nd of the two later
					retroute[#retroute].time = retroute[#retroute].time + (STEP_T/2)
				end
			end
		end
	end
	return { cycle=STEP_T*(LAST_STEP+0), blendmode="OVR", route=retroute}
end
function squares_base(BOX_W, BOX_H, BORDER, red, blue)
	IN_A_ROW = math.ceil( 640/(BOX_W*2) ) +4
    TOTAL_ROWS = math.ceil( 480/(BOX_H*2) ) + 2
    NUM_BOXES = IN_A_ROW * TOTAL_ROWS
	local boxes = {
		--background
		{ cycle=99, blendmode="OVR", route = {
			{ time = 0, rect={0,0,640,480}, twolor={red,blue} },
			}	},
	}
	for boxn=0, NUM_BOXES do
		table.insert( boxes, box(boxn, BOX_W, BOX_H, BORDER, true) )
	end
	for boxn=0, NUM_BOXES do
		table.insert( boxes, box(boxn, BOX_W, BOX_H, BORDER, false) )
	end
	return boxes
end
