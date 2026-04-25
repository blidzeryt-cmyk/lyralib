#include <cstdint>

typedef int32_t i32;
typedef int16_t i16;

struct wavHeader {
    char chunkId[4] = {'R','I','F','F'};
    i32 chunkSize = 36;
    char format[4] = {'W','A','V','E'};
    char subchunk1Id[4] = {'f','m','t',' '};
    i32 subchunk1Size = 16;
    i16 audioFormat = 1;
    i16 numChannels = 1;
    i32 sampleRate = 44100;
    i16 bitsPerSample = 16;
    i16 blockAlign = numChannels * (bitsPerSample / 8);
    i32 byteRate = sampleRate * blockAlign;
    char subchunk2Id[4] = {'d','a','t','a'};
    i32 subchunk2Size = 0;
};