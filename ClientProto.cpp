// includes SFML in the project
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdlib.h>
#include "SFML/Graphics/Texture.hpp"
#include <vector>
#include "sienet.h"
#include <iostream>
using namespace std;

// main method
#define TRUE 1
#ifdef TRUE
//ifdef SIENI_PROTO
int main() {
    sf::ContextSettings contextSettings;  
    
    contextSettings.depthBits = 32;
    // window name
    int height = 720;
    int width = 960;
    sf::RenderWindow window(sf::VideoMode(width, height), "SieniRTS", sf::Style::Default, contextSettings);
    window.setActive();
    
    std::vector<sf::Texture> sieniTyyppiTexture(66);
    sieniTyyppiTexture[0].loadFromFile("resources/DefaultSieni.png");    
    sieniTyyppiTexture[64].loadFromFile("resources/Rakennus1.png");    
    sieniTyyppiTexture[65].loadFromFile("resources/Rakennus2.png");  
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

    
    sf::Sprite sieniSprite;
    //sieni.setScale(sf::Vector2f(2,2));
    sieniSprite.setTexture(sieniTyyppiTexture[0]);
    std::vector<sf::Sprite> sieniSpritet;
    sf::Sprite uusiSieniSprite(sieniSprite);
    sieniSpritet.push_back(uusiSieniSprite);
    
    std::vector<Sieni> sienet;
    sienet.push_back(Sieni(300.0, 200.0, 300.0, 200.0, 0, 0, 0, 0, 0.0, 0.0, 8.0));
    Sieni uusiSieni;
    
    
    sf::Sprite taloSprite;
    taloSprite.setScale(sf::Vector2f(5,5));
    taloSprite.setTexture(sieniTyyppiTexture[64]);
    std::vector<sf::Sprite> taloSpritet;
    sf::Sprite uusiTaloSprite(taloSprite);
    taloSpritet.push_back(uusiTaloSprite);
    taloSpritet[0].setPosition(300.0,200.0);
    
    std::vector<House> talot;
    talot.push_back(House(sieniTyyppiTexture[64],300.0,200.0,0,0,0,0));
    House uusiTalo(sieniTyyppiTexture[64]);
    
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
            
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {
                double mX = (sf::Mouse::getPosition(window).x)-(taloSprite.getScale().x)*8;
                double mY = (sf::Mouse::getPosition(window).y)-(taloSprite.getScale().y*8);
                sf::Packet p;
                    uusiTalo.setPacket(p << 10         // purkkaa tulossa
                            << mX << mY // x ja y
                            << 0 << 0 << 0 << 0     // hp, state, team, type
                            );
                    uusiTalo.setPos(mX, mY);
                    uusiTaloSprite.setPosition(mX, mY);
                    talot.push_back(uusiTalo);
                    taloSpritet.push_back(uusiTaloSprite);
            }
            
            // klikkauksesta tehrään siäni
            /*
                     .-'~~~-.          
                   .'o  oOOOo`.   
                  :~~~-.oOo   o`.  
                   `. \ ~-.  oOOo. 
                     `.; / ~.  OO: 
                     .'  ;-- `.o.'
                    ,'  ; ~~--'~  
                    ;  ;      
                _\\;_\\//_
                ==------===    */
            if (event.type == sf::Event::MouseButtonPressed) {
                double mX = (sf::Mouse::getPosition(window).x)-(sieniSprite.getScale().x*8);
                double mY = (sf::Mouse::getPosition(window).y)-(sieniSprite.getScale().y*8);
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Packet p;
                    uusiSieni.setPacket(p << 10         // purkkaa tulossa
                            << mX << mY             // x ja y
                            << mX << mY             // tx ja ty
                            << 0 << 0 << 0 << 0     // hp, state, team, type
                            << 0.0 << 0.0 << 8.0    // dx, dy, speed
                            );
                    sienet.push_back(uusiSieni);
                    sieniSpritet.push_back(uusiSieniSprite);
                } 
                else {
                    for (int i=0; i<sienet.size(); i++){
                        sienet[i].setTarget(mX,mY);
                        sienet[i].pathFind();
                    }
                }
            }


        }
        // draw everything on the screen
        
        window.clear();
        for(int i=0; i<hexat.size(); ++i)
            window.draw(hexat[i]);
        
        for(int i=0; i<talot.size(); ++i) {
            window.draw(taloSpritet[i]);
        }        
        
        for(int i=0; i<sienet.size(); ++i) {
            sienet[i].areWeThereYet();
            
            sienet[i].setPos(
                    sienet[i].getX() + sienet[i].getdx(),
                    sienet[i].getY() + sienet[i].getdy());
            sieniSpritet[i].setPosition(sienet[i].getX(), sienet[i].getY());
            
            window.draw(sieniSpritet[i]);
        }
        
        window.display();
        sf::sleep(sf::milliseconds(50));
    }
    // close the program when the loop breaks
    return EXIT_SUCCESS;
}
#endif

