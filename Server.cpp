// include SFML
#include <SFML/Network.hpp>
// include printing
#include <IOStream>
#include <String>

#include <sstream>

#define PORT 8118

void send(sf::TcpSocket& socket, std::string msg) {
	// send string to socket
	msg+="\n";
	socket.send(msg.c_str(), msg.size() + 1);
}
std::string recv(sf::TcpSocket& socket) {
	char buffer[1024];				// buffer size 1024
	std::size_t received = 0;		// size
	socket.receive(buffer, sizeof(buffer), received);	// actually receive
	return buffer;
}

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

	std::vector<sf::IpAddress> IPs;	// create list of IPs
	sf::TcpListener listener;		// create socket listener
	sf::TcpSocket client;			// client "Api"
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
		break;
	}
	std::string b=server_info;
	while (true) {
		send(client, b);
		b = recv(client);
		std::cout << b << std::endl;
	}
	return EXIT_SUCCESS;
}