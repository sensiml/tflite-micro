# Enable u-arch specfic behaviours
ifneq (,$(filter $(TARGET_ARCH), x86_64))
  # CMSIS-NN optimizations not supported
endif



ifneq (,$(CMSIS_NN_LIBS))
  ifeq (,$(CMSIS_PATH))
    $(error CMSIS_NN_LIBS provided but not CMSIS_PATH)
  endif
endif


ifeq (,$(GECKO_SDK_PATH))
$(error GECKO_SDK_PATH not defined)
endif

# Unless an external path is provided we force a download during the first
# phase of make.
CMSIS_DEFAULT_DOWNLOAD_PATH := $(MAKEFILE_DIR)/downloads/cmsis
CMSIS_PATH := $(CMSIS_DEFAULT_DOWNLOAD_PATH)
ifeq ($(CMSIS_PATH), $(CMSIS_DEFAULT_DOWNLOAD_PATH))
  DOWNLOAD_RESULT := $(shell $(MAKEFILE_DIR)/ext_libs/cmsis_download.sh ${MAKEFILE_DIR}/downloads)
  ifneq ($(DOWNLOAD_RESULT), SUCCESS)
    $(error Something went wrong with the CMSIS download: $(DOWNLOAD_RESULT))
  endif
endif

ifeq (,$(CMSIS_NN_LIBS))
  THIRD_PARTY_CC_SRCS += $(call recursive_find,$(CMSIS_PATH)/CMSIS/NN/Source,*.c)
else
  MICROLITE_LIBS += $(CMSIS_NN_LIBS)
endif
THIRD_PARTY_CC_HDRS += $(call recursive_find,$(CMSIS_PATH)/CMSIS/NN/Include,*.h)

INCLUDES += \
  -I$(CMSIS_PATH) \
  -I$(CMSIS_PATH)/CMSIS/Core/Include \
  -I$(CMSIS_PATH)/CMSIS/DSP/Include \
  -I$(CMSIS_PATH)/CMSIS/NN/Include \
   -I$(GECKO_SDK_PATH)/platform/Device/SiliconLabs/EFR32MG24/Include \
   -I$(GECKO_SDK_PATH)/platform/common/inc \
   -I$(GECKO_SDK_PATH)/hardware/board/inc \
   -I$(GECKO_SDK_PATH)/platform/CMSIS/Include \
   -I$(GECKO_SDK_PATH)/platform/service/device_init/inc \
   -I$(GECKO_SDK_PATH)/platform/emdrv/dmadrv/inc \
   -I$(GECKO_SDK_PATH)/platform/emdrv/common/inc \
   -I$(GECKO_SDK_PATH)/platform/emlib/inc \
   -I$(GECKO_SDK_PATH)/platform/emlib/host/inc \
   -I$(GECKO_SDK_PATH)/platform/service/iostream/inc \
   -I$(GECKO_SDK_PATH)/platform/driver/mvp/inc \
   -I$(GECKO_SDK_PATH)/hardware/driver/mx25_flash_shutdown/inc/sl_mx25_flash_shutdown_eusart \
   -I$(GECKO_SDK_PATH)/platform/common/toolchain/inc \
   -I$(GECKO_SDK_PATH)/platform/service/system/inc \
   -I$(GECKO_SDK_PATH)/util/third_party/tensorflow_extra \
   -I$(GECKO_SDK_PATH)/platform/service/udelay/inc

# Note all the headers from CMSIS/Core/Include are needed to ensure that the
# project generation scripts copy over the compiler specific implementations of
# the various intrinisics.
THIRD_PARTY_CC_HDRS += \
  $(CMSIS_PATH)/LICENSE.txt \
  $(wildcard $(CMSIS_PATH)/CMSIS/Core/Include/*.h) \
  $(CMSIS_PATH)/CMSIS/DSP/Include/arm_common_tables.h \
  $(CMSIS_PATH)/CMSIS/DSP/Include/arm_helium_utils.h \
  $(CMSIS_PATH)/CMSIS/DSP/Include/arm_math.h \
  $(CMSIS_PATH)/CMSIS/DSP/Include/arm_math_memory.h \
  $(CMSIS_PATH)/CMSIS/DSP/Include/arm_math_types.h \
  $(CMSIS_PATH)/CMSIS/DSP/Include/dsp/basic_math_functions.h \
  $(CMSIS_PATH)/CMSIS/DSP/Include/dsp/bayes_functions.h \
  $(CMSIS_PATH)/CMSIS/DSP/Include/dsp/complex_math_functions.h \
  $(CMSIS_PATH)/CMSIS/DSP/Include/dsp/controller_functions.h \
  $(CMSIS_PATH)/CMSIS/DSP/Include/dsp/distance_functions.h \
  $(CMSIS_PATH)/CMSIS/DSP/Include/dsp/fast_math_functions.h \
  $(CMSIS_PATH)/CMSIS/DSP/Include/dsp/filtering_functions.h \
  $(CMSIS_PATH)/CMSIS/DSP/Include/dsp/interpolation_functions.h \
  $(CMSIS_PATH)/CMSIS/DSP/Include/dsp/matrix_functions.h \
  $(CMSIS_PATH)/CMSIS/DSP/Include/dsp/none.h \
  $(CMSIS_PATH)/CMSIS/DSP/Include/dsp/statistics_functions.h \
  $(CMSIS_PATH)/CMSIS/DSP/Include/dsp/support_functions.h \
  $(CMSIS_PATH)/CMSIS/DSP/Include/dsp/svm_defines.h \
  $(CMSIS_PATH)/CMSIS/DSP/Include/dsp/svm_functions.h \
  $(CMSIS_PATH)/CMSIS/DSP/Include/dsp/transform_functions.h \
  $(CMSIS_PATH)/CMSIS/DSP/Include/dsp/utils.h

# We add -I$(CMSIS_PATH) to enable the code in the TFLM repo (mostly in the
# tensorflow/lite/micro/kernels/cmsis_nn) to use include paths relative to
# the CMSIS code-base.
#
# The CMSIS code itself uses includes such as #include "arm_math.h" and so
# we add $(CMSIS_PATH)/CMSIS/Core/Include etc. to be able to build the CMSIS
# code without any modifications.

