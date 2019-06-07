#include <QApplication>
#include <QDebug>
#include <QObject>
#include <QVBoxLayout>
#include "widgets/nstatusbar.h"

#include <QMainWindow>
#include <QStatusBar>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QMainWindow mainwin;
    mainwin.setCentralWidget(new QWidget(&mainwin));

    auto layout = new QVBoxLayout(mainwin.centralWidget());
    mainwin.centralWidget()->setLayout(layout);

    layout->addStretch(1);
    layout->setMargin(0);
    NStatusBar stsbar;
    layout->addWidget(&stsbar);

    stsbar.ShowMessage("Hello World", 5000);

    mainwin.statusBar()->showMessage("Status Bar: Hello World", 5000);
    mainwin.show();
    return app.exec();
}

