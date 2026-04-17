#include <iostream>
#include "GameManager.h"

int main() {
	GameManager gm = GameManager();
	gm.init();
	while (true) gm.update();
}