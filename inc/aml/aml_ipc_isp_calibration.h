/*
 * Copyright (C) 2014-2019 Amlogic, Inc. All rights reserved.
 *
 * All information contained herein is Amlogic confidential.
 *
 * This software is provided to you pursuant to Software License Agreement
 * (SLA) with Amlogic Inc ("Amlogic"). This software may be used
 * only in accordance with the terms of this agreement.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification is strictly prohibited without prior written permission from
 * Amlogic.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef AML_IPC_ISP_CALIBRATION_H

#define AML_IPC_ISP_CALIBRATION_H

#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
    uint16_t total_gain;
    uint16_t lm_med_noise_intensity_thresh;
} calibration_stitching_lm_med_noise_intensity_thresh_t[9];
AmlStatus aml_ipc_isp_get_calibration_stitching_lm_med_noise_intensity_thresh(
    struct AmlIPCISP *isp, calibration_stitching_lm_med_noise_intensity_thresh_t param);
AmlStatus aml_ipc_isp_set_calibration_stitching_lm_med_noise_intensity_thresh(
    struct AmlIPCISP *isp, calibration_stitching_lm_med_noise_intensity_thresh_t param);

typedef struct {
    uint16_t High_CT;
    uint16_t Mid_CT1;
    uint16_t Mid_CT2;
    uint16_t Low_CT;
} AWB_colour_preference_t[1];
AmlStatus aml_ipc_isp_get_AWB_colour_preference(struct AmlIPCISP *isp,
                                                AWB_colour_preference_t param);
AmlStatus aml_ipc_isp_set_AWB_colour_preference(struct AmlIPCISP *isp,
                                                AWB_colour_preference_t param);

typedef struct {
    uint32_t enable;
    uint32_t lux_low_boundary;
    uint32_t lux_high_boundary;
    uint32_t contrast_threshold;
    uint32_t BG_threshold;
    uint32_t BG_weight;
    uint32_t rgHigh_LUT_max;
    uint32_t rgHigh_LUT_min;
    uint32_t print_debug;
} calibration_awb_mix_light_parameters_t[1];
AmlStatus
aml_ipc_isp_get_calibration_awb_mix_light_parameters(struct AmlIPCISP *isp,
                                                     calibration_awb_mix_light_parameters_t param);
AmlStatus
aml_ipc_isp_set_calibration_awb_mix_light_parameters(struct AmlIPCISP *isp,
                                                     calibration_awb_mix_light_parameters_t param);
typedef uint8_t calibration_pf_radial_lut_array_t[33];
AmlStatus aml_ipc_isp_get_calibration_pf_radial_lut_array(struct AmlIPCISP *isp,
                                                          calibration_pf_radial_lut_array_t param);
AmlStatus aml_ipc_isp_set_calibration_pf_radial_lut_array(struct AmlIPCISP *isp,
                                                          calibration_pf_radial_lut_array_t param);

typedef struct {
    uint16_t rm_centre_x;
    uint16_t rm_centre_y;
    uint16_t rm_off_centre_mult;
} calibration_pf_radial_params_t[1];
AmlStatus aml_ipc_isp_get_calibration_pf_radial_params(struct AmlIPCISP *isp,
                                                       calibration_pf_radial_params_t param);
AmlStatus aml_ipc_isp_set_calibration_pf_radial_params(struct AmlIPCISP *isp,
                                                       calibration_pf_radial_params_t param);

typedef uint8_t calibration_sinter_radial_lut_t[33];
AmlStatus aml_ipc_isp_get_calibration_sinter_radial_lut(struct AmlIPCISP *isp,
                                                        calibration_sinter_radial_lut_t param);
AmlStatus aml_ipc_isp_set_calibration_sinter_radial_lut(struct AmlIPCISP *isp,
                                                        calibration_sinter_radial_lut_t param);

typedef struct {
    uint16_t rm_enable;
    uint16_t rm_centre_x;
    uint16_t rm_centre_y;
    uint16_t rm_off_centre_mult;
} calibration_sinter_radial_params_t[1];
AmlStatus
aml_ipc_isp_get_calibration_sinter_radial_params(struct AmlIPCISP *isp,
                                                 calibration_sinter_radial_params_t param);
AmlStatus
aml_ipc_isp_set_calibration_sinter_radial_params(struct AmlIPCISP *isp,
                                                 calibration_sinter_radial_params_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t AWB_bg_max_gain;
} calibration_AWB_bg_max_gain_t[9];
AmlStatus aml_ipc_isp_get_calibration_AWB_bg_max_gain(struct AmlIPCISP *isp,
                                                      calibration_AWB_bg_max_gain_t param);
AmlStatus aml_ipc_isp_set_calibration_AWB_bg_max_gain(struct AmlIPCISP *isp,
                                                      calibration_AWB_bg_max_gain_t param);

typedef struct {
    uint32_t dark_prc;
    uint32_t bright_prc;
    uint32_t min_dk;
    uint32_t max_dk;
    uint32_t pD_cut_min;
    uint32_t pD_cut_max;
    uint32_t dark_contrast_min;
    uint32_t dark_contrast_max;
    uint32_t min_str;
    uint32_t max_str;
    uint32_t dark_prc_gain_target;
    uint32_t contrast_min;
    uint32_t contrast_max;
    uint32_t max_iridix_gain;
    uint32_t print_debug;
} calibration_iridix8_strength_dk_enh_control_t[1];
AmlStatus aml_ipc_isp_get_calibration_iridix8_strength_dk_enh_control(
    struct AmlIPCISP *isp, calibration_iridix8_strength_dk_enh_control_t param);
AmlStatus aml_ipc_isp_set_calibration_iridix8_strength_dk_enh_control(
    struct AmlIPCISP *isp, calibration_iridix8_strength_dk_enh_control_t param);
typedef struct {
    uint32_t enable_antiflicker;
    uint32_t antiflicker_frequency;
    uint32_t manual_integration_time;
    uint32_t manual_sensor_analog_gain;
    uint32_t manual_sensor_digital_gain;
    uint32_t manual_isp_digital_gain;
    uint32_t manual_max_integration_time;
    uint32_t max_integration_time;
    uint32_t max_sensor_AG;
    uint32_t max_sensor_DG;
    uint32_t max_isp_DG;
    uint32_t max_exposure_ratio;
    uint32_t integration_time;
    uint32_t sensor_analog_gain_log2;
    uint32_t sensor_digital_gain_log2;
    uint32_t isp_digital_gain_log2;
    uint32_t analog_gain_last_priority;
    uint32_t analog_gain_reserve;
} calibration_cmos_control_t[1];
AmlStatus aml_ipc_isp_get_calibration_cmos_control(struct AmlIPCISP *isp,
                                                   calibration_cmos_control_t param);
AmlStatus aml_ipc_isp_set_calibration_cmos_control(struct AmlIPCISP *isp,
                                                   calibration_cmos_control_t param);
typedef struct {
    uint32_t total_gain_log2;
    uint32_t expsoure_log2;
    uint32_t mix_light_contrast;
    uint32_t cur_lens_pos;
    uint32_t cur_focus_value;
} calibration_status_info_t[1];
AmlStatus aml_ipc_isp_get_calibration_status_info(struct AmlIPCISP *isp,
                                                  calibration_status_info_t param);
AmlStatus aml_ipc_isp_set_calibration_status_info(struct AmlIPCISP *isp,
                                                  calibration_status_info_t param);
typedef struct {
    uint32_t black_percentage;
    uint32_t white_percentage;
    uint32_t auto_black_min;
    uint32_t auto_black_max;
    uint32_t auto_white_prc;
    uint32_t avg_coeff;
    uint32_t enable_auto_level;
} calibration_auto_level_control_t[1];
AmlStatus aml_ipc_isp_get_calibration_auto_level_control(struct AmlIPCISP *isp,
                                                         calibration_auto_level_control_t param);
AmlStatus aml_ipc_isp_set_calibration_auto_level_control(struct AmlIPCISP *isp,
                                                         calibration_auto_level_control_t param);
typedef struct {
    uint16_t total_gain;
    uint16_t dp_slope;
} calibration_dp_slope_t[9];
AmlStatus aml_ipc_isp_get_calibration_dp_slope(struct AmlIPCISP *isp, calibration_dp_slope_t param);
AmlStatus aml_ipc_isp_set_calibration_dp_slope(struct AmlIPCISP *isp, calibration_dp_slope_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t dp_threshold;
} calibration_dp_threshold_t[9];
AmlStatus aml_ipc_isp_get_calibration_dp_threshold(struct AmlIPCISP *isp,
                                                   calibration_dp_threshold_t param);
AmlStatus aml_ipc_isp_set_calibration_dp_threshold(struct AmlIPCISP *isp,
                                                   calibration_dp_threshold_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t stitching_lm_mov_mult;
} calibration_stitching_lm_mov_mult_t[9];
AmlStatus
aml_ipc_isp_get_calibration_stitching_lm_mov_mult(struct AmlIPCISP *isp,
                                                  calibration_stitching_lm_mov_mult_t param);
AmlStatus
aml_ipc_isp_set_calibration_stitching_lm_mov_mult(struct AmlIPCISP *isp,
                                                  calibration_stitching_lm_mov_mult_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t stitching_lm_np;
} calibration_stitching_lm_np_t[9];
AmlStatus aml_ipc_isp_get_calibration_stitching_lm_np(struct AmlIPCISP *isp,
                                                      calibration_stitching_lm_np_t param);
AmlStatus aml_ipc_isp_set_calibration_stitching_lm_np(struct AmlIPCISP *isp,
                                                      calibration_stitching_lm_np_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t stitching_ms_mov_mult;
} calibration_stitching_ms_mov_mult_t[9];
AmlStatus
aml_ipc_isp_get_calibration_stitching_ms_mov_mult(struct AmlIPCISP *isp,
                                                  calibration_stitching_ms_mov_mult_t param);
AmlStatus
aml_ipc_isp_set_calibration_stitching_ms_mov_mult(struct AmlIPCISP *isp,
                                                  calibration_stitching_ms_mov_mult_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t stitching_ms_np;
} calibration_stitching_ms_np_t[9];
AmlStatus aml_ipc_isp_get_calibration_stitching_ms_np(struct AmlIPCISP *isp,
                                                      calibration_stitching_ms_np_t param);
AmlStatus aml_ipc_isp_set_calibration_stitching_ms_np(struct AmlIPCISP *isp,
                                                      calibration_stitching_ms_np_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t stitching_svs_mov_mult;
} calibration_stitching_svs_mov_mult_t[9];
AmlStatus
aml_ipc_isp_get_calibration_stitching_svs_mov_mult(struct AmlIPCISP *isp,
                                                   calibration_stitching_svs_mov_mult_t param);
AmlStatus
aml_ipc_isp_set_calibration_stitching_svs_mov_mult(struct AmlIPCISP *isp,
                                                   calibration_stitching_svs_mov_mult_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t stitching_svs_np;
} calibration_stitching_svs_np_t[9];
AmlStatus aml_ipc_isp_get_calibration_stitching_svs_np(struct AmlIPCISP *isp,
                                                       calibration_stitching_svs_np_t param);
AmlStatus aml_ipc_isp_set_calibration_stitching_svs_np(struct AmlIPCISP *isp,
                                                       calibration_stitching_svs_np_t param);

typedef uint8_t calibration_evtolux_probability_enable_t[1];
AmlStatus aml_ipc_isp_get_calibration_evtolux_probability_enable(
    struct AmlIPCISP *isp, calibration_evtolux_probability_enable_t param);
AmlStatus aml_ipc_isp_set_calibration_evtolux_probability_enable(
    struct AmlIPCISP *isp, calibration_evtolux_probability_enable_t param);

typedef uint8_t calibration_awb_avg_coef_t[1];
AmlStatus aml_ipc_isp_get_calibration_awb_avg_coef(struct AmlIPCISP *isp,
                                                   calibration_awb_avg_coef_t param);
AmlStatus aml_ipc_isp_set_calibration_awb_avg_coef(struct AmlIPCISP *isp,
                                                   calibration_awb_avg_coef_t param);

typedef uint8_t calibration_iridix_avg_coef_t[1];
AmlStatus aml_ipc_isp_get_calibration_iridix_avg_coef(struct AmlIPCISP *isp,
                                                      calibration_iridix_avg_coef_t param);
AmlStatus aml_ipc_isp_set_calibration_iridix_avg_coef(struct AmlIPCISP *isp,
                                                      calibration_iridix_avg_coef_t param);

typedef uint8_t calibration_iridix_strength_maximum_t[1];
AmlStatus
aml_ipc_isp_get_calibration_iridix_strength_maximum(struct AmlIPCISP *isp,
                                                    calibration_iridix_strength_maximum_t param);
AmlStatus
aml_ipc_isp_set_calibration_iridix_strength_maximum(struct AmlIPCISP *isp,
                                                    calibration_iridix_strength_maximum_t param);

typedef uint16_t calibration_iridix_min_max_str_t[1];
AmlStatus aml_ipc_isp_get_calibration_iridix_min_max_str(struct AmlIPCISP *isp,
                                                         calibration_iridix_min_max_str_t param);
AmlStatus aml_ipc_isp_set_calibration_iridix_min_max_str(struct AmlIPCISP *isp,
                                                         calibration_iridix_min_max_str_t param);

typedef uint32_t calibration_iridix_ev_lim_full_str_t[1];
AmlStatus
aml_ipc_isp_get_calibration_iridix_ev_lim_full_str(struct AmlIPCISP *isp,
                                                   calibration_iridix_ev_lim_full_str_t param);
AmlStatus
aml_ipc_isp_set_calibration_iridix_ev_lim_full_str(struct AmlIPCISP *isp,
                                                   calibration_iridix_ev_lim_full_str_t param);

typedef struct {
    uint32_t iridix_ev_lim_no_str_0;
    uint32_t iridix_ev_lim_no_str_1;
} calibration_iridix_ev_lim_no_str_t[1];
AmlStatus
aml_ipc_isp_get_calibration_iridix_ev_lim_no_str(struct AmlIPCISP *isp,
                                                 calibration_iridix_ev_lim_no_str_t param);
AmlStatus
aml_ipc_isp_set_calibration_iridix_ev_lim_no_str(struct AmlIPCISP *isp,
                                                 calibration_iridix_ev_lim_no_str_t param);

typedef uint8_t calibration_ae_correction_t[12];
AmlStatus aml_ipc_isp_get_calibration_ae_correction(struct AmlIPCISP *isp,
                                                    calibration_ae_correction_t param);
AmlStatus aml_ipc_isp_set_calibration_ae_correction(struct AmlIPCISP *isp,
                                                    calibration_ae_correction_t param);

typedef uint32_t calibration_ae_exposure_correction_t[12];
AmlStatus
aml_ipc_isp_get_calibration_ae_exposure_correction(struct AmlIPCISP *isp,
                                                   calibration_ae_exposure_correction_t param);
AmlStatus
aml_ipc_isp_set_calibration_ae_exposure_correction(struct AmlIPCISP *isp,
                                                   calibration_ae_exposure_correction_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t sinter_strength;
} calibration_sinter_strength_t[9];
AmlStatus aml_ipc_isp_get_calibration_sinter_strength(struct AmlIPCISP *isp,
                                                      calibration_sinter_strength_t param);
AmlStatus aml_ipc_isp_set_calibration_sinter_strength(struct AmlIPCISP *isp,
                                                      calibration_sinter_strength_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t sinter_strength1;
} calibration_sinter_strength1_t[9];
AmlStatus aml_ipc_isp_get_calibration_sinter_strength1(struct AmlIPCISP *isp,
                                                       calibration_sinter_strength1_t param);
AmlStatus aml_ipc_isp_set_calibration_sinter_strength1(struct AmlIPCISP *isp,
                                                       calibration_sinter_strength1_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t sinter_thresh1;
} calibration_sinter_thresh1_t[9];
AmlStatus aml_ipc_isp_get_calibration_sinter_thresh1(struct AmlIPCISP *isp,
                                                     calibration_sinter_thresh1_t param);
AmlStatus aml_ipc_isp_set_calibration_sinter_thresh1(struct AmlIPCISP *isp,
                                                     calibration_sinter_thresh1_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t sinter_thresh4;
} calibration_sinter_thresh4_t[9];
AmlStatus aml_ipc_isp_get_calibration_sinter_thresh4(struct AmlIPCISP *isp,
                                                     calibration_sinter_thresh4_t param);
AmlStatus aml_ipc_isp_set_calibration_sinter_thresh4(struct AmlIPCISP *isp,
                                                     calibration_sinter_thresh4_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t sinter_intConfig;
} calibration_sinter_intConfig_t[9];
AmlStatus aml_ipc_isp_get_calibration_sinter_intConfig(struct AmlIPCISP *isp,
                                                       calibration_sinter_intConfig_t param);
AmlStatus aml_ipc_isp_set_calibration_sinter_intConfig(struct AmlIPCISP *isp,
                                                       calibration_sinter_intConfig_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t sharp_alt_d;
} calibration_sharp_alt_d_t[9];
AmlStatus aml_ipc_isp_get_calibration_sharp_alt_d(struct AmlIPCISP *isp,
                                                  calibration_sharp_alt_d_t param);
AmlStatus aml_ipc_isp_set_calibration_sharp_alt_d(struct AmlIPCISP *isp,
                                                  calibration_sharp_alt_d_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t sharp_alt_ud;
} calibration_sharp_alt_ud_t[9];
AmlStatus aml_ipc_isp_get_calibration_sharp_alt_ud(struct AmlIPCISP *isp,
                                                   calibration_sharp_alt_ud_t param);
AmlStatus aml_ipc_isp_set_calibration_sharp_alt_ud(struct AmlIPCISP *isp,
                                                   calibration_sharp_alt_ud_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t sharp_alt_du;
} calibration_sharp_alt_du_t[9];
AmlStatus aml_ipc_isp_get_calibration_sharp_alt_du(struct AmlIPCISP *isp,
                                                   calibration_sharp_alt_du_t param);
AmlStatus aml_ipc_isp_set_calibration_sharp_alt_du(struct AmlIPCISP *isp,
                                                   calibration_sharp_alt_du_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t demosaic_np_offset;
} calibration_demosaic_np_offset_t[9];
AmlStatus aml_ipc_isp_get_calibration_demosaic_np_offset(struct AmlIPCISP *isp,
                                                         calibration_demosaic_np_offset_t param);
AmlStatus aml_ipc_isp_set_calibration_demosaic_np_offset(struct AmlIPCISP *isp,
                                                         calibration_demosaic_np_offset_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t mesh_shading_strength;
} calibration_mesh_shading_strength_t[9];
AmlStatus
aml_ipc_isp_get_calibration_mesh_shading_strength(struct AmlIPCISP *isp,
                                                  calibration_mesh_shading_strength_t param);
AmlStatus
aml_ipc_isp_set_calibration_mesh_shading_strength(struct AmlIPCISP *isp,
                                                  calibration_mesh_shading_strength_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t saturation_strength;
} calibration_saturation_strength_t[9];
AmlStatus aml_ipc_isp_get_calibration_saturation_strength(struct AmlIPCISP *isp,
                                                          calibration_saturation_strength_t param);
AmlStatus aml_ipc_isp_set_calibration_saturation_strength(struct AmlIPCISP *isp,
                                                          calibration_saturation_strength_t param);

typedef uint16_t calibration_ccm_one_gain_threshold_t[1];
AmlStatus
aml_ipc_isp_get_calibration_ccm_one_gain_threshold(struct AmlIPCISP *isp,
                                                   calibration_ccm_one_gain_threshold_t param);
AmlStatus
aml_ipc_isp_set_calibration_ccm_one_gain_threshold(struct AmlIPCISP *isp,
                                                   calibration_ccm_one_gain_threshold_t param);

typedef struct {
    uint16_t r_y_ratio;
    uint16_t g_y_ratio;
    uint16_t b_y_ratio;
    uint16_t rgb_y_offset;
    uint16_t r_u_ratio;
    uint16_t g_u_ratio;
    uint16_t b_u_ratio;
    uint16_t rgb_u_offset;
    uint16_t r_v_ratio;
    uint16_t g_v_ratio;
    uint16_t b_v_ratio;
    uint16_t rgb_v_offset;
} calibration_rgb2yuv_conversion_t[1];
AmlStatus aml_ipc_isp_get_calibration_rgb2yuv_conversion(struct AmlIPCISP *isp,
                                                         calibration_rgb2yuv_conversion_t param);
AmlStatus aml_ipc_isp_set_calibration_rgb2yuv_conversion(struct AmlIPCISP *isp,
                                                         calibration_rgb2yuv_conversion_t param);
typedef uint16_t calibration_ae_zone_wght_hor_t[34];
AmlStatus aml_ipc_isp_get_calibration_ae_zone_wght_hor(struct AmlIPCISP *isp,
                                                       calibration_ae_zone_wght_hor_t param);
AmlStatus aml_ipc_isp_set_calibration_ae_zone_wght_hor(struct AmlIPCISP *isp,
                                                       calibration_ae_zone_wght_hor_t param);

typedef uint16_t calibration_ae_zone_wght_ver_t[34];
AmlStatus aml_ipc_isp_get_calibration_ae_zone_wght_ver(struct AmlIPCISP *isp,
                                                       calibration_ae_zone_wght_ver_t param);
AmlStatus aml_ipc_isp_set_calibration_ae_zone_wght_ver(struct AmlIPCISP *isp,
                                                       calibration_ae_zone_wght_ver_t param);

typedef uint16_t calibration_awb_zone_wght_hor_t[34];
AmlStatus aml_ipc_isp_get_calibration_awb_zone_wght_hor(struct AmlIPCISP *isp,
                                                        calibration_awb_zone_wght_hor_t param);
AmlStatus aml_ipc_isp_set_calibration_awb_zone_wght_hor(struct AmlIPCISP *isp,
                                                        calibration_awb_zone_wght_hor_t param);

typedef uint16_t calibration_awb_zone_wght_ver_t[34];
AmlStatus aml_ipc_isp_get_calibration_awb_zone_wght_ver(struct AmlIPCISP *isp,
                                                        calibration_awb_zone_wght_ver_t param);
AmlStatus aml_ipc_isp_set_calibration_awb_zone_wght_ver(struct AmlIPCISP *isp,
                                                        calibration_awb_zone_wght_ver_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t sharpen_fr;
} calibration_sharpen_fr_t[9];
AmlStatus aml_ipc_isp_get_calibration_sharpen_fr(struct AmlIPCISP *isp,
                                                 calibration_sharpen_fr_t param);
AmlStatus aml_ipc_isp_set_calibration_sharpen_fr(struct AmlIPCISP *isp,
                                                 calibration_sharpen_fr_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t sharpen_ds1;
} calibration_sharpen_ds1_t[9];
AmlStatus aml_ipc_isp_get_calibration_sharpen_ds1(struct AmlIPCISP *isp,
                                                  calibration_sharpen_ds1_t param);
AmlStatus aml_ipc_isp_set_calibration_sharpen_ds1(struct AmlIPCISP *isp,
                                                  calibration_sharpen_ds1_t param);
typedef struct {
    uint16_t integration_time;
    uint16_t gain;
} calibration_cmos_exposure_partition_luts_t[20];
AmlStatus aml_ipc_isp_get_calibration_cmos_exposure_partition_luts(
    struct AmlIPCISP *isp, calibration_cmos_exposure_partition_luts_t param);
AmlStatus aml_ipc_isp_set_calibration_cmos_exposure_partition_luts(
    struct AmlIPCISP *isp, calibration_cmos_exposure_partition_luts_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t temper_strength;
} calibration_temper_strength_t[9];
AmlStatus aml_ipc_isp_get_calibration_temper_strength(struct AmlIPCISP *isp,
                                                      calibration_temper_strength_t param);
AmlStatus aml_ipc_isp_set_calibration_temper_strength(struct AmlIPCISP *isp,
                                                      calibration_temper_strength_t param);

typedef uint32_t scaler_h_filter_t[4 * 64];
AmlStatus aml_ipc_isp_get_scaler_h_filter(struct AmlIPCISP *isp, scaler_h_filter_t param);
AmlStatus aml_ipc_isp_set_scaler_h_filter(struct AmlIPCISP *isp, scaler_h_filter_t param);

typedef uint32_t scaler_v_filter_t[4 * 64];
AmlStatus aml_ipc_isp_get_scaler_v_filter(struct AmlIPCISP *isp, scaler_v_filter_t param);
AmlStatus aml_ipc_isp_set_scaler_v_filter(struct AmlIPCISP *isp, scaler_v_filter_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t lm_med_noise_intensity_thresh;
} calibration_sinter_strength_MC_contrast_t[9];
AmlStatus aml_ipc_isp_get_calibration_sinter_strength_MC_contrast(
    struct AmlIPCISP *isp, calibration_sinter_strength_MC_contrast_t param);
AmlStatus aml_ipc_isp_set_calibration_sinter_strength_MC_contrast(
    struct AmlIPCISP *isp, calibration_sinter_strength_MC_contrast_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t exposure_ratio_adjustment;
} calibration_exposure_ratio_adjustment_t[9];
AmlStatus aml_ipc_isp_get_calibration_exposure_ratio_adjustment(
    struct AmlIPCISP *isp, calibration_exposure_ratio_adjustment_t param);
AmlStatus aml_ipc_isp_set_calibration_exposure_ratio_adjustment(
    struct AmlIPCISP *isp, calibration_exposure_ratio_adjustment_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t cnr_uv_delta12_slope;
} calibration_cnr_uv_delta12_slope_t[9];
AmlStatus
aml_ipc_isp_get_calibration_cnr_uv_delta12_slope(struct AmlIPCISP *isp,
                                                 calibration_cnr_uv_delta12_slope_t param);
AmlStatus
aml_ipc_isp_set_calibration_cnr_uv_delta12_slope(struct AmlIPCISP *isp,
                                                 calibration_cnr_uv_delta12_slope_t param);

typedef struct {
    uint16_t gain_log2_threshold;
} calibration_fs_mc_off_t[1];
AmlStatus aml_ipc_isp_get_calibration_fs_mc_off(struct AmlIPCISP *isp,
                                                calibration_fs_mc_off_t param);
AmlStatus aml_ipc_isp_set_calibration_fs_mc_off(struct AmlIPCISP *isp,
                                                calibration_fs_mc_off_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t sinter_sad;
} calibration_sinter_sad_t[9];
AmlStatus aml_ipc_isp_get_calibration_sinter_sad(struct AmlIPCISP *isp,
                                                 calibration_sinter_sad_t param);
AmlStatus aml_ipc_isp_set_calibration_sinter_sad(struct AmlIPCISP *isp,
                                                 calibration_sinter_sad_t param);

typedef struct {
    uint16_t total_gain;
    uint16_t ae_control_HDR_target;
} calibration_ae_control_HDR_target_t[9];
AmlStatus
aml_ipc_isp_get_calibration_ae_control_HDR_target(struct AmlIPCISP *isp,
                                                  calibration_ae_control_HDR_target_t param);
AmlStatus
aml_ipc_isp_set_calibration_ae_control_HDR_target(struct AmlIPCISP *isp,
                                                  calibration_ae_control_HDR_target_t param);

typedef struct {
    uint32_t AE_convergance;
    uint32_t LDR_AE_target;
    uint32_t AE_tail_weight;
    uint32_t Max_percentage_WDR;
    uint32_t Time_filter_for_exposure_ratio_WDR;
    uint32_t bright_percentage_of_pixels;
    uint32_t hi_target_prc;
    uint32_t disable_iridix_global_gain;
    uint32_t AE_tolerance;
} calibration_ae_control_t[1];
AmlStatus aml_ipc_isp_get_calibration_ae_control(struct AmlIPCISP *isp,
                                                 calibration_ae_control_t param);
AmlStatus aml_ipc_isp_set_calibration_ae_control(struct AmlIPCISP *isp,
                                                 calibration_ae_control_t param);
typedef uint16_t calibration_gamma_ev1_t[129];
AmlStatus aml_ipc_isp_get_calibration_gamma_ev1(struct AmlIPCISP *isp,
                                                calibration_gamma_ev1_t param);
AmlStatus aml_ipc_isp_set_calibration_gamma_ev1(struct AmlIPCISP *isp,
                                                calibration_gamma_ev1_t param);

typedef uint16_t calibration_gamma_ev2_t[129];
AmlStatus aml_ipc_isp_get_calibration_gamma_ev2(struct AmlIPCISP *isp,
                                                calibration_gamma_ev2_t param);
AmlStatus aml_ipc_isp_set_calibration_gamma_ev2(struct AmlIPCISP *isp,
                                                calibration_gamma_ev2_t param);

typedef struct {
    uint32_t dual_gamma_enable;
    uint32_t dual_gamma_ev0;
    uint32_t dual_gamma_ev1;
} calibration_gamma_threshold_t[1];
AmlStatus aml_ipc_isp_get_calibration_gamma_threshold(struct AmlIPCISP *isp,
                                                      calibration_gamma_threshold_t param);
AmlStatus aml_ipc_isp_set_calibration_gamma_threshold(struct AmlIPCISP *isp,
                                                      calibration_gamma_threshold_t param);

typedef struct {
    uint32_t defog_enable;
    uint32_t defog_detect_mode;
    uint32_t acc_fog_value_threshhold;
    uint32_t hist_fog_idx_threshhold;
    uint32_t hist_fog_pec_threshhold_1;
    uint32_t hist_fog_pec_threshhold_2;
    uint32_t ratio_delta;
    uint32_t max_rng;
    uint32_t min_rng;
    uint32_t black_percentage;
    uint32_t white_percentage;
    uint32_t avg_coeff;
    uint32_t reserved1;
    uint32_t reserved2;
    uint32_t reserved3;
    uint32_t reserved4;
} calibration_defog_control_t[1];
AmlStatus aml_ipc_isp_get_calibration_defog_control(struct AmlIPCISP *isp,
                                                    calibration_defog_control_t param);
AmlStatus aml_ipc_isp_set_calibration_defog_control(struct AmlIPCISP *isp,
                                                    calibration_defog_control_t param);
typedef struct {
    uint32_t GAIN_LOG2_ID_mult_256;
    uint32_t lum_thresh;
    uint32_t sad_amp;
    uint32_t uu_sh_slope;
    uint32_t uu_sh_thresh;
    uint32_t luma_thresh_low_d;
    uint32_t luma_thresh_low_ud;
    uint32_t luma_slope_low_d;
    uint32_t luma_slope_low_ud;
    uint32_t luma_thresh_high_d;
    uint32_t luma_thresh_high_ud;
    uint32_t luma_slope_high_d;
    uint32_t luma_slope_high_ud;
} calibration_demosaic_rgb_extension_control_t[9];
AmlStatus aml_ipc_isp_get_calibration_demosaic_rgb_extension_control(
    struct AmlIPCISP *isp, calibration_demosaic_rgb_extension_control_t param);
AmlStatus aml_ipc_isp_set_calibration_demosaic_rgb_extension_control(
    struct AmlIPCISP *isp, calibration_demosaic_rgb_extension_control_t param);
typedef struct {
    uint32_t GAIN_LOG2_ID_mult_256;
    uint32_t alpha_undershoot;
    uint32_t luma_thresh_low;
    uint32_t luma_slope_low;
    uint32_t luma_thresh_high;
    uint32_t luma_slope_high;
} calibration_fr_sharpen_extension_control_t[9];
AmlStatus aml_ipc_isp_get_calibration_fr_sharpen_extension_control(
    struct AmlIPCISP *isp, calibration_fr_sharpen_extension_control_t param);
AmlStatus aml_ipc_isp_set_calibration_fr_sharpen_extension_control(
    struct AmlIPCISP *isp, calibration_fr_sharpen_extension_control_t param);
typedef struct {
    uint32_t GAIN_LOG2_ID_mult_256;
    uint32_t alpha_undershoot;
    uint32_t luma_thresh_low;
    uint32_t luma_slope_low;
    uint32_t luma_thresh_high;
    uint32_t luma_slope_high;
} calibration_ds_sharpen_extension_control_t[9];
AmlStatus aml_ipc_isp_get_calibration_ds_sharpen_extension_control(
    struct AmlIPCISP *isp, calibration_ds_sharpen_extension_control_t param);
AmlStatus aml_ipc_isp_set_calibration_ds_sharpen_extension_control(
    struct AmlIPCISP *isp, calibration_ds_sharpen_extension_control_t param);
typedef struct {
    uint32_t GAIN_LOG2_ID_mult_256;
    uint32_t delta_factor;
    uint32_t umean1_thd;
    uint32_t umean1_offset;
    uint32_t umean1_slope;
    uint32_t umean2_thd;
    uint32_t umean2_offset;
    uint32_t umean2_slope;
    uint32_t vmean1_thd;
    uint32_t vmean1_offset;
    uint32_t vmean1_slope;
    uint32_t vmean2_thd;
    uint32_t vmean2_offset;
    uint32_t vmean2_slope;
    uint32_t uv_delta1_thd;
    uint32_t uv_delta1_offset;
    uint32_t uv_delta1_slope;
    uint32_t uv_delta2_thd;
    uint32_t uv_delta2_offset;
    uint32_t uv_delta2_slope;
} calibration_cnr_extension_control_t[9];
AmlStatus
aml_ipc_isp_get_calibration_cnr_extension_control(struct AmlIPCISP *isp,
                                                  calibration_cnr_extension_control_t param);
AmlStatus
aml_ipc_isp_set_calibration_cnr_extension_control(struct AmlIPCISP *isp,
                                                  calibration_cnr_extension_control_t param);
typedef struct {
    uint32_t GAIN_LOG2_ID_mult_256;
    uint32_t svariance;
    uint32_t bright_pr;
    uint32_t contrast;
    uint32_t white_level;
} calibration_iridix_extension_control_t[9];
AmlStatus
aml_ipc_isp_get_calibration_iridix_extension_control(struct AmlIPCISP *isp,
                                                     calibration_iridix_extension_control_t param);
AmlStatus
aml_ipc_isp_set_calibration_iridix_extension_control(struct AmlIPCISP *isp,
                                                     calibration_iridix_extension_control_t param);
typedef struct {
    uint32_t GAIN_LOG2_ID_mult_256;
    uint32_t black_level_in;
    uint32_t black_level_out;
} calibration_sqrt_extension_control_t[9];
AmlStatus
aml_ipc_isp_get_calibration_sqrt_extension_control(struct AmlIPCISP *isp,
                                                   calibration_sqrt_extension_control_t param);
AmlStatus
aml_ipc_isp_set_calibration_sqrt_extension_control(struct AmlIPCISP *isp,
                                                   calibration_sqrt_extension_control_t param);

typedef struct {
    uint32_t GAIN_LOG2_ID_mult_256;
    uint32_t black_level_in;
    uint32_t black_level_out;
} calibration_square_be_extension_control_t[9];
AmlStatus aml_ipc_isp_get_calibration_square_be_extension_control(
    struct AmlIPCISP *isp, calibration_square_be_extension_control_t param);
AmlStatus aml_ipc_isp_set_calibration_square_be_extension_control(
    struct AmlIPCISP *isp, calibration_square_be_extension_control_t param);

typedef struct {
    uint32_t skip_cnt;
    uint32_t exposure_log2;
    uint32_t integrator;
    uint32_t error_log2;
    uint32_t exposure_ratio;
} calibration_3aalg_ae_t[1];
AmlStatus aml_ipc_isp_get_calibration_3aalg_ae(struct AmlIPCISP *isp, calibration_3aalg_ae_t param);
AmlStatus aml_ipc_isp_set_calibration_3aalg_ae(struct AmlIPCISP *isp, calibration_3aalg_ae_t param);
typedef struct {
    uint32_t skip_cnt;
    uint32_t wb_log2_0;
    uint32_t wb_log2_1;
    uint32_t wb_log2_2;
    uint32_t wb_log2_3;
    uint32_t wb_0;
    uint32_t wb_1;
    uint32_t wb_2;
    uint32_t wb_3;
    uint32_t global_awb_red_gain;
    uint32_t global_awb_blue_gain;
    uint32_t p_high;
    uint32_t temperature_detected;
    uint32_t light_source_candidate;
} calibration_3aalg_awb_t[1];
AmlStatus aml_ipc_isp_get_calibration_3aalg_awb(struct AmlIPCISP *isp,
                                                calibration_3aalg_awb_t param);
AmlStatus aml_ipc_isp_set_calibration_3aalg_awb(struct AmlIPCISP *isp,
                                                calibration_3aalg_awb_t param);
typedef struct {
    uint32_t skip_cnt;
    uint32_t gamma_gain;
    uint32_t gamma_offset;
} calibration_3aalg_gamma_t[1];
AmlStatus aml_ipc_isp_get_calibration_3aalg_gamma(struct AmlIPCISP *isp,
                                                  calibration_3aalg_gamma_t param);
AmlStatus aml_ipc_isp_set_calibration_3aalg_gamma(struct AmlIPCISP *isp,
                                                  calibration_3aalg_gamma_t param);

typedef struct {
    uint32_t skip_cnt;
    uint32_t strength_target;
    uint32_t iridix_contrast;
    uint32_t dark_enh;
    uint32_t iridix_global_DG;
    uint32_t diff;
    uint32_t iridix_strength;
} calibration_3aalg_iridix_t[1];
AmlStatus aml_ipc_isp_get_calibration_3aalg_iridix(struct AmlIPCISP *isp,
                                                   calibration_3aalg_iridix_t param);
AmlStatus aml_ipc_isp_set_calibration_3aalg_iridix(struct AmlIPCISP *isp,
                                                   calibration_3aalg_iridix_t param);
typedef struct {
    uint16_t GAIN_LOG2_ID_mult_256;
    uint16_t dpdev_threshold;
} calibration_dp_devthreshold_t[9];
AmlStatus aml_ipc_isp_get_calibration_dp_devthreshold(struct AmlIPCISP *isp,
                                                      calibration_dp_devthreshold_t param);
AmlStatus aml_ipc_isp_set_calibration_dp_devthreshold(struct AmlIPCISP *isp,
                                                      calibration_dp_devthreshold_t param);

typedef struct {
    uint16_t GAIN_LOG2_ID_mult_256;
    uint16_t hue;
    uint16_t luma;
    uint16_t sat;
    uint16_t saturation;
    uint16_t purple_strength;
} calibration_pf_correction_t[9];
AmlStatus aml_ipc_isp_get_calibration_pf_correction(struct AmlIPCISP *isp,
                                                    calibration_pf_correction_t param);
AmlStatus aml_ipc_isp_set_calibration_pf_correction(struct AmlIPCISP *isp,
                                                    calibration_pf_correction_t param);
typedef struct {
    uint16_t GAIN_LOG2_ID_mult_256;
    uint16_t fc_slope;
    uint16_t alias_slop;
    uint16_t alias_thresh;
} calibration_fc_correction_t[9];
AmlStatus aml_ipc_isp_get_calibration_fc_correction(struct AmlIPCISP *isp,
                                                    calibration_fc_correction_t param);
AmlStatus aml_ipc_isp_set_calibration_fc_correction(struct AmlIPCISP *isp,
                                                    calibration_fc_correction_t param);

typedef uint16_t calibration_light_src_t[1 * 2];
AmlStatus aml_ipc_isp_get_calibration_light_src(struct AmlIPCISP *isp,
                                                calibration_light_src_t param);
AmlStatus aml_ipc_isp_set_calibration_light_src(struct AmlIPCISP *isp,
                                                calibration_light_src_t param);

typedef uint16_t calibration_rg_pos_t[15];
AmlStatus aml_ipc_isp_get_calibration_rg_pos(struct AmlIPCISP *isp, calibration_rg_pos_t param);
AmlStatus aml_ipc_isp_set_calibration_rg_pos(struct AmlIPCISP *isp, calibration_rg_pos_t param);

typedef uint16_t calibration_bg_pos_t[15];
AmlStatus aml_ipc_isp_get_calibration_bg_pos(struct AmlIPCISP *isp, calibration_bg_pos_t param);
AmlStatus aml_ipc_isp_set_calibration_bg_pos(struct AmlIPCISP *isp, calibration_bg_pos_t param);

typedef uint16_t calibration_mesh_rgbg_weight_t[15 * 15];
AmlStatus aml_ipc_isp_get_calibration_mesh_rgbg_weight(struct AmlIPCISP *isp,
                                                       calibration_mesh_rgbg_weight_t param);
AmlStatus aml_ipc_isp_set_calibration_mesh_rgbg_weight(struct AmlIPCISP *isp,
                                                       calibration_mesh_rgbg_weight_t param);

typedef uint16_t calibration_mesh_ls_weight_t[15 * 15];
AmlStatus aml_ipc_isp_get_calibration_mesh_ls_weight(struct AmlIPCISP *isp,
                                                     calibration_mesh_ls_weight_t param);
AmlStatus aml_ipc_isp_set_calibration_mesh_ls_weight(struct AmlIPCISP *isp,
                                                     calibration_mesh_ls_weight_t param);

typedef uint16_t calibration_mesh_color_temperature_t[15 * 15];
AmlStatus
aml_ipc_isp_get_calibration_mesh_color_temperature(struct AmlIPCISP *isp,
                                                   calibration_mesh_color_temperature_t param);
AmlStatus
aml_ipc_isp_set_calibration_mesh_color_temperature(struct AmlIPCISP *isp,
                                                   calibration_mesh_color_temperature_t param);

typedef uint16_t calibration_wb_strength_t[3];
AmlStatus aml_ipc_isp_get_calibration_wb_strength(struct AmlIPCISP *isp,
                                                  calibration_wb_strength_t param);
AmlStatus aml_ipc_isp_set_calibration_wb_strength(struct AmlIPCISP *isp,
                                                  calibration_wb_strength_t param);

typedef uint16_t calibration_sky_lux_th_t[1];
AmlStatus aml_ipc_isp_get_calibration_sky_lux_th(struct AmlIPCISP *isp,
                                                 calibration_sky_lux_th_t param);
AmlStatus aml_ipc_isp_set_calibration_sky_lux_th(struct AmlIPCISP *isp,
                                                 calibration_sky_lux_th_t param);

typedef uint16_t calibration_ct_rg_pos_calc_t[9];
AmlStatus aml_ipc_isp_get_calibration_ct_rg_pos_calc(struct AmlIPCISP *isp,
                                                     calibration_ct_rg_pos_calc_t param);
AmlStatus aml_ipc_isp_set_calibration_ct_rg_pos_calc(struct AmlIPCISP *isp,
                                                     calibration_ct_rg_pos_calc_t param);

typedef uint16_t calibration_ct_bg_pos_calc_t[9];
AmlStatus aml_ipc_isp_get_calibration_ct_bg_pos_calc(struct AmlIPCISP *isp,
                                                     calibration_ct_bg_pos_calc_t param);
AmlStatus aml_ipc_isp_set_calibration_ct_bg_pos_calc(struct AmlIPCISP *isp,
                                                     calibration_ct_bg_pos_calc_t param);

typedef uint16_t calibration_color_temp_t[9];
AmlStatus aml_ipc_isp_get_calibration_color_temp(struct AmlIPCISP *isp,
                                                 calibration_color_temp_t param);
AmlStatus aml_ipc_isp_set_calibration_color_temp(struct AmlIPCISP *isp,
                                                 calibration_color_temp_t param);

typedef uint16_t calibration_ct65pos_t[1];
AmlStatus aml_ipc_isp_get_calibration_ct65pos(struct AmlIPCISP *isp, calibration_ct65pos_t param);
AmlStatus aml_ipc_isp_set_calibration_ct65pos(struct AmlIPCISP *isp, calibration_ct65pos_t param);

typedef uint16_t calibration_ct40pos_t[1];
AmlStatus aml_ipc_isp_get_calibration_ct40pos(struct AmlIPCISP *isp, calibration_ct40pos_t param);
AmlStatus aml_ipc_isp_set_calibration_ct40pos(struct AmlIPCISP *isp, calibration_ct40pos_t param);

typedef uint16_t calibration_ct30pos_t[1];
AmlStatus aml_ipc_isp_get_calibration_ct30pos(struct AmlIPCISP *isp, calibration_ct30pos_t param);
AmlStatus aml_ipc_isp_set_calibration_ct30pos(struct AmlIPCISP *isp, calibration_ct30pos_t param);

typedef uint32_t calibration_evtolux_ev_lut_t[17];
AmlStatus aml_ipc_isp_get_calibration_evtolux_ev_lut(struct AmlIPCISP *isp,
                                                     calibration_evtolux_ev_lut_t param);
AmlStatus aml_ipc_isp_set_calibration_evtolux_ev_lut(struct AmlIPCISP *isp,
                                                     calibration_evtolux_ev_lut_t param);

typedef uint32_t calibration_evtolux_lux_lut_t[17];
AmlStatus aml_ipc_isp_get_calibration_evtolux_lux_lut(struct AmlIPCISP *isp,
                                                      calibration_evtolux_lux_lut_t param);
AmlStatus aml_ipc_isp_set_calibration_evtolux_lux_lut(struct AmlIPCISP *isp,
                                                      calibration_evtolux_lux_lut_t param);

typedef uint16_t calibration_black_level_r_t[6 * 2];
AmlStatus aml_ipc_isp_get_calibration_black_level_r(struct AmlIPCISP *isp,
                                                    calibration_black_level_r_t param);
AmlStatus aml_ipc_isp_set_calibration_black_level_r(struct AmlIPCISP *isp,
                                                    calibration_black_level_r_t param);

typedef uint16_t calibration_black_level_gr_t[6 * 2];
AmlStatus aml_ipc_isp_get_calibration_black_level_gr(struct AmlIPCISP *isp,
                                                     calibration_black_level_gr_t param);
AmlStatus aml_ipc_isp_set_calibration_black_level_gr(struct AmlIPCISP *isp,
                                                     calibration_black_level_gr_t param);

typedef uint16_t calibration_black_level_gb_t[6 * 2];
AmlStatus aml_ipc_isp_get_calibration_black_level_gb(struct AmlIPCISP *isp,
                                                     calibration_black_level_gb_t param);
AmlStatus aml_ipc_isp_set_calibration_black_level_gb(struct AmlIPCISP *isp,
                                                     calibration_black_level_gb_t param);

typedef uint16_t calibration_black_level_b_t[6 * 2];
AmlStatus aml_ipc_isp_get_calibration_black_level_b(struct AmlIPCISP *isp,
                                                    calibration_black_level_b_t param);
AmlStatus aml_ipc_isp_set_calibration_black_level_b(struct AmlIPCISP *isp,
                                                    calibration_black_level_b_t param);

typedef uint16_t calibration_static_wb_t[4];
AmlStatus aml_ipc_isp_get_calibration_static_wb(struct AmlIPCISP *isp,
                                                calibration_static_wb_t param);
AmlStatus aml_ipc_isp_set_calibration_static_wb(struct AmlIPCISP *isp,
                                                calibration_static_wb_t param);

typedef uint16_t calibration_mt_absolute_ls_a_ccm_t[9];
AmlStatus
aml_ipc_isp_get_calibration_mt_absolute_ls_a_ccm(struct AmlIPCISP *isp,
                                                 calibration_mt_absolute_ls_a_ccm_t param);
AmlStatus
aml_ipc_isp_set_calibration_mt_absolute_ls_a_ccm(struct AmlIPCISP *isp,
                                                 calibration_mt_absolute_ls_a_ccm_t param);

typedef uint16_t calibration_mt_absolute_ls_d40_ccm_t[9];
AmlStatus
aml_ipc_isp_get_calibration_mt_absolute_ls_d40_ccm(struct AmlIPCISP *isp,
                                                   calibration_mt_absolute_ls_d40_ccm_t param);
AmlStatus
aml_ipc_isp_set_calibration_mt_absolute_ls_d40_ccm(struct AmlIPCISP *isp,
                                                   calibration_mt_absolute_ls_d40_ccm_t param);

typedef uint16_t calibration_mt_absolute_ls_d50_ccm_t[9];
AmlStatus
aml_ipc_isp_get_calibration_mt_absolute_ls_d50_ccm(struct AmlIPCISP *isp,
                                                   calibration_mt_absolute_ls_d50_ccm_t param);
AmlStatus
aml_ipc_isp_set_calibration_mt_absolute_ls_d50_ccm(struct AmlIPCISP *isp,
                                                   calibration_mt_absolute_ls_d50_ccm_t param);

typedef uint8_t calibration_shading_ls_a_r_t[1024];
AmlStatus aml_ipc_isp_get_calibration_shading_ls_a_r(struct AmlIPCISP *isp,
                                                     calibration_shading_ls_a_r_t param);
AmlStatus aml_ipc_isp_set_calibration_shading_ls_a_r(struct AmlIPCISP *isp,
                                                     calibration_shading_ls_a_r_t param);

typedef uint8_t calibration_shading_ls_a_g_t[1024];
AmlStatus aml_ipc_isp_get_calibration_shading_ls_a_g(struct AmlIPCISP *isp,
                                                     calibration_shading_ls_a_g_t param);
AmlStatus aml_ipc_isp_set_calibration_shading_ls_a_g(struct AmlIPCISP *isp,
                                                     calibration_shading_ls_a_g_t param);

typedef uint8_t calibration_shading_ls_a_b_t[1024];
AmlStatus aml_ipc_isp_get_calibration_shading_ls_a_b(struct AmlIPCISP *isp,
                                                     calibration_shading_ls_a_b_t param);
AmlStatus aml_ipc_isp_set_calibration_shading_ls_a_b(struct AmlIPCISP *isp,
                                                     calibration_shading_ls_a_b_t param);

typedef uint8_t calibration_shading_ls_tl84_r_t[1024];
AmlStatus aml_ipc_isp_get_calibration_shading_ls_tl84_r(struct AmlIPCISP *isp,
                                                        calibration_shading_ls_tl84_r_t param);
AmlStatus aml_ipc_isp_set_calibration_shading_ls_tl84_r(struct AmlIPCISP *isp,
                                                        calibration_shading_ls_tl84_r_t param);

typedef uint8_t calibration_shading_ls_tl84_g_t[1024];
AmlStatus aml_ipc_isp_get_calibration_shading_ls_tl84_g(struct AmlIPCISP *isp,
                                                        calibration_shading_ls_tl84_g_t param);
AmlStatus aml_ipc_isp_set_calibration_shading_ls_tl84_g(struct AmlIPCISP *isp,
                                                        calibration_shading_ls_tl84_g_t param);

typedef uint8_t calibration_shading_ls_tl84_b_t[1024];
AmlStatus aml_ipc_isp_get_calibration_shading_ls_tl84_b(struct AmlIPCISP *isp,
                                                        calibration_shading_ls_tl84_b_t param);
AmlStatus aml_ipc_isp_set_calibration_shading_ls_tl84_b(struct AmlIPCISP *isp,
                                                        calibration_shading_ls_tl84_b_t param);

typedef uint8_t calibration_shading_ls_d65_r_t[1024];
AmlStatus aml_ipc_isp_get_calibration_shading_ls_d65_r(struct AmlIPCISP *isp,
                                                       calibration_shading_ls_d65_r_t param);
AmlStatus aml_ipc_isp_set_calibration_shading_ls_d65_r(struct AmlIPCISP *isp,
                                                       calibration_shading_ls_d65_r_t param);

typedef uint8_t calibration_shading_ls_d65_g_t[1024];
AmlStatus aml_ipc_isp_get_calibration_shading_ls_d65_g(struct AmlIPCISP *isp,
                                                       calibration_shading_ls_d65_g_t param);
AmlStatus aml_ipc_isp_set_calibration_shading_ls_d65_g(struct AmlIPCISP *isp,
                                                       calibration_shading_ls_d65_g_t param);

typedef uint8_t calibration_shading_ls_d65_b_t[1024];
AmlStatus aml_ipc_isp_get_calibration_shading_ls_d65_b(struct AmlIPCISP *isp,
                                                       calibration_shading_ls_d65_b_t param);
AmlStatus aml_ipc_isp_set_calibration_shading_ls_d65_b(struct AmlIPCISP *isp,
                                                       calibration_shading_ls_d65_b_t param);

typedef uint16_t calibration_awb_warming_ls_a_t[3];
AmlStatus aml_ipc_isp_get_calibration_awb_warming_ls_a(struct AmlIPCISP *isp,
                                                       calibration_awb_warming_ls_a_t param);
AmlStatus aml_ipc_isp_set_calibration_awb_warming_ls_a(struct AmlIPCISP *isp,
                                                       calibration_awb_warming_ls_a_t param);

typedef uint16_t calibration_awb_warming_ls_d50_t[3];
AmlStatus aml_ipc_isp_get_calibration_awb_warming_ls_d50(struct AmlIPCISP *isp,
                                                         calibration_awb_warming_ls_d50_t param);
AmlStatus aml_ipc_isp_set_calibration_awb_warming_ls_d50(struct AmlIPCISP *isp,
                                                         calibration_awb_warming_ls_d50_t param);

typedef uint16_t calibration_awb_warming_ls_d75_t[3];
AmlStatus aml_ipc_isp_get_calibration_awb_warming_ls_d75(struct AmlIPCISP *isp,
                                                         calibration_awb_warming_ls_d75_t param);
AmlStatus aml_ipc_isp_set_calibration_awb_warming_ls_d75(struct AmlIPCISP *isp,
                                                         calibration_awb_warming_ls_d75_t param);

typedef uint8_t calibration_noise_profile_t[128];
AmlStatus aml_ipc_isp_get_calibration_noise_profile(struct AmlIPCISP *isp,
                                                    calibration_noise_profile_t param);
AmlStatus aml_ipc_isp_set_calibration_noise_profile(struct AmlIPCISP *isp,
                                                    calibration_noise_profile_t param);

typedef uint8_t calibration_demosaic_t[128];
AmlStatus aml_ipc_isp_get_calibration_demosaic(struct AmlIPCISP *isp, calibration_demosaic_t param);
AmlStatus aml_ipc_isp_set_calibration_demosaic(struct AmlIPCISP *isp, calibration_demosaic_t param);

typedef uint16_t calibration_gamma_t[129];
AmlStatus aml_ipc_isp_get_calibration_gamma(struct AmlIPCISP *isp, calibration_gamma_t param);
AmlStatus aml_ipc_isp_set_calibration_gamma(struct AmlIPCISP *isp, calibration_gamma_t param);

typedef uint32_t calibration_iridix_asymmetry_t[65];
AmlStatus aml_ipc_isp_get_calibration_iridix_asymmetry(struct AmlIPCISP *isp,
                                                       calibration_iridix_asymmetry_t param);
AmlStatus aml_ipc_isp_set_calibration_iridix_asymmetry(struct AmlIPCISP *isp,
                                                       calibration_iridix_asymmetry_t param);

typedef uint16_t calibration_awb_scene_presets_t[7 * 2];
AmlStatus aml_ipc_isp_get_calibration_awb_scene_presets(struct AmlIPCISP *isp,
                                                        calibration_awb_scene_presets_t param);
AmlStatus aml_ipc_isp_set_calibration_awb_scene_presets(struct AmlIPCISP *isp,
                                                        calibration_awb_scene_presets_t param);
typedef uint8_t calibration_wdr_np_lut_t[128];
AmlStatus aml_ipc_isp_get_calibration_wdr_np_lut(struct AmlIPCISP *isp,
                                                 calibration_wdr_np_lut_t param);
AmlStatus aml_ipc_isp_set_calibration_wdr_np_lut(struct AmlIPCISP *isp,
                                                 calibration_wdr_np_lut_t param);

typedef uint32_t calibration_ca_filter_mem_t[32];
AmlStatus aml_ipc_isp_get_calibration_ca_filter_mem(struct AmlIPCISP *isp,
                                                    calibration_ca_filter_mem_t param);
AmlStatus aml_ipc_isp_set_calibration_ca_filter_mem(struct AmlIPCISP *isp,
                                                    calibration_ca_filter_mem_t param);

typedef uint16_t calibration_ca_correction_t[3];
AmlStatus aml_ipc_isp_get_calibration_ca_correction(struct AmlIPCISP *isp,
                                                    calibration_ca_correction_t param);
AmlStatus aml_ipc_isp_set_calibration_ca_correction(struct AmlIPCISP *isp,
                                                    calibration_ca_correction_t param);

typedef uint16_t calibration_ca_correction_mem_t[4 * 10];
AmlStatus aml_ipc_isp_get_calibration_ca_correction_mem(struct AmlIPCISP *isp,
                                                        calibration_ca_correction_mem_t param);
AmlStatus aml_ipc_isp_set_calibration_ca_correction_mem(struct AmlIPCISP *isp,
                                                        calibration_ca_correction_mem_t param);

typedef uint32_t calibration_lut3d_mem_t[1];
AmlStatus aml_ipc_isp_get_calibration_lut3d_mem(struct AmlIPCISP *isp,
                                                calibration_lut3d_mem_t param);
AmlStatus aml_ipc_isp_set_calibration_lut3d_mem(struct AmlIPCISP *isp,
                                                calibration_lut3d_mem_t param);

typedef uint32_t calibration_decompander0_mem_t[33];
AmlStatus aml_ipc_isp_get_calibration_decompander0_mem(struct AmlIPCISP *isp,
                                                       calibration_decompander0_mem_t param);
AmlStatus aml_ipc_isp_set_calibration_decompander0_mem(struct AmlIPCISP *isp,
                                                       calibration_decompander0_mem_t param);

typedef uint32_t calibration_decompander1_mem_t[257];
AmlStatus aml_ipc_isp_get_calibration_decompander1_mem(struct AmlIPCISP *isp,
                                                       calibration_decompander1_mem_t param);
AmlStatus aml_ipc_isp_set_calibration_decompander1_mem(struct AmlIPCISP *isp,
                                                       calibration_decompander1_mem_t param);

typedef uint16_t calibration_shading_radial_r_t[129];
AmlStatus aml_ipc_isp_get_calibration_shading_radial_r(struct AmlIPCISP *isp,
                                                       calibration_shading_radial_r_t param);
AmlStatus aml_ipc_isp_set_calibration_shading_radial_r(struct AmlIPCISP *isp,
                                                       calibration_shading_radial_r_t param);

typedef uint16_t calibration_shading_radial_g_t[129];
AmlStatus aml_ipc_isp_get_calibration_shading_radial_g(struct AmlIPCISP *isp,
                                                       calibration_shading_radial_g_t param);
AmlStatus aml_ipc_isp_set_calibration_shading_radial_g(struct AmlIPCISP *isp,
                                                       calibration_shading_radial_g_t param);

typedef uint16_t calibration_shading_radial_b_t[129];
AmlStatus aml_ipc_isp_get_calibration_shading_radial_b(struct AmlIPCISP *isp,
                                                       calibration_shading_radial_b_t param);
AmlStatus aml_ipc_isp_set_calibration_shading_radial_b(struct AmlIPCISP *isp,
                                                       calibration_shading_radial_b_t param);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* end of include guard: AML_IPC_ISP_CALIBRATION_H */
