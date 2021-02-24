#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "enterdialog.h"
#include "camera_widget.h"
#include "netwidget.h"
#include "uart_widget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    setWindowTitle(QObject::tr("Choose Model:"));
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_relog_btn_clicked()
{
    close();
    EnterDialog enter;
    enter.exec();
}

void MainWidget::on_camera_clicked()
{
    close();
    camera_widget *camera_widows = new camera_widget;
    camera_widows->show();
}

void MainWidget::on_net_btn_clicked()
{
    close();
    netwidget *net_widows = new netwidget;
    net_widows->show();
}


void MainWidget::on_uart_btn_clicked()
{
    close();
    uart_widget *uart_windows = new uart_widget;
    uart_windows->show();
}

void MainWidget::on_exit_btn_clicked()
{
    close();
}
