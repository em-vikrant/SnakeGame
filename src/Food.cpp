/* File     Food.cpp
 * Brief    Food class implementation.
 */

#include <sstream>

#include "Food.hpp"

Food::Food() {
    texture = LoadTexture(FoodLocation);
    position = {0.0f, 0.0f};
    rotationAngle = 0.0f;
    dimensions = {static_cast<float>(texture.width), static_cast<float>(texture.height)};
}

Food::~Food() {
    UnloadTexture(texture);
}

void Food::SetValidPlanePos(const Vector3& gamePanelLimit) {
    pixelSize = static_cast<uint16_t>(gamePanelLimit.z);
    gameDimensions = (Vector2) {gamePanelLimit.x, gamePanelLimit.y};

    cellScaleFactor = (4 * pixelSize * pixelSize) / (texture.width * texture.height);
    cellScaleFactor = std::sqrt(cellScaleFactor);

    UpdatePos();
}

void Food::Draw() {
    DrawTextureEx(texture, position, 0.0f, cellScaleFactor, WHITE);
}

Rectangle Food::GetFoodBlockPosition() {
    Rectangle foodBlock = (Rectangle) {position.x, position.y, texture.width * cellScaleFactor, texture.height * cellScaleFactor};
    return(foodBlock);
}

void Food::UpdatePos() {
    position = GenerateRandomPosition(gameDimensions);
}

std::string Food::ToString() {
    std::ostringstream oss;
    oss << "[ ";
    oss << "X:" << position.x << " ";
    oss << "Y:" << position.y << " ";
    oss << "]";
    return(oss.str());
}

Vector2 Food::GenerateRandomPosition(const Vector2& gamePanleLimit) {
    float x = GetRandomValue(0, (gamePanleLimit.x / pixelSize) - 1);
    float y = GetRandomValue(0, (gamePanleLimit.y / pixelSize) - 1);
    return Vector2Scale((Vector2){x, y}, pixelSize);
}

