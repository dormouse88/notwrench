#include "Hero.h"

Hero::Hero()
	:_home(), _pos(), _size(), _vel(),
	_engine(0.f), _health(0.f), _chromaPower(255.f, 255.f, 255.f),
	inWinZone(false)
{
	LoadHome(_home, _size);
}

Hero::~Hero(void)
{}

void Hero::LoadHome(sf::Vector2f home, sf::Vector2f size) {
	_home = home;
	_pos = home;
	_size = size;
	_vel.x = 0.f; _vel.y = 0.f;
	inWinZone = false;

	chromagrid.resize(size.y);
	for (int i = 0; i<chromagrid.size(); i++) {
		chromagrid.at(i).resize(size.x);
	}
}

void Hero::Die() {
	_pos.x = _home.x;
	_pos.y = _home.y;
}

void Hero::DoStep(sf::FloatRect scr, BoxSeq & boxes) {
    //HANDLE KEYBOARD...
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )
		_vel.x -= _engine;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) )
		_vel.x += _engine;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
        _vel.y -= _engine;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )
		_vel.y += _engine;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) )
        Die();

    //APPLY DRAG...
    _vel *= 0.95f;

    //UPDATE POSITION...
	_pos += _vel;
	
    //BOUNDS CHECKING...
	const sf::FloatRect bb(_pos, _size);
	if (bb.left + bb.width > scr.left + scr.width) 
		inWinZone = true;
	else {
		if (bb.top + bb.height > scr.top + scr.height)
			_pos.y = scr.top + scr.height - bb.height;
		if (bb.left < scr.left)
			_pos.x = 0;
		if (bb.top < scr.top)
			_pos.y = 0;
	}

    //UPDATE CHROMAGRID
	for (int i = 0; i<chromagrid.size(); i++) {
		for (int j = 0; j<chromagrid.at(i).size(); j++) {
			chromagrid.at(i).at(j) = sf::Color::Black;
		}
	}
	sf::FloatRect heroFR(_pos, _size);
	for (BoxSeq::iterator itr = boxes.begin(); itr != boxes.end(); itr++) {
		sf::FloatRect boxFR = (*itr)->GetPos();
		sf::FloatRect intersect;
		if ( heroFR.intersects(boxFR, intersect) ) {
			//pseudo-draw into chromagrid...
			sf::Color boxC = (*itr)->GetCol();
			for (int rowi = intersect.top; rowi < intersect.top + intersect.height; rowi++) {
				for (int coli = intersect.left; coli < intersect.left + intersect.width; coli++) {
					try {
						sf::Color & cell = chromagrid.at(rowi - heroFR.top).at(coli - heroFR.left);
						std::string bm = (*itr)->GetBlendString();
						if (bm == SUB) {  //(Mechanics are actually subtractive)
							if (boxC.r > cell.r) cell.r = 0;
							else cell.r -= boxC.r;
							if (boxC.g > cell.g) cell.g = 0;
							cell.g -= boxC.g;
							if (boxC.b > cell.b) cell.b = 0;
							cell.b -= boxC.b;
						}
						else if (bm == ADD) {
							cell += boxC;
						}
						else {
							cell = boxC;
						}
					}
					catch( const std::out_of_range & e) { 
						//(vector out-of-range access due to floating point rounding errors)
					}
				}
			}
		}
	}

	//FIND AVERAGE CHROMA...
	int n = 0;
	sf::Vector3f sumColor;
	for (int i = 0; i<chromagrid.size(); i++) {
		for (int j = 0; j<chromagrid.at(i).size(); j++) {
			sf::Color thisCol = chromagrid.at(i).at(j);
			sumColor.x += thisCol.r;
			sumColor.y += thisCol.g;
			sumColor.z += thisCol.b;
			n++;
		}
	}
	_chromaPower.x = 255.f - (sumColor.x / n);
	_chromaPower.y = 255.f - (sumColor.y / n);
	_chromaPower.z = 255.f - (sumColor.z / n);

    //avg_color = pygame.transform.average_color(scr, self.rect)
	//_chromaPower = [255-c for c in avg_color]
	//_chromaPower.x = 120.f;
	//_chromaPower.y = 160.f;
	//_chromaPower.z = 200.f;

    //APPLY CHROMA POWERS...
	float & health_c = _chromaPower.x;
	float & spare_c = _chromaPower.y;
	float & move_c = _chromaPower.z;
    _engine = move_c * 0.001f;
    if (_engine < 0.01f)
        _engine = 0.f;
    _health += (health_c - 128.f)*0.08f;			//lower health if on below half color terrain (128)
    _health -= (_health - health_c) *0.03f;			//(naturally gravitate health toward terrain)
	_health = std::max(0.f, std::min(_health, 255.f));
    if (_health <= 0.f)
        Die();
}


void Hero::Draw(sf::RenderTarget & window)
{
	//Non-Scaling Way...
	//float minBorder = 0.f;
	//float maxBorder = std::min(_size.x, _size.y) / 2.f;
	//float border = minBorder + ( (maxBorder - minBorder) * (1.f - _health/255.f) ) ;

	sf::RectangleShape includingBorder;
	includingBorder.setPosition(_pos);
	includingBorder.setSize(_size);

	sf::RectangleShape excludingBorder(includingBorder);
	excludingBorder.setOrigin(_size / 2.f);
	excludingBorder.move(_size / 2.f);
	excludingBorder.scale(_health / 255.f, _health / 255.f);

	includingBorder.setFillColor(sf::Color::White);
	excludingBorder.setFillColor(sf::Color::Green);

	window.draw(includingBorder);
	window.draw(excludingBorder);
}			