#include <iostream>
#include <string>
#include <SFML/Network.hpp>

using namespace std;

int main() {
	sf::TcpListener listener;
	listener.listen(4000);

        string tmp{"hej"};
        while ( tmp != "end" )
        {
	cout << "Waiting for client..." << endl;
        
	sf::TcpSocket client;
	listener.accept(client);

	cout << "Client connected!" << endl;

	sf::Packet p;
	p << "<system>" << "Welcome!";
	client.send(p);

	client.receive(p);
	string message;
	p >> message;
	cout << "Received a message: " << message << endl;
        }
	return 0;
}
