#include "MainMenu.h"
#include "OverMenu.h"
#include "GameLevel.h"
#include "Const.h"
#include <stdlib.h>
#include <time.h> 

int main()
{
	srand((unsigned)time(NULL));
	Clock clock;
	
	std::unique_ptr<AppState> curState(new MainMenu());
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Just Another Asteroids!");
	

	//float accumulatedTime = 0;
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
		//accumulatedTime += dt;
		/*while (accumulatedTime >= 0.01f)
		{
			
			accumulatedTime -= 0.01f;
		}*/
		AppState* next = curState->update_state(dt);
		if (next != nullptr)
			curState.reset(next);
		curState->render_frame(window);
		window.display();

	}

	return 0;
}