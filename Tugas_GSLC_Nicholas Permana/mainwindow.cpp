#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QtDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mNetManager = new QNetworkAccessManager(this);
    connect(mNetManager, &QNetworkAccessManager::finished,
            this, &MainWindow::handleNetFinished);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openUrl(const QString &url)
{
    mNetManager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::testJson(QByteArray data){
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

    QString Quote = obj["quote"].toString();

    qDebug() << Quote;

    ui->quote_label->setText(Quote);

    //website: https://api.kanye.rest
}

void MainWindow::handleNetFinished(QNetworkReply *reply)
{
    if (reply->error()==QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();
        testJson(data);
    }
    else
        qDebug("Network error");
}

void MainWindow::on_pushButtonGetUrl_clicked()
{
    openUrl(ui->lineEditUrl->text());

}
