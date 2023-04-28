#include <QtMultimedia>
#include "audio-lv.h"
#include <thread>


int32_t audio_write(int32_t dev_id, int32_t sr, float *pcm, int32_t samples) {

    QList<QAudioDevice> devs = QMediaDevices::audioOutputs();

    for (auto d: devs ) {
        qDebug() << d.description();
    }
    QAudioDevice dev = devs[dev_id];
    QAudioFormat format = dev.preferredFormat();
    format.setSampleFormat(QAudioFormat::SampleFormat::Float);
    format.setSampleRate(sr);
    format.setChannelCount(1);

    if(!dev.isFormatSupported(format)) {
        return -1;
    }

    QAudioSink sink(dev, format);

    sink.setBufferSize(samples*4);
    QIODevice *buffer = sink.start();

    uint32_t count = buffer->write((char*) pcm, samples*4);

    while(sink.bytesFree()+7 < samples*4){
         std::this_thread::yield();
        //qDebug() << sink.bytesFree() << samples*4 ;
    }

    sink.stop();
    return count;

}
