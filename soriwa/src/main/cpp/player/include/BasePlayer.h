//
// Created by newstone 2021-03-04.
//

#ifndef SORIWA_BASEPLAYER_H
#define SORIWA_BASEPLAYER_H

#include <oboe/Oboe.h>
#include <unordered_map>
#include <BaseSource.h>

class BasePlayer : public oboe::AudioStreamCallback {
public:
    BasePlayer();
    ~BasePlayer();

    virtual oboe::DataCallbackResult onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) override ;
    virtual void onErrorAfterClose(oboe::AudioStream *oboeStream, oboe::Result error) override;
    virtual void onErrorBeforeClose(oboe::AudioStream * oboeStream, oboe::Result error) override;

    int addSource(const std::string& sourcePath);
    void deleteSource(int id);
    BaseSource* source;
private:
};

#endif //SORIWA_BASEPLAYER_H
