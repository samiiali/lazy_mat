#include <iostream>
#include <gtest/gtest.h>
#include "matrix.hpp"

int main (int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    int rc = RUN_ALL_TESTS();
    return rc;
}

TEST (test_suite, empty_ctor)
{
    linalg::mat_t mat1(2,2);
    mat1(0,1) = 1.2;
    linalg::mat_t mat2;
    mat2 = mat1;
    linalg::mat_t mat3(linalg::mat_fmt::col_major);
    mat3 = std::move(mat1);
    ASSERT_EQ(mat3._data[1], 1.2);
}

TEST (test_suite, init_row_major)
{
    linalg::mat_t mat1(2,2);
    mat1(0,1) = 1.0;
    linalg::mat_t mat2(2,2);
    mat1 = mat1; // copy assignment to self
    mat1 = std::move(mat1); // move assignment to self
    ASSERT_EQ(mat1._data.size(), 4);
    ASSERT_EQ(mat1._data[1], 1.0);
    mat2 = std::move(mat1);
    ASSERT_EQ(mat2._data.size(), 4);
    ASSERT_EQ(mat2._data[1], 1.0);
}

TEST (test_suite, assign_failure)
{
    EXPECT_DEATH({
            linalg::mat_t mat1(2,2);
            mat1(0,1) = 1.0;
            linalg::mat_t mat2(2,3);
            mat2 = mat1;
        }, ".*");
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

TEST (test_suite, mult_test)
{
    linalg::mat_t mat1(3,2);
    linalg::mat_t mat2(2,3);
    mat1.assign(0.0);
    mat2.assign(0.0);
    mat1(0,0) = mat1(0,1) = mat2(0,0) = mat2(1,0) = 1.0;
    linalg::mat_t mat3 = mat1 * mat2;
    EXPECT_EQ(mat3(0,0), 2.0);
    linalg::mat_t mat5(linalg::mat_fmt::col_major);
    mat5 = mat1 * mat2;
    EXPECT_EQ(mat5(0,0), 2.0);
    EXPECT_DEATH({
            linalg::mat_t mat4(2,2);
            mat4 = mat1 * mat2;
        }, ".*");
}

TEST (test_suite, sub_test)
{
    linalg::mat_t mat1(3,2);
    linalg::mat_t mat2(3,2);
    mat1.assign(0.0);
    mat2.assign(0.0);
    mat1(0,0) = mat1(0,1) = 1.0;
    mat2(1,0) = mat1(1,1) = 1.0;
    linalg::mat_t mat3 = mat1 - mat2;
    EXPECT_EQ(mat3(0,0), 1.0);
    EXPECT_EQ(mat3(1,0), -1.0);
}
