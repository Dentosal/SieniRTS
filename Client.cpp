// includes SFML in the project
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include "SFML/Graphics/Texture.hpp"
#include <vector>
#include <SFML/system.hpp>
#include "net.h"

// main method
int main() {
    
    sf::TcpSocket* socket = connect();
    socket->setBlocking(false);
    sf::ContextSettings contextSettings;  
    
    contextSettings.depthBits = 32;
    // window name
    int height = 480;
    int width = 640;
    sf::RenderWindow window(sf::VideoMode(width, height), "SieniRTS", sf::Style::Default, contextSettings);
    window.setActive();
    
    // create clock
    sf::Clock clock;

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
    if (!hexaTexture.loadFromFile("resources/hexagonTile3.png")) {    
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
    
    for (int i = 0; i < width; i+=24){
        for (int j = 2*(i%48)/3; j < height; j+=32){
            uusiHexa.setPosition(i,j);
            hexat.push_back(uusiHexa);
        }
    }
    
    
    // main window loop
    while (window.isOpen()) {
        window.clear();

        // scan for events and react to them
        sf::Event event;
        while (window.pollEvent(event)) {

            // close the window
            if (event.type == sf::Event::Closed) {
             window.close();
             }//(event.type == sf::Event::Closed)
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }

            // mouse should do stuff
            if (event.type == sf::Event::MouseButtonPressed) { // is this the right event?
                sf::Packet p;
                int x = sf::Mouse::getPosition(window).x;
                int y = sf::Mouse::getPosition(window).y;
                p << x << y;
                socket->send(p);
            }


        }
        // draw everything on the sreen
        
        for(int i=0; i<hexat.size(); ++i)
            window.draw(hexat[i]);
        for(int i=0; i<sienet.size(); ++i)
            window.draw(sienet[i]);
        window.display();
        sf::sleep(sf::milliseconds(200));
        sf::Packet p;
        sf::Socket::Status foo = socket->receive(p);
        if (foo == sf::Socket::Done){
            int x,y;
            p >> x >> y;
                sf::Sprite uusiSieni(sieni);
                uusiSieni.setPosition(x,y);
                sienet.push_back(uusiSieni);
            
        }
        
    }
    // close the program when the loop breaks
    return EXIT_SUCCESS;
}

