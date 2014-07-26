// include SFML
#include <SFML/Network.hpp>
// include printing
#include <IOStream>
#include <String>
#include <sstream>

sf::TcpSocket* connect() {
	std::string hostip = "194.197.235.49";
	std::cout << "IP: ";
//	std::cin >> hostip;

	// create socket and connect
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(hostip, 8118);
	if (status != sf::Socket::Done)	{
		std::cout << "Connection creation error\nErrno 101" << std::endl; 	// error
		return NULL;
	}
	sf::Packet p;
	socket.receive(p);
	int newport;


	p >> newport;
	std::cout << "Connecting to: " << newport << std::endl;
	socket.disconnect();
	sf::TcpSocket* newSocket = new sf::TcpSocket();
	sf::Socket::Status stts =  newSocket->connect(hostip, newport);
	if (stts != sf::Socket::Done)	{
		std::cout << "Connection creation error\nErrno 102" << std::endl; 	// error
		return NULL;
	}
	return newSocket;
}