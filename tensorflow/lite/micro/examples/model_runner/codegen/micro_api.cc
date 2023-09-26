/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "tensorflow/lite/micro/kernels/micro_ops.h"
#include "tensorflow/lite/micro/micro_api.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/micro/micro_log.h"
#include "tensorflow/lite/micro/gen_micro_mutable_op_resolver.h"

// Globals, used for compatibility with Arduino-style sketches.
namespace {

const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* model_input = nullptr;
TfLiteTensor* model_output = nullptr;

}  // namespace

// The name of this function is important for Arduino compatibility.
int micro_model_setup(const void* model_data, int kTensorArenaSize,
                      uint8_t* tensor_arena) {

  // Map the model into a usable data structure. This doesn't involve any
  // copying or parsing, it's a very lightweight operation.
  model = tflite::GetModel(model_data);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    MicroPrintf("Model provided is schema version %d not equal "
                         "to supported version %d.",
                         model->version(), TFLITE_SCHEMA_VERSION);
    return 1;
  }
  MicroPrintf("Create Interpretor");

  // clang-format off
  // Only Pull in functions that are needed by the model
  static tflite::MicroMutableOpResolver<kNumberOperators> micro_op_resolver = get_resolver();
  
  static tflite::MicroInterpreter static_interpreter(
      model, micro_op_resolver, tensor_arena, kTensorArenaSize);
  interpreter = &static_interpreter;

  MicroPrintf("Allocate Tensor Arena");

  // Allocate memory from the tensor_arena for the model's tensors.
  TfLiteStatus allocate_status = interpreter->AllocateTensors();

  if (allocate_status != kTfLiteOk) {
    MicroPrintf("Allocate failed for tensor size %d",
                         kTensorArenaSize);
    return 2;
  }

  MicroPrintf("FOUND TENSOR SIZE: %d",
                       interpreter->arena_used_bytes());

  // Obtain pointer to the model's input tensor.
  model_input = interpreter->input(0);
  model_output = interpreter->output(0);

  return 0;
}


int8_t quantize_input(uint8_t input_value, float scale_factor, int zero_bias){
  int tmp_value = input_value * (float)scale_factor;
  tmp_value+=(float)zero_bias;

  if (tmp_value < -128) {
        tmp_value = -128;
      }
      if (tmp_value > 127) {
        tmp_value = 127;
      }

	return (int8_t)tmp_value;
}

int micro_model_invoke(unsigned char* input_data, int num_inputs, float* results,
                       int num_outputs, float scale_factor, int zero_bias) {


  if (model_input->type == kTfLiteFloat32) {
    for (int i = 0; i < num_inputs; i++) {
      model_input->data.f[i] = (float)input_data[i];
    }
  }

  if (model_input->type == kTfLiteUInt8) {
    for (int i = 0; i < num_inputs; i++) {
      model_input->data.uint8[i] = input_data[i];
    }
  }

  if (model_input->type == kTfLiteInt8) {
    for (int i = 0; i < num_inputs; i++) {
      model_input->data.int8[i] = quantize_input(input_data[i], scale_factor, zero_bias);
    }
  }

  // Run inference, and report any error.
  TfLiteStatus invoke_status = interpreter->Invoke();

  if (invoke_status != kTfLiteOk) {
    MicroPrintf("Invoke failed on index");
    return 1;
  }

  // Read the predicted y value from the model's output tensor
  if (model_output->type == kTfLiteFloat32) {
  for (int i = 0; i < num_outputs; i++) {
    results[i] = model_output->data.f[i];
  }
  }

  if (model_output->type == kTfLiteUInt8) {
  for (int i = 0; i < num_outputs; i++) {
    results[i] = (float)model_output->data.uint8[i];
  }
  }


  if (model_output->type == kTfLiteInt8) {
  for (int i = 0; i < num_outputs; i++) {
    results[i] = (float)model_output->data.int8[i];
  }
  }


  return 0;
}
