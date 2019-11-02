#include "GameManager.h"

GameManager* game = nullptr;
//Entry Point for Application
int main(int argc, char* argv[]) {
	game = new GameManager(argc, argv);

	return 0;
}