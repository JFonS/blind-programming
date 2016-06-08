#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket(this);
  socket->connectToHost(QHostAddress("127.0.0.1"), 1234,QIODevice::ReadWrite);
  //while(socket->waitForConnected());

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
  QString keyCode = QString("0x") + QString::number(e->nativeVirtualKey(),16);
  if (e->modifiers() == Qt::ControlModifier
      and e->nativeVirtualKey() != 0xffe3 and e->nativeVirtualKey() != 0xffe4) {
    keyCode = QString("Control_L+")+keyCode;
  }


  socket->write(keyCode.toUtf8());
}
