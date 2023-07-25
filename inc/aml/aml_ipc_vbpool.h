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

#ifndef AML_IPC_VBPOOL_H

#define AML_IPC_VBPOOL_H

#include "aml_ipc_component.h"

#ifdef __cplusplus
extern "C" {
#endif

enum AmlIPCVBPoolChannel { AML_VBPOOL_OUTPUT };

struct AmlIPCVBPoolBuffer;
struct AmlIPCVBPoolPriv;
struct AmlIPCVBPool {
    AML_OBJ_EXTENDS(AmlIPCVBPool, AmlIPCComponent, AmlIPCComponentClass);
    struct AmlIPCVBPoolPriv *priv;
    struct AmlIPCVideoFormat format;
    int num_buffer;
    int active;
    int live;
    int line_alignment;
    char *fill_color;
};
AML_OBJ_DECLARE_TYPEID(AmlIPCVBPool, AmlIPCComponent, AmlIPCComponentClass);

struct AmlIPCVBPool *aml_ipc_vbpool_new(int nbuf, struct AmlIPCVideoFormat *format);

AmlStatus aml_ipc_vbpool_set_alignment(struct AmlIPCVBPool *vbp, int alignment);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* end of include guard: AML_IPC_VBPOOL_H */
