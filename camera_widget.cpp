#include "camera_widget.h"
#include "ui_camera_widget.h"
#include "mainwidget.h"
#include "netwidget.h"
#include "uart_widget.h"
#include "local_camera.h"
#include "opencv_local_camera.h"

camera_widget::camera_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::camera_widget)
{
    ui->setupUi(this);

    setWindowTitle(QObject::tr("Camera Model:"));
}

camera_widget::~camera_widget()
{
    delete ui;
}

void camera_widget::on_goto_menu_btn_clicked()
{
    close();
    MainWidget *mainwidows = new MainWidget;
    mainwidows->show();
}

void camera_widget::on_exit_clicked()
{
    close();
}

void camera_widget::on_goto_net_clicked()
{
    close();
    netwidget *net = new netwidget();
    net->show();
}

void camera_widget::on_goto_uart_clicked()
{
    close();
    uart_widget *uartwidget = new uart_widget;
    uartwidget->show();
}

void camera_widget::on_open_local_camera_clicked()
{
    close();
    local_camera *camera_windows = new local_camera;
    camera_windows->show();
}

void camera_widget::on_Opencv_local_camera_clicked()
{
    //close()此处关闭会造成系统不稳定
    opencv_local_camera *opencv_camera = new opencv_local_camera();
    opencv_camera->show();
    close();

}
