#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "QtNetwork/QNetworkInterface"
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_DHCP_clicked()
{
    ui->STATICIP->setEnabled(false);
}

void MainWindow::on_STATIC_clicked()
{
    ui->STATICIP->setEnabled(true);
}


void MainWindow::on_lineEdit_masque_cursorPositionChanged(int arg1, int arg2)
{
//    int adr1, adr2, adr3, adr4, mask1, mask2, mask3, mask4;
//    adr1 = ui->adr1->value();
//    adr2 = ui->adr2->value();
//    adr3 = ui->adr3->value();
//    adr4 = ui->adr4->value();

    QString ip = ui->lineEdit_ip->text();

    if(ip.contains("192.")){
        QMessageBox::information(this,"message","classe C");
        ui->lineEdit_masque->setText("255.255.255.0");
    }
    else if(ip.contains("169.")){
        QMessageBox::information(this,"message","classe B");
        ui->lineEdit_masque->setText("255.255.0.0");
    }
    else if(ip.contains("169.")){
        QMessageBox::information(this,"message","classe A");
        ui->lineEdit_masque->setText("255.0.0.0");
    }
}

void MainWindow::on_btnValider_clicked()
{
    if(ui->DHCP->isChecked() && ui->lineEdit_ip->text().isEmpty() && ui->lineEdit_masque->text().isEmpty()){
        QString cmd("netsh interface ip set address \"Ethernet\" dhcp");
        QProcess proc;
        proc.start(cmd);
        proc.waitForFinished();
        qDebug() << proc.readAll();
        QMessageBox::information(this,"message","Commande réussie");
    }
    else if(ui->lineEdit_ip->text().isEmpty() && ui->lineEdit_masque->text().isEmpty()){
        QMessageBox::information(this,"message","L'un des champs est vide.");
    }
    else {
        QString cmdIP("netsh interface ip set address \"Ethernet\" static " + ui->lineEdit_ip->text() + " " + ui->lineEdit_masque->text() + " " + ui->lineEdit_3->text() + " ");
        QString cmdDNS("netsh interface ip set dns \"Ethernet\" static " + ui->lineEdit_4->text() + " primary");
        QProcess proc;
        proc.start(cmdIP);
        proc.start(cmdDNS);
        proc.waitForFinished();
        qDebug() << proc.readAll();
        QMessageBox::information(this,"message","Commande réussie");
    }
}

void MainWindow::on_btnAnnuler_clicked()
{
    close();
}
