#include "Sound.h"
#include <fstream>

#define SIZE_LIMIT 1000

Sound::Sound() : WorldElement (), _looping(false), _soundPath(""), _smallSound(false), _spatialised(false), _maximaleDistance(0), _fullVolumeDistance(0)
{

}

Sound::Sound(const std::string &soundPath) : WorldElement (), _looping(true), _spatialised(false), _maximaleDistance(0), _fullVolumeDistance(0)
{
    setSoundFile(soundPath);
}

void Sound::setSoundFile(const std::string &soundPath)
{
    _soundPath = soundPath;
    std::ifstream in(_soundPath, std::ifstream::ate | std::ifstream::binary);
    _smallSound = in.tellg() < SIZE_LIMIT;

#ifdef IN_QT

#else
    if (_smallSound) {
        _buffer.loadFromFile(_soundPath);
        _sound.setBuffer(_buffer);
    } else {
        _music.openFromFile(_soundPath);
        _music.setLoop(_looping);
    }

#endif
}

void Sound::play()
{
    _isPlaying = true;
#ifdef IN_QT

#else
    if (_smallSound) {
        _sound.play();
    } else {
        _music.play();
    }

#endif
}

void Sound::pause()
{
    _isPlaying = false;
#ifdef IN_QT

#else
    if (_smallSound) {
        _sound.pause();
    } else {
        _music.pause();
    }

#endif

}

void Sound::stop()
{
    _isPlaying = false;
#ifdef IN_QT

#else
    if (_smallSound) {
        _sound.stop();
    } else {
        _music.stop();
    }

#endif

}
