#ifndef CATEDRAL_EVENTVIEWER_HPP
#define CATEDRAL_EVENTVIEWER_HPP

#include <global.hpp>

class CatedralNamespace::UserInterface::SmallWidgets::EventViewer : public QWidget {
    QGridLayout *gridLayout;
public:
    QTextEdit *EventViewerConsole;
    QWidget* EventViewer;

    void setupUi(QWidget* Widget);
    void AppendText(const QString& Time, const QString &text) const;
};

#endif
