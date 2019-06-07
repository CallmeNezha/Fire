#ifndef RESPONSER_H
#define RESPONSER_H

#include <QObject>

class Responser : public QObject
{
    Q_OBJECT
public:
    explicit Responser(QObject *parent = nullptr);

signals:

public slots:
    void onColBarClicked(int index);
};

#endif // RESPONSER_H
