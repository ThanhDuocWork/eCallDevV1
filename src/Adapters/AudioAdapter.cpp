#include"AudioAdapter.h"
#include <iostream>
std::shared_ptr<AudioAdapter> AudioAdapter::mInstanceAudio = nullptr;
AudioAdapter::AudioAdapter()
    : pcmHandle(nullptr), params(nullptr), fileRB(nullptr),
      sampleRate(44100), numChannels(2), bitsPerSample(16),
      flagStop(false), flagPause(false), isPlaying(false)
       {}
 
AudioAdapter::~AudioAdapter() {
    stopAudio();
    if (pcmHandle) snd_pcm_close(pcmHandle);
    if (fileRB) fclose(fileRB);
}
 
bool AudioAdapter::openFile(const std::string filename) {
    if (fileRB) {
        fclose(fileRB);  
    }
    fileRB = fopen(filename.c_str(), "rb");
    if (!fileRB) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }
    return true;
}

 
bool AudioAdapter::configureDevice() {
    if (snd_pcm_open(&pcmHandle, "default", SND_PCM_STREAM_PLAYBACK, 0) < 0) {
        std::cerr << "Failed to open PCM device" << std::endl;
        return false;
    }
 
    snd_pcm_hw_params_alloca(&params);
    snd_pcm_hw_params_any(pcmHandle, params);
    snd_pcm_hw_params_set_access(pcmHandle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(pcmHandle, params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_channels(pcmHandle, params, numChannels);
    snd_pcm_hw_params_set_rate_near(pcmHandle, params, &sampleRate, 0);
 
    if (snd_pcm_hw_params(pcmHandle, params) < 0) {
        std::cerr << "Failed to set PCM hardware parameters" << std::endl;
        snd_pcm_close(pcmHandle);
        return false;
    }
 
    return true;
}
 
void AudioAdapter::playAudio() {
    if (!fileRB || !pcmHandle) {
        std::cerr << "Audio file or PCM device is not open." << std::endl;
        return;
    }
 
    flagStop = false;
    isPlaying = true;
    flagPause = false;
 
    while (!flagStop) {
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]() { return !flagPause || flagStop; });
            if (flagStop) break;
        }
 
        int frames = fread(buffer, sizeof(unsigned char), bufferSize, fileRB);
        if (frames <= 0) {
            if (feof(fileRB)) {
                printLog_I("End of file reached.");
                break;
            }
        }
 
        int framesToPlay = frames / (numChannels * (bitsPerSample / 8));
        int err = snd_pcm_writei(pcmHandle, buffer, framesToPlay);
        if (err == -EPIPE) {
            snd_pcm_prepare(pcmHandle);
        } else if (err < 0) {
            std::cerr << "Error writing to PCM device: " << snd_strerror(err) << std::endl;
            break;
        }
    }
 
    snd_pcm_drain(pcmHandle);
    isPlaying = false;
    printLog_I("Playback finished or stopped.");
}
 
 
void AudioAdapter::pauseAudio() {
    std::lock_guard<std::mutex> lock(mtx);
    if (!isPlaying || flagPause) {
        printLog_I("Cannot pause, playback is not active or already paused.");
        return;
    }
 
    if (pcmHandle) {
        int err = snd_pcm_pause(pcmHandle, 1);  
        if (err < 0) {
            std::cerr << "snd_pcm_pause not supported, stopping playback manually." << std::endl;
            snd_pcm_drop(pcmHandle);  
        } else {
            printLog_I( "Playback paused via snd_pcm_pause.");
        }
    }
 
    flagPause = true;
    printLog_I("Playback paused.");
}
 
 
void AudioAdapter::resumeAudio() {
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (!flagPause) {
            printLog_I("Cannot resume, playback is not paused.");
            return;
        }
 
        if (pcmHandle) {
            int err = snd_pcm_pause(pcmHandle, 0);
            if (err < 0) {
                std::cerr << "snd_pcm_pause not supported, restarting playback manually." << std::endl;
                snd_pcm_prepare(pcmHandle);  
            } else {
                printLog_I("Playback resumed via snd_pcm_pause.");
            }
        }
 
        flagPause = false;  
    }
    cv.notify_one();  
}
 
 
void AudioAdapter::stopAudio() {
    {
        std::lock_guard<std::mutex> lock(mtx);
        flagStop = true;    
        flagPause = false;  
    }
    if (pcmHandle) {
        snd_pcm_drop(pcmHandle);
    }
    if (playThread.joinable()) {
        playThread.join();
    }
    printLog_I("Playback stopped.");
}

AudioAdapter *AudioAdapter::getInstance()
{
    if(mInstanceAudio == nullptr)
    {
        mInstanceAudio = std::make_shared<AudioAdapter>();
    }
    return mInstanceAudio.get();
}

void AudioAdapter::runFileWAV(const std::string &filename) {
    if (!openFile(filename)) {
        std::cerr << "Failed to open WAV file: " << filename << std::endl;
        return;
    }
    if (!configureDevice()) {
        std::cerr << "Failed to configure ALSA device." << std::endl;
        return;
    }
    if (playThread.joinable()) {
        stopAudio();
        playThread.join();  
    }
    //playThread = std::thread(&AudioAdapter::playAudio, this);
    std::thread([this]() { playAudio(); }).detach();
}


void AudioAdapter::handleLogicRunAudio(const std::string &data)
{
    if (data == "ON") {
        printLog_I("Audio ON command received.");
        runFileWAV("/home/duoctdt/Example_Project/src/piano.wav");
    } else if (data == "OFF") {
        printLog_I("Audio OFF command received.");
        stopAudio(); 
    } else if (data == "PAUSE") {
        printLog_I("Audio PAUSE command received.");
        pauseAudio();
    } else if (data == "RESUME") {
        printLog_I("Audio RESUME command received.");
        resumeAudio();
    } else {
        printLog_I("Error: Invalid audio command received.");
    }
}
