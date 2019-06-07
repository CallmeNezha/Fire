
#include <QApplication>
#include <QStandardItemModel>
#include <QFile>

#include "widgets/ntableview.h"

int main(int argc, char* argv[])
{
    Q_INIT_RESOURCE(grades);

    QApplication app( argc, argv );
    QStandardItemModel *model=new QStandardItemModel();

    QFile file(":/grades.txt");
    if (file.open(QFile::ReadOnly)) {
        QString line = file.readLine(200);
        QStringList list = line.simplified().split(',');
        model->setHorizontalHeaderLabels(list);

        int row = 0;
        QStandardItem *newItem = 0;
        while (file.canReadLine()) {
            line = file.readLine(200);
            if (!line.startsWith('#') && line.contains(',')) {
                list = line.simplified().split(',');
                for (int col = 0; col < list.length(); ++col){
                    newItem = new QStandardItem(list.at(col));
                    model->setItem(row, col, newItem);
                }
                ++row;
            }
        }
    }
    file.close();

    NTableView *tableView = new NTableView(model);

    tableView->setWindowTitle(QObject::tr("Frozen Column Example"));
    tableView->resize(560, 680);
    tableView->show();
    return app.exec();
}

