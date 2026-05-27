#include <Catedral/Catedral.hpp>
#include <Catedral/Connector.hpp>
#include <Catedral/CmdLine.hpp>
#include <UserInterface/Widgets/CatedralSidebar.hpp>

#include <QTimer>
#include <QHBoxLayout>
#include <QFontDatabase>
#include <QApplication>

static void LoadCatedralFonts()
{
    const QStringList fonts = {
        ":/icons/FontSpaceGrotesk",
        ":/icons/FontJetBrainsMono",
        ":/icons/FontJetBrainsMonoBold"
    };
    for ( const auto& f : fonts ) {
        int id = QFontDatabase::addApplicationFont( f );
        if ( id < 0 ) {
            spdlog::warn( "Failed to load embedded font: {}", f.toStdString() );
        }
    }
    QFont uiFont( "Space Grotesk" );
    uiFont.setPixelSize( 13 );
    QApplication::setFont( uiFont );
}

CatedralSpace::Catedral::Catedral( QMainWindow* w )
{
    w->setVisible( false );

    spdlog::set_pattern( "[%T] [%^%l%$] %v" );
    spdlog::info(
        "Catedral Framework [Version: {}] [CodeName: {}]",
        CatedralNamespace::Version,
        CatedralNamespace::CodeName
    );

    this->CatedralMainWindow = w;
    this->dbManager = new CatedralSpace::DBManager( "data/client.db", DBManager::CreateSqlFile );
}

void CatedralSpace::Catedral::Init( int argc, char** argv )
{
    auto List      = std::vector<Util::ConnectionInfo>();
    auto Connect   = new CatedralNamespace::UserInterface::Dialogs::Connect;
    auto Arguments = cmdline::parser();
    auto Path      = std::string();

    Arguments.add( "debug",  '\0', "debug mode" );
    Arguments.add( "config", '\0', "toml config path" );
    Arguments.parse_check( argc, argv );


    if ( Arguments.exist( "debug" ) ) {
        spdlog::set_level( spdlog::level::debug );
        spdlog::debug( "Debug mode enabled" );
    }

    if ( Arguments.exist( "config" ) ) {
        Path = Arguments.get<std::string>( "config" );

        if ( ! QFile::exists( Path.c_str() ) ) {
            Path = std::string();
        }
    }

    if ( Path.empty() ) {
        Path = "client/config.toml";
    }

    if ( ! QFile::exists( Path.c_str() ) ) {
        Path = "config.toml";

        if ( ! QFile::exists( Path.c_str() ) ) {
            spdlog::error( "couldn't find config file" );
            Exit();
        }
    }

    Config = toml::parse_file( Path );
    spdlog::info( "loaded config file: {}", Path );

    /* TODO: handle any kind of error */
    const auto& font   = *Config.get_as<toml::table>( "font" );
    const auto  family = font["family"].value<std::string>().value_or( "Monospace" );
    const auto  size   = font["size"].value<int>().value_or( 10 );

    // Qt6: UTF-8 is the default codec; QTextCodec removed - no-op needed
    QApplication::setFont( QFont( family.c_str(), size ) );
        QTimer::singleShot( 10, [&]() {
        QApplication::setFont( QFont( family.c_str(), size ) );
    } );

    this->CatedralMainWindow->setVisible( false );

    Connect->TeamserverList = dbManager->listTeamservers();
    Connect->passDB( this->dbManager );
    Connect->setupUi( new QDialog );

    CatedralX::Teamserver = Connect->StartDialog( false );

    delete Connect;
}

void CatedralSpace::Catedral::Start()
{
    this->ClientInitConnect = false;
    LoadCatedralFonts();
    this->CatedralMainWindow->setVisible( true );
    // Catedral UI v2: sidebar vertical fijo a la izquierda
    auto* sidebar = new CatedralSidebar( this->CatedralMainWindow );
    sidebar->addItem( ":/icons/SidebarSessions",  "Sessions",       this->CatedralAppUI.actionSessionsTable );
    sidebar->addItem( ":/icons/SidebarGraph",     "Sessions Graph", this->CatedralAppUI.actionSessionsGraph );
    sidebar->addItem( ":/icons/SidebarListeners", "Listeners",      this->CatedralAppUI.actionListeners );
    sidebar->addItem( ":/icons/SidebarPayload",   "Payload",        this->CatedralAppUI.actionGeneratePayload );
    sidebar->addItem( ":/icons/SidebarLoot",      "Loot",           this->CatedralAppUI.actionLoot );
    sidebar->addItem( ":/icons/SidebarChat",      "Chat",           this->CatedralAppUI.actionChat );
    sidebar->addItem( ":/icons/SidebarLogs",      "Event Logs",     this->CatedralAppUI.actionLogs );
    sidebar->addItem( ":/icons/SidebarHelp",      "Help",           this->CatedralAppUI.actionAbout );
    sidebar->addStretch();

    auto* shellWrapper = new QWidget( this->CatedralMainWindow );
    auto* shellLayout  = new QHBoxLayout( shellWrapper );
    shellLayout->setContentsMargins( 0, 0, 0, 0 );
    shellLayout->setSpacing( 0 );
    shellLayout->addWidget( sidebar );
    shellLayout->addWidget( this->CatedralAppUI.centralwidget, 1 );
    this->CatedralMainWindow->setCentralWidget( shellWrapper );
    this->CatedralMainWindow->show();
}

void CatedralSpace::Catedral::Exit()
{
    spdlog::critical( "Exit Program" );
    CatedralApplication->CatedralMainWindow->close();

    exit( 0 );
}

CatedralSpace::Catedral::~Catedral()
{
    delete this->dbManager;
    delete this->CatedralMainWindow;
}
