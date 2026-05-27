#include <UserInterface/Widgets/CatedralSidebar.hpp>

#include <QIcon>
#include <QSize>

CatedralSidebar::CatedralSidebar( QWidget* parent )
    : QFrame( parent )
{
    setObjectName( "CatedralSidebar" );
    setFixedWidth( 60 );
    setFrameShape( QFrame::NoFrame );

    Layout = new QVBoxLayout( this );
    Layout->setContentsMargins( 6, 10, 6, 10 );
    Layout->setSpacing( 6 );
    Layout->setAlignment( Qt::AlignTop );

    Group = new QButtonGroup( this );
    Group->setExclusive( true );
}

QToolButton* CatedralSidebar::addItem( const QString& iconResource,
                                       const QString& tooltip,
                                       QAction* action )
{
    auto* btn = new QToolButton( this );
    btn->setObjectName( "CatedralSidebarItem" );
    btn->setIcon( QIcon( iconResource ) );
    btn->setIconSize( QSize( 32, 32 ) );
    btn->setFixedSize( QSize( 48, 48 ) );
    btn->setToolTip( tooltip );
    btn->setToolButtonStyle( Qt::ToolButtonIconOnly );
    btn->setCheckable( true );
    btn->setAutoRaise( true );

    if ( action != nullptr ) {
        QObject::connect( btn, &QToolButton::clicked, action, &QAction::trigger );
    }

    Layout->addWidget( btn );
    Group->addButton( btn );
    return btn;
}

void CatedralSidebar::addStretch()
{
    Layout->addStretch( 1 );
}
