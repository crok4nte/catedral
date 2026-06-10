#include <global.hpp>
#include <Catedral/Catedral.hpp>
#include <QTimer>

auto main(
    int    argc,
    char** argv
) -> int {
    auto CatedralApp = QApplication( argc, argv );
    auto Status   = 0;

    QApplication::setOrganizationName( "Catedral" );
    QApplication::setApplicationName( "Catedral" );

    QGuiApplication::setWindowIcon( QIcon( ":/Catedral.ico" ) );

    CatedralNamespace::CatedralApplication = new CatedralNamespace::CatedralSpace::Catedral( new QMainWindow );
    CatedralNamespace::CatedralApplication->Init( argc, argv );

    Status = QApplication::exec();

    spdlog::info( "Catedral Application status: {}", Status );

    return Status;
}
