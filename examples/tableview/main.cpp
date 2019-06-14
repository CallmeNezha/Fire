#include "widgets/window.h"
#include "widgets/ntableview.h"
#include "widgets/nfindbar.h"
#include "widgets/nfilterbar.h"
#include "widgets/nsortfilterproxymodel.h"

int main(int argc, char* argv[])
{
    Q_INIT_RESOURCE(grades);
    QApplication app( argc, argv );
    Window window;
    return app.exec();
}

