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
#CFLAGS+=-I./inc/GL
CFLAGS+=-I./inc/GLES2
#CFLAGS+=-I./inc/GLES3
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

SRC_FILES := $(shell find $(SUB_DIRS)/ -iname '*.c')
SRC_OBJS := $(SRC_FILES:%.c=%.o)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

#*******************************************************************************
.PHONY: all

all: egl

egl:$(SRC_OBJS)
	$(CC) -o $(BIN_DIRS)/ffmpeg_egl  $(SRC_OBJS)  $(CFLAGS) $(LDFLAGS)	

clean:
	rm  -rf  $(BIN_DIRS)/* $(SRC_OBJS)

help:
	@echo "*--------------------------------------------------------------------------------------------------*"
	@echo "*-- 编译命令：  make egl   --*"
	@echo "*--------------------------------------------------------------------------------------------------*"

