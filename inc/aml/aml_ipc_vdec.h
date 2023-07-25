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

#ifndef AML_IPC_VDEC_H

#define AML_IPC_VDEC_H

#ifdef __cplusplus
extern "C" {
#endif

enum AmlIPCVdecChannel { AML_VDEC_INPUT, AML_VDEC_OUTPUT };

enum AmlIPCVDecDWMode {
    VDEC_DW_AFBC_ONLY = 0,      // AFBC compress data for display only
    VDEC_DW_AFBC_1_1_DW = 1,    // width x height
    VDEC_DW_AFBC_1_4_DW = 2,    // width/4 x height/4
    VDEC_DW_AFBC_x2_1_4_DW = 3, // width/4 x height/4
    VDEC_DW_AFBC_1_2_DW = 4,    // width/2 x height/2
    VDEC_DW_NO_AFBC = 16,       // width x height
};

struct AmlIPCVdecPriv;
struct AmlIPCVdec {
    AML_OBJ_EXTENDS(AmlIPCVdec, AmlIPCComponent, AmlIPCComponentClass);
    struct AmlIPCVideoFormat out_format;
    struct AmlIPCVdecPriv *priv;
    char *device;
    int in_codec;    // enum AmlIPCVideoCodec
    int in_buf_size; // in KB
    int in_nbuf;     // nbuf for v4l2 output device
    int out_nbuf;    // nbuf for v4l2 capture device
    int out_nplane;  // nplane for v4l2 capture device
    int dw_mode;
    int sp;
};
AML_OBJ_DECLARE_TYPEID(AmlIPCVdec, AmlIPCComponent, AmlIPCComponentClass);

struct AmlIPCVdec *aml_ipc_vdec_new(const char *device);
AmlStatus aml_ipc_vdec_set_device(struct AmlIPCVdec *dec, const char *device);
AmlStatus aml_ipc_vdec_set_input_size(struct AmlIPCVdec *dec, int sizeKB);
AmlStatus aml_ipc_vdec_set_input_nbuf(struct AmlIPCVdec *dec, int nbuf);
AmlStatus aml_ipc_vdec_set_output_nbuf(struct AmlIPCVdec *dec, int nbuf);
// only support NV12/NV21/YU12
AmlStatus aml_ipc_vdec_set_output_pixfmt(struct AmlIPCVdec *dec, enum AmlPixelFormat pixfmt);
AmlStatus aml_ipc_vdec_set_output_nplane(struct AmlIPCVdec *dec, int nplane);
// only support VDEC_DW_NO_AFBC
AmlStatus aml_ipc_vdec_set_dw_mode(struct AmlIPCVdec *dec, enum AmlIPCVDecDWMode dw_mode);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* end of include guard: AML_IPC_VDEC_H */
