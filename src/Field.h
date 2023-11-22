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
    /**
     * Checks if the field is traversable or not. Every field except wall is traversable.
     *
     * @return whether the field is traversable or not.
     */
    [[nodiscard]] bool isTraversable() const;
    [[nodiscard]] char toString() const;

    [[nodiscard]] const Id& getId() const;
    void setId( const Id& id );

    /**
     * Gets unique vertex id based on directions.
     * The base of this id is the direction to the previous vertex, and the direction to the current one on the route.
     * 
     * @param directions to current field
     *
     * @return unique id to the vertex
     */
    [[nodiscard]] int getVertexId( int directions ) const;
    void setVertexId( int directions, int idx );

    std::array< Id, 3 > getNeighbours( Direction direction ) const;
    [[nodiscard]] Direction getNeighbourDirection( const Id& otherId ) const;
    
    /**
     * Gets cost of travel to the current field from a previous one.
     * If the previous field's type has to be modified, the cost is 6, otherwise it is 1.
     * 
     * @param previous field on the possible route
     * @param direction from the previous field
     *
     * @return cost of the travel
     */
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
