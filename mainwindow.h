#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <math.h>

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

    void on_btnUygula_clicked();

    void on_cmbRenk_currentTextChanged(const QString &arg1);

    void on_btnSaga_clicked();

    void on_btnSola_clicked();

    void on_btnYukari_clicked();

    void on_btnAsagi_clicked();

    void on_btnKucult_clicked();

    void on_btnBuyult_clicked();

    void on_btnBoya_clicked();

private:
    Ui::MainWindow *ui;
    QRgb renk;
    QRgb renk2;
    QRgb renkdeneme;
    int a = 50;
    int b = 30;
   // QImage ortam;
    QImage res;
    QImage res2;
    QPoint OrtaNokta;
    QPoint CemberOrta;
    QPoint ilkNokta;
    QPoint sonNokta;
    QPoint bitis;
    int xOrta;
    int yOrta;
    int tpsag=0;
    int tpsol = 0;
    void EkraninOrtasi();
    QList<QPoint> KoselerListesi;
    void dogruCizDDA2(QPoint ilk,QPoint son);
    int otelemeMiktarı = 100;
    int cemberOteleme=50;
    int cemberKucult=10;
    void cemberBresenham();
    int cemberX = 50, cemberY = 0;
    int DcemberX, DcemberY;
    int cemberMi = 0;
    int cemberOlcekle =0;
    void Simetri(int , int);
    void Doldur(int , int , QRgb , QRgb);
};
#endif // MAINWINDOW_H
