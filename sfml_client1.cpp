#include <iostream>
#include <string>
#include <SFML/Network.hpp>

using namespace std;

void print(sf::Packet &p) {
	string from, msg;
	p >> from >> msg;

	cout << from << ": " << msg << endl;
}

int main() {
	sf::TcpSocket socket;
	socket.connect(sf::IpAddress("localhost"), 4001);

	sf::Packet p;
	if (socket.receive(p) == sf::TcpSocket::Done)
		print(p);

	return 0;
}
