#ifndef CATEDRAL_LISTENERTABLE_HPP
#define CATEDRAL_LISTENERTABLE_HPP

#include <global.hpp>
#include <QTableWidget>

#include <Catedral/DBManager/DBManager.hpp>
#include <Catedral/Packager.hpp>

class CatedralNamespace::UserInterface::Widgets::ListenersTable : public QWidget
{
private:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QTableWidget *tableWidget;
    CatedralSpace::DBManager* dbManager;
    CatedralSpace::Packager* Packager;

    QPushButton* buttonAdd;
    QPushButton* buttonEdit;
    QPushButton* buttonRemove;

public:
    QString TeamserverName;
    QWidget* ListenerWidget;

    void setupUi( QWidget* widget );
    void ButtonsInit();
    void setDBManager( CatedralSpace::DBManager* dbManager );

    Util::Packager::Package CreateNewPackage( int EventID, MapStrStr ) const;

    void ListenerAdd( Util::ListenerItem item ) const;
    void ListenerEdit( Util::ListenerItem item ) const;
    void ListenerRemove( QString ListenerName ) const;
    void ListenerError( QString ListenerName, QString Error ) const;
};

#endif // CATEDRAL_LISTENERTABLE_HPP