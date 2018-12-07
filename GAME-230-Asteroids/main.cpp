#include "MainMenu.h"
#include "OverMenu.h"
#include "GameLevel.h"
#include "Const.h"
#include <stdlib.h>
#include <time.h> 

#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF |
		_CRTDBG_LEAK_CHECK_DF);
	srand((unsigned)time(NULL));
	Clock clock;
	
	std::unique_ptr<AppState> curState(new MainMenu());
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Just Another Asteroids!");
	
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
		if (next == (AppState*)7777777) {
			curState.reset();
			break;
		}
		if (next != nullptr) {
			curState.reset(next);
		}			
		curState->render_frame(window);
		window.display();
	}

	return 0;
}