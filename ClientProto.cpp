#include <SFML/Window.hpp>

int main() {
  
  sf::Window window(sf::VideoMode(640, 480), "SieniRTS", sf::Style::Default, contextSettings);
  window.setActive();
  
  sf::Clock clock;
  
  while (window.isOpen) {
    sf:Event event;
    
    while (window.pollEvent(event)) {

      if (event.type == sf::Event::Closed) {
	window.close();
      }

      if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
	window.close();
      }

    }
    
    window.update; 
  }
  
  return EXIT_SUCCESS;
}

