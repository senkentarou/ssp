# include <cstdint>

struct WavHeader {

    /* RIFF Chunk Descriptor */
    uint8_t RIFF[4];
    uint32_t chunkSize;
    uint8_t WAVE[4];

    /* "fmt " Sub-chunk */
    uint8_t fmt[4];
    uint32_t subChunk1Size;  // default: 16
    uint16_t audioFormat;  // uncompressed PCM: 1
    uint16_t channels;  // mono: 1
    uint32_t samplesPerSec;  // sampling rate: 44100, 8000, etc..
    uint32_t bytesPerSec;  // bytes to recode per sec
    uint16_t blockAlign;  // block boundary (16bit mono = 16*1/8=2bytes)
    uint16_t bitsPerSample;

    /* "data" Sub-chunk */
    uint8_t subChunk2ID[4];
    uint32_t subChunk2Size;

};
