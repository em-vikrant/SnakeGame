#pragma once

#include <iostream>
#include <string>
#include "raylib.h"
#include "raymath.h"

#include "app_cfg.hpp"


/* Class for the Game Panel. */ 
class GamePanel {
    public:
        GamePanel();
        GamePanel(std::string gmTitle, uint8_t cellSizePx = defaultCellSizePx);
        GamePanel(uint8_t cellSizePx, uint16_t scWidth, uint16_t scHeight, std::string gmTitle);

        ~GamePanel();

        void SetScreenWidth(const uint16_t& scWidth);
        void SetScreenHeight(const uint16_t& scHeight);
        void SetFrameRatePS(const uint8_t& frameRate);

        void SetBackGround(const Color& clr);
        void Show();
        void Clear();
        void Init();

        inline uint16_t GetScreenWidth() const { return(cellInRows * pixelSize); }
        inline uint16_t GetScreenHeight() const { return(cellInCols * pixelSize); }
        inline uint16_t GetPixelSize() const { return(pixelSize); }
        inline uint16_t GetPixelCnt() const { return(cellInCols * cellInRows); }

        bool CheckClosingEvent();
        void SetGameOver();
        bool IsGameOver();
        Direction CheckKeyPressedEvent();
        void DrawGridLines();

    private:
        bool isGameOver;
        uint16_t pixelSize;
        uint16_t cellInRows;
        uint8_t cellInCols;
        std::string title;
};
