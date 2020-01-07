/*
 * demo_add.cc
 *  Copyright © 2018年 rokid. All rights reserved.
 *
 *  Created on: Dec 29, 2019
 *      Author: Wenbing.Wang
 */

#include <gtest/gtest.h>
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/kernels/test_util.h"
#include "tensorflow/lite/model.h"
#include "add_test.h"
#include "tensorflow/lite/schema/schema_generated.h"

using namespace tflite;
using namespace tflite::add;
int main (int argc, char* argv[]) {
    FloatAddOpModel m({TensorType_FLOAT32, {1, 2, 2, 1}},
                        {TensorType_FLOAT32, {1, 2, 2, 1}},
                        {TensorType_FLOAT32, {}}, ActivationFunctionType_NONE);
    m.PopulateTensor<float>(m.input1(), {-2.0, 0.2, 0.7, 0.8});
    m.PopulateTensor<float>(m.input2(), {0.1, 0.2, 0.3, 0.5});
    m.Invoke();
    EXPECT_THAT(m.GetOutput(), ElementsAreArray({-1.9, 0.4, 1.0, 1.3}));

    printf ("add finished!\n");
    return 0;
}
