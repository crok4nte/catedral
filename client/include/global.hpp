#ifndef CATEDRAL_GLOBAL_HPP
#define CATEDRAL_GLOBAL_HPP

#include <QApplication>
#include <QMainWindow>
#include <QtNetwork/QTcpSocket>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QAction>
#include <QFormLayout>
#include <QGridLayout>
#include <QLabel>
#include <QMenu>
#include <QDate>
#include <QMenuBar>
#include <QPushButton>
#include <QSpacerItem>
#include <QTabWidget>
#include <QWidget>
#include <QDialog>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>

#include <string>
#include <map>
#include <iostream>
#include <any>

#include <External.h>

#include <Catedral/Service.hpp>
#include <UserInterface/Widgets/FileBrowser.hpp>
#include <Util/Base.hpp>

typedef uint32_t            u32;
typedef uint64_t            u64;

/* windows habit lol */
typedef char*               PCHAR;
typedef char                BYTE;
typedef void*               PVOID;
typedef void*               LPVOID;
typedef unsigned long int   UINT_PTR;

/* std typedefs */
typedef std::map<std::string, std::string> MapStrStr;
typedef std::map<std::string, std::any>    MapStrAny;

/* TODO: rewrite everything.
 *       this is a stupid design
 *       move every class into its own header
 *       remove this namespace */

namespace CatedralNamespace
{
    extern std::string Version;
    extern std::string CodeName;

    namespace Util
    {
        class ColorText;

        std::string base64_encode( const char* buf, unsigned int bufLen );
        std::string gen_random( const int len );

        typedef struct RegisteredCommand
        {
            /* for what agent is it this command */
            std::string     Agent;
            std::string     Module;
            std::string     Command;
            std::string     Help;
            u32             Behaviour;
            std::string     Usage;
            std::string     Example;
            void*           Function;
            std::string     Path;

        } RegisteredCommand ;

        typedef struct RegisteredModule
        {
            /* for what agent is it this command */
            std::string Agent;

            std::string Name;
            std::string Description;
            std::string Behavior;
            std::string Usage;
            std::string Example;

        } RegisteredModule;

        typedef struct ListenerItem
        {
            std::string Name;
            std::string Protocol;
            std::string Status;

            std::any    Info;
        } ListenerItem;
    };

    namespace UserInterface
    {
        class CatedralUi;

        namespace Dialogs {
            class Connect;
            class NewListener;
        }

        // Widgets
        namespace Widgets {
            class Chat;
            class SessionTable;
            class ListenersTable;
            class CredentialsTable;
            class TeamserverTabSession;
            class ProcessList;
        }

        namespace SmallWidgets {
            class EventViewer;
        }

    };

    namespace CatedralSpace {

        struct Listener {

            static QString PayloadHTTPS;
            static QString PayloadHTTP;
            static QString PayloadSMB;
            static QString PayloadExternal;

            typedef struct
            {
                QStringList Hosts;
                QString     HostBind;
                QString     HostRotation;
                QString     PortBind;
                QString     PortConn;
                QString     UserAgent;
                QStringList Headers;
                QStringList Uris;
                QString     HostHeader;
                QString     Secure;
                QString     ProxyEnabled;
                QString     ProxyType;
                QString     ProxyHost;
                QString     ProxyPort;
                QString     ProxyUsername;
                QString     ProxyPassword;
            } HTTP;

            typedef struct
             {
                QString PipeName;
            } SMB;

            typedef struct
            {
                QString Endpoint;
            } External;

            typedef MapStrStr Service;
        };

        class Packager;
        class DBManager;
        class Catedral;
    }

    extern CatedralNamespace::CatedralSpace::Catedral* CatedralApplication;
};

namespace CatedralNamespace
{
    class Connector;

    namespace UserInterface::Widgets
    {
        class DemonInteracted;
    }

    namespace CatedralSpace
    {
        class DemonCommands;
    };

    namespace Util
    {
        typedef struct
        {

            QString TeamserverID;
            QString Name;
            u64     MagicValue;
            QString External;
            QString Internal;
            QString Listener;
            QString User;
            QString Computer;
            QString Domain;
            QString OS;
            QString OSBuild;
            QString OSArch;
            QString Process;
            QString PID;
            QString Arch;
            QString First;
            QString Last;
            QDateTime LastUTC;
            QString Elevated;
            QString PivotParent;
            QString Marked;
            QString Health;
            u32     SleepDelay;
            u32     SleepJitter;
            u64     KillDate;
            u32     WorkingHours;

            UserInterface::Widgets::DemonInteracted* InteractedWidget;
            UserInterface::Widgets::ProcessList*     ProcessList;
            class FileBrowser*                             FileBrowser;

            void Export();
        } SessionItem;

        typedef struct
        {
            QString Name;
            QString Host;
            QString Port;
            QString User;
            QString Password;

            std::vector<ListenerItem>      Listeners;
            std::vector<json>              RegisteredListeners;
            std::vector<SessionItem>       Sessions;
            std::vector<RegisteredCommand> RegisteredCommands;
            std::vector<RegisteredModule>  RegisteredModules;
            std::vector<ServiceAgent>      ServiceAgents;

            QStringList   AddedCommands;
            QJsonDocument DemonConfig;
            QStringList   IpAddresses;

            UserInterface::Widgets::TeamserverTabSession* TabSession;
        } ConnectionInfo;
    };
}

// Global Instance
namespace CatedralX
{
    extern bool                                     DebugMode;
    extern bool                                     GateGUI;
    extern CatedralNamespace::Util::ConnectionInfo     Teamserver;
    extern CatedralNamespace::UserInterface::CatedralUi*  CatedralUserInterface;
    extern CatedralNamespace::Connector*               Connector;
}

#endif
