#include "MainMenu.h"

MainMenu::MainMenu() {
	currentIndex = 0;
	font.loadFromFile("font.ttf");
	mainMenuChoice[0].setFont(font);
	mainMenuChoice[0].setCharacterSize(50);
	mainMenuChoice[0].setString("Start");
	mainMenuChoice[0].setFillColor(Color::White);
	mainMenuChoice[0].setPosition(WIDTH / 2 - 100, HEIGHT / 2);

	mainMenuChoice[1].setFont(font);
	mainMenuChoice[1].setCharacterSize(50);
	mainMenuChoice[1].setString("Exit");
	mainMenuChoice[1].setFillColor(Color::White);
	mainMenuChoice[1].setPosition(WIDTH / 2 - 100, HEIGHT / 2 + 60);

	MainText.setFont(font);
	MainText.setCharacterSize(100);
	MainText.setString("Just Another Asteroids");
	MainText.setFillColor(Color::White);
	MainText.setPosition(150, 150);

	currentChoiceRect.setSize(Vector2f(30, 30));
	currentChoiceRect.setFillColor(Color::Red);
}

AppState* MainMenu::update_state(float dt)
{
	static int upFlag = 0;
	static int downFlag = 0;
	static int enterFlag = 0;
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		upFlag = 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		downFlag = 1;
	}
	if (!Keyboard::isKeyPressed(Keyboard::Up) && upFlag == 1) {
		mainMenuChoice[currentIndex].setColor(Color::White);
		currentIndex = (currentIndex - 1 + 2) % (2);
		upFlag = 0;
	}
	if (!Keyboard::isKeyPressed(Keyboard::Down) && downFlag == 1) {
		mainMenuChoice[currentIndex].setColor(Color::White);
		currentIndex = (currentIndex + 1) % (2);
		downFlag = 0;
	}
	mainMenuChoice[currentIndex].setColor(Color::Red);
	currentChoiceRect.setPosition(Vector2f(mainMenuChoice[currentIndex].getPosition().x - 50, mainMenuChoice[currentIndex].getPosition().y + 20));
	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		enterFlag = 1;
	}
	if (!Keyboard::isKeyPressed(Keyboard::Enter) && enterFlag == 1) {
		mainMenuChoice[currentIndex].setColor(Color::White);
		enterFlag = 0;
		if (currentIndex == 1) {
			exit(0);
		}
		return new GameLevel(1);;
	}
	return nullptr;
}

void MainMenu::render_frame(RenderWindow &window)
{
	window.clear();
	//window.draw(background);
	window.draw(MainText);
	for (int i = 0; i < 2; i++) {
		window.draw(mainMenuChoice[i]);
	}
	window.draw(currentChoiceRect);
}

