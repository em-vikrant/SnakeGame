/* FILE : main.cpp
 * BRIEF: Main file to controll the game. */

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <map>
#include "raylib.h"
#include "raymath.h"

#include "GamePanel.hpp"
#include "Snake.hpp"
#include "Food.hpp"


int main(void) {
    /* 1. Setting up the game panel before initializing objects & rendering. */
    GamePanel gamePanel("Snake Game");
    gamePanel.Init();
    gamePanel.SetFrameRatePS(60);

    /* 2. Object declaration and rendering. */
    Food food = Food();
    Snake snake(100, 100);

    food.SetValidPlanePos({
            static_cast<float>(gamePanel.GetScreenWidth()),
            static_cast<float>(gamePanel.GetScreenHeight()),
            static_cast<float>(gamePanel.GetPixelSize())
            });

    snake.SetValidPlanePos({
            static_cast<float>(gamePanel.GetScreenWidth()),
            static_cast<float>(gamePanel.GetScreenHeight()),
            static_cast<float>(gamePanel.GetPixelSize())
            });
    snake.SetDelay(0.3);

    /* Game Loop. */
    while (gamePanel.CheckClosingEvent() == false) {
        gamePanel.Show();
        gamePanel.SetBackGround(WHITE);
        gamePanel.DrawGridLines();

        if(gamePanel.IsGameOver() != true) {
            Direction dir;
            if((dir = gamePanel.CheckKeyPressedEvent()) != NODIR) { 
                snake.ChangeDirection(dir);
            }

            /* Check if food is eaten. */
            if(snake.Eaten(food.GetFoodBlockPosition()) == true) {
                food.UpdatePos();
            }

            /* Check if snake collides with it's own body. */
            if(snake.BodyCollision() == true) {
                gamePanel.SetGameOver();
            }
        }

        /* Render all objects. */
        food.Draw();
        snake.Draw();
        
        gamePanel.Clear();
    }

    return 0;
}
