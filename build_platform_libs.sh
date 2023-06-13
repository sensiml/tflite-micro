#!/bin/bash

if [ -z "$1" ];
  then
    echo "Skipping build, to rebuild projects run build_platform_libs.sh build"
else
    echo "Rebuilding all gen folders"
    rm -rf gen/*

    pushd tensorflow/lite/micro/examples/model_runner/codegen
    python codegen.py
    popd

    make -j -f tensorflow/lite/micro/tools/make/Makefile generate_model_runner_make_project LDFLAGS=-fPIC SKIP_PIGWEED_DOWNLOAD=true
    make -j -f tensorflow/lite/micro/tools/make/Makefile TARGET=x86mingw64 generate_model_runner_make_project SKIP_PIGWEED_DOWNLOAD=true
    make -j -f tensorflow/lite/micro/tools/make/Makefile TARGET=cortex_a_generic TARGET_ARCH=cortex-a53+fp generate_model_runner_make_project TOOLCHAIN=arm-none-linux-gnueabihf GNU_INSTALL_ROOT=/usr/local/gcc-arm-10.3-2021.07-x86_64-arm-none-linux-gnueabihf SKIP_PIGWEED_DOWNLOAD=true
    make -j -f tensorflow/lite/micro/tools/make/Makefile TARGET=cortex_a_generic TARGET_ARCH=cortex-a72+fp generate_model_runner_make_project TOOLCHAIN=arm-none-linux-gnueabihf GNU_INSTALL_ROOT=/usr/local/gcc-arm-10.3-2021.07-x86_64-arm-none-linux-gnueabihf SKIP_PIGWEED_DOWNLOAD=true
    make -j -f tensorflow/lite/micro/tools/make/Makefile TARGET=mplab_xc32 TARGET_ARCH=ATSAMD21G18A generate_model_runner_make_project TOOLCHAIN=xc32-  OPTIMIZED_KERNEL_DIR=cmsis_nn SKIP_PIGWEED_DOWNLOAD=true
    make -j -f tensorflow/lite/micro/tools/make/Makefile TARGET=cortex_m_generic TARGET_ARCH=cortex-m4+fp generate_model_runner_make_project TOOLCHAIN=arm-gcc-none-eabi  OPTIMIZED_KERNEL_DIR=cmsis_nn SKIP_PIGWEED_DOWNLOAD=true
    make -j -f tensorflow/lite/micro/tools/make/Makefile TARGET=cortex_m_generic TARGET_ARCH=cortex-m4+fp generate_model_runner_make_project TOOLCHAIN=arm-gcc-none-eabi  OPTIMIZED_KERNEL_DIR=siliconlabs SKIP_PIGWEED_DOWNLOAD=true
fi



pushd gen/linux_x86_64_default/prj/model_runner/make/
if [ ! -f libtensorflow-microlite.a ]; then   
    echo "BUILDING linux_x86_64_default"
    make lib -j 
    cp libtensorflow-microlite.a $SENSIML_SERVER_DEV_HOME/kbserver/codegen/templates/compilers/x86gcc_generic/libsensiml/libtensorflow-microlite.a
    exit
else
    echo "SKIPPING linux_x86_64_default"
fi
popd


pushd gen/x86mingw64_x86_64_default/prj/model_runner/make/
if [ ! -f libtensorflow-microlite.a ]; then
    echo "BUILDING x86mingw64_x86_64_default"
    docker run -it -w /tflite-micro -v $(pwd):/tflite-micro 358252950181.dkr.ecr.us-west-2.amazonaws.com/sml_x86mingw_generic:9.3-v1.0 make -j lib 
    cp libtensorflow-microlite.a $SENSIML_SERVER_DEV_HOME/kbserver/codegen/templates/compilers/x86mingw64_generic/libsensiml/libtensorflow-microlite.a
else
    echo "SKIPPING x86mingw64_x86_64_default"
fi
popd


pushd gen/cortex_a_generic_cortex-a53+fp_default/prj/model_runner/make/
if [ ! -f libtensorflow-microlite.a ]; then
    echo "BUILDING cortex_a_generic_cortex"
    docker run -it -w /tflite-micro -v $(pwd):/tflite-micro 358252950181.dkr.ecr.us-west-2.amazonaws.com/arm_none_linux_gnueabihf_base:10.3.1-v1.0 make -j lib 
    cp libtensorflow-microlite.a $SENSIML_SERVER_DEV_HOME/kbserver/codegen/templates/compilers/arm-none-linux-gnueabihf/libsensiml/cortex-a53+fp/libtensorflow-microlite.a
else
    echo "SKIPPING cortex_a_generic_cortex-a53+fp_default"
fi
popd

pushd gen/cortex_a_generic_cortex-a72+fp_default/prj/model_runner/make/
if [ ! -f libtensorflow-microlite.a ]; then
    echo "BUILDING cortex_a_generic_cortex"
    docker run -it -w /tflite-micro -v $(pwd):/tflite-micro 358252950181.dkr.ecr.us-west-2.amazonaws.com/arm_none_linux_gnueabihf_base:10.3.1-v1.0 make -j lib 
    cp libtensorflow-microlite.a $SENSIML_SERVER_DEV_HOME/kbserver/codegen/templates/compilers/arm-none-linux-gnueabihf/libsensiml/cortex-a72+fp/libtensorflow-microlite.a
else
    echo "SKIPPING cortex_a_generic_cortex-a72+fp_default"
fi
popd


pushd  gen/mplab_xc32_ATSAMD21G18A_default//prj/model_runner/make/
if [ ! -f libtensorflow-microlite.a ]; then
    echo "BUILDING mplabxc32"
    docker run -it -w /tflite-micro -v $(pwd):/tflite-micro 358252950181.dkr.ecr.us-west-2.amazonaws.com/sml_microchip_xc32:4.00-v1.0 make -j lib 
else
    echo "SKIPPING cortex_m4_generci_cortex"
fi
popd


pushd  gen/cortex_m_generic_cortex-m4+fp_default/prj/model_runner/make/
if [ ! -f libtensorflow-microlite.a ]; then
    echo "BUILDING cortex_m4_generic_cortex"
    docker run -it -w /tflite-micro -v $(pwd):/tflite-micro 358252950181.dkr.ecr.us-west-2.amazonaws.com/sml_armgcc_generic:10.3.1-v1.0 make -j lib 
else
    echo "SKIPPING cortex_m4_generci_cortex"
fi
popd


pushd  gen/cortex_m_generic_cortex-m4+fp_default/prj/model_runner/make/
if [ ! -f libtensorflow-microlite.a ]; then
    echo "BUILDING cortex_m4_generic_cortex siliconlabs"
    docker run -it -w /tflite-micro -v $(pwd):/tflite-micro 358252950181.dkr.ecr.us-west-2.amazonaws.com/sml_armgcc_generic:10.3.1-v1.0 make -j lib 
else
    echo "SKIPPING cortex_m4_generci_cortex"
fi
popd




