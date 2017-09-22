#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <SFML/Network.hpp>

using namespace std;

typedef std::shared_ptr<sf::TcpSocket> SocketPtr;

int main() {
	sf::TcpListener listener;
	listener.listen(4000);

	cout << "Server is running!" << endl;

	sf::SocketSelector all;
	all.add(listener);

	vector<SocketPtr> clients;

	while (all.wait()) {
		if (all.isReady(listener)) {
			cout << "A client connected!" << endl;
			SocketPtr c = make_shared<sf::TcpSocket>();
			listener.accept(*c);
			all.add(*c);
			clients.push_back(c);
		}

		for (size_t i = 0; i < clients.size(); i++) {
			if (!all.isReady(*clients[i]))
				continue;

			sf::Packet p;
			if (clients[i]->receive(p) != sf::TcpSocket::Done) {
				cout << "A client disconnected" << endl;
				all.remove(*clients[i]);
				clients.erase(clients.begin() + i);
				break;
			}

			string message;
			p >> message;
			cout << "Got a message: " << message << endl;

			sf::Packet send;
			send << "Someone" << message;
			for (size_t j = 0; j < clients.size(); j++) {
				clients[j]->send(send);
			}
		}
	}

	return 0;
}
