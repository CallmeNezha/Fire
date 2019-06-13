#include "widgets/ntableview.h"
#include <QMenu>
#include <QScrollBar>
#include <QHeaderView>

//! [constructor]
NTableView::NTableView(QAbstractItemModel * model, QWidget* parent)
    : QTableView (parent)
    , currentSection_(0)
{

    horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(horizontalHeader(), SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onHHeaderCtxMenuRequested(QPoint)));

    setModel(model);
    frozenTableView = new QTableView(this);


    init();

    //connect the headers and scrollbars of both tableviews together
    connect(horizontalHeader(),&QHeaderView::sectionResized, this,
            &NTableView::updateSectionWidth);
    connect(verticalHeader(),&QHeaderView::sectionResized, this,
            &NTableView::updateSectionHeight);

    connect(frozenTableView->verticalScrollBar(), &QAbstractSlider::valueChanged,
            verticalScrollBar(), &QAbstractSlider::setValue);
    connect(verticalScrollBar(), &QAbstractSlider::valueChanged,
            frozenTableView->verticalScrollBar(), &QAbstractSlider::setValue);

}
//! [constructor]

NTableView::~NTableView()
{
    delete frozenTableView;
}


void NTableView::freezeSection(int logicalIndex)
{
    frozenTableView->show();
    for (int column = 0; column < model()->columnCount(); ++column)
    {
        if (column == logicalIndex)
        {
            frozenTableView->setColumnHidden(column, false);

        }
        else
        {
            frozenTableView->setColumnHidden(column, true);
        }
    }
}

void NTableView::cancelFreeze()
{
    frozenTableView->setHidden(true);
}

void NTableView::onHHeaderCtxMenuRequested(QPoint pos)
{
    currentSection_ = horizontalHeader()->logicalIndexAt(pos);
    QPoint globalPos = horizontalHeader()->mapToGlobal(pos);
    QMenu* menu = new QMenu(this);

    QAction* freezeSection = menu->addAction("Freeze Section");
    connect(freezeSection, &QAction::triggered, this, [this]{
        this->freezeSection(currentSection_);
        frozenTableView->setColumnWidth(currentSection_, columnWidth(0));
        updateFrozenTableGeometry();
    });

    QAction* cancelFreeze  = menu->addAction("Cancel Freeze");
    connect(cancelFreeze, &QAction::triggered, this, [this]{this->cancelFreeze();});

    menu->addSeparator();

    QAction* hideSection   = menu->addAction("Hide Section");
    connect(hideSection, &QAction::triggered, this, [this]{setColumnHidden(currentSection_, true); });

    QAction* showSection   = menu->addAction("Show Sections");
    connect(showSection, &QAction::triggered, this, [this]{
        for (int column = 0; column < model()->columnCount(); ++column)
        {
            setColumnHidden(column, false);
        }
    });

    menu->addSeparator();

    QAction* filterSection = menu->addAction("Filter Append");
    connect(filterSection, &QAction::triggered, this, [this]{ emit get_head(currentSection_);});

    menu->exec(globalPos);
}



//! [init part1]
void NTableView::init()
{
    frozenTableView->setModel(model());
    frozenTableView->setFocusPolicy(Qt::NoFocus);
    frozenTableView->verticalHeader()->hide();
    frozenTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    viewport()->stackUnder(frozenTableView);
    //! [init part1]

    //! [init part2]
    frozenTableView->setStyleSheet("QTableView { border: none;"
                                   "background-color: #EEE;"
                                   "selection-background-color: #999}"); //for demo purposes
    frozenTableView->setSelectionModel(selectionModel());

    frozenTableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    frozenTableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    frozenTableView->hide();

    updateFrozenTableGeometry();

    setHorizontalScrollMode(ScrollPerPixel);
    setVerticalScrollMode(ScrollPerPixel);
    frozenTableView->setVerticalScrollMode(ScrollPerPixel);
}

//! [init part2]


//! [sections]
void NTableView::updateSectionWidth(int logicalIndex, int /* oldSize */, int newSize)
{
    frozenTableView->setColumnWidth(currentSection_, columnWidth(0));
    updateFrozenTableGeometry();
}

void NTableView::updateSectionHeight(int logicalIndex, int /* oldSize */, int newSize)
{
    frozenTableView->setRowHeight(logicalIndex, newSize);
}
//! [sections]


//! [resize]
void NTableView::resizeEvent(QResizeEvent * event)
{
    QTableView::resizeEvent(event);
    updateFrozenTableGeometry();
}
//! [resize]


//! [navigate]
QModelIndex NTableView::moveCursor(CursorAction cursorAction,
                                          Qt::KeyboardModifiers modifiers)
{
    QModelIndex current = QTableView::moveCursor(cursorAction, modifiers);

    if (cursorAction == MoveLeft && current.column() > 0
            && visualRect(current).topLeft().x() < frozenTableView->columnWidth(0) ){
        const int newValue = horizontalScrollBar()->value() + visualRect(current).topLeft().x()
                - frozenTableView->columnWidth(0);
        horizontalScrollBar()->setValue(newValue);
    }
    return current;
}
//! [navigate]

void NTableView::scrollTo (const QModelIndex & index, ScrollHint hint){
    if (index.column() > 0)
        QTableView::scrollTo(index, hint);
}

//! [geometry]
void NTableView::updateFrozenTableGeometry()
{
    frozenTableView->setGeometry(verticalHeader()->width() + frameWidth(),
                                 frameWidth(), columnWidth(0),
                                 viewport()->height()+horizontalHeader()->height());
}
//! [geometry]


