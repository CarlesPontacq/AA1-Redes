#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include "NetworkManager.h"

void main()
{
	NT->Init();
	while (!NT->GetDisconnectFromServer()) {
		NT->Update();
	}

}