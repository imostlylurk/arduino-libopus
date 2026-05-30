/* celt_stubs.c - minimal CELT stubs for SILK-only build.
   Provides just enough to link: a dummy CELTMode with window/overlap,
   and no-op encoder/decoder functions. */

#if defined(HAVE_CONFIG_H) || defined(ARDUINO)
#include "opus_config.h"
#endif

/* Define CELT_C so we get the global_stack/scratch_ptr definitions and celt_fatal */
#define CELT_C

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "celt.h"
#include "modes.h"
#include "os_support.h"
#include "stack_alloc.h"
#include "mathops.h"

/* Dummy window: 120 samples of sine-squared window at 48kHz (2.5ms overlap).
   This is enough for gain_fade / stereo_fade to not crash. */
#define DUMMY_OVERLAP 120
static opus_val16 dummy_window[DUMMY_OVERLAP];

/* The single global dummy mode */
static CELTMode dummy_mode_instance;
static int dummy_mode_initialized = 0;

static void dummy_mode_init(void)
{
   int i;
   if (dummy_mode_initialized) return;
   dummy_mode_initialized = 1;
   OPUS_CLEAR(&dummy_mode_instance, 1);
   dummy_mode_instance.Fs = 48000;
   dummy_mode_instance.overlap = DUMMY_OVERLAP;
   dummy_mode_instance.window = dummy_window;
   /* Create a simple sine-squared window */
   for (i = 0; i < DUMMY_OVERLAP; i++)
   {
#ifdef FIXED_POINT
      dummy_window[i] = FRAC_MUL16(32767, celt_cos_norm(65536 - (opus_int32)((opus_int32)(2*i+1) * 32768 / DUMMY_OVERLAP)));
#else
      dummy_window[i] = (opus_val16)sin(3.14159265f * (i + 0.5f) / DUMMY_OVERLAP);
#endif
   }
}

/* Encoder stubs */
typedef struct {
   int dummy;
} CELTEncoderStub;

int celt_encoder_get_size(int channels)
{
   (void)channels;
   return sizeof(CELTEncoderStub);
}

int celt_encoder_init(CELTEncoder *st, opus_int32 sampling_rate, int channels, int arch)
{
   (void)st; (void)sampling_rate; (void)channels; (void)arch;
   return OPUS_OK;
}

int celt_encode_with_ec(CELTEncoder *st, const opus_val16 *pcm, int frame_size,
   unsigned char *compressed, int nbCompressedBytes, ec_enc *enc)
{
   (void)st; (void)pcm; (void)frame_size; (void)compressed;
   (void)nbCompressedBytes; (void)enc;
   return 0;
}

int celt_encoder_ctl(CELTEncoder *st, int request, ...)
{
   va_list ap;
   va_start(ap, request);
   (void)st;
   switch(request) {
      case CELT_GET_MODE_REQUEST:
      {
         const CELTMode **mode = va_arg(ap, const CELTMode**);
         dummy_mode_init();
         if (mode) *mode = &dummy_mode_instance;
         break;
      }
      case OPUS_GET_FINAL_RANGE_REQUEST:
      {
         opus_uint32 *rng = va_arg(ap, opus_uint32*);
         if (rng) *rng = 0;
         break;
      }
      default:
         break;
   }
   va_end(ap);
   return OPUS_OK;
}

/* Decoder stubs */
typedef struct {
   int dummy;
} CELTDecoderStub;

int celt_decoder_get_size(int channels)
{
   (void)channels;
   return sizeof(CELTDecoderStub);
}

int celt_decoder_init(CELTDecoder *st, opus_int32 sampling_rate, int channels)
{
   (void)st; (void)sampling_rate; (void)channels;
   return OPUS_OK;
}

int celt_decode_with_ec(CELTDecoder *st, const unsigned char *data,
   int len, opus_val16 *pcm, int frame_size, ec_dec *dec, int accum)
{
   (void)st; (void)data; (void)len; (void)pcm; (void)frame_size;
   (void)dec; (void)accum;
   return 0;
}

int celt_decoder_ctl(CELTDecoder *st, int request, ...)
{
   va_list ap;
   va_start(ap, request);
   (void)st;
   switch(request) {
      case CELT_GET_MODE_REQUEST:
      {
         const CELTMode **mode = va_arg(ap, const CELTMode**);
         dummy_mode_init();
         if (mode) *mode = &dummy_mode_instance;
         break;
      }
      default:
         break;
   }
   va_end(ap);
   return OPUS_OK;
}

/* opus_strerror was in celt.c which we removed */
const char *opus_strerror(int error)
{
   static const char * const error_strings[] = {
      "success",
      "invalid argument",
      "buffer too small",
      "internal error",
      "corrupted stream",
      "request not implemented",
      "invalid state",
      "memory allocation error",
      "generic error"
   };
   if (error >= 0 && error < (int)(sizeof(error_strings)/sizeof(error_strings[0])))
      return error_strings[error];
   return "unknown error";
}
