#include <iostream>
#include <vector>
#include <cmath>
#include <complex>

//
// fft sample and complex sample
//

using namespace std;

// fftに適した順番に整列する
void fftShuffle(vector< complex<double> > &data) {
    
    int numSample = (int)data.size();
    int indReverse = 0;  
    for (int indSample = 0; indSample < numSample; indSample++) {  

        if (indReverse > indSample) {
            complex<double> tmp = data[indSample];
            data[indSample] = data[indReverse];
            data[indReverse] = tmp;
        }
        int numHalfSample = numSample >> 1;
        while ((numHalfSample >= 1) && (indReverse >= numHalfSample)) {
            indReverse -= numHalfSample;
            numHalfSample >>= 1;
        }
        indReverse += numHalfSample;
    }  
}

// fftを計算する
void fft(vector< complex<double> > &fftData) {
    
	int numSample = fftData.size();
    int start = 0;
    int N = 2;

    for (int step = 1; step < numSample; step *= 2) {
        start = 0;
        while (start < numSample) {
            for (int i = 0; i < N/2; i++) {
                double w_r =  cos(2 * M_PI * i / N);
                double w_i = -sin(2 * M_PI * i / N);
                complex<double> w(w_r, w_i);
                complex<double> tmp1 = fftData[start + i] + fftData[start + i + step] * w;
                complex<double> tmp2 = fftData[start + i] - fftData[start + i + step] * w;
                fftData[start + i] = tmp1;
                fftData[start + i + step] = tmp2;
            }
            start += (2 * step);
        }
        N *= 2;
    }
}

void ifft(vector< complex<double> > &fftData) {

    int dataSize = (int)fftData.size();

    for (int i = 0; i < dataSize; i++) {
        fftData[i] = conj(fftData[i]);
    }

    fft(fftData);

    for (int i = 0; i < dataSize; i++) {
        fftData[i] = conj(fftData[i]);
    }

    for (int i = 0; i < dataSize; i++) {
        fftData[i] /= dataSize;
    }

}

int main() {

	int numSample = 8;
    int numFftBin = 16;
    vector<double> data;
	vector< complex<double> > fftData;

    // make data
	for (int i = 0; i < numSample; i++) {
        data.push_back(sin(2.0 * M_PI * i / numSample));
    }

    for (int i = numSample; i < numFftBin; i++) {
        data.push_back(0.0);
    }

    // make fftData
    for (int i = 0; i < numFftBin; i++) {
        complex<double> tmp(data[i], 0.0);
        fftData.push_back(tmp);
    }

    // shuffle fftData    
    fftShuffle(fftData);

    //*/ show obj of data
    cout << "data" << endl;
    for (unsigned int i = 0; i < data.size(); i++) {
        cout << data[i] << endl;
    }
    
    cout << "fftData" << endl;
    for (unsigned int i = 0; i < fftData.size(); i++) {
        cout << fftData[i] << endl;
    }
    //*/

    // calc fft
    fft(fftData);

    //*/ show data of fft
    cout << "fft" << endl;
    for (unsigned int i = 0; i < fftData.size(); i++) {
        cout << fftData[i] << endl;
    }
    //*/

    //*/ show data of power 
    cout << "power" << endl;
    for (unsigned int i = 0; i < fftData.size(); i++) {
        cout << norm(fftData[i]) << endl;
    }
    //*/
    
    // calc ifft
    fftShuffle(fftData);
    ifft(fftData);
    
    //*/ show data of fft
    cout << "ifft" << endl;
    for (unsigned int i = 0; i < fftData.size(); i++) {
        cout << fftData[i] << endl;
    }
    //*/

	return 0;
}
