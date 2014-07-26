// include SFML
#include <SFML/Network.hpp>
// include printing
#include <IOStream>
#include <String>
#include <sstream>


void send(sf::TcpSocket& socket, std::string msg) {
	sf::Packet p;
	p << msg;
	socket.send(p);
}
std::string recv(sf::TcpSocket& socket) {
	sf::Packet p;
	socket.receive(p);
	std::string ret;
	p >> ret;
	return ret;
}

int connect() {
	std::string hostip = "194.197.235.49";
	std::cout << "IP: ";
//	std::cin >> hostip;
	std::string client_info = "0.1/Server";	// server info

	// create socket and connect
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(hostip, 8118);
	if (status != sf::Socket::Done)	{
		std::cout << "Connection creation error\nErrno 101" << std::endl; 	// error
		return 1;
	}
	else {
		std::cout << "Connection ok" << std::endl;
	}




	std::string b=client_info;
	while (true) {
		b = recv(socket);
		send(socket, b);
		//std::cout << b << std::endl;
		break;
	}
	std::cout << "READY" << std::endl;
	return 0;
}