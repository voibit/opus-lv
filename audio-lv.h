#ifndef AUDIO
#define AUDIO
#include <stdint.h>


int32_t audio_write(int32_t dev_id, int32_t sr, float *pcm, int32_t samples);

#endif
