#pragma once


/* Screen dimensions. */
constexpr uint16_t defaultScreenHeight  = 600;      /*! Screen height. */
constexpr uint16_t defaultScreenWidth   = 800;      /*! Screen Width. */
constexpr uint8_t defaultCellSizePx     = 10;       /*! Pixel Dimension. */


/* Images Locations. */
constexpr const char* FoodLocation      = "F:/Workplace/CPP_PROJECTS/GitHub/SnakeGame/images/pokemon.png";
constexpr const char* SnakeHeadLocation = "F:/Workplace/CPP_PROJECTS/GitHub/SnakeGame/images/snake.png";


/* Direction data. */
enum Direction { UP = 0, DOWN = 1, LEFT = 3, RIGHT = 4, NODIR };

std::map<Direction, Vector2> dirMap{ {UP, {0, -1}}, {DOWN, {0, 1}}, {LEFT, {-1, 0}}, {RIGHT, {1, 0}} };

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


