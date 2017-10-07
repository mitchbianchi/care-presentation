#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QMainWindow>
#include <QtNetwork>

namespace Ui {
class UserInterface;
}

class UserInterface : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserInterface(QWidget *parent = 0);
    ~UserInterface();

public slots:
    void updateData();
    void onResult(QNetworkReply* reply);
    //void replyFinished(QNetworkReply *reply);

private:
    Ui::UserInterface *ui;
};

#endif // USERINTERFACE_H
