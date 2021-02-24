#include "enterdialog.h"
#include "ui_enterdialog.h"
#include "mainwidget.h"
#include <QString>

EnterDialog::EnterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnterDialog)
{
    ui->setupUi(this);
    setWindowTitle(QObject::tr("Welcome!"));
}

EnterDialog::~EnterDialog()
{
    delete ui;
}

void EnterDialog::on_pushButton_2_clicked()
{
    close();
}

void EnterDialog::on_log_btn_clicked()
{
    QString name = ui->name_entered->text();
    QString password = ui->password_entered->text();
    if(name == "123" && password =="123")
    {
        close();
        MainWidget *w = new MainWidget;
        w->show();
    }
    else {
        close();
        MainWidget *w = new MainWidget;
        w->show();
    }
}
