#pragma once

#include "Direction.h"

#include <array>
#include <string>

namespace Maze
{

class Field {
public:
    enum class Type {
        Empty,
        Wall,
        Entrance,
        Exit,
        PlacedMirror,
        PlacedNegativeMirror,
        Mirror,
        NegativeMirror
    };

    using Id = std::pair< int, int >;
    static const Id DefaultId;

    [[nodiscard]] Type getType() const;
    void setType( Type type );
    [[nodiscard]] bool isTraversable() const;
    [[nodiscard]] char toString() const;

    [[nodiscard]] const Id& getId() const;
    void setId( const Id& id );

    [[nodiscard]] int getVertexId( int directions ) const;
    void setVertexId( int directions, int idx );

    std::array< Id, 3 > getNeighbours( Direction direction ) const;
    [[nodiscard]] Direction getNeighbourDirection( const Id& otherId ) const;

    [[nodiscard]] int getCostOfTravel( const Field* field, Direction directionFromPrevious ) const;
    [[nodiscard]] Type getTypeToReachField( const Field* field, Direction directionFromPrevious ) const;

private:
    Type m_type = Type::Wall;

    Id m_id = DefaultId;
    Id m_leftNeighbour;
    Id m_rightNeighbour;
    Id m_topNeighbour;
    Id m_bottomNeighbour;

    std::array< int, 16 > m_vertexIds{
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
    };
};

}
