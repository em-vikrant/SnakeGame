/* File     GamePanel.cpp
 * Brief    GamePanel class implementation.
 */

#include "GamePanel.hpp"

GamePanel::GamePanel() : pixelSize(defaultCellSizePx) {
    cellInRows = defaultScreenWidth / pixelSize;
    cellInCols = defaultScreenHeight / pixelSize;
    title = std::string("Game Window");
}
        
GamePanel::GamePanel(std::string gmTitle, uint8_t cellSizePx)
    : title(gmTitle), pixelSize(cellSizePx) {
    cellInRows = defaultScreenWidth / pixelSize;
    cellInCols = defaultScreenHeight / pixelSize;
}

GamePanel::GamePanel(uint8_t cellSizePx, uint16_t scWidth, uint16_t scHeight, std::string gmTitle)
    : pixelSize(cellSizePx), title(gmTitle) {
    SetScreenWidth(scWidth);
    SetScreenHeight(scHeight);
}

GamePanel::~GamePanel() {
    CloseWindow();
}

void GamePanel::SetScreenWidth(const uint16_t& scWidth) {
    cellInRows = scWidth / pixelSize;
}

void GamePanel::SetScreenHeight(const uint16_t& scHeight) {
    cellInCols = scHeight / pixelSize;
}

void GamePanel::SetFrameRatePS(const uint8_t& frameRate) {
    SetTargetFPS(frameRate);
}

void GamePanel::SetBackGround(const Color& clr) {
    ClearBackground(clr);
}

void GamePanel::Init() {
    InitWindow(cellInRows * pixelSize, cellInCols * pixelSize, title.c_str());
    isGameOver = false;
}

void GamePanel::Show() {
    BeginDrawing();
}

void GamePanel::Clear() {
    EndDrawing();
}

bool GamePanel::CheckClosingEvent() {
    return(WindowShouldClose());
}

void GamePanel::SetGameOver() {
    isGameOver = true;
}

bool GamePanel::IsGameOver() {
    if(isGameOver == true) {
        DrawText("Game Over", (GetScreenWidth() - 15 * pixelSize) / 2, (GetScreenHeight() - 5 * pixelSize) / 2, 30, RED);
    }
    return(isGameOver);
}

Direction GamePanel::CheckKeyPressedEvent() {
    Direction dir = NODIR;
    /* Check for the events. */
    if(IsKeyPressed(KEY_UP) == true)
    {
        dir = Direction::UP;
    }
    else if(IsKeyPressed(KEY_DOWN) == true)
    {
        dir = Direction::DOWN;
    }
    else if(IsKeyPressed(KEY_LEFT) == true)
    {
        dir = Direction::LEFT;
    }
    else if(IsKeyPressed(KEY_RIGHT) == true)
    {
        dir = Direction::RIGHT;
    }
    return(dir);
}

void GamePanel::DrawGridLines() {
    for(int r = 0; r < cellInCols; r++) {
        for(int c = 0; c < cellInRows; c++) {
            uint8_t dim = pixelSize * 2;
            DrawRectangleLines(r * dim, c * dim, dim, dim, (Color){218, 218, 218, 255});
        }
    }
}
