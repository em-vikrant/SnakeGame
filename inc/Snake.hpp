#pragma once

#include <iostream>
#include <deque>
#include <cmath>
#include <map>
#include "raylib.h"
#include "raymath.h"

#include "app_cfg.hpp"


class Snake {
    public:
        Snake();
        Snake(uint16_t posX, uint16_t posY);
        ~Snake();

        void SetValidPlanePos(Vector3 gamePanelLimit);
        void SetDelay(double seconds);

        void ChangeDirection(Direction dir);
        bool Eaten(Rectangle foodRec);
        bool BodyCollision();
        void Draw();


    protected:
        void Update();

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

        std::map<Direction, Vector2> dirMap{
            {UP, {0, -1}}, {DOWN, {0, 1}}, {LEFT, {-1, 0}}, {RIGHT, {1, 0}}
        };
};
