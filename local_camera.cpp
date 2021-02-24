#include "local_camera.h"
#include "ui_local_camera.h"
#include "mainwidget.h"

#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QCameraImageCapture>

#include <QFileDialog>
#include <QDebug>

local_camera::local_camera(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::local_camera)
{
    ui->setupUi(this);
    //获取可使用的摄像头
    QList<QCameraInfo> aviable_camera = QCameraInfo::availableCameras();  
    //选中摄像头
    camera_chosen = new QCamera(aviable_camera.at(0),this);
    //设为从摄像头中采集图片
    imageCapture = new QCameraImageCapture(camera_chosen);
    //设置摄像头显示器
    camera_chosen->setViewfinder(ui->camera_windows);

    camera_chosen->start();

}

local_camera::~local_camera()
{
    camera_chosen->stop();
    ui->camera_windows->close();
    delete ui;

}

void local_camera::on_takephoto_btn_clicked()
{

    //进入截图模式
    camera_chosen->setCaptureMode(QCamera::CaptureStillImage);
    //如果曝光和白平衡模式不是手动模式，那么就要使用请求的锁来锁定相机设置
    camera_chosen->searchAndLock();

    // 必须使用绝对路径
    QString fileName = QFileDialog::getSaveFileName();
    //保存图片
    imageCapture->capture(fileName);
    camera_chosen->unlock();

}

void local_camera::on_goback_menu_clicked()
{
    camera_chosen->stop();
    close();
    MainWidget *mainwidows = new MainWidget;
    mainwidows->show();
}



