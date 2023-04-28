#include "opus-lv.h"
#include "opus.h"

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

int32_t encode(uint8_t *state, const float *pcm, int32_t samples, int32_t frame_size, uint8_t *data, int32_t max_data_bytes) {
    OpusEncoder *enc = (OpusEncoder *) state;
    int32_t done = 0;
    int32_t frames = samples / frame_size;
    for (int32_t i = 0;i <frames; i++) {
        int32_t res =  opus_encode_float(enc, pcm+i*frame_size, frame_size, data+done, max_data_bytes-done);
        if (res<0) return res;
        done += res;
    }

    return done;
}


int32_t decode_state_size() {
    return opus_decoder_get_size(1);
}

int32_t decode_init(uint8_t *state, int32_t fs) {
    OpusDecoder *dec = (OpusDecoder *) state;

    /*
    opus_decoder_ctl(dec, OPUS_SET_VBR(0));
    opus_decoder_ctl(dec, OPUS_SET_BITRATE(48000));
    */

    int32_t ret = opus_decoder_init(dec, fs, 1);
    return ret == OPUS_OK;
}



int32_t decode(uint8_t *state,
               const uint8_t *data,
               int32_t data_bytes,
               int32_t bytes_per_frame,
               float *pcm,
               int32_t pcm_samples,
               int32_t fec)
{

    OpusDecoder *dec = (OpusDecoder *) state;
    int32_t done = 0;
    int32_t frames = data_bytes / bytes_per_frame;

    int32_t max_frame_size;
    opus_decoder_ctl(dec,OPUS_GET_SAMPLE_RATE(&max_frame_size));
    max_frame_size /1000*60;

    for (int32_t i = 0;i <frames; i++) {
        int32_t res =  opus_decode_float(dec,
                                        data+i*bytes_per_frame,
                                        bytes_per_frame,
                                        pcm+done,
                                        pcm_samples-done,
                                        fec);
        if (res<0) return res;
        done += res;
    }

    return done;

}
