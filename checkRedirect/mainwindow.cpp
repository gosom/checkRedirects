#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include "crawler.h"
#include "myurl.h"
#include <QMessageBox>
#include <QFile>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    crawler = new Crawler(this);
    connect(this, SIGNAL(start_crawling()),
            crawler, SLOT(start_crawl()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoad_csv_triggered()
{
    QString fname = QFileDialog::getOpenFileName(this, "Select csv file", "",
                                                 "*.txt *.csv");
    int num_loaded = 0;
    QString msg;
    if(!fname.isNull()){
        num_loaded = crawler->load_from_file(fname);
        if(num_loaded > 0)
            msg = QString("Loaded %1 urls").arg(num_loaded);
        else
            msg = QString("0 urls were loaded");
        QMessageBox::information(this, "Urls loaded", msg);
        if(num_loaded > 0)
            emit start_crawling();
    }else{
        QMessageBox::warning(this, "Error", "Cannot open file");
    }

}

void MainWindow::on_crawling_finished(){
    QString fname = QFileDialog::getSaveFileName(this, "Save results", "", "");
    QFile f(fname);
    if(!f.open(QIODevice::WriteOnly|QIODevice::Text)){
        QMessageBox::warning(this, "Error", "Cannot open file");
    }else{
        QTextStream out(&f);
        crawler->write_results(out);
        QDesktopServices::openUrl(QUrl("file:///" + fname));
    }
}
