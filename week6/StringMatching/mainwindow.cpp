#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "", tr("Text Files (*.txt)"));
    qDebug() << fileName;


    text = QString();
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
        qDebug() << "Can not open";
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        text += line;
    }
    ui->textBrowser->setText(text.left(2000));
    ui->label_2->setText(QString());
}

void MainWindow::on_pushButton_2_clicked()
{

    pattern = ui->lineEdit->text();
    //text = ui->textBrowser->toPlainText();

    int m = text.length();
    char *a = (char*)malloc((m+10) * sizeof(char));
    if(!a)
        qDebug() << "malloc failed";

    strcpy(a, text.toStdString().c_str());


    int n = pattern.length();
    char *b = (char*)malloc((n+10) * sizeof(char));
    if(!b)
        qDebug() << "malloc failed";
    strcpy(b, pattern.toStdString().c_str());


    matcher matchers[] = { BM, KMP, BF };
    const char* names[] = { "BM", "KMP", "BF" };

    result rs[3];

    res = QString();
    for (auto i = 0u; i < 3/*MAGIC*/; i++) {
        result r;
        double time = 0;
        int times = 0;



        while (1) {
            Timing timer;
            timer.setDivisor(1);
            timer.start();
            r = matchers[i](b, n, a, m);
            timer.end();
            times += 1;
            time += timer.getCPUtime();
            auto __ = r.size();
            if(__==5){
                r = matchers[i](b, n, a, m);
            }
            cout << r.size() << endl;
            if (time > 100000) {
                time /= times;
                rs[i] = r;
                break;
            }
        }

        res += names[i] + QString(": ");
        res += QString::number(time);
        res += " us; ";
    }

    QApplication::clipboard()->setText(res);
    res = QString("Running time: ") + res;
    ui->label_4->setText(res);
    res = QString("Text length ") +  QString::number(m) + QString(", pattern length ") + QString::number(n) + QString(". Total of ") + QString::number(rs[0].size()) + QString(" occurrence(s) found. ");
    if(rs[0].size() == rs[1].size() && rs[0].size() == rs[2].size())
        res += QString("Results consistent.");
    ui->label_2->setText(res);


    QString res_;
    for(auto i : rs[0]){
     res_ += QString::number(i) + QString(", ");
    }

    ui->label_2->setText(res);
    ui->textEdit->setText(res_);



    int __ = 2000;
    QString resultHtml = text.left(__);
    resultHtml = resultHtml.replace(QString('\n'),QString("<br/>"));
    resultHtml = resultHtml.replace(pattern, QString("<font color=\"red\">") + pattern + QString("</font>"));
    ui->textBrowser->setHtml(resultHtml + QString("..."));


    /*
    r.push_back(-1);
    QString resultHtml = text.left(r[0]);
    for(int i=0; i<r.size()-1; i++){
        resultHtml += QString("<font color=\"red\">") + pattern + QString("</font>") + text.midRef(r[i]+n, r[i+1]-r[i]-n+1).toString();
    }

    resultHtml = resultHtml.replace(QString('\n'),QString("<br/>"));
    ui->textBrowser->setHtml(resultHtml);

    */
    //free(a);
    //free(b);
}

