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
    int kierros = 1;
    sf::RenderWindow window(sf::VideoMode(width, height), "SieniRTS", sf::Style::Default, contextSettings);
    window.setActive();
    
    
    sf::Texture sieniTex;
    sf::Texture houseTex;
    
    sieniTex.loadFromFile("resources/DefaultSieni.png");
    houseTex.loadFromFile("resources/Rakennus1.png");
    
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
    
    std::vector<Sieni> sienet;
    sienet.push_back(Sieni(&sieniTex, 300.0, 200.0, 300.0, 200.0, 0, 0, 0, 0, 0.0, 0.0, 8.0));


    
    std::vector<House> talot;
    talot.push_back(House(&houseTex, 0, 0, 0, 0, 0, 0));


    for (int i = -48; i <= width; i+=48){
        for (int j = 2*(i%96)/3-64; j <= height; j+=64){ // shifts every other line 32 px down
            
            if ( (i == 48*13 && 32*7  <= j && j <= 32*11) || (i == 48*14 && 32*12 <= j && j <= 32*14) ) continue;
            
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
              VÃ¤lilyÃ¤nnistÃ¤ tehrÃ¤Ã¤n talo
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
            
            // klikkauksesta ei tehrä enää siäniä
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
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                double mX = (sf::Mouse::getPosition(window).x)-8;
                double mY = (sf::Mouse::getPosition(window).y)-8;
                for (int i=0; i<sienet.size(); ++i){
                    sienet[i].setTarget(mX,mY);
                    sienet[i].pathFind();
                }
            }            
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                double mX = (sf::Mouse::getPosition(window).x);
                double taloX = (mX - ((int)mX % 48));
                double mY = (sf::Mouse::getPosition(window).y)-32*((int(taloX)%96)/48);
                double taloY = (mY - ((int)mY % 64))+((int(taloX)%96)/48)*32;
                if (sienet.size() >= 10){
                    talot.push_back(House(&houseTex, taloX, taloY, 0, 0, 0, 0));
                    talot.back().setPos(taloX, taloY);
                    for (int i=0; i<10; ++i){
                        sienet.erase(sienet.begin()+i);
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
            if (kierros%100 == 0){
                sienet.push_back(Sieni(&sieniTex,
                        talot[i].getX() + ((rand()&255)/255.0)*48,
                        talot[i].getY() + ((rand()&255)/255.0)*64,
                        talot[i].getX() + ((rand()&95)) - 24,
                        talot[i].getY() + ((rand()&127)) - 32,
                        0, 0, 0, 0, 0.0, 0.0, 8.0));
                sienet.back().pathFind();
            }
            
        }        
        
        for(int i=0; i<sienet.size(); ++i) {
            sienet[i].areWeThereYet();

            for(int j=0; j<sienet.size(); ++j) {
                if (i!=j) {
                    if (sienet[i].doesCollide(sienet[j])) {
                        sienet[i].stop();
                        sienet[i].KnockBack(sienet[j]);
                    }
                }
            }
            
            sienet[i].setPos(
                    sienet[i].getX() + sienet[i].getdx(),
                    sienet[i].getY() + sienet[i].getdy());
            
            if (sienet[i].railossa()) {
                sienet.erase(sienet.begin()+i);
                continue;
            }
            
            window.draw(sienet[i].getSprite());
        }
        
        window.display();
        sf::sleep(sf::milliseconds(50));
        ++kierros;
    }
    // close the program when the loop breaks
    return EXIT_SUCCESS;
}
#endif

