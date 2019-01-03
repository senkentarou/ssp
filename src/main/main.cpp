# include "main.h"

int main(void) {

    // wavファイルの情報を抜き出す
    Wav w("../../data/create_wave_0.wav");

    WavHeader wavHeader = w.getWavHeader();
    std::vector<double> wavData = w.getWavData();

    //*/ フレームで分けてフーリエ変換 -> STFT
    int frameWindowSize = static_cast<int>(wavHeader.samplesPerSec * 0.03);
    int frameShiftSize = static_cast<int>(wavHeader.samplesPerSec * 0.01);
    int fftBinSize = 512;

    STFT stft(wavData, frameWindowSize, frameShiftSize, fftBinSize);
    std::vector< std::vector<double> > powerSpectrumData = stft.getPowerSpectrumData();

    /*/
    std::vector<double> data;

    for (unsigned int i = 0; i < 8; i++) {
        data.push_back(1.0);
    }

    STFT s(data, 8, 2, 16);
    std::vector< std::vector<double> > powerSpectrumData = s.getPowerSpectrumData();
    //*/


    // melフィルタバンクをかけて対数化, 離散コサイン変換とリフタリング -> MFCC

    
    /*/ For confirmation of variables
    w.printWavInfo();
    for (unsigned int i = 0; i < wavData.size(); i++) {
        std::cout << wavData[i] << std::endl;
    }

    //*/

    std::cout << "Power: " << std::endl;
    for (unsigned int i = 0; i < powerSpectrumData.size(); i++) {
        std::cout << "-- frame" << i+1 << " --" << std::endl;
        for (unsigned int j = 0; j < powerSpectrumData[i].size(); j++) {
            std::cout << powerSpectrumData[i][j] << std::endl;
        }
    }
    //*/

    return 0;
}
