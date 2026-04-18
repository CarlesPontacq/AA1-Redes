#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "User.h"



int main() {

	//TODO: Receive all external info from server
	User user = { "eauna", 69420, 0 };

	User otherUsers[PLAYER_COUNT - 1] = {
		{"blah", 0, 1},
		{"bweh", 0, 2},
		{"blip", 0, 3}
	};

	GameManager gm = GameManager(user, otherUsers);
	while (gm.update());
}