# include "wav.h"

Wav::Wav() {
    
}

Wav::Wav(const char* filepath) {

    // Read wav file along with wavHeader
    FILE* wavFile = std::fopen(filepath, "r");

    // ERROR PROCESSING: cannot open wav file
    if (wavFile == nullptr) {
        std::cerr << "Cannot open wav file: " << filepath << std::endl;
        exit(-1);
    }

    // Read wav file header
    size_t bytesRead = std::fread(&wavHeader, 1, sizeof(wavHeader), wavFile);
    
    // Read wav data
    if (bytesRead > 0) {
        uint16_t bufSize = 4096;
        int8_t* buffer = new int8_t[bufSize];  // read by 1byte

        while ((bytesRead = std::fread(buffer, sizeof(buffer[0]), (bufSize / sizeof(buffer[0])), wavFile)) > 0) {
            for (size_t i = 0; i < bytesRead; i++) {
                wavData.push_back(static_cast<double>(buffer[i]));
            }
        }

        delete [] buffer;
        buffer = nullptr;
    }

    // Close File
    std::fclose(wavFile);
}

Wav::~Wav() {
    
}

std::vector<double> Wav::getWavData() {
    return wavData;
}

WavHeader Wav::getWavHeader() {
    return wavHeader;
}

void Wav::printWavInfo() {

        /* Header Infomation */
        std::cout << "RIFF header : " << wavHeader.RIFF[0] << wavHeader.RIFF[1] << wavHeader.RIFF[2] << wavHeader.RIFF[3] << std::endl;
        std::cout << "WAVE header : " << wavHeader.WAVE[0] << wavHeader.WAVE[1] << wavHeader.WAVE[2] << wavHeader.WAVE[3] << std::endl;
        std::cout << "FMT : " << wavHeader.fmt[0] << wavHeader.fmt[1] << wavHeader.fmt[2] << wavHeader.fmt[3] << std::endl;
        std::cout << "Data string : " << wavHeader.subChunk2ID[0] << wavHeader.subChunk2ID[1] << wavHeader.subChunk2ID[2] << wavHeader.subChunk2ID[3] << std::endl;

        /* Depends on data */
        std::cout << std::endl;
        std::cout << "Data size : " << wavHeader.chunkSize << std::endl;  // totalFileSize - 8 bytes (RIFF size and WAVE size)
        std::cout << "Sub chunk size : " << wavHeader.subChunk1Size << std::endl;
        std::cout << "Audio format : " << wavHeader.audioFormat << std::endl;
        std::cout << "Channels : " << wavHeader.channels << std::endl;
        std::cout << "Sampling rate : " << wavHeader.samplesPerSec << std::endl;
        std::cout << "Bytes per sec : " << wavHeader.bytesPerSec << std::endl;
        std::cout << "Block align : " << wavHeader.blockAlign << std::endl;
        std::cout << "Bits used : " << wavHeader.bitsPerSample << std::endl;
        std::cout << "Data length : " << wavHeader.subChunk2Size << std::endl;
        std::cout << std::endl;

}


