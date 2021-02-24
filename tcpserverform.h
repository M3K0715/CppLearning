#ifndef TCPSERVERFORM_H
#define TCPSERVERFORM_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class tcpserverForm;
}

class tcpserverForm : public QWidget
{
    Q_OBJECT

public:
    explicit tcpserverForm(QWidget *parent = nullptr);
    ~tcpserverForm();

    QTcpSocket *tcp_server_socket;
    QTcpServer *tcp_server;

private slots:
    void on_start_connect_btn_clicked();

    void after_listen_get_new_connect();

    void listen_get_msg_read_show();

    void on_end_connect_btn_clicked();

    void on_send_msg_btn_clicked();

private:
    Ui::tcpserverForm *ui;
};

#endif // TCPSERVERFORM_H
