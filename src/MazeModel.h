#pragma once

#include "Maze.h"

#include <QAbstractTableModel>
#include <QPoint>

#include <stack>
#include <vector>

class MazeModel : public QAbstractTableModel
{
    Q_OBJECT

    Q_PROPERTY( QString direction MEMBER m_directionString NOTIFY directionChanged )
    Q_PROPERTY( QPoint currentField MEMBER m_currentField NOTIFY currentFieldChanged )
public:
    enum DisplayRoles {
        IsMirror,
        IsNegativeMirror,
        IsWall,
        IsEntrance
    };

    MazeModel( std::vector< std::vector< Maze::Field > > maze, std::stack< Maze::Field::Id > route, QObject* parent = nullptr );

    int rowCount( const QModelIndex& parent ) const override;
    int columnCount( const QModelIndex& parent ) const override;

    Q_INVOKABLE bool hasNextId() const;
    Q_INVOKABLE QPoint getNextId();

    QVariant data( const QModelIndex& index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

signals:
    void directionChanged();
    void currentFieldChanged();

private:
    std::vector< std::vector< Maze::Field >> m_mazeField;
    std::stack< Maze::Field::Id > m_route;
    QPoint m_currentField;
    Maze::Field::Id m_previous = Maze::Field::DefaultId;
    Maze::Direction m_direction = Maze::Direction::Unknown;
    QString m_directionString;
    Maze::Direction m_previousDirection = Maze::Direction::Unknown;
};
