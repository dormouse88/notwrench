/* 
 * File:   SoundGen.cpp
 * Author: Dormouse
 * 
 * Created on 07 January 2015, 15:27
 */

#include "SoundGen.hpp"

#include <iostream>
#include <stdlib.h>
#include <assert.h>
SoundGen::SoundGen()
    :sampleCount(768), amplification(0.f)
{
    samples.resize(sampleCount, 0);
}
//SoundGen::~SoundGen() {}

void SoundGen::SetCallbacks(std::function<float()> eng, std::function<float()> hea, std::function<int()> lev)
{
    getEngine = eng;
    getHealth = hea;
    getLevel = lev;
    
    unsigned int channelCount = 1;
    unsigned int sampleRate = 44100;
    initialize(channelCount, sampleRate);
}

bool SoundGen::onGetData(Chunk& data)
{
    //Indirected random walk...
    targetAmp += (( (rand() % 199) -99 ) / 1000.f);
    targetAmp = std::max(0.03f, std::min(targetAmp, 0.97f));
    if (targetAmp > amplification) amplification += 0.02f;
    else amplification -= 0.02f;

    //Indirected randomly set...
    targetSamples = 624 + getLevel() * 4 * 12;
    targetSamples += (rand() % 72) * (getLevel() + 1);
    sampleCount = targetSamples;
    if (targetSamples > sampleCount) sampleCount +=96;
    else sampleCount -=72;
    
    int num_main_waves = 8;
    int num_harm_waves = 12;
    int num_saww_waves = 46;
    float main_samples = (float)sampleCount / num_main_waves;
    float harm_samples = (float)sampleCount / num_harm_waves;
    float saww_samples = (float)sampleCount / num_saww_waves;
    //assert( sampleCount % num_main_waves == 0);
    //assert( sampleCount % num_harm_waves == 0);
    const float TWO_PI = 6.283185307179586476925286766559;
    const int main_amp = 14000;
    const int harm_amp = 11000;
    const int saww_amp = 7000;
    int final_main_amp = main_amp * amplification;
    int final_harm_amp = harm_amp * getEngine();
    int final_saww_amp = saww_amp * getHealth();
    assert(final_main_amp <= main_amp);
    assert(final_harm_amp <= harm_amp);
    assert(final_saww_amp <= saww_amp);
    assert(final_main_amp + final_harm_amp + final_saww_amp < 32001);
    
    samples.resize(sampleCount);
    for (int i = 0; i<samples.size(); i++) {
        //samples[i] =  sin( (i*TWO_PI)/main_samples ) * final_main_amp;
        samples[i] = sin( (i*TWO_PI)/harm_samples ) * final_harm_amp;
        samples[i] += (abs( fmod(i+saww_samples/2, 2 * saww_samples) - saww_samples ) - saww_samples/2 ) * final_saww_amp / saww_samples;
        assert(samples[i] < 32000);
        assert(samples[i] > -32000);
    }
    
    assert(samples[0] < 5000);
    assert(samples[0] > -5000);
    assert(samples[samples.size()-1] < 5000);
    assert(samples[samples.size()-1] > -5000);

    //if (rand() % 50 == 0) 
    //std::cout << getEngine() << " " << getHealth() << " " << getLevel() << std::endl;
    
    
    
    
    //Generate some sounds..
//    const unsigned int HALFSC = sampleCount / 2;
//    const unsigned AMPLITUDE = 5000;
//    const double TWO_PI = 6.28318;
//    const double INCREMENT = 440./44100;
//    double t = 0;
//    for (auto & x: samples) {
//        x = (HALFSC - abs(HALFSC-t))*(1./HALFSC)* AMPLITUDE * sin(t*INCREMENT*TWO_PI);
//        x += (HALFSC - abs(HALFSC-t))*(1./HALFSC)* AMPLITUDE * sin(t*INCREMENT*0.9*TWO_PI);
//        t++;
//    }

    data.samples = &samples[0];
    data.sampleCount = sampleCount;
//    for (auto x: samples) {
//        std::cout << x << std::endl;
//    }
//    std::cout << "ENDENDENDENDEND" << std::endl;
    return true;    
}
