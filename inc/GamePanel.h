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
            : cellPxSize(defaultCellSizePx)
        {
            cellInRows = defaultScreenWidth / cellPxSize;
            cellInCols = defaultScreenHeight / cellPxSize;
            title = std::string("Game Window");
        }
        
        GamePanel(std::string gmTitle, uint8_t cellSizePx = defaultCellSizePx)
            : title(gmTitle), cellPxSize(cellSizePx)
        {
            cellInRows = defaultScreenWidth / cellPxSize;
            cellInCols = defaultScreenHeight / cellPxSize;
        }

        GamePanel(uint8_t cellSizePx, uint16_t scWidth, uint16_t scHeight, std::string gmTitle)
            : cellPxSize(cellSizePx), title(gmTitle)
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
            cellInRows = scWidth / cellPxSize;
        }

        void SetScreenHeight(uint16_t scHeight)
        {
            cellInCols = scHeight / cellPxSize;
        }

        void Init()
        {
            InitWindow(cellInRows * cellPxSize, cellInCols * cellPxSize, title.c_str());
            isGameOver = false;
        }

        void SetFrameRatePS(uint8_t frameRate)
        {
            SetTargetFPS(frameRate);
        }

        void Show() { BeginDrawing(); }
        void Clear() { EndDrawing(); }
        void SetBackGround(Color clr) { ClearBackground(clr); }

        uint16_t GetScreenWidth() { return(cellInRows * cellPxSize); }
        uint16_t GetScreenHeight() { return(cellInCols * cellPxSize); }
        uint16_t GetPixelSize() { return(cellPxSize); }

        bool CheckClosingEvent() { return(WindowShouldClose()); }
        void SetGameOver() { isGameOver = true; }

        bool IsGameOver()
        {
            if(isGameOver == true)
            {
                DrawText("Game Over", (GetScreenWidth() - 15 * cellPxSize) / 2, (GetScreenHeight() - 5 * cellPxSize) / 2, 30, RED);
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

    private:
        bool isGameOver;
        uint16_t cellPxSize;
        uint16_t cellInRows;
        uint8_t cellInCols;
        std::string title;
};
