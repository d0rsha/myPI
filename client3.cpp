#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <SFML/Network.hpp>

using namespace std;

void print(sf::Packet &p) {
	string from, msg;
	p >> from >> msg;

	cout << from << ": " << msg << endl;
}

void receive(sf::TcpSocket &from, std::atomic<bool> &done) {
	sf::Packet p;
	while (from.receive(p) == sf::TcpSocket::Done) {
		print(p);
	}
	done.store(true);
}

int main() {
	sf::TcpSocket socket;
	socket.connect(sf::IpAddress("127.0.0.1"), 4000);

	std::atomic<bool> done(false);
	thread t(&receive, std::ref(socket), std::ref(done));

	string line;
	while (getline(cin, line) && !done.load()) {
		sf::Packet p;
		p << line;
		socket.send(p);
	}

	socket.disconnect();
	t.join();

	return 0;
}
