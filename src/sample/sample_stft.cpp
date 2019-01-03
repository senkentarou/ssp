# include <iostream>
# include <vector>
# include <cmath>

using namespace std;

int hammingWindow(vector<double> &data) {

    unsigned int dataLength = data.size();
    for (unsigned int n = 0; n < dataLength; n++) {
        data[n] *= 0.54 - (0.46 * cos((2 * n * M_PI) / (dataLength - 1)));
    }

    return 0;
}

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

int main(void) {

    int dataSize = 100;
    int windowSize = 10;
    int shiftSize = 5;

    vector<double> data;
    vector< vector<double> > spectrogram;

    data.reserve(dataSize);
    for (int t = 0; t < dataSize; t++) {
        double tmp = sin(2 * M_PI * t / dataSize);
        //double tmp = 1.0;
        cout << tmp << endl;
        data.push_back(tmp);
    }

    // STFT
    int cnt = 0;
    for (int i = 0; i < dataSize - (windowSize - 1); i += shiftSize) {
        // フレームサイズに分割
        vector<double> extractData(data.begin() + i, data.begin() + i + windowSize);
        // 窓関数を掛ける
        hammingWindow(extractData);
        // DFT -> スペクトログラム
        spectrogram.push_back(dftPowerSpectrum(extractData));
        cnt++;
    }

    //*/
    cout << "spectrogram" << endl;
    for (unsigned int i = 0; i < spectrogram.size(); i++) {
        for (unsigned int j = 0; j < spectrogram[i].size(); j++) {
            cout << spectrogram[i][j] << ",";
        }
        cout << endl;
    }
    cout << cnt << endl;
    //*/

    return 0;
}
