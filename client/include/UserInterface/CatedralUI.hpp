#ifndef CATEDRAL_UI_HPP
#define CATEDRAL_UI_HPP

#include <global.hpp>

#include <UserInterface/Dialogs/About.hpp>
#include <UserInterface/Dialogs/Connect.hpp>
#include <UserInterface/Dialogs/Listener.hpp>
#include <UserInterface/Dialogs/Payload.hpp>

#include <UserInterface/Widgets/SessionTable.hpp>
#include <UserInterface/Widgets/Chat.hpp>
#include <UserInterface/Widgets/ListenerTable.hpp>

#include <Catedral/DBManager/DBManager.hpp>

// QT libraries
#include <QDesktopServices>
#include <QShortcut>
#include <QStatusBar>
#include <QDockWidget>
#include <QHeaderView>
#include <QSplitter>
#include <QTableWidget>
#include <QFile>
#include <QStackedWidget>

class CatedralNamespace::UserInterface::CatedralUi : public QMainWindow
{
public:
    QWidget*               centralwidget                 = {};
    QAction*               actionNew_Client              = {};
    QAction*               actionChat                    = {};
    QAction*               actionDisconnect              = {};
    QAction*               actionExit                    = {};
    QAction*               actionTeamserver              = {};
    QAction*               actionGeneratePayload         = {};
    QAction*               actionAbout                   = {};
    QAction*               actionOpen_Help_Documentation = {};
    QAction*               actionGithub_Repository       = {};
    QAction*               actionListeners               = {};
    QAction*               actionSessionsTable           = {};
    QAction*               actionSessionsGraph           = {};
    QAction*               actionLogs                    = {};
    QAction*               actionLoot                    = {};
    QGridLayout*           gridLayout                    = {};
    QGridLayout*           gridLayout_3                  = {};
    QTabWidget*            TeamserverTabWidget           = {};
    QMenuBar*              menubar                       = {};
    QMenu*                 menuCatedral                     = {};
    QMenu*                 menuView                      = {};
    QMenu*                 menuAttack                    = {};
    QMenu*                 menuHelp                      = {};
    QMenu*                 MenuSession                   = {};
    QStatusBar*            statusbar                     = {};
    Dialogs::Connect*      ConnectDialog                 = {};
    About*                 AboutDialog                   = {};
    QMainWindow*           CatedralWindow                   = {};
    CatedralSpace::DBManager* dbManager                     = {};

public:
    void MarkSessionAs( CatedralNamespace::Util::SessionItem session, QString Mark );
    void UpdateSessionsHealth();
    void setupUi( QMainWindow *mainWindow );
    void retranslateUi( QMainWindow *mainWindow ) const;
    void setDBManager( CatedralSpace::DBManager* dbManager );
    void NewTeamserverTab( CatedralNamespace::Util::ConnectionInfo* );
    void NewTeamserverTab( QString Name );
    void NewBottomTab( QWidget* TabWidget, const std::string& TitleName, const QString IconPath = "" ) const;
    int openOrFocusFeatureTab( QWidget*       widget,
                               const QString& title,
                               const QString& iconResource = QString() );
    int openOrFocusBottomTab( QWidget*       widget,
                              const QString& title,
                              const QString& iconResource = QString() );
    void ConnectEvents();

public slots:
    void OneSecondTick();
};

#endif
