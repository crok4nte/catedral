#include <global.hpp>
#include <UserInterface/Dialogs/About.hpp>

About::About( QDialog* dialog )
{
    AboutDialog = dialog;

    if ( AboutDialog->objectName().isEmpty() )
        AboutDialog->setObjectName( QString::fromUtf8( "Dialogs" ) );

    AboutDialog->setWindowTitle("About Catedral Framework");
    AboutDialog->setMinimumSize(400, 323);

    gridLayout = new QGridLayout(AboutDialog);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

    label = new QLabel( AboutDialog );
    label->setObjectName(QString::fromUtf8("label_Name"));
    label->setMinimumSize(QSize(196, 0));

    gridLayout->addWidget(label, 0, 0, 1, 3);

    pushButton = new QPushButton(AboutDialog);
    pushButton->setObjectName(QString::fromUtf8("pushButton_New_Profile"));
    gridLayout->addWidget(pushButton, 3, 2, 1, 1);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(horizontalSpacer, 2, 1, 1, 1);

    textBrowser = new QTextBrowser(AboutDialog);
    textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
    textBrowser->setOpenExternalLinks(true);

    gridLayout->addWidget(textBrowser, 1, 0, 1, 3);
    const QString Version  = QString::fromStdString( CatedralNamespace::Version );
    const QString CodeName = QString::fromStdString( CatedralNamespace::CodeName );

    label->setText(
        "<html><head/><body>"
        "<p align=\"center\" style=\"margin:0;\">"
            "<span style=\"font-size:30pt; font-weight:700; letter-spacing:4px; color:#F2F2F4;\">CATEDRAL</span>"
        "</p>"
        "<p align=\"center\" style=\"margin:2px 0 0 0;\">"
            "<span style=\"font-size:10pt; letter-spacing:3px; color:#6E8FB0;\">COMMAND &amp; CONTROL FRAMEWORK</span>"
        "</p>"
        "</body></html>" );

    pushButton->setText( "Close" );

    textBrowser->setOpenExternalLinks( true );
    textBrowser->setHtml(
        "<html><head><style type=\"text/css\"> p, li { white-space: pre-wrap; } </style></head>"
        "<body style=\"font-family:'Space Grotesk','Inter','Segoe UI',sans-serif; font-size:10pt; color:#C8CDD4;\">"

        "<p align=\"center\" style=\"margin:4px 0;\">"
            "<span style=\"font-family:'JetBrains Mono',monospace; color:#6A6A72; font-size:9pt;\">"
            "build " + Version + " &nbsp;·&nbsp; codename &ldquo;" + CodeName + "&rdquo;"
            "</span>"
        "</p>"

        "<p align=\"center\" style=\"margin:14px 24px; color:#9AA7B4;\">"
            "<i>&ldquo;Every operation deserves a cathedral &mdash; quiet on the outside, "
            "vast and deliberate within.&rdquo;</i>"
        "</p>"

        "<p style=\"margin:14px 8px 4px 8px; color:#7E8A97; font-size:9pt; letter-spacing:1px;\">"
            "WHAT IS CATEDRAL"
        "</p>"
        "<p style=\"margin:0 8px; color:#C8CDD4;\">"
            "Catedral is a post-exploitation command &amp; control framework built for "
            "adversary simulation and red team operations: multiplayer teamserver, "
            "modular listeners, in-memory implants and a fast, modern operator UI."
        "</p>"

        "<p style=\"margin:16px 8px 4px 8px; color:#7E8A97; font-size:9pt; letter-spacing:1px;\">"
            "OPERATOR &amp; AUTHOR"
        "</p>"
        "<p style=\"margin:0 8px;\">"
            "Crafted and operated by "
            "<span style=\"color:#6E8FB0; font-weight:700;\">4p0stol</span>."
        "</p>"

        "<p align=\"center\" style=\"margin:18px 8px 6px 8px; color:#55555C; font-size:8pt;\">"
            "For authorized engagements only &mdash; use responsibly."
        "</p>"

        "</body></html>" );

    QObject::connect( pushButton, &QPushButton::clicked, this, &About::onButtonClose );
    QMetaObject::connectSlotsByName( AboutDialog );
}

void About::setupUi()
{

}

void About::onButtonClose()
{
    AboutDialog->close();
}
