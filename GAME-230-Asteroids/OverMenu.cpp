#include "OverMenu.h"

OverMenu::OverMenu(int score) {
	currentIndex = 0;
	this->score = score;
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
	endText.setPosition(400, 150);

	scoreText.setFont(font);
	scoreText.setCharacterSize(50);
	scoreText.setString("Final Score: " + std::to_string(score));
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(450, 300);

	currentChoiceRect.setSize(Vector2f(30, 30));
	currentChoiceRect.setFillColor(Color::Red);

	if (!backTex.loadFromFile("end.jpg"))
	{
		exit(0);
	}
	else
	{
		Vector2u TextureSize = backTex.getSize(); //Get size of texture.
		Vector2u WindowSize = Vector2u(WIDTH, HEIGHT);             //Get size of window.
		float ScaleX = (float)WindowSize.x / TextureSize.x;
		float ScaleY = (float)WindowSize.y / TextureSize.y;     //Calculate scale.
		background.setTexture(backTex);
		background.setScale(ScaleX, ScaleY);      //Set scale.  
	}
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
	window.draw(background);
	window.draw(endText);
	window.draw(scoreText);
	for (int i = 0; i < 2; i++) {
		window.draw(endMenuChoice[i]);
	}
	window.draw(currentChoiceRect);
}

