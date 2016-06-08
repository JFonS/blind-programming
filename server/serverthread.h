#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H
#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QKeyEvent>
#include <QProcess>


class ServerThread : public QThread
{
  Q_OBJECT

public:
  explicit ServerThread(qintptr ID, QObject *parent = 0);

  void run();

signals:
  void error(QTcpSocket::SocketError socketerror);

public slots:
  void readyRead();
  void disconnected();

private:
  QTcpSocket *socket;
  qintptr socketDescriptor;
  QProcess *editorProcess;
  int id;

};

#endif // SERVERTHREAD_H
