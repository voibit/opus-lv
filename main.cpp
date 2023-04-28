#include "opus-lv.h"
#include "audio-lv.h"
#include <stdio.h>
#include <random>

#include <QDebug>

int main() {
    size_t n = encode_state_size();
    uint8_t *enc_state = new uint8_t[n];
    encode_init(enc_state,48000,48000);



    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<> d{0, 0.2};
    float data[48000];
    for (size_t i=0; i< 48000; i++) {
        data[i] = d(gen);
    }

    qDebug() << "audio" << audio_write(0,44100,data, 44100);


    uint8_t bytes[6000];
    memset(bytes,0,1920 );


    int frames = 50;

    qDebug() << "encode" << encode(enc_state,data,48000,960, bytes, 6000);



    uint8_t *dec_state = new uint8_t[decode_state_size()];
    qDebug() << "decode init" << decode_init(dec_state,48000);
    qDebug() << "decode" << decode(dec_state,bytes,6000,120,data,48000,0);




    return 0;
}
