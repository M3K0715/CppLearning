#ifndef UDP_MODE_H
#define UDP_MODE_H

#include <QWidget>
#include <QUdpSocket>

namespace Ui {
class udp_mode;
}

class udp_mode : public QWidget
{
    Q_OBJECT

public:
    explicit udp_mode(QWidget *parent = nullptr);
    ~udp_mode();

    QUdpSocket *udpsocket;

private slots:
    void on_start_connect_btn_clicked();

    void on_end_connect_btn_clicked();

    void on_send_msg_btn_clicked();

    void conneted_wait_for_msg();

private:
    Ui::udp_mode *ui;
};

#endif // UDP_MODE_H
