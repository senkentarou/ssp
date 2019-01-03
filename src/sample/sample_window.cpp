
# include <iostream>
# include <vector>
# include <cmath>

using namespace std;

void hammingWindow(vector<double> &data) {

    for (unsigned int n = 0; n < data.size(); n++) {
        data[n] *= 0.54 - (0.46 * cos((2 * n * M_PI) / (data.size() - 1)));
    }
}


int main(void) {

    vector<double> data(10, 1000);  // 10個の要素を1で初期化

    cout << "before" << endl;
    for (unsigned int i = 0; i < data.size(); i++) {
        cout << data[i] << endl;
    }

    hammingWindow(data);

    cout << "after" << endl;
    for (unsigned int i = 0; i < data.size(); i++) {
        cout << data[i] << endl;
    }

    return 0;
}
