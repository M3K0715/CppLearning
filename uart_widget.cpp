#include "uart_widget.h"
#include "ui_uart_widget.h"
#include "mainwidget.h"
#include <QSerialPortInfo>
#include <QtSerialPort>
#include <QMessageBox>
#include <QString>
#include "camera_widget.h"
#include "netwidget.h"

/*本页面的构造函数 */
uart_widget::uart_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::uart_widget)
{
    ui->setupUi(this);                      //先构建一个QWidget界面，再加载xml构建出我们创建的ui界面。

    setWindowTitle(QObject::tr("UART Connect:"));

    QStringList serialNamePort;             //一个string类的list 存放搜索到串口的名字
    serilaPort = new QSerialPort(this);     //新建一个串口

    //连接函数用于输入接收
    connect(serilaPort,&QSerialPort::readyRead ,
            this,&uart_widget::serial_port_ready_to_read );

    //找到每一个串口并且记录到serialNamePort
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        serialNamePort << info.portName();
    }
    ui->series_num->addItems(serialNamePort);//输出到下拉菜单中
}

uart_widget::~uart_widget()
{
    delete ui;
}


void uart_widget::on_goto_menu_btn_clicked()
{
    close();
    MainWidget *mainwidows = new MainWidget;
    mainwidows->show();
}

void uart_widget::on_exit_clicked()
{
    close();
}

void uart_widget::on_open_ser_btn_clicked()
{
    //默认设置
    QSerialPort::BaudRate baudRate = QSerialPort::Baud115200;
    QSerialPort::DataBits databits = QSerialPort::Data8;
    QSerialPort::StopBits stopbits = QSerialPort::OneStop;
    QSerialPort::Parity paritybits = QSerialPort::NoParity;

    /*                  *
     * 下拉菜单的选项选择  *
     *                  */

    if(ui->baud_rate->currentText() == "4800")
    {
        baudRate = QSerialPort::Baud4800;
    }else if(ui->baud_rate->currentText() == "9600")
    {
        baudRate = QSerialPort::Baud9600;
    }else if(ui->baud_rate->currentText() == "115200")
    {
        baudRate = QSerialPort::Baud115200;
    }

    if(ui->data_bit->currentText() == "5"){
        databits = QSerialPort::Data5;
    }else if (ui->data_bit->currentText() == "6") {
        databits = QSerialPort::Data6;
    }else if (ui->data_bit->currentText() == "7") {
        databits = QSerialPort::Data7;
    }else if (ui->data_bit->currentText() == "8") {
        databits = QSerialPort::Data8;
    }

    if(ui->stop_bit->currentText() == "1"){
        stopbits = QSerialPort::OneStop;
    }else if (ui->stop_bit->currentText() == "2") {
        stopbits = QSerialPort::TwoStop;
    }else if (ui->stop_bit->currentText() == "1.5") {
        stopbits = QSerialPort::OneAndHalfStop;
    }

    if(ui->parity_bit->currentText() == "none")
    {
        paritybits = QSerialPort::NoParity;
    }else if (ui->parity_bit->currentText() == "even") {
        paritybits = QSerialPort::EvenParity;
    }else if (ui->parity_bit->currentText() == "odd") {
        paritybits = QSerialPort::OddParity;
    }

    //设置参数
    serilaPort->setPortName(ui->series_num->currentText());
    serilaPort->setBaudRate(baudRate);
    serilaPort->setDataBits(databits);
    serilaPort->setParity(paritybits);
    serilaPort->setStopBits(stopbits);
    serilaPort->setFlowControl(QSerialPort::NoFlowControl);

    //打开串口
    if(serilaPort->open(QIODevice::ReadWrite) == true)
    {
        QMessageBox::information(this,"information","success");
    }else
    {
        QMessageBox::critical(this,"information","error");
    }


}

void uart_widget::on_close_ser_btn_clicked()
{
    serilaPort->close();
}

//读串口
void uart_widget::serial_port_ready_to_read()
{
    QString recv_buf = QString(serilaPort->readAll());



    QByteArray  byte = recv_buf.toUtf8();

/*
    qDebug() << "Change start";
    QString::size_type size = recv_buf.size();
    for (QString::size_type i = 0;i != recv_buf.size();i++)
    {
       qDebug() << int(byte.at(i));
       byte.toHex();
    }
    qDebug() << recv_buf.toUtf8() <<  "Change over";
*/
    ui->reveive_msg_edit->appendPlainText(recv_buf);    //显示读出值

}

void uart_widget::on_sendmsg_ser_btn_clicked()
{
    serilaPort->write(ui->send_msg_edit->text().toLocal8Bit().data());
    char c = '\n';                  //自动输入回车
    serilaPort->write(&c,1);
    ui->send_msg_edit->clear();     //清理输出框的值
}

void uart_widget::on_clear_msg_btn_clicked()
{
    ui->send_msg_edit->clear();
    ui->reveive_msg_edit->clear();
}

void uart_widget::on_goto_camera_clicked()
{
    camera_widget *camera = new camera_widget();
    camera->show();
}

void uart_widget::on_goto_net_clicked()
{
    netwidget *net = new netwidget();
    net->show();
}
