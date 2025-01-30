/* File		Snake.cpp
 * Brief	Snake class implementation.
 */

#include <string>

#include "Snake.hpp"

Snake::Snake() {
	/* Initailize body positions. */
	cellScaleFactor = 0.0f;
	direction = RIGHT;
	snakeBody.push_back((Vector2){0.0f, 0.0f});
	stunned = false;
	texture = LoadTexture(SnakeHeadLocation);
}

Snake::Snake(uint16_t posX, uint16_t posY) : Snake() {
	std::deque<Vector2>::iterator itr = std::begin(snakeBody);
	itr->x = static_cast<float>(posX);
	itr->y = static_cast<float>(posY);
}

Snake::~Snake() {
	UnloadTexture(texture);
}

void Snake::SetValidPlanePos(Vector3 gamePanelLimit) {
	pixelSize = gamePanelLimit.z;
	gameLimits = (Vector2){gamePanelLimit.x, gamePanelLimit.y};

	cellScaleFactor = (4 * pixelSize * pixelSize) / (texture.width * texture.height);
	cellScaleFactor = std::sqrt(cellScaleFactor);
}

void Snake::Draw() {
	std::string text = "SNAKE SIZE: " + std::to_string(snakeBody.size());
	DrawText(text.data(), 10, 10, 15, DARKGRAY);

	/* Draw snake body */
	for(int idx = 0; idx < snakeBody.size(); idx++) {
		Color bodyClr = (idx % 2 == 0) ?  GREEN : LIME;

		uint16_t width = pixelSize * 2;
		uint16_t height = pixelSize * 2;
		DrawRectangle(snakeBody[idx].x, snakeBody[idx].y, width, height, bodyClr);
	}

	/* Add Snake face to the body rendered. */
	Color clr = (stunned != true) ? GREEN : RED;
	DrawTextureEx(texture, (Vector2){snakeBody[0].x, snakeBody[0].y}, 0.0f, cellScaleFactor, clr);

	if(stunned != true) {
		if(IsTimerElapsed(drawDelayTimer) == true) {
			Update();
			SetTimerSec(drawDelayTimer, drawDelay);
		}
	}
}

void Snake::ChangeDirection(Direction dir) {
	if(direction != dir && isPollarOpposite(direction, dir) != true) {
		/* Change the direction. */
		direction = dir;

		/* Set the timer again to avoid multiple shifts in same direction. */
		SetTimerSec(drawDelayTimer, drawDelay);
		Update();
	}
}

void Snake::SetDelay(double seconds)
{
	drawDelay = seconds;
	SetTimerSec(drawDelayTimer, drawDelay);
}

bool Snake::Eaten(Rectangle foodRec) {
	bool ret = false;
	Rectangle snakeHeadRec = (Rectangle) {snakeBody[0].x, snakeBody[0].y, texture.width * cellScaleFactor, texture.height * cellScaleFactor};
	if(CheckCollisionRecs(snakeHeadRec, foodRec) == true)
	{
		ret = true;

		/* Grow the snake body. */
		Vector2 offset = Vector2Multiply(dirMap[direction], (Vector2){pixelSize * 2, pixelSize * 2});
		snakeBody.push_front(Vector2Add(snakeBody[0], offset));
	}
	return(ret);
}

bool Snake::BodyCollision() {
	Vector2& head = snakeBody[0];

	/* Check if snake head collided with walls. */
	if( ( (direction == LEFT || direction == RIGHT) && (head.x < 0 || head.x > gameLimits.x - 2 * pixelSize) ) ||
		( (direction == UP || direction == DOWN) && (head.y < 0 || head.y > gameLimits.y - 2 * pixelSize) ) ) {
		stunned = true;
	}
	else { /* Check if snake head collided with its body.*/
		for(int idx = 1; idx < snakeBody.size(); idx++) {
			if(Vector2Equals(head, snakeBody[idx]) == true) {
				stunned = true;
			}
		}
	}

	return(stunned);
}

void Snake::Update() {
	Vector2 offset = Vector2Multiply(dirMap[direction], (Vector2){pixelSize * 2, pixelSize * 2});
	snakeBody.push_front(Vector2Add(snakeBody[0], offset));
	snakeBody.pop_back();
}

