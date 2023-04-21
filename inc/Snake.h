#pragma once

#include <iostream>
#include <string>
#include <deque>
#include <cmath>
#include "raylib.h"
#include "raymath.h"

#include "app_cfg.h"


class Snake
{
    public:
        Snake()
        {
            /* Initailize body positions. */
            cellScaleFactor = 0.0f;
            direction = RIGHT;
            snakeBody.push_back((Vector2){0.0f, 0.0f});
            stunned = false;
            texture = LoadTexture(SnakeHeadLocation);
        }

        Snake(uint16_t posX, uint16_t posY)
            : Snake()
        {
            std::deque<Vector2>::iterator itr = std::begin(snakeBody);
            itr->x = static_cast<float>(posX);
            itr->y = static_cast<float>(posY);
        }

        ~Snake()
        {
            UnloadTexture(texture);
        }

        void SetValidPlanePos(Vector3 gamePanelLimit)
        {
            pixelSize = gamePanelLimit.z;
            gameLimits = (Vector2){gamePanelLimit.x, gamePanelLimit.y};

            cellScaleFactor = (4 * pixelSize * pixelSize) / (texture.width * texture.height);
            cellScaleFactor = std::sqrt(cellScaleFactor);
        }

        void Draw(Color clr = WHITE)
        {
            char text[20];
            snprintf(text, sizeof(text), "SNAKE SIZE: %d", snakeBody.size());
            DrawText((const char *)text, 10, 10, 8, BLACK);

            /* Draw snake body */
            for(int idx = 0; idx < snakeBody.size(); idx++)
            {
                DrawRectangleLines(snakeBody[idx].x, snakeBody[idx].y, texture.width * cellScaleFactor, texture.height * cellScaleFactor, DARKGREEN);
            }

            /* Add Snake face to the body rendered. */
            DrawTextureEx(texture, (Vector2){snakeBody[0].x, snakeBody[0].y}, 0.0f, cellScaleFactor, GREEN);

            if(stunned != true)
            {
                if(IsTimerElapsed(drawDelayTimer) == true)
                {
                    Update();
                    SetTimerSec(drawDelayTimer, drawDelay);
                }
            }
        }

        void ChangeDirection(Direction dir)
        {
            if(direction != dir && isPollarOpposite(direction, dir) != true)
            {
                /* Change the direction. */
                direction = dir;

                /* Set the timer again to avoid multiple shifts in same direction. */
                SetTimerSec(drawDelayTimer, drawDelay);
                Update();
            }
        }

        void SetDelay(double seconds)
        {
            drawDelay = seconds;
            SetTimerSec(drawDelayTimer, drawDelay);
        }

        bool Eaten(Rectangle foodRec)
        {
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

        bool BodyCollision()
        {
            Vector2& head = snakeBody[0];
            for(int idx = 1; idx < snakeBody.size(); idx++)
            {
                if(Vector2Equals(head, snakeBody[idx]) == true)
                {
                    stunned = true;
                }
            }
            return(stunned);
        }

    protected:
        void Update()
        {
            Vector2 offset = Vector2Multiply(dirMap[direction], (Vector2){pixelSize * 2, pixelSize * 2});
            snakeBody.push_front(Vector2Add(snakeBody[0], offset));
            snakeBody.pop_back();
        }

    private:
        Vector2 gameLimits;
        Direction direction;

        std::deque<Vector2> snakeBody;
        Texture2D texture;

        float pixelSize;
        double drawDelay;
        double drawDelayTimer;
        float cellScaleFactor;
        bool stunned;
};
