
# include <vector>
# include <complex>
# include <cmath>

class STFT {
private:
    int frameWindowSize;
    int frameShiftSize;
    int fftBinSize;
    std::vector< std::vector< std::complex<double> > > fftData;
    std::vector< std::vector<double> > powerSpectrumData;

    void calculateHammingWindow(std::vector<double> &data);
    std::vector< std::complex<double> > calculateFFT(std::vector<double> &data);
    void fftShuffle(std::vector< std::complex<double> > &data);

public:
    STFT();
    STFT(const std::vector<double> &data, int windowSize, int shiftSize, int fftSize);
    ~STFT();

    std::vector< std::vector< std::complex<double> > > getFFTData();
    std::vector< std::vector<double> > getPowerSpectrumData();
};
