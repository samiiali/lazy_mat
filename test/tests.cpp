#include <iostream>
#include <gtest/gtest.h>
#include "mat.hpp" // this includes stor.hpp as well ...
#include "vec.hpp"

int main (int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    int rc = RUN_ALL_TESTS();
    return rc;
}

TEST (test_suite, storage_test)
{
    linalg::stor_t stor0;
    stor0.resize({4,3,5});
    ASSERT_EQ(stor0.index({2,1,3}), 38);
    linalg::stor_t stor1;
    stor1.set_perm({2,1,0});
    stor1.resize({4,3,5});
    ASSERT_EQ(stor1.index({2,1,3}), 38);
    ASSERT_EQ(stor1.index({0,0,0}), 0);
    ASSERT_EQ(stor1.index({3,2,4}), 4*3*5-1);
    ASSERT_DEATH(stor1.index({3,3,4}), ".*");
    linalg::stor_t stor2;
    stor2.set_perm({0,1,2});
    stor2.resize({4,3,5});
    ASSERT_EQ(stor2.index({2,1,3}), 42);
    ASSERT_EQ(stor1.index({0,0,0}), 0);
    ASSERT_EQ(stor2.index({3,2,4}), 4*3*5-1);
    ASSERT_DEATH(stor2.index({3,3,4}), ".*");
    linalg::mat_stor_t stor9(linalg::stor_fmt_t::col_maj);
    stor9.resize(2,2);
    stor9(0,1) = 1.2;
    EXPECT_EQ(stor9.data_at(2), 1.2);
}

TEST (test_suite, empty_ctor)
{
    linalg::mat_t mat1(2,2);
    EXPECT_DEATH(mat1.resize(-1,1), ".*");
    EXPECT_DEATH(mat1.resize(1,-1), ".*");
    mat1.resize(1,2);
    ASSERT_EQ(mat1.data().size(), 2);
    mat1.resize(2,2);
    mat1(0,1) = 1.2;
    linalg::mat_t mat2;
    std::ostringstream output;
    output << mat2;
    EXPECT_EQ(output.str(), "\n");
    mat2 = mat1;
    linalg::mat_t mat3;
    mat3 = std::move(mat1);
    ASSERT_EQ(mat3.data_at(1), 1.2);
}

TEST (test_suite, init_row_maj)
{
    linalg::mat_t mat1(2,2);
    mat1(0,1) = 1.0;
    linalg::mat_t mat2(2,2);
    mat1 = mat1; // copy assignment to self
    mat1 = std::move(mat1); // move assignment to self
    ASSERT_EQ(mat1.data().size(), 4);
    ASSERT_EQ(mat1.data_at(1), 1.0);
    mat2 = std::move(mat1);
    ASSERT_EQ(mat2.data().size(), 4);
    ASSERT_EQ(mat2.data_at(1), 1.0);
}

TEST (test_suite, assign_failure)
{
    linalg::mat_t mat1(2,2);
    mat1(0,1) = 1.0;
    linalg::mat_t mat2(2,3);
    mat2 = mat1; // this copy should work ... dont argue with me
    EXPECT_EQ(mat2(0,1), 1.0);
}

TEST (test_suite, move_with_different_dim)
{
    linalg::mat_t mat1(2,2);
    mat1(0,1) = 1.2;
    linalg::mat_t mat2(1,2);
    mat2 = std::move(mat1);
    EXPECT_EQ(mat2.data_at(1), 1.2);
}

TEST (test_suite, output)
{
    linalg::mat_t mat1(2,2);
    mat1.assign(0.0);
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
    linalg::mat_t mat5;
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

TEST (test_suite, vec_print)
{
    linalg::vec_t vec1(3);
    vec1.assign(0.0);
    vec1(1) = 1.0;
    std::ostringstream oss;
    oss << vec1;
    EXPECT_EQ(oss.str(), "  0.0000e+00\n  1.0000e+00\n  0.0000e+00\n");
}

TEST (test_suite, vec_operation)
{
    linalg::vec_t vec1(3);
    linalg::vec_t vec3(2);
    linalg::vec_t vec4(3);
    vec1.assign(1.0);
    linalg::mat_t mat1(2,3);
    mat1.assign(2.0);
    linalg::vec_t vec2;
    std::ostringstream oss;
    oss << vec2;
    EXPECT_EQ(oss.str(), "\n");
    oss.str("");
    vec2 = mat1 * vec1;
    vec3 = mat1 * vec1;
    EXPECT_DEATH({vec4=mat1*vec1;}, ".*");
    oss << vec2;
    EXPECT_EQ(oss.str(), "  6.0000e+00\n  6.0000e+00\n");
}

TEST (test_suite, vec_op2)
{
    linalg::vec_t vec1(3, linalg::vec_type_t::row_vec);
    vec1.assign(2.0);
    vec1(1) = 3.5;
    EXPECT_EQ(vec1.data_at(1), 3.5);
    EXPECT_EQ(vec1.data()[1], 3.5);
    vec1.resize(5);
    EXPECT_EQ(vec1._type, linalg::vec_type_t::row_vec);
    vec1.resize(6, linalg::vec_type_t::col_vec);
    vec1.resize(6, linalg::vec_type_t::row_vec);
    linalg::mat_t mat1(6,6);
    mat1.assign(1.5);
    linalg::vec_t vec2 = vec1 * mat1;
    linalg::mat_t mat3(1,6);
}