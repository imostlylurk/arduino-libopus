/* silk_stubs.c - stubs for stereo SILK functions removed for mono-only build.
   When ENCODER_NUM_CHANNELS=1 and DECODER_NUM_CHANNELS=1, stereo code paths
   are never taken but the linker still needs these symbols. */

#if defined(HAVE_CONFIG_H) || defined(ARDUINO)
#include "opus_config.h"
#endif

#include "main.h"
#include "structs.h"
#include "entenc.h"
#include "entdec.h"

/* Convert Left/Right stereo signal to adaptive Mid/Side representation */
void silk_stereo_LR_to_MS(
    stereo_enc_state            *state,
    opus_int16                  x1[],
    opus_int16                  x2[],
    opus_int8                   ix[ 2 ][ 3 ],
    opus_int8                   *mid_only_flag,
    opus_int32                  mid_side_rates_bps[],
    opus_int32                  total_rate_bps,
    opus_int                    prev_speech_act_Q8,
    opus_int                    toMono,
    opus_int                    fs_kHz,
    opus_int                    frame_length
)
{
   (void)state; (void)x1; (void)x2; (void)ix; (void)mid_only_flag;
   (void)mid_side_rates_bps; (void)total_rate_bps; (void)prev_speech_act_Q8;
   (void)toMono; (void)fs_kHz; (void)frame_length;
}

/* Convert adaptive Mid/Side representation to Left/Right stereo signal */
void silk_stereo_MS_to_LR(
    stereo_dec_state            *state,
    opus_int16                  x1[],
    opus_int16                  x2[],
    const opus_int32            pred_Q13[],
    opus_int                    fs_kHz,
    opus_int                    frame_length
)
{
   (void)state; (void)x1; (void)x2; (void)pred_Q13;
   (void)fs_kHz; (void)frame_length;
}

/* Find least-squares prediction gain */
opus_int32 silk_stereo_find_predictor(
    opus_int32                  *ratio_Q14,
    const opus_int16            x[],
    const opus_int16            y[],
    opus_int32                  mid_res_amp_Q0[],
    opus_int                    length,
    opus_int                    smooth_coef_Q16
)
{
   (void)ratio_Q14; (void)x; (void)y; (void)mid_res_amp_Q0;
   (void)length; (void)smooth_coef_Q16;
   return 0;
}

/* Quantize mid/side predictors */
void silk_stereo_quant_pred(
    opus_int32                  pred_Q13[],
    opus_int8                   ix[ 2 ][ 3 ]
)
{
   (void)pred_Q13; (void)ix;
}

/* Entropy code the mid/side quantization indices */
void silk_stereo_encode_pred(
    ec_enc                      *psRangeEnc,
    opus_int8                   ix[ 2 ][ 3 ]
)
{
   (void)psRangeEnc; (void)ix;
}

/* Entropy code the mid-only flag */
void silk_stereo_encode_mid_only(
    ec_enc                      *psRangeEnc,
    opus_int8                   mid_only_flag
)
{
   (void)psRangeEnc; (void)mid_only_flag;
}

/* Decode mid/side predictors */
void silk_stereo_decode_pred(
    ec_dec                      *psRangeDec,
    opus_int32                  pred_Q13[]
)
{
   (void)psRangeDec; (void)pred_Q13;
}

/* Decode mid-only flag */
void silk_stereo_decode_mid_only(
    ec_dec                      *psRangeDec,
    opus_int                    *decode_only_mid
)
{
   (void)psRangeDec;
   if (decode_only_mid) *decode_only_mid = 0;
}
