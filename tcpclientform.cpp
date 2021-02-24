#include "tcpclientform.h"
#include "ui_tcpclientform.h"
#include <QMessageBox>

tcpclientForm::tcpclientForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tcpclientForm)
{
    ui->setupUi(this);
    setWindowTitle(QObject::tr("TCP Client"));

    tcp_client_socket = new QTcpSocket(this);
    //连接建立成功会有conneted信号
    connect(tcp_client_socket,&QTcpSocket::connected,this,&tcpclientForm::after_start_btn_connect_success);
    //连接成功等待信号传入
    connect(tcp_client_socket,&QTcpSocket::readyRead,this,&tcpclientForm::connected_then_get_msg_show);

}

tcpclientForm::~tcpclientForm()
{
    delete ui;
}

void tcpclientForm::after_start_btn_connect_success()
{
    //获得connected信号，连接成功
    QMessageBox::information(this,"状态","连接成功");

}

void tcpclientForm::connected_then_get_msg_show()
{
    //读数据

    QString buf = tcp_client_socket->readAll();
    ui->receive_msg_edit->setPlainText(buf);

    /*
     * 字符转换
        qDebug() << "Change start";
        QString::size_type size = recv_buf.size();
        for (QString::size_type i = 0;i != recv_buf.size();i++)
        {
           qDebug() << int(byte.at(i));
           byte.toHex();
        }
        qDebug() << recv_buf.toUtf8() <<  "Change over";
    */
}

void tcpclientForm::on_start_connect_btn_clicked()
{
    //根据ip和port建立连接
    tcp_client_socket->connectToHost(ui->ipaddress_edit->text(),ui->port_edit->text().toUInt());

}

void tcpclientForm::on_send_msg_btn_clicked()
{
    //发送信息
    tcp_client_socket->write(ui->sen_msg_edit->toPlainText().toLocal8Bit().data());
    ui->sen_msg_edit->clear();
}

void tcpclientForm::on_end_connect_btn_clicked()
{
    tcp_client_socket->close();
}
