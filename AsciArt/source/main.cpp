#include "App/App.h"

int main(void)
{
	App app("AsciArt", sf::VideoMode(800u, 600u));
	app.run();

	return 0;
}