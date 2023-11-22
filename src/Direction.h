#pragma once

#include <string>

namespace Maze
{
    enum class Direction {
        Left,
        Right,
        Top,
        Bottom,
        Unknown
    };

    int getMultiDirection( Direction first, Direction second );
    Direction reverseDirection( Direction direction );
std::string directionToString( Direction direction );
}
