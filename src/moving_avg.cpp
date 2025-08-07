#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip> // for setprecision

using namespace std;

int main() {
    ifstream file("data/stock.csv");
    if (!file.is_open()) {
        cerr << "Error opening file.\n";
        return 1;
    }

    string line;
    vector<pair<string, double>> prices;

    // Skip header line
    getline(file, line);

    // Read data
    while (getline(file, line)) {
        stringstream ss(line);
        string date, open, high, low, close, volume, div, split;

        getline(ss, date, ',');
        getline(ss, open, ',');
        getline(ss, high, ',');
        getline(ss, low, ',');
        getline(ss, close, ',');
        getline(ss, volume, ',');
        getline(ss, div, ',');
        getline(ss, split, ',');

        prices.push_back({date, stod(close)});
    }

    file.close();

    // Sliding window average
    int k = 3;
    cout << "Moving Average (k = " << k << ") of Closing Prices:\n";
    cout << "---------------------------------------------\n";

    for (size_t i = 0; i <= prices.size() - k; ++i) {
        double sum = 0.0;
        for (int j = 0; j < k; ++j) {
            sum += prices[i + j].second;
        }
        double avg = sum / k;
        cout << prices[i + k - 1].first << " => " << fixed << setprecision(2) << avg << endl;
    }

    return 0;
}
