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
#ifndef AML_IPC_OVERLAY_H

#define AML_IPC_OVERLAY_H

#ifdef __cplusplus
extern "C" {
#endif

enum AmlIPCOverlayChannel { AML_OVERLAY_INPUT, AML_OVERLAY_OUTPUT };
struct AmlIPCOverlayPriv;
struct AmlIPCOverlay {
    AML_OBJ_EXTENDS(AmlIPCOverlay, AmlIPCComponent, AmlIPCComponentClass);
    struct AmlIPCOverlayPriv *priv;
    char *font_file;
    char *draw;
    int font_size;
    int font_color;
    int bg_color;
    int pos_x;
    int pos_y;
    int num_font_glyph_cache;
};
AML_OBJ_DECLARE_TYPEID(AmlIPCOverlay, AmlIPCComponent, AmlIPCComponentClass);

struct AmlIPCOverlay *aml_ipc_overlay_new(void);
typedef void (*AmlIPCScriptFunc)(void *sce, void *param);
AmlStatus aml_ipc_script_bind_str(struct AmlIPCOverlay *ov, const char *name, char *val);
AmlStatus aml_ipc_script_bind_int(struct AmlIPCOverlay *ov, const char *name, int val);
AmlStatus aml_ipc_script_bind_func(struct AmlIPCOverlay *ov, const char *name,
                                   AmlIPCScriptFunc func, void *param);
// AmlIPCScriptFunc call below APIs to get parameters, or abort execution
int aml_ipc_script_arg_int(void *sce, int idx);
char *aml_ipc_script_arg_str(void *sce, int idx);
void aml_ipc_script_abort(void *sce, int retval, const char *fmt, ...);

// all variables and functions shall bind before compile to avoid undefined symbols
AmlStatus aml_ipc_script_compile(struct AmlIPCOverlay *ov, const char *script, int len);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* end of include guard: AML_IPC_OVERLAY_H */
