#include "MazeModel.h"

MazeModel::MazeModel( std::vector< std::vector< Maze::Field > > maze, std::stack< Maze::Field::Id > route, QObject* parent )
    : QAbstractTableModel{ parent }
    , m_mazeField{ maze }
    , m_route{ route }
{

}

int MazeModel::rowCount( const QModelIndex& parent ) const
{
    return m_mazeField.size();
}

int MazeModel::columnCount( const QModelIndex& parent ) const
{
    return m_mazeField.size() > 0 ? m_mazeField[ 0 ].size() : 0;
}

bool MazeModel::hasNextId() const
{
    return !m_route.empty();
}

QPoint MazeModel::getNextId()
{
    const auto next = m_route.top();
    m_route.pop();
    m_previousDirection = m_direction;

    if (!m_route.empty()) {
        std::map<Maze::Direction, std::pair< int, int>> neighbours;
        auto current = next;
        neighbours.emplace( Maze::Direction::Left, std::make_pair( current.first, current.second - 1 ) );
        neighbours.emplace( Maze::Direction::Right, std::make_pair( current.first, current.second + 1 ) );
        neighbours.emplace( Maze::Direction::Top, std::make_pair( current.first - 1, current.second ) );
        neighbours.emplace( Maze::Direction::Bottom, std::make_pair( current.first + 1, current.second ) );

        const auto nextDirection = m_route.top();
        for(const auto& neighbour : neighbours) {
            if ( nextDirection == neighbour.second ) {
                m_direction = neighbour.first;
            }
        }
    } else {
        m_direction = m_previousDirection;
    }

    m_directionString = QString::fromStdString( Maze::directionToString( m_direction ) );
    emit directionChanged();

    m_currentField = QPoint( next.first, next.second );
    emit currentFieldChanged();

    m_previous = next;
    return QPoint( next.first, next.second );
}

QVariant MazeModel::data( const QModelIndex& index, int role) const
{
    const auto& field = m_mazeField[ index.row() ][ index.column() ];
    switch ( role ) {
        case IsMirror:
            return field.getType() == Maze::Field::Type::Mirror || field.getType() == Maze::Field::Type::PlacedMirror;
        case IsNegativeMirror:
            return field.getType() == Maze::Field::Type::NegativeMirror || field.getType() == Maze::Field::Type::PlacedNegativeMirror;
        case IsWall:
            return field.getType() == Maze::Field::Type::Wall;
        case IsEntrance:
            return field.getType() == Maze::Field::Type::Entrance;
    }

    return {};
}

QHash< int, QByteArray > MazeModel::roleNames() const
{
    static QHash< int, QByteArray > names = {
        { DisplayRoles::IsMirror, "isMirror" },
        { DisplayRoles::IsNegativeMirror, "isNegativeMirror" },
        { DisplayRoles::IsWall, "isWall" },
        { DisplayRoles::IsEntrance, "isEntrance" }
    };
    return names;
}
