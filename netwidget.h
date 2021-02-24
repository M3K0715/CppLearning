#ifndef NETWIDGET_H
#define NETWIDGET_H

#include <QWidget>

namespace Ui {
class netwidget;
}

class netwidget : public QWidget
{
    Q_OBJECT

public:
    explicit netwidget(QWidget *parent = nullptr);
    ~netwidget();

private slots:
    void on_goto_menu_btn_clicked();

    void on_exit_clicked();

    void on_goto_camera_clicked();

    void on_goto_uart_clicked();

    void on_work_as_client_clicked();

    void on_work_as_server_clicked();

    void on_UDP_mode_clicked();

private:
    Ui::netwidget *ui;
};

#endif // NETWIDGET_H
