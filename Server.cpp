// include SFML
#include <SFML/Network.hpp>
// include printing
#include <IOStream>
#include <String>

#define PORT 8118

int send(sf::TcpSocket, std::string) {
	return 1;
}



int main() {
	sf::IpAddress SelfIP = sf::IpAddress::getPublicAddress();	// get own ip
	std::string IP = SelfIP.toString();

	std::cout << "IP: " << IP << std::endl; 	// print ip

	std::string server_info = "0.1/Server";	// server info

	std::vector<sf::IpAddress> IPs;	// create list of IPs
	sf::TcpListener listener;		// create socket listener
	while (true) {
		if (listener.listen(PORT) != sf::Socket::Done){
			std::cout << "Connection creation error\nErrno 1" << std::endl; 	// error
			return 1;
		}
		sf::TcpSocket client;
		if (listener.accept(client) != sf::Socket::Done)
		{
    		std::cout << "Connection creation error\nErrno 2" << std::endl; 	// error
			return 1;
		}
		std::cout << "Client connected from ip \"" << client.getRemoteAddress() << "\"" << std::endl;

	}
	return EXIT_SUCCESS;
}