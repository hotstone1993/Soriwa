//
// Created by newstone 2021-03-04.
//

#ifndef SORIWA_BASEPLAYER_H
#define SORIWA_BASEPLAYER_H

#include <oboe/Oboe.h>
#include <unordered_map>
#include <BaseSource.h>

enum class PlayerStatus {
    loading, // Parsing music data
    ready, // Complete loading of music data
    playing,
    finishing,
    not_support,
    end
};

class Configuration;

class BasePlayer : public oboe::AudioStreamCallback {
public:
    BasePlayer(const Configuration& config);
    virtual ~BasePlayer();

    virtual oboe::DataCallbackResult onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) override ;
    virtual void onErrorAfterClose(oboe::AudioStream *oboeStream, oboe::Result error) override;
    virtual void onErrorBeforeClose(oboe::AudioStream * oboeStream, oboe::Result error) override;

    int addSource(const std::string& sourcePath);
    void deleteSource(int id);

    int play();
    int stop();

    PlayerStatus getStatus();
    int getFrameSize();

    BaseSource* source;

protected:
    PlayerStatus status;
    Configuration* configuration;
};

#endif //SORIWA_BASEPLAYER_H
