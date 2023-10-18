#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    renk = qRgb(255,0,0);
    QImage ortam(1024,768,QImage::Format_RGB32);
    ui->lblEkran->setPixmap(QPixmap::fromImage(ortam));
    res = ortam;
    ui->lblEkran->setGeometry(0,0,1024,768);
    ui->lblEkran->setFrameShape(QFrame::Box);
    ui->lblEkran->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::EkraninOrtasi()
{
    int x1 = 0;
    int x2 = 1024;
    int y1 = 768;
    int y2 = 0;

    xOrta = (x1 + x2)/2;
    yOrta = (y1 + y2)/2;
    OrtaNokta.rx() = xOrta;
    OrtaNokta.ry() = yOrta;
    res.setPixel(OrtaNokta.x(), OrtaNokta.y(), renk);
    ui->lblEkran->setPixmap(QPixmap::fromImage(res));
}

void MainWindow::on_cmbRenk_currentTextChanged(const QString &arg1)
{
    if(ui->cmbRenk->currentText() == "Red")
    {
        renk2 = qRgb(255,0,0);
    }

    if(ui->cmbRenk->currentText() == "Blue")
    {
        renk2 = qRgb(32,163,221);
    }

    if(ui->cmbRenk->currentText() == "Yellow")
    {
        renk2 = qRgb(255,240,80);
    }

    if(ui->cmbRenk->currentText() == "Green")
    {
        renk2 = qRgb(0,128,0);
    }
    if(ui->cmbRenk->currentText() == "Orange")
    {
        renk2 = qRgb(255,130,50);
    }
    if(ui->cmbRenk->currentText() == "Purple")
    {
        renk2 = qRgb(120,59,146);
    }

    if(ui->cmbRenk->currentText() == "Pink")
    {
        renk2 = qRgb(255,179,222);
    }

    if(ui->cmbRenk->currentText() == "Dark Pink")
    {
        renk2 = qRgb(231,67,148);
    }
}

void MainWindow::dogruCizDDA2(QPoint ilk ,QPoint son)
{
    double dx=son.x()-ilk.x();
    double dy=son.y()-ilk.y();
    double Xartim, Yartim;
    double adim;
    double x,y;
    if(fabs(dx)>fabs(dy))
    {
        adim=fabs(dx);
    }
    else
    {
        adim=fabs(dy);
    }
    Xartim=dx/adim;
    Yartim=dy/adim;
    x=ilk.x();
    y=ilk.y();

    for(int i=0; i<adim; i++)
    {
        QApplication::processEvents();
        x+=Xartim;
        y+=Yartim;
        res.setPixel(round(x),round(y),renk2);
        ui->lblEkran->setPixmap(QPixmap::fromImage(res));
    }

}

void MainWindow::cemberBresenham()
{
    if(cemberOlcekle == 1)
    {
        cemberX = DcemberX;
        cemberY = DcemberY;
        int hata = 0;
        int hata1; // x, y+1
        int hata2; // x-1, y+1
        Simetri(cemberX, cemberY);
        while(cemberX >= cemberY) {
            QApplication::processEvents();
            hata1 = hata + 2*cemberY + 1;
            hata2 = hata + 2*cemberY + 1 - 2*cemberX + 1;
            if (abs(hata1) < abs(hata2)) {
                cemberY++;
                hata = hata1;
            } else {
                cemberX--;
                cemberY++;
                hata = hata2;
            }
            Simetri(cemberX, cemberY);
            ui->lblEkran->setPixmap(QPixmap::fromImage(res));
          }
    }
    else
    {
        cemberX = 50;
        cemberY = 0;
        int hata = 0;
        int hata1; // x, y+1
        int hata2; // x-1, y+1
        Simetri(cemberX, cemberY);
        while(cemberX >= cemberY) {
            QApplication::processEvents();
            hata1 = hata + 2*cemberY + 1;
            hata2 = hata + 2*cemberY + 1 - 2*cemberX + 1;
            if (abs(hata1) < abs(hata2)) {
                cemberY++;
                hata = hata1;
            } else {
                cemberX--;
                cemberY++;
                hata = hata2;
            }
            Simetri(cemberX, cemberY);
            ui->lblEkran->setPixmap(QPixmap::fromImage(res));
          }
    }
      //Doldur(OrtaNokta.x(),OrtaNokta.y(),res.pixel(OrtaNokta.x(),OrtaNokta.y()),renk);
}

void MainWindow::Simetri(int X, int Y)
{
    res.setPixel(OrtaNokta.x() + X, OrtaNokta.y() + Y, renk2);
    res.setPixel(OrtaNokta.x() + Y, OrtaNokta.y() + X, renk2);
    res.setPixel(OrtaNokta.x() - Y, OrtaNokta.y() + X, renk2);
    res.setPixel(OrtaNokta.x() - X, OrtaNokta.y() + Y, renk2);
    res.setPixel(OrtaNokta.x() - X, OrtaNokta.y() - Y, renk2);
    res.setPixel(OrtaNokta.x() - Y, OrtaNokta.y() - X, renk2);
    res.setPixel(OrtaNokta.x() + Y, OrtaNokta.y() - X, renk2);
    res.setPixel(OrtaNokta.x() + X, OrtaNokta.y() - Y, renk2);
}

void MainWindow::Doldur(int x, int y, QRgb zemin, QRgb yeniRenk)
{

    QApplication::processEvents();
    if(res.pixel(x,y)==zemin)
    {
        res.setPixel(x,y,yeniRenk);
        ui->lblEkran->setPixmap(QPixmap::fromImage(res));
        Doldur(x+1,y,zemin,yeniRenk);
        Doldur(x-1,y,zemin,yeniRenk);
        Doldur(x,y+1,zemin,yeniRenk);
        Doldur(x,y-1,zemin,yeniRenk);
    }
}

void MainWindow::on_btnUygula_clicked()
{
    res = QImage();
    QImage ortam(1024,768,QImage::Format_RGB32);
    ui->lblEkran->setPixmap(QPixmap::fromImage(ortam));
    res = ortam;
    EkraninOrtasi();
    QString sekil = ui->cmbSekil->currentText();
    //QString crntRenk = ui->cmbRenk->currentText();

    if(sekil == "Square")
    {
      cemberMi =0;
      KoselerListesi.clear();
      QPoint A ,B ,C , D;
      A.rx() = (OrtaNokta.x()-a);
      A.ry() = (OrtaNokta.y()-a);
      res.setPixel(A.x(), A.y(), renk2);
      ui->lblEkran->setPixmap(QPixmap::fromImage(res));

      B.rx() = (OrtaNokta.x()-a);
      B.ry() = (OrtaNokta.y()+a);
      res.setPixel(B.x(), B.y(), renk2);
      ui->lblEkran->setPixmap(QPixmap::fromImage(res));

      C.rx() = (OrtaNokta.x()+a);
      C.ry() = (OrtaNokta.y()+a);
      res.setPixel(C.x(), C.y(), renk2);
      ui->lblEkran->setPixmap(QPixmap::fromImage(res));

      D.rx() = (OrtaNokta.x()+a);
      D.ry() = (OrtaNokta.y()-a);
      res.setPixel(D.x(), D.y(), renk2);
      ui->lblEkran->setPixmap(QPixmap::fromImage(res));

      KoselerListesi.append(A);
      bitis = A;
      KoselerListesi.append(B);
      KoselerListesi.append(C);
      KoselerListesi.append(D);

      //KoselerListesi.append(KoselerListesi[0]);
      for(int i=0; i<(KoselerListesi.length()); i++)
      {
          if(i == KoselerListesi.length()-1)
          {
            dogruCizDDA2(KoselerListesi[i],bitis);
          }
          else
          {
            dogruCizDDA2(KoselerListesi[i],KoselerListesi[i+1]);
          }
      }
      //KoselerListesi.clear();

    }

    if(sekil == "Tringle")
    {
      cemberMi = 0;
      KoselerListesi.clear();
      QPoint A ,B ,C;
      int kokUc = sqrt(3);

      A.rx() = (OrtaNokta.x()-a);
      A.ry() = (OrtaNokta.y()+ round((a*kokUc)/3));
      res.setPixel(A.x(), A.y(), renk2);
      ui->lblEkran->setPixmap(QPixmap::fromImage(res));

      B.rx() = (OrtaNokta.x());
      B.ry() = (OrtaNokta.y()+-round((2*a*kokUc)/3));
      res.setPixel(B.x(), B.y(), renk2);
      ui->lblEkran->setPixmap(QPixmap::fromImage(res));

      C.rx() = (OrtaNokta.x()+a);
      C.ry() = (OrtaNokta.y()+ round((a*kokUc)/3));
      res.setPixel(C.x(), C.y(), renk2);
      ui->lblEkran->setPixmap(QPixmap::fromImage(res));


      KoselerListesi.append(A);
      bitis = A;
      KoselerListesi.append(B);
      KoselerListesi.append(C);

      //KoselerListesi.append(KoselerListesi[0]);
      for(int i=0; i<(KoselerListesi.length()); i++)
      {

          if(i == KoselerListesi.length()-1)
          {
            dogruCizDDA2(KoselerListesi[i],bitis);
          }
          else
          {
            dogruCizDDA2(KoselerListesi[i],KoselerListesi[i+1]);
          }
      }
      //KoselerListesi.clear();

    }

    if(sekil == "Rectangle")
    {
      cemberMi =0;
      KoselerListesi.clear();
      QPoint A ,B ,C ,D;
      int kokUc = sqrt(3);

      A.rx() = (OrtaNokta.x()-a);
      A.ry() = (OrtaNokta.y()+ -b);
      res.setPixel(A.x(), A.y(), renk2);
      ui->lblEkran->setPixmap(QPixmap::fromImage(res));

      B.rx() = (OrtaNokta.x() - a);
      B.ry() = (OrtaNokta.y() + b);
      res.setPixel(B.x(), B.y(), renk2);
      ui->lblEkran->setPixmap(QPixmap::fromImage(res));

      C.rx() = (OrtaNokta.x()+a);
      C.ry() = (OrtaNokta.y()+ b);
      res.setPixel(C.x(), C.y(), renk2);
      ui->lblEkran->setPixmap(QPixmap::fromImage(res));

      D.rx() = (OrtaNokta.x()+a);
      D.ry() = (OrtaNokta.y()-b);
      res.setPixel(D.x(), D.y(), renk2);
      ui->lblEkran->setPixmap(QPixmap::fromImage(res));

      KoselerListesi.append(A);
      bitis = A;
      KoselerListesi.append(B);
      KoselerListesi.append(C);
      KoselerListesi.append(D);

      //KoselerListesi.append(KoselerListesi[0]);
      for(int i=0; i<(KoselerListesi.length()); i++)
      {
          if(i == KoselerListesi.length()-1)
          {
            dogruCizDDA2(KoselerListesi[i],bitis);
          }
          else
          {
            dogruCizDDA2(KoselerListesi[i],KoselerListesi[i+1]);
          }
      }

    }

    if(sekil == "Circle")
    {
      cemberMi = 1;
      cemberOlcekle = 0;
      CemberOrta = OrtaNokta;
      DcemberX = 50;
      DcemberY = 0;
      cemberBresenham();

    }

    if(sekil == "Pentagon")
    {
      cemberMi =0;
      KoselerListesi.clear();
      QPoint A ,B ,C ,D ,E;
      int kokUc = sqrt(3);

      A.rx() = (OrtaNokta.x()-a);
      A.ry() = (OrtaNokta.y()+ -b);
      res.setPixel(A.x(), A.y(), renk2);
      ui->lblEkran->setPixmap(QPixmap::fromImage(res));

      B.rx() = (OrtaNokta.x() - a);
      B.ry() = (OrtaNokta.y() + b);
      res.setPixel(B.x(), B.y(), renk2);
      ui->lblEkran->setPixmap(QPixmap::fromImage(res));

      C.rx() = (OrtaNokta.x()+a);
      C.ry() = (OrtaNokta.y()+ b);
      res.setPixel(C.x(), C.y(), renk2);
      ui->lblEkran->setPixmap(QPixmap::fromImage(res));

      D.rx() = (OrtaNokta.x()+a);
      D.ry() = (OrtaNokta.y()-b);
      res.setPixel(D.x(), D.y(), renk2);
      ui->lblEkran->setPixmap(QPixmap::fromImage(res));

      E.rx() = (OrtaNokta.x()+a);
      E.ry() = (OrtaNokta.y()-b);
      res.setPixel(D.x(), D.y(), renk2);
      ui->lblEkran->setPixmap(QPixmap::fromImage(res));

      KoselerListesi.append(A);
      bitis = A;
      KoselerListesi.append(B);
      KoselerListesi.append(C);
      KoselerListesi.append(D);
      KoselerListesi.append(E);

      //KoselerListesi.append(KoselerListesi[0]);
      for(int i=0; i<(KoselerListesi.length()); i++)
      {
          if(i == KoselerListesi.length()-1)
          {
            dogruCizDDA2(KoselerListesi[i],bitis);
          }
          else
          {
            dogruCizDDA2(KoselerListesi[i],KoselerListesi[i+1]);
          }
      }
      //KoselerListesi.clear();


    }
}

void MainWindow::on_btnSaga_clicked()
{
    res = QImage();
    QImage ortam(1024,768,QImage::Format_RGB32);
    ui->lblEkran->setPixmap(QPixmap::fromImage(ortam));
    res = ortam;

    if(cemberMi ==1)
    {
        //boyandiMi = 0;
        OrtaNokta.rx() = OrtaNokta.x()+cemberOteleme;
        CemberOrta.rx() = OrtaNokta.x();
        CemberOrta.ry() = OrtaNokta.y();
        //cemberY = 0;
        //cemberX = 50;
        cemberY = DcemberY;
        cemberX = DcemberX;
        //DcemberX = cemberX;
        //DcemberY = cemberY;
        cemberBresenham();
        while (cemberX>=cemberY) {
            ui->lblEkran->setPixmap(QPixmap::fromImage(res));
        }

    }
    //KoselerListesi.append(KoselerListesi[0]);
    else{

        for (int i = 0; i < KoselerListesi.length(); ++i) {
            KoselerListesi[i].rx() = KoselerListesi[i].x() + otelemeMiktarı;
            KoselerListesi[i].ry() = KoselerListesi[i].y();
            res.setPixel(KoselerListesi[i].x(),KoselerListesi[i].y(),renk2);
            ui->lblEkran->setPixmap(QPixmap::fromImage(res));
        }
        bitis = KoselerListesi[0];

        for (int j = 0; j < KoselerListesi.length(); ++j) {

            if(j == KoselerListesi.length()-1)
            {
              dogruCizDDA2(KoselerListesi[j],bitis);
            }
            else
            {
              dogruCizDDA2(KoselerListesi[j],KoselerListesi[j+1]);
            }
        }
    }
    //KoselerListesi.clear();


}


void MainWindow::on_btnSola_clicked()
{
    res = QImage();
    QImage ortam(1024,768,QImage::Format_RGB32);
    ui->lblEkran->setPixmap(QPixmap::fromImage(ortam));
    res = ortam;
    if(cemberMi ==1)
    {
        //boyandiMi = 0;
        OrtaNokta.rx() = OrtaNokta.x()-cemberOteleme;
        CemberOrta.rx() = OrtaNokta.x();
        CemberOrta.ry() = OrtaNokta.y();
        //cemberY = 0;
        //cemberX = 50;
        cemberY = DcemberY;
        cemberX = DcemberX;
        //DcemberX = cemberX;
        //DcemberY = cemberY;
        cemberBresenham();
        while (cemberX>=cemberY) {
            ui->lblEkran->setPixmap(QPixmap::fromImage(res));
        }

    }
    //KoselerListesi.append(KoselerListesi[0]);
    else{

        for (int i = 0; i < KoselerListesi.length(); ++i) {

            KoselerListesi[i].rx() = KoselerListesi[i].x() - otelemeMiktarı;
            KoselerListesi[i].ry() = KoselerListesi[i].y();
            res.setPixel(KoselerListesi[i].x(),KoselerListesi[i].y(),renk2);
            ui->lblEkran->setPixmap(QPixmap::fromImage(res));
        }
        bitis = KoselerListesi[0];

        for (int j = 0; j < KoselerListesi.length(); ++j) {

            if(j == KoselerListesi.length()-1)
            {
              dogruCizDDA2(KoselerListesi[j],bitis);
            }
            else
            {
              dogruCizDDA2(KoselerListesi[j],KoselerListesi[j+1]);
            }
        }
    }
    //KoselerListesi.clear();
}


void MainWindow::on_btnYukari_clicked()
{
    res = QImage();
    QImage ortam(1024,768,QImage::Format_RGB32);
    ui->lblEkran->setPixmap(QPixmap::fromImage(ortam));
    res = ortam;
    if(cemberMi ==1)
    {
        //boyandiMi = 0;
        OrtaNokta.ry() = OrtaNokta.y()-cemberOteleme;
        CemberOrta.rx() = OrtaNokta.x();
        CemberOrta.ry() = OrtaNokta.y();
        //cemberY = 0;
        //cemberX = 50;
        cemberY = DcemberY;
        cemberX = DcemberX;
        //DcemberX = cemberX;
        //DcemberY = cemberY;
        cemberBresenham();
        while (cemberX>=cemberY) {
            ui->lblEkran->setPixmap(QPixmap::fromImage(res));
        }

    }
   else{

        for (int i = 0; i < KoselerListesi.length(); ++i) {

            KoselerListesi[i].rx() = KoselerListesi[i].x();
            KoselerListesi[i].ry() = KoselerListesi[i].y() - otelemeMiktarı;
            res.setPixel(KoselerListesi[i].x(),KoselerListesi[i].y(),renk2);
            ui->lblEkran->setPixmap(QPixmap::fromImage(res));
        }
        bitis = KoselerListesi[0];

        for (int j = 0; j < KoselerListesi.length(); ++j) {

            if(j == KoselerListesi.length()-1)
            {
              dogruCizDDA2(KoselerListesi[j],bitis);
            }
            else
            {
              dogruCizDDA2(KoselerListesi[j],KoselerListesi[j+1]);
            }
        }
    }
}


void MainWindow::on_btnAsagi_clicked()
{
    res = QImage();
    QImage ortam(1024,768,QImage::Format_RGB32);
    ui->lblEkran->setPixmap(QPixmap::fromImage(ortam));
    res = ortam;
    if(cemberMi ==1)
    {
        //boyandiMi = 0;
        OrtaNokta.ry() = OrtaNokta.y()+cemberOteleme;
        CemberOrta.rx() = OrtaNokta.x();
        CemberOrta.ry() = OrtaNokta.y();
        //cemberY = 0;
        //cemberX = 50;
        cemberY = DcemberY;
        cemberX = DcemberX;
        //DcemberX = cemberX;
        //DcemberY = cemberY;
        cemberBresenham();
        while (cemberX>=cemberY) {
            ui->lblEkran->setPixmap(QPixmap::fromImage(res));
        }

    }
    else{

        for (int i = 0; i < KoselerListesi.length(); ++i) {

            KoselerListesi[i].rx() = KoselerListesi[i].x();
            KoselerListesi[i].ry() = KoselerListesi[i].y() + otelemeMiktarı;
            res.setPixel(KoselerListesi[i].x(),KoselerListesi[i].y(),renk2);
            ui->lblEkran->setPixmap(QPixmap::fromImage(res));
        }
        bitis = KoselerListesi[0];

        for (int j = 0; j < KoselerListesi.length(); ++j) {

            if(j == KoselerListesi.length()-1)
            {
              dogruCizDDA2(KoselerListesi[j],bitis);
            }
            else
            {
              dogruCizDDA2(KoselerListesi[j],KoselerListesi[j+1]);
            }
        }
    }
}


void MainWindow::on_btnKucult_clicked()
{
    res = QImage();
    QImage ortam(1024,768,QImage::Format_RGB32);
    ui->lblEkran->setPixmap(QPixmap::fromImage(ortam));
    res = ortam;
    cemberOlcekle = 1;
    if(cemberMi ==1)
    {
        //boyandiMi = 0;
        //OrtaNokta.rx() = OrtaNokta.x()-cemberOteleme;
        cemberY = 0;
        cemberX = cemberX-cemberKucult;
        DcemberX = cemberX;
        DcemberY = cemberY;
        cemberBresenham();
        while (cemberX>=cemberY) {
            ui->lblEkran->setPixmap(QPixmap::fromImage(res));
        }

    }
    else{
        double x,y;
        double sx,sy;

        sx=0.7;
        sy=0.7;

        for (int i = 0; i < KoselerListesi.length(); ++i) {

            KoselerListesi[i].rx() = KoselerListesi[i].x()*sx;
            KoselerListesi[i].ry() = KoselerListesi[i].y()*sy;
            res.setPixel(KoselerListesi[i].x(),KoselerListesi[i].y(),renk2);

        }
        ui->lblEkran->setPixmap(QPixmap::fromImage(res2));
        bitis = KoselerListesi[0];

        for (int j = 0; j < KoselerListesi.length(); ++j) {

            if(j == KoselerListesi.length()-1)
            {
              dogruCizDDA2(KoselerListesi[j],bitis);
            }
            else
            {
              dogruCizDDA2(KoselerListesi[j],KoselerListesi[j+1]);
            }
        }

    }
}


void MainWindow::on_btnBuyult_clicked()
{
    res = QImage();
    QImage ortam(1024,768,QImage::Format_RGB32);
    ui->lblEkran->setPixmap(QPixmap::fromImage(ortam));
    res = ortam;
    cemberOlcekle = 1;
    if(cemberMi ==1)
    {
        //boyandiMi = 0;
        //OrtaNokta.rx() = OrtaNokta.x()+cemberOteleme;
        cemberY = 0;
        cemberX = cemberX+cemberOteleme;
        DcemberX = cemberX;
        DcemberY = cemberY;
        cemberBresenham();
        while (cemberX>=cemberY) {
            ui->lblEkran->setPixmap(QPixmap::fromImage(res));
        }

    }
   else{
        double x,y;
        double sx,sy;

        sx=1.2;
        sy=1.2;

        for (int i = 0; i < KoselerListesi.length(); ++i) {

            KoselerListesi[i].rx() = KoselerListesi[i].x()*sx;
            KoselerListesi[i].ry() = KoselerListesi[i].y()*sy;
            res2.setPixel(KoselerListesi[i].x(),KoselerListesi[i].y(),renk2);

        }
        ui->lblEkran->setPixmap(QPixmap::fromImage(res));
        bitis = KoselerListesi[0];

        for (int j = 0; j < KoselerListesi.length(); ++j) {

            if(j == KoselerListesi.length()-1)
            {
              dogruCizDDA2(KoselerListesi[j],bitis);
            }
            else
            {
              dogruCizDDA2(KoselerListesi[j],KoselerListesi[j+1]);
            }
        }
    }
 }



void MainWindow::on_btnBoya_clicked()
{
    if(cemberMi == 1 )
    {
        cemberX = DcemberX;
        cemberY = DcemberY;
        while (cemberX>=cemberY) {
            Doldur(CemberOrta.x()+1,CemberOrta.y()+1,res.pixel(cemberX,cemberY),renk2);
        }

        //Doldur(OrtaNokta.x()+1,OrtaNokta.y()+1,res.pixel(cemberX,cemberY),renk2);

        //KoselerListesi.clear();
    }
    else
    {
        int x=0,y=0;
        KoselerListesi.append(KoselerListesi[0]);
        for(int i=0;i<KoselerListesi.length()-1;i++)//birinci elemandan 2 tane var o yüzden -1
        {
            x+=KoselerListesi[i].x();
            y+=KoselerListesi[i].y();
        }
        x=x/(KoselerListesi.length()-1);
        y=y/(KoselerListesi.length()-1);
        Doldur(x,y,res.pixel(x,y),renk2);
        //Doldur(KoselerListesi[0].x(),KoselerListesi[0].y(),res.pixel(x,y),renk);
        //KoselerListesi.clear();
    }
}

