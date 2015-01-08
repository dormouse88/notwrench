#include "App.h"

App::App(void)
	:groove(0), hero()
{
    window.create(sf::VideoMode(640, 480), "NotWrench");
	window.setMouseCursorVisible(false);
	//use one of these two:
	window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(45);

	levelPack.NextLevel(hero, boxes);
        soundGen.SetCallbacks(std::bind( &Hero::GetAudioModulation, &hero));
	Run();
}

App::~App(void)
{}

void App::Run()
{
    soundGen.play();
    while (window.isOpen())
    {
        BaseHandleInput();
        DoLogicAndDraw();
    }
    soundGen.stop();
}

void App::DoLogicAndDraw()
{
    window.clear();

    for (BoxSeq::iterator itr = boxes.begin(); itr != boxes.end(); itr++) {
        (*itr)->DoFrame(groove);
        (*itr)->Draw(window);
	}

    hero.DoStep(sf::FloatRect(sf::Vector2f(), window.getView().getSize() ), boxes);
    hero.Draw(window);

	window.display();

    if (hero.inWinZone) {
		levelPack.NextLevel(hero, boxes);
        groove = 0;
	}
}

void App::BaseHandleInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::KeyPressed)
		{
			if ((event.key.code == sf::Keyboard::F4) && (event.key.alt == true))
				window.close();
		}
	}
	if (	(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ) ||
			(sf::Keyboard::isKeyPressed(sf::Keyboard::Z) ) ||
			(sf::Keyboard::isKeyPressed(sf::Keyboard::X) ) ||
			(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) )		)
		groove++;
}


