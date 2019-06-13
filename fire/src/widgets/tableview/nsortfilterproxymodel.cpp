#include "widgets/nsortfilterproxymodel.h"

//! [0]
NSortFilterProxyModel::NSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

// Insert a new instance into the reg_dic
void NSortFilterProxyModel::append(int column, QVector<QRegExp> reg_vec)
{
    reg_dic.insert(column, reg_vec);
}

// Clear the reg_dic
void NSortFilterProxyModel::clear()
{
    reg_dic.clear();
}

// Set the switcher to a specific mode
void NSortFilterProxyModel::set_switcher(bool flag)
{
    switcher = flag;
}

// Get current switcher
bool NSortFilterProxyModel::get_switcher()
{
    return switcher;
}
//! [0]

//! [1]
//!
bool NSortFilterProxyModel::filterAcceptsRow(int sourceRow,
        const QModelIndex &sourceParent) const
{
    bool ret = FALSE;
    // swticher TRUE : go to complex filter mode
    if(switcher)
    {
        // In complex filter mode, ret is initialed TRUE because we will use "&="
        ret = TRUE;
        // Logic process : We use "|=" for the same column and "&=" for different columns
        for(QMap<int, QVector<QRegExp>>::const_iterator map_itr = reg_dic.begin(); map_itr != reg_dic.end(); ++map_itr)
        {
            bool temp_ret = FALSE;
            int col = map_itr.key();
            for(QVector<QRegExp>::const_iterator reg_itr = map_itr.value().begin(); reg_itr != map_itr.value().end(); ++reg_itr)
            {
                QModelIndex temp_index = sourceModel()->index(sourceRow, col, sourceParent);
                temp_ret |= sourceModel()->data(temp_index).toString().contains(*reg_itr);
            }
            ret &= temp_ret;
        }
        return ret;
    }
    // switcher FALSE : go to global filter mode
    else
    {
        // Logic procee : We use "|=" to match each element in tableview
        int col_count = sourceModel()->columnCount();
        for(int i = 0; i < col_count; ++i)
        {
            QModelIndex temp_index = sourceModel()->index(sourceRow, i, sourceParent);
            ret |= sourceModel()->data(temp_index).toString().contains(filterRegExp());
        }
        return ret;
    }
}
//! [1]

//! [2] //! [3]
//bool NSortFilterProxyModel::lessThan(const QModelIndex &left,
//                                      const QModelIndex &right) const
//{
//    QVariant leftData = sourceModel()->data(left);
//    QVariant rightData = sourceModel()->data(right);
////! [2]

////! [4]
//    if (leftData.type() == QVariant::DateTime) {
//        return leftData.toDateTime() < rightData.toDateTime();
//    } else {
//        static QRegExp emailPattern("[\\w\\.]*@[\\w\\.]*)");

//        QString leftString = leftData.toString();
//        if(left.column() == 1 && emailPattern.indexIn(leftString) != -1)
//            leftString = emailPattern.cap(1);

//        QString rightString = rightData.toString();
//        if(right.column() == 1 && emailPattern.indexIn(rightString) != -1)
//            rightString = emailPattern.cap(1);

//        return QString::localeAwareCompare(leftString, rightString) < 0;
//    }
//}
//! [3] //! [4]

