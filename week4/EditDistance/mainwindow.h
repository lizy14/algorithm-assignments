#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QString>
#include "EditDistance.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QStandardItemModel *model;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_checkBox_clicked(bool checked);

    void on__a_textChanged(const QString&){if(autoUpdate)update();}
    void on__b_textChanged(const QString&){if(autoUpdate)update();}
    void on__0_valueChanged(const QString&){if(autoUpdate)update();}
    void on__1_valueChanged(const QString&){if(autoUpdate)update();}
    void on__2_valueChanged(const QString&){if(autoUpdate)update();}
    void on__3_valueChanged(const QString&){if(autoUpdate)update();}
    void on__4_valueChanged(const QString&){if(autoUpdate)update();}
    void on__5_valueChanged(const QString&){if(autoUpdate)update();}
private:
    Ui::MainWindow *ui;
    void update();
    bool autoUpdate;
};

#endif // MAINWINDOW_H
