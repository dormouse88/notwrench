    num = 5
    t = 23
name = "Tall"
hero =  {left=((640/num)-40)/2, top=120, width=40, height=240}
boxes = {
	{ cycle=99, blendmode="OVR", route = {
		{ time=0, rect={ 0, 0, 640, 480}, twolor={180, 255} },
		}	},
}

function hurt(cyc, y, h)
	return { cycle=cyc, blendmode="SUB", route = {
		{ time=0,     rect={ 0,   y, 640/num, h}, dimfade="FADE", twolor={140, 0} },
		{ time=cyc-1, rect={ 640, y, 640/num, h}, dimfade="SNAP" },
		}	}
end
function help(cyc, y, h)
	return { cycle=cyc, blendmode="SUB", route = {
		{ time=0,     rect={ 0,   480-y-h, 640/num, h}, dimfade="FADE", twolor={0, 50} },
		{ time=cyc-1, rect={ 640, 480-y-h, 640/num, h}, dimfade="SNAP" },
		}	}
end

for i=1, num do
	i_ex = math.pow(2, i)
	ti = t * math.pow(2, (num-i))
	h = 480/i_ex
	y = 480 - (h*2)
	if i == num then h = h*2 end
	table.insert(boxes, hurt( ti*3, y, h) )
	table.insert(boxes, help( ti, y, h) )
end
