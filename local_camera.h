#ifndef LOCAL_CAMERA_H
#define LOCAL_CAMERA_H

#include <QWidget>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraImageCapture>

namespace Ui {
class local_camera;
}

class local_camera : public QWidget
{
    Q_OBJECT

public:
    explicit local_camera(QWidget *parent = nullptr);
    ~local_camera();

    QCamera *camera_chosen;
    QCameraImageCapture *imageCapture;

private slots:
    void on_takephoto_btn_clicked();

    void on_goback_menu_clicked();

private:
    Ui::local_camera *ui;
};

#endif // LOCAL_CAMERA_H
