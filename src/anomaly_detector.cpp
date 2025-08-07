#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

struct StockData {
    string date;
    double close;
};

vector<StockData> readCSV(const string& filename) {
    vector<StockData> data;
    ifstream file(filename);
    string line;

    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string date, token;
        double open, high, low, close, volume, div, split;

        getline(ss, date, ',');
        ss >> open; ss.ignore();
        ss >> high; ss.ignore();
        ss >> low; ss.ignore();
        ss >> close; ss.ignore();

        data.push_back({date, close});
    }

    return data;
}

void detectAnomalies(const vector<StockData>& data, int k = 5, double threshold = 0.10) {
    cout << "Anomalies (Close Price Deviates > " << threshold * 100 << "%):\n";

    for (int i = k; i < data.size(); ++i) {
        double sum = 0.0;
        for (int j = i - k; j < i; ++j)
            sum += data[j].close;

        double avg = sum / k;
        double deviation = abs(data[i].close - avg) / avg;

        if (deviation > threshold) {
            cout << data[i].date << " → " << data[i].close 
                 << " (Avg: " << avg << ", Deviation: " << deviation * 100 << "%)\n";
        }
    }
}

int main() {
    string filepath = "data/stock.csv";
    vector<StockData> stock = readCSV(filepath);
    detectAnomalies(stock);
    return 0;
}
