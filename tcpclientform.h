#ifndef TCPCLIENTFORM_H
#define TCPCLIENTFORM_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class tcpclientForm;
}

class tcpclientForm : public QWidget
{
    Q_OBJECT

public:
    explicit tcpclientForm(QWidget *parent = nullptr);
    ~tcpclientForm();

    QTcpSocket *tcp_client_socket;

private slots:
    void after_start_btn_connect_success();

    void connected_then_get_msg_show();

    void on_start_connect_btn_clicked();

    void on_send_msg_btn_clicked();

    void on_end_connect_btn_clicked();

private:
    Ui::tcpclientForm *ui;
};

#endif // TCPCLIENTFORM_H
