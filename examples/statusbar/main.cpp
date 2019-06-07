#include <QApplication>
#include <QDebug>
#include <QObject>
#include <QVBoxLayout>
#include "widgets/nstatusbar.h"

#include <QMainWindow>
#include <QStatusBar>
#include <QStyle>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QMainWindow mainwin;
    mainwin.setCentralWidget(new QWidget(&mainwin));

    auto layout = new QVBoxLayout(mainwin.centralWidget());
    mainwin.centralWidget()->setLayout(layout);

    layout->addStretch(1);
    NStatusBar stsbar;
    layout->addWidget(&stsbar);

    stsbar.SetIcon(mainwin.style()->standardIcon(QStyle::SP_MessageBoxWarning), 5000);
    stsbar.ShowMessage("Hello World", 5000);
    stsbar.SetPrecent(50);

    mainwin.statusBar()->showMessage("Status Bar: Hello World", 5000);

    mainwin.setWindowTitle("Status Bar Example");
    mainwin.resize(500, 500);
    mainwin.show();
    return app.exec();
}

