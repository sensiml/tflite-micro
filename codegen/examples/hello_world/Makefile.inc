# TODO(rjascani): The codegen runtime files (ie, in runtime subdir) should be a
# separate library.
CODEGEN_HELLO_WORLD_SRCS := \
$(TENSORFLOW_ROOT)codegen/examples/hello_world/hello_world.cc \
$(TENSORFLOW_ROOT)codegen/examples/hello_world/hello_world_model.cc \
$(TENSORFLOW_ROOT)codegen/runtime/micro_codegen_context.cc

CODEGEN_HELLO_WORLD_HDRS := \
$(TENSORFLOW_ROOT)codegen/examples/hello_world/hello_world_model.h \
$(TENSORFLOW_ROOT)codegen/runtime/micro_codegen_context.h

# Builds a standalone binary.
$(eval $(call microlite_test,codegen_hello_world,\
$(CODEGEN_HELLO_WORLD_SRCS),,))