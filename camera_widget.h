#ifndef CAMERA_WIDGET_H
#define CAMERA_WIDGET_H

#include <QWidget>

namespace Ui {
class camera_widget;
}

class camera_widget : public QWidget
{
    Q_OBJECT

public:
    explicit camera_widget(QWidget *parent = nullptr);
    ~camera_widget();

private slots:
    void on_goto_menu_btn_clicked();

    void on_exit_clicked();

    void on_goto_net_clicked();

    void on_goto_uart_clicked();

    void on_open_local_camera_clicked();

    void on_Opencv_local_camera_clicked();

private:
    Ui::camera_widget *ui;
};

#endif // CAMERA_WIDGET_H
