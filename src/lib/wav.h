# include <iostream>
# include <vector>
# include <cstdio>

#include "wavformat.h"

class Wav {
private:
    WavHeader wavHeader;
    std::vector<double> wavData;

public:
    Wav();
    Wav(const char* filepath);
    ~Wav();

    WavHeader getWavHeader();
    std::vector<double> getWavData();
    
    void printWavInfo();
};
