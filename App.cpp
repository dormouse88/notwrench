#include "App.h"
#include <iostream>

App::App(void)
    :groove(0), hero(), quitYet(false)
{
    window.create(sf::VideoMode(640, 480), "NotWrench");
    window.setMouseCursorVisible(false);
    //use one of these two:
    //window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(45);
    
    preShader.create(640, 480);
    shader.loadFromFile("postfx.frag", sf::Shader::Fragment);
    levelPack.NextLevel(hero, boxes);
    soundGen.SetCallbacks(std::bind( &Hero::GetEngine, &hero), std::bind( &Hero::GetHealth, &hero), std::bind( &LevelPack::GetLevel, &levelPack) );
    //Run();
}

App::~App(void)
{}

void App::Run()
{
    soundGen.play();
    while (quitYet == false)
    {
        BaseHandleInput();
        DoLogicAndDraw();
    }
    soundGen.stop();
    window.close();
}

void App::DoLogicAndDraw()
{
    preShader.clear();
    window.clear();

    for (BoxSeq::iterator itr = boxes.begin(); itr != boxes.end(); itr++) {
        (*itr)->DoFrame(groove);
        (*itr)->Draw(preShader);
    }

    hero.DoStep(sf::FloatRect(sf::Vector2f(), window.getView().getSize() ), boxes);
    hero.Draw(preShader);

    preShader.display();

    sf::Sprite spr(preShader.getTexture());
    shader.setParameter("texture", sf::Shader::CurrentTexture);
    shader.setParameter("pixel_threshold", (hero.GetHealth() * 0.03) );
    shader.setParameter("blur_radius", hero.GetEngine() * 0.06);
//    shader.setParameter("edge_threshold", 1.0 - (hero.GetEngine() * 0.99) );
//    shader.setParameter("blink_alpha", 1.0 - hero.GetHealth() * 0.8);
    window.draw(spr, &shader);
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
            quitYet = true;
        if (event.type == sf::Event::KeyPressed)
        {
            if ((event.key.code == sf::Keyboard::F4) && (event.key.alt == true))
                quitYet = true;
            if ((event.key.code == sf::Keyboard::N) && (event.key.alt == true))
            {
                levelPack.NextLevel(hero, boxes);
                groove = 0;
            }
        }
    }
    if (	(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ) ||
                    (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) ) ||
                    (sf::Keyboard::isKeyPressed(sf::Keyboard::X) ) ||
                    (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) )		)
            groove++;
}


