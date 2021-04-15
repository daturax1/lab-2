#ifndef LOGIC_H
#define LOGIC_H

#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <cmath>

using namespace std;

bool is_normal_metric(string text);
vector<vector<string>> read_csv_file(string path);
vector<string> split_line(string line);
void load_metric(vector<double> metric, double& minimum, double& maximum, double& mediana);

#endif // LOGIC_H
