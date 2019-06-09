
#include <QApplication>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QFile>
#include <QAction>
#include <QVBoxLayout>
#include <QShortcut>

#include "widgets/ntableview.h"
#include "widgets/nfindbar.h"

int main(int argc, char* argv[])
{
    Q_INIT_RESOURCE(grades);

    QApplication app( argc, argv );
    QMainWindow* mainwin = new QMainWindow();

    mainwin->setCentralWidget(new QWidget());
    QVBoxLayout* layout = new QVBoxLayout();
    mainwin->centralWidget()->setLayout(layout);


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
    layout->addWidget(tableView);

    NFindBar* findbar = new NFindBar(tableView);

    QStringList header_list;
    {
        for (int i=1; i < model->columnCount(); ++i)
        {
            header_list.append(model->horizontalHeaderItem(i)->text());
        }
    }
    findbar->hide();
    layout->addWidget(findbar);

    QAction* find_action = new QAction("Find", tableView);
    find_action->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
    QObject::connect(find_action, SIGNAL(triggered()), findbar, SLOT(show()));
    tableView->addAction(find_action);

    mainwin->show();
    return app.exec();
}

