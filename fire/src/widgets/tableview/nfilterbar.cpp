#include "widgets/nfilterbar.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QToolButton>
#include <QWidgetAction>

NFilterBar::NFilterBar(QWidget *parent)
    : QWidget(parent)
    , pattern_group_(new QActionGroup(this))
{
    // Set layout
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(3);
    setLayout(layout);

    layout->addWidget(new QLabel("Filter:"));
    layout->addWidget(&filter_editor, 1);
    filter_editor.setClearButtonEnabled(true);

    // Add filter button
    layout->addWidget(&filter_button);
    filter_button.setText("Start Filtering");
    connect(&filter_button, SIGNAL(clicked()), this, SIGNAL(filterBtnClicked()));

    // Add close Button
    layout->addWidget(&close_button);
    close_button.setMaximumWidth(25);
    close_button.setFocusPolicy(Qt::NoFocus);
    close_button.setStyleSheet("* { border: none; }");
    close_button.setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    connect(&close_button, &QPushButton::clicked, this, &QWidget::hide);

    // Add menu
    QMenu *menu = new QMenu(this);
    case_sensitivity_action_ = menu->addAction(tr("Case Sensitive"));
    case_sensitivity_action_->setCheckable(true);
    connect(case_sensitivity_action_, &QAction::toggled, this, &NFilterBar::filterChanged);

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
    connect(pattern_group_, &QActionGroup::triggered, this, &NFilterBar::filterChanged);

    // Add menu button
    QToolButton *optionsButton = new QToolButton;

    optionsButton->setCursor(Qt::ArrowCursor);
    optionsButton->setFocusPolicy(Qt::NoFocus);
    optionsButton->setStyleSheet("* { border: none; }");
    optionsButton->setMenu(menu);
    optionsButton->setPopupMode(QToolButton::InstantPopup);

    QWidgetAction *optionsAction = new QWidgetAction(&filter_editor);
    optionsAction->setDefaultWidget(optionsButton);
    filter_editor.addAction(optionsAction, QLineEdit::LeadingPosition);
}

// append formatted column name to the search text
void NFilterBar::append_column_name_to_filter_text(QString head)
{
    if(isHidden())
    {
        show();
    }
    QString current_text = filter_editor.text();
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
    filter_editor.setText(current_text);
}

//
void NFilterBar::show_hide()
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

QLineEdit const & NFilterBar::get_filter_editor()
{
    return filter_editor;
}

Qt::CaseSensitivity NFilterBar::caseSensitivity() const
{
    return case_sensitivity_action_->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
}

void NFilterBar::setCaseSensitivity(Qt::CaseSensitivity cs)
{
    case_sensitivity_action_->setChecked(cs == Qt::CaseSensitive);
}

static inline QRegExp::PatternSyntax patternSyntaxFromAction(const QAction *a)
{
    return static_cast<QRegExp::PatternSyntax>(a->data().toInt());
}

QRegExp::PatternSyntax NFilterBar::patternSyntax() const
{
    return patternSyntaxFromAction(pattern_group_->checkedAction());
}

void NFilterBar::setPatternSyntax(QRegExp::PatternSyntax s)
{
    foreach (QAction *a, pattern_group_->actions()) {
        if (patternSyntaxFromAction(a) == s) {
            a->setChecked(true);
            break;
        }
    }
}

