#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ifstream file("C:\\Users\\DELL\\Desktop\\stock_analyzer\\data\\stock.csv");

    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    getline(file, line); // skip header

    vector<pair<string, float>> stock_data;

    while (getline(file, line)) {
        stringstream ss(line);
        string date, open, high, low, close, volume, dividends, splits;

        // Get each comma-separated field
        getline(ss, date, ',');
        getline(ss, open, ',');
        getline(ss, high, ',');
        getline(ss, low, ',');
        getline(ss, close, ',');
        getline(ss, volume, ',');
        getline(ss, dividends, ',');
        getline(ss, splits, ',');

        try {
            float close_price = stof(close);
            stock_data.push_back({date, close_price});
        } catch (...) {
            cerr << "Invalid close value on line: " << line << endl;
        }
    }

    // ✅ Print first 5 entries
    cout << "Date\t\tClose Price" << endl;
    for (int i = 0; i < min(5, (int)stock_data.size()); ++i) {
        cout << stock_data[i].first << "\t" << stock_data[i].second << endl;
    }

    return 0;
}
