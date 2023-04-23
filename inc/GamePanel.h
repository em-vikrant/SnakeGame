#pragma once

#include <iostream>
#include <string>
#include "raylib.h"
#include "raymath.h"

#include "app_cfg.h"


/* Class for the Game Panel. */ 
class GamePanel
{
    public:
        GamePanel()
            : pixelSize(defaultCellSizePx)
        {
            cellInRows = defaultScreenWidth / pixelSize;
            cellInCols = defaultScreenHeight / pixelSize;
            title = std::string("Game Window");
        }
        
        GamePanel(std::string gmTitle, uint8_t cellSizePx = defaultCellSizePx)
            : title(gmTitle), pixelSize(cellSizePx)
        {
            cellInRows = defaultScreenWidth / pixelSize;
            cellInCols = defaultScreenHeight / pixelSize;
        }

        GamePanel(uint8_t cellSizePx, uint16_t scWidth, uint16_t scHeight, std::string gmTitle)
            : pixelSize(cellSizePx), title(gmTitle)
        {
            SetScreenWidth(scWidth);
            SetScreenHeight(scHeight);
        }

        ~GamePanel()
        {
            CloseWindow();
        }

        void SetScreenWidth(uint16_t scWidth)
        {
            cellInRows = scWidth / pixelSize;
        }

        void SetScreenHeight(uint16_t scHeight)
        {
            cellInCols = scHeight / pixelSize;
        }

        void Init()
        {
            InitWindow(cellInRows * pixelSize, cellInCols * pixelSize, title.c_str());
            isGameOver = false;
        }

        void SetFrameRatePS(uint8_t frameRate)
        {
            SetTargetFPS(frameRate);
        }

        void Show() { BeginDrawing(); }
        void Clear() { EndDrawing(); }
        void SetBackGround(Color clr) { ClearBackground(clr); }

        uint16_t GetScreenWidth() { return(cellInRows * pixelSize); }
        uint16_t GetScreenHeight() { return(cellInCols * pixelSize); }
        uint16_t GetPixelSize() { return(pixelSize); }
        uint16_t GetPixelCnt() { return(cellInCols * cellInRows); }

        bool CheckClosingEvent() { return(WindowShouldClose()); }
        void SetGameOver() { isGameOver = true; }

        bool IsGameOver()
        {
            if(isGameOver == true)
            {
                DrawText("Game Over", (GetScreenWidth() - 15 * pixelSize) / 2, (GetScreenHeight() - 5 * pixelSize) / 2, 30, RED);
            }
            return(isGameOver);
        }

        Direction CheckKeyPressedEvent()
        {
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

        void DrawGridLines()
        {
            for(int r = 0; r < cellInCols; r++)
            {
                for(int c = 0; c < cellInRows; c++)
                {
                    uint8_t dim = pixelSize * 2;
                    DrawRectangleLines(r * dim, c * dim, dim, dim, (Color){218, 218, 218, 255});
                }
            }
        }

    private:
        bool isGameOver;
        uint16_t pixelSize;
        uint16_t cellInRows;
        uint8_t cellInCols;
        std::string title;
};
