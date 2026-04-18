#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include "NetworkManager.h"

void main()
{
	NT->EstablishConnectionWithServer();
	while (!NT->GetDisconnectFromServer()) {
		NT->ReceiveServerPacket();
		NT->SendServerPacket();
		NT->CheckForServerDisconnection();
	}

}