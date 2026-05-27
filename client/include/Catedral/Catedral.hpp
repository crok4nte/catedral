#ifndef CATEDRAL_CATEDRAL_HPP
#define CATEDRAL_CATEDRAL_HPP

#include <global.hpp>
#include <UserInterface/CatedralUI.hpp>
#include <Catedral/DBManager/DBManager.hpp>

using namespace CatedralNamespace;

class CatedralSpace::Catedral {

public:
    toml::table Config;

    UserInterface::CatedralUi CatedralAppUI;
    DBManager* dbManager;
    QMainWindow* CatedralMainWindow;
    bool ClientInitConnect = true;

    Catedral( QMainWindow* );
    ~Catedral();

    void Init( int argc, char** argv );
    void Start();

    static void Exit();
};

#endif
