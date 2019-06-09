#ifndef NFINDBAR_H
#define NFINDBAR_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QActionGroup>
#include <QRegExp>


Q_DECLARE_METATYPE(QRegExp::PatternSyntax)

class NFindBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(Qt::CaseSensitivity caseSensitivity READ caseSensitivity WRITE setCaseSensitivity)
    Q_PROPERTY(QRegExp::PatternSyntax patternSyntax READ patternSyntax WRITE setPatternSyntax)

signals:
    void prevBtnClicked();
    void nextBtnClicked();
    void filterChanged();

public:
    enum SearchSpec
    {
        CaseSensitive = 1,
        WholeWordOnly = 2,
        UseRegularExp = 4
    };

    explicit NFindBar(QWidget *parent = nullptr);


    Qt::CaseSensitivity caseSensitivity() const;
    void setCaseSensitivity(Qt::CaseSensitivity cs);


    QRegExp::PatternSyntax patternSyntax() const;
    void setPatternSyntax(QRegExp::PatternSyntax s);
protected:

    QLineEdit   search_;
    QPushButton find_prev_;
    QPushButton find_next_;
    QPushButton close_;

    QAction      *case_sensitivity_action_;
    QActionGroup *pattern_group_;

};

#endif // NFINDBAR_H
