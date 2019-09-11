#include "Sound.h"
#include <fstream>

Sound::Sound() : WorldElement (), _looping(false), _soundPath(""), _soundFileSize(0), _spatialised(false), _maximaleDistance(0), _fullVolumeDistance(0)
{

}

Sound::Sound(const std::string &soundPath) : WorldElement (), _looping(false), _soundPath(soundPath), _spatialised(false), _maximaleDistance(0), _fullVolumeDistance(0)
{
    std::ifstream in(_soundPath, std::ifstream::ate | std::ifstream::binary);
    _soundFileSize = in.tellg();
#ifdef IN_QT

#else
    _buffer.loadFromFile(_soundPath);
    _sound.setBuffer(_buffer);

#endif
}

void Sound::setSoundFile(const std::string &soundPath)
{
    _soundPath = soundPath;
    std::ifstream in(_soundPath, std::ifstream::ate | std::ifstream::binary);
    _soundFileSize = in.tellg();
#ifdef IN_QT

#else
    _buffer.loadFromFile(_soundPath);
    _sound.setBuffer(_buffer);

#endif
}

void Sound::play()
{

#ifdef IN_QT

#else
    _sound.play();

#endif
}

void Sound::pause()
{

}

void Sound::stop()
{

}
