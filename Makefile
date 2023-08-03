CC=aarch64-linux-gnu-gcc
CPP=aarch64-linux-gnu-g++

CFLAGS := -Wall
CFLAGS += -g -O0

CFLAGS += -I./inc
CFLAGS+=-I./inc/libavcodec
CFLAGS+=-I./inc/libavformat
CFLAGS+=-I./inc/libavutil
CFLAGS+=-I./inc/libavdevice
CFLAGS+=-I./inc/libavfilter
CFLAGS+=-I./inc/libswresample
CFLAGS+=-I./inc/EGL
CFLAGS+=-I./inc/GLES2
CFLAGS+=-I./inc/KHR
CFLAGS+=-I./inc/drm
CFLAGS += -I./inc/gbm
CFLAGS += -I./inc/aml
CFLAGS += -I./inc/adda

LDFLAGS += -L./lib
LDFLAGS += -ldl
LDFLAGS += -lavformat -lavcodec -lavdevice -lavfilter -lavutil -lswscale -lswresample -lpostproc -lx264
#LDFLAGS += -lavformat  -lavutil 
LDFLAGS += -ldrm -lEGL -lasound -lpng -lcrypto -lion -ljpeg -laml_ipc_sdk
LDFLAGS += -lfdk-aac -lfreetype -lgbm -lgdc -lGLESv2 -lspeexdsp -lge2d -lz -lbz2
LDFLAGS += -lpthread


SUB_DIRS := $(CURDIR)/src
BIN_DIRS := $(CURDIR)/bin

#SRC_FILES := $(shell find $(SUB_DIRS)/ -iname '*.c')
SRC_FILES := $(SUB_DIRS)/lt8612.c
SRC_FILES += $(SUB_DIRS)/ffmpeg_egl.c
SRC_OBJS := $(SRC_FILES:%.c=%.o)

GBM_OBJS = $(SUB_DIRS)/aml_drm_gbm.o
GBM_OBJS += $(SUB_DIRS)/lt8612.o
%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

#*******************************************************************************
.PHONY: all

all: egl gbm

egl:$(SRC_OBJS)
	$(CC) -o $(BIN_DIRS)/ffmpeg_egl  $(SRC_OBJS)  $(CFLAGS) $(LDFLAGS)	
gbm:$(GBM_OBJS)
	$(CC) -o $(BIN_DIRS)/drm_gbm  $(GBM_OBJS)  $(CFLAGS) $(LDFLAGS)
clean:
	rm  -rf  $(BIN_DIRS)/* $(SRC_OBJS) $(GBM_OBJS)

help:
	@echo "*--------------------------------------------------------------------------------------------------*"
	@echo "*-- 编译命令：  make egl   --*"
	@echo "*--------------------------------------------------------------------------------------------------*"

