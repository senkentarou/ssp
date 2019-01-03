
# include <iostream>
# include <vector>
# include <cmath>

using namespace std;

vector<double> dftPowerSpectrum(vector<double> data) {

    unsigned int dataLength = data.size();
    unsigned int binSize = (dataLength * 2) - 1;

    for (unsigned int i = dataLength; i < binSize; i++) {
        data.push_back(0.0);
    }

    vector<double> p;
    double XReal;
    double XImag;
    for (unsigned int k = 0; k < binSize; k++) {  // for each output element
        XReal = 0.0;
        XImag = 0.0;
        for (unsigned int t = 0; t < binSize; t++) {  // for each input element
            XReal += data[t] * cos(2.0 * M_PI * k * t / binSize);
            XImag -= data[t] * sin(2.0 * M_PI * k * t / binSize);
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
    int sample = 12;  // N

    for (int t = 0; t < sample; t++) {
        double tmp = sin(2 * M_PI * t / sample);
        //double tmp = 1.0;
        cout << tmp << endl;
        data.push_back(tmp);
    }

    p = dftPowerSpectrum(data);

    cout << "dft power spector" << endl;
    for (unsigned int i = 0; i < p.size(); i++) {
        cout << p[i] << endl;
    }

    return 0;
}
