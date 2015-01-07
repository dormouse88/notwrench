#include "Box.h"
#include <iostream> //temp

Box::Box(void)
	:cycle(), blendMode(), offset()
{
}

Box::~Box(void) {}

void Box::DoFrame(unsigned int groove)
{
    unsigned int gc = (groove + offset) % cycle;
	positionAspect.UpdateActual(gc);
	colorAspect.UpdateActual(gc);
}

void Box::Draw(sf::RenderTarget & window)
{
	sf::RectangleShape theBox;
	sf::FloatRect pos = positionAspect.GetActual();
	theBox.setPosition(	pos.left, pos.top );
	theBox.setSize( sf::Vector2f(pos.width, pos.height) );
	sf::Color col = colorAspect.GetActual();
	theBox.setFillColor(col);
	window.draw(theBox, sf::RenderStates(blendMode) );
}

//void Box::DrawGL()
//{
//    // set the color to use in draw
//    glColor3f(0.5, 0.5, 0.0);       
//    // create a polygon ( define the vertexs) 
//    glBegin(GL_POLYGON); {           
//        glVertex2f(-0.5, -0.5);
//        glVertex2f(-0.5,  0.5);
//        glVertex2f( 0.5,  0.5);
//        glVertex2f( 0.5, -0.5);
//    } glEnd();
//}

void Box::LoadRoute(lua_State * L)
{
	{
		lua_getfield(L, -1, "cycle");
		cycle = lua_tonumber(L, -1);
		lua_pop(L,1);
	}
	{
		lua_getfield(L, -1, "blendmode");
                //SFML 2.1 code...
//		if (lua_tostring(L, -1) == ADD) blendMode = sf::BlendMode::BlendAdd;
//		else if (lua_tostring(L, -1) == SUB) blendMode = sf::BlendMode::BlendMultiply;
//		else blendMode = sf::BlendMode::BlendNone;
                //SFML 2.2 code...
                blendString = lua_tostring(L, -1);
		lua_pop(L,1);
                if (blendString == ADD)
                    blendMode = sf::BlendMode(sf::BlendMode::Factor::One, sf::BlendMode::Factor::One);
		else if (blendString == SUB)
                    blendMode = sf::BlendMode(sf::BlendMode::Factor::Zero, sf::BlendMode::Factor::OneMinusSrcColor, sf::BlendMode::Equation::Add);
		else
                    blendMode = sf::BlendNone;
	}
	std::vector<DataPoint<sf::FloatRect> > pRoute;
	std::vector<DataPoint<sf::Color> > cRoute;
	lua_getfield(L, -1, "route");
	int routeindex = 1;
	while (routeindex > 0) {
		lua_pushinteger(L, routeindex);
		lua_gettable(L, -2);
		if (lua_isnil(L, -1)) {
			routeindex = -1;
		}
		else {
			routeindex++;
			DataPoint<sf::FloatRect> pD;
			DataPoint<sf::Color> cD;
			bool saveP = true;
			bool saveC = true;
			{
				lua_getfield(L, -1, "time");
				pD.time = lua_tonumber(L, -1);
				cD.time = lua_tonumber(L, -1);
				lua_pop(L,1);
			}
			{
				lua_getfield(L, -1, "rect");
				if ( lua_isnil(L,-1) ) saveP = false;
				else {
					{
						lua_pushinteger(L, 1);//mn
						lua_gettable(L, -2);
						pD.value.left = lua_tonumber(L, -1);
						lua_pop(L,1);
					}
					{
						lua_pushinteger(L, 2);//mn
						lua_gettable(L, -2);
						pD.value.top = lua_tonumber(L, -1);
						lua_pop(L,1);
					}
					{
						lua_pushinteger(L, 3);//mn
						lua_gettable(L, -2);
						pD.value.width = lua_tonumber(L, -1);
						lua_pop(L,1);
					}
					{
						lua_pushinteger(L, 4);//mn
						lua_gettable(L, -2);
						pD.value.height = lua_tonumber(L, -1);
						lua_pop(L,1);
					}
				}
				lua_pop(L,1);
			}
			{
				lua_getfield(L, -1, "dimfade");
				if ( ! lua_isnil(L,-1) && lua_tostring(L, -1) == FADE ) pD.mustBlend = true;
				else pD.mustBlend = false;
				lua_pop(L,1);
			}
			{
				lua_getfield(L, -1, "twolor");
				if ( lua_isnil(L,-1) ) saveC = false;
				else {
					{
						lua_pushinteger(L, 1);//mn
						lua_gettable(L, -2);
						cD.value.r = lua_tonumber(L, -1);
						lua_pop(L,1);
					}
					{
						lua_pushinteger(L, 2);//mn
						lua_gettable(L, -2);
						cD.value.b = lua_tonumber(L, -1);
						lua_pop(L,1);
					}
				}
				lua_pop(L,1);
			}
			{
				lua_getfield(L, -1, "colfade");
				if ( ! lua_isnil(L,-1) && lua_tostring(L, -1) == FADE ) cD.mustBlend = true;
				else cD.mustBlend = false;
				lua_pop(L,1);
			}
			if (saveP) pRoute.push_back(pD);
			if (saveC) cRoute.push_back(cD);
		}
		lua_pop(L,1);
	}
	lua_pop(L,1);
	{
		lua_getfield(L, -1, "offset");
		offset = lua_tonumber(L, -1);
		lua_pop(L,1);
	}
	positionAspect.SetRoute(pRoute, cycle, offset);
	colorAspect.SetRoute(cRoute, cycle, offset);

	//for asp, dim_or_col in zip(self.aspects, [1,2]):
	//	route = asp.route
	//	ri = asp.ri
	//	#Create new gapless 'routes' for each aspect...
	//	for rn in raw_route:
	//		if rn[dim_or_col] != None:
	//			route.append( DataPoint_1A(rn[0], rn[dim_or_col][0], rn[dim_or_col][1] ) )

	//	#Calculate metadata (blends) for new 'route'...
	//	if len(route) < 1:
	//		raise "no values given for aspect!"
	//	elif len(route) == 1:
	//		route[0].blend = 'NO_BLEND'
	//	else:
	//		while ri().blend == 'NOT_SET':
	//			if ri().fade == FADE:
	//				#Calculate floating point blend rates...
	//				interval = (asp.ri.look_ahead().time - asp.ri().time) % self.cycle
	//				asp.ri().blend = [ (j-i)/interval for i,j in zip(ri().value, ri.look_ahead().value) ]
	//			else:
	//				ri().blend = 'NO_BLEND'
	//			next(ri)
	//		asp.ri.index = 0

	//	#Load DataPoint immediately prior to offset...
	//	while self.offset > ri.look_ahead().time and ri.look_ahead().time > ri().time:
	//		next(ri)
	//	asp.actual = copy.deepcopy(ri().value)
}                    
				

//Designed for a load of boxes (NOT CYCLIC)
//class IteratedGroup:
//    def __init__(self):
//        self.list_ = list()
//    def __iter__(self):
//        self.it = 0
//        self.list_ = [x for x in self.list_ if not(hasattr(x, 'kill_me') and x.kill_me == True)]
//        return self
//    def __next__(self):
//        try:
//            self.it += 1
//            return self.list_[self.it - 1]
//        except IndexError:
//            raise StopIteration
