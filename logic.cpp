#include "logic.h"
using namespace std;

bool is_normal_metric(string text){
    /* Проверяет метрику на числовой формат */
    if (text == "")
        return false;
    for (int i = 0; i < text.length(); ++i){
        if (!isdigit(text[i]) && (text[i] != '-' && text[i] != '.')){
            return false;
        }
    }
    return true;
}

vector<string> split_line(string line){
    vector<string> result;
    string word = "";
    for (int i = 0; i < line.length(); ++i){
        char symbol = line[i];
        if ((symbol == ',') || symbol == '\n'){
            result.push_back(word);
            word = "";
            continue;
        }
        word += symbol;
    }
    result.push_back(word);
    return result;
}

vector<vector<string>> read_csv_file(string str_path){
    /* Считывает данные из файла и записывает в двумерный массив */
    vector<vector<string>> result;
    string line = "";
    ifstream file(str_path);

    while(getline(file, line)){
        vector<string> line_model = split_line(line);
        result.push_back(line_model);
    }
    return result;
}

void load_metric(vector<double> metric, double& minimum, double& maximum, double& mediana){
    /* Считает метрику по массиву metric и записывает все значения в переданные переменные */

    sort(metric.begin(), metric.end());
    minimum = 0; maximum = 0; mediana = 0;
    if (metric.size() != 0){
        minimum = metric[0];
        maximum = metric[metric.size() - 1];
        if (metric.size() % 2){
            mediana = metric[metric.size() / 2];
        } else {
            mediana = (metric[metric.size() / 2 - 1] + metric[metric.size() / 2]) / 2;
        }
    }
}
