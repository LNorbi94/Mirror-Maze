#pragma once

#include "Maze.h"
#include "Vertex.h"

#include <stack>
#include <vector>

class PathFinder {
public:
    explicit PathFinder( Maze::Maze& maze );

    void findShortestPath();
    const std::stack< Maze::Field::Id >& getRoute() const;

private:
    void travelShortestPath();

    Maze::Maze& m_maze;
    std::vector< Maze::Vertex > m_vertices;
    Maze::Vertex m_endVertex;

    std::stack< Maze::Field::Id > m_route;
};
