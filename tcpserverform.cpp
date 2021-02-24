#include "tcpserverform.h"
#include "ui_tcpserverform.h"
#include <QMessageBox>
#include <QDebug>

tcpserverForm::tcpserverForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tcpserverForm)
{
    ui->setupUi(this);
    setWindowTitle(QObject::tr("TCP Server"));
    tcp_server = new QTcpServer(this);
    tcp_server_socket = new QTcpSocket(this);

    //监听端口获得新连接
    connect(tcp_server,&QTcpServer::newConnection,this,&tcpserverForm::after_listen_get_new_connect);

}

tcpserverForm::~tcpserverForm()
{
    delete ui;
}

void tcpserverForm::on_start_connect_btn_clicked()
{
    //监听端口
    tcp_server->listen(QHostAddress::Any,ui->port_edit->text().toUInt());
}

void tcpserverForm::after_listen_get_new_connect()
{
    //监听到新连接之后记录socket
    tcp_server_socket = tcp_server->nextPendingConnection();
    //获得可读信号
    connect(tcp_server_socket,&QTcpSocket::readyRead,this,&tcpserverForm::listen_get_msg_read_show);
    QHostAddress addr = tcp_server_socket->peerAddress();
    QString addr_buff = addr.toString();

    QString ip_addr_temp =  addr_buff;
    QString ip_addr;
    int i = 0;
    //填充ip地址
    for(i = 7; ip_addr_temp[i] != '\0'; i ++ )
    {
        ip_addr[i-7] = ip_addr_temp[i];
     }

    qDebug() << addr_buff;
    QMessageBox::information(this,"新连接",ip_addr);
}

void tcpserverForm::listen_get_msg_read_show()
{
    //读取数据
    QString buf = tcp_server_socket->readAll();
    ui->receive_edit->setPlainText(buf);

}

void tcpserverForm::on_end_connect_btn_clicked()
{
    //结束连接
    tcp_server_socket->close();
}

void tcpserverForm::on_send_msg_btn_clicked()
{
    //发送数据
    tcp_server_socket->write(ui->send_edit->toPlainText().toLocal8Bit().data());
}
