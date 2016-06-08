#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
#include <QKeyEvent>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void keyPressEvent(QKeyEvent * event);

private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;

};

#endif // MAINWINDOW_H
