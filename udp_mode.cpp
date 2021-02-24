#include "udp_mode.h"
#include "ui_udp_mode.h"
#include <QString>
#include <QMessageBox>
#include <QHostAddress>

udp_mode::udp_mode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::udp_mode)
{
    ui->setupUi(this);

    udpsocket = new QUdpSocket(this);

}

udp_mode::~udp_mode()
{
    delete ui;
}
void udp_mode::conneted_wait_for_msg()
{
    while (udpsocket->hasPendingDatagrams())
    {
        QByteArray array;
        array.resize(udpsocket->pendingDatagramSize());
        udpsocket->readDatagram(array.data(),array.size());

        QString buf ;
        buf = array;
        ui->receive_edit->setPlainText(buf);

    }
}

void udp_mode::on_start_connect_btn_clicked()
{
    //绑定端口并返回状态
    if(udpsocket->bind(ui->local_port_edit->text().toUInt()) == true)
    {
        QMessageBox::information(this,"information","connect success");
    }else
    {
        QMessageBox::critical(this,"information","connect fail");
    }

    //读接收状态,若有信息则调用处理函数
    connect(udpsocket, &QUdpSocket::readyRead,this, &udp_mode::conneted_wait_for_msg);
}

void udp_mode::on_end_connect_btn_clicked()
{
    udpsocket->close();
}


void udp_mode::on_send_msg_btn_clicked()
{
    quint16 port;
    QString buf;
    QHostAddress add;

    //设置目标ip地址
    add.setAddress(ui->dest_address_edit->text());
    //获得发送字符串
    buf = ui->send_edit->toPlainText();
    //获得端口号
    port = ui->dest_port_edit->text().toUInt();
    //发送数据
    udpsocket->writeDatagram(buf.toLocal8Bit().data(),buf.length(),add,port);

}
