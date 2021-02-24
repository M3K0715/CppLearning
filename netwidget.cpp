#include "netwidget.h"
#include "ui_netwidget.h"
#include <mainwidget.h>
#include "camera_widget.h"
#include "uart_widget.h"
#include "tcpclientform.h"
#include "tcpserverform.h"
#include "udp_mode.h"

netwidget::netwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::netwidget)
{
    ui->setupUi(this);

    setWindowTitle(QObject::tr("Choose Net model:"));
}

netwidget::~netwidget()
{
    delete ui;
}

void netwidget::on_goto_menu_btn_clicked()
{
    close();
    MainWidget *mainwidows = new MainWidget;
    mainwidows->show();

}

void netwidget::on_exit_clicked()
{
    close();
}

void netwidget::on_goto_camera_clicked()
{
    camera_widget *camera = new camera_widget();
    camera->show();
}

void netwidget::on_goto_uart_clicked()
{
    uart_widget *uartwidget = new uart_widget;
    uartwidget->show();
}

void netwidget::on_work_as_client_clicked()
{
    tcpclientForm *client_windows = new tcpclientForm;
    client_windows->show();
}

void netwidget::on_work_as_server_clicked()
{
    tcpserverForm *server_windows = new tcpserverForm;
    server_windows->show();
}

void netwidget::on_UDP_mode_clicked()
{
    udp_mode *udp = new udp_mode;
    udp->show();
}
