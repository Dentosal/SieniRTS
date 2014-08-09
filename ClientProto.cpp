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
    
    
    sf::Texture sieniTex;
    sf::Texture houseTex;
    
    sieniTex.loadFromFile("resources/DefaultSieni.png");
    houseTex.loadFromFile("resources/Rakennus1.png");
    
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
  
    sf::Texture hexaTexture;
    if (!hexaTexture.loadFromFile("resources/hexagonTile4.png")) {    
        // error...
    }
    
    //load sprites
    sf::Sprite hexa;
    hexa.setTexture(hexaTexture);
    std::vector<sf::Sprite> hexat;            
    sf::Sprite uusiHexa(hexa);
    
    std::vector<Sieni> sienet;
    sienet.push_back(Sieni(&sieniTex, 300.0, 200.0, 300.0, 200.0, 0, 0, 0, 0, 0.0, 0.0, 8.0));


    
    std::vector<House> talot;
    talot.push_back(House(&houseTex, 0, 0, 0, 0, 0, 0));


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
            /*
              Välilyännistä tehrään talo
                       .
                ('
                '|
                |'
               [::]
               [::]   _......_
               [::].-'      _.-`.
               [:.'    .-. '-._.-`.
               [/ /\   |  \        `-..
               / / |   `-.'      .-.   `-.
              /  `-'            (   `.    `.
             |           /\      `-._/      \
             '    .'\   /  `.           _.-'|
            /    /  /   \_.-'        _.':;:/
          .'     \_/             _.-':;_.-'
         /   .-.             _.-' \;.-'
        /   (   \       _..-'     |
        \    `._/  _..-'    .--.  |
         `-.....-'/  _ _  .'    '.|
                  | |_|_| |      | \  (o)
             (o)  | |_|_| |      | | (\'/)
            (\'/)/  ''''' |     o|  \;:;
             :;  |        |      |  |/)
         LGB  ;: `-.._    /__..--'\.' ;:
                  :;  `--' :;   :;  
             
             */
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {

                double mX = (sf::Mouse::getPosition(window).x);
                double taloX = (mX - ((int)mX % 48));
                double mY = (sf::Mouse::getPosition(window).y)-32*((int(taloX)%96)/48);
                double taloY = (mY - ((int)mY % 64))+((int(taloX)%96)/48)*32;
                
                talot.push_back(House(&houseTex, taloX, taloY, 0, 0, 0, 0));
                talot.back().setPos(taloX, taloY);
            }            
            
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::LControl)) {

                double mX = (sf::Mouse::getPosition(window).x);
                double taloX = (mX - ((int)mX % 48));
                double mY = (sf::Mouse::getPosition(window).y)-32*((int(taloX)%96)/48);
                double taloY = (mY - ((int)mY % 64))+((int(taloX)%96)/48)*32;
                for (int i = 0; i<talot.size(); ++i){
                    if (talot[i].getX()==taloX && talot[i].getY()==taloY){
                        talot.erase(talot.begin()+i);
                        for (int jtn=0; jtn<5; ++jtn) {
                            sienet.push_back(Sieni(&sieniTex, taloX+((rand()&255)/255.0)*48, taloY+((rand()&255)/255.0)*64, ((rand()&255)/255.0)*width, ((rand()&255)/255.0)*height, 0, 0, 0, 0, 0.0, 0.0, 8.0));
                            sienet.back().pathFind();
                        }
                    }
                }
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
                double mX = (sf::Mouse::getPosition(window).x)-8;
                double mY = (sf::Mouse::getPosition(window).y)-8;
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sienet.push_back(Sieni(&sieniTex, mX, mY, mX, mY, 0, 0, 0, 0, 0.0, 0.0, 8.0));
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
            window.draw(talot[i].getSprite());
        }        
        
        for(int i=0; i<sienet.size(); ++i) {
            sienet[i].areWeThereYet();
            sienet[i].collide();
            
            sienet[i].setPos(
                    sienet[i].getX() + sienet[i].getdx(),
                    sienet[i].getY() + sienet[i].getdy());
            
            window.draw(sienet[i].getSprite());
        }
        
        window.display();
        sf::sleep(sf::milliseconds(50));
    }
    // close the program when the loop breaks
    return EXIT_SUCCESS;
}
#endif

