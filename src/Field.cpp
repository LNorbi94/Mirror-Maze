#include "Field.h"

#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>

namespace Maze {

const Field::Id Field::DefaultId = { -1, -1 };

Field::Type Field::getType() const
{
    return m_type;
}

void Field::setType( const Type type )
{
    if ( m_type != type ) {
        m_type = type;
    }
}

bool Field::isTraversable() const
{
    return m_type != Type::Wall;
}

char Field::toString() const
{
    return static_cast< int >( m_type ) + '0';
}

const Field::Id& Field::getId() const
{
    return m_id;
}

void Field::setId( const Id& id )
{
    m_id = id;

    m_topNeighbour = std::make_pair( m_id.first - 1, m_id.second );
    m_leftNeighbour = std::make_pair( m_id.first, m_id.second - 1 );
    m_bottomNeighbour = std::make_pair( m_id.first + 1, m_id.second );
    m_rightNeighbour = std::make_pair( m_id.first, m_id.second + 1 );
}

int Field::getVertexId( const int directions ) const
{
    return m_vertexIds[ directions ];
}

void Field::setVertexId( const int directions, const int idx )
{
    m_vertexIds[ directions ] = idx;
}

std::array< Field::Id, 3 > Field::getNeighbours( const Direction lightDirection ) const
{
    if ( m_type == Type::NegativeMirror ) {
        switch ( lightDirection ) {
            case Direction::Top:
                return { m_leftNeighbour };
                break;
            case Direction::Bottom:
                return { m_rightNeighbour };
                break;
            case Direction::Left:
                return { m_topNeighbour };
                break;
            case Direction::Right:
                return { m_bottomNeighbour };
                break;
            default:
                break;
        }
    } else if ( m_type == Type::Mirror ) {
        switch ( lightDirection ) {
            case Direction::Top:
                return { m_rightNeighbour };
                break;
            case Direction::Bottom:
                return { m_leftNeighbour };
                break;
            case Direction::Left:
                return { m_bottomNeighbour };
                break;
            case Direction::Right:
                return { m_topNeighbour };
                break;
            default:
                break;
        }
    } else if ( m_type == Type::Entrance ) {
        switch ( lightDirection ) {
            case Direction::Top:
                return { m_bottomNeighbour };
                break;
            case Direction::Bottom:
                return { m_topNeighbour };
                break;
            case Direction::Left:
                return { m_rightNeighbour };
                break;
            case Direction::Right:
                return { m_leftNeighbour };
                break;
            default:
                break;
        }
    } else {
        switch ( reverseDirection( lightDirection ) ) {
            case Direction::Top:
            {
                return { m_bottomNeighbour, m_leftNeighbour, m_rightNeighbour };
            }
            case Direction::Bottom:
            {
                return { m_topNeighbour, m_leftNeighbour, m_rightNeighbour };
            }
            case Direction::Left:
            {
                return { m_bottomNeighbour, m_topNeighbour, m_rightNeighbour };
            }
            case Direction::Right:
            {
                return { m_bottomNeighbour, m_topNeighbour, m_leftNeighbour };
            }
        }
    }

    return {};
}

Direction Field::getNeighbourDirection( const Id& otherId ) const
{
    if ( m_topNeighbour == otherId ) {
        return Direction::Top;
    } else if ( m_bottomNeighbour == otherId ) {
        return Direction::Bottom;
    } else if ( m_leftNeighbour == otherId ) {
        return Direction::Left;
    } else if ( m_rightNeighbour == otherId ) {
        return Direction::Right;
    }
    return Direction::Unknown;
}

int Field::getCostOfTravel( const Field* field, const Direction lightDirection ) const
{
    return 1 + ( getTypeToReachField( field, lightDirection ) != m_type ? 5 : 0 );
}

Field::Type Field::getTypeToReachField( const Field* field, const Direction lightDirection ) const
{
    if ( field == nullptr ) {
        return m_type;
    }

    if ( m_type == Type::Empty ) {
        const auto directionToNext = getNeighbourDirection( field->getId() );
        switch ( lightDirection ) {
            case Direction::Top: {
                switch ( directionToNext ) {
                    case Direction::Right:
                        return Type::PlacedMirror;
                    case Direction::Left:
                        return Type::PlacedNegativeMirror;
                }
                break;
            }
            case Direction::Bottom: {
                switch ( directionToNext ) {
                    case Direction::Right:
                        return Type::PlacedNegativeMirror;
                    case Direction::Left:
                        return Type::PlacedMirror;
                }
                break;
            }
            case Direction::Left: {
                switch ( directionToNext ) {
                    case Direction::Top:
                        return Type::PlacedNegativeMirror;
                    case Direction::Bottom:
                        return Type::PlacedMirror;
                }
                break;
            }
            case Direction::Right: {
                switch ( directionToNext ) {
                    case Direction::Top:
                        return Type::PlacedMirror;
                    case Direction::Bottom:
                        return Type::PlacedNegativeMirror;
                }
                break;
            }
        }
    }
    return m_type;
}

}
