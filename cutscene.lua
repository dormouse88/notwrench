	red = {255,0}
	blue  = {0,255}

function mrstop(rect1, x, y)
	local rect2 = {x, y, rect1[3], rect1[4] }
	return { cycle=300, blendmode="OVR", route = {
		{ time =  0, rect=rect1, dimfade="SNAP", twolor={228,228} },
		{ time =100, rect=rect1, dimfade="FADE" },
		{ time =140, rect=rect2, dimfade="SNAP" },
		}	}
end
function mrgun(rect2)
	local rect1 = {rect2[1] - 400, rect2[2], rect2[3], rect2[4] }
	return { cycle=300, blendmode="OVR", route = {
		{ time =  0, rect=rect1, dimfade="FADE", twolor={20,200} },
		{ time = 80, rect=rect2, dimfade="SNAP" },
		}	}
end	

name = "Cutscene"
hero = {left=50, top=50, width=48, height=36}
boxes = 
{
	--sky
	{ cycle=99, blendmode="OVR", route = {
		{ time=0, rect={0,0,640,400}, twolor={160,180} },
		}	},
	--ground
	{ cycle=99, blendmode="OVR", route = {
		{ time=0, rect={0,400,640,80}, twolor={180,255} },
		}	},
	--laser
	{ cycle=300, blendmode="OVR", route = {
		{ time=0,  rect={230,210,170,30}, twolor=red },
		{ time=2,  twolor=blue },
		{ time=4,  twolor=red },
		{ time=6,  twolor=blue },
		{ time=8,  twolor=red },
		{ time=10, twolor=blue },
		{ time=12, twolor=red },
		{ time=14, twolor=blue },
		{ time=16, twolor=red },
		{ time=18, twolor=blue },
		{ time=20, rect={0,0,0,0} },
		}, offset=210	},
--                                              ##
--                                          #   ##   #
--                                          ##########
--                                              ##
--                                              ##
--                                             ####
--                                             #  #
--                                            ##  ##
	--Mr stop...
	mrstop( {400,20,80,240}, 500, -600), --head and torso
	mrstop( {300,120,280,40}, 1300, -120), --arms
	mrstop( {380,260,120,40}, 1380, -1000), --knees
	mrstop( {380,300,50,100}, 980, 100), --left leg
	mrstop( {450,300,50,100}, 1450, 200), --right leg
--                                                ##     
--                                               ###########
--                                                ####
--                                                ##
--                                                #####
--                                                ## ##
--                                              #### ##
	--Mr gun...
	mrgun( {60,160,60,160} ), --head and torso
	mrgun( {30,210,200,30} ), --gun
	mrgun( {120,230,50,30} ), --stock
	mrgun( {60,320,30,60} ), --back thigh
	mrgun( {20,380,70,20} ), --back calf
	mrgun( {90,320,60,30} ), --front thigh
	mrgun( {120,350,30,50} ), --front calf
}