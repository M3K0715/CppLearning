#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:

    void on_relog_btn_clicked();

    void on_camera_clicked();

    void on_net_btn_clicked();

    void on_uart_btn_clicked();

    void on_exit_btn_clicked();

private:
    Ui::MainWidget *ui;
};
#endif // MAINWIDGET_H
