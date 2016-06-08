    #include "serverthread.h"

  ServerThread::ServerThread(qintptr ID, QObject *parent) :
      QThread(parent),
      id(ID)
  {
      this->socketDescriptor = ID;
  }

  void ServerThread::run()
  {
      // thread starts here
      qDebug() << " Thread started";

      socket = new QTcpSocket();

      // set the ID
      if(!socket->setSocketDescriptor(this->socketDescriptor))
      {
          // something's wrong, we just emit a signal
          emit error(socket->error());
          return;
      }

      // connect socket and signal
      // note - Qt::DirectConnection is used because it's multithreaded
      //        This makes the slot to be invoked immediately, when the signal is emitted.

      connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
      connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

      // We'll have multiple clients, we want to know which is which
      qDebug() << socketDescriptor << " Client connected";

      // make this thread a loop,
      // thread will stay alive so that signal/slot to function properly
      // not dropped out in the middle when thread dies

      editorProcess = new QProcess(this);
      QString editorCmd = QString("konsole -name blindEditor%1 -e ").arg(id);
      editorCmd += "vim";
      //editorCmd += "nano";

      editorProcess->start(editorCmd);

      exec();
  }

  void ServerThread::readyRead()
  {
      // get the information
      QByteArray Data = socket->readAll();

      // will write on server side window
      qDebug() << socketDescriptor << " Data in: " << Data << " PID: " << editorProcess->pid();

      QString keyCode = QString(Data); //QString("0x") + QString::number(e->nativeVirtualKey(),16);

      /*if (e->modifiers() == Qt::ControlModifier
          and e->nativeVirtualKey() != 0xffe3 and e->nativeVirtualKey() != 0xffe4) {
          keyCode = QString("Control_L+")+keyCode;
      }*/

      QString cmd = QString("xdotool search --classname blindEditor%1 key %2").arg(id).arg(keyCode);

      QProcess::execute(cmd);

      socket->write(Data);
  }

  void ServerThread::disconnected()
  {
      qDebug() << socketDescriptor << " Disconnected, killing " << editorProcess->pid();

      editorProcess->close();

      socket->deleteLater();
      exit(0);
  }
