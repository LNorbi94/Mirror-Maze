#include "Vertex.h"

Maze::Vertex::Vertex( Field::Id id, const int currentVertex, Field::Id previous, const int previousVertex, const Direction directionFromPrevious, const int distance )
    : id{ std::move( id ) }
    , currentVertex{ currentVertex }
    , previous{ std::move( previous ) }
    , previousVertex{ previousVertex }
    , directionFromPrevious{ directionFromPrevious }
    , distance{ distance }
{
}
