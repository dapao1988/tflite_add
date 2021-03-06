/*
 * demo_add.cc
 *  Copyright © 2018年 rokid. All rights reserved.
 *
 *  Created on: Dec 29, 2019
 *      Author: Wenbing.Wang
 */

#if GOOGLE_TEST
#include <gtest/gtest.h>
#endif
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
//#include "tensorflow/lite/kernels/test_util.h"
#include "test_util.h"
#include "tensorflow/lite/model.h"
#include "add_test.h"
#include "mul_test.h"
#include "tensorflow/lite/schema/schema_generated.h"

using namespace tflite;
using namespace tflite::add;
using namespace tflite::mul;

void tensor_add() {
    FloatAddOpModel m({TensorType_FLOAT32, {1, 2, 2, 1}},
                        {TensorType_FLOAT32, {1, 2, 2, 1}},
                        {TensorType_FLOAT32, {}}, ActivationFunctionType_NONE);
    m.PopulateTensor<float>(m.input1(), {-2.0, 0.2, 0.7, 0.8});
    m.PopulateTensor<float>(m.input2(), {0.1, 0.2, 0.3, 0.5});
    m.Invoke();
    //EXPECT_THAT(m.GetOutput(), ElementsAreArray({-1.9, 0.4, 1.0, 1.3}));
    const std::vector<float> & in0 = m.GetInput(0);
    const std::vector<float> & in1 = m.GetInput(1);
    const std::vector<float> & out = m.GetOutput();

    printf("\ninput0:\n");
    for (auto item:in0) {
        printf("%f ", item);
    }
    printf("\ninput1:\n");
    for (auto item:in1) {
        printf("%f ", item);
    }
    printf("\noutput0:\n");
    for (auto item:out) {
        printf("%f ", item);
    }
    printf ("\nadd finished!\n");
}
void tensor_mul() {
    FloatMulOpModel m({TensorType_FLOAT32, {1, 2, 2, 1}},
                        {TensorType_FLOAT32, {1, 2, 2, 1}},
                        {TensorType_FLOAT32, {}}, ActivationFunctionType_NONE);
    m.PopulateTensor<float>(m.input1(), {-2.0, 0.2, 0.7, 0.8});
    m.PopulateTensor<float>(m.input2(), {0.1, 0.2, 0.3, 0.5});
    m.Invoke();
    //EXPECT_THAT(m.GetOutput(), ElementsAreArray({-1.9, 0.4, 1.0, 1.3}));
    const std::vector<float> & in0 = m.GetInput(0);
    const std::vector<float> & in1 = m.GetInput(1);
    const std::vector<float> & out = m.GetOutput();

    printf("\ninput0:\n");
    for (auto item:in0) {
        printf("%f ", item);
    }
    printf("\ninput1:\n");
    for (auto item:in1) {
        printf("%f ", item);
    }
    printf("\noutput0:\n");
    for (auto item:out) {
        printf("%f ", item);
    }
    printf ("\nmul finished!\n");
}
int main (int argc, char* argv[]) {

    printf("start to add two tensors....\n");
    tensor_add();
    printf("add done!!\n");
    printf("start to mul two tensors....\n");
    tensor_mul();
    printf("mul done!!\n");

    printf ("exit program !!");
    return 0;
}
