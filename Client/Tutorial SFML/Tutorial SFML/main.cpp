#include <iostream>
#include <SFML/Graphics.hpp>
#include "SceneManager.h"

int main() {
	
	NT->Init();
	
	while (!NT->GetDisconnectFromServer()) {
		NT->Update();
	}

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), WINDOW_NAME);

	SceneManager sm = SceneManager();
	while (sm.update(*window));

	delete window;
}