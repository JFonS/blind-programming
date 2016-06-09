#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  QStringList items;
  items << "TEST1" << "TEST2";
  ui->comboBox->addItems(items);
}

MainWindow::~MainWindow()
{
  delete ui;
}

