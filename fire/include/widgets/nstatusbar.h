#ifndef NSTATUSBAR_H
#define NSTATUSBAR_H

#include <QWidget>
#include <QLabel>
#include <QProgressBar>

/**
 * @brief The NStatusBar class
 */
class NStatusBar : public QWidget
{
    Q_OBJECT
public slots:

    /**
     * @brief ShowMessage
     * @param msg       - message
     * @param timeout   - clear message after timeout ms
     */
    void ShowMessage(const QString& msg, int timeout);

    /**
     * @brief SetIcon
     * @param icon      - icon
     * @param timeout   - clear icon after timeout ms
     */
    void SetIcon(const QIcon& icon, int timeout);
public:
    explicit NStatusBar(QWidget* parent = Q_NULLPTR);

private:
    QLabel       icon_;
    QLabel       label_;
    QProgressBar pbar_;
};

#endif // NSTATUSBAR_H
