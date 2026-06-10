#include <global.hpp>
#include <QTimeZone>
#include <UserInterface/Widgets/CatedralSidebar.hpp>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QSplitter>

// Headers for UserInterface
#include <Catedral/Catedral.hpp>

#include <UserInterface/CatedralUI.hpp>
#include <Catedral/Connector.hpp>
#include <UserInterface/Widgets/DemonInteracted.h>
#include <UserInterface/Widgets/TeamserverTabSession.h>
#include <UserInterface/SmallWidgets/EventViewer.hpp>
#include <UserInterface/Widgets/LootWidget.h>

#include <Util/ColorText.h>

#include <Catedral/Packager.hpp>

#include <QPixmap>
#include <QProcess>
#include <QToolButton>
#include <QShortcut>
#include <QTimer>

using namespace CatedralNamespace::CatedralSpace;

void CatedralNamespace::UserInterface::CatedralUi::setupUi(QMainWindow *mainWindow)
{
    CatedralWindow = mainWindow;

    if ( CatedralWindow->objectName().isEmpty() ) {
        CatedralWindow->setObjectName( QString::fromUtf8( "CatedralWindow " ) );
    }

    CatedralWindow->resize( 1399, 821 );
    CatedralWindow->setStyleSheet( FileRead( ":/stylesheets/Catedral" ) );

    actionNew_Client = new QAction( CatedralWindow );
    actionNew_Client->setObjectName( QString::fromUtf8( "NewClient" ) );

    actionChat = new QAction( CatedralWindow );
    actionChat->setObjectName( QString::fromUtf8( "actionChat" ) );

    actionDisconnect = new QAction( CatedralWindow );
    actionDisconnect->setObjectName( QString::fromUtf8( "actionDisconnect" ) );

    actionExit = new QAction( CatedralWindow );
    actionExit->setObjectName( QString::fromUtf8( "actionExit" ) );

    actionTeamserver = new QAction( CatedralWindow );
    actionTeamserver->setObjectName( QString::fromUtf8( "actionTeamserver" ) );

    actionGeneratePayload = new QAction( CatedralWindow );
    actionGeneratePayload->setObjectName( QString::fromUtf8( "actionGeneratePayload" ) );

    actionAbout = new QAction( CatedralWindow );
    actionAbout->setObjectName( QString::fromUtf8( "actionAbout" ) );

    actionOpen_Help_Documentation = new QAction( CatedralWindow );
    actionOpen_Help_Documentation->setObjectName( QString::fromUtf8( "actionOpen_Help_Documentation" ) );

    actionGithub_Repository = new QAction( CatedralWindow );
    actionGithub_Repository->setObjectName( QString::fromUtf8( "actionGithub_Repository" ) );

    actionListeners = new QAction( CatedralWindow );
    actionListeners->setObjectName( QString::fromUtf8( "actionListeners" ) );

    actionSessionsTable = new QAction( CatedralWindow );
    actionSessionsTable->setObjectName( QString::fromUtf8( "actionSessionsTable" ) );

    actionSessionsGraph = new QAction( CatedralWindow );
    actionSessionsGraph->setObjectName( QString::fromUtf8( "actionSessionsGraph" ) );

    actionLogs = new QAction( CatedralWindow );
    actionLogs->setObjectName( QString::fromUtf8( "actionLogs" ) );

    actionLoot = new QAction( CatedralWindow );
    actionLoot->setObjectName( QString::fromUtf8( "actionLoot" ) );

    centralwidget = new QWidget( CatedralWindow );
    centralwidget->setObjectName( QString::fromUtf8( "centralwidget" ) );
    gridLayout_3 = new QGridLayout( centralwidget );
    gridLayout_3->setObjectName( QString::fromUtf8( "gridLayout_3" ) );
    gridLayout_3->setContentsMargins( 0, 0, 0, 0 );

    TeamserverTabWidget = new QTabWidget( centralwidget );
    TeamserverTabWidget->setObjectName( QString::fromUtf8( "TeamserverTabWidget" ) );
    // removed in Catedral Phase 3 (legacy stylesheet)
    // TeamserverTabWidget->setStyleSheet( FileRead( ":/stylesheets/teamserverTab" ) );
    TeamserverTabWidget->setTabBarAutoHide( true );
    TeamserverTabWidget->setTabsClosable( true );

    /* TODO: refactor this. */
    CatedralX::Teamserver.TabSession = new UserInterface::Widgets::TeamserverTabSession;
    CatedralX::Teamserver.TabSession->setupUi( new QWidget, CatedralX::Teamserver.Name );
    TeamserverTabWidget->setCurrentIndex(
        TeamserverTabWidget->addTab(
            CatedralX::Teamserver.TabSession->PageWidget,
            CatedralX::Teamserver.Name
        )
    );

    gridLayout_3->addWidget( TeamserverTabWidget, 0, 0, 1, 1 );

    menubar = new QMenuBar( this->CatedralWindow );
    menubar->setObjectName( QString::fromUtf8( "menubar" ) );
    menubar->setGeometry( QRect( 0, 0, 1143, 20 ) );

    // removed in Catedral Phase 3 (legacy stylesheet)
    // menubar->setStyleSheet( FileRead( ":/stylesheets/menubar" ) );

    menuCatedral   = new QMenu( menubar );
    menuView    = new QMenu( menubar );
    menuAttack  = new QMenu( menubar );
    MenuSession = new QMenu( menubar );
    menuHelp    = new QMenu( menubar );

    menuCatedral->setObjectName( QString::fromUtf8( "menuCatedral" ) );
    menuView->setObjectName( QString::fromUtf8( "menuView" ) );
    menuAttack->setObjectName( QString::fromUtf8( "menuAttack" ) );

    CatedralWindow->setMenuBar( menubar );
    menubar->setVisible( false );  // sidebar replaces menubar visually; QActions retain shortcuts

    menuHelp->setObjectName( QString::fromUtf8( "menuHelp" ) );

    statusbar = new QStatusBar( CatedralWindow );
    statusbar->setObjectName( QString::fromUtf8( "statusbar" ) );
    statusbar->setLayoutDirection( Qt::LayoutDirection::RightToLeft );
    statusbar->setSizeGripEnabled( false );
    statusbar->setVisible( false ); // change that by setting
    CatedralWindow->setStatusBar( statusbar );

    menubar->addAction( menuCatedral->menuAction() );
    menubar->addAction( menuView->menuAction() );
    menubar->addAction( menuAttack->menuAction() );
    menubar->addAction( menuHelp->menuAction() );

    menuCatedral->addAction( actionNew_Client );
    menuCatedral->addSeparator();
    menuCatedral->addAction( actionDisconnect );
    menuCatedral->addAction( actionExit );

    MenuSession->addAction( actionSessionsTable );
    MenuSession->addAction( actionSessionsGraph );

    menuView->addAction( actionListeners );
    menuView->addSeparator();
    menuView->addAction( MenuSession->menuAction() );
    menuView->addSeparator();
    menuView->addAction( actionChat );
    menuView->addAction( actionLoot );
    menuView->addSeparator();
    menuView->addAction( actionLogs );
    menuView->addAction( actionTeamserver );

    menuAttack->addAction( actionGeneratePayload );

    menuHelp->addAction( actionAbout );
    menuHelp->addSeparator();
    menuHelp->addAction( actionOpen_Help_Documentation );
    menuHelp->addSeparator();
    menuHelp->addAction( actionGithub_Repository );

    /* connect events & buttons */
    ConnectEvents();

    /* set text for each action, button and widget */
    retranslateUi( CatedralWindow );

    QMetaObject::connectSlotsByName( CatedralWindow );
}

void CatedralNamespace::UserInterface::CatedralUi::OneSecondTick()
{

}

void CatedralNamespace::UserInterface::CatedralUi::MarkSessionAs(CatedralNamespace::Util::SessionItem Session, QString Mark)
{
    for ( int i = 0; i <  CatedralX::Teamserver.TabSession->SessionTableWidget->SessionTableWidget->rowCount(); i++ )
    {
        auto AgentID = CatedralX::Teamserver.TabSession->SessionTableWidget->SessionTableWidget->item( i, 0 )->text();

        if ( Session.Name.compare( AgentID ) == 0 )
        {
            auto Package = new Util::Packager::Package;
            QString Marked;

            if ( Mark.compare( "Alive" ) == 0 )
            {
                Marked = "Alive";
                Session.Marked = Marked;

                auto Icon = ( Session.Elevated.compare( "true" ) == 0 ) ?
                            WinVersionIcon( Session.OS, true ) :
                            WinVersionIcon( Session.OS, false );

                CatedralX::Teamserver.TabSession->SessionTableWidget->SessionTableWidget->item( i, 0 )->setIcon( Icon );

                for ( int j = 0; j < CatedralX::Teamserver.TabSession->SessionTableWidget->SessionTableWidget->columnCount(); j++ )
                {
                    CatedralX::Teamserver.TabSession->SessionTableWidget->SessionTableWidget->item( i, j )->setBackground( QColor( Util::ColorText::Colors::Hex::Background ) );
                    CatedralX::Teamserver.TabSession->SessionTableWidget->SessionTableWidget->item( i, j )->setForeground( QColor( Util::ColorText::Colors::Hex::Foreground ) );
                }
            }
            else if ( Mark.compare( "Dead" ) == 0 )
            {
                Marked = "Dead";
                Session.Marked = Marked;

                CatedralX::Teamserver.TabSession->SessionTableWidget->SessionTableWidget->item( i, 0 )->setIcon( QIcon( ":/icons/DeadWhite" ) );

                for ( int j = 0; j < CatedralX::Teamserver.TabSession->SessionTableWidget->SessionTableWidget->columnCount(); j++ )
                {
                    CatedralX::Teamserver.TabSession->SessionTableWidget->SessionTableWidget->item( i, j )->setBackground( QColor( Util::ColorText::Colors::Hex::CurrentLine ) );
                    CatedralX::Teamserver.TabSession->SessionTableWidget->SessionTableWidget->item( i, j )->setForeground( QColor( Util::ColorText::Colors::Hex::Comment ) );
                }
            }

            Package->Body = Util::Packager::Body_t {
                .SubEvent = Util::Packager::Session::MarkAs,
                .Info = {
                        { "AgentID", AgentID.toStdString() },
                        { "Marked",  Marked.toStdString() },
                }
            };

            CatedralX::Connector->SendPackage( Package );

            break;
        }
    }
}


void CatedralNamespace::UserInterface::CatedralUi::UpdateSessionsHealth()
{
    for ( auto& session : CatedralX::Teamserver.Sessions )
    {
        if ( session.Marked.compare( "Dead" ) == 0 )
            continue;

        auto Now  = QDateTime::currentDateTimeUtc();
        auto diff = session.LastUTC.secsTo( Now );

        // Qt6: fromTime_t removed; compute components arithmetically from diff (seconds)
        auto seconds = QString::number( diff % 60 );
        auto minutes = QString::number( (diff / 60) % 60 );
        auto hours   = QString::number( (diff / 3600) % 24 );
        auto days    = QString::number( diff / 86400 );

        if ( diff < 60 )
        {
            session.Last = QString("%1s").arg(seconds);
            CatedralX::Teamserver.TabSession->SessionTableWidget->ChangeSessionValue(session.Name, 8, session.Last.toStdString().c_str());
        }
        else if ( diff < 60 * 60 )
        {
            session.Last = QString("%1m %2s").arg(minutes, seconds);
            CatedralX::Teamserver.TabSession->SessionTableWidget->ChangeSessionValue(session.Name, 8, session.Last.toStdString().c_str());
        }
        else if ( diff < 24 * 60 * 60 )
        {
            session.Last = QString("%1h %2m").arg(hours, minutes);
            CatedralX::Teamserver.TabSession->SessionTableWidget->ChangeSessionValue(session.Name, 8, session.Last.toStdString().c_str());
        }
        else
        {
            session.Last = QString("%1d %2h").arg(days, hours);
            CatedralX::Teamserver.TabSession->SessionTableWidget->ChangeSessionValue(session.Name, 8, session.Last.toStdString().c_str());
        }

        // it is very normal for agents to delay three second due to network latency
        auto AllowedDiff = 3;

        if ( session.KillDate > 0 )
        {
            auto UNIX_TIME_START  = 0x019DB1DED53E8000; //January 1, 1970 (start of Unix epoch) in "ticks"
            auto TICKS_PER_SECOND = 10000000; //a tick is 100ns
            auto KillDateInEpoch  = ( session.KillDate - UNIX_TIME_START ) / TICKS_PER_SECOND;

            if ( Now.secsTo( QDateTime::fromSecsSinceEpoch( KillDateInEpoch, QTimeZone::utc() ) ) <= 0 )
            {
                // agent reached its killdate
                session.Health = "killdate";
                session.Marked = "Dead";
                CatedralX::Teamserver.TabSession->SessionTableWidget->ChangeSessionValue( session.Name, 9, session.Health );
                MarkSessionAs( session, QString( "Dead") );
                continue;
            }
        }

        if ( ( ( session.WorkingHours >> 22 ) & 1 ) == 1 )
        {
            uint32_t StartHour   = ( session.WorkingHours >> 17 ) & 0b011111;
            uint32_t StartMinute = ( session.WorkingHours >> 11 ) & 0b111111;
            uint32_t EndHour     = ( session.WorkingHours >>  6 ) & 0b011111;
            uint32_t EndMinute   = ( session.WorkingHours >>  0 ) & 0b111111;
            bool isOffHours = false;

            if ( StartHour < Now.time().hour() || EndHour > Now.time().hour() ) {
                isOffHours = true;
            }

            if ( StartHour == Now.time().hour() && StartMinute < Now.time().minute() ) {
                isOffHours = true;
            }

            if ( EndHour == Now.time().hour() && EndMinute > Now.time().minute() ) {
                isOffHours = true;
            }

            if ( isOffHours ) {
                // agent is offhours
                session.Health = "offhours";
                CatedralX::Teamserver.TabSession->SessionTableWidget->ChangeSessionValue(session.Name, 9, session.Health);
                continue;
            }
        }

        if ( diff - AllowedDiff < session.SleepDelay + ( session.SleepDelay * 0.01 * session.SleepJitter ) ) {
            // agent has ping back in time
            session.Health = "healthy";
            CatedralX::Teamserver.TabSession->SessionTableWidget->ChangeSessionValue( session.Name, 9, session.Health );
            continue;
        } else {
            // agent has not pinged back in time
            session.Health = "unresponsive";
            CatedralX::Teamserver.TabSession->SessionTableWidget->ChangeSessionValue( session.Name, 9, session.Health );
            continue;
        }
    }
}

void CatedralNamespace::UserInterface::CatedralUi::retranslateUi(QMainWindow* mainWindow ) const
{
    mainWindow->setWindowTitle( "Catedral Framework" );

    actionNew_Client->setText( "New Client" );
    actionChat->setText( "Teamserver Chat" );
    actionDisconnect->setText( "Disconnect" );
    actionExit->setText( "Exit" );
    actionTeamserver->setText( "Teamserver" );
    actionGeneratePayload->setText( "Payload" );
    actionAbout->setText( "About" );
    actionOpen_Help_Documentation->setText( "Open Documentation" );
    actionGithub_Repository->setText( "Github Repository" );
    actionListeners->setText( "Listeners" );
    actionSessionsTable->setText( "Table" );
    actionSessionsGraph->setText( "Graph" );
    actionLogs->setText( "Event Viewer" );
    actionLoot->setText( "Loot" );
    menuCatedral->setTitle( "Catedral" );
    menuView->setTitle( "View" );
    menuAttack->setTitle( "Attack" );
    menuHelp->setTitle( "About" );
    MenuSession->setTitle( "Session View" );

    CatedralWindow->setFocus();
    CatedralWindow->showMaximized();

}

void CatedralNamespace::UserInterface::CatedralUi::ConnectEvents()
{
    auto OneSecondTimer = new QTimer( this );

    QMainWindow::connect( OneSecondTimer, &QTimer::timeout, this, [&]() {
        UpdateSessionsHealth();
    } );
    OneSecondTimer->start(1000);

    QMainWindow::connect( actionNew_Client, &QAction::triggered, this, []() {
        QProcess::startDetached( QCoreApplication::applicationFilePath(), QStringList{""} );
    } );

    QMainWindow::connect( actionChat, &QAction::triggered, this, [&](){
        auto Teamserver = CatedralX::Teamserver.TabSession;
        if ( Teamserver->TeamserverChat == nullptr ) {
            Teamserver->TeamserverChat = new Widgets::Chat;
            Teamserver->TeamserverChat->setupUi(new QWidget);
            Teamserver->TeamserverName = CatedralX::Teamserver.Name;
        }

        NewBottomTab(
            Teamserver->TeamserverChat->ChatWidget,
            "Teamserver Chat"
        );
    } );

    QMainWindow::connect( actionDisconnect, &QAction::triggered, this, []() {
        if ( CatedralX::Connector != nullptr ) {
            CatedralX::Connector->Disconnect();
            MessageBox( "Disconnected", "Disconnected from " + CatedralX::Teamserver.Name, QMessageBox::Information );
        } else {
            MessageBox( "Error", "Couldn't disconnect from " + CatedralX::Teamserver.Name, QMessageBox::Critical );
        }
    } );

    QMainWindow::connect( actionExit, &QAction::triggered, this, []() {
        Catedral::Exit();
    } );

    QMainWindow::connect( actionSessionsTable, &QAction::triggered, this, []() {
        CatedralX::Teamserver.TabSession->MainViewWidget->setCurrentIndex( 0 );
    } );

    QMainWindow::connect( actionListeners, &QAction::triggered, this, [&](){
        auto Teamserver = CatedralX::Teamserver.TabSession;

        if ( Teamserver->ListenerTableWidget == nullptr ) {
            Teamserver->ListenerTableWidget = new Widgets::ListenersTable;
            Teamserver->ListenerTableWidget->setupUi(new QWidget);
            Teamserver->ListenerTableWidget->setDBManager(this->dbManager);
            Teamserver->ListenerTableWidget->TeamserverName = CatedralX::Teamserver.Name;
        }

        NewBottomTab(
            Teamserver->ListenerTableWidget->ListenerWidget,
            "Listeners"
        );
    } );

    QMainWindow::connect( actionTeamserver, &QAction::triggered, this, [&](){
        if ( CatedralX::Teamserver.TabSession->Teamserver == nullptr ) {
            CatedralX::Teamserver.TabSession->Teamserver = new Teamserver;
            CatedralX::Teamserver.TabSession->Teamserver->setupUi( new QDialog );
        }

        NewBottomTab(
            CatedralX::Teamserver.TabSession->Teamserver->TeamserverWidget,
            "Teamserver"
        );
    } );

    QMainWindow::connect( actionSessionsGraph, &QAction::triggered, this, [&]() {
        CatedralX::Teamserver.TabSession->MainViewWidget->setCurrentIndex( 1 );
    } );

    QMainWindow::connect( actionLogs, &QAction::triggered, this, [&]() {
        auto Teamserver = CatedralX::Teamserver.TabSession;

        if ( Teamserver->SmallAppWidgets->EventViewer == nullptr )
        {
            Teamserver->SmallAppWidgets->EventViewer = new SmallWidgets::EventViewer;
            Teamserver->SmallAppWidgets->EventViewer->setupUi( new QWidget );
        }

        openOrFocusBottomTab(
            Teamserver->SmallAppWidgets->EventViewer->EventViewer,
            "Event Viewer",
            ":/icons/SidebarLogs"
        );
    } );

    QMainWindow::connect( actionLoot, &QAction::triggered, this, [&]() {
        if ( CatedralX::Teamserver.TabSession->LootWidget == nullptr ) {
            CatedralX::Teamserver.TabSession->LootWidget = new LootWidget;
        }

        NewBottomTab( CatedralX::Teamserver.TabSession->LootWidget, "Loot Collection" );
    } );

    QMainWindow::connect( actionGeneratePayload, &QAction::triggered, this, [&]() {
        if ( CatedralX::Teamserver.TabSession->PayloadDialog == nullptr ) {
            auto* host = new QDialog();
            host->setWindowFlags( Qt::Widget );  // disable dialog window decoration when embedded
            CatedralX::Teamserver.TabSession->PayloadDialog = new Payload;
            CatedralX::Teamserver.TabSession->PayloadDialog->setupUi( host );
            CatedralX::Teamserver.TabSession->PayloadDialog->TeamserverName = CatedralX::Teamserver.Name;
        }

        // Start() does meaningful init (clears combos, retranslateUi) — kept, internal show() is
        // commented in Payload.cc since the widget is embedded as a tab.
        CatedralX::Teamserver.TabSession->PayloadDialog->Start();

        openOrFocusBottomTab( CatedralX::Teamserver.TabSession->PayloadDialog->PayloadDialog,
                              "Payload", ":/icons/SidebarPayload" );
    } );

    QMainWindow::connect( actionAbout, &QAction::triggered, this, [&]() {
        if ( AboutDialog == nullptr ) {
            auto* host = new QDialog( CatedralX::CatedralUserInterface->CatedralWindow );
            host->setWindowFlags( Qt::Widget );
            AboutDialog = new About( host );
            AboutDialog->setupUi();
        }

        openOrFocusBottomTab( AboutDialog->AboutDialog, "About", ":/icons/SidebarHelp" );
    } );

    QMainWindow::connect( actionGithub_Repository, &QAction::triggered, this, []() {
        QDesktopServices::openUrl( QUrl( "https://github.com/CatedralFramework/Catedral" ) );
    } );

    QMainWindow::connect( actionOpen_Help_Documentation, &QAction::triggered, this, []() {
        QDesktopServices::openUrl( QUrl( "https://github.com/CatedralFramework/Catedral/wiki" ) );
    } );
}

void CatedralNamespace::UserInterface::CatedralUi::NewBottomTab(QWidget* TabWidget, const std::string& TitleName, const QString IconPath ) const
{
    CatedralX::Teamserver.TabSession->NewBottomTab( TabWidget, TitleName );
}

int CatedralNamespace::UserInterface::CatedralUi::openOrFocusFeatureTab( QWidget*       widget,
                                                                          const QString& title,
                                                                          const QString& iconResource )
{
    for ( int i = 0; i < TeamserverTabWidget->count(); ++i ) {
        if ( TeamserverTabWidget->tabText( i ) == title ) {
            TeamserverTabWidget->setCurrentIndex( i );
            if ( widget != nullptr && widget != TeamserverTabWidget->widget( i ) ) {
                widget->deleteLater();
            }
            return i;
        }
    }

    int idx;
    if ( ! iconResource.isEmpty() ) {
        idx = TeamserverTabWidget->addTab( widget, QIcon( iconResource ), title );
    } else {
        idx = TeamserverTabWidget->addTab( widget, title );
    }
    TeamserverTabWidget->setCurrentIndex( idx );
    return idx;
}

int CatedralNamespace::UserInterface::CatedralUi::openOrFocusBottomTab( QWidget*       widget,
                                                                         const QString& title,
                                                                         const QString& iconResource )
{
    auto* tabs = CatedralX::Teamserver.TabSession->tabWidget;
    if ( tabs == nullptr ) {
        return -1;
    }

    for ( int i = 0; i < tabs->count(); ++i ) {
        if ( tabs->tabText( i ) == title ) {
            tabs->setCurrentIndex( i );
            if ( widget != nullptr && widget != tabs->widget( i ) ) {
                // Find the scroll area that wraps the original widget, if any
                auto* existing = tabs->widget( i );
                if ( auto* sa = qobject_cast<QScrollArea*>( existing ) ) {
                    if ( sa->widget() != widget ) {
                        widget->deleteLater();
                    }
                } else {
                    widget->deleteLater();
                }
            }
            return i;
        }
    }

    // Allow the embedded widget to shrink/grow freely inside the tab.
    if ( widget != nullptr ) {
        widget->setMinimumSize( 0, 0 );
        widget->setMaximumSize( QWIDGETSIZE_MAX, QWIDGETSIZE_MAX );
    }

    // Wrap in a QScrollArea so content larger than the tab can be scrolled.
    auto* scroll = new QScrollArea();
    scroll->setWidget( widget );
    scroll->setWidgetResizable( true );
    scroll->setFrameShape( QFrame::NoFrame );
    scroll->setHorizontalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    scroll->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );

    CatedralX::Teamserver.TabSession->NewBottomTab( scroll, title.toStdString(), iconResource );

    // Give the bottom area enough room so feature tabs are usable (~60% of vertical space).
    auto* split = CatedralX::Teamserver.TabSession->splitter_TopBot;
    if ( split != nullptr ) {
        int total = split->height();
        if ( total <= 0 ) {
            total = 800;  // sensible default before first layout
        }
        split->setSizes( QList<int>() << ( total * 40 / 100 ) << ( total * 60 / 100 ) );
    }

    return tabs->currentIndex();
}

void CatedralNamespace::UserInterface::CatedralUi::setDBManager(CatedralSpace::DBManager* dbManager)
{
    this->dbManager = dbManager;
}

void UserInterface::CatedralUi::NewTeamserverTab(CatedralNamespace::Util::ConnectionInfo* Connection )
{
    Connection->TabSession = new UserInterface::Widgets::TeamserverTabSession;
    Connection->TabSession->setupUi( new QWidget, Connection->Name );

    int id = TeamserverTabWidget->addTab( Connection->TabSession->PageWidget, Connection->Name );
    TeamserverTabWidget->setCurrentIndex( id );
    CatedralX::Teamserver = *Connection;
}

void UserInterface::CatedralUi::NewTeamserverTab(QString Name )
{
    CatedralX::Teamserver.TabSession = new UserInterface::Widgets::TeamserverTabSession;
    CatedralX::Teamserver.TabSession->setupUi( new QWidget, CatedralX::Teamserver.Name );

    int id = TeamserverTabWidget->addTab( CatedralX::Teamserver.TabSession->PageWidget, CatedralX::Teamserver.Name );
    TeamserverTabWidget->setCurrentIndex( id );
}

