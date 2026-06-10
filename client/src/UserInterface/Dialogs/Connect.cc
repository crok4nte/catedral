#include <global.hpp>

#include <Catedral/DBManager/DBManager.hpp>
#include <Catedral/Connector.hpp>
#include <Catedral/Catedral.hpp>

#include <UserInterface/Dialogs/Connect.hpp>

#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>

namespace {

// Pequeño helper para una etiqueta de campo (caption) sobre cada input.
QLabel* FieldCaption( QWidget* parent, const QString& text )
{
    auto* l = new QLabel( text, parent );
    l->setObjectName( "ConnectFieldCaption" );
    return l;
}

// Construye un campo (caption + input) dentro de un layout vertical compacto.
QVBoxLayout* FieldBlock( QLabel* caption, QLineEdit* input )
{
    auto* v = new QVBoxLayout();
    v->setSpacing( 4 );
    v->setContentsMargins( 0, 0, 0, 0 );
    v->addWidget( caption );
    v->addWidget( input );
    return v;
}

} // namespace

void CatedralNamespace::UserInterface::Dialogs::Connect::setupUi( QDialog* Form )
{
    this->ConnectDialog = Form;

    if ( Form->objectName().isEmpty() )
        Form->setObjectName( QString::fromUtf8( "Form" ) );

    Form->setObjectName( "ConnectDialog" );
    Form->resize( 760, 480 );
    Form->setMinimumSize( QSize( 760, 480 ) );
    Form->setMaximumSize( QSize( 760, 480 ) );

    // El dialogo corre antes de que la ventana principal aplique el tema,
    // por eso lo estilizamos aqui directamente con el QSS global de Catedral.
    Form->setStyleSheet( FileRead( ":/stylesheets/Catedral" ) );

    // ---- Layout raiz: dos paneles (brand | formulario) ----
    auto* root = new QHBoxLayout( Form );
    root->setContentsMargins( 0, 0, 0, 0 );
    root->setSpacing( 0 );

    // =====================================================================
    //  Panel izquierdo: marca + lista de perfiles
    // =====================================================================
    brandPanel = new QFrame( Form );
    brandPanel->setObjectName( "ConnectBrand" );
    brandPanel->setFixedWidth( 280 );

    auto* brandLayout = new QVBoxLayout( brandPanel );
    brandLayout->setContentsMargins( 24, 28, 24, 24 );
    brandLayout->setSpacing( 0 );

    brandGlyph = new QLabel( "\xE2\x9B\xAA", brandPanel ); // ⛪ glifo catedral
    brandGlyph->setObjectName( "ConnectBrandGlyph" );

    brandTitle = new QLabel( "CATEDRAL", brandPanel );
    brandTitle->setObjectName( "ConnectBrandTitle" );

    brandTagline = new QLabel( "Command & Control", brandPanel );
    brandTagline->setObjectName( "ConnectBrandTagline" );

    profilesCaption = new QLabel( "TEAMSERVER PROFILES", brandPanel );
    profilesCaption->setObjectName( "ConnectSectionCaption" );

    listContextMenu = new QMenu( this );
    listContextMenu->addAction( "Remove", this, &Connect::itemRemove );
    listContextMenu->addAction( "Clear",  this, &Connect::itemsClear );

    listWidget = new QListWidget( brandPanel );
    listWidget->setObjectName( "ConnectProfileList" );
    listWidget->setContextMenuPolicy( Qt::CustomContextMenu );
    listWidget->addAction( listContextMenu->menuAction() );

    ButtonNewProfile = new QPushButton( "+  New Profile", brandPanel );
    ButtonNewProfile->setObjectName( "ConnectNewProfile" );
    ButtonNewProfile->setCursor( Qt::PointingHandCursor );
    ButtonNewProfile->setMinimumHeight( 34 );

    brandVersion = new QLabel( brandPanel );
    brandVersion->setObjectName( "ConnectBrandVersion" );
    brandVersion->setText( QString( "v%1  ·  %2" )
        .arg( QString::fromStdString( CatedralNamespace::Version ) )
        .arg( QString::fromStdString( CatedralNamespace::CodeName ) ) );

    brandLayout->addWidget( brandGlyph );
    brandLayout->addWidget( brandTitle );
    brandLayout->addWidget( brandTagline );
    brandLayout->addSpacing( 28 );
    brandLayout->addWidget( profilesCaption );
    brandLayout->addSpacing( 8 );
    brandLayout->addWidget( listWidget, /*stretch=*/1 );
    brandLayout->addSpacing( 10 );
    brandLayout->addWidget( ButtonNewProfile );
    brandLayout->addSpacing( 14 );
    brandLayout->addWidget( brandVersion );

    // =====================================================================
    //  Panel derecho: formulario de conexion
    // =====================================================================
    formPanel = new QFrame( Form );
    formPanel->setObjectName( "ConnectForm" );

    auto* formLayout = new QVBoxLayout( formPanel );
    formLayout->setContentsMargins( 36, 34, 36, 30 );
    formLayout->setSpacing( 0 );

    formHeader = new QLabel( "Connect to Teamserver", formPanel );
    formHeader->setObjectName( "ConnectFormHeader" );

    formHint = new QLabel( "Authenticate against a running Catedral teamserver.", formPanel );
    formHint->setObjectName( "ConnectFormHint" );
    formHint->setWordWrap( true );

    // -- Campos --
    label_Name = FieldCaption( formPanel, "PROFILE NAME" );
    lineEdit_Name = new QLineEdit( formPanel );
    lineEdit_Name->setObjectName( "lineEdit_Name" );
    lineEdit_Name->setPlaceholderText( "e.g. Operation Spire" );
    lineEdit_Name->setMinimumHeight( 34 );

    label_Host = FieldCaption( formPanel, "HOST" );
    lineEdit_Host = new QLineEdit( formPanel );
    lineEdit_Host->setObjectName( "lineEdit_Host" );
    lineEdit_Host->setPlaceholderText( "127.0.0.1" );
    lineEdit_Host->setMinimumHeight( 34 );

    label_Port = FieldCaption( formPanel, "PORT" );
    lineEdit_Port = new QLineEdit( formPanel );
    lineEdit_Port->setObjectName( "lineEdit_Port" );
    lineEdit_Port->setPlaceholderText( "40056" );
    lineEdit_Port->setMinimumHeight( 34 );
    lineEdit_Port->setMaximumWidth( 140 );

    label_User = FieldCaption( formPanel, "OPERATOR" );
    lineEdit_User = new QLineEdit( formPanel );
    lineEdit_User->setObjectName( "lineEdit_User" );
    lineEdit_User->setPlaceholderText( "operator handle" );
    lineEdit_User->setMinimumHeight( 34 );

    label_Password = FieldCaption( formPanel, "PASSWORD" );
    lineEdit_Password = new QLineEdit( formPanel );
    lineEdit_Password->setObjectName( "lineEdit_Password" );
    lineEdit_Password->setEchoMode( QLineEdit::Password );
    lineEdit_Password->setPlaceholderText( "••••••••" );
    lineEdit_Password->setMinimumHeight( 34 );

    ButtonConnect = new QPushButton( "Connect", formPanel );
    ButtonConnect->setObjectName( "ConnectSubmit" );
    ButtonConnect->setProperty( "primary", true );
    ButtonConnect->setCursor( Qt::PointingHandCursor );
    ButtonConnect->setMinimumHeight( 40 );

    // Fila Host + Port lado a lado.
    auto* hostPortRow = new QHBoxLayout();
    hostPortRow->setSpacing( 14 );
    hostPortRow->addLayout( FieldBlock( label_Host, lineEdit_Host ), /*stretch=*/1 );
    hostPortRow->addLayout( FieldBlock( label_Port, lineEdit_Port ) );

    formLayout->addWidget( formHeader );
    formLayout->addSpacing( 4 );
    formLayout->addWidget( formHint );
    formLayout->addSpacing( 24 );
    formLayout->addLayout( FieldBlock( label_Name, lineEdit_Name ) );
    formLayout->addSpacing( 14 );
    formLayout->addLayout( hostPortRow );
    formLayout->addSpacing( 14 );
    formLayout->addLayout( FieldBlock( label_User, lineEdit_User ) );
    formLayout->addSpacing( 14 );
    formLayout->addLayout( FieldBlock( label_Password, lineEdit_Password ) );
    formLayout->addStretch( 1 );
    formLayout->addWidget( ButtonConnect );

    root->addWidget( brandPanel );
    root->addWidget( formPanel, /*stretch=*/1 );

    // Compatibilidad: widgets heredados que ya no se muestran.
    plainTextEdit    = nullptr;
    gridLayout       = nullptr;
    horizontalSpacer = nullptr;

    paletteGray = new QPalette();
    paletteGray->setColor( QPalette::Base, Qt::gray );

    paletteWhite = new QPalette();
    paletteWhite->setColor( QPalette::Base, Qt::white );

    Form->setWindowTitle( "Catedral — Connect" );

    ButtonConnect->setFocus();

    connect( listWidget, &QListWidget::itemPressed, this, &Connect::itemSelected );
    connect( listWidget, &QListWidget::customContextMenuRequested, this, &Connect::handleContextMenu );

    connect( lineEdit_Name, &QLineEdit::returnPressed, this, [&](){
        onButton_Connect();
    } );

    connect( lineEdit_User, &QLineEdit::returnPressed, this, [&](){
        onButton_Connect();
    } );

    connect( lineEdit_Host, &QLineEdit::returnPressed, this, [&](){
        onButton_Connect();
    } );

    connect( lineEdit_Port, &QLineEdit::returnPressed, this, [&](){
        onButton_Connect();
    } );

    connect( lineEdit_Password, &QLineEdit::returnPressed, this, [&](){
        onButton_Connect();
    } );

    QMetaObject::connectSlotsByName( Form );
}

Util::ConnectionInfo CatedralNamespace::UserInterface::Dialogs::Connect::StartDialog( bool FromAction )
{
    auto ProfileName = std::string();

    listWidget->clear();

    for ( auto & TeamserverConnection : TeamserverList )
    {
        listWidget->addItem( TeamserverConnection.Name );
    }

    listWidget->setCurrentRow( 0 );

    if ( ! listWidget->selectedItems().empty() )
        this->itemSelected();
    else
        this->isNewProfile = true;

    connect( ButtonConnect,    &QPushButton::clicked, this, &Connect::onButton_Connect );
    connect( ButtonNewProfile, &QPushButton::clicked, this, &Connect::onButton_NewProfile );

    ConnectDialog->exec();

    auto ConnectionInfo = new Util::ConnectionInfo;

    ConnectionInfo->Name     = lineEdit_Name->text();
    ConnectionInfo->Host     = lineEdit_Host->text();
    ConnectionInfo->Port     = lineEdit_Port->text();
    ConnectionInfo->User     = lineEdit_User->text();
    ConnectionInfo->Password = lineEdit_Password->text();

    ProfileName = ConnectionInfo->Name.toStdString();

    if ( this->tryConnect )
    {
        auto ConnectionInstant = new Connector( ConnectionInfo );

        CatedralX::Teamserver = *ConnectionInfo;
        CatedralX::Connector  = ConnectionInstant;

        if ( this->isNewProfile ) {
            if ( ! this->dbManager->addTeamserverInfo( *ConnectionInfo ) ) {
                spdlog::warn( "Failed to add Teamserver Info to database" );
            }
        }
        else if ( ConnectionInstant->ErrorString == nullptr ) {
            spdlog::info( "Connecting to profile: {}", ProfileName );
        } else {
            spdlog::critical( "Couldn't connect to profile: {}", ProfileName );
            Catedral::Exit();
        }

    } else {

        if (!FromAction) {
            spdlog::info("Exit program from Connection Dialog");
            CatedralNamespace::CatedralSpace::Catedral::Exit();
        }

    }

    return *ConnectionInfo;
}

void CatedralNamespace::UserInterface::Dialogs::Connect::passDB(CatedralNamespace::CatedralSpace::DBManager* db)
{
    this->dbManager = db;
}

void CatedralNamespace::UserInterface::Dialogs::Connect::onButton_Connect()
{
    if ( lineEdit_Name->text().isEmpty() )
    {
        auto MessageBox = QMessageBox();
        MessageBox.setWindowTitle( "Error" );
        MessageBox.setText( "Name is empty" );
        MessageBox.setIcon( QMessageBox::Critical );
        // removed in Catedral Phase 3 (legacy stylesheet)
        // MessageBox.setStyleSheet( FileRead( ":/stylesheets/MessageBox" ) );
        MessageBox.exec();

        return;
    }

    if ( lineEdit_Host->text().isEmpty() )
    {
        auto MessageBox = QMessageBox();

        MessageBox.setWindowTitle( "Error" );
        MessageBox.setText( "Host is empty" );
        MessageBox.setIcon( QMessageBox::Critical );
        // removed in Catedral Phase 3 (legacy stylesheet)
        // MessageBox.setStyleSheet( FileRead( ":/stylesheets/MessageBox" ) );
        MessageBox.exec();

        return;
    }

    if ( lineEdit_Port->text().isEmpty()  )
    {
        auto MessageBox = QMessageBox();

        MessageBox.setWindowTitle( "Error" );
        MessageBox.setText( "Port is empty" );
        MessageBox.setIcon( QMessageBox::Critical );
        // removed in Catedral Phase 3 (legacy stylesheet)
        // MessageBox.setStyleSheet( FileRead( ":/stylesheets/MessageBox" ) );
        MessageBox.exec();

        return;
    }

    if ( lineEdit_User->text().isEmpty() )
    {
        auto MessageBox = QMessageBox();

        MessageBox.setWindowTitle( "Error" );
        MessageBox.setText( "User is empty" );
        MessageBox.setIcon( QMessageBox::Critical );
        // removed in Catedral Phase 3 (legacy stylesheet)
        // MessageBox.setStyleSheet( FileRead( ":/stylesheets/MessageBox" ) );
        MessageBox.exec();

        return;
    }

    if ( lineEdit_Password->text().isEmpty() )
    {
        auto MessageBox = QMessageBox();

        MessageBox.setWindowTitle( "Error" );
        MessageBox.setText( "Password is empty" );
        MessageBox.setIcon( QMessageBox::Critical );
        // removed in Catedral Phase 3 (legacy stylesheet)
        // MessageBox.setStyleSheet( FileRead( ":/stylesheets/MessageBox" ) );
        MessageBox.exec();

        return;
    }

    if ( this->dbManager->checkTeamserverExists( lineEdit_Name->text() ) && this->isNewProfile )
    {
        auto MessageBox = QMessageBox();

        MessageBox.setWindowTitle( "Error" );
        MessageBox.setText( "Profile Name already exists" );
        MessageBox.setIcon( QMessageBox::Critical );
        // removed in Catedral Phase 3 (legacy stylesheet)
        // MessageBox.setStyleSheet( FileRead( ":/stylesheets/MessageBox" ) );
        MessageBox.exec();

        return;
    }

    this->tryConnect = true;
    this->listWidget->addItem( lineEdit_Name->text() );
    this->ConnectDialog->close();
}

void CatedralNamespace::UserInterface::Dialogs::Connect::itemSelected()
{
    auto ProfileName = listWidget->currentItem()->text();
    this->isNewProfile = false;

    for ( auto& Profile : TeamserverList )
    {
        if ( Profile.Name == ProfileName )
        {
            lineEdit_Name->setPalette( *paletteGray );
            lineEdit_Name->setReadOnly( true );
            lineEdit_Name->setText( Profile.Name );
            lineEdit_Host->setText( Profile.Host );
            lineEdit_Port->setText( Profile.Port );
            lineEdit_User->setText( Profile.User );
            lineEdit_Password->setText( Profile.Password );
        }
    }

    ButtonConnect->setFocus();
}

void CatedralNamespace::UserInterface::Dialogs::Connect::onButton_NewProfile()
{
    this->isNewProfile = true;

    listWidget->setCurrentIndex(QModelIndex());

    lineEdit_Name->clear();
    lineEdit_Name->setPalette(*paletteWhite);
    lineEdit_Name->setReadOnly(false);

    lineEdit_Host->setText( "127.0.0.1" );
    lineEdit_Port->setText( "40056" );
    lineEdit_User->clear();
    lineEdit_Password->clear();

    lineEdit_Name->setFocus();
}

void CatedralNamespace::UserInterface::Dialogs::Connect::handleContextMenu( const QPoint &pos )
{
    auto globalPos = listWidget->mapToGlobal( pos );
    listContextMenu->exec( globalPos );
}

void CatedralNamespace::UserInterface::Dialogs::Connect::itemRemove()
{
    for ( int i = 0; i < listWidget->selectedItems().size(); ++i )
    {
        auto item = listWidget->takeItem( listWidget->currentRow() );

        this->dbManager->removeTeamserverInfo( item->text() );

        delete item;
    }

    this->onButton_NewProfile();
}

void CatedralNamespace::UserInterface::Dialogs::Connect::itemsClear()
{
    this->listWidget->clear();
    this->dbManager->removeAllTeamservers();
    this->onButton_NewProfile();
}
