#pragma once
#include "Scene.h"
#include <vector>
#include "Ranking.h"

class RankingScene : public Scene
{

	sf::Font* font;

public:
	void enter(SharedMemory* _sharedMemory) {
		sharedMemory = _sharedMemory;
		font = new sf::Font(FONT_PATH);

		std::vector<User> users;
		users.push_back({ "eauna", 69420, 0 });
		users.push_back({ "foo", 1, 1 });
		users.push_back({ "bar", 2, 2 });
		users.push_back({ "fizz", 3, 3 });

		//TODO: Get users ordered by most points, up to rankingListLength amount
		for (int index = 0; index < users.size(); ++index)
			objects.push_back(new Ranking(users[index], *font, index));
	}
};

