make -j -f tensorflow/lite/micro/tools/make/Makefile generate_model_runner_make_project
make -j -f tensorflow/lite/micro/tools/make/Makefile TARGET=x86mingw64 generate_model_runner_make_project
make -j -f tensorflow/lite/micro/tools/make/Makefile TARGET=cortex_a_generic TARGET_ARCH=cortex-a53+fp generate_model_runner_make_project TOOLCHAIN=arm-none-linux-gnueabihf GNU_INSTALL_ROOT=/usr/local/gcc-arm-10.3-2021.07-x86_64-arm-none-linux-gnueabihf
make -j -f tensorflow/lite/micro/tools/make/Makefile TARGET=cortex_a_generic TARGET_ARCH=cortex-a72+fp generate_model_runner_make_project TOOLCHAIN=arm-none-linux-gnueabihf GNU_INSTALL_ROOT=/usr/local/gcc-arm-10.3-2021.07-x86_64-arm-none-linux-gnueabihf


docker run -it  -v $(pwd):/tflite-micro 358252950181.dkr.ecr.us-west-2.amazonaws.com/sensiml/arm_none_linux_gnueabihf_base:10.3.1 TENSORFLOWarm_none_linux_gnueabihf
cd tflite-micro && make -j lib 
