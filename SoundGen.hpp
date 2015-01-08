/* 
 * File:   SoundGen.hpp
 * Author: Dormouse
 *
 * Created on 07 January 2015, 15:27
 */

#ifndef SOUNDGEN_HPP
#define	SOUNDGEN_HPP

#include <SFML/Audio.hpp>
#include <vector>

// custom audio stream that generates soundwaves
class SoundGen : public sf::SoundStream
{
public:
    SoundGen();
//    virtual ~SoundGen();
    void SetCallbacks(std::function<float()> f);
private:
    virtual bool onGetData(Chunk& data);

    virtual void onSeek(sf::Time timeOffset) {}         //Seeking is not supported

    unsigned int sampleCount;
    std::vector<sf::Int16> samples;
    std::function<float()> getModelData;
    float amplification;
    
};

#endif	/* SOUNDGEN_HPP */

