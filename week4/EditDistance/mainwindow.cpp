#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = nullptr;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    //input
    string a = ui->_a->text().toStdString();
    string b = ui->_b->text().toStdString();
    Costs c;
    c[0] = ui->_0->text().toInt();
    c[1] = ui->_1->text().toInt();
    c[2] = ui->_2->text().toInt();
    c[3] = ui->_3->text().toInt();
    c[4] = ui->_4->text().toInt();
    c[5] = ui->_5->text().toInt();
    //end of input


    EditDistance editDistance(a, b, c);
    editDistance.solve();
    auto ops = editDistance.getOperations();
    auto cost = editDistance.getCost();
    //end of calculation

    delete model;
    model = new QStandardItemModel();
    model->setHorizontalHeaderItem(0, new QStandardItem(("Operation")));
    model->setHorizontalHeaderItem(1, new QStandardItem(("Cost")));
    model->setHorizontalHeaderItem(2, new QStandardItem(("i")));
    model->setHorizontalHeaderItem(3, new QStandardItem(("a after the operation")));
    model->setHorizontalHeaderItem(4, new QStandardItem(("j")));
    model->setHorizontalHeaderItem(5, new QStandardItem(("b after the operation")));

    ui->tableView->setModel(model);

    string txt[] = {
        "COPY   ",
        "REPLACE",
        "DELETE ",
        "INSERT ",
        "TWIDDLE",
        "KILL   "
    };
    int j=0, i=0;
    auto _=0u;
    for(; _<ops.size(); _++){
        auto __ = ops[_];
        model->setItem(_, 0, new QStandardItem(QString::fromStdString(txt[__])));
        model->setItem(_, 1, new QStandardItem(QString::number((int)c[__])));
        switch(__){
        case COPY:
            i++, j++;
            break;
        case REPLACE:
            i++, j++;
            break;
        case DELETE:
            i++;
            break;
        case INSERT:
            j++;
            break;
        case TWIDDLE:
            i += 2, j += 2;
            break;
        case KILL:
            j = b.length()+1;
            break;
        }



        model->setItem(_, 2, new QStandardItem(QString::number(i)));
        model->setItem(_, 3, new QStandardItem(QString::fromStdString(a.substr(0, i))));
        model->setItem(_, 4, new QStandardItem(QString::number(j)));
        model->setItem(_, 5, new QStandardItem(QString::fromStdString(b.substr(0, j))));

    }
    model->setItem(_, 0, new QStandardItem(QString("Total")));
    model->setItem(_, 1, new QStandardItem(QString::number(cost)));
    model->setItem(_, 3, new QStandardItem(QString::fromStdString(a)));
    model->setItem(_, 5, new QStandardItem(QString::fromStdString(b)));

    ui->tableView->resizeColumnsToContents();
    //end

}
