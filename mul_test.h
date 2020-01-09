/* Copyright 2017 The TensorFlow Authors. All Rights Reserved.

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
#ifndef TENSORFLOW_LITE_KERNELS_TEST_MULTIPLY_H_
#define TENSORFLOW_LITE_KERNELS_TEST_MULTIPLY_H_
#if GOOGLE_TEST
#include <gtest/gtest.h>
#include "tensorflow/lite/kernels/test_util.h"
#else
#include "test_util.h"
#endif
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"

namespace tflite {
namespace mul {

#if GOOGLE_TEST
using ::testing::ElementsAreArray;
#endif

class BaseMulOpModel : public SingleOpModel {
 public:
  BaseMulOpModel(const TensorData& input1, const TensorData& input2,
                 const TensorData& output,
                 ActivationFunctionType activation_type) {
    input1_ = AddInput(input1);
    input2_ = AddInput(input2);
    output_ = AddOutput(output);
    SetBuiltinOp(BuiltinOperator_MUL, BuiltinOptions_MulOptions,
                 CreateMulOptions(builder_, activation_type).Union());
    BuildInterpreter({GetShape(input1_), GetShape(input2_)});
  }

  int input1() { return input1_; }
  int input2() { return input2_; }

 protected:
  int input1_;
  int input2_;
  int output_;
};

class FloatMulOpModel : public BaseMulOpModel {
 public:
  using BaseMulOpModel::BaseMulOpModel;

  std::vector<float> GetOutput() { return ExtractVector<float>(output_); }
  std::vector<float> GetInput(int index) { assert(index >=0 && index <output_); return ExtractVector<float>(index); }
};

class IntegerMulOpModel : public BaseMulOpModel {
 public:
  using BaseMulOpModel::BaseMulOpModel;

  std::vector<int32_t> GetOutput() { return ExtractVector<int32_t>(output_); }
};

// For quantized Mul, the error shouldn't exceed (2*step + step^2).
// The param min=-1.0 & max=1.0 is used in the following tests.
// The tolerance value is ~0.0157.
const float kQuantizedStep = 2.0 / 255.0;
const float kQuantizedTolerance =
    2.0 * kQuantizedStep + kQuantizedStep * kQuantizedStep;
const float kQuantizedStepInt16 = 2.0 / 32767.0;
const float kQuantizedToleranceInt16 =
    2.0 * kQuantizedStepInt16 + kQuantizedStepInt16 * kQuantizedStepInt16;

class QuantizedMulOpModel : public BaseMulOpModel {
 public:
  using BaseMulOpModel::BaseMulOpModel;

  template <typename integer_dtype>
  std::vector<float> GetDequantizedOutput() {
    return Dequantize<integer_dtype>(ExtractVector<integer_dtype>(output_),
                                     GetScale(output_), GetZeroPoint(output_));
  }

  std::vector<float> GetDequantizedOutputInt16() {
    return Dequantize<int16_t>(ExtractVector<int16_t>(output_),
                               GetScale(output_), GetZeroPoint(output_));
  }
};

}  // namespace
}  // namespace tflite

#endif
