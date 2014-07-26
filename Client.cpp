#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "net.h"

int main()
{
    connect();


    // Request a 32-bits depth buffer when creating the window
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 32;

    // Create the main window
    sf::Window window(sf::VideoMode(640, 480), "SieniRTS", sf::Style::Default, contextSettings);





    // Create a clock for measuring the time elapsed
    sf::Clock clock;

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

            // Escape key: exit
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window.close();

        }

        // Finally, display the rendered frame on screen
        window.display();
    }

    return EXIT_SUCCESS;
}
