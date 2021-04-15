#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->setWindowTitle("Романова Александра");
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Глобальные переменные */
QStandardItemModel *main_model = new QStandardItemModel;
QStandardItemModel metric_model;

void MainWindow::on_btn_loadfile_clicked() {
    QString file_path = QFileDialog::getOpenFileName(this, tr("Open file"));
    if (!file_path.contains(".csv")){
        ui->label_title->setText("Error");// Вывод ошибки
        return;
    }
    vector<vector<string>> matrix = read_csv_file(file_path.toStdString());
    if (matrix.empty()) {
        ui->label_title->setText("Error");// Вывод ошибки
        return;
    }

    // Устанавливаем CSV модель
    main_model->clear();
    main_model->setColumnCount(matrix.at(0).size());
    // Устанавливаем заголовки
    QStringList headers;
    for (int i = 0; i < matrix.at(0).size(); ++i) {
        headers.push_back(QString::fromStdString(matrix.at(0).at(i)));
    }
    main_model->setHorizontalHeaderLabels(headers);

    for (int i = 1; i < matrix.size(); ++i) {
        QList<QStandardItem *> standardItemsList;
        for (string item_str : matrix.at(i)){
            QString item_qt_str = QString::fromStdString(item_str);
            standardItemsList.append(new QStandardItem(item_qt_str));
        }
        main_model->insertRow(main_model->rowCount(), standardItemsList);
    }
    ui->label_title->setText(file_path);

    /* Vectors */
    vector<double> arr;

    arr.push_back(2.4); // добавляем в конец вектора элемент 2.4
    arr.push_back(-3.2);
    arr.at(0); // обращаемся к 0 элементу
    arr.size(); // возвращает размер вектора
    for (int i = 0; i < arr.size(); ++i){
        arr.at(i); // arr[i]
    }
}

void MainWindow::on_btn_load_clicked()
{
    ui->table_metric->setModel(main_model);
}

void MainWindow::on_btn_metric_clicked()
{
    QString col_str = ui->line_col->text();
    // Проверка на числовой формат

    int col = 1;
    if (col < 1 || col > main_model->columnCount()){
        ui->label_title->setText("Error");
        return;
    }
    col--; // для отсчета с нуля
    QString region = ui->line_region->text();

    vector<double> col_metric;

    for (int i = 0; i < main_model->rowCount(); ++i){
        QString model_region = main_model->item(i, 1)->text();
        if (model_region == region){
            QList<QStandardItem *> res; // Создаем строку
            for (int j = 0; j < main_model->columnCount(); ++j){ // Заполняем строку
                res.append(new QStandardItem(main_model->item(i, j)->text())); // Добавляем в строку каждую "ячейку" нужного региона
            }
            if (is_normal_metric(main_model->item(i, col)->text().toStdString())){
                col_metric.push_back(main_model->item(i, col)->text().toDouble());
            }
            metric_model.appendRow(res);
        }
    }
    ui->table_metric->setModel(&metric_model);
    double min = 0, max = 0, med = 0;
    load_metric(col_metric, min, max, med);

    QString result_text = "Минимум: "+ QString::number(min) +"\nМаксимум: "+ QString::number(max)
            +"\nМедиана: "+ QString::number(med);
    if (col_metric.size() == 0){
        result_text = "Нет результатов. Проверьте название региона или выбранную колонку.";
    }
    ui->label_result->setText(result_text);

}
