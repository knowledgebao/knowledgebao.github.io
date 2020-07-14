# Hisilicon Hi35xx sample Makefile

include ../Makefile.param
#ifeq ($(SAMPLE_PARAM_FILE), )
#     SAMPLE_PARAM_FILE:=../Makefile.param
#     include $(SAMPLE_PARAM_FILE)
#endif
SHELL=/bin/bash

ifeq (0x35360100,$(HICHIP))
export CROSS_COMPILE=arm-hisiv600-linux-
export CROSS=arm-hisiv600-linux-
endif

export CXX:=$(CROSS)g++
export CC:=$(CROSS)gcc
export AR:=$(CROSS)ar
export STRIP := $(CROSS)strip
export OBJCOPY := $(CROSS)objcopy
export LD := $(CROSS)ld

# BOARD_NAME ?= _16CH_3536_PCIE_CARD
BOARD_NAME  ?= _THERMO_3536C_BOX
REF_NAME    ?= THERMO_B2R_FW_V1.1_DEV
TEMPER_ALGO ?= TEMPER_ALGO_MASK
MAKE_JOBS   ?= -j20


ifneq (,$(findstring THERMO,$(REF_NAME)))

ifneq (,$(findstring DEV,$(REF_NAME)))
CFLAGS += -DTHERMO_DEV=1
endif # DEV

ifneq (,$(findstring DEBUG,$(REF_NAME)))
DEBUG := ON
endif # DEBUG

ifneq (,$(findstring EUR,$(REF_NAME)))
CFLAGS += -DDISABLE_IR_GEN1 -DDISABLE_FACE_RECOG
endif # EUR

ifneq (,$(findstring CHINESE,$(REF_NAME)))
CFLAGS += -DAPPSTR_LANG_DEFAULT=1
endif # CHINESE

endif # THERMO

ifeq (ON,$(DEBUG))
    BUILD_TYPE := -g -ggdb -O0 # -DTHERMO_ENABLE_DEBUG=1
else
    BUILD_TYPE := -g -O2
endif

B2_BASE_INCDIR = -Ibase/live555/include -Ibase/onvif/include -Ibase/johnson_base/include -Ibase/zlib/include -Ibase/openssl/include -Ibase/civetweb/include -Ibase/gat1400/include
SQLITE3_INCDIR = -Isqlite-amalgamation-3240000
SQLITE3_OBJ = sqlite-amalgamation-3240000/sqlite3.o
PROTOBUF_VER = 3.5.1
ICONV_VER = 1.16
ICONV_INCDIR = -Ilibiconv-$(ICONV_VER)/include
GAT1400_INCDIR = -Igat1400/

CFLAGS += $(B2_BASE_INCDIR) $(SQLITE3_INCDIR) $(ZLIB_INCDIR) $(ICONV_INCDIR) -Inanopb -Idatabase -I. -Iprotobuf-$(PROTOBUF_VER)/src -Iexternal_curl/include -IWL-4020
CFLAGS += $(GAT1400_INCDIR) -Ivideo_factory
CFLAGS += -I../../../drv/cipher/include
CFLAGS += -Imp4v2-2.0.0/include
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -DDEV_HICHIP=$(HICHIP) -D$(BOARD_NAME) -D$(TEMPER_ALGO)
CFLAGS += -Wno-unused-variable -Wno-return-type -Wno-unused-but-set-variable -Wno-unused-function -Wno-sign-compare
CONLYFLAGS += -std=gnu11 $(BUILD_TYPE) -fdiagnostics-color=always
#flags used by sqlite
CONLYFLAGS += -DHAVE_USLEEP -DHAVE_ISNAN -DHAVE_GMTIME_R -DHAVE_LOCALTIME_R -DHAVE_LOCALTIME_S
CXXFLAGS += -std=c++11 $(BUILD_TYPE) -fdiagnostics-color=always -D_GLIBCXX_USE_C99 -Iproto_cpp -Irtsp_proxy -Irecognition -Iweb_cpp -Iweb_cpp/civetweb
LDFLAGS := -L../../../drv/cipher/src/ -l:libhi_cipher.a -lrt -lpthread -lm -ldl -Wl,--gc-sections

# target source
PROTO_CPP := $(wildcard proto_cpp/*.proto)
PROTO_CPP_C := $(PROTO_CPP:%.proto=%.pb.cc)

TEST_SRC := $(wildcard *_test.cpp)
TEST_SRC += $(wildcard web_cpp/*_test.cpp)
TEST_SRC += test_cpp/test.cpp

SRC  := $(wildcard *.c)
SRC  += gen/git-rev.c
SRC  += database/db_common.c
SRC  += $(wildcard websocket_lib/*.c)
SRC  += $(wildcard web_cpp/*/*.c)
SRC_CXX := $(wildcard *.cpp)
SRC_CXX += $(wildcard database/*.cpp)
SRC_CXX += $(wildcard rtsp_proxy/*.cpp)
SRC_CXX += $(wildcard recogd_cpp/*.cpp)
SRC_CXX += $(wildcard sdk/*.cpp)
SRC_CXX += $(wildcard recognition/*.cpp)
SRC_CXX += $(wildcard web_cpp/*.cpp) 
# SRC_CXX += $(wildcard web_cpp/*/*.cpp)
SRC_CXX := $(filter-out $(TEST_SRC),$(SRC_CXX))
SRC_CC := $(wildcard *.cc) $(PROTO_CPP_C)
GAT1400_CXX := $(wildcard gat1400/*.cpp)
VIDEO_FACTORY_CXX := $(wildcard video_factory/*.cpp)

TEST_SRC += string_utils.cpp

MEDIA_SRC := $(wildcard media_cpp/*.cpp)
MEDIA_SRC += syscfg.cpp os_ops.cpp string_utils.cpp log.cpp
MEDIA_SRC += rtsp_client.cpp $(wildcard rtsp_proxy/*.cpp) sock_utils.cpp
JOHNSON_SRC := $(wildcard johnson_cpp/*.cpp)
WL4020_SRC := $(wildcard WL-4020/*c)
SQL  += $(wildcard database/*.sql)
OBJ  := $(SRC:%.c=%.o)
OBJ  += $(SQLITE3_OBJ)
OBJ  += $(SQL:%.sql=%.o)
OBJ_CXX := $(SRC_CXX:%.cpp=%.o)
OBJ_CC := $(SRC_CC:%.cc=%.o)
MEDIA_OBJ := $(MEDIA_SRC:%.cpp=%.o)
JOHNSON_OBJ := $(JOHNSON_SRC:%.cpp=%.o)
GAT1400_OBJ += $(GAT1400_CXX:%.cpp=%.o)
VIDEO_FACTORY_OBJ += $(VIDEO_FACTORY_CXX:%.cpp=%.o)
WL4020_OBJ := $(WL4020_SRC:%.c=%.o)
OBJ  += $(WL4020_OBJ)

TEST_OBJ := $(TEST_SRC:%.cpp=%.o)

WEB_HEADERS := $(wildcard web_cpp/*.h) $(wildcard web_cpp/*/*.h) $(wildcard web_cpp/*/*.inl)
GAT1400_HEADERS:= $(wildcard gat1400/*.h) $(wildcard nanopb/*.h)
VIDEO_FACTORY_HEADERS := $(wildcard video_factory/*.h)

HEADERS := $(wildcard *.h) $(wildcard database/*.h) $(wildcard rtsp_proxy/*.h) $(wildcard recognition/*.h) $(wildcard sdk/*.h) $(WEB_HEADERS) $(GAT1400_HEADERS) $(VIDEO_FACTORY_HEADERS)

TARGET := meg_b2
TARGET_MEDIA := media
TARGET_JOHNSON := johnson

all: $(TARGET) $(TARGET_MEDIA) $(TARGET_JOHNSON) led_flash hwinit

MPI_LIBS := $(REL_LIB)/libmpi.a
MPI_LIBS += $(REL_LIB)/libhdmi.a
IVE_LIBS := $(REL_LIB)/libive.a
PB_LIBS := protobuf-$(PROTOBUF_VER)/src/.libs/libprotobuf.a
ICONV_LIB := libiconv-$(ICONV_VER)/lib/.libs/libiconv.a
MP4_LIBS := mp4v2-2.0.0/.libs/libmp4v2.a
LIVE555_LIB := base/live555/lib/liblive555.a
ifeq (ON, $(ENABLE_ONVIF))
	ONVIF_LIB := base/onvif/lib/libonviflite.a
endif
JOHNSON_BASE_LIB := base/johnson_base/lib/libjohnson_base.a
ZLIB_LIB := base/zlib/lib/libz.a
OPENSSL_LIBS := base/openssl/lib/libssl.a base/openssl/lib/libcrypto.a
CIVETWEB_LIB := base/civetweb/lib/libcivetweb.a
GAT1400_LIB := base/gat1400/lib/libgat1400.a

ifeq (uclibc,$(LIBC))
CURL_LIBS := external_curl/lib/libcurl.a $(OPENSSL_LIBS)
else
# No pre-compiled library for glibc
endif

$(SHELL echo "$(CFLAGS)")
$(SHELL echo "$(CXXFLAGS)")

env:
	@echo CROSS       = $(CROSS)
	@echo HICHIP      = $(HICHIP)
	@echo BOARD_NAME  = $(BOARD_NAME)
	@echo TEMPER_ALGO = $(TEMPER_ALGO)
	@echo REF_NAME    = $(REF_NAME)
	@echo BUILD_TYPE  = $(BUILD_TYPE)
	@echo CONLYFLAGS  = $(CONLYFLAGS)
	@echo CFLAGS      = $(CFLAGS)
	@echo CXXFLAGS    = $(CXXFLAGS)


protobuf-$(PROTOBUF_VER)/Makefile:
	tar -xf protobuf-cpp-$(PROTOBUF_VER).tar.gz && pushd protobuf-$(PROTOBUF_VER) && ./configure --host=$(patsubst %-,%,$(CROSS)) --with-protoc=protoc --enable-static=yes --enable-shared=no && popd

$(PB_LIBS): protobuf-$(PROTOBUF_VER)/Makefile
	make -C protobuf-$(PROTOBUF_VER) $(MAKE_JOBS)

libiconv-$(ICONV_VER)/Makefile:
	tar -xf libiconv-$(ICONV_VER).tar.gz && pushd libiconv-$(ICONV_VER) && ./configure --host=$(patsubst %-,%,$(CROSS)) CC=$(CROSS)gcc --enable-static && popd

$(ICONV_LIB): libiconv-$(ICONV_VER)/Makefile
	make -C libiconv-$(ICONV_VER) $(MAKE_JOBS)

$(MP4_LIBS):
	tar -jxf mp4v2-2.0.0.tar.bz2 && pushd mp4v2-2.0.0 &&  ./configure --host=$(patsubst %-,%,$(CROSS)) CC=$(CROSS)gcc CXX=$(CROSS)g++ --disable-option-checking --disable-debug --disable-optimize --disable-fvisibility --disable-gch --disable-largefile --disable-util --disable-dependency-tracking --disable-libtool-lock && popd
	make -C mp4v2-2.0.0 $(MAKE_JOBS)

$(PROTO_CPP_C):%.pb.cc:%.proto
	protoc-$(PROTOBUF_VER) -Iproto_cpp --cpp_out=./proto_cpp $<

$(TARGET): $(MP4_LIBS) $(ICONV_LIB) $(PB_LIBS) $(PROTO_CPP_C) $(OBJ) $(OBJ_CXX) $(OBJ_CC) $(COMM_OBJ) $(GAT1400_OBJ) $(VIDEO_FACTORY_OBJ)
	@echo link $@
	@$(CXX) $(CFLAGS) -o $@.unstripped $(OBJ) $(OBJ_CXX) $(OBJ_CC) $(COMM_OBJ) $(GAT1400_OBJ) $(GAT1400_LIB) $(MPI_LIBS) $(AUDIO_LIBA) $(JPEGD_LIBA) $(IVE_LIBS) $(ONVIF_LIB)  $(LIVE555_LIB) $(PB_LIBS) $(CIVETWEB_LIB) $(CURL_LIBS) $(ZLIB_LIB) $(LDFLAGS) $(VIDEO_FACTORY_OBJ) $(MP4_LIBS) $(ICONV_LIB)
	@$(STRIP) $@.unstripped -o $@

$(TARGET_MEDIA): $(OBJ) $(MEDIA_OBJ) algocfg.o database/db_face.o
	@echo link $@
	@$(CXX) $(CFLAGS) -o $@.unstripped $(OBJ) $(MEDIA_OBJ) algocfg.o $(LDFLAGS) $(LIVE555_LIB) database/db_face.o
	@$(STRIP) $@.unstripped -o $@

$(TARGET_JOHNSON): $(JOHNSON_OBJ) gen/git-rev.o syscfg.o os_ops.o hii2c.o higpio.o eeprom_reader.o common.o database/db_face.o database/db_capture.o string_utils.o log.o
	@echo link $@
	@$(CXX) $(CXXFLAGS) -o $@ $(JOHNSON_OBJ) $(JOHNSON_BASE_LIB) gen/git-rev.o syscfg.o os_ops.o hii2c.o higpio.o eeprom_reader.o common.o database/db_face.o database/db_capture.o string_utils.o log.o $(LDFLAGS)
	@$(STRIP) $@

fpga_reset: utils/fpga_reset.o higpio.o file_lock.o common.o log.o
	$(CXX) $(CFLAGS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	$(STRIP) $@

led_flash: utils/led_flash.o higpio.o common.o log.o
	@echo link $@
	@$(CXX) $(CFLAGS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@$(STRIP) $@

hwinit: utils/hwinit.o eeprom_reader.o higpio.o hii2c.o common.o log.o
	@echo link $@
	@$(CXX) $(CFLAGS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@$(STRIP) $@

i2c-test: utils/i2c-test.o common.o log.o
	$(CXX) $(CFLAGS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	$(STRIP) $@

sqlite3: sqlite-amalgamation-3240000/shell.o $(SQLITE3_OBJ)
	$(CXX) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	$(STRIP) $@

wl4020Test: $(WL4020_SRC) $(WL4020_OBJ) common.o
	$(CC) $(CFLAGS) -DWL4020_TEST -o $@ $^ $(LDFLAGS)
	$(STRIP) $@

system_upgrade: utils/system_upgrade.c utils/u-boot-crc32.c common.o log.o
	$(CXX) $(CFLAGS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	$(STRIP) $@

meg_b2_test: $(TEST_OBJ) $(SQLITE3_OBJ) $(OBJ_CC) $(PB_LIBS) log.o
	@echo link $@
	@$(CXX) $(CFLAGS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o:%.c $(HEADERS)
	@echo CXX $<
	@$(CC) $(CFLAGS) $(CONLYFLAGS) -c $< -o $@

%.o:%.sql
	$(eval $@_TMP := $(subst .,_,$(notdir $<)))
	@echo ".section .rodata" >$<.S
	@echo ".global _$($@_TMP)_start" >>$<.S
	@echo ".global _$($@_TMP)_end" >>$<.S
	@echo ".global _$($@_TMP)_size" >>$<.S
	@echo "_$($@_TMP)_start: .incbin \"$<\"" >>$<.S
	@echo "_$($@_TMP)_end:" >>$<.S
	@echo "_$($@_TMP)_size: .word _$($@_TMP)_end-_$($@_TMP)_start" >>$<.S
	$(CC) $(CFLAGS) -c $<.S -o $@
	rm $<.S
	@# $(LD) -r -b binary -z noexecstack $< $@
	@# $(OBJCOPY) -I binary -O elf32-little -B armv5te $< $@

%.o:%.cpp $(HEADERS)
	@echo CXX $<
	@$(CXX) $(CFLAGS) $(CXXFLAGS)  -c $< -o $@

%.o:%.cc $(HEADERS)
	@echo CXX $<
	@$(CXX) $(CFLAGS) $(CXXFLAGS)  -c $< -o $@

$(JOHNSON_OBJ):%.o:%.cpp $(HEADERS)
	@echo CXX $<
	@$(CXX) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

$(GAT1400_OBJ):%.o:%.cpp $(WEB_HEADERS)  $(HEADERS)
	@echo CXX $<
	@$(CXX) $(CXXFLAGS) $(CFLAGS) -O3 -c $< -o $@

$(VIDEO_FACTORY_OBJ):%.o:%.cpp $(VIDEO_FACTORY_HEADERS) build_options.h
	@echo CXX $<
	@$(CXX) $(CXXFLAGS) $(CFLAGS) -O3 -c $< -o $@

.SUFFIXES:

.PHONY: gen/git-rev.c clean all

gen/git-rev.c:
	@echo gen git-rev.c
	@-mkdir -p gen
	@echo "#include \"common.h\"" >gen/git-rev.c
	@echo "#define _BUILD_GIT_REV \\" >>gen/git-rev.c
	@git rev-parse --short HEAD >>gen/git-rev.c
	@echo "const char *BUILD_GIT_REV = C_MACRO_XSTR(_BUILD_GIT_REV);" >>gen/git-rev.c
	@echo "const char *BUILD_DATETIME = \"$(shell date -Iseconds)\";" >>gen/git-rev.c
	@echo "const char *BUILD_TOP_TAG_NAME = \"$(REF_NAME)\";" >>gen/git-rev.c
	@echo "const uint32_t BUILD_TIMESTAMP = $(shell date +%s);" >>gen/git-rev.c

app_string.o: app_string.cpp gen/git-rev.c
	@echo CXX $<
	@$(CXX) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -rf $(TARGET) gen hwinit johnson led_flash media media.unstripped meg_b2.unstripped
	@rm -f $(OBJ) $(OBJ_CXX) $(OBJ_CC) $(JOHNSON_OBJ)
	@rm -f $(COMM_OBJ) $(GAT1400_OBJ) $(MEDIA_OBJ) $(VIDEO_FACTORY_OBJ) 
	@rm -f utils/*.o

distclean: clean
	@rm -rf protobuf-3.5.1 mp4v2-2.0.0 libiconv-1.16

print-%  : ; @echo $* = $($*)

train_roi_SRCS := cmd/train_roi/train_roi.cpp traincfg.cpp train_fun.cpp bitmap.cpp bmp_encoder.cpp common.cpp

train_roi: cmd/train_roi/train_roi ;

cmd/train_roi/train_roi: $(train_roi_SRCS:.cpp=.o)
	$(CXX) $(CFLAGS) -o $@ $^
