//
// https://modoocode.com/285
//

#include <android/log.h>
#include "AudioThreadPool.h"

AudioThreadPool::AudioThreadPool(unsigned int size) : size(size), isFinish(false) {
    threads.reserve(size);
    for(unsigned int i = 0; i < size; ++i) {
        threads.emplace_back([this]() { this->Run(); });
    }
}
AudioThreadPool::~AudioThreadPool() {
    isFinish = false;
    cv.notify_all();

    for(auto& t: threads) {
        t.join();
    }
}

void AudioThreadPool::Run() {
    while(true) {
        std::unique_lock<std::mutex> lock(mut);
        cv.wait(lock, [this]() { return !this->jobs.empty() || isFinish; });

        if(isFinish && this->jobs.empty()) {
            return;
        }

        std::function<void()> job = std::move(jobs.front());
        jobs.pop();
        lock.unlock();

        job();
    }
}

void AudioThreadPool::EnqueueJob(std::function<void()> job) {
    if(isFinish) {
        __android_log_print(ANDROID_LOG_DEBUG, "AudioThreadPool", "Stop Audio Thread Pool!!");
        return;
    }
    {
        std::lock_guard<std::mutex> lock(mut);
        jobs.push(std::move(job));
    }
    cv.notify_one();
}