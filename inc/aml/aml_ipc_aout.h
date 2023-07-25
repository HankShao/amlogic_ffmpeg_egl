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
#ifndef AML_IPC_AOUT_H

#define AML_IPC_AOUT_H

#ifdef __cplusplus
extern "C" {
#endif

enum AmlAOutChannel { AML_AOUT_INPUT };
struct AmlIPCAOutPriv;
struct AmlIPCAOut {
    AML_OBJ_EXTENDS(AmlIPCAOut, AmlIPCComponent, AmlIPCComponentClass);
    struct AmlIPCAOutPriv *priv;
    unsigned int buffer_time;
    unsigned int period_time;
    char *device;
    char *vol_device;
    char *vol_control;
    char *vol_curve;
    float volume;
};
AML_OBJ_DECLARE_TYPEID(AmlIPCAOut, AmlIPCComponent, AmlIPCComponentClass);

#define AML_IPC_AOUT(obj) ((struct AmlIPCAOut *)(obj))

struct AmlIPCAOut *aml_ipc_aout_new();

AmlStatus aml_ipc_aout_set_volume(struct AmlIPCAOut *aout, float vol);

/**
 * @brief set AudioOut device
 *
 * @param aout
 * @param device
 *
 * @return
 */
AmlStatus aml_ipc_aout_set_device(struct AmlIPCAOut *aout, char *device);

/**
 * @brief set AudioOut buffer time in us
 *
 * @param aout
 * @param time
 *
 * @return
 */
AmlStatus aml_ipc_aout_set_buffer_time(struct AmlIPCAOut *aout, int time);

/**
 * @brief set AudioOut period time in us
 *
 * @param aout
 * @param time
 *
 * @return
 */
AmlStatus aml_ipc_aout_set_period_time(struct AmlIPCAOut *aout, int time);

/**
 * @brief set AudioOut alsa volume device
 *
 * @param aout
 * @param vol_dev
 *
 * @return
 */
AmlStatus aml_ipc_aout_set_vol_device(struct AmlIPCAOut *aout, char *vol_dev);

/**
 * @brief set AudioOut alsa volume control
 *
 * @param aout
 * @param vol_ctl
 *
 * @return
 */
AmlStatus aml_ipc_aout_set_vol_control(struct AmlIPCAOut *aout, char *vol_ctl);

/**
 * @brief set volume calibration curve
 *
 * @param aout
 * @param npoint, num element in curve, must be multiple of 2
 * @param curve, volume calibration points, each pair represent the input and output volume
 * below code will set up 2 straight-line (0.0, 0.0) - (0.08, 0.5) - (1.0, 1.0)
 *   float curve[] = {0.08, 0.5};
 *   aml_ipc_aout_set_vol_curve(aout, sizeof(curve)/sizeof(curve[0]), curve);
 * the default start (0.0, 0.0) and end point (1.0, 1.0) is omit here, but you can also specify them
 * explicitly, below code specify another 2 straight-line with different start and end point:
 *   float curve[] = {0.0, 0.2, 0.08, 0.5, 1.0, 0.8};
 *
 * @return
 */
AmlStatus aml_ipc_aout_set_vol_curve(struct AmlIPCAOut *aout, int npoint, float *curve);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* end of include guard: AML_IPC_AOUT_H */
