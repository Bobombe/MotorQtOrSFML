#ifndef SOUND_H
#define SOUND_H

#include "WorldElement.h"

#ifdef IN_QT

#else
#include <SFML/Audio.hpp>

#endif


class Sound : public WorldElement
{
public:
    Sound();
    Sound(const std::string &soundPath);

    void setSoundFile(const std::string &soundPath);
    void play();
    void pause();
    void stop();

protected:
    bool _looping;
    std::string _soundPath;
    bool _smallSound;

    // Handling spatialised sounds
    bool _spatialised;
    double _maximaleDistance; // Distance at which the sound can be eared.
    double _fullVolumeDistance; // Distance at which the sound volume is maximal.

    // Handling sound depending of techno
#ifdef IN_QT

#else
    sf::SoundBuffer _buffer;
    sf::Sound _sound;
    sf::Music _music;

#endif

};

#endif // SOUND_H
