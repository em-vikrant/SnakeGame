#pragma once

#include <iostream>
#include <string>
#include "raylib.h"
#include "raymath.h"

#include "app_cfg.h"


class Food
{
    public:
        Food();
        ~Food();

        void SetValidPlanePos(const Vector3& gamePanelLimit);

        void Draw();
        Rectangle GetFoodBlockPosition();
        void UpdatePos();
        std::string ToString();

    private:
        Vector2 GenerateRandomPosition(const Vector2& gamePanleLimit);

        Vector2 position;
        Vector2 dimensions;
        Vector2 gameDimensions;
        Texture2D texture;
        float rotationAngle;
        float cellScaleFactor;
        uint16_t pixelSize;
};


