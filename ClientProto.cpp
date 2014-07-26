// includes SFML in the project
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdlib.h>
#include "SFML/Graphics/Texture.hpp"
#include <vector>

// main method
int main() {
    
    sf::ContextSettings contextSettings;  
    
    contextSettings.depthBits = 32;
    // window name
    int height = 480;
    int width = 640;
    sf::RenderWindow window(sf::VideoMode(width, height), "SieniRTS", sf::Style::Default, contextSettings);
    window.setActive();
    

    // tehrään siäni
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

    sf::Texture sieniTexture;
    if (!sieniTexture.loadFromFile("resources/DefaultSieni.png")) {    
        // error...
    }
    sf::Texture hexaTexture;
    if (!hexaTexture.loadFromFile("resources/hexagonTile4.png")) {    
        // error...
    }
    
    sf::Sprite hexa;
    hexa.setTexture(hexaTexture);
    std::vector<sf::Sprite> hexat;            
    sf::Sprite uusiHexa(hexa);
    
    sf::Sprite sieni;
    sf::Vector2f hahmoSize(5, 5);
    sieni.setScale(hahmoSize - sf::Vector2f(2, 2));
    sieni.setTexture(sieniTexture);
    std::vector<sf::Sprite> sienet;
    
    for (int i = 0; i+48 <= width; i+=48){
        for (int j = 2*(i%96)/3; j+64 <= height; j+=64){
            uusiHexa.setPosition(i+1,j);
            hexat.push_back(uusiHexa);
        }
    }
    
    window.clear();
    // main window loop
    while (window.isOpen()) {

        // scan for events and react to them
        sf::Event event;
        while (window.pollEvent(event)) {

            // close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }

            // mouse should do stuff
            if (event.type == sf::Event::MouseButtonPressed) { // is this the right event?
                sf::Sprite uusiSieni(sieni);
                uusiSieni.setPosition((sf::Mouse::getPosition(window).x)-(sieni.getScale().x)*8,(sf::Mouse::getPosition(window).y)-(sieni.getScale().y*8));
                sienet.push_back(uusiSieni);
            }


        }
        // draw everything on the sreen
        
        for(int i=0; i<hexat.size(); ++i)
            window.draw(hexat[i]);
        for(int i=0; i<sienet.size(); ++i)
            window.draw(sienet[i]);
        window.display();
        sf::sleep(sf::milliseconds(200));
        
    }
    // close the program when the loop breaks
    return EXIT_SUCCESS;
}

