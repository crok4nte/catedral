#include <global.hpp>
#include <UserInterface/Widgets/Chat.hpp>
#include <Util/ColorText.h>
#include <QtCore>
#include <QCompleter>
#include <QAbstractItemModel>

#include <Catedral/Packager.hpp>
#include <Catedral/Connector.hpp>

void CatedralNamespace::UserInterface::Widgets::Chat::setupUi( QWidget *Form )
{
    ChatWidget = Form;

    if ( Form->objectName().isEmpty() ) {
        Form->setObjectName(QString::fromUtf8("Form"));
    }

    Form->resize( 932, 536 );

    gridLayout = new QGridLayout(Form);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout->setVerticalSpacing(4);
    gridLayout->setContentsMargins(1, 4, 1, 4);
    lineEdit = new QLineEdit(Form);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

    gridLayout->addWidget(lineEdit, 2, 1, 1, 1);

    auto label = new QLabel(Form);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout->addWidget(label, 2, 0, 1, 1);

    EventLogText = new QTextEdit(Form);
    EventLogText->setObjectName(QString::fromUtf8("EventLogText"));
    EventLogText->setReadOnly(true);
    EventLogText->setLineWrapMode(QTextEdit::LineWrapMode::NoWrap);

    gridLayout->addWidget(EventLogText, 0, 0, 1, 2);

    Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
    lineEdit->setText(QString());

    label->setStyleSheet("padding-bottom: 3px; padding-left: 5px;");

    lineEdit->setStyleSheet(
            "background-color: "+Util::ColorText::Colors::Hex::Background+";"
            + "color: "+Util::ColorText::Colors::Hex::Foreground+";"
            );

    EventLogText->setStyleSheet(
            "background-color: "+Util::ColorText::Colors::Hex::Background+";"
            + "color: "+Util::ColorText::Colors::Hex::Foreground+";"
            );

    label->setText( CatedralX::Teamserver.User );
    lineEdit->setPlaceholderText( "Message the team as " + CatedralX::Teamserver.User + "  —  press Enter to send" );
    connect( lineEdit, &QLineEdit::returnPressed, this, &Chat::AppendFromInput );

    QMetaObject::connectSlotsByName(Form);
}

void CatedralNamespace::UserInterface::Widgets::Chat::AppendText(const QString& Time, const QString& text) const
{
    QString t = Util::ColorText::Comment(Time) +" "+ text;

    EventLogText->append( t );
}

void CatedralNamespace::UserInterface::Widgets::Chat::AddUserMessage(const QString Time, QString User, QString text) const
{
    // Estructura moderna: cabecera (avatar-inicial + nombre en acento + hora tenue)
    // y el mensaje en su propia linea debajo, con sangria. Distingue mensajes
    // propios (acento steel-blue) de los del resto del equipo (cyan).
    const bool    self   = ( CatedralX::Teamserver.User.compare( User ) == 0 );
    const QString accent = self ? "#6E8FB0" : "#5BC0EB";
    const QString safeUser = User.toHtmlEscaped();
    const QString initial  = safeUser.isEmpty() ? QString( "?" ) : safeUser.left( 1 ).toUpper();

    const QString html =
        "<div style=\"margin:10px 0 0 0;\">"
            "<span style=\"background-color:" + accent + "; color:#0E0E10; "
                   "font-weight:700; padding:1px 6px; border-radius:4px;\">" + initial + "</span>"
            "<span style=\"color:" + accent + "; font-weight:700;\">&nbsp;&nbsp;" + safeUser + "</span>"
            "<span style=\"color:#6A6A72;\">&nbsp;&nbsp;" + Time.toHtmlEscaped() + "</span>"
        "</div>"
        "<div style=\"color:#E6E6E6; margin:2px 0 2px 10px; "
               "border-left:2px solid " + accent + "; padding-left:8px;\">"
            + text.toHtmlEscaped() +
        "</div>";

    EventLogText->append( html );
}

void CatedralNamespace::UserInterface::Widgets::Chat::AppendFromInput()
{
    auto text = this->lineEdit->text();

    if ( ! text.isEmpty() )
    {
        Util::Packager::Package Package;

        Util::Packager::Head_t Head;
        Util::Packager::Body_t Body;

        auto User = CatedralX::Teamserver.User.toStdString();

        Head.Event        = Util::Packager::Chat::Type;
        Head.Time         = QTime::currentTime().toString("hh:mm:ss").toStdString();
        Head.User         = User;
        Body.SubEvent     = Util::Packager::Chat::NewMessage;
        Body.Info[ User ] = text.toHtmlEscaped().toUtf8().toBase64().toStdString();

        Package.Head = Head;
        Package.Body = Body;

        CatedralX::Connector->SendPackage( &Package );
    }

    this->lineEdit->clear();
}
