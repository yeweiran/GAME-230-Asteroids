#include "OverMenu.h"

OverMenu::OverMenu() {
	currentIndex = 0;
	font.loadFromFile("font.ttf");
	endMenuChoice[0].setFont(font);
	endMenuChoice[0].setCharacterSize(50);
	endMenuChoice[0].setString("Back to Main Menu");
	endMenuChoice[0].setFillColor(Color::White);
	endMenuChoice[0].setPosition(WIDTH / 2 - 100, HEIGHT / 2);

	endMenuChoice[1].setFont(font);
	endMenuChoice[1].setCharacterSize(50);
	endMenuChoice[1].setString("Exit");
	endMenuChoice[1].setFillColor(Color::White);
	endMenuChoice[1].setPosition(WIDTH / 2 - 100, HEIGHT / 2 + 60);

	endText.setFont(font);
	endText.setCharacterSize(100);
	endText.setString("Game Over");
	endText.setFillColor(Color::White);
	endText.setPosition(150, 150);

	currentChoiceRect.setSize(Vector2f(30, 30));
	currentChoiceRect.setFillColor(Color::Red);
}

AppState* OverMenu::update_state(float dt)
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
		endMenuChoice[currentIndex].setColor(Color::White);
		currentIndex = (currentIndex - 1 + 2) % (2);
		upFlag = 0;
	}
	if (!Keyboard::isKeyPressed(Keyboard::Down) && downFlag == 1) {
		endMenuChoice[currentIndex].setColor(Color::White);
		currentIndex = (currentIndex + 1) % (2);
		downFlag = 0;
	}
	endMenuChoice[currentIndex].setColor(Color::Red);
	currentChoiceRect.setPosition(Vector2f(endMenuChoice[currentIndex].getPosition().x - 50, endMenuChoice[currentIndex].getPosition().y + 20));
	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		enterFlag = 1;
	}
	if (!Keyboard::isKeyPressed(Keyboard::Enter) && enterFlag == 1) {
		endMenuChoice[currentIndex].setColor(Color::White);
		enterFlag = 0;
		if (currentIndex == 1) {
			exit(0);
		}
		return new MainMenu();
	}
	return nullptr;
}

void OverMenu::render_frame(RenderWindow &window)
{
	window.clear();
	//window.draw(background);
	window.draw(endText);
	for (int i = 0; i < 2; i++) {
		window.draw(endMenuChoice[i]);
	}
	window.draw(currentChoiceRect);
}

