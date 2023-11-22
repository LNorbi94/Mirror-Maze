#include "PathFinder.h"

#include <queue>

PathFinder::PathFinder( Maze::Maze& maze )
    : m_maze{ maze }
{
}

void PathFinder::findShortestPath()
{
    if ( !m_maze.isMazeSolveable() ) {
        return;
    }

    const auto cmp = [ this ] ( const int lhs, const int rhs ) {
        return m_vertices[ lhs ].distance > m_vertices[ rhs ].distance;
    };
    std::priority_queue< int, std::vector< int >, decltype( cmp ) > queue{ cmp };

    const auto& start = m_maze.getStartOfMaze();
    const auto& end = m_maze.getEndOfMaze();

    auto* startField = m_maze.getMazeField( start );
    if ( startField != nullptr ) {
        const auto startDirection = m_maze.getDirectionToStart();
        const auto directionToNext = Maze::reverseDirection( startDirection );
        const auto vertexId = m_maze.getVertexId( startField, Maze::getMultiDirection( startDirection, directionToNext ) );
        m_vertices.emplace_back( startField->getId(), vertexId, Maze::Field::DefaultId, -1, startDirection, 0 );
        queue.push( vertexId );
    }

    while ( !queue.empty() ) {
        const auto vertexIdx = queue.top();
        const auto vertex = m_vertices[ vertexIdx ];
        const auto* field = m_maze.getMazeField( vertex.id );
        if ( field->getId() == end ) {
            m_endVertex = vertex;
            break;
        }
        queue.pop();

        const auto directionToVertex = vertex.directionFromPrevious;
        for ( auto* neighbour : m_maze.getNeighbours( field, directionToVertex ) ) {
            if ( neighbour == nullptr ) {
                break;
            }

            const auto distance = vertex.distance + field->getCostOfTravel( neighbour, directionToVertex );
            const auto directionToNeighbour = field->getNeighbourDirection( neighbour->getId() );
            const auto directionId = m_maze.getVertexId( neighbour, Maze::getMultiDirection( directionToVertex, directionToNeighbour ) );
            if ( m_vertices.size() > directionId ) {
                auto& neighbourVertex = m_vertices[ directionId ];
                if ( distance < neighbourVertex.distance ) {
                    neighbourVertex.previous = vertex.id;
                    neighbourVertex.previousVertex = vertex.currentVertex;
                    neighbourVertex.directionFromPrevious = directionToNeighbour;
                    neighbourVertex.distance = distance;
                    queue.push( directionId );
                }
            } else {
                m_vertices.emplace_back( neighbour->getId(), directionId, vertex.id, vertex.currentVertex, directionToNeighbour, distance );
                queue.push( directionId );
            }
        }
    }

    if ( m_endVertex.previousVertex == -1 ) {
        m_maze.setError( Maze::Maze::Error::Unsolveable );
    } else {
        travelShortestPath();
    }
}

const std::stack<Maze::Field::Id>& PathFinder::getRoute() const
{
    return m_route;
}

void PathFinder::travelShortestPath()
{
    const auto& start = m_maze.getStartOfMaze();
    const auto& end = m_maze.getEndOfMaze();
    auto* field = m_maze.getMazeField( end );
    auto* nextField = field;
    auto& nextVertex = m_endVertex;
    m_route.push( nextVertex.id );
    while ( field != nullptr && field->getId() != start ) {
        field = m_maze.getMazeField( nextVertex.previous );
        nextVertex = m_vertices[ nextVertex.previousVertex ];
        m_route.push( field->getId() );
        if ( field != nullptr ) {
            field->setType( field->getTypeToReachField( nextField, nextVertex.directionFromPrevious ) );
            nextField = field;
        }
    }
    //m_route.push( field->getId() );
}
