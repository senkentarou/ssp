
# include <iostream>
# include <vector>
# include <cmath>

# include <fstream>

using namespace std;

double hz2mel(double f) {
    return 1127.01048 * log(1.0 + (f / 700.0));
}

int main(void) {

    int freqNum = 10000;
    vector<double> mel; 
    mel.reserve(freqNum);

    for (int i = 0; i < freqNum; i++) {
        mel.push_back(hz2mel((double)i));
    }

    //*/ ファイル出力
    ofstream outputcsv("../../data/mel_scale.csv");
    for (unsigned int i = 0; i < mel.size(); i++) {
        outputcsv << i << "," << mel[i] << "\n";
    }
    outputcsv.close();
    //*/
    return 0;
}
