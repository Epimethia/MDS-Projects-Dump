#include "CGameController.h"

CGameController Game;

int main() {

	Game.Init();
	while (true) {
		if (Game.GameLoop()) {
			break;
		}
	}
	_getch();
	return 0;
}
