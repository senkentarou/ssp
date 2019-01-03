
# include <iostream>
# include <vector>
# include <cmath>
# include <fstream>

//
// idealな結果と一致しない(doubleに依る)
//


using namespace std;

double hz2mel(double hz) {
    return 1127.01048 * log(hz / 700 + 1.0);
}


double mel2hz(double mel) {
    return 700.0 * (exp(mel / 1127.01048) - 1.0);
}

//
// fs=サンプリング周波数, ndft=離散コサイン変換のサンプル数, melChannels=メルフィルタバンクのチャネル数
//
vector< vector<double> > setMelFilterBank(double fs, double ndft, double melChannels) {


    // 設定
    double fmax = fs / 2.0;  // ナイキスト周波数の最大値
    double nmax = (ndft / 2.0) + 1.0;  // 周波数インデックスの最大値
    double melmax = hz2mel(fmax);  // melフィルタバンクの上限

    // メルフィルタバンクの中心周波数(三角形の頂点)を格納
    // mfbCFreq = mel filter bank center frequency
    vector<double> mfbCFreq;
    mfbCFreq.reserve(melChannels + 2);
    for (int i = 0; i < melChannels + 2; i++) {
        mfbCFreq.push_back(mel2hz((melmax / (melChannels + 1)) * i));
    }

    // 周波数空間上の対応点を格納
    // dftBFreq = discrete fourier transform bin frequency
    vector<double> dftBFreq;
    dftBFreq.reserve(nmax);
    for (int i = 0; i < nmax; i++) {
        dftBFreq.push_back((fmax / (nmax - 1)) * i);
    }

    vector< vector<double> > mfb;
    mfb.reserve(melChannels * nmax);

    // mfbの作成
    for (int m = 1; m <= melChannels; m++) {
        vector<double> tmp;
        tmp.reserve(nmax);
        for (int n = 0; n < nmax; n++) {
            double weight;
            if (dftBFreq[n] < mfbCFreq[m-1]) {
                weight = 0.0;
            } else if (dftBFreq[n] <= mfbCFreq[m]) {
                weight = (dftBFreq[n] - mfbCFreq[m-1]) / (mfbCFreq[m] - mfbCFreq[m-1]);
            } else if (dftBFreq[n] <= mfbCFreq[m+1]) {
                weight = (mfbCFreq[m+1] - dftBFreq[n]) / (mfbCFreq[m+1] - mfbCFreq[m]);
            } else {
                weight = 0.0;
            }
            tmp.push_back(weight);
        }
        mfb.push_back(tmp);
    }

    return mfb;
}

int main(void) {

    vector< vector<double> > mfb;

    mfb = setMelFilterBank(8000, 512, 12);

    /*/
    double a = 1000.0;
    double b = hz2mel(a);
    double c = mel2hz(b);
    cout << c << endl;
    //*/

    //*/
    int cnt = 0;
    for (unsigned int i = 0; i < mfb[0].size(); i++) {
        cout << mfb[0][i] << endl;
        cnt++;
    }
    cout << cnt << endl;
    //*/

    //*/ ファイル出力
    ofstream outputcsv("../../data/mel_filter_bank.csv");
    for (unsigned int i = 0; i < mfb.size(); i++) {
        for (unsigned int j = 0; j < mfb[0].size(); j++) {
            outputcsv << mfb[i][j] << ",";
        }
        outputcsv << "\n";
    }
    outputcsv.close();
    //*/

    return 0;
}
