#include "widgets/nfindbar.h"
#include <QGridLayout>
#include <QLabel>
#include <QAction>
#include <QMenu>
#include <QToolButton>
#include <QSizePolicy>
#include <QWidgetAction>

NFindBar::NFindBar(QWidget *parent)
    : QWidget(parent)
    , pattern_group_(new QActionGroup(this))
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(3);
    setLayout(layout);

    layout->addWidget(new QLabel("Find:  "));
    layout->addWidget(&find_editor, 1);
    find_editor.setClearButtonEnabled(true);

    // FIND PREVIOUS
    layout->addWidget(&find_prev_item);
    find_prev_item.setText("Find Previous");
    connect(&find_prev_item, SIGNAL(clicked()), this, SIGNAL(prevBtnClicked()));

    // FIND NEXT
    layout->addWidget(&find_next_item);
    find_next_item.setText("Find Next");
    connect(&find_next_item, SIGNAL(clicked()), this, SIGNAL(nextBtnClicked()));

    // CLOSE BUTTON
    layout->addWidget(&close_button);
    close_button.setMaximumWidth(25);
    close_button.setFocusPolicy(Qt::NoFocus);
    close_button.setStyleSheet("* { border: none; }");
    close_button.setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    connect(&close_button, &QPushButton::clicked, this, &QWidget::hide);

    QMenu *menu = new QMenu(this);
    case_sensitivity_action_ = menu->addAction(tr("Case Sensitive"));
    case_sensitivity_action_->setCheckable(true);
    connect(case_sensitivity_action_, &QAction::toggled, this, &NFindBar::filterChanged);

    menu->addSeparator();
    pattern_group_->setExclusive(true);
    QAction *patternAction = menu->addAction("Fixed String");
    patternAction->setData(QVariant(int(QRegExp::FixedString)));
    patternAction->setCheckable(true);
    patternAction->setChecked(true);
    pattern_group_->addAction(patternAction);
    patternAction = menu->addAction("Regular Expression");
    patternAction->setCheckable(true);
    patternAction->setData(QVariant(int(QRegExp::RegExp2)));
    pattern_group_->addAction(patternAction);
    connect(pattern_group_, &QActionGroup::triggered, this, &NFindBar::filterChanged);


    QToolButton *optionsButton = new QToolButton;

    optionsButton->setCursor(Qt::ArrowCursor);
    optionsButton->setFocusPolicy(Qt::NoFocus);
    optionsButton->setStyleSheet("* { border: none; }");
//    optionsButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    optionsButton->setMenu(menu);
    optionsButton->setPopupMode(QToolButton::InstantPopup);

    QWidgetAction *optionsAction = new QWidgetAction(&find_editor);
    optionsAction->setDefaultWidget(optionsButton);
    find_editor.addAction(optionsAction, QLineEdit::LeadingPosition);
}

void NFindBar::show_hide()
{
    if(isHidden())
    {
        show();
    }
    else
    {
        hide();
    }
}

Qt::CaseSensitivity NFindBar::caseSensitivity() const
{
    return case_sensitivity_action_->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
}

void NFindBar::setCaseSensitivity(Qt::CaseSensitivity cs)
{
    case_sensitivity_action_->setChecked(cs == Qt::CaseSensitive);
}

static inline QRegExp::PatternSyntax patternSyntaxFromAction(const QAction *a)
{
    return static_cast<QRegExp::PatternSyntax>(a->data().toInt());
}

QRegExp::PatternSyntax NFindBar::patternSyntax() const
{
    return patternSyntaxFromAction(pattern_group_->checkedAction());
}

void NFindBar::setPatternSyntax(QRegExp::PatternSyntax s)
{
    foreach (QAction *a, pattern_group_->actions()) {
        if (patternSyntaxFromAction(a) == s) {
            a->setChecked(true);
            break;
        }
    }
}



