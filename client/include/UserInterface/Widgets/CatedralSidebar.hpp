#ifndef CATEDRAL_SIDEBAR_HPP
#define CATEDRAL_SIDEBAR_HPP

#include <QFrame>
#include <QToolButton>
#include <QVBoxLayout>
#include <QAction>
#include <QButtonGroup>
#include <QList>

class QPropertyAnimation;

class CatedralSidebar : public QFrame {
    Q_OBJECT

public:
    explicit CatedralSidebar( QWidget* parent = nullptr );

    QToolButton* addItem( const QString& iconResource,
                          const QString& label,
                          QAction* action );

    void addStretch();

public slots:
    void toggle();
    void setExpanded( bool expanded, bool animate = true );

private:
    void applyButtonStyle();

    QVBoxLayout*        Layout;
    QButtonGroup*       Group;
    QToolButton*        ToggleButton;
    QList<QToolButton*> Items;
    QPropertyAnimation* WidthAnim;
    bool                Expanded;

    static constexpr int CollapsedWidth = 48;
    static constexpr int ExpandedWidth  = 190;
    static constexpr int IconPx         = 20;
    static constexpr int ItemHeight     = 38;
};

#endif
