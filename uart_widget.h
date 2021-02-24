#ifndef UART_WIDGET_H
#define UART_WIDGET_H

#include <QWidget>
#include <QSerialPort>

namespace Ui {
class uart_widget;
}

class uart_widget : public QWidget
{
    Q_OBJECT

public:
    explicit uart_widget(QWidget *parent = nullptr);
    ~uart_widget();
    QSerialPort * serilaPort;

private slots:
    void on_goto_menu_btn_clicked();

    void on_exit_clicked();

    void on_open_ser_btn_clicked();

    void on_close_ser_btn_clicked();

    void serial_port_ready_to_read();

    void on_sendmsg_ser_btn_clicked();

    void on_clear_msg_btn_clicked();

    void on_goto_camera_clicked();

    void on_goto_net_clicked();

private:
    Ui::uart_widget *ui;
};

#endif // UART_WIDGET_H
