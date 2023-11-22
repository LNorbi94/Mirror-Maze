#include "Vertex.h"

Maze::Vertex::Vertex( const Field::Id id, const int currentVertex, const Field::Id previous, const int previousVertex, const Direction directionFromPrevious, const int distance )
    : id{ id }
    , previous{ previous }
    , currentVertex{ currentVertex }
    , previousVertex{ previousVertex }
    , directionFromPrevious{ directionFromPrevious }
    , distance{ distance }
{
}
