#ifndef OPENCV_LOCAL_CAMERA_H
#define OPENCV_LOCAL_CAMERA_H

#include <QWidget>
#include <QDebug>
#include <QTimer>
#include <QImage>
#include <QWidget>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/face.hpp>
#include <vector>
#include <opencv2/imgproc.hpp>
#include <core.hpp>
#include <opencv2/face/mace.hpp>

#include <QThread>




using namespace cv;
using namespace std;

namespace Ui {
class opencv_local_camera;
}

class opencv_local_camera : public QWidget
{
    Q_OBJECT

public:
    explicit opencv_local_camera(QWidget *parent = nullptr);
    ~opencv_local_camera();

    QImage  Mat2QImage(Mat cvImg);

signals:
    void report_face();

private slots:
    void on_open_camera_clicked();

    void on_goto_menu_clicked();

    void on_exit_btn_clicked();

    void timer_handler();

    void on_capture_image_clicked();

    void on_close_camera_clicked();

    void on_train_module_clicked();

    void on_identify_image_clicked();

    void report_face_handler();

private:
    Ui::opencv_local_camera     *ui;

    const int TIMING_MS     = 10;
    const int C_PEOPLE_NUM  = 3;
    const int C_PIC_NUM     = 9;
    int             count;
    int             face_num = 0;


    QTimer              *timer;
    QImage              imag;
    QImage              imag_identify;
    Mat                 cap;                    //捕捉到的图像
    Mat                 cap_gray,cap_tmp;       //定义一个Mat变量，用于存储每一帧的图像
    VideoCapture        capture;                //声明视频读入类

    CascadeClassifier   eye_Classifier;         //载入眼分类器
    CascadeClassifier   face_cascade;           //载入脸分类器


    //vector 是个类模板 需要提供明确的模板实参 vector<Rect>则是个确定的类 模板的实例化  需要指点std域名才可以用：using namespace std;
    vector<Rect> eyeRect;
    vector<Rect> faceRect;
    vector<Rect> faces;

    Ptr<cv::face::BasicFaceRecognizer> model;
    Ptr<cv::face::BasicFaceRecognizer> modelPCA;
};

#endif // OPENCV_LOCAL_CAMERA_H
