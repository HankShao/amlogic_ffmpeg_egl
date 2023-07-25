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
#ifndef AML_IPC_VOEGL_H

#define AML_IPC_VOEGL_H

#ifdef __cplusplus
extern "C" {
#endif

enum AmlIPCVoEglChannel { AML_VOEGL_INPUT };

struct AmlIPCVoEglPriv;
struct AmlIPCVoEgl {
    AML_OBJ_EXTENDS(AmlIPCVoEgl, AmlIPCComponent, AmlIPCComponentClass);
    struct AmlIPCVoEglPriv *priv;
    struct AmlIPCVoEgl *next;
    struct AmlRect rect;
    int z_order;
    int alpha;
    int sync_margin;
    int freerun_fps;
};

AML_OBJ_DECLARE_TYPEID(AmlIPCVoEgl, AmlIPCComponent, AmlIPCComponentClass);

enum AmlIPCVoDisplayMode {
    AML_DISPLAY_MODE_UNKNOWN = 0,
    AML_DISPLAY_MODE_HDMI,
    AML_DISPLAY_MODE_PANEL
};

struct AmlIPCVoDisplay;
struct AmlIPCVoDisplayFormat {
    enum AmlIPCVoDisplayMode connector;
    int width, height, fps;
};

struct AmlIPCVoDisplay *aml_ipc_vo_display_instance();
AmlStatus aml_ipc_vo_display_get_supported_formats(struct AmlIPCVoDisplay *disp, int *nfmt,
                                                   struct AmlIPCVoDisplayFormat *fmt);
AmlStatus aml_ipc_vo_display_set_format(struct AmlIPCVoDisplay *disp,
                                        struct AmlIPCVoDisplayFormat *fmt);

struct AmlIPCVoEgl *aml_ipc_voegl_new();
AmlStatus aml_ipc_voegl_set_position(struct AmlIPCVoEgl *vo, struct AmlRect *rc, int z_order);
AmlStatus aml_ipc_voegl_set_alpha(struct AmlIPCVoEgl *vo, int alpha);
AmlStatus aml_ipc_voegl_set_freerun(struct AmlIPCVoEgl *vo, int fps);
AmlStatus aml_ipc_voegl_set_sync_margin(struct AmlIPCVoEgl *vo, int ms);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* end of include guard: AML_IPC_VOEGL_H */
