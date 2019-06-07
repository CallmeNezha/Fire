#include "widgets/ncolbar.h"
#include <QFormLayout>
#include <QPushButton>



NColBar::NColBar(QList<BtnInfo> btnsinfo, QWidget *parent)
    : QWidget(parent)
{
    QFormLayout* layout = new QFormLayout(this);
    layout->setSpacing(0);
    layout->setVerticalSpacing(0);
    layout->setContentsMargins(0,0,0,0);

    auto createBtn = [this](const QIcon& icon){
        QPushButton* btn = new QPushButton(icon,"",this);
        btn->setFlat(true);
        btn->setIconSize(QSize(40,40));
        btn->setFixedHeight(60);
        btn->setCheckable(true);
        return btn;
    };

    for (int i = 0; i < btnsinfo.size(); ++i)
    {
        const BtnInfo& info = btnsinfo[i];
        QPushButton* btn = createBtn(info.icon);
        btn->setText(info.name);
        btn->setToolTip(info.tooltip);
        layout->addRow(btn);
        btn_group_.addButton(btn, i);
    }

    connect(&btn_group_, SIGNAL(buttonClicked(int)), this, SIGNAL(clicked(int)));
}


void NColBar::Click(int index)
{
    QAbstractButton* button = btn_group_.button(index);
    if (!button)
    {
        return;
    }
    button->click();
}
