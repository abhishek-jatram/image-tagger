#include "gtest/gtest.h"
#include "engine/common/types/tensor3d.hpp"

TEST(Tensor3DTest, CreateTensor) {
    Tensor3D<int> tensor(2,5,1);
    EXPECT_NE(tensor.data(), nullptr);
}

// TEST(Tensor3DTest, CreateTensorFromData) {
//     int data[1][5][2] = {
//         {
//             {1,2},
//             {3,4},
//             {5,6},
//             {7,8},
//             {9,10}
//         }
//     };
//     Tensor3D<int> tensor(2,5,1, **data);
//     EXPECT_EQ(tensor(1,1,0), data[0][1][1]);
// }

// TEST(Tensor3DTest, DestroyTensor) {
//     Tensor3D<int>* tensor_ptr = new Tensor3D<int> (2,5,1);
//     int* data = tensor_ptr->data();
//     delete tensor_ptr;
//     EXPECT_EQ(data, nullptr);
// }

// TEST(Tensor3DTest, TransposeTensor) {
//     int data[1][5][2] = {
//         {
//             {1,2},
//             {3,4},
//             {5,6},
//             {7,8},
//             {9,10}
//         }
//     };
//     Tensor3D<int> tensor(2,5,1, **data);
//     EXPECT_EQ(tensor(1,2,0), data[0][2][1]);

//     Tensor3D<int> transposed_tensor = tensor.Transpose(Dimension::Y, Dimension::X, Dimension::Z);
//     EXPECT_EQ(tensor(2,1,0), data[0][2][1]);
// }
