#include <widgets/nfilterbar.h>
#include <widgets/nfindbar.h>
#include <widgets/nsortfilterproxymodel.h>
#include <widgets/ntableview.h>
#include <widgets/window.h>
#include <QtWidgets>
#include <QVector>
#include <QMainWindow>

QStandardItemModel* parseCSV()
{
    QStandardItemModel* csvModel = new QStandardItemModel();
    QFile file("D:/Huang/msg_name_table.csv");

    if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
        qDebug() << "File not exists";
    } else {
        // Create a thread to retrieve data from a file
        QString line = file.readLine();
        QStringList list = line.simplified().split(',');
        csvModel->setHorizontalHeaderLabels(list);
        QTextStream in(&file);
        //Reads the data up to the end of file
        while (!in.atEnd())
        {
            QString line = in.readLine();
            // Adding to the model in line with the elements
            QList<QStandardItem *> standardItemsList;
            // Consider that the line separated by semicolons into columns
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
    /* Create main window */
    qmainWindow = new QMainWindow();
    qmainWindow->setCentralWidget(new QWidget());
    qmainWindow->resize(860, 640);

    /* Load source model, load proxy model with source model.Then set the proxy model as source model in tableview */
    sourceModel = new QStandardItemModel();
    sourceModel = parseCSV();
    nsortfilterproxyModel = new NSortFilterProxyModel();
    nsortfilterproxyModel->setSourceModel(sourceModel);
    ntableView = new NTableView(nsortfilterproxyModel);

    init_header_list(nsortfilterproxyModel);
    /* Add widgets and set specific attributes */
    qvboxLayout = new QVBoxLayout();
    qmainWindow->centralWidget()->setLayout(qvboxLayout);
    qvboxLayout->addWidget(ntableView);
    nfilterBar = new NFilterBar(ntableView);
    qvboxLayout->addWidget(nfilterBar);
    nfilterBar->hide();
    nfindBar = new NFindBar(ntableView);
    qvboxLayout->addWidget(nfindBar);
    nfindBar->hide();

    /* Add connections */
    QObject::connect(nfilterBar, SIGNAL(filterBtnClicked()), this, SLOT(filter()));
    QObject::connect(nfindBar, SIGNAL(prevBtnClicked()), this, SLOT(prev()));
    QObject::connect(nfindBar, SIGNAL(nextBtnClicked()), this, SLOT(next()));

    /* Add column name to filter action */
    QAction* append_column_filter = new QAction("Filter Column");
    ntableView->addCustomAction(append_column_filter);
    QObject::connect(append_column_filter, &QAction::triggered, this, &Window::appendColumnNameToFilter);
    QObject::connect(nfilterBar, SIGNAL(returnPressed()), nfilterBar, SIGNAL(filterBtnClicked()), Qt::UniqueConnection);

    /* Bind action with slots and connect */
    QAction* find_action = new QAction("Find", ntableView);
    find_action->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
    QObject::connect(find_action, SIGNAL(triggered()), nfindBar, SLOT(show_hide()));
    ntableView->addAction(find_action);

    QAction* filter_action = new QAction("Filter", ntableView);
    filter_action->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));
    QObject::connect(filter_action, SIGNAL(triggered()), nfilterBar, SLOT(show_hide()));
    ntableView->addAction(filter_action);

    /* Show main window */
    qmainWindow->show();
}

// Receive head index from ntableview, parse it into the specific column name and append
void Window::appendColumnNameToFilter()
{
    QString current_text = nfilterBar->text();

    const QString head = ntableView->model()->headerData(ntableView->selectedSection(), Qt::Horizontal).toString();
    if (current_text.trimmed().isEmpty())
    {
        current_text.clear();
        current_text.append("\"" + head + "\" = {\"\"}");
    }
    else
    {
        current_text = current_text.trimmed();
        current_text.append(" | \"" + head + "\" = {\"\"}");
    }
    nfilterBar->setText(current_text);
}

/* Filter function can filter specific rows the user want with fixed string or regexps */
void Window::filter()
{
    QRegExp rx("\\s*\"[^,\"]*\"\\s*=\\s*\\{\\s*\(\"[^,\"]*\"\)\\s*\(,\\s*\"[^,\"]*\"\\s*\)*\\s*\\}\\s*\(\\|\(\\s*\"[^,\"]*\"\\s*=\\s*\\{\\s*\(\"[^,\"]*\"\)\\s*\(,\\s*\"[^,\"]*\"\\s*\)*\\s*\\}\\s*\)\)*");
    QRegExpValidator validator(rx);
    int pos = 0;
    QString text = nfilterBar->text();
    // If a valid text which can pass the regexp validator is inputted, set the switcher TRUE and start complex filter mode, else go to global filter.
    if(validator.validate(text, pos) == 2)
    {
        nsortfilterproxyModel->set_switcher(TRUE);
        nsortfilterproxyModel->clear();
        QStringList list = nfilterBar->text().split("|");
        for(QString per_string:list)
        {
            // "head" : column name
            QString head = per_string.split("=")[0].split("\"")[1];
            // "value" : store different regexp for the same "head"
            QVector<QRegExp> value;
            QString temp;
            for(QString temp:per_string.split("=")[1].split(","))
            {
                value.append(QRegExp(temp.split("\"")[1], nfilterBar->caseSensitivity(), nfilterBar->patternSyntax()));
            }

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
    }
    // Not using complex filter function
    else
    {
        global_filter();
    }
}

/* Filter key words globally */
void Window::global_filter()
{
    nsortfilterproxyModel->set_switcher(FALSE);
    QRegExp regExp(nfilterBar->text(),
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

void Window::init_header_list(NSortFilterProxyModel *model)
{
    for(int i = 0; i < model->columnCount(); i++)
    {
      header_list.append(model->headerData(i, Qt::Horizontal).toString());
    }
}


