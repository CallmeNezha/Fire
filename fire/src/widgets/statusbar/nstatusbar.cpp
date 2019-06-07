#include "widgets/nstatusbar.h"
#include <QHBoxLayout>
#include <QTimer>
#include <QIcon>

NStatusBar::NStatusBar(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(&icon_, 0);
    layout->addWidget(&label_, 1);
    layout->addStretch();
    layout->addWidget(&pbar_);

    layout->setMargin(6);
}


void NStatusBar::ShowMessage(const QString& msg, int timeout)
{
    label_.setText(msg);
    if (timeout > 0)
    {
        QTimer::singleShot(timeout, this, [this]{ this->label_.setText(""); });
    }
}

void NStatusBar::SetIcon(const QIcon& icon, int timeout)
{
    QPixmap pixmap = icon.pixmap(QSize(30, 30));
    icon_.setPixmap(pixmap);
    if (timeout > 0)
    {
        QTimer::singleShot(timeout, this, [this]{ this->icon_.setPixmap(QPixmap()); });
    }
}


