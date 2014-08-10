// include SFML
#include <SFML/Network.hpp>
// include printing
#include <IOStream>
#include <String>
#include <sstream>
#include <stdio.h>
#define PORT 8118


struct Client
{
	sf::IpAddress ip;
	sf::TcpSocket* socket;
	Client(sf::IpAddress i, sf::TcpSocket* s) {
		ip=i;
		socket=s;
	}
};


void my_handler(int s){
	printf("Caught signal %d\n",s);
	exit(1);
}

#ifdef SIENI_SERVER
int main(int argc, char** argv) {
	sf::IpAddress SelfIP = sf::IpAddress::getPublicAddress();	// get own ip
	std::string IP = SelfIP.toString();

	std::cout << "IP: " << IP << std::endl; 	// print ip


    int port = PORT;
    if(argc==2) {
    	std::istringstream iss(argv[1]);
    	iss >> port;
    }

	std::vector<Client> clients;	// create list of sockets
	sf::TcpListener listener;			// create socket listener
	sf::TcpSocket client;				// client "Api"
	sf::SocketSelector ss;



	int new_port = (rand()%90)+8105;
	sf::IpAddress cip;

		if (listener.listen(PORT) != sf::Socket::Done){
			std::cout << "Connection creation error\nErrno 1" << std::endl; 	// error
			return 1;
		}
	while (true) {
		std::cout << "Start loop" << std::endl;
		if (listener.accept(client) != sf::Socket::Done)
		{
			std::cout << "Connection creation error\nErrno 2" << std::endl; 	// error
			return 1;
		}
		cip=client.getRemoteAddress();
		std::cout << "Client connected from ip \"" << cip << "\"" << std::endl;

		new_port--;

		std::cout << "Assigned port " << new_port << std::endl;

		sf::Packet p;
		p << new_port;
		sf::TcpListener tempListener;
		if (tempListener.listen(new_port) != sf::Socket::Done){
			std::cout << "Connection creation error\nErrno 3" << std::endl; 	// error
			return 1;
		}
		client.send(p);
		//listener.close();
		client.disconnect();
		sf::TcpSocket* newcli = new sf::TcpSocket();
		if (tempListener.accept(*newcli) != sf::Socket::Done)
		{
			std::cout << "Connection creation error: Client refused connection\nErrno 4" << std::endl; 	// error
			return 1;
		}
		ss.add(*newcli);
		clients.push_back(Client(cip, newcli));
		if (clients.size()==2) {
			break;
		}
	}
	std::cout << "Exit connection loop" << std::endl;
	sf::Packet p;
	int x=0;
	int y=0; 
	while (true) {
		// server main loop
		if (ss.wait(sf::milliseconds(100))) {
			for (int i=0; i<clients.size();i++) {
				if (ss.isReady(*clients.at(i).socket)) {
					clients.at(i).socket->receive(p);
					for (int j=0; j<clients.size();j++) {
						clients.at(j).socket->send(p);
					}
				}
			}
		}
	}
	return EXIT_SUCCESS;
}
#endif


