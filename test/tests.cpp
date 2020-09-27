#include <iostream>
#include <gtest/gtest.h>
#include "matrix.hpp"

int main (int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    int rc = RUN_ALL_TESTS();
    return rc;
}

TEST (test_suite, init_row_major)
{
    linalg::mat_t mat1(2,2);
    mat1(0,1) = 1.0;
    ASSERT_EQ(mat1._data.size(), 4);
    ASSERT_EQ(mat1._data[1], 1.0);
}

TEST (test_suite, init_col_major)
{
    linalg::mat_t mat1(2,2, linalg::mat_fmt::col_major);
    mat1(0,1) = 1.0;
    EXPECT_EQ(mat1._data[2], 1.0);
}

TEST (test_suite, output)
{
    linalg::mat_t mat1(2,2, linalg::mat_fmt::col_major);
    mat1(0,1) = 1.0;
    std::ostringstream output;
    output << mat1;
    EXPECT_EQ(output.str(), "  0.0000e+00  1.0000e+00\n  0.0000e+00  0.0000e+00\n");
}

TEST (test_suite, diag_test)
{
    linalg::mat_t mat1(3,3);
    mat1(0,0) = 1.0;

    linalg::mat_t mat2(3,3), mat3(3,3), mat4(3,3);

    mat2(0,0) = 2.0;
    mat3(0,0) = 3.0;
    mat4(0,0) = 4.0;

    linalg::mat_t mat5 = (mat1 + mat2) + (mat3 + mat4);
    EXPECT_EQ(mat5(0,0), 10.0);

    linalg::mat_t mat6(3,3);
    mat6 = mat5;
    mat6 = mat2 + mat3;
    EXPECT_EQ(mat6(0,0), 5.0);

    mat6 = mat2 + (mat3 + mat4);
    EXPECT_EQ(mat6(0,0), 9.0);

    mat6 = (mat3 + mat4) + mat2;
    EXPECT_EQ(mat6(0,0), 9.0);
}
