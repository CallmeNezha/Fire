#ifndef NFILTERBAR_H
#define NFILTERBAR_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QActionGroup>
#include <QRegExp>


//Q_DECLARE_METATYPE(QRegExp::PatternSyntax)

class NFilterBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(Qt::CaseSensitivity caseSensitivity READ caseSensitivity WRITE setCaseSensitivity)
    Q_PROPERTY(QRegExp::PatternSyntax patternSyntax READ patternSyntax WRITE setPatternSyntax)

signals:
    void filterBtnClicked();
    void filterChanged();

public:
    enum SearchSpec
    {
        CaseSensitive = 1,
        WholeWordOnly = 2,
        UseRegularExp = 4
    };

    explicit NFilterBar(QWidget *parent = nullptr);


    Qt::CaseSensitivity caseSensitivity() const;
    void setCaseSensitivity(Qt::CaseSensitivity cs);


    QRegExp::PatternSyntax patternSyntax() const;
    void setPatternSyntax(QRegExp::PatternSyntax s);

    QString get_filter_editor_text() const { return filter_editor.text();}
    void append_column_name_to_filter_text(QString head);

    QLineEdit const &get_filter_editor();

private:

    QLineEdit   filter_editor;
    QPushButton filter_button;
    QPushButton close_button;

    QAction      *case_sensitivity_action_;
    QActionGroup *pattern_group_;

};
#endif // NFILTERBAR_H
