#include "MainMenu.h"
#include "OverMenu.h"
#include "GameLevel.h"
#include <stdlib.h>

int main()
{
	std::unique_ptr<AppState> curState(new MainMenu());
	RenderWindow window(VideoMode(800, 600), "Just Another Asteroids!");

	CircleShape shape(100.f);
	shape.setFillColor(Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		float dt = clock.restart().asSeconds();
		AppState* next = curState->update_state(dt);
		curState->render_frame(window);
		window.display();

		if (next != nullptr)
			curState.reset(next);
	}

	return 0;
}