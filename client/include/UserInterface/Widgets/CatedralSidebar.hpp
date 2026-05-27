#ifndef CATEDRAL_SIDEBAR_HPP
#define CATEDRAL_SIDEBAR_HPP

#include <QFrame>
#include <QToolButton>
#include <QVBoxLayout>
#include <QAction>
#include <QButtonGroup>

class CatedralSidebar : public QFrame {
    Q_OBJECT

public:
    explicit CatedralSidebar( QWidget* parent = nullptr );

    QToolButton* addItem( const QString& iconResource,
                          const QString& tooltip,
                          QAction* action );

    void addStretch();

private:
    QVBoxLayout*  Layout;
    QButtonGroup* Group;
};

#endif
