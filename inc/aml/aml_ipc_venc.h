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

#ifndef AML_IPC_VENC_H

#define AML_IPC_VENC_H

#include "aml_ipc_component.h"

#ifdef __cplusplus
extern "C" {
#endif

struct AmlRectFloat {
    float left;
    float top;
    float width;
    float height;
};
enum AmlIPCVencChannel { AML_VENC_INPUT, AML_VENC_OUTPUT };

#define AML_VENC_MAX_QUALITY_LEVEL 6

// must match AMVGOPModeOPT in AML_MultiEncoder.h
enum AmlIPCVencGopOpt {
    AML_VENC_GOP_OPT_NONE,
    AML_VENC_GOP_OPT_ALL_I,
    AML_VENC_GOP_OPT_IP,
    AML_VENC_GOP_OPT_IBBBP,
    AML_VENC_GOP_OPT_IP_SVC1,
    AML_VENC_GOP_OPT_IP_SVC2,
    AML_VENC_GOP_OPT_IP_SVC3,
    AML_VENC_GOP_OPT_IP_SVC4
};

enum AmlIPCVencIntraRefreshMode {
    AML_VENC_INTRA_REFRESH_DISABLE,
    AML_VENC_INTRA_REFRESH_ROW,
    AML_VENC_INTRA_REFRESH_COLUMN,
    AML_VENC_INTRA_REFRESH_STEP,
    AML_VENC_INTRA_REFRESH_ADAPTIVE
};

enum AmlIPCVencProfile {
    AML_VENC_PROFILE_AUTO, // H264:high, H265:main
    AML_VENC_PROFILE_H264_BASELINE,
    AML_VENC_PROFILE_H264_MAIN,
    AML_VENC_PROFILE_H264_HIGH
};

struct AmlIPCVencPriv;
struct AmlIPCVenc {
    AML_OBJ_EXTENDS(AmlIPCVenc, AmlIPCComponent, AmlIPCComponentClass);
    struct AmlIPCVencPriv *priv;
    enum AmlIPCVideoCodec codec;
    int width;
    int height;
    enum AmlPixelFormat pixfmt;
    int gop;
    int framerate;
    int bitrate;
    int min_buffers;
    int max_buffers;
    int encoder_bufsize;
    int quality_level;
    int gop_opt;
    enum AmlIPCVencIntraRefreshMode intra_refresh_mode;
    int intra_refresh_num;
    int ltr_idr_pq_delta;
    int ltr_goodp_pq_delta;
    int ltr_goodp_interval; // 0 disable ltr
    enum AmlIPCVencProfile profile;
    int p_qp_delta;
    int i_qp_min;
    int i_qp_max;
    int p_qp_min;
    int p_qp_max;
    int b_qp_min;
    int b_qp_max;
    int max_delta_qp;
    int multi_slice_nCTU;
    int multi_slice_size;
    int rotation;  // 0, 90, 180, 270
    int mirroring; // 0:no mirror, 1:vertical 2:horizontal 3:both vertical and horizontal
    int roi_enabled;
    int bitrate_window;
    int skip_threshold;
};
AML_OBJ_DECLARE_TYPEID(AmlIPCVenc, AmlIPCComponent, AmlIPCComponentClass);

struct AmlIPCVenc *aml_ipc_venc_new(enum AmlIPCVideoCodec codec);

AmlStatus aml_ipc_venc_set_bitrate(struct AmlIPCVenc *enc, int bitrate);
AmlStatus aml_ipc_venc_set_gop_size(struct AmlIPCVenc *enc, int gopsize);
AmlStatus aml_ipc_venc_force_insert_idr(struct AmlIPCVenc *enc);
AmlStatus aml_ipc_venc_set_roi(struct AmlIPCVenc *enc, int quality, struct AmlRectFloat *rect,
                               int *index);
AmlStatus aml_ipc_venc_clear_roi(struct AmlIPCVenc *enc, int index);
// quality_level: 0: CBR, 1~6: VBR level (the bigger the number ,the better the quality)
AmlStatus aml_ipc_venc_set_quality_level(struct AmlIPCVenc *enc, int quality_level);

/**
 * @brief set venc codec
 *
 * @param venc
 * @param codec
 *
 * @return
 */
AmlStatus aml_ipc_venc_set_codec(struct AmlIPCVenc *venc, enum AmlIPCVideoCodec codec);

/**
 * @brief set venc buffer size in KB
 *
 * @param venc
 * @param size
 *
 * @return
 */
AmlStatus aml_ipc_venc_set_bufsize(struct AmlIPCVenc *venc, int size);

/**
 * @brief  set venc gop options
 *
 * @param venc
 * @param opt
 *
 * @return
 */
AmlStatus aml_ipc_venc_set_gop_option(struct AmlIPCVenc *venc, enum AmlIPCVencGopOpt opt);

AmlStatus aml_ipc_venc_set_intra_refresh(struct AmlIPCVenc *venc,
                                         enum AmlIPCVencIntraRefreshMode mode, int nCTU);

AmlStatus aml_ipc_venc_set_longterm_reference(struct AmlIPCVenc *venc, int ltr_goodp_interval,
                                              int ltr_goodp_qp_delta, int ltr_idr_qp_delta);

AmlStatus aml_ipc_venc_set_profile(struct AmlIPCVenc *venc, enum AmlIPCVencProfile profile);

/**
 * @brief set QP delta for IDR frame, delta is relative to P frame QP, after set IDR QP delte, IDR
 * frame QP is in the range of [QP+delta_min,QP+delta_max]
 *
 * @param venc
 * @param delta_min, [-51,50]
 * @param delta_max, [-50,51]
 *
 * @return
 */
AmlStatus aml_ipc_venc_set_idr_qp_delta(struct AmlIPCVenc *venc, int delta_min, int delta_max);

/**
 * @brief set QP range for I/P/B frames
 *
 * @param venc
 * @param minqpI, 0~51
 * @param maxqpI, minqpI+1,51
 * @param minqpP, minqpI,maxqpI
 * @param maxqpP, minqpP+1,maxqpI
 * @param minqpB, minqpI,maxqpI
 * @param maxqpB, minqpB+1,maxqpI
 *
 * @return
 */
AmlStatus aml_ipc_venc_set_qp_range(struct AmlIPCVenc *venc, int minqpI, int maxqpI, int minqpP,
                                    int maxqpP, int minqpB, int maxqpB);

/**
 * @brief enable/disable multi slice
 *
 * @param venc
 * @param nCTU, numbers of MB(H264 16x16 blocks)/CTU(H265 64x64 blocks)
 * @param size, only valid for H265, specify size of dependeant slices in bytes
 *
 * @return
 */
AmlStatus aml_ipc_venc_set_slice_split(struct AmlIPCVenc *venc, int nCTU, int size);

/**
 * @brief enable encoder rotation, only support 0, 90, 180, 270 degree
 *
 * @param venc
 * @param angle
 *
 * @return
 */
AmlStatus aml_ipc_venc_set_rotation(struct AmlIPCVenc *venc, int angle);

/**
 * @brief enable encoder mirror direction
 *
 * @param venc
 * @param hmirror, enable horizontal mirroring
 * @param vmirror, enable vertical mirroring
 *
 * @return
 */
AmlStatus aml_ipc_venc_set_mirroring(struct AmlIPCVenc *venc, int horizontal, int vertical);

AmlStatus aml_ipc_venc_enable_roi_feature(struct AmlIPCVenc *venc, int enable);

/**
 * @brief Change the strict bit-rate control by encoding skip frames
 * @param venc
 * @param bitrate_window, the length of windows (in frames) to calculate current bitrate
 * 0: will disable the feature
 * other value: last number of frames to calculate current bitrate (max 120 frames)
 * value larger than that will be clipped
 *
 * @param skip_threshold, percentage of the current bitrate in compare with the origianl
 * bitrates settings to trigger skip encoding of next frame
 * example: int skip_threshold = 120;
 *
 *@return
 **/
AmlStatus aml_ipc_venc_change_strict_rc(struct AmlIPCVenc *venc, int bitrate_window,
                                        int skip_threshold);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* end of include guard: AML_IPC_VENC_H */
