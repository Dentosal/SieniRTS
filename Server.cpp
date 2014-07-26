// include SFML
#include <SFML/Network.hpp>
// include printing
#include <IOStream>
#include <String>
#include <sstream>

#define PORT 8118



int main(int argc, char** argv) {
	sf::IpAddress SelfIP = sf::IpAddress::getPublicAddress();	// get own ip
	std::string IP = SelfIP.toString();

	std::cout << "IP: " << IP << std::endl; 	// print ip

	std::string server_info = "0.1/Server";	// server info


    int port = PORT;
    if(argc==2) {
    	std::istringstream iss(argv[1]);
    	iss >> port;
    }

	std::vector<sf::TcpSocket> sockets;	// create list of sockets
	sf::TcpListener listener;		// create socket listener
	sf::TcpSocket client;			// client "Api"
	int left = 2;
	int new_port;

	while (true) {
		if (listener.listen(PORT) != sf::Socket::Done){
			std::cout << "Connection creation error\nErrno 1" << std::endl; 	// error
			return 1;
		}
		if (listener.accept(client) != sf::Socket::Done)
		{
    		std::cout << "Connection creation error\nErrno 2" << std::endl; 	// error
			return 1;
		}
		std::cout << "Client connected from ip \"" << client.getRemoteAddress() << "\"" << std::endl;

		while {
			new_port=8100-left;
			if (listener.listen(PORT) != sf::Socket::Done){

			}
		}

		left--;
		if (left==0) {
			break;
		}
	}
	std::string msg=server_info;
	std::string back;
	while (true) {
		// server main loop
		send(client, msg);
		back = recv(client);
		//std::cout << back << std::endl;
	}
	return EXIT_SUCCESS;
}