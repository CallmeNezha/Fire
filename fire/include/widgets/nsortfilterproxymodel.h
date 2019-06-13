#ifndef NSORTFILTERPROXYMODEL_H
#define NSORTFILTERPROXYMODEL_H
#include <QtWidgets>
#include <QSortFilterProxyModel>
#include <QRegExp>
#include <QVector>
#include <QMap>

using namespace std;
class NSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    NSortFilterProxyModel(QObject *parent = 0);
    // append : append new column with relative regexp vector
    void append(int column, QVector<QRegExp> reg_vec);
    // clear : clear reg_dic
    void clear();
    // set_switcher : change the filter type
    void set_switcher(bool flag);
    // get_switcher : return the value of switch
    bool get_switcher();

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

//  if need to sort override the function below
//    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    QMap<int, QVector<QRegExp>> reg_dic;
    // switcher is a switcher for start a complex filter type
    bool switcher = FALSE;

};
//! [0]


#endif // NSORTFILTERPROXYMODEL_H
