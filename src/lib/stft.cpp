# include "stft.h"

STFT::STFT() {

}

STFT::STFT(const std::vector<double> &data, int windowSize, int shiftSize, int fftSize) {

    frameWindowSize = windowSize;
    frameShiftSize = shiftSize;
    fftBinSize = fftSize;

    // FFT計算
    for (int i = 0; i < static_cast<int>(data.size()) - (frameWindowSize - 1); i += frameShiftSize) {
        std::vector<double> extractData(data.begin() + i, data.begin() + (i + frameWindowSize));
        calculateHammingWindow(extractData);
        fftData.push_back(calculateFFT(extractData));
    }

    // PowerSpectrum計算
    for (int i = 0; i < static_cast<int>(fftData.size()); i++) {
        std::vector<double> tmp;
        for (int j = 0; j < static_cast<int>(fftData[i].size()); j++) {
            tmp.push_back(std::norm(fftData[i][j]));
        }
        powerSpectrumData.push_back(tmp);
    }

}

STFT::~STFT() {

}

void STFT::calculateHammingWindow(std::vector<double> &data) {
    int dataSize = static_cast<int>(data.size());
    for (int i = 0; i < dataSize; i++) {
        data[i] *= 0.54 - (0.46 * std::cos((2.0 * i * M_PI) / (dataSize - 1)));
    }
}


std::vector< std::complex<double> > STFT::calculateFFT(std::vector<double> &data) {
    
    std::vector< std::complex<double> > complexData;
    int inputDataSize = static_cast<int>(data.size());
    int start = 0;
    int numPeriod = 2;
    
    for (int i = 0; i < inputDataSize; i++) {
        std::complex<double>tmp(data[i], 0.0);
        complexData.push_back(tmp);    
    }

    for (int i = inputDataSize; i < fftBinSize; i++) {
        std::complex<double>tmp(0.0, 0.0);
        complexData.push_back(tmp);
    }

    fftShuffle(complexData);

    for (int step = 1; step < fftBinSize; step *= 2) {
        start = 0;
        while (start < fftBinSize) {
            for (int i = 0; i < numPeriod / 2; i++) {
                std::complex<double> w(std::cos(2.0 * M_PI * i / numPeriod), -(std::sin(2.0 * M_PI * i / numPeriod)));
                std::complex<double> tmp1 = complexData[start + i] + complexData[start + i + step] * w;
                std::complex<double> tmp2 = complexData[start + i] - complexData[start + i + step] * w;
                complexData[start + i] = tmp1;
                complexData[start + i + step] = tmp2;
            }
            start += (2 * step);
        }
        numPeriod *= 2;
    }

    return complexData;
}


void STFT::fftShuffle(std::vector< std::complex<double> > &data) {

    int dataSize = static_cast<int>(data.size());
    int indReverse = 0;

    for (int indSample = 0; indSample < dataSize; indSample++) {  

        if (indReverse > indSample) {
            std::complex<double> tmp = data[indSample];
            data[indSample] = data[indReverse];
            data[indReverse] = tmp;
        }
        int numHalfSample = dataSize / 2;
        while ((numHalfSample >= 1) && (indReverse >= numHalfSample)) {
            indReverse -= numHalfSample;
            numHalfSample /= 2;
        }
        indReverse += numHalfSample;
    }
}

std::vector< std::vector< std::complex<double> > > STFT::getFFTData() {
    return fftData;
}

std::vector< std::vector<double> > STFT::getPowerSpectrumData() {
    return powerSpectrumData;
}
