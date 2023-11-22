#pragma once

#include "Direction.h"
#include "Field.h"

#include <array>
#include <string>
#include <vector>

namespace Maze
{

class Maze {
public:
    enum class Error {
        InvalidMaze,
        Unsolveable,
        None
    };

    Maze( int width, int height, const std::string& maze );

    [[nodiscard]] std::array< Field*, 3 > getNeighbours( const Field* field, Direction direction );
    [[nodiscard]] Field* getMazeField( const Field::Id& id );
    [[nodiscard]] int getVertexId( Field* field, int directions );

    [[nodiscard]] const Field::Id& getStartOfMaze() const;
    [[nodiscard]] Direction getDirectionToStart() const;
    [[nodiscard]] const Field::Id& getEndOfMaze() const;

    [[nodiscard]] std::string toString() const;

    [[nodiscard]] bool isMazeSolveable() const;
    void setError( Error error );

    std::vector< std::vector< Field > > getMaze();

private:
    [[nodiscard]] bool isValidIndex( const Field::Id& id ) const;
    [[nodiscard]] Direction determineDirection( const Field::Id& id ) const;
    void createField( const Field::Id& id, int type );

    std::vector< std::vector< Field > > m_maze;
    int m_height = 0;
    int m_width = 0;
    int m_lastVertexId = 0;

    Field::Id m_start = { -1, -1 };
    Direction m_directionToStart = Direction::Unknown;
    Field::Id m_end = { -1, -1 };

    Error m_error = Error::None;
};

}
