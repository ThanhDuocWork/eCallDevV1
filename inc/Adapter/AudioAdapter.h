#ifndef AUDIOADAPTER_H
#define AUDIOADAPTER_H
#include <iostream> 
#include <alsa/asoundlib.h>
#include <condition_variable>
#include <mutex>
#include <string>
#include<memory>
#include "Logger.h"
#include<thread>
#include<chrono>
class AudioAdapter {
private:
    snd_pcm_t *pcmHandle;
    snd_pcm_hw_params_t *params;
    std::string filename;
    FILE *fileRB;
    unsigned int sampleRate;
    int numChannels;
    int bitsPerSample;
    const int bufferSize = 4096;
    unsigned char buffer[4096];
 
    bool flagStop;    
    bool flagPause;   
    bool isPlaying;   
 
    std::thread playThread;
    std::condition_variable cv;
    std::mutex mtx;
    static std::shared_ptr<AudioAdapter> mInstanceAudio;
    // AudioAdapter();
    std::string cacheStopSignelMQTT;

    std::mutex audioMutex;
 
public:
    // AudioAdapter()= default;
    AudioAdapter();
    ~AudioAdapter();
 
    bool openFile(const std::string filename);
    bool configureDevice();
    void playAudio();
    void pauseAudio();
    void resumeAudio();
    void stopAudio();
    static AudioAdapter *getInstance();
    void runFileWAV(const std::string &filename);
    void handleLogicRunAudio(const std::string &data);
    std::string handleStopAudifromMQTT(const std::string &data = "");

    void handleLogicAudioCommandHMI(const std::string status);
    std::mutex& getMutex();
};
 
#endif // AUDIOADAPTER_H