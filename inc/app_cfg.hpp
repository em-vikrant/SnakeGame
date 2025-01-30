#ifndef APP_CFG_H
#define APP_CFG_H

#include "raymath.h"

/* Screen dimensions. */
constexpr uint16_t defaultScreenHeight  = 400;      /*! Screen height. */
constexpr uint16_t defaultScreenWidth   = 400;      /*! Screen Width. */
constexpr uint8_t defaultCellSizePx     = 10;       /*! Pixel Dimension. */


/* Images Locations. */
constexpr const char* FoodLocation      = ROOT_PATH"/images/pokemon.png";
constexpr const char* SnakeHeadLocation = ROOT_PATH"/images/snake.png";

/* Direction data. */
enum Direction {
    UP = 0,
    DOWN = 1,
    LEFT = 3,
    RIGHT = 4,
    NODIR
};

inline bool isPollarOpposite(Direction dir1, Direction dir2) noexcept
{
    return(1 == abs(dir1 - dir2));
}

/* Timer functions. */
inline void SetTimerSec(double& timer, double seconds) noexcept
{
    timer = GetTime() + seconds;
}

inline bool IsTimerElapsed(double& timer) noexcept
{
    return(timer <= GetTime());
}

#endif
