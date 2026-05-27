#ifndef CATEDRAL_DBMANAGER_HPP
#define CATEDRAL_DBMANAGER_HPP

#include <global.hpp>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

using namespace std;

class CatedralNamespace::CatedralSpace::DBManager
{
private:
    QSqlDatabase DB;

    bool createNewDatabase();

public:
    static string DBFilePath;

    static int OpenSqlFile;
    static int CreateSqlFile;

    DBManager(const QString& FilePath, int OpenFlag = OpenSqlFile);

    bool addTeamserverInfo( const Util::ConnectionInfo& );
    bool checkTeamserverExists( const QString& ProfileName );
    bool removeTeamserverInfo( const QString& ProfileName );
    bool removeAllTeamservers();
    vector<Util::ConnectionInfo> listTeamservers();
};

#endif