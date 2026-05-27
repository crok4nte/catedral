#ifndef CATEDRAL_CONNECTOR_HPP
#define CATEDRAL_CONNECTOR_HPP

#include <global.hpp>
#include <QJsonDocument>
#include <QJsonObject>
#include <QWebSocket>
#include <QAbstractSocket>

#include <Catedral/Packager.hpp>

namespace CatedralNamespace
{
    class Connector : public QTcpSocket
    {
    private:
        QWebSocket*           Socket     = nullptr;
        Util::ConnectionInfo* Teamserver = nullptr;
        CatedralSpace::Packager* Packager   = nullptr;

    public:
        QString ErrorString = nullptr;

        Connector( Util::ConnectionInfo* );
        ~Connector() noexcept;

        bool Disconnect();

        void SendLogin();
        void SendPackage( Util::Packager::PPackage package );
    };
}

#endif //CATEDRAL_CONNECTOR_HPP
