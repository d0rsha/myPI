#include <SFML/Network.hpp>
#include <iostream>
#include <string>


using namespace std;

int main()
{
    sf::TcpSocket socket;
    socket.connect(sf::IpAddress("LI15-24"), 4000);

    sf::Packet p;

    if (socket.receive(p) == sf::TcpSocket::Done)
    {
         string from, msg;
         p >> from >> msg;
         cout <<  from << " : " << msg << endl;
    }
    return 0;
}
