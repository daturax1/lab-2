#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "logic.h"

#include <cctype>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QFileDialog>
#include <stdio.h>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_loadfile_clicked();

    void on_btn_load_clicked();

    void on_btn_metric_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
