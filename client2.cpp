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
	socket.connect(sf::IpAddress("localhost"), 4000);

	sf::SocketSelector wait;
	wait.add(socket);

	while (true) {
		while (wait.wait(sf::milliseconds(500))) {
			sf::Packet p;
			if (socket.receive(p) == sf::TcpSocket::Done)
				print(p);
		}

		string line;
		if (!getline(cin, line))
			break;

		sf::Packet p;
		p << line;
		socket.send(p);
	}

	return 0;
}
