// includes SFML in the project
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <windows.h>

#include "SFML/Graphics/Texture.hpp"

// main method
int main() {
  
    
  
    sf::ContextSettings contextSettings;  

    contextSettings.depthBits = 32;
    // window name
    sf::RenderWindow window(sf::VideoMode(640, 480), "SieniRTS", sf::Style::Default, contextSettings);
    window.setActive();

    // create clock
    sf::Clock clock;

    // tehr‰‰n si‰ni
    /*
     *
                 ___..._
         _,--'       "`-.
       ,'.  .            \
     ,/:. .     .       .'
     |;..  .      _..--'
     `--:...-,-'""\
             |:.  `.
             l;.   l
             `|:.   |
              |:.   `.,
             .l;.    j, ,
          `. \`;:.   //,/
           .\\)`;,|\'/(
            ` `itz `(,
     * 
     */

    sf::Texture texture1;
    if (!texture1.loadFromFile("resources/DefaultSieni.png")) {    
        // error...
    }
    sf::Sprite sieni;
    sieni.setScale(hahmoSize - sf::Vector2f(3, 3));
    sieni.setTexture(texture1);
    sieni.setColor(sf::Color(0, 255, 255));

    // main window loop
    while (window.isOpen()) {

        // scan for events and react to them
        sf::Event event;
        while (window.pollEvent(event)) {

            // close the window
            // if (event.type == sf::Event::Closed) {
            // window.close();
            // }(event.type == sf::Event::Closed)
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }

            // v√§lily√∂nti tekee sienisi√§ asioita
            if (((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) || (event.type == sf::Event::Closed)) {
                system("start chrome.exe http://sieni.es");
            }

            // mouse should do stuff
            if (event.type == sf::Event::MouseButtonPressed) { // is this the right event?

                sieni.setPosition(event.x,event.y);
                window.draw(sieni);
            }


        }
        // draw everything on the sreen
        window.display(); 
    }
    // close the program when the loop breaks
    return EXIT_SUCCESS;
}

