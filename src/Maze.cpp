#include "Maze.h"

#include <sstream>
#include <string>

namespace Maze
{

Maze::Maze( const int width, const int height, const std::string& maze )
    : m_height{ height }
    , m_width{ width }
{
    if ( m_width < 3 || m_width > 200 || m_height < 3 || m_height > 200 ) {
        m_error = Error::InvalidMaze;
        return;
    }

    m_maze.resize( m_height );
    for (auto i = 0; i < m_height; ++i) {
        m_maze[ i ].resize( m_width );
        for (auto j = 0; j < m_width; ++j) {
            const auto idx = i * m_width + j;
            if ( idx < maze.size() && isdigit( maze[ idx ] ) ) {
                const auto type = maze[ idx ] - '0';
                createField( std::make_pair( i, j ), type );
            } else {
                m_error = Error::InvalidMaze;
            }
        }
    }
}

std::array< Field*, 3 > Maze::getNeighbours( const Field* field, const Direction direction )
{
    std::array< Field*, 3 > neighbours{};
    if ( field == nullptr ) {
        return neighbours;
    }

    auto next = 0;
    for ( const auto& idx : field->getNeighbours( direction ) ) {
        auto* neighbour = getMazeField( idx );
        if ( neighbour != nullptr && neighbour->isTraversable() ) {
            neighbours[ next++ ] = neighbour;
        }
    }

    return neighbours;
}

Field* Maze::getMazeField( const Field::Id& id )
{
    return isValidIndex( id ) ? &m_maze[ id.first ][ id.second ] : nullptr;
}

int Maze::getVertexId( Field* field, const int directions )
{
    auto id = field->getVertexId( directions );
    if ( id == -1 ) {
        field->setVertexId( directions, m_lastVertexId );
        return m_lastVertexId++;
    }
    return id;
}

const Field::Id& Maze::getStartOfMaze() const
{
    return m_start;
}

Direction Maze::getDirectionToStart() const
{
    return m_directionToStart;
}

const Field::Id& Maze::getEndOfMaze() const
{
    return m_end;
}

std::string Maze::toString() const
{
    std::stringstream ss;
    for ( const auto& row : m_maze ) {
        for ( const auto& field : row ) {
            ss << field.toString();
        }
    }
    return ss.str();
}

bool Maze::isMazeSolveable() const
{
    return m_error == Error::None;
}

void Maze::setError( const Error error )
{
    if ( m_error != error ) {
        m_error = error;
    }
}

std::vector< std::vector< Field > > Maze::getMaze()
{
    return m_maze;
}

bool Maze::isValidIndex( const Field::Id& id ) const
{
    return id.first >= 0 && id.first < m_height && id.second >= 0 && id.second < m_width;
}

Direction Maze::determineDirection( const Field::Id& id ) const
{
    if ( id.first == 0 ) {
        return Direction::Top;
    } else if ( id.first == m_height - 1 ) {
        return Direction::Bottom;
    } else if ( id.second == 0 ) {
        return Direction::Left;
    } else {
        return Direction::Right;
    }
}

void Maze::createField( const Field::Id& id, const int type )
{
    if ( type >= 0 && type <= 7 && type != 1 ) {
        auto& mazeField = m_maze[ id.first ][ id.second ];
        mazeField.setId( id );
        mazeField.setType( static_cast< Field::Type >( type ) );
        if ( type == 2 ) {
            m_start = id;
            m_directionToStart = determineDirection( id );
        } else if( type == 3 ) {
            m_end = id;
        }
    } else if ( type != 1 ) {
        m_error = Error::InvalidMaze;
    }
}

}
