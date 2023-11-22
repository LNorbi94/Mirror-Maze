#include "Direction.h"

namespace Maze
{
    int getMultiDirection( const Direction first, const Direction second )
    {
        return ( static_cast< int >( first ) * 4 ) + static_cast< int >( second );
    }

    Direction reverseDirection( const Direction direction )
    {
        switch ( direction ) {
            case Direction::Top:
                return Direction::Bottom;
            case Direction::Bottom:
                return Direction::Top;
            case Direction::Left:
                return Direction::Right;
            case Direction::Right:
                return Direction::Left;
            default:
                break;
        }
        return Direction::Unknown;
    }

    std::string directionToString( Direction direction )
    {
        switch ( direction ) {
            case Direction::Top:
                return "Top";
            case Direction::Bottom:
                return "Bottom";
            case Direction::Left:
                return "Left";
            case Direction::Right:
                return "Right";
            default:
                break;
        }
        return "Unknown";
    }
}
