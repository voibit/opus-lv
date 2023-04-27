#ifndef OPUS_LV
#define OPUS_LV

#include <stdint.h>
#include <stdio.h>

int32_t encode_state_size();
int32_t encode_init(uint8_t *state, int32_t fs, int32_t bitrate);
int32_t encode(uint8_t *state, const float *pcm, int32_t pcm_size, int32_t frame_size, uint8_t *data, int32_t max_data_bytes);
int32_t decode_state_size();
int32_t decode_init(uint8_t *state, int32_t fs, int32_t bitrate);
int32_t decode(uint8_t *state, const uint8_t *data,  int32_t data_bytes, int16_t *pcm, int32_t frame_size, int32_t fec);

#endif
