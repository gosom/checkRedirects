#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "crawler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionLoad_csv_triggered();
    void on_crawling_finished();

signals:
    void start_crawling();


private:
    Ui::MainWindow *ui;
    Crawler* crawler;
};

#endif // MAINWINDOW_H
