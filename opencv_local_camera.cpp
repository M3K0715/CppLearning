#include "opencv_local_camera.h"
#include "ui_opencv_local_camera.h"
#include "mainwidget.h"
#include <QMessageBox>
#define EYE_CHECK  0
#define SEND_MSG   0


opencv_local_camera::opencv_local_camera(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::opencv_local_camera)
{
    ui->setupUi(this);
    timer = new QTimer(this);

    count = 0;

    connect(timer,&QTimer::timeout,this,&opencv_local_camera::timer_handler);

    connect(this,&opencv_local_camera::report_face,this,&opencv_local_camera::report_face_handler);

    modelPCA = face::EigenFaceRecognizer::create();
    modelPCA->read("C:\\Qt\\PROJECT\\build-untitled22-Desktop_Qt_5_12_8_MinGW_32_bit-Debug\\MyFacePCAModel.xml");//加载分类器

    if (!face_cascade.load("C:\\Qt\\PROJECT\\haarcascade_frontalface_alt2.xml"))
    {
        qDebug("Load haarcascade_frontalface_alt failed!");
        return;
    }


    if (!eye_Classifier.load("C:\\Qt\\PROJECT\\haarcascade_eye.xml"))  //需要将xml文档放在自己指定的路径下
    {
        qDebug("Load haarcascade_eye.xml failed!");
        return;
    }

}

opencv_local_camera::~opencv_local_camera()
{
    delete ui;
}

void opencv_local_camera::on_open_camera_clicked()
{
    capture.open(0);

    if(!capture.isOpened())
    {
        QMessageBox::critical(this, tr("ERROR"),tr("打开摄像头失败.\n"));
        qDebug() << "Open camera error" << endl;
    }

    capture >> cap;
    if (!cap.empty()) //判断当前帧是否捕捉成功 **这步很重要
    {
        imag = Mat2QImage(cap);
        imag = imag.scaled(ui->collect_area->width(), ui->collect_area->height(),
                                                Qt::IgnoreAspectRatio, Qt::SmoothTransformation);//设置图片大小和label的长宽一致

        //imshow("name", cap); //若当前帧捕捉成功，显示
        ui->collect_area->setPixmap(QPixmap::fromImage(imag));  // 将图片显示到label上
     }

     //waitKey(TIMING_MS);

     timer->start(TIMING_MS);


}

void opencv_local_camera::on_goto_menu_clicked()
{
    close();
    MainWidget *mainwidows = new MainWidget;
    mainwidows->show();
}

void opencv_local_camera::on_exit_btn_clicked()
{
    close();
}

void opencv_local_camera::timer_handler()
{

    capture >> cap;
    if (!cap.empty()) //判断当前帧是否捕捉成功 **这步很重要
    {
        cvtColor(cap, cap_gray, CV_BGR2GRAY);   //转为灰度图

        equalizeHist(cap_gray, cap_gray);       //直方图均衡化，增加对比度方便处理

        //检测关于脸部位置
        face_cascade.detectMultiScale(cap_gray, faceRect, 1.1, 3,
                 0 | CASCADE_DO_ROUGH_SEARCH |CASCADE_DO_CANNY_PRUNING |CASCADE_FIND_BIGGEST_OBJECT, Size(50, 50));//检测

        for (size_t i = 0; i < faceRect.size(); i++)
        {
            rectangle(cap, faceRect[i], Scalar(0, 255, 0));      //用绿色矩形画出检测到的位置

            Mat faceROI = cap_gray(faceRect[i]);
#if EYE_CHECK
            int eye_num=0;
            eye_Classifier.detectMultiScale(faceROI, eyeRect, 1.1, 1, 0 | CASCADE_DO_ROUGH_SEARCH, Size(30, 30));//检测
            for (size_t j = 0; j < eyeRect.size(); j++)
            {
                Rect rect(faceRect[i].x + eyeRect[j].x, faceRect[i].y + eyeRect[j].y, eyeRect[j].width, eyeRect[j].height);
                rectangle(cap, rect, Scalar(255, 0, 255));   //用蓝色矩形画出检测到的位置
                eye_num++;
                if(eye_num==2)
                    break;
            }
#endif
            int predictPCA = 0;
            Mat face_test;
            Point text_lb;
            // 不加前面的cv::的话resize()方法会和MainWindow中的resize()冲突。
            cv::resize(faceROI,face_test,Size(92, 112));

            //可添加label显示灰度图
            // imshow("frame", face_test);
            // 测试图像应该是灰度图


            predictPCA = modelPCA->predict(face_test);

            face_num = predictPCA;



#if SEND_MSG
            qDebug() << "Send msg Face is found\n";
            emit find_face();


            if(predictPCA==0)  // 这个3也就是上面labels.push_back(3);和图片是一一对应的
            {
                string name = "face_no_no_matchable_face";  // 文本提示
                text_lb = Point(faceRect[i].x, faceRect[i].y);
                putText(cap, name, text_lb, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));
            }

            if(predictPCA==1)  // 这个3也就是上面labels.push_back(3);和图片是一一对应的
            {
                string name = "face_2";  // 文本提示
                text_lb = Point(faceRect[i].x, faceRect[i].y);
                putText(cap, name, text_lb, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));
            }

            if(predictPCA==2)  // 这个3也就是上面labels.push_back(3);和图片是一一对应的
            {
                string name = "face_3";  // 文本提示
                text_lb = Point(faceRect[i].x, faceRect[i].y);
                putText(cap, name, text_lb, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));
            }

            if(predictPCA==3)  // 这个3也就是上面labels.push_back(3);和图片是一一对应的
            {
                string name = "face_gmd";  // 文本提示
                text_lb = Point(faceRect[i].x, faceRect[i].y);
                putText(cap, name, text_lb, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));
            }
#endif
        }
     }
    imag = Mat2QImage(cap);

    imag = imag.scaled(ui->collect_area->width(), ui->collect_area->height(),
                                            Qt::IgnoreAspectRatio, Qt::SmoothTransformation);//设置图片大小和label的长宽一致

    //imshow("name", cap); //若当前帧捕捉成功，显示
    ui->collect_area->setPixmap(QPixmap::fromImage(imag));  // 将图片显示到label上
}

//mat转换成image格式的图像
QImage  opencv_local_camera::Mat2QImage(Mat cvImg)
{
    Mat temp = cvImg;
    QImage qImg;
    if(temp.channels()==3)     //3 channels color image
    {

        cv::cvtColor(temp,temp,COLOR_BGR2RGB);
        qImg =QImage((const unsigned char*)(temp.data),
                    temp.cols, temp.rows,
                    temp.cols*temp.channels(),
                    QImage::Format_RGB888);
    }
    else if(temp.channels()==1)                    //grayscale image
    {
        qImg =QImage((const unsigned char*)(temp.data),
                    temp.cols,temp.rows,
                    temp.cols*temp.channels(),
                    QImage::Format_Indexed8);
    }
    else
    {
        qImg =QImage((const unsigned char*)(temp.data),
                    temp.cols,temp.rows,
                    temp.cols*temp.channels(),
                    QImage::Format_RGB888);
    }
    return qImg;
}


void opencv_local_camera::on_capture_image_clicked()
{
    capture>>cap; //读取当前帧
    if (!cap.empty()) //判断当前帧是否捕捉成功 **这步很重要
    {

        imag = imag.scaled(ui->capture_area->width(), ui->capture_area->height(),
                                            Qt::IgnoreAspectRatio, Qt::SmoothTransformation);//设置图片大小和label的长宽一致

        //imshow(name, cap); //若当前帧捕捉成功，显示
        ui->capture_area->setPixmap(QPixmap::fromImage(imag));  // 将图片显示到label上
    }
    else
        qDebug("can not capture image\n");


    Mat dst;

    cv::resize(cap, dst, Size(92, 112));//改变大小为标准大小，输出到dst中
    cvtColor(dst,dst,COLOR_BGR2RGB);    //转换图片格式
    imwrite(format("C://Qt//PROJECT//orl_faces//s42//%d.jpg", count), dst);
#if 0
    QMessageBox::information(this, tr("Store"),tr("Finish"));
    qDebug("Stored image finished!\n");
#endif
    count++;
}

void opencv_local_camera::on_close_camera_clicked()
{
    timer->stop();         // 停止读取数据。
    capture.release();      //关闭摄像头
}

void opencv_local_camera::on_train_module_clicked()
{

    vector<Mat> images;
    Mat img;
    String location = "C:\\Qt\\PROJECT\\orl_faces\\s01\\1.pgm";

    for (unsigned int i = 0; i < location.size() ;i++)
    {
        qDebug() << i << location[i] << endl;
    }

    for (int s = 1; s <= C_PEOPLE_NUM;s++)
    {


        for (int s_0x = 1; s_0x <= 9;s_0x++)
        {
           qDebug() << s << s_0x << location[24]<<location[25]<<location[26]<<location[27]<<location[28]<<endl;
            img = imread(location, IMREAD_GRAYSCALE);
            images.push_back(img);                                          // 将图片 添加到images中
            location[28]++;
        }
        location[28] = '1';
        location[26]++;

    }


#if 1
    img = imread("C:\\Qt\\PROJECT\\orl_faces\\s41\\1.jpg", IMREAD_GRAYSCALE);
    images.push_back(img);                                          // 将图片 添加到images中
    img = imread("C:\\Qt\\PROJECT\\orl_faces\\s41\\2.jpg", IMREAD_GRAYSCALE);
    images.push_back(img);                                          // 将图片 添加到images中
    img = imread("C:\\Qt\\PROJECT\\orl_faces\\s41\\3.jpg", IMREAD_GRAYSCALE);
    images.push_back(img);                                          // 将图片 添加到images中
    img = imread("C:\\Qt\\PROJECT\\orl_faces\\s41\\4.jpg", IMREAD_GRAYSCALE);
    images.push_back(img);                                          // 将图片 添加到images中
    img = imread("C:\\Qt\\PROJECT\\orl_faces\\s41\\5.jpg", IMREAD_GRAYSCALE);
    images.push_back(img);                                          // 将图片 添加到images中
    img = imread("C:\\Qt\\PROJECT\\orl_faces\\s41\\6.jpg", IMREAD_GRAYSCALE);
    images.push_back(img);                                          // 将图片 添加到images中
    img = imread("C:\\Qt\\PROJECT\\orl_faces\\s41\\7.jpg", IMREAD_GRAYSCALE);
    images.push_back(img);                                          // 将图片 添加到images中
    img = imread("C:\\Qt\\PROJECT\\orl_faces\\s41\\8.jpg", IMREAD_GRAYSCALE);
    images.push_back(img);                                          // 将图片 添加到images中
    img = imread("C:\\Qt\\PROJECT\\orl_faces\\s41\\9.jpg", IMREAD_GRAYSCALE);
    images.push_back(img);                                          // 将图片 添加到images中

#endif

    vector<int> labels;

#if 1
    for (int num_of_people = 0;num_of_people < C_PEOPLE_NUM + 1;num_of_people++)
    {
        for (int num_of_pic = 1;num_of_pic <= 9; num_of_pic++)
        {
            labels.push_back(num_of_people);
        }
    }
#endif

    model = face::EigenFaceRecognizer::create();
    model->train(images, labels);
    model->save("MyFacePCAModel.xml");

    QMessageBox::information(this, tr("Train"),tr("Finished"));
    qDebug()<< "train finish\n";
}

void opencv_local_camera::on_identify_image_clicked()
{
    Point text_lb;


    Mat faceROI = cap_gray(faceRect[0]);

    int eye_num=0;
    eye_Classifier.detectMultiScale(faceROI, eyeRect, 1.1, 1, 0 | CASCADE_DO_ROUGH_SEARCH, Size(30, 30));//检测
    for (size_t j = 0; j < eyeRect.size(); j++)
    {
        Rect rect(faceRect[0].x + eyeRect[j].x, faceRect[0].y + eyeRect[j].y, eyeRect[j].width, eyeRect[j].height);
        rectangle(cap, rect, Scalar(255, 0, 255));   //用蓝色矩形画出检测到的位置
        eye_num++;
        if(eye_num==2)
            break;
    }

    if(face_num==0)  // 这个3也就是上面labels.push_back(3);和图片是一一对应的
    {
        string name = "face_no_no_matchable_face";  // 文本提示
        text_lb = Point(faceRect[0].x, faceRect[0].y);
        putText(cap, name, text_lb, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));
    }

    if(face_num==1)  // 这个3也就是上面labels.push_back(3);和图片是一一对应的
    {
        string name = "face_2";  // 文本提示
        text_lb = Point(faceRect[0].x, faceRect[0].y);
        putText(cap, name, text_lb, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));
    }

    if(face_num==2)  // 这个3也就是上面labels.push_back(3);和图片是一一对应的
    {
        string name = "face_3";  // 文本提示
        text_lb = Point(faceRect[0].x, faceRect[0].y);
        putText(cap, name, text_lb, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));
    }

    if(face_num==3)  // 这个3也就是上面labels.push_back(3);和图片是一一对应的
    {
        string name = "face_gmd";  // 文本提示
        text_lb = Point(faceRect[0].x, faceRect[0].y);
        putText(cap, name, text_lb, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));
    }

    imag_identify = Mat2QImage(cap);

    imag_identify = imag_identify.scaled(ui->capture_area->width(), ui->capture_area->height(),
                                            Qt::IgnoreAspectRatio, Qt::SmoothTransformation);//设置图片大小和label的长宽一致

    ui->capture_area->setPixmap(QPixmap::fromImage(imag_identify));  // 将图片显示到label上

    emit report_face();//发信号，进行识别
}

void opencv_local_camera::report_face_handler()
{
    if(face_num != 0)
    {
        QMessageBox msgBox;
        msgBox.resize(640,480);
        msgBox.setText("The face has been identified.");
        QString s = QString::number(face_num, 10);
        s = s + "  Is that U?";
        msgBox.setInformativeText(s);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No );
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();

        switch (ret) {
          case QMessageBox::Yes:
              // Save was clicked
              break;
          case QMessageBox::No:
              // Don't Save was clicked
              break;

          default:
              // should never be reached
              break;
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Warning"),tr("Can't match faces!"),
                                         QMessageBox::Ok , QMessageBox::Ok);
    }
}
