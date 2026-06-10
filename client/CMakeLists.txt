cmake_minimum_required( VERSION 3.15 )
project( Catedral )

##
## cmake sets
##
set( QT_VERSION 6 )
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )
set( CMAKE_AUTOUIC ON )
set( CMAKE_CPP_COMPILER /usr/bin/x86_64-w64-mingw32-g++ )
set( CMAKE_C_COMPILER /usr/bin/x86_64-w64-mingw32-gcc )
set( CMAKE_CXX_FLAGS "-fpermissive" )
set( REQUIRED_LIBS Core Gui Widgets Network WebSockets Sql )
set( REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network Qt6::WebSockets Qt6::Sql )
set( APP_ICON_RESOURCE_WINDOWS "data/Catedral.qrc" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY .. )
set( CMAKE_INCLUDE_CURRENT_DIR ON )

##
## import includes and external libraries
##
include_directories( include  )
include_directories( external/spdlog/include )
include_directories( external/json/include )
include_directories( external/tomlplusplus )

##
## find qt packages
##
find_package( Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED )

set( CATEDRAL_INCLUDE

        # Misc
        include/Catedral/Connector.hpp
        include/Catedral/DBManager/DBManager.hpp
        include/Catedral/DemonCmdDispatch.h
        include/Catedral/Packager.hpp
        include/Catedral/Catedral.hpp
        include/Catedral/Service.hpp
        include/Catedral/CmdLine.hpp

        # Dialogs
        include/UserInterface/Dialogs/Payload.hpp
        include/UserInterface/Dialogs/About.hpp
        include/UserInterface/Dialogs/Connect.hpp
        include/UserInterface/Dialogs/Listener.hpp

        # small widgets
        include/UserInterface/SmallWidgets/EventViewer.hpp
        include/UserInterface/SmallWidgets/EventViewer.hpp

        # widgets
        include/UserInterface/Widgets/Chat.hpp
        include/UserInterface/Widgets/DemonInteracted.h
        include/UserInterface/Widgets/ListenerTable.hpp
        include/UserInterface/Widgets/ProcessList.hpp
        include/UserInterface/Widgets/SessionTable.hpp
        include/UserInterface/Widgets/SessionGraph.hpp
        include/UserInterface/Widgets/TeamserverTabSession.h
        include/UserInterface/Widgets/LootWidget.h
        include/UserInterface/Widgets/FileBrowser.hpp
        include/UserInterface/Widgets/Teamserver.hpp
        include/UserInterface/Widgets/CatedralSidebar.hpp

        include/UserInterface/CatedralUI.hpp
)

# src for UI
set(
        CATEDRAL_UI

        src/UserInterface/CatedralUi.cc
        src/global.cc

        # Dialogs
        src/UserInterface/Dialogs/About.cc
        src/UserInterface/Dialogs/Connect.cc
        src/UserInterface/Dialogs/Listener.cc
        src/UserInterface/Dialogs/Payload.cc

        # Widgets
        src/UserInterface/Widgets/SessionTable.cc
        src/UserInterface/Widgets/SessionGraph.cc
        src/UserInterface/Widgets/Chat.cc
        src/UserInterface/Widgets/ListenersTable.cc
        src/UserInterface/Widgets/DemonInteracted.cc
        src/UserInterface/Widgets/TeamserverTabSession.cc
        src/UserInterface/Widgets/LootWidget.cc
        src/UserInterface/Widgets/FileBrowser.cc
        src/UserInterface/Widgets/Teamserver.cc
        src/UserInterface/Widgets/ProcessList.cc
        src/UserInterface/Widgets/CatedralSidebar.cc

        # SmallWidgets
        src/UserInterface/SmallWidgets/EventViewer.cc
)

set(
        CATEDRAL_UTIL

        src/Util/ColorText.cpp
        src/Util/Base64.cpp
        src/Util/Base.cpp
)

# src for Catedral
set( CATEDRAL_SOURCE
        src/Main.cc

        src/Catedral/Packager.cc
        src/Catedral/Connector.cc
        src/Catedral/Service.cc

        src/Catedral/DBManger/DBManager.cc
        src/Catedral/DBManger/Teamserver.cc

        src/Catedral/Demon/ConsoleInput.cc
        src/Catedral/Demon/CommandSend.cc
        src/Catedral/Demon/CommandOutput.cc
        src/Catedral/Demon/Commands.cc

        src/Catedral/Catedral.cc

    ${CATEDRAL_UI}
)

add_executable( ${PROJECT_NAME} ${CATEDRAL_INCLUDE} ${CATEDRAL_SOURCE} ${CATEDRAL_UTIL} ${APP_ICON_RESOURCE_WINDOWS} data/Catedral.rc )
add_definitions( -DQT_NO_DEBUG_OUTPUT )

target_link_libraries(
    ${PROJECT_NAME}
    ${REQUIRED_LIBS_QUALIFIED}
    # spdlog::spdlog
    # spdlog::spdlog_header_only
)
