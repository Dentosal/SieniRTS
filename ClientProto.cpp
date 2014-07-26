// includes SFML in the project
#include <SFML/Window.hpp>
#include <windows.h>

// main method
int main() {
  
  // window name
  sf::Window window(sf::VideoMode(640, 480), "SieniRTS", sf::Style::Default, contextSettings);
  window.setActive();
  
  // create clock
  sf::Clock clock;
  
  // main window loop
  while (window.isOpen) {

    // scan for events and react to them
    sf:Event event;
    while (window.pollEvent(event)) {

      // close the window
      if (event.type == sf::Event::Closed) {
	window.close();
      }
      if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
	window.close();
      }
      
      // v�lily�nti tekee sienisi� asioita
      if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
	system("chrome.exe http://sieni.es");
      }

      // mouse should do stuff
      if (event.type == sf::Event::MousePressed) { // is this the right event?
	// TODO: do stuff
      }
	

    }
    // draw everything on the sreen
    window.update; 
  }
  // close the program when the loop breaks
  return EXIT_SUCCESS;
}

