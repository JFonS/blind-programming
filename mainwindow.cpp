#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  grabKeyboard();
  editorProcess = new QProcess(this);
  QString editorCmd = "konsole -name blindEditor1 -e ";
  editorCmd += "vim";
  //editorCmd += "nano";

  editorProcess->start(editorCmd);

}

MainWindow::~MainWindow()
{
  delete ui;
}



void MainWindow::keyPressEvent(QKeyEvent *e){

  QString keyCode = QString("0x") + QString::number(e->nativeVirtualKey(),16);

  if (e->modifiers() == Qt::ControlModifier
      and e->nativeVirtualKey() != 0xffe3 and e->nativeVirtualKey() != 0xffe4) {
      keyCode = QString("Control_L+")+keyCode;
  }

  QString cmd = QString("xdotool search --classname blindEditor1 key %1").arg(keyCode);

  QProcess::execute(cmd);

}

