//
// Created by newstone 2021-03-13.
//

#include <cstdint>
#include <limits>
#include <android/log.h>
#include <vector>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
}
#include "FfmpegDecoder.h"

template <typename T>
constexpr double normalize (T value) {
    return value < 0
           ? -static_cast<double>(value) / std::numeric_limits<T>::min()
           :  static_cast<double>(value) / std::numeric_limits<T>::max()
            ;
}

FfmpegDecoder::FfmpegDecoder() {
}

FfmpegDecoder::~FfmpegDecoder() {
}

int FfmpegDecoder::getAudioStream(const std::string& filePath, float*& outputBuffer, int& channels, int& sampleRate, int& bitsPerSample, unsigned long long& length) {

    AVFormatContext* avFormatContext = nullptr;
    AVStream* avAudioStream = nullptr;
    AVCodecContext* avCodecContext = nullptr;
    AVFrame* avFrame = nullptr;
    int streamIndex = -1;
    char errbuf[128];

    av_register_all();
    avFrame = av_frame_alloc();
    if (!avFrame) {
        __android_log_print(ANDROID_LOG_DEBUG, "[FFmpeg Decoder]", "%s" ,"Error allocating the frame");
        return 1;
    }

    avFormatContext = NULL;
    int err = avformat_open_input(&avFormatContext, filePath.c_str(), NULL, NULL);
    if (err != 0) {
        av_strerror(err, errbuf, sizeof(errbuf));
        __android_log_print(ANDROID_LOG_DEBUG, "[FFmpeg Decoder]", "Error open the avformat(%s) - %s", errbuf, filePath.c_str());
        av_free(avFrame);
        return 1;
    }

    err = avformat_find_stream_info(avFormatContext, NULL);
    if (err < 0) {
        av_strerror(err, errbuf, sizeof(errbuf));
        __android_log_print(ANDROID_LOG_DEBUG, "[FFmpeg Decoder]", "Error finding the stream info(%s)", errbuf);
        av_free(avFrame);
        avformat_close_input(&avFormatContext);
        return 1;
    }

    // Find the audio stream
    AVCodec* cdc = nullptr;
    streamIndex = av_find_best_stream(avFormatContext, AVMEDIA_TYPE_AUDIO, -1, -1, &cdc, 0);
    if (streamIndex < 0) {
        av_strerror(streamIndex, errbuf, sizeof(errbuf));
        __android_log_print(ANDROID_LOG_DEBUG, "[FFmpeg Decoder]", "Could not find any audio stream in the file(%s)", errbuf);
        av_free(avFrame);
        avformat_close_input(&avFormatContext);
        return 1;
    }

    avAudioStream = avFormatContext->streams[streamIndex];
    avCodecContext = avAudioStream->codec;
    avCodecContext->codec = cdc;

    err = avcodec_open2(avCodecContext, avCodecContext->codec, NULL);
    if (err != 0) {
        av_strerror(err, errbuf, sizeof(errbuf));
        __android_log_print(ANDROID_LOG_DEBUG, "[FFmpeg Decoder]", "Couldn't open the context with the decoder(%s)", errbuf);
        av_free(avFrame);
        avformat_close_input(&avFormatContext);
        __android_log_print(ANDROID_LOG_DEBUG, "[FFmpeg Decoder]", "%s" ,"Couldn't open the context with the decoder");
        return 1;
    }

    channels = avCodecContext->channels;
    sampleRate = avCodecContext->sample_rate;
    length = static_cast<unsigned long long>((avFormatContext->duration / static_cast<float>(AV_TIME_BASE)) * sampleRate);
    void* tempBuffer = nullptr;
    AVSampleFormat sampleFormat = avCodecContext->sample_fmt;
    bitsPerSample = 32; //
    if (sampleFormat == AV_SAMPLE_FMT_S16 || sampleFormat == AV_SAMPLE_FMT_S16P) {
        tempBuffer = new short[channels * length];
    } else if(sampleFormat == AV_SAMPLE_FMT_S32 || sampleFormat == AV_SAMPLE_FMT_S32P) {
        tempBuffer = new int[channels * length];
    }
    //2. Decode
    outputBuffer = new float[channels * length];

    AVPacket readingPacket;
    av_init_packet(&readingPacket);
    unsigned long long idx = 0;

    while (av_read_frame(avFormatContext, &readingPacket) >= 0) {
        if(readingPacket.stream_index == streamIndex) {
            int gotFrame = 0;
            if (avcodec_decode_audio4(avCodecContext, avFrame, &gotFrame, &readingPacket) < 1) {
                __android_log_print(ANDROID_LOG_DEBUG, "[FFmpeg Decoder]", "Error in decoding.");
                continue;
            }

            if(gotFrame) {
                if(sampleFormat == AV_SAMPLE_FMT_S16P) {
                    for(int i = 0; i < avFrame->nb_samples; i++, idx++) {
                        for(int ch = 0; ch < channels; ++ch) {
                            static_cast<short*>(tempBuffer)[channels * idx + ch] = reinterpret_cast<short*>(avFrame->extended_data[ch])[i];
                        }
                    }
                } else if(sampleFormat == AV_SAMPLE_FMT_S16) {
                    short* shortBuffer = (short*)avFrame->extended_data[0];
                    memcpy(static_cast<short*>(tempBuffer) + (idx * channels), shortBuffer, avFrame->nb_samples * channels * sizeof(short));
                    idx += avFrame->nb_samples;
                }
                else if(sampleFormat == AV_SAMPLE_FMT_FLTP) {
                    for(int i = 0; i < avFrame->nb_samples; i++, idx++) {
                        for(int ch = 0; ch < channels; ++ch) {
                            outputBuffer[channels * idx + ch] = reinterpret_cast<float*>(avFrame->extended_data[ch])[i];
                        }
                    }
                } else if(sampleFormat == AV_SAMPLE_FMT_FLT) {
                    float* floatBuffer = (float*)avFrame->extended_data[0];
                    memcpy(static_cast<float*>(outputBuffer) + (idx * channels), floatBuffer, avFrame->nb_samples * channels * sizeof(float));
                    idx += avFrame->nb_samples;
                }
                else if(sampleFormat == AV_SAMPLE_FMT_S32P) {
                    for(int i = 0; i < avFrame->nb_samples; i++, idx++) {
                        for(int ch = 0; ch < channels; ++ch) {
                            static_cast<int*>(tempBuffer)[channels * idx + ch] = reinterpret_cast<int*>(avFrame->extended_data[ch])[i];
                        }
                    }
                } else if(sampleFormat == AV_SAMPLE_FMT_S32) {
                    int* intBuffer = (int*)avFrame->extended_data[0];
                    memcpy(static_cast<int*>(tempBuffer) + (idx * channels), intBuffer, avFrame->nb_samples * channels * sizeof(int));
                    idx += avFrame->nb_samples;
                }
            }
        }
    }

    if (sampleFormat == AV_SAMPLE_FMT_S16 || sampleFormat == AV_SAMPLE_FMT_S16P) {
        for(unsigned long long i = 0; i < length * channels; ++i) {
            outputBuffer[i] = normalize<short>(static_cast<short*>(tempBuffer)[i]);
        }
        delete[] tempBuffer;
    } else if(sampleFormat == AV_SAMPLE_FMT_S32 || sampleFormat == AV_SAMPLE_FMT_S32P) {
        for(unsigned long long i = 0; i < length * channels; ++i) {
            outputBuffer[i] = normalize<int>(static_cast<int*>(tempBuffer)[i]);
        }
        delete[] tempBuffer;
    }

    //3. Cleanup FFmpeg
    if (avFrame) {
        av_free(avFrame);
        avFrame = nullptr;
    }
    if (avCodecContext) {
        avcodec_close(avCodecContext);
        avCodecContext = nullptr;
    }
    if (avFormatContext) {
        avformat_close_input(&avFormatContext);
        avFormatContext = nullptr;
    }
    return 0;
}