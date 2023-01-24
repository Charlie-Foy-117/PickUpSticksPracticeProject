#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <cmath>

int main()
{
    //------------------------------------------------------------
    // Setup
    //------------------------------------------------------------

#pragma region Setup


    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pick Up Sticks", sf::Style::None);

    srand(time(NULL));

    //Textures

    sf::Texture playerTexture;
    sf::Texture grassTexture;
    sf::Texture stickTexture;

    //Check for texture img

    if (!playerTexture.loadFromFile("Assets/Player_Stand.png"))
    {
        //error
        std::cout << "Texture load failed for Assets/Player_Stand.png" << std::endl;
    }
    else
    {
        std::cout << "Texture load was successful for Assets/Player_Stand.png" << std::endl;
    }

    if (!grassTexture.loadFromFile("Assets/Grass.png"))
    {
        //error
        std::cout << "Texture load failed for Assets/Grass.png" << std::endl;
    }
    else
    {
        std::cout << "Texture load was successful for Assets/Grass.png" << std::endl;
    }

    if (!stickTexture.loadFromFile("Assets/Stick.png"))
    {
        //error
        std::cout << "Texture load failed for Assets/Stick.png" << std::endl;
    }
    else
    {
        std::cout << "Texture load was successful for Assets/Stick.png" << std::endl;
    }

    //Sprites
    sf::Sprite playerSprite;
    sf::Sprite grassSprite;
    sf::Sprite stickSprite;

    //Player Sprite
    sf::Vector2f playerPosition(100.0f, 100.0f);

    playerSprite.setTexture(playerTexture);

    playerSprite.setPosition(playerPosition);
    playerSprite.setOrigin((float)(playerTexture.getSize().x / 2), (float)(playerTexture.getSize().y / 2));

    grassSprite.setTexture(grassTexture);
    stickSprite.setTexture(stickTexture);


    //Grass Sprite

    std::vector<sf::Sprite> grassSpriteVector;
    size_t numGrassSprites = 15;

    for (size_t i = 0; i < numGrassSprites; ++i)
    {
        grassSprite.setOrigin((grassTexture.getSize().x / 2.0f), (grassTexture.getSize().y / 2.0f));
        grassSprite.setPosition(sf::Vector2f((float)(rand() % (window.getSize().x - grassTexture.getSize().x)), (float)(rand() % (window.getSize().y - grassTexture.getSize().y))));
        grassSprite.setColor(sf::Color(0, rand() % 255, 0));

        int scaleTen = 5 + rand() % 10;
        float scale = scaleTen / 10.0f;
        grassSprite.setScale(scale, scale);
        grassSpriteVector.push_back(grassSprite);
    }


    //Stick Sprite

    std::vector<sf::Sprite> stickSpriteVector;
    size_t numStickSprites = 1;

    for (size_t i = 0; i < numStickSprites; ++i)
    {
        stickSprite.setOrigin((stickTexture.getSize().x / 2.0f), (stickTexture.getSize().y / 2.0f));
        stickSprite.setPosition(sf::Vector2f((float)(rand() % (window.getSize().x - stickTexture.getSize().x)), (float)(rand() % (window.getSize().y - stickTexture.getSize().y))));
        stickSprite.setRotation((float)(rand()% 360));
        stickSpriteVector.push_back(stickSprite);
    }


    //colour example
    //playerSprite.setColor(sf::Color::Cyan);

    //rotation example
    //playerSprite.setRotation(90);

    //scale example
    //playerSprite.setScale(sf::Vector2f(3.0f, 3.0f));

    //origin example
    //playerSprite.setOrigin((float)(playerTexture.getSize().x / 2), (float)(playerTexture.getSize().y / 2));



    //FONT
    //Load font
    sf::Font gameFont;
    gameFont.loadFromFile("Assets/GameFont.ttf");

    //Create text objects
    sf::Text gameTitle;
    gameTitle.setFont(gameFont);
    gameTitle.setString("Pick Up Sticks");
    float textWidth = gameTitle.getLocalBounds().width;
    gameTitle.setPosition(window.getSize().x / 2.0f - textWidth / 2.0f, 10.0f);

    gameTitle.setFillColor(sf::Color::Black);

    
    sf::Text scoreLabel;
    int score = 0;

    std::stringstream ss;
    ss << "Score = " << score;
    scoreLabel.setFont(gameFont);
    scoreLabel.setString(ss.str());

    float scoreLabelWidth = scoreLabel.getLocalBounds().width;
    scoreLabel.setPosition(window.getSize().x - scoreLabelWidth, 10.0f);
    



    //Sound
    sf::SoundBuffer startSFXBuffer;
    startSFXBuffer.loadFromFile("Assets/Start.wav");

    sf::Sound startSFX;
    startSFX.setBuffer(startSFXBuffer);
    startSFX.play();
    
    sf::Music gameMusic;
    gameMusic.openFromFile("Assets/GameMusic.OGG");
    gameMusic.setLoop(true);
    gameMusic.play();

    //Positioning
    float xDir = (10 - rand() % 21)/10.0f;
    float yDir = (10 - rand() % 21)/10.0f;
    sf::Vector2f direction(xDir, yDir);

   
    bool dashPressedLastFrame = false;

#pragma endregion

    
    while (window.isOpen())
    {

    //------------------------------------------------------------
    // Event Polling
    //------------------------------------------------------------

#pragma region Event Polling


        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }

            if (event.type == sf::Event::Closed)
                window.close();
        }

#pragma endregion


    //------------------------------------------------------------
    // Updating
    //------------------------------------------------------------

#pragma region Updating

        //movement
        int player1Controller = 1;

        direction.x = 0;
        direction.y = 0;
        
        if (sf::Joystick::isConnected(1))
        {
            
            
            float axisX = sf::Joystick::getAxisPosition(player1Controller, sf::Joystick::X);
            float axisY = sf::Joystick::getAxisPosition(player1Controller, sf::Joystick::Y);

            float deadZone = 25;

            if (abs(axisX) > deadZone || abs(axisY) > deadZone)
            {
               direction.x = axisX / 100.0f;
               direction.y = axisY / 100.0f;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            direction.x = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            direction.x = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            direction.y = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            direction.y = 1;
        }

        sf::Vector2f newPosition = playerSprite.getPosition() + direction * 0.1f;
        playerSprite.setPosition(newPosition);

        //dashing/blink

        bool dashPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(player1Controller, 0);

        if (dashPressed && !dashPressedLastFrame)
        {
            sf::Vector2f blinkPosition = playerSprite.getPosition() + direction * 100.0f;
            playerSprite.setPosition(blinkPosition);
        }

        dashPressedLastFrame = dashPressed;

        //spawn a stick with mouse click

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            //getmouse position
            //get local mouse position (relative to window)
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);
            sf::Vector2f mousePositonFloat = (sf::Vector2f)localPosition;
            //Spawn a stick at that position
            stickSprite.setPosition(mousePositonFloat);
            stickSpriteVector.push_back(stickSprite);
        }

     


#pragma endregion


    //------------------------------------------------------------
    // Drawing
    //------------------------------------------------------------

#pragma region Drawing


        window.clear(sf::Color(60, 150, 64));

        //draw all things
        for (size_t i = 0; i < grassSpriteVector.size(); i++)
        {
            window.draw(grassSpriteVector[i]);
        }

        for (size_t i = 0; i < stickSpriteVector.size(); i++)
        {
            window.draw(stickSpriteVector[i]);
        }

        window.draw(playerSprite);
        window.draw(scoreLabel);
        window.draw(gameTitle);
        window.display();


#pragma endregion
        
    }

    return 0;
}