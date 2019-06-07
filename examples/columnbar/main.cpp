#include <QApplication>
#include <QDebug>
#include <QObject>
#include "widgets/ncolbar.h"
#include "responser.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    auto responser = new Responser();

    auto colbar = new NColBar({
                {"Button 1", "Button 1 ToolTip", QIcon()},
                {"Button 2", "Button 2 ToolTip", QIcon()},
                {"Button 3", "Button 3 ToolTip", QIcon()},
                {"Button 4", "Button 4 ToolTip", QIcon()}
            });

    QObject::connect(colbar, SIGNAL(clicked(int)), responser, SLOT(onColBarClicked(int)));
    colbar->show();
    return app.exec();
}

