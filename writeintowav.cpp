#include <fstream>
#include <iostream>
#include <string>
#include "wavstructure.h"
#include <cstdint>
#include <cmath>
#include <vector>

wavHeader H;


void WriteWavHeader(int32_t datasize){

    std::ofstream out;
    out.open("out.wav", std::ios::binary);

    out.write(H.chunkId, 4);
    out.write((char*)&H.chunkSize, 4);
    out.write(H.format, 4);
    out.write(H.subchunk1Id, 4);
    out.write((char*)&H.subchunk1Size, 4);
    out.write((char*)&H.audioFormat, 2);
    out.write((char*)&H.numChannels, 2);
    out.write((char*)&H.sampleRate, 4);
    out.write((char*)&H.byteRate, 4);
    out.write((char*)&H.blockAlign, 2);
    out.write((char*)&H.bitsPerSample, 2);
    out.write(H.subchunk2Id, 4);
    out.write((char*)&H.subchunk2Size, 4);
    out.close();
}
double adsr(double t, double duration, double attack, double decay, double sustain, double release) {
    if (t < attack) {
        return t / attack;
    } 
    else if (t < attack + decay) {
        double decayT = t - attack;
        return 1 - (decayT / decay) * (1 - sustain);
    } 
    else if (t < duration - release) {
        return sustain;
    } 
    else {
        double releaseT = t - (duration - release);
        return sustain * (1 - releaseT / release);
    }
}

void WriteWavData(double duration, double freq, double volume = 0.9){
    double pi = 3.14159265358979323846;
    i32 numSamples = duration * H.sampleRate;
    std::ofstream out;
    out.open("out.wav", std::ios::binary | std::ios::app);
    for (i32 i = 0; i < numSamples; i++){
        double t = (double)i/H.sampleRate;
        double envelope = adsr(t, duration, 0.01, 0.1, 0.7, 0.2);
        double value = sin(2 * pi * freq* t) * envelope * volume;
        i16 sample = static_cast<i16>(value * 30000);
        out.write((char*)&sample, 2);
    }
    out.close();
}

