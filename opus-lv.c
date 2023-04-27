#include "opus-lv.h"



int32_t encode_state_size() {
    return opus_encoder_get_size(1);
}

int32_t encode_init(uint8_t *state, int32_t fs, int32_t bitrate) {
    OpusEncoder *enc = (OpusEncoder *) state;
    int32_t ret = opus_encoder_init(enc, fs, 1, OPUS_APPLICATION_VOIP);

    if (ret == OPUS_OK && bitrate!=0 ) {
        opus_encoder_ctl(enc, OPUS_SET_VBR(0));
        ret = opus_encoder_ctl(enc, OPUS_SET_BITRATE(bitrate));
    }
    return ret == OPUS_OK;
}

int32_t encode(uint8_t *state, const float *pcm, int32_t pcm_size, int32_t frame_size, uint8_t *data, int32_t max_data_bytes) {
    OpusEncoder *enc = (OpusEncoder *) state;
    int32_t done = 0;
    int32_t frames = pcm_size / frame_size;
    for (int32_t i = 0;i <frames; i++) {
        int32_t res =  opus_encode_float(enc, pcm+i*frames, frame_size, data+done, max_data_bytes-done);
        if (res<0) return res;
        done += res;
    }

    return done;
}


int32_t decode_state_size() {
    return opus_decoder_get_size(1);
}

int32_t decode_init(uint8_t *state, int32_t fs, int32_t bitrate) {
    OpusDecoder *dec = (OpusDecoder *) state;

    int32_t ret = opus_decoder_init(dec, fs, 1);
    if (ret == OPUS_OK && bitrate!=0 ) {
        ret = opus_decoder_ctl(dec, OPUS_SET_BITRATE(bitrate));
    }
    return ret == OPUS_OK;
}

int32_t decode(uint8_t *state, const uint8_t *data,  int32_t data_bytes, float *pcm, int32_t frame_size, int32_t fec) {
    OpusDecoder *dec = (OpusDecoder *) state;
    return opus_decode_float(dec, data, data_bytes, pcm, frame_size,fec);
}



