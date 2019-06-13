#include <widgets/nfilterbar.h>
#include <widgets/nfindbar.h>
#include <widgets/nsortfilterproxymodel.h>
#include <widgets/ntableview.h>
#include <widgets/window.h>
#include <QtWidgets>
#include <QVector>
#include <QMainWindow>

// the parameter is used to set header_list
QStandardItemModel* parseCSV(QStringList &header_list)
{
    QStandardItemModel* csvModel = new QStandardItemModel();
    QFile file(":/msg_name_table.csv");

    if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
        qDebug() << "File not exists";
    } else {
        // Create a thread to retrieve data from a file
        QString line = file.readLine();
        QStringList list = line.simplified().split(',');
        csvModel->setHorizontalHeaderLabels(list);
        header_list = list;
        QTextStream in(&file);
        //Reads the data up to the end of file
        while (!in.atEnd())
        {
            QString line = in.readLine();
            // Adding to the model in line with the elements
            QList<QStandardItem *> standardItemsList;
            // consider that the line separated by semicolons into columns
            for (QString item : line.split(",")) {
                standardItemsList.append(new QStandardItem(item));
            }
            csvModel->insertRow(csvModel->rowCount(), standardItemsList);
        }
        file.close();
    }
    return csvModel;
}

Window::Window()
{
    // Create main window
    qmainWindow = new QMainWindow();
    qmainWindow->setCentralWidget(new QWidget());
    qmainWindow->resize(860, 640);

    // Load source model, load proxy model with source model.Then set the proxy model as source model in tableview
    sourceModel = new QStandardItemModel();
    sourceModel = parseCSV(header_list);
    nsortfilterproxyModel = new NSortFilterProxyModel();
    nsortfilterproxyModel->setSourceModel(sourceModel);
    ntableView = new NTableView(nsortfilterproxyModel);

    // Add widgets and set specific attributes
    qvboxLayout = new QVBoxLayout();
    qmainWindow->centralWidget()->setLayout(qvboxLayout);
    qvboxLayout->addWidget(ntableView);
    nfilterBar = new NFilterBar(ntableView);
    qvboxLayout->addWidget(nfilterBar);
    nfilterBar->hide();
    nfindBar = new NFindBar(ntableView);
    qvboxLayout->addWidget(nfindBar);
    nfindBar->hide();

    // Add connections
    QObject::connect(nfilterBar, SIGNAL(filterBtnClicked()), this, SLOT(filter()));
    QObject::connect(nfindBar, SIGNAL(prevBtnClicked()), this, SLOT(prev()));
    QObject::connect(nfindBar, SIGNAL(nextBtnClicked()), this, SLOT(next()));
    QObject::connect(ntableView, SIGNAL(get_head(int)), this, SLOT(rec_head(int)));

    QObject::connect(&nfilterBar->get_filter_editor(), SIGNAL(returnPressed()), nfilterBar, SIGNAL(filterBtnClicked()), Qt::UniqueConnection);
    // Bind action with slots and connect
    QAction* find_action = new QAction("Find", ntableView);
    find_action->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
    QObject::connect(find_action, SIGNAL(triggered()), nfindBar, SLOT(show()));
    ntableView->addAction(find_action);

    QAction* filter_action = new QAction("Filter", ntableView);
    filter_action->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));
    QObject::connect(filter_action, SIGNAL(triggered()), nfilterBar, SLOT(show()));
    ntableView->addAction(filter_action);

    // Show main window
    qmainWindow->show();
}

// Receive head index from ntableview, parse it into the specific column name and append
void Window::rec_head(int head_index)
{
    nfilterBar->append_column_name_to_filter_text(header_list[head_index]);
}

// Filter function can filter specific rows the user want with fixed string or regexps
void Window::filter()
{
    QRegExp rx2("\\s*\"[^,\"]*\"\\s*=\\s*\\{\\s*\(\"[^,\"]*\"\)\\s*\(,\\s*\"[^,\"]*\"\\s*\)*\\s*\\}\\s*\(\\|\(\\s*\"[^,\"]*\"\\s*=\\s*\\{\\s*\(\"[^,\"]*\"\)\\s*\(,\\s*\"[^,\"]*\"\\s*\)*\\s*\\}\\s*\)\)*");
    QRegExpValidator v2(rx2);
    int pos = 0;
    QString text = nfilterBar->get_filter_editor_text();
//    qDebug() <<v2.validate(text, pos);
    // If a valid text which can pass the regexp validator is inputted, set the switcher TRUE and start complex filter mode
    //     else go to global filter
    if(v2.validate(text, pos) == 2 && (nfilterBar->patternSyntax() == 2 || nfilterBar->patternSyntax() == 3))
    {
        nsortfilterproxyModel->set_switcher(TRUE);
        nsortfilterproxyModel->clear();
        QStringList list = nfilterBar->get_filter_editor_text().split("|");
        for(QString per_string:list)
        {
            if(!v2.validate(per_string, pos))
            {
                global_filter();
                break;
            }
            else
            {
                // When parsing the text, it's necessary to checked if format is valid again to avoid index out of range
                if(per_string.split("=")[0].split("\"").size() == 3)
                {
                    QString head = per_string.split("=")[0].split("\"")[1];
                    QVector<QRegExp> value;
                    QString temp;
                    for(QString temp:per_string.split("=")[1].split(","))
                    {
                        // If format is valid, append regexp
                        if(temp.split("\"").size() == 3)
                        {
                            value.append(QRegExp(temp.split("\"")[1], nfilterBar->caseSensitivity(), nfilterBar->patternSyntax()));
                        }
                        else
                        {
                            nsortfilterproxyModel->set_switcher(FALSE);
                            break;
                        }
                    }
                    // If format is valid, start filtering
                    if(nsortfilterproxyModel->get_switcher())
                    {
                        int key = header_list.indexOf(head);
                        // By default, when parameter "key" == -1, which means the column to be searched is -1, then the column limit will be invalid.
                        if(key != -1)
                        {
                            nsortfilterproxyModel->append(key, value);
                            nsortfilterproxyModel->setFilterRegExp(QRegExp());
                        }
                        // Can't find specific head in header_list
                        else
                        {
                            global_filter();
                            break;
                        }
                    }
                    // format error
                    else
                    {
                        global_filter();
                        break;
                    }
                }
                // format error
                else
                {
                    global_filter();
                    break;
                }
            }
        }
    }
    // Not using complex filter function
    else
    {
        global_filter();
    }

//    match
//    QModelIndexList nidx = nsortfilterproxyModel->match(
//                nsortfilterproxyModel->index(0,2)
//                , Qt::DisplayRole
//                , "5", -1, Qt::MatchContains);

}

// Filter key words globally
void Window::global_filter()
{
    nsortfilterproxyModel->set_switcher(FALSE);
    QRegExp regExp(nfilterBar->get_filter_editor_text(),
                   nfilterBar->caseSensitivity(),
                   nfilterBar->patternSyntax());
    nsortfilterproxyModel->setFilterRegExp(regExp);
}

void Window::prev()
{
    // to be completed
    return;
}

void Window::next()
{
    // to be completed
    return;
}


