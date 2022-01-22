#include "Game.h"
#include <Windows.h>

#undef main

int main(){

	//Òþ²Øcmd´°¿Ú
	//HWND hwnd = GetForegroundWindow();
	//ShowWindow(hwnd, SW_HIDE);

	class Game game = Game();
	bool isRun = true;
	if (game.OpenGame() > 0) {
		isRun = false;
	}
	if (isRun) {
		game.Updata();
	}
	game.Shutdown();
}