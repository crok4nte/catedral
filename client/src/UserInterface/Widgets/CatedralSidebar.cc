#include <UserInterface/Widgets/CatedralSidebar.hpp>

#include <QIcon>
#include <QSize>
#include <QPixmap>
#include <QPainter>
#include <QColor>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QVariantAnimation>
#include <QSettings>

namespace {

// Recolorea un icono (SVG/PNG monocromo) por estado del QToolButton.
// Reposo: gris neutro. Hover (Active): gris claro. Activo (On): azul acento.
QIcon TintedIcon( const QString& resource, int px )
{
    const QPixmap base = QIcon( resource ).pixmap( QSize( px, px ) );

    auto tint = [&]( const QColor& c ) {
        QPixmap p = base;
        QPainter painter( &p );
        painter.setCompositionMode( QPainter::CompositionMode_SourceIn );
        painter.fillRect( p.rect(), c );
        painter.end();
        return p;
    };

    QIcon icon;
    icon.addPixmap( tint( QColor( "#9A9AA0" ) ), QIcon::Normal, QIcon::Off );  // reposo
    icon.addPixmap( tint( QColor( "#C8CDD4" ) ), QIcon::Active, QIcon::Off );  // hover
    icon.addPixmap( tint( QColor( "#6E8FB0" ) ), QIcon::Normal, QIcon::On  );  // activo
    icon.addPixmap( tint( QColor( "#6E8FB0" ) ), QIcon::Active, QIcon::On  );  // activo+hover
    return icon;
}

} // namespace

CatedralSidebar::CatedralSidebar( QWidget* parent )
    : QFrame( parent )
    , Expanded( false )
{
    setObjectName( "CatedralSidebar" );
    setFrameShape( QFrame::NoFrame );

    Layout = new QVBoxLayout( this );
    Layout->setContentsMargins( 4, 8, 4, 8 );
    Layout->setSpacing( 4 );
    Layout->setAlignment( Qt::AlignTop );

    Group = new QButtonGroup( this );
    Group->setExclusive( true );

    // Boton toggle (logo / hamburguesa) que despliega o colapsa la barra.
    ToggleButton = new QToolButton( this );
    ToggleButton->setObjectName( "CatedralSidebarToggle" );
    ToggleButton->setIconSize( QSize( IconPx, IconPx ) );
    ToggleButton->setFixedHeight( ItemHeight );
    ToggleButton->setToolTip( "Expandir / colapsar menu" );
    ToggleButton->setToolButtonStyle( Qt::ToolButtonIconOnly );
    ToggleButton->setAutoRaise( true );
    ToggleButton->setCursor( Qt::PointingHandCursor );
    QObject::connect( ToggleButton, &QToolButton::clicked, this, &CatedralSidebar::toggle );
    Layout->addWidget( ToggleButton );

    // Animacion del ancho (despliegue fluido). Mantiene min == max durante el tween.
    WidthAnim = new QPropertyAnimation( this, "maximumWidth", this );
    WidthAnim->setDuration( 200 );
    WidthAnim->setEasingCurve( QEasingCurve::InOutCubic );
    QObject::connect( WidthAnim, &QVariantAnimation::valueChanged, this,
                      [this]( const QVariant& v ) { setMinimumWidth( v.toInt() ); } );

    // Estado persistente entre sesiones.
    QSettings settings;
    const bool startExpanded = settings.value( "ui/sidebarExpanded", true ).toBool();
    setExpanded( startExpanded, /*animate=*/false );
}

QToolButton* CatedralSidebar::addItem( const QString& iconResource,
                                       const QString& label,
                                       QAction* action )
{
    auto* btn = new QToolButton( this );
    btn->setObjectName( "CatedralSidebarItem" );
    btn->setIcon( TintedIcon( iconResource, IconPx ) );
    btn->setIconSize( QSize( IconPx, IconPx ) );
    btn->setText( "  " + label );
    btn->setFixedHeight( ItemHeight );
    btn->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed );
    btn->setToolTip( label );
    btn->setToolButtonStyle( Expanded ? Qt::ToolButtonTextBesideIcon
                                      : Qt::ToolButtonIconOnly );
    btn->setCheckable( true );
    btn->setAutoRaise( true );
    btn->setCursor( Qt::PointingHandCursor );

    if ( action != nullptr ) {
        QObject::connect( btn, &QToolButton::clicked, action, &QAction::trigger );
    }

    Layout->addWidget( btn );
    Group->addButton( btn );
    Items.append( btn );
    return btn;
}

void CatedralSidebar::addStretch()
{
    Layout->addStretch( 1 );
}

void CatedralSidebar::applyButtonStyle()
{
    const auto style = Expanded ? Qt::ToolButtonTextBesideIcon
                                : Qt::ToolButtonIconOnly;
    for ( auto* b : Items ) {
        b->setToolButtonStyle( style );
    }
}

void CatedralSidebar::setExpanded( bool expanded, bool animate )
{
    Expanded = expanded;
    applyButtonStyle();

    // Flecha del toggle: apunta a donde ira la barra al pulsar.
    ToggleButton->setIcon( TintedIcon( expanded ? ":/icons/ChevronLeft"
                                                 : ":/icons/ChevronRight", IconPx ) );

    const int target = expanded ? ExpandedWidth : CollapsedWidth;

    if ( animate ) {
        WidthAnim->stop();
        WidthAnim->setStartValue( width() );
        WidthAnim->setEndValue( target );
        WidthAnim->start();
    } else {
        setMinimumWidth( target );
        setMaximumWidth( target );
    }

    QSettings settings;
    settings.setValue( "ui/sidebarExpanded", expanded );
}

void CatedralSidebar::toggle()
{
    setExpanded( !Expanded, /*animate=*/true );
}
