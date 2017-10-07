#include "userinterface.h"
#include "ui_userinterface.h"
#include "QLabel"
#include "qframe.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <QTimer>
#include <QtNetwork>
#include <QScriptEngine>
#include <QScriptValue>
#include <QScriptValueIterator>

QLabel *text;
int retrialNum = 0;
using namespace std;

UserInterface::UserInterface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserInterface)
{
    text = new QLabel(this);
    updateData();
    ui->setupUi(this);

    // Timed function recalled each 10000ms
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateData()));
    timer->start(10000);
}

void UserInterface::updateData(){

    //Request DATA to API
    QNetworkAccessManager networkManager;
    QUrl url("https://www.bitstamp.net/api/v2/ticker/btceur/");
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    networkManager.get(request);

    connect(&networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onResult(QNetworkReply*)));

    if(retrialNum > 0)
    {
        std::string name = "Retry #";
        char numstr[21];
        QString result = QString::fromStdString(name + itoa(retrialNum, numstr, 10));

        text->setText(result);
    }
    retrialNum++;
}

void UserInterface::onResult(QNetworkReply* reply)
{
    if (reply->error() != QNetworkReply::NoError)
        return;

    //If no error occur data are retrieved and text is updated
    QByteArray data = reply->readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonObject json = doc.object();

    QString bid = QString("BC/EUR: ");
    QString bidValue = json["bid"].toString();
    bid.append(bidValue);
    text->setText(bid);
    retrialNum = -1;

    reply->deleteLater();
}

UserInterface::~UserInterface()
{
    delete ui;
}
