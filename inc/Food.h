#pragma once

#include <iostream>
#include <string>
#include "raylib.h"
#include "raymath.h"

#include "app_cfg.h"


class Food
{
    public:
        Food()
        {
            texture = LoadTexture(FoodLocation);
            position = {0.0f, 0.0f};
            rotationAngle = 0.0f;
            dimensions = {static_cast<float>(texture.width), static_cast<float>(texture.height)};
        }

        ~Food()
        {
            UnloadTexture(texture);
        }

        void SetValidPlanePos(Vector3 gamePanelLimit)
        {
            pixelSize = static_cast<uint16_t>(gamePanelLimit.z);
            gameDimensions = (Vector2) {gamePanelLimit.x, gamePanelLimit.y};

            cellScaleFactor = (4 * pixelSize * pixelSize) / (texture.width * texture.height);
            cellScaleFactor = std::sqrt(cellScaleFactor);

            UpdatePos();
        }

        void Draw()
        {
            DrawTextureEx(texture, position, 0.0f, cellScaleFactor, WHITE);
        }

        Rectangle GetFoodBlockPosition()
        {
            Rectangle foodBlock = (Rectangle) {position.x, position.y, texture.width * cellScaleFactor, texture.height * cellScaleFactor};
            return(foodBlock);
        }

        void UpdatePos()
        {
            position = GenerateRandomPosition(gameDimensions);
        }

        std::string ToString()
        {
            std::ostringstream oss;
            oss << "[ ";
            oss << "X:" << position.x << " ";
            oss << "Y:" << position.y << " ";
            oss << "]";
            return(oss.str());
        }

    private:
        Vector2 GenerateRandomPosition(Vector2 gamePanleLimit)
        {
            float x = GetRandomValue(0, (gamePanleLimit.x / pixelSize) - 1);
            float y = GetRandomValue(0, (gamePanleLimit.y / pixelSize) - 1);
            return Vector2Scale((Vector2){x, y}, pixelSize);
        }

        Vector2 position;
        Vector2 dimensions;
        Vector2 gameDimensions;
        Texture2D texture;
        float rotationAngle;
        float cellScaleFactor;
        uint16_t pixelSize;
};


