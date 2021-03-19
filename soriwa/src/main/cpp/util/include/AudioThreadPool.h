//
// https://modoocode.com/285
//

#ifndef SORIWA_AUDIOTHREADPOOL_H
#define SORIWA_AUDIOTHREADPOOL_H

#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class AudioThreadPool {
public:
    AudioThreadPool(unsigned int size);
    ~AudioThreadPool();

    void EnqueueJob(std::function<void()> job);
private:
    void Run();

    unsigned int size;
    bool isFinish;

    std::vector<std::thread> threads;
    std::queue<std::function<void()>> jobs;
    std::condition_variable cv;
    std::mutex mut;
};



#endif //SORIWA_AUDIOTHREADPOOL_H
