#include "App.h"
#include <iostream>

const int SOUND_STEPS = 3;
const int BLUR_STEPS = 3;
const int JAGGY_STEPS = 3;
const int X_DIM = 640;
const int Y_DIM = 480;


App::App(void)
    :groove(0)
    ,hero()
    ,quitYet(false)
    ,fullScreen(false)
    ,soundMult(SOUND_STEPS)
    ,blurMult(BLUR_STEPS)
    ,jaggyMult(JAGGY_STEPS)
{
    CreateWindow(false);
    preShader.create(X_DIM, Y_DIM);
    shader.loadFromFile("postfx.frag", sf::Shader::Fragment);
    levelPack.NextLevel(hero, boxes);
    soundGen.SetCallbacks(std::bind( &Hero::GetEngine, &hero), std::bind( &Hero::GetHealth, &hero), std::bind( &LevelPack::GetLevel, &levelPack) );
    //Run();
}

App::~App(void)
{}

void App::CreateWindow(bool full)
{
    sf::Uint32 style;
    if (full) {
        style = sf::Style::None;
        window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "NotWrench", style);
    }
    else {
        style = sf::Style::Default;
        window.create(sf::VideoMode(X_DIM, Y_DIM), "NotWrench", style);
    }
    window.setMouseCursorVisible(false);
    //use one of these two:
    //window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(45);
    
    sf::View view(sf::FloatRect(0, 0, X_DIM, Y_DIM));
    window.setView(view);
}

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
    shader.setParameter("pixel_threshold", hero.GetHealth() * 0.03 * ((float)jaggyMult / (float)JAGGY_STEPS) );
    shader.setParameter("blur_radius", hero.GetEngine() * 0.06 * ((float)blurMult / (float)BLUR_STEPS) );
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
            if ((event.key.code == sf::Keyboard::Return) && (event.key.alt == true))
            {
                //toggle fullscreen
                fullScreen = ! fullScreen;
                CreateWindow(fullScreen);
            }
            if ((event.key.code == sf::Keyboard::M))
            {
                //cycle mute
                soundMult++;
                if (soundMult > SOUND_STEPS)
                    soundMult = 0;
                soundGen.setVolume(100.f * (float)soundMult / (float)SOUND_STEPS);
            }
            if ((event.key.code == sf::Keyboard::B))
            {
                //cycle blur shader
                blurMult++;
                if (blurMult > BLUR_STEPS)
                    blurMult = 0;
            }
            if ((event.key.code == sf::Keyboard::V))
            {
                //cycle jaggy shader
                jaggyMult++;
                if (jaggyMult > JAGGY_STEPS)
                    jaggyMult = 0;
            }
        }
    }
    if (	(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ) ||
                    (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) ) ||
                    (sf::Keyboard::isKeyPressed(sf::Keyboard::X) ) ||
                    (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) )		)
            groove++;
}


