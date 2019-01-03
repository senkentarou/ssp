# include <iostream>
# include <vector>
# include <cmath>

using namespace std;

vector<double> dft_powerspector(vector<double> data) {

    unsigned int dataLength = data.size();
    vector<double> p;
    double XReal;
    double XImag;
    for (unsigned int k = 0; k < dataLength; k++) {  // for each output element
        XReal = 0.0;
        XImag = 0.0;
        for (unsigned int t = 0; t < dataLength; t++) {  // for each input element
            XReal += data[t] * cos(2.0 * M_PI * k * t / dataLength);
            XImag -= data[t] * sin(2.0 * M_PI * k * t / dataLength);
        }
        p.push_back((XReal * XReal) + (XImag * XImag));
    }

    return p;
}

int main() {

    vector<double> data;
    vector<double> p;
    
    data.reserve(4);
    cout << "Input" << endl;
    int term = 10;
    for (int t = 0; t < term; t++) {
        double tmp = sin(2 * M_PI * t / term);
        cout << tmp << endl;
        data.push_back(tmp);
    }

    p = dft_powerspector(data);

    cout << "dft power spector" << endl;
    for (unsigned int i = 0; i < p.size(); i++) {
        cout << p[i] << endl;
    }

    return 0;
}
