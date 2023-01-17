#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

int main()
{
    //------------------------------------------------------------
    // Setup
    //------------------------------------------------------------

#pragma region Setup


    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pick Up Sticks", sf::Style::None);

    srand(time(NULL));

    sf::Texture playerTexture;
    sf::Texture grassTexture;


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

    sf::Sprite playerSprite;
    sf::Sprite grassSprite;
    grassSprite.setTexture(grassTexture);
    playerSprite.setTexture(playerTexture);
    std::vector<sf::Sprite> grassSpriteVector;
    int numGrassSprites = 5;

    for (size_t i = 0; i < numGrassSprites; i++)
    {
        grassSprite.setPosition(sf::Vector2f(rand() % (window.getSize().x - grassTexture.getSize().x), rand() % (window.getSize().y - grassTexture.getSize().y)));
        grassSpriteVector.push_back(grassSprite);
    }

    //postion
    playerSprite.setPosition(sf::Vector2f(0.0f, 100.0f));

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
    // Drawing
    //------------------------------------------------------------

#pragma region Drawing


        window.clear(sf::Color(60, 150, 64));

        //draw all things
        for (size_t i = 0; i < grassSpriteVector.size(); i++)
        {
            window.draw(grassSpriteVector[i]);
        }
        window.draw(playerSprite);

        window.display();


#pragma endregion

    }

    return 0;
}