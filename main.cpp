#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QRandomGenerator>
#include <QDebug>
#include <QSurfaceFormat>

#include <sstream>

#include "src/Maze.h"
#include "src/PathFinder.h"
#include "src/MazeModel.h"

std::string createRandomMaze( const int width, const int height )
{
    std::stringstream ss;
    for (auto i = 0; i < height; ++i) {
        for (auto j = 0; j < width; ++j) {
            if (i == 0 || i == height - 1) {
                ss << "1";
            } else if (j == 0 || j == width - 1) {
                if( j == width - 1 && i == width / 2 ) {
                    ss << "3";
                } else if( j == 0 && i == width / 4 ) {
                    ss << "2";
                } else {
                    ss << "1";
                }
            } else {
                switch ( QRandomGenerator::global()->bounded( 10 ) ) {
                    case 0:
                        ss << ((i == 1 || j == width - 2) ? "0" : "6");
                        break;
                    case 1:
                        ss << ((i == 1 || j == width - 2) ? "0" : "1");
                        break;
                    case 2:
                        ss << ((i == 1 || j == width - 2) ? "0" : "1");
                        break;
                    default:
                        ss << "0";
                }
            }
        }
    }
    return ss.str();
}

int main( int argc, char* argv [] )
{
    QGuiApplication app{ argc, argv };

    QSurfaceFormat format;
    format.setSamples( 8 );
    QSurfaceFormat::setDefaultFormat( format );

    QQmlApplicationEngine engine;
    const QUrl url{ u"qrc:/MirrorMaze/Main.qml"_qs };
    QObject::connect( &engine, &QQmlApplicationEngine::objectCreated,
                     &app, [ url ] ( QObject* obj, const QUrl& objUrl ) {
        if ( !obj && url == objUrl ) {
            QCoreApplication::exit( -1 );
        }
    }, Qt::QueuedConnection);

    const auto height = 30;
    const auto width = 30;
    std::string mazeTrack = createRandomMaze( width, height );
    qDebug() << QString::fromStdString( mazeTrack );

    const auto savedTrack = "111111111111111111111111111111100000000000000000000000000001100000000066160001006000161001101100000000100000000000100601160100610001000100661010006001100060000061606006000001000001100060001610006610100106061601206000000000006000106001000001106010101001600010000600000001100001616016001100000000001001100000000001060001000010001601160010000010060010000010010001110010600110606060001000100101101000100001600006161006000101100000011660100000000000010001100010106100000010000006000003100001000610100601001000000601100000010001010060016000100001160001010101001061116000100101100111000600000600000000161001100601100060000000100100000001106160010000000101010600010001100000100100110000011011010101160000111000000100600000000101100600000101000010000010110001110000000610000010000601610001160000100000101000060000010001101010060000000660010001010001160000000001000000001100001001111111111111111111111111111111";
    Maze::Maze maze{ width, height, savedTrack };
    PathFinder pathFinder{ maze };
    pathFinder.findShortestPath();

    MazeModel model{ maze.getMaze(), pathFinder.getRoute() };
    qmlRegisterSingletonInstance( "MazeModel", 1, 0, "Maze", &model );

    engine.load( url );

    return app.exec();
}
