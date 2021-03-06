//
// Created by newst on 2021-03-25.
//

#ifndef SORIWA_CUSTOMPLAYER_H
#define SORIWA_CUSTOMPLAYER_H


#include "BasePlayer.h"

class CustomPlayer : public BasePlayer {
public:
    CustomPlayer(const Configuration& config);
    virtual ~CustomPlayer();

    virtual oboe::DataCallbackResult onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) override ;
    virtual void onErrorAfterClose(oboe::AudioStream *oboeStream, oboe::Result error) override;
    virtual void onErrorBeforeClose(oboe::AudioStream * oboeStream, oboe::Result error) override;

    virtual int addSource(const std::string& sourcePath) override;
    void setRenderer(std::function<void(float*, float*, int)> renderer);
private:
    std::function<void(float*, float*, int)> renderer;
    float* output;
};


#endif //SORIWA_CUSTOMPLAYER_H
