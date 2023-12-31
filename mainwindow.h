#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_DHCP_clicked();

    void on_STATIC_clicked();

    void on_lineEdit_masque_cursorPositionChanged(int arg1, int arg2);

    void on_btnValider_clicked();

    void on_btnAnnuler_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
