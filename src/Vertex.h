#pragma once

#include "Field.h"

namespace Maze
{

struct Vertex {
    Vertex() = default;
    Vertex( Field::Id id, int currentVertex, Field::Id previous, int previousVertex, Direction directionFromPrevious, int distance );

    Field::Id id = Field::DefaultId;
    int currentVertex = -1;

    Field::Id previous = Field::DefaultId;
    int previousVertex = -1;
    Direction directionFromPrevious = Direction::Unknown;

    int distance = 0;
};

}
