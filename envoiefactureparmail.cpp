#include "envoiefactureparmail.h"

Smtp::Smtp( const QString &user, const QString &pass, const QString &host, int port, int timeout )
{
  socket = new QSslSocket(this);

  connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
  connect(socket, SIGNAL(connected()), this, SLOT(connected() ) );
  connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this,SLOT(errorReceived(QAbstractSocket::SocketError)));
  connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
  connect(socket, SIGNAL(disconnected()), this,SLOT(disconnected()));


  this->user = user;
  this->pass = pass;

  this->host = host;
  this->port = port;
  this->timeout = timeout;


}

Smtp::~Smtp()
{
  delete t;
  delete socket;
}

void Smtp::sendMail(const QString &from, const QString &to, const QString &subject, const QString &body, QStringList files)
{
    message = "To: " + to + "\n";
       message.append("From: " + from + "\n");
       message.append("Subject: " + subject + "\n");

       //Let's intitiate multipart MIME with cutting boundary "frontier"
       message.append("MIME-Version: 1.0\n");
       message.append("Content-Type: multipart/mixed; boundary=frontier\n\n");



       message.append( "--frontier\n" );
       //message.append( "Content-Type: text/html\n\n" );  //Uncomment this for HTML formating, coment the line below
       message.append( "Content-Type: text/plain\n\n" );
       message.append(body);
       message.append("\n\n");

       if(!files.isEmpty())
       {
           qDebug() << "Files to be sent: " << files.size();
           foreach(QString filePath, files)
           {
               QFile file(filePath);
               if(file.exists())
               {
                   if (!file.open(QIODevice::ReadOnly))
                   {
                       qDebug("Couldn't open the file");
                       QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Couldn't open the file\n\n" )  );
                           return ;
                   }
                   QByteArray bytes = file.readAll();
                   message.append( "--frontier\n" );
                   message.append( "Content-Type: application/octet-stream\nContent-Disposition: attachment; filename="+ QFileInfo(file.fileName()).fileName() +";\nContent-Transfer-Encoding: base64\n\n" );
                   message.append(bytes.toBase64());
                   message.append("\n");
               }
           }
       }
       else
           qDebug() << "No attachments found";


       message.append( "--frontier--\n" );

       message.replace( QString::fromLatin1( "\n" ), QString::fromLatin1( "\r\n" ) );
       message.replace( QString::fromLatin1( "\r\n.\r\n" ),QString::fromLatin1( "\r\n..\r\n" ) );


       this->from = from;
       rcpt = to;
       state = Init;
       socket->connectToHostEncrypted("smtp.gmail.com",465); //"smtp.gmail.com" and 465 for gmail TLS
       if (!socket->waitForConnected(timeout)) {
            qDebug()<< "send_mail " << socket->errorString();
        }

       t = new QTextStream( socket );

}

void Smtp::stateChanged(QAbstractSocket::SocketState socketState)
{

  qDebug() <<"stateChanged " << socketState;
}

void Smtp::errorReceived(QAbstractSocket::SocketError socketError)
{
  qDebug() << "error " <<socketError;
}

void Smtp::disconnected()
{

  qDebug() <<"disconneted";
  qDebug() << "error "  << socket->errorString();
}

void Smtp::connected()
{
  qDebug() << "Connected ";
}

void Smtp::readyRead()
{

  qDebug() <<"readyRead";


  QString responseLine;
  do
    {
      responseLine = socket->readLine();
      response += responseLine;
    }
  while ( socket->canReadLine() && responseLine[3] != ' ' );

  responseLine.truncate( 3 );

  qDebug() << "Server response code:" <<  responseLine;
  qDebug() << "Server response: " << response;

  if ( state == Init && responseLine == "220" )
    {

      *t << "EHLO localhost" <<"\r\n";

      t->flush();

      state = HandShake;
    }
  else if (state == HandShake && responseLine == "250")
    {
      socket->startClientEncryption();
      if(!socket->waitForEncrypted(timeout))
        {
          qDebug() << socket->errorString();
          state = Close;
        }

      *t << "EHLO localhost" << "\r\n";
      t->flush();
      state = Auth;
    }
  else if (state == Auth && responseLine == "250")
    {
      qDebug() << "Auth";
      *t << "AUTH LOGIN" << "\r\n";
      t->flush();
      state = User;
    }
  else if (state == User && responseLine == "334")
    {
      qDebug() << "Username";
      *t << QByteArray().append(user).toBase64()  << "\r\n";
      t->flush();

      state = Pass;
    }
  else if (state == Pass && responseLine == "334")
    {
      qDebug() << "Pass";
      *t << QByteArray().append(pass).toBase64() << "\r\n";
      t->flush();

      state = Mail;
    }
  else if ( state == Mail && responseLine == "235" )
    {
      qDebug() << "MAIL FROM:<" << from << ">";
      *t << "MAIL FROM:<" << from << ">\r\n";
      t->flush();
      state = Rcpt;
    }
  else if ( state == Rcpt && responseLine == "250" )
    {
      *t << "RCPT TO:<" << rcpt << ">\r\n"; //r
      t->flush();
      state = Data;
    }
  else if ( state == Data && responseLine == "250" )
    {

      *t << "DATA\r\n";
      t->flush();
      state = Body;
    }
  else if ( state == Body && responseLine == "354" )
    {
      *t << message << "\r\n.\r\n";
      t->flush();
      state = Quit;
    }
  else if ( state == Quit && responseLine == "250" )
    {

      *t << "QUIT\r\n";
      t->flush();
      state = Close;
      emit status( tr( "Message sent" ) );
    }
  else if ( state == Close )
    {
      deleteLater();
      return;
    }
  else
    {
      QMessageBox::warning(0,"System Message!","Something Went Wrong",QMessageBox::Ok);

      state = Close;
      emit status( tr( "Failed to send message" ) );
    }
  response = "";
}
