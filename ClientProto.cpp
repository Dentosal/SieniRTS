// includes SFML in the project
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdlib.h>
#include "SFML/Graphics/Texture.hpp"
#include <vector>
#include "sienet.h"

// main method
int main2() {
    
    sf::ContextSettings contextSettings;  
    
    contextSettings.depthBits = 32;
    // window name
    int height = 480;
    int width = 640;
    sf::RenderWindow window(sf::VideoMode(width, height), "SieniRTS", sf::Style::Default, contextSettings);
    window.setActive();
    
    std::vector<sf::Texture> sieniTyyppiTexture;
    sieniTyyppiTexture[0].loadFromFile("resources/DefaultSieni.png");    
    sieniTyyppiTexture[256].loadFromFile("resources/Rakennus1.png");    
    sieniTyyppiTexture[257].loadFromFile("resources/Rakennus2.png");  
    
    // tehrÃ¤Ã¤n siÃ¤ni
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
  
    sf::Texture hexaTexture;
    if (!hexaTexture.loadFromFile("resources/hexagonTile4.png")) {    
        // error...
    }
    
    //load sprites
    sf::Sprite hexa;
    hexa.setTexture(hexaTexture);
    std::vector<sf::Sprite> hexat;            
    sf::Sprite uusiHexa(hexa);
    
    sf::Sprite sieni;
    //sieni.setScale(sf::Vector2f(2,2));
    sieni.setTexture(sieniTyyppiTexture[0]);
    std::vector<sf::Sprite> sienet;
    sf::Sprite uusiSieni(sieni);
    
    for (int i = 0; i+48 <= width; i+=48){
        for (int j = 2*(i%96)/3; j+64 <= height; j+=64){ // shifts every other line 32 px down
            uusiHexa.setPosition(i+1,j);
            hexat.push_back(uusiHexa);
        }
    }
    
//    for (int i = 0; i <= 5; ++i){
//        uusiSieni.setPosition((sieni.getScale().x)*8,(sf::Mouse::getPosition(window).y)-(sieni.getScale().y*8));
//        sienet.push_back(uusiSieni);
//    }
    
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
            if (event.type == sf::Event::MouseButtonPressed) {
                uusiSieni.setPosition(
                        (sf::Mouse::getPosition(window).x)-(sieni.getScale().x)*8,
                        (sf::Mouse::getPosition(window).y)-(sieni.getScale().y*8));
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

