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
#ifndef AML_IPC_ISP_TUNNING_H

#define AML_IPC_ISP_TUNNING_H

#include "aml_ipc_isp_calibration.h"
#include <stdint.h>
#include <sys/types.h>
#ifdef __cplusplus
extern "C" {
#endif

/**************************** 1. BlackLevel ******************************/
typedef struct {
    /* common part */
    uint8_t enable_module_black_level;

    calibration_black_level_r_t black_level_r;
    calibration_black_level_gr_t black_level_gr;
    calibration_black_level_gb_t black_level_gb;
    calibration_black_level_b_t black_level_b;
    calibration_sqrt_extension_control_t sqrt_extension_control;
    calibration_square_be_extension_control_t square_be_extension_control;

    int32_t enable_manual_black_level;

    struct {
    } auto_params;

    struct {
        int32_t manual_black_level_r;
        int32_t manual_black_level_gr;
        int32_t manual_black_level_gb;
        int32_t manual_black_level_b;
    } manual_params;
} BlackLevelParam_T;

AmlStatus aml_ipc_isp_get_black_level_params(struct AmlIPCISP *isp,
                                             BlackLevelParam_T *param);
AmlStatus aml_ipc_isp_set_black_level_params(struct AmlIPCISP *isp,
                                             BlackLevelParam_T *param);
/************************************************************************/


/**************************** 2. Shading  ****************************/
typedef struct {
    /* common part */
    uint8_t enable_module_shading;

    calibration_shading_ls_a_r_t shading_ls_a_r;
    calibration_shading_ls_a_g_t shading_ls_a_g;
    calibration_shading_ls_a_b_t shading_ls_a_b;
    calibration_shading_ls_tl84_r_t shading_ls_tl84_r;
    calibration_shading_ls_tl84_g_t shading_ls_tl84_g;
    calibration_shading_ls_tl84_b_t shading_ls_tl84_b;
    calibration_shading_ls_d65_r_t shading_ls_d65_r;
    calibration_shading_ls_d65_g_t shading_ls_d65_g;
    calibration_shading_ls_d65_b_t shading_ls_d65_b;

    struct {
    } auto_params;

    struct {
    } manual_params;
} ShadingParam_T;

AmlStatus aml_ipc_isp_get_shading_params(struct AmlIPCISP *isp,
                                             ShadingParam_T *param);
AmlStatus aml_ipc_isp_set_shading_params(struct AmlIPCISP *isp,
                                             ShadingParam_T *param);
/*********************************************************************/


/**************************** 3. CA ******************************/
typedef struct {
    /* common part */
    uint8_t enable_module_ca;

    calibration_ca_filter_mem_t ca_filter_mem;
    calibration_ca_correction_t ca_correction;
    calibration_ca_correction_mem_t ca_correction_mem;

    struct {
    } auto_params;

    struct {
    } manual_params;
} CAParam_T;

AmlStatus aml_ipc_isp_get_ca_params(struct AmlIPCISP *isp,
                                             CAParam_T *param);
AmlStatus aml_ipc_isp_set_ca_params(struct AmlIPCISP *isp,
                                             CAParam_T *param);
/*****************************************************************/


/************************************ 4. AE *************************************/
typedef struct {
    uint32_t enable_antiflicker;
    uint32_t antiflicker_frequency;
    uint32_t max_sensor_AG;
    uint32_t max_sensor_DG;
    uint32_t max_isp_DG;
    uint32_t max_exposure_ratio;
    uint32_t analog_gain_last_priority;
    uint32_t analog_gain_reserve;
} calibration_cmos_control_tunning_t[1];

enum AmlISPAEState { AE_STATE_NONE, AE_STATE_SEARCHING, AE_STATE_CONVERGING };

typedef struct {
    /* common part */
    u_char ae_zone_weight[33][33];
    int32_t enable_system_manual_exposure_ratio;       // SYSTEM_MANUAL_EXPOSURE_RATIO
    int32_t enable_system_manual_integration_time;     // SYSTEM_MANUAL_INTEGRATION_TIME
    int32_t enable_system_manual_sensor_analog_gain;   // SYSTEM_MANUAL_SENSOR_ANALOG_GAIN
    int32_t enable_system_manual_sensor_digital_gain;  // SYSTEM_MANUAL_SENSOR_DIGITAL_GAIN
    int32_t enable_system_manual_isp_digital_gain;     // SYSTEM_MANUAL_ISP_DIGITAL_GAIN
    int32_t sensor_antiflicker_fps;                    // 25/30 fps
    int32_t sensor_vmax_fps;                           // sensor_vmax_fps <= sensor_antiflicker_fps

    struct {
        calibration_ae_control_HDR_target_t ae_control_HDR_target;
        calibration_ae_control_t ae_control;
        calibration_cmos_control_tunning_t cmos_control_tunning;
        calibration_cmos_exposure_partition_luts_t cmos_exposure_partition_luts;
    } auto_params;

    struct {
        int32_t manual_system_exposure_ratio;              // SYSTEM_EXPOSURE_RATIO      // 当前曝光比
        int32_t manual_system_integration_time;            // SYSTEM_INTEGRATION_TIME    // 当前曝光时间
        uint32_t manual_system_sensor_analog_gain;         // SYSTEM_SENSOR_ANALOG_GAIN   // 当AG
        uint32_t manual_system_sensor_digital_gain;        // SYSTEM_SENSOR_DIGITAL_GAIN  // 当DG
        uint32_t manual_system_isp_digital_gain;           // SYSTEM_ISP_DIGITAL_GAIN   // 当ISPG
    } manual_params;
} AEParam_T;

typedef struct {
    enum AmlISPAEState current_ae_state_id;      // AE_STATE_ID
    int32_t current_exposure_value;              // AE_GET_EXPOSURE         单位us readonly
    int32_t current_exposure_ratio;              // SYSTEM_EXPOSURE_RATIO   当前曝光比
    int32_t current_exposure_fps;                // SENSOR_VMAX_FPS      当前曝光帧率
    int32_t current_short_integration_time;      // SYSTEM_SHORT_INTEGRATION_TIME     当前短曝光时间
    int32_t current_long_integration_time;	     //  SYSTEM_LONG_INTEGRATION_TIME    当前长曝光时间
    uint32_t current_sensor_analog_gain;         // SYSTEM_SENSOR_ANALOG_GAIN   // 当AG
    uint32_t current_sensor_digital_gain;        // SYSTEM_SENSOR_DIGITAL_GAIN  // 当DG
    uint32_t current_isp_digital_gain;           // SYSTEM_ISP_DIGITAL_GAIN   // 当ISPG
    int32_t current_average_luma;                // CMOS_HIST_MEAN          // 当前平均亮度
    int32_t current_target_luma;                 // AE_TARGET               // 当前ae目标值
    int32_t current_iso_value;                   // STATUS_ISO
    struct {
        uint32_t fullhist_sum; // sum of ae statistics
        uint32_t value[1024];
    } ae_statistics;
} AEInfo_T;
AmlStatus aml_ipc_isp_get_ae_params(struct AmlIPCISP *isp,
                                             AEParam_T *param);
AmlStatus aml_ipc_isp_set_ae_params(struct AmlIPCISP *isp,
                                             AEParam_T *param);
AmlStatus aml_ipc_isp_fetch_ae_info(struct AmlIPCISP *isp,
                                             AEInfo_T *info);
/********************************************************************************/


/*************************** 5. Light Compenstaion ***************************/
enum AmlISPLightCompensationMode { LC_DISABLE, LC_HLC, LC_BLC };
typedef struct {
    enum AmlISPLightCompensationMode mode;
    uint8_t light_compensation_value;

    struct {
    } auto_params;

    struct {
    } manual_params;
} LCParam_T;

AmlStatus aml_ipc_isp_set_lc_params(struct AmlIPCISP *isp,
                                             LCParam_T *param);
AmlStatus aml_ipc_isp_get_lc_params(struct AmlIPCISP *isp,
                                             LCParam_T *param);
/*********************************************************************************/


/********************************* 6. AWB **********************************/
enum AmlISPWhiteBalanceMode {
    WB_MODE_MANUAL,
    WB_MODE_AUTO,
    WB_MODE_DAYLIGHT,
    WB_MODE_CLOUDY,
    WB_MODE_TUNGSTEN,
    WB_MODE_FLUORESCENT,
    WB_MODE_SUNSET,
    WB_MODE_SHADE,
    WB_MODE_WARM_FLUORESCENT
};

enum AmlISPWhiteBalanceState { WB_STATE_NONE, WB_STATE_SEARCHING, WB_STATE_CONVERGING };

typedef struct {
    u_char awb_zone_weight[33][33];
    int32_t enable_system_manual_awb;                  // SYSTEM_MANUAL_AWB
    enum AmlISPWhiteBalanceMode awb_mode_id;           // AWB_MODE_ID

    // below parameters are generated by calibration
    calibration_static_wb_t static_wb;//
    calibration_ct30pos_t ct30pos;
    calibration_ct40pos_t ct40pos;
    calibration_ct65pos_t ct65pos;
    calibration_color_temp_t color_temp;
    calibration_ct_rg_pos_calc_t ct_rg_pos_calc; // r/g
    calibration_ct_bg_pos_calc_t ct_bg_pos_calc; // b/g
    calibration_mesh_color_temperature_t mesh_color_temperature; //估算色温值， 不建议修改
    calibration_mesh_ls_weight_t mesh_ls_weight;
    calibration_mesh_rgbg_weight_t mesh_rgbg_weight;
    calibration_bg_pos_t bg_pos;
    calibration_rg_pos_t rg_pos;
    calibration_light_src_t light_src; // 必须要有cwf光源或tl84
    calibration_awb_scene_presets_t awb_scene_presets;
    calibration_sky_lux_th_t sky_lux_th; // 不建议修改
    calibration_wb_strength_t wb_strength; // 不建议修改
    /* ********************************************** */

    struct {
        calibration_awb_mix_light_parameters_t awb_mix_light_parameters;
        calibration_awb_avg_coef_t awb_avg_coef;
        calibration_awb_warming_ls_a_t awb_warming_ls_a;
        calibration_awb_warming_ls_d50_t awb_warming_ls_d50;
        calibration_awb_warming_ls_d75_t awb_warming_ls_d75;
        AWB_colour_preference_t awb_colour_preference;
        calibration_evtolux_probability_enable_t evtolux_probability_enable;  //默认关闭
        calibration_evtolux_ev_lut_t evtolux_ev_lut;
        calibration_evtolux_lux_lut_t evtolux_lux_lut;
    } auto_params;

    struct {
        int32_t manual_system_awb_red_gain;                // SYSTEM_AWB_RED_GAIN
        int32_t manual_system_awb_blue_gain;               // SYSTEM_AWB_BLUE_GAIN
    } manual_params;

} AWBParam_T;

typedef struct {
    enum AmlISPWhiteBalanceState current_awb_state_id; // AWB_STATE_ID
    int32_t current_awb_red_gain;
    int32_t current_awb_green_even_gain;
    int32_t current_awb_green_odd_gain;
    int32_t current_awb_blue_gain;
    int32_t current_awb_temperature;                   // AWB_TEMPERATURE
    struct {
        uint32_t num_value;
        uint32_t total_sum; // sum of awb statistics
        struct {
            uint16_t rg;
            uint16_t bg;
            uint32_t sum;
        } value[1089];
    } awb_statistics;
} AWBInfo_T;

AmlStatus aml_ipc_isp_get_awb_params(struct AmlIPCISP *isp,
                                             AWBParam_T *param);
AmlStatus aml_ipc_isp_set_awb_params(struct AmlIPCISP *isp,
                                             AWBParam_T *param);
AmlStatus aml_ipc_isp_fetch_awb_info(struct AmlIPCISP *isp,
                                             AWBInfo_T *info);
/**************************************************************************/


/************************* 7. CCM ***************************/
typedef struct {
    uint8_t enable_module_ccm;
    int32_t enable_system_manual_ccm; // SYSTEM_MANUAL_CCM

    // below parameters are generated by calibration
    calibration_mt_absolute_ls_a_ccm_t mt_absolute_ls_a_ccm;
    calibration_mt_absolute_ls_d40_ccm_t mt_absolute_ls_d40_ccm;
    calibration_mt_absolute_ls_d50_ccm_t mt_absolute_ls_d50_ccm;
    /* ******************************************************** */

    struct {
        calibration_ccm_one_gain_threshold_t ccm_one_gain_threshold;
    } auto_params;

    struct {
        struct {
            int32_t RR;    // 0~4095
            int32_t RG;
            int32_t RB;
            int32_t GR;
            int32_t GG;
            int32_t GB;
            int32_t BR;
            int32_t BG;
            int32_t BB;
        } ccm_matrix;
    } manual_params;
} CCMParam_T;

AmlStatus aml_ipc_isp_get_ccm_params(struct AmlIPCISP *isp,
                                             CCMParam_T *param);
AmlStatus aml_ipc_isp_set_ccm_params(struct AmlIPCISP *isp,
                                             CCMParam_T *param);
/************************************************************/


/************************ 8. GAMMA **************************/
typedef struct {
    uint8_t enable_module_gamma;
    int32_t dual_gamma_enable;

    struct {
        calibration_gamma_ev1_t gamma_ev1;
        calibration_gamma_ev2_t gamma_ev2;
    } auto_params;

    struct {
        calibration_gamma_t gamma;
    } manual_params;
} GAMMAParam_T;

AmlStatus aml_ipc_isp_get_gamma_params(struct AmlIPCISP *isp,
                                             GAMMAParam_T *param);
AmlStatus aml_ipc_isp_set_gamma_params(struct AmlIPCISP *isp,
                                             GAMMAParam_T *param);
/**************************************************************/


/************************* 9. Iridix ***************************/
typedef struct {
    uint8_t enable_module_iridix;

    calibration_iridix_avg_coef_t iridix_avg_coef;
    calibration_iridix_strength_maximum_t iridix_strength_maximum;
    calibration_iridix_min_max_str_t iridix_min_max_str;
    calibration_iridix_ev_lim_full_str_t iridix_ev_lim_full_str;
    calibration_iridix_ev_lim_no_str_t iridix_ev_lim_no_str;

    int32_t enable_manual_iridix; // mode: manual or auto

    struct {
        calibration_iridix8_strength_dk_enh_control_t iridix8_strength_dk_enh_control;
        calibration_iridix_extension_control_t iridix_extension_control;
    } auto_params;

    struct {
        uint32_t white_level;
        uint8_t svariance;
        uint8_t bright_pr;
        uint8_t contrast;
        uint16_t dark_enh;
        uint16_t strength;
    } manual_params;
} IridixParam_T;

AmlStatus aml_ipc_isp_get_iridix_params(struct AmlIPCISP *isp,
                                             IridixParam_T *param);
AmlStatus aml_ipc_isp_set_iridix_params(struct AmlIPCISP *isp,
                                             IridixParam_T *param);
/***************************************************************/


/*************************** 10. DPC ****************************/
typedef struct {
    uint8_t enable_module_dp;
    int32_t enable_manual_raw_frontend;

    struct {
        calibration_dp_slope_t dp_slope;
        calibration_dp_threshold_t dp_threshold;
        calibration_dp_devthreshold_t dp_devthreshold;
    } auto_params;

    struct {
        uint16_t raw_frontend_dp_slope;
        uint16_t raw_frontend_dp_threshold;
        uint16_t raw_frontend_hpdev_threshold;
    } manual_params;
} DPCParam_T;

AmlStatus aml_ipc_isp_get_dpc_params(struct AmlIPCISP *isp,
                                             DPCParam_T *param);
AmlStatus aml_ipc_isp_set_dpc_params(struct AmlIPCISP *isp,
                                             DPCParam_T *param);
/***************************************************************/


/************************* 11. Sinter **************************/
typedef struct {
    calibration_noise_profile_t noise_profile;
    calibration_wdr_np_lut_t wdr_np_lut;

    uint8_t enable_module_sinter;
    int32_t enable_manual_sinter; // space zone

    struct {
        calibration_sinter_strength_t sinter_strength;
        calibration_sinter_strength1_t sinter_strength1;
        calibration_sinter_thresh1_t sinter_thresh1;
        calibration_sinter_thresh4_t sinter_thresh4;
        calibration_sinter_intConfig_t sinter_intConfig;
        calibration_sinter_sad_t sinter_sad;
    } auto_params;

    struct {
        uint8_t sad_filt_thresh;
        uint8_t thresh_1hv;
        uint8_t thresh_4hv;
        uint8_t strength_1;
    } manual_params;
} SinterParam_T;
AmlStatus aml_ipc_isp_get_sinter_params(struct AmlIPCISP *isp,
                                             SinterParam_T *param);
AmlStatus aml_ipc_isp_set_sinter_params(struct AmlIPCISP *isp,
                                             SinterParam_T *param);
/***************************************************************/


/************************* 12. Temper **************************/
typedef struct {
    uint8_t enable_module_temper;
    int32_t enable_manual_temper; // time zone

    struct {
        calibration_temper_strength_t temper_strength;
    } auto_params;

    struct {
        uint8_t global_offset;
    } manual_params;
} TemperParam_T;

AmlStatus aml_ipc_isp_get_temper_params(struct AmlIPCISP *isp,
                                             TemperParam_T *param);
AmlStatus aml_ipc_isp_set_temper_params(struct AmlIPCISP *isp,
                                             TemperParam_T *param);
/***************************************************************/


/************************** 13. CNR ****************************/
typedef struct {
    uint8_t enable_module_cnr;
    int32_t enable_manual_cnr;    // color zone

    struct {
        calibration_cnr_extension_control_t cnr_extension_control;
    } auto_params;

    struct {
        uint16_t uv_delta_slope;
    } manual_params;
} CNRParam_T;

AmlStatus aml_ipc_isp_get_cnr_params(struct AmlIPCISP *isp,
                                             CNRParam_T *param);
AmlStatus aml_ipc_isp_set_cnr_params(struct AmlIPCISP *isp,
                                             CNRParam_T *param);
/***************************************************************/


/************************ 14. Demosaic **************************/
typedef struct {
    uint8_t enable_module_demosaic;
    int32_t enable_manual_demosaic;

    struct {
        calibration_sharp_alt_d_t sharp_alt_d;
        calibration_sharp_alt_ud_t sharp_alt_ud;
        calibration_sharp_alt_du_t sharp_alt_du;
        calibration_demosaic_np_offset_t demosaic_np_offset;
        calibration_demosaic_rgb_extension_control_t rgb_extension_control;
    } auto_params;

    struct {
        uint8_t sharp_alt_ld;
        uint8_t sharp_alt_ldu;
        uint8_t sharp_alt_lu;
        uint8_t sad_amp;
        uint8_t uu_sh_slope;
        uint16_t uu_sh_thresh;
        uint16_t luma_thresh_low_d;
        uint16_t luma_thresh_low_ud;
        uint16_t luma_thresh_high_ud;
        uint32_t luma_slope_high_ud;
    } manual_params;
} DemosaicParam_T;

AmlStatus aml_ipc_isp_get_demosaic_params(struct AmlIPCISP *isp,
                                             DemosaicParam_T *param);
AmlStatus aml_ipc_isp_set_demosaic_params(struct AmlIPCISP *isp,
                                             DemosaicParam_T *param);
/***************************************************************/


/************************ 15. Sharpen **************************/
typedef struct {
    uint8_t enable_module_sharpen_fr;
    uint8_t enable_module_sharpen_ds1;
    int32_t enable_manual_sharpen;       // ISP_MODULES_MANUAL_SHARPEN

    struct {
        calibration_sharpen_fr_t sharpen_fr;
        calibration_sharpen_ds1_t sharpen_ds1;
        calibration_fr_sharpen_extension_control_t fr_sharpen_extension_control;
        calibration_ds_sharpen_extension_control_t ds_sharpen_extension_control;
    } auto_params;

    struct {
      struct {
          uint16_t strength;
          uint16_t luma_thresh_low;
          uint16_t luma_slope_low;
          uint16_t luma_thresh_high;
          uint16_t luma_slope_high;
      } fr_sharpen;

      struct {
          uint16_t strength;
          uint16_t luma_thresh_low;
          uint16_t luma_slope_low;
          uint16_t luma_thresh_high;
          uint16_t luma_slope_high;
      } ds1_sharpen;
    } manual_params;
} SharpenParam_T;

AmlStatus aml_ipc_isp_get_sharpen_params(struct AmlIPCISP *isp,
                                             SharpenParam_T *param);
AmlStatus aml_ipc_isp_set_sharpen_params(struct AmlIPCISP *isp,
                                             SharpenParam_T *param);
/***************************************************************/


/*************************** 16. FC ****************************/
typedef struct {
    int32_t enable_manual_fc;

    struct {
        calibration_fc_correction_t fc_correction;
    } auto_params;

    struct {
        uint8_t fc_slope;
        uint8_t fc_alias_slope;
        uint8_t fc_alias_thresh;
    } manual_params;
} FCParam_T;

AmlStatus aml_ipc_isp_get_fc_params(struct AmlIPCISP *isp,
                                             FCParam_T *param);
AmlStatus aml_ipc_isp_set_fc_params(struct AmlIPCISP *isp,
                                             FCParam_T *param);
/***************************************************************/


/*************************** 17. PF ****************************/
typedef struct {
    uint8_t enable_module_pf;
    int32_t enable_manual_pf;

    struct {
        calibration_pf_correction_t pf_correction;
    } auto_params;

    struct {
        uint16_t hue_strength;
        uint16_t sat_strength;
        uint16_t luma_strength;
        uint16_t purple_strength;
        uint8_t saturation_strength;
    } manual_params;
} PFParam_T;

AmlStatus aml_ipc_isp_get_pf_params(struct AmlIPCISP *isp,
                                             PFParam_T *param);
AmlStatus aml_ipc_isp_set_pf_params(struct AmlIPCISP *isp,
                                             PFParam_T *param);
/***************************************************************/


/************************* 18. WDR ***************************/
typedef struct {
    int32_t enable_manual_frame_stitch;

    struct {
        calibration_stitching_lm_np_t stitching_lm_np;
        calibration_stitching_lm_mov_mult_t stitching_lm_mov_mult;
        calibration_fs_mc_off_t fs_mc_off;
    } auto_params;

    struct {
        uint16_t lm_exposure_ratio;
        uint16_t lm_np_mult;
        uint16_t lm_alpha_mov_slope;
    } manual_params;
} WDRParam_T;

AmlStatus aml_ipc_isp_get_wdr_params(struct AmlIPCISP *isp,
                                             WDRParam_T *param);
AmlStatus aml_ipc_isp_set_wdr_params(struct AmlIPCISP *isp,
                                             WDRParam_T *param);
/***************************************************************/


/*********************** 19. AutoLevel *************************/
typedef struct {
    struct {
        calibration_auto_level_control_t auto_level_control;
    } auto_params;

    struct {
    } manual_params;
} AutoLevelParam_T;

AmlStatus aml_ipc_isp_get_autolevel_params(struct AmlIPCISP *isp,
                                             AutoLevelParam_T *param);
AmlStatus aml_ipc_isp_set_autolevel_params(struct AmlIPCISP *isp,
                                             AutoLevelParam_T *param);
/***************************************************************/


/*********************** 20. Saturation ***********************/
typedef struct {
    struct {
        calibration_saturation_strength_t saturation_strength;
    } auto_params;

    struct {
    } manual_params;
} SaturationParam_T;

AmlStatus aml_ipc_isp_get_saturation_params(struct AmlIPCISP *isp,
                                             SaturationParam_T *param);
AmlStatus aml_ipc_isp_set_saturation_params(struct AmlIPCISP *isp,
                                             SaturationParam_T *param);
/**************************************************************/


/************************** 21. Defog *************************/
typedef struct {
    struct {
        calibration_defog_control_t defog_control;
    } auto_params;

    struct {
    } manual_params;
} DefogParam_T;

AmlStatus aml_ipc_isp_get_defog_params(struct AmlIPCISP *isp,
                                             DefogParam_T *param);
AmlStatus aml_ipc_isp_set_defog_params(struct AmlIPCISP *isp,
                                             DefogParam_T *param);
/**************************************************************/


/**************************** 22. AF ***************************/
#define ISP_V4L2_AF_STATS_SIZE             (2 + 2178)
typedef struct {
    struct {
        uint32_t fullhist_sum; // sum of af statistics
        uint64_t value[ISP_V4L2_AF_STATS_SIZE/2];
    } af_statistics;
} AFInfo_T;

AmlStatus aml_ipc_isp_fetch_af_info(struct AmlIPCISP *isp,
                                             AFInfo_T *info);
/***************************************************************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* end of include guard: AML_IPC_ISP_TUNNING_H */
