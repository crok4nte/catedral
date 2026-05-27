#include <global.hpp>

#include <UserInterface/Dialogs/Listener.hpp>

#include <QFile>
#include <QApplication>
#include <QDialog>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QSpacerItem>
#include <QVBoxLayout>

using namespace CatedralNamespace::CatedralSpace;
using namespace CatedralNamespace::UserInterface::Dialogs;

bool is_number( const std::string& s )
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

NewListener::NewListener( QDialog* Dialog )
{
    ListenerDialog = Dialog;

    if ( ListenerDialog->objectName().isEmpty() )
        ListenerDialog->setObjectName( QString::fromUtf8( "ListenerWidget" ) );

    // removed in Catedral Phase 3 (legacy stylesheet)
    // Dialog->setStyleSheet( FileRead( ":/stylesheets/Dialogs/Listener" ) );

    ListenerDialog->setMinimumSize( 950, 650 );

    gridLayout = new QGridLayout( ListenerDialog );
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

    ConfigBox = new QGroupBox( ListenerDialog );
    ConfigBox->setObjectName(QString::fromUtf8("ConfigBox"));

    gridLayout_2 = new QGridLayout( ConfigBox );
    gridLayout_2->setObjectName( QString::fromUtf8( "gridLayout_2" ) );
    gridLayout_2->setHorizontalSpacing( 0 );
    gridLayout_2->setContentsMargins( 0, 0, 0, 0 );

    StackWidgetConfigPages = new QStackedWidget( ConfigBox );
    StackWidgetConfigPages->setObjectName( QString::fromUtf8( "StackWidgetConfigPages" ) );

    // ============
    // === HTTP ===
    // ============
    PageHTTP = new QWidget();
    PageHTTP->setObjectName( QString::fromUtf8( "PageHTTP" ) );

    LabelHosts              = new QLabel( PageHTTP );
    HostsGroup              = new QGroupBox( PageHTTP );
    ButtonHostsGroupAdd     = new QPushButton( PageHTTP );
    ButtonHostsGroupClear   = new QPushButton( PageHTTP );

    LabelHostRotation       = new QLabel( PageHTTP );
    ComboHostRotation       = new QComboBox( PageHTTP );

    LabelHostBind           = new QLabel( PageHTTP );
    ComboHostBind           = new QComboBox( PageHTTP );

    LabelPortBind           = new QLabel( PageHTTP );
    InputPortBind           = new QLineEdit( PageHTTP );

    LabelPortConn           = new QLabel( PageHTTP );
    InputPortConn           = new QLineEdit( PageHTTP );

    LabelUserAgent          = new QLabel( PageHTTP );
    InputUserAgent          = new QLineEdit( PageHTTP );

    LabelHeaders            = new QLabel( PageHTTP );
    HeadersGroup            = new QGroupBox( PageHTTP );
    ButtonHeaderGroupAdd    = new QPushButton( PageHTTP );
    ButtonHeaderGroupClear  = new QPushButton( PageHTTP );

    LabelUris               = new QLabel( PageHTTP );
    UrisGroup               = new QGroupBox( PageHTTP );
    ButtonUriGroupClear     = new QPushButton( PageHTTP );
    ButtonUriGroupAdd       = new QPushButton( PageHTTP );

    LabelHostHeader         = new QLabel( PageHTTP );
    InputHostHeader         = new QLineEdit( PageHTTP );

    CheckEnableProxy        = new QCheckBox( PageHTTP );

    horizontalSpacer_6      = new QSpacerItem( 0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum );
    verticalSpacer          = new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
    verticalSpacerHeader    = new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
    ProxyConfigBox          = new QGroupBox( PageHTTP );
    verticalSpacerUris      = new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );

    // formLayout_Hosts/Header/Uri are attached to internal scroll-area content widgets below
    formLayout_3            = new QFormLayout( ProxyConfigBox );

    LabelProxyType = new QLabel( ProxyConfigBox );
    ComboProxyType = new QComboBox( ProxyConfigBox );
    LabelProxyHost = new QLabel( ProxyConfigBox );
    InputProxyHost = new QLineEdit( ProxyConfigBox );
    LabelProxyPort = new QLabel( ProxyConfigBox );
    InputProxyPort = new QLineEdit( ProxyConfigBox );
    LabelUserName  = new QLabel( ProxyConfigBox );
    InputUserName  = new QLineEdit( ProxyConfigBox );
    LabelPassword  = new QLabel( ProxyConfigBox );
    InputPassword  = new QLineEdit( ProxyConfigBox );

    formLayout_3->setWidget( 0, QFormLayout::LabelRole, LabelProxyType );
    formLayout_3->setWidget( 0, QFormLayout::FieldRole, ComboProxyType );
    formLayout_3->setWidget( 1, QFormLayout::LabelRole, LabelProxyHost );
    formLayout_3->setWidget( 1, QFormLayout::FieldRole, InputProxyHost );
    formLayout_3->setWidget( 2, QFormLayout::LabelRole, LabelProxyPort );
    formLayout_3->setWidget( 2, QFormLayout::FieldRole, InputProxyPort );
    formLayout_3->setWidget( 3, QFormLayout::LabelRole, LabelUserName );
    formLayout_3->setWidget( 3, QFormLayout::FieldRole, InputUserName );
    formLayout_3->setWidget( 4, QFormLayout::LabelRole, LabelPassword );
    formLayout_3->setWidget( 4, QFormLayout::FieldRole, InputPassword );

    ComboHostBind->addItems( QStringList() << CatedralX::Teamserver.IpAddresses << "127.0.0.1" << "0.0.0.0" );

    CheckEnableProxy->setObjectName( "bool" );
    ProxyConfigBox->setEnabled( true );
    InputUserAgent->setText( "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.110 Safari/537.36" ); // default. maybe make it dynamic/random ?
    InputUserAgent->setCursorPosition( 0 );
    InputPortBind->setText( "443" );
    InputPortConn->setText( "443" );

    // =============
    // ==== SMB ====
    // =============
    PageSMB = new QWidget();
    PageSMB->setObjectName(QString::fromUtf8("PageSMB"));
    formLayout = new QFormLayout( PageSMB );
    formLayout->setObjectName(QString::fromUtf8("formLayout"));
    LabelPipeName = new QLabel( PageSMB );
    LabelPipeName->setObjectName(QString::fromUtf8("LabelPipeName"));

    formLayout->setWidget(0, QFormLayout::LabelRole, LabelPipeName);

    InputPipeName = new QLineEdit( PageSMB );
    InputPipeName->setObjectName( QString::fromUtf8( "InputPipeName" ) );

    formLayout->setWidget(0, QFormLayout::FieldRole, InputPipeName);

    // ==============
    // == External ==
    // ==============
    PageExternal = new QWidget();
    PageExternal->setObjectName(QString::fromUtf8("PageExternal"));
    formLayout_2 = new QFormLayout(PageExternal);
    formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
    LabelEndpoint = new QLabel(PageExternal);
    LabelEndpoint->setObjectName(QString::fromUtf8("LabelEndpoint"));

    formLayout_2->setWidget(0, QFormLayout::LabelRole, LabelEndpoint);

    InputEndpoint = new QLineEdit(PageExternal);
    InputEndpoint->setObjectName(QString::fromUtf8("InputEndpoint"));

    formLayout_2->setWidget(0, QFormLayout::FieldRole, InputEndpoint);

    gridLayout_2->addWidget( StackWidgetConfigPages, 0, 0, 1, 1 );


    gridLayout->addWidget(ConfigBox, 3, 0, 1, 6);

    ComboPayload = new QComboBox( ListenerDialog );
    ComboPayload->setObjectName( QString::fromUtf8( "ComboPayload" ) );

    gridLayout->addWidget(ComboPayload, 1, 1, 1, 5);

    LabelListenerName = new QLabel(ListenerDialog);
    LabelListenerName->setObjectName(QString::fromUtf8("LabelListenerName"));

    gridLayout->addWidget(LabelListenerName, 0, 0, 1, 1);

    LabelPayload = new QLabel(ListenerDialog);
    LabelPayload->setObjectName(QString::fromUtf8("LabelPayload"));

    gridLayout->addWidget(LabelPayload, 1, 0, 1, 1);

    horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(horizontalSpacer_5, 4, 4, 1, 1);

    ButtonSave = new QPushButton(ListenerDialog);
    ButtonSave->setObjectName(QString::fromUtf8("ButtonSave"));

    gridLayout->addWidget(ButtonSave, 4, 2, 1, 1);

    horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(horizontalSpacer_4, 4, 1, 1, 1);

    horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(horizontalSpacer_3, 4, 5, 1, 1);

    InputListenerName = new QLineEdit(ListenerDialog);
    InputListenerName->setObjectName(QString::fromUtf8("InputListenerName"));

    gridLayout->addWidget(InputListenerName, 0, 1, 1, 5);

    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(horizontalSpacer_2, 4, 0, 1, 1);

    ButtonClose = new QPushButton(ListenerDialog);
    ButtonClose->setObjectName(QString::fromUtf8("ButtonClose"));

    gridLayout->addWidget(ButtonClose, 4, 3, 1, 1);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(horizontalSpacer, 2, 0, 1, 6);

    StackWidgetConfigPages->setCurrentIndex( 0 );

    // ========================================
    // === Page HTTP/HTTPs layout (2 columns) ===
    // ========================================
    //
    //   +-------------------------+-------------------+
    //   | Bind & Connection       | Hosts   [+] [x]   |
    //   |  Host (Bind): combo     |  (scroll area)    |
    //   |  Port Bind:   input     +-------------------+
    //   |  Port Conn:   input     | Headers [+] [x]   |
    //   |  Host Rotat:  combo     |  (scroll area)    |
    //   |  User Agent:  input     +-------------------+
    //   |  Host Header: input     | URIs    [+] [x]   |
    //   |                         |  (scroll area)    |
    //   +-------------------------+-------------------+
    //   | [x] Enable Proxy connection                 |
    //   | +-- Proxy Config -------------------------+ |
    //   | |  Type / Host / Port / User / Pass      | |
    //   | +----------------------------------------+ |
    //   +---------------------------------------------+

    gridLayout_3 = new QGridLayout( PageHTTP );
    gridLayout_3->setObjectName( QString::fromUtf8( "gridLayout_3" ) );
    gridLayout_3->setContentsMargins( 6, 6, 6, 6 );
    gridLayout_3->setSpacing( 6 );

    // ---- Left column: connection settings ----
    auto BindBox        = new QGroupBox( "Bind & Connection", PageHTTP );
    auto bindGrid       = new QGridLayout( BindBox );
    bindGrid->setContentsMargins( 8, 12, 8, 8 );
    bindGrid->setHorizontalSpacing( 8 );
    bindGrid->setVerticalSpacing( 6 );

    bindGrid->addWidget( LabelHostBind,     0, 0 );
    bindGrid->addWidget( ComboHostBind,     0, 1 );
    bindGrid->addWidget( LabelPortBind,     1, 0 );
    bindGrid->addWidget( InputPortBind,     1, 1 );
    bindGrid->addWidget( LabelPortConn,     2, 0 );
    bindGrid->addWidget( InputPortConn,     2, 1 );
    bindGrid->addWidget( LabelHostRotation, 3, 0 );
    bindGrid->addWidget( ComboHostRotation, 3, 1 );
    bindGrid->addWidget( LabelUserAgent,    4, 0 );
    bindGrid->addWidget( InputUserAgent,    4, 1 );
    bindGrid->addWidget( LabelHostHeader,   5, 0 );
    bindGrid->addWidget( InputHostHeader,   5, 1 );
    bindGrid->setColumnStretch( 0, 0 );
    bindGrid->setColumnStretch( 1, 1 );
    bindGrid->setRowStretch( 6, 1 );

    // LabelHosts is now superseded by HostsGroup title; hide it
    LabelHosts->setVisible( false );
    LabelHeaders->setVisible( false );
    LabelUris->setVisible( false );

    // ---- Helper lambda: build a list section (groupbox with scrollable form + Add/Clear) ----
    auto buildListSection = [&]( QGroupBox* group,
                                 const QString& title,
                                 QFormLayout*& formOut,
                                 QPushButton* addBtn,
                                 QPushButton* clearBtn ) -> void
    {
        group->setTitle( title );
        group->setMinimumHeight( 110 );

        auto outerLayout = new QVBoxLayout( group );
        outerLayout->setContentsMargins( 6, 12, 6, 6 );
        outerLayout->setSpacing( 4 );

        auto scroll = new QScrollArea( group );
        scroll->setWidgetResizable( true );
        scroll->setFrameShape( QFrame::NoFrame );
        scroll->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
        scroll->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );

        auto content = new QWidget;
        formOut = new QFormLayout( content );
        formOut->setContentsMargins( 2, 2, 2, 2 );
        formOut->setSpacing( 4 );
        formOut->setFieldGrowthPolicy( QFormLayout::ExpandingFieldsGrow );

        scroll->setWidget( content );
        outerLayout->addWidget( scroll, 1 );

        auto buttonsRow = new QHBoxLayout;
        buttonsRow->setContentsMargins( 0, 0, 0, 0 );
        buttonsRow->addStretch( 1 );
        buttonsRow->addWidget( addBtn );
        buttonsRow->addWidget( clearBtn );
        outerLayout->addLayout( buttonsRow );
    };

    buildListSection( HostsGroup,   "Hosts",   formLayout_Hosts,  ButtonHostsGroupAdd,  ButtonHostsGroupClear );
    buildListSection( HeadersGroup, "Headers", formLayout_Header, ButtonHeaderGroupAdd, ButtonHeaderGroupClear );
    buildListSection( UrisGroup,    "URIs",    formLayout_Uri,    ButtonUriGroupAdd,    ButtonUriGroupClear );

    // ---- Right column: stacked list sections ----
    auto rightCol       = new QWidget( PageHTTP );
    auto rightColLayout = new QVBoxLayout( rightCol );
    rightColLayout->setContentsMargins( 0, 0, 0, 0 );
    rightColLayout->setSpacing( 6 );
    rightColLayout->addWidget( HostsGroup,   1 );
    rightColLayout->addWidget( HeadersGroup, 1 );
    rightColLayout->addWidget( UrisGroup,    1 );

    // ---- Assemble PageHTTP grid ----
    gridLayout_3->addWidget( BindBox,          0, 0, 1, 1 );
    gridLayout_3->addWidget( rightCol,         0, 1, 1, 1 );
    gridLayout_3->addWidget( CheckEnableProxy, 1, 0, 1, 2 );
    gridLayout_3->addWidget( ProxyConfigBox,   2, 0, 1, 2 );

    gridLayout_3->setColumnStretch( 0, 1 );
    gridLayout_3->setColumnStretch( 1, 1 );
    gridLayout_3->setRowStretch( 0, 1 );

    ProxyConfigBox->setEnabled( false );

    InputProxyHost->setReadOnly( true );
    InputProxyPort->setReadOnly( true );
    InputUserName->setReadOnly( true );
    InputPassword->setReadOnly( true );

    InputProxyHost->setPlaceholderText( "" );

    LabelProxyHost->setEnabled( false );
    LabelProxyPort->setEnabled( false );
    LabelUserName->setEnabled( false );
    LabelPassword->setEnabled( false );

    auto style = QString( "color: #9A9AA0;" );
    LabelProxyType->setStyleSheet( style );
    LabelProxyHost->setStyleSheet( style );
    LabelProxyPort->setStyleSheet( style );
    LabelUserName->setStyleSheet( style );
    LabelPassword->setStyleSheet( style );

    // Set a sensible minimum height so the HTTP page does not collapse when
    // the dialog is embedded as a tab with limited vertical space.
    PageHTTP->setMinimumHeight( 560 );

    // Wrap each config page in a QScrollArea so the embedded tab scrolls when
    // its height is constrained, instead of letting children overlap.
    auto wrapInScroll = []( QWidget* page ) -> QScrollArea* {
        auto scroll = new QScrollArea();
        scroll->setWidget( page );
        scroll->setWidgetResizable( true );
        scroll->setFrameShape( QFrame::NoFrame );
        scroll->setHorizontalScrollBarPolicy( Qt::ScrollBarAsNeeded );
        scroll->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );
        return scroll;
    };

    StackWidgetConfigPages->addWidget( wrapInScroll( PageHTTP ) );
    StackWidgetConfigPages->addWidget( wrapInScroll( PageSMB ) );
    StackWidgetConfigPages->addWidget( wrapInScroll( PageExternal ) );

    ListenerDialog->setWindowTitle( "Create Listener" );
    LabelPayload->setText(QCoreApplication::translate("ListenerWidget", "Payload: ", nullptr));
    ComboPayload->setItemText(0, QCoreApplication::translate("ListenerWidget", "Https", nullptr));
    ComboPayload->setItemText(1, QCoreApplication::translate("ListenerWidget", "Http", nullptr));
    ComboPayload->setItemText(2, QCoreApplication::translate("ListenerWidget", "Smb", nullptr));
    ComboPayload->setItemText(3, QCoreApplication::translate("ListenerWidget", "External", nullptr));

    LabelListenerName->setText(QCoreApplication::translate("ListenerWidget", "Name:", nullptr));
    ButtonSave->setText(QCoreApplication::translate("ListenerWidget", "Save", nullptr));
    ButtonClose->setText(QCoreApplication::translate("ListenerWidget", "Close", nullptr));
    ConfigBox->setTitle(QCoreApplication::translate("ListenerWidget", "Config Options", nullptr));
    LabelUserAgent->setText(QCoreApplication::translate("ListenerWidget", "User Agent:  ", nullptr));
    ButtonUriGroupClear->setText(QCoreApplication::translate("ListenerWidget", "Clear", nullptr));
    LabelUris->setText(QCoreApplication::translate("ListenerWidget", "Uris:", nullptr));
    LabelHostHeader->setText(QCoreApplication::translate("ListenerWidget", "Host Header: ", nullptr));
    CheckEnableProxy->setText(QCoreApplication::translate("ListenerWidget", "Enable Proxy connection", nullptr));
    ButtonHeaderGroupClear->setText(QCoreApplication::translate("ListenerWidget", "Clear", nullptr));
    LabelHeaders->setText(QCoreApplication::translate("ListenerWidget", "Headers:", nullptr));
    ButtonHostsGroupAdd->setText(QCoreApplication::translate("ListenerWidget", "Add", nullptr));
    LabelHostBind->setText(QCoreApplication::translate("ListenerWidget", "Host (Bind):", nullptr));
    ButtonUriGroupAdd->setText(QCoreApplication::translate("ListenerWidget", "Add", nullptr));
    LabelHosts->setText(QCoreApplication::translate("ListenerWidget", "Hosts", nullptr));
    ButtonHostsGroupClear->setText(QCoreApplication::translate("ListenerWidget", "Clear", nullptr));
    ButtonHeaderGroupAdd->setText(QCoreApplication::translate("ListenerWidget", "Add", nullptr));
    LabelPortBind->setText(QCoreApplication::translate("ListenerWidget", "PortBind:", nullptr));
    LabelPortConn->setText(QCoreApplication::translate("ListenerWidget", "PortConn:", nullptr));
    LabelProxyType->setText(QCoreApplication::translate("ListenerWidget", "Proxy Type:", nullptr));
    LabelProxyHost->setText(QCoreApplication::translate("ListenerWidget", "Proxy Host:", nullptr));
    LabelProxyPort->setText(QCoreApplication::translate("ListenerWidget", "Proxy Port: ", nullptr));
    LabelUserName->setText(QCoreApplication::translate("ListenerWidget", "UserName: ", nullptr));
    LabelPassword->setText(QCoreApplication::translate("ListenerWidget", "Password: ", nullptr));
    LabelHostRotation->setText(QCoreApplication::translate("ListenerWidget", "Host Rotation: ", nullptr));
    LabelPipeName->setText(QCoreApplication::translate("ListenerWidget", "Pipe Name: ", nullptr));
    LabelEndpoint->setText(QCoreApplication::translate("ListenerWidget", "Endpoint: ", nullptr));

    ComboPayload->addItem( "Https" );
    ComboPayload->addItem( "Http" );
    ComboPayload->addItem( "Smb" );
    ComboPayload->addItem( "External" );

    ComboProxyType->addItem( "http" );
    ComboProxyType->addItem( "https" );

    ComboHostRotation->addItem( "round-robin" );
    ComboHostRotation->addItem( "random" );

    QObject::connect( ButtonSave, &QPushButton::clicked, this, &NewListener::onButton_Save );
    QObject::connect( ButtonClose, &QPushButton::clicked, this, [&]()
    {
        this->DialogClosed = true;
        this->ListenerDialog->close();

        // Free();
    } );

    QObject::connect( ButtonHostsGroupAdd, &QPushButton::clicked, this, [&]()
    {
        auto Item = new QLineEdit;
        Item->setFocus();

        if ( HostsData.size() == 0 ) {
            if ( ! CatedralX::Teamserver.IpAddresses.isEmpty() ) {
                Item->setText( CatedralX::Teamserver.IpAddresses[ 0 ] );
            }
        }

        formLayout_Hosts->setWidget( HostsData.size(), QFormLayout::FieldRole, Item );

        HostsData.push_back( Item );
    } );

    QObject::connect( ButtonHostsGroupClear, &QPushButton::clicked, this, [&]()
    {
        for ( auto& uri : HostsData )
            delete uri;

        HostsData.clear();

    } );

    QObject::connect( ButtonUriGroupAdd, &QPushButton::clicked, this, [&]()
    {
        auto Item = new QLineEdit;
        Item->setFocus();

        formLayout_Uri->setWidget( UrisData.size(), QFormLayout::FieldRole, Item );

        UrisData.push_back( Item );
    } );

    QObject::connect( ButtonUriGroupClear, &QPushButton::clicked, this, [&]()
    {
        for ( auto& uri : UrisData )
            delete uri;

        UrisData.clear();

    } );

    QObject::connect( ButtonHeaderGroupAdd, &QPushButton::clicked, this, [&]()
    {
        auto Item = new QLineEdit;
        Item->setFocus();

        formLayout_Header->setWidget( HeadersData.size(), QFormLayout::FieldRole, Item );

        HeadersData.push_back( Item );
    } );

    QObject::connect( ButtonHeaderGroupClear, &QPushButton::clicked, this, [&]()
    {
        for ( auto& header : HeadersData )
            delete header;

        HeadersData.clear();

    } );

    QObject::connect( ComboPayload, &QComboBox::currentTextChanged, this, [&]( const QString& text )
    {
        if ( text.compare( CatedralSpace::Listener::PayloadHTTPS ) == 0 )
        {
            StackWidgetConfigPages->setCurrentIndex( 0 );
            InputPortBind->setText( "443" );
            InputPortConn->setText( "443" );
        }
        else if ( text.compare( CatedralSpace::Listener::PayloadHTTP ) == 0 )
        {
            StackWidgetConfigPages->setCurrentIndex( 0 );
            InputPortBind->setText( "80" );
            InputPortConn->setText( "80" );
        }
        else if ( text.compare( CatedralSpace::Listener::PayloadSMB ) == 0 )
        {
            StackWidgetConfigPages->setCurrentIndex( 1 );
        }
        else if ( text.compare( CatedralSpace::Listener::PayloadExternal ) == 0 )
        {
            StackWidgetConfigPages->setCurrentIndex( 2 );
        }
        else
        {
            for ( const auto& listener : ServiceListeners )
            {
                if ( listener.Name == text.toStdString() )
                {
                    StackWidgetConfigPages->setCurrentIndex( listener.Index );
                    return;
                }
            }

            spdlog::error( "Payload not found" );
        }
    } );

    QObject::connect( CheckEnableProxy, &QCheckBox::toggled, this, &NewListener::onProxyEnabled );

    QMetaObject::connectSlotsByName( Dialog );
}

MapStrStr NewListener::Start( Util::ListenerItem Item, bool Edit )
{
    auto ListenerInfo = MapStrStr();
    auto Payload      = QString();

    if ( Edit )
    {
        InputListenerName->setText( Item.Name.c_str() );
        InputListenerName->setReadOnly( true );

        if ( ( Item.Protocol == Listener::PayloadHTTP.toStdString() ) || ( Item.Protocol == Listener::PayloadHTTPS.toStdString() ) )
        {
            if ( Item.Protocol == Listener::PayloadHTTPS.toStdString() )
                ComboPayload->setCurrentIndex( 0 );
            else
                ComboPayload->setCurrentIndex( 1 );

            ComboPayload->setDisabled( true );

            auto Info = any_cast<Listener::HTTP>( Item.Info );

            ComboHostBind->addItem( Info.HostBind );
            ComboHostBind->setDisabled( true );

            if ( Info.HostRotation.compare( "round-robin" ) == 0 )
                ComboHostRotation->setCurrentIndex( 0 );
            else if ( Info.HostRotation.compare( "random" ) == 0 )
                ComboHostRotation->setCurrentIndex( 1 );
            else
                ComboHostRotation->setCurrentIndex( 0 );

            InputPortBind->setText( Info.PortBind );
            InputPortBind->setReadOnly( true );

            InputPortConn->setText( Info.PortConn );
            InputPortConn->setReadOnly( true );

            InputUserAgent->setText( Info.UserAgent );
            InputUserAgent->setCursorPosition( 0 );

            if ( ! Info.Hosts.empty() )
            {
                for ( const auto& host : Info.Hosts )
                {
                    if ( host.isEmpty() )
                        continue;

                    auto input = new QLineEdit;
                    input->setText( host );

                    formLayout_Hosts->setWidget( HostsData.size(), QFormLayout::FieldRole, input );

                    HostsData.push_back( input );
                }
            }

            if ( ! Info.Headers.empty() )
            {
                for ( const auto& header : Info.Headers )
                {
                    if ( header.isEmpty() )
                        continue;

                    auto input = new QLineEdit;
                    input->setText( header );

                    formLayout_Header->setWidget( HeadersData.size(), QFormLayout::FieldRole, input );

                    HeadersData.push_back( input );
                }
            }

            if ( ! Info.Uris.empty() )
            {
                for ( const auto& uri : Info.Uris )
                {
                    if ( uri.isEmpty() )
                        continue;

                    auto input = new QLineEdit;
                    input->setText(uri );

                    formLayout_Uri->setWidget(UrisData.size(), QFormLayout::FieldRole, input );

                    UrisData.push_back(input );
                }
            }

            InputHostHeader->setText( Info.HostHeader );

            if ( Info.ProxyEnabled.compare( "true" ) == 0 )
                CheckEnableProxy->setCheckState( Qt::CheckState::Checked );
            else
                CheckEnableProxy->setCheckState( Qt::CheckState::Unchecked );

            if ( Info.ProxyType.compare( "http" ) == 0 )
                ComboProxyType->setCurrentIndex( 0 );
            else
                ComboProxyType->setCurrentIndex( 1 );

            InputProxyHost->setText( Info.ProxyHost );
            InputProxyPort->setText( Info.ProxyPort );
            InputUserName->setText( Info.ProxyUsername );
            InputPassword->setText( Info.ProxyPassword );
        }
        else if ( Item.Protocol == Listener::PayloadSMB.toStdString() )
        {
            ComboPayload->setCurrentIndex( 2 );
            auto Info = any_cast<Listener::SMB>( Item.Info );

            InputPipeName->setText( Info.PipeName );
            InputPipeName->setReadOnly( true );
        }
        else if ( Item.Protocol == Listener::PayloadExternal.toStdString() )
        {
            ComboPayload->setCurrentIndex( 3 );

            auto Info = any_cast<Listener::External>( Item.Info );

            InputEndpoint->setText( Info.Endpoint );
            InputEndpoint->setReadOnly( true );
        }
        else
        {
            // we assume that it's a service listener

            for ( const auto& listener : ServiceListeners )
            {
                if ( listener.Name == Item.Protocol )
                {
                    auto ListenerConfiguration = json::parse( any_cast<Listener::Service>( Item.Info )[ "Info" ] );

                    ComboPayload->setCurrentIndex( listener.Index + 1 );

                    /* TODO: iterate over ServiceListeners and check what has been set
                     *       and blah blah blah just set everything based on the specified object
                     *       and check if its editable etc. */

                    for ( const auto& item : listener.Items )
                    {
                        auto object   = item[ "object" ].get<std::string>();
                        auto editable = item[ "editable" ].get<bool>();
                        auto value    = QString();

                        value = QString( ListenerConfiguration[ item[ "name" ] ].get<std::string>().c_str() );

                        /* if object type is "input" */
                        if ( object == "input" )
                        {
                            auto Line = ( ( QLineEdit* ) item[ "Line" ].get<::uint64_t>() );

                            Line->setText( value );

                            if ( ! editable )
                                Line->setReadOnly( true );
                        }
                    }

                }
            }
        }

        ListenerDialog->setWindowTitle( "Edit Listener" );
        ComboPayload->setDisabled( true );
    }

    ListenerDialog->exec();

    Payload = ComboPayload->currentText();

    ListenerInfo.insert( { "Name",     InputListenerName->text().toStdString() } );
    ListenerInfo.insert( { "Protocol", ComboPayload->currentText().toStdString() } );
    ListenerInfo.insert( { "Status",  "online" } );

    if ( ( Payload.compare( CatedralSpace::Listener::PayloadHTTPS ) == 0 ) || ( Payload.compare( CatedralSpace::Listener::PayloadHTTP ) == 0 ) )
    {
        auto Hosts   = std::string();
        auto Headers = std::string();
        auto Uris    = std::string();

        if ( Payload.compare( CatedralSpace::Listener::PayloadHTTPS ) == 0 )
            ListenerInfo.insert( { "Secure", "true"  } );
        else
            ListenerInfo.insert( { "Secure", "false" } );

        if ( ! HostsData.empty() )
        {
            for ( u32 i = 0; i < HostsData.size(); ++i )
            {
                if ( i == ( HostsData.size() - 1 ) )
                    Hosts += HostsData.at( i )->text().toStdString();
                else
                    Hosts += HostsData.at( i )->text().toStdString() + ", ";

                delete HostsData.at( i );
            }
        }
        else
        {
            Hosts = ComboHostBind->currentText().toStdString();
        }

        if ( ! HeadersData.empty() )
        {
            for ( u32 i = 0; i < HeadersData.size(); ++i )
            {
                if ( i == ( HeadersData.size() - 1 ) )
                    Headers += HeadersData.at( i )->text().toStdString();
                else
                    Headers += HeadersData.at( i )->text().toStdString() + ", ";

                delete HeadersData.at( i );
            }
        }

        if ( ! UrisData.empty() )
        {
            for ( u32 i = 0; i < UrisData.size(); ++i )
            {
                if ( i == ( UrisData.size() - 1 ) )
                    Uris += UrisData.at( i )->text().toStdString();
                else
                    Uris += UrisData.at( i )->text().toStdString() + ", ";

                delete UrisData.at( i );
            }
        }

        ListenerInfo.insert( { "Hosts", Hosts } );
        ListenerInfo.insert( { "HostBind", ComboHostBind->currentText().toStdString() } );
        ListenerInfo.insert( { "HostRotation", ComboHostRotation->currentText().toStdString() } );
        ListenerInfo.insert( { "PortBind", InputPortBind->text().toStdString() } );
        ListenerInfo.insert( { "PortConn", InputPortConn->text().toStdString() } );
        ListenerInfo.insert( { "Headers", Headers } );
        ListenerInfo.insert( { "Uris", Uris } );
        ListenerInfo.insert( { "UserAgent", InputUserAgent->text().toStdString() } );
        ListenerInfo.insert( { "HostHeader", InputHostHeader->text().toStdString() } );

        ListenerInfo.insert( { "Proxy Enabled", CheckEnableProxy->isChecked() ? "true" : "false" } );

        if ( CheckEnableProxy->isChecked() )
        {
            ListenerInfo.insert( { "Proxy Type", ComboProxyType->currentText().toStdString() } );
            ListenerInfo.insert( { "Proxy Host", InputProxyHost->text().toStdString() } );
            ListenerInfo.insert( { "Proxy Port", InputProxyPort->text().toStdString() } );
            ListenerInfo.insert( { "Proxy Username", InputUserName->text().toStdString() } );
            ListenerInfo.insert( { "Proxy Password", InputPassword->text().toStdString() } );
        }
    }
    else if ( Payload.compare( CatedralSpace::Listener::PayloadSMB ) == 0 )
    {
        ListenerInfo.insert( { "PipeName", InputPipeName->text().toStdString() } );
    }
    else if ( Payload.compare( CatedralSpace::Listener::PayloadExternal ) == 0 )
    {
        for ( auto& Listener : CatedralX::Teamserver.Listeners )
        {
            if ( Listener.Protocol == CatedralSpace::Listener::PayloadExternal.toStdString() )
            {
                if ( any_cast<CatedralSpace::Listener::External>( Listener.Info ).Endpoint.compare( InputEndpoint->text() ) == 0 )
                {
                    MessageBox( "Listener Error", "Listener External: Endpoint already registered.", QMessageBox::Icon::Critical );
                    return MapStrStr{};
                }
            }
        }

        ListenerInfo.insert( { "Endpoint", InputEndpoint->text().toStdString() } );
    }
    else
    {
        for ( const auto& listener : ServiceListeners )
        {
            if ( listener.Name == Payload.toStdString() )
            {
                auto Listener = MapStrStr{
                    { "Name",       InputListenerName->text().toStdString() },
                    { "Protocol",   listener.Name },
                    { "ClientUser", CatedralX::Teamserver.User.toStdString() },
                };

                for ( const auto& item : listener.Items )
                {
                    auto object = QString( item[ "object" ].get<std::string>().c_str() );

                    if ( object == "input" )
                    {
                        auto Name = item[ "name" ].get<std::string>();
                        auto Line = ( QLineEdit* ) item[ "Line" ].get<::uint64_t>();

                        Listener.insert( { Name, Line->text().toStdString() } );
                    }
                }

                return Listener;
            }
        }

        spdlog::error( "Payload not found" );

        return {};
    }

    return ListenerInfo;
}

MapStrStr CatedralNamespace::UserInterface::Dialogs::NewListener::collectInfo() const
{
    auto ListenerInfo = MapStrStr();
    auto Payload      = ComboPayload->currentText();

    ListenerInfo.insert( { "Name",     InputListenerName->text().toStdString() } );
    ListenerInfo.insert( { "Protocol", ComboPayload->currentText().toStdString() } );
    ListenerInfo.insert( { "Status",  "online" } );

    if ( ( Payload.compare( CatedralSpace::Listener::PayloadHTTPS ) == 0 ) || ( Payload.compare( CatedralSpace::Listener::PayloadHTTP ) == 0 ) )
    {
        auto Hosts   = std::string();
        auto Headers = std::string();
        auto Uris    = std::string();

        if ( Payload.compare( CatedralSpace::Listener::PayloadHTTPS ) == 0 )
            ListenerInfo.insert( { "Secure", "true"  } );
        else
            ListenerInfo.insert( { "Secure", "false" } );

        if ( ! HostsData.empty() )
        {
            for ( u32 i = 0; i < HostsData.size(); ++i )
            {
                if ( i == ( HostsData.size() - 1 ) )
                    Hosts += HostsData.at( i )->text().toStdString();
                else
                    Hosts += HostsData.at( i )->text().toStdString() + ", ";
                // NOTE: do NOT delete here — the dialog is still alive in tab mode
            }
        }
        else
        {
            Hosts = ComboHostBind->currentText().toStdString();
        }

        if ( ! HeadersData.empty() )
        {
            for ( u32 i = 0; i < HeadersData.size(); ++i )
            {
                if ( i == ( HeadersData.size() - 1 ) )
                    Headers += HeadersData.at( i )->text().toStdString();
                else
                    Headers += HeadersData.at( i )->text().toStdString() + ", ";
            }
        }

        if ( ! UrisData.empty() )
        {
            for ( u32 i = 0; i < UrisData.size(); ++i )
            {
                if ( i == ( UrisData.size() - 1 ) )
                    Uris += UrisData.at( i )->text().toStdString();
                else
                    Uris += UrisData.at( i )->text().toStdString() + ", ";
            }
        }

        ListenerInfo.insert( { "Hosts", Hosts } );
        ListenerInfo.insert( { "HostBind", ComboHostBind->currentText().toStdString() } );
        ListenerInfo.insert( { "HostRotation", ComboHostRotation->currentText().toStdString() } );
        ListenerInfo.insert( { "PortBind", InputPortBind->text().toStdString() } );
        ListenerInfo.insert( { "PortConn", InputPortConn->text().toStdString() } );
        ListenerInfo.insert( { "Headers", Headers } );
        ListenerInfo.insert( { "Uris", Uris } );
        ListenerInfo.insert( { "UserAgent", InputUserAgent->text().toStdString() } );
        ListenerInfo.insert( { "HostHeader", InputHostHeader->text().toStdString() } );

        ListenerInfo.insert( { "Proxy Enabled", CheckEnableProxy->isChecked() ? "true" : "false" } );

        if ( CheckEnableProxy->isChecked() )
        {
            ListenerInfo.insert( { "Proxy Type", ComboProxyType->currentText().toStdString() } );
            ListenerInfo.insert( { "Proxy Host", InputProxyHost->text().toStdString() } );
            ListenerInfo.insert( { "Proxy Port", InputProxyPort->text().toStdString() } );
            ListenerInfo.insert( { "Proxy Username", InputUserName->text().toStdString() } );
            ListenerInfo.insert( { "Proxy Password", InputPassword->text().toStdString() } );
        }
    }
    else if ( Payload.compare( CatedralSpace::Listener::PayloadSMB ) == 0 )
    {
        ListenerInfo.insert( { "PipeName", InputPipeName->text().toStdString() } );
    }
    else if ( Payload.compare( CatedralSpace::Listener::PayloadExternal ) == 0 )
    {
        for ( auto& Listener : CatedralX::Teamserver.Listeners )
        {
            if ( Listener.Protocol == CatedralSpace::Listener::PayloadExternal.toStdString() )
            {
                if ( any_cast<CatedralSpace::Listener::External>( Listener.Info ).Endpoint.compare( InputEndpoint->text() ) == 0 )
                {
                    MessageBox( "Listener Error", "Listener External: Endpoint already registered.", QMessageBox::Icon::Critical );
                    return MapStrStr{};
                }
            }
        }

        ListenerInfo.insert( { "Endpoint", InputEndpoint->text().toStdString() } );
    }
    else
    {
        for ( const auto& listener : ServiceListeners )
        {
            if ( listener.Name == Payload.toStdString() )
            {
                auto Listener = MapStrStr{
                    { "Name",       InputListenerName->text().toStdString() },
                    { "Protocol",   listener.Name },
                    { "ClientUser", CatedralX::Teamserver.User.toStdString() },
                };

                for ( const auto& item : listener.Items )
                {
                    auto object = QString( item[ "object" ].get<std::string>().c_str() );

                    if ( object == "input" )
                    {
                        auto Name = item[ "name" ].get<std::string>();
                        auto Line = ( QLineEdit* ) item[ "Line" ].get<::uint64_t>();

                        Listener.insert( { Name, Line->text().toStdString() } );
                    }
                }

                return Listener;
            }
        }

        spdlog::error( "Payload not found" );

        return {};
    }

    return ListenerInfo;
}

auto NewListener::ListenerCustomAdd( QString Json ) -> bool
{
    if ( Json.isEmpty() )
        return false;

    auto Listener = json::parse( Json.toStdString() );
    auto Page     = ( QWidget* )     nullptr;
    auto Layout   = ( QFormLayout* ) nullptr;
    auto Service  = ServiceListener();

    Page    = new QWidget;
    Layout  = new QFormLayout( Page );
    Service = {
        .Name   = Listener[ "Name" ],
        .Page   = Page,
        .Layout = Layout,
        .Index  = StackWidgetConfigPages->count()
    };

    for ( auto Item : Listener[ "Items" ] )
    {
        if ( Item[ "object" ] == "input" )
        {
            auto Label = new QLabel( Page );
            auto Line  = new QLineEdit( Page );
            auto index = Service.Items.size();

            Label->setText( Item[ "text" ].get<std::string>().c_str() );
            Line->setPlaceholderText( Item[ "placeholder" ].get<std::string>().c_str() );

            Layout->setWidget( index, QFormLayout::LabelRole, Label );
            Layout->setWidget( index, QFormLayout::FieldRole, Line  );

            Service.Items.push_back( {
                { "name",     Item[ "name" ]     },
                { "object",   Item[ "object" ]   },
                { "required", Item[ "required" ] },
                { "editable", Item[ "editable" ] },
                { "Label",    ( uint64_t ) Label },
                { "Line",     ( uint64_t ) Line  },
            } );
        }
    }

    ServiceListeners.push_back( Service );
    ComboPayload->addItem( Service.Name.c_str() );
    StackWidgetConfigPages->addWidget( Page );

    /* check if we already registered this listener */
    for ( auto& x : CatedralX::Teamserver.RegisteredListeners )
    {
        if ( x[ "Name" ] == Listener[ "Name" ] )
            return false;
    }

    /* if not then lets add it. */
    CatedralX::Teamserver.RegisteredListeners.push_back( Listener );

    return true;
}

void CatedralNamespace::UserInterface::Dialogs::NewListener::onButton_Save()
{
    auto Payload = ComboPayload->currentText();

    if ( ( Payload.compare( CatedralSpace::Listener::PayloadHTTPS ) == 0 ) ||
         ( Payload.compare( CatedralSpace::Listener::PayloadHTTP  ) == 0 ) )
    {
        if ( InputListenerName->text().isEmpty() )
        {
            MessageBox( "Listener Error", "No Listener Name specified", QMessageBox::Critical );

            return;
        }

        if ( InputPortBind->text().isEmpty() )
        {
            MessageBox( "Listener Error", "No PortBind specified", QMessageBox::Critical );

            return;
        }
        else
        {
            if ( ! is_number( InputPortBind->text().toStdString() ) )
            {
                MessageBox( "Listener Error", "PortBind is not a number", QMessageBox::Critical );

                return;
            }
        }

        if ( InputPortConn->text().isEmpty() )
        {
            MessageBox( "Listener Error", "No PortConn specified", QMessageBox::Critical );

            return;
        }
        else
        {
            if ( ! is_number( InputPortConn->text().toStdString() ) )
            {
                MessageBox( "Listener Error", "PortConn is not a number", QMessageBox::Critical );

                return;
            }
        }

        if ( InputUserAgent->text().isEmpty() )
        {
            MessageBox( "Listener Error", "No UserAgent specified", QMessageBox::Critical );

            return;
        }

        if ( CheckEnableProxy->isChecked() )
        {
            if ( InputProxyHost->text().isEmpty() )
            {
                MessageBox( "Listener Error", "No Proxy Host specified", QMessageBox::Critical );

                return;
            }

            if ( InputProxyPort->text().isEmpty() )
            {
                MessageBox( "Listener Error", "No Proxy Port specified", QMessageBox::Critical );

                return;
            }
            else
            {
                if ( ! is_number( InputProxyPort->text().toStdString() ) )
                {
                    MessageBox( "Listener Error", "Port is not a number", QMessageBox::Critical );
                    return;
                }
            }
        }

    }
    else if ( Payload.compare( CatedralSpace::Listener::PayloadSMB )  == 0 )
    {
        if ( InputPipeName->text().isEmpty() )
        {
            MessageBox( "Listener Error", "No Pipe name specified", QMessageBox::Critical );

            return;
        }
    }
    else if ( Payload.compare( CatedralSpace::Listener::PayloadExternal )  == 0 )
    {
        if ( InputEndpoint->text().isEmpty() )
        {
            MessageBox( "Listener Error", "No Endpoint specified", QMessageBox::Critical );

            return;
        }
    }
    else
    {
        for ( const auto& listener : ServiceListeners )
        {
            if ( Payload.compare( listener.Name.c_str() ) == 0 )
            {
                for ( auto item : listener.Items )
                {
                    auto object = item[ "object" ].get<std::string>();

                    /* if object type is "input" */
                    if ( object == "input" )
                    {
                        auto Line = ( ( QLineEdit* ) item[ "Line" ].get<::uint64_t>() );

                        /* if the operator didn't specify a value that is required then let that operator know. */
                        if ( item[ "required" ].get<bool>() && Line->text().isEmpty() )
                        {
                            auto itemName = QString( item[ "name" ].get<std::string>().c_str() );
                            MessageBox( "Listener Error", "No " + itemName + " specified", QMessageBox::Critical );
                            return;
                        }
                    }

                }
            }
        }
    }

    this->DialogSaved = true;
    emit listenerSaved();
    this->ListenerDialog->close();
}

void CatedralNamespace::UserInterface::Dialogs::NewListener::onProxyEnabled()
{
    if ( CheckEnableProxy->isChecked() )
    {
        ProxyConfigBox->setEnabled( true );

        auto style = QString( "color: #E6E6E6;" );
        LabelProxyType->setStyleSheet( style );
        LabelProxyHost->setStyleSheet( style );
        LabelProxyPort->setStyleSheet( style );
        LabelUserName->setStyleSheet( style );
        LabelPassword->setStyleSheet( style );

        InputProxyHost->setReadOnly( false );
        InputProxyPort->setReadOnly( false );
        InputUserName->setReadOnly( false );
        InputPassword->setReadOnly( false );

        LabelProxyHost->setEnabled( false );
        LabelProxyPort->setEnabled( false );
        LabelUserName->setEnabled( false );
        LabelPassword->setEnabled( false );
    }
    else
    {
        ProxyConfigBox->setEnabled( false );

        auto style = QString( "color: #9A9AA0;" );
        LabelProxyType->setStyleSheet( style );
        LabelProxyHost->setStyleSheet( style );
        LabelProxyPort->setStyleSheet( style );
        LabelUserName->setStyleSheet( style );
        LabelPassword->setStyleSheet( style );

        InputProxyHost->setReadOnly( true );
        InputProxyPort->setReadOnly( true );
        InputUserName->setReadOnly( true );
        InputPassword->setReadOnly( true );

        LabelProxyHost->setEnabled( true );
        LabelProxyPort->setEnabled( true );
        LabelUserName->setEnabled( true );
        LabelPassword->setEnabled( true );
    }
}

auto NewListener::Free() -> void
{
    for ( auto listener : ServiceListeners )
    {
        for ( auto item : listener.Items )
        {
            // delete ( QLabel* )    listener.Items[ item ][ "Label" ].get<uint64_t>();
            // delete ( QLineEdit* ) listener.Items[ item ][ "Line"  ].get<uint64_t>();
        }

        delete listener.Layout;
        delete listener.Page;
    }
}
