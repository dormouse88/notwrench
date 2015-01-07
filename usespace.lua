    col1 = 110
    col2 = 210
    col3 = 310
    col4 = 410
    col5 = 510
    row1 = 5
    row2 = 165
    row3 = 325
    lw = 80
    lh = 150

function deepcopy(orig)
	local copy
	if type(orig) == 'table' then
		copy = {}
		for orig_key, orig_value in next, orig, nil do        
			copy[deepcopy(orig_key)] = deepcopy(orig_value)
		end
		--setmetatable(copy, deepcopy(getmetatable(orig)))
	else
		copy = orig
	end
	return copy
end

function space(rect_in)
	return { cycle=99, blendmode="OVR", route = {
		{ time = 0, rect = rect_in, twolor={0,255} },
		}	}
end
function use(version, rect_in)
	local rect1 = deepcopy(rect_in)
	local rect2 = deepcopy(rect_in)
	rect2[1] = rect2[1] + 700 
	local rect3 = deepcopy(rect_in)
	if version == 1 then rect3[2] = rect3[2] - 300 end
	if version == 2 then rect3[1] = rect3[1] - 300 end
	if version == 3 then rect3[2] = rect3[2] + 300 end
	ret = { cycle=140, blendmode="OVR", route = {
		{ time = 0, rect = rect1, dimfade="FADE", twolor={255,0}, colfade="SNAP" },
		{ time = 80, rect = rect2, dimfade="SNAP", },
		{ time = 100, rect = rect3, dimfade="FADE", },
		}, offset=0	}
	if version == 2 then ret.blendmode = "ADD" end
	return ret
end
	
name = "Use Space"
hero = {left=20, top=210, width=80, height=60}
boxes =
{
	--background
	{ cycle=99, blendmode="OVR", route = {
		{ time = 0, rect={0,0,640,480}, twolor={140,100} },
		}	},
	--space
	space( {col1,row2,lw,30}),
	space( {col1,row2+60,lw,30}),
	space( {col1,row2+120,lw,30}),
	space( {col1, row2, 30, 60}),
	space( {col1+50, row2+60, 30, 60}),
	space( {col2, row2, lw, 30}),
	space( {col2, row2+60, lw, 30}),
	space( {col2, row2, 30, 150}),
	space( {col2+50, row2, 30, 60}),
	space( {col3, row2, lw, 30}),
	space( {col3, row2+60, lw, 30}),
	space( {col3, row2, 30, 150}),
	space( {col3+50, row2, 30, 150}),
	space( {col4, row2, lw, 30}),
	space( {col4, row2, 30, 150}),
	space( {col4, row2+120, lw, 30}),
	space( {col5, row2, lw, 30}),
	space( {col5, row2, 30, 150}),
	space( {col5, row2+120, lw, 30}),
	space( {col5, row2+60, lw, 30}),
    --use
	--u
	use(1, {col1, row1, 30, 150}),
	use(1, {col1+50, row1, 30, 150}),
	use(1, {col1, row1+120, lw, 30}),
	--s
	use(2, {col1, row2, lw, 30}),
	use(2, {col1, row2+60, lw, 30}),
	use(2, {col1, row2+120, lw, 30}),
	use(2, {col1, row2, 30, 60}),
	use(2, {col1+50, row2+60, 30, 60}),
	--e
	use(3, {col1, row3, lw, 30}),
	use(3, {col1, row3, 30, 150}),
	use(3, {col1, row3+120, lw, 30}),
	use(3, {col1, row3+60, lw, 30}),
}

