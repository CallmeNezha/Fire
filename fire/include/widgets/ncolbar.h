#ifndef NCOLBAR_H
#define NCOLBAR_H

#include <QWidget>
#include <QButtonGroup>
#include <QIcon>

/**
 * @brief The NColBar class
 */
class NColBar : public QWidget
{
    Q_OBJECT
signals:
    /**
     * @brief clicked signal emitted when button is clicked
     * @param index     - index of button
     */
    void clicked(int index);

public slots:
    /**
     * @brief Click button by index
     * @param index     -
     */
    void Click(int index);

public:

    /**
     * @brief The BtnInfo struct
     * @param name      - button name
     * @param tooltip   - button tooltip
     * @param icon      - button icon
     */
    struct BtnInfo
    {
        QString name;
        QString tooltip;
        QIcon   icon;
    };

    explicit NColBar(QList<BtnInfo> btnsinfo, QWidget *parent = nullptr);

private:
    QButtonGroup btn_group_;
};

#endif // NCOLBAR_H
