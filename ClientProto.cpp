#include <SFML/Window.hpp>

int main()
{
  
  sf::Window window(sf::VideoMode(640, 480), "SieniRTS", sf::Style::Default, contextSettings);
  window.setActive();
  
  while (window.isOpen) {
    
    window.update; 
  }
  
  return EXIT_SUCCESS;
}

