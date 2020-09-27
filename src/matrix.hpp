#include <cstdio>
#include <iostream>
#include <vector>

#ifndef MATRIX_H
#define MATRIX_H

namespace linalg
{

// ============================================================================

enum class mat_fmt
{
    row_major,
    col_major,
};

// ============================================================================

enum class mat_op_name
{
    add,
    sub,
    mult,
    none = -1,
};

// ============================================================================

template <typename lhs_t, typename rhs_t>
class mat_op_t
{
public:
    mat_op_t (const lhs_t& lhs, const rhs_t& rhs, mat_op_name op);

    double operator() (size_t i, size_t j) const;

    const lhs_t& _lhs;
    const rhs_t& _rhs;
    const size_t _nrow;
    const size_t _ncol;
    const mat_op_name _op;
};

// ============================================================================

class mat_t
{
public:
    mat_t (size_t nrow, size_t ncol, mat_fmt fmt = mat_fmt::row_major);

    template <typename lhs_t, typename rhs_t>
    mat_t (const mat_op_t<lhs_t, rhs_t>& op);

    template <typename lhs_t, typename rhs_t>
    mat_t& operator= (const mat_op_t<lhs_t, rhs_t>& op);

    friend std::ostream& operator<< (std::ostream& os, const mat_t& mat);

    double& operator() (size_t i, size_t j);
    double operator() (size_t i, size_t j) const;

    size_t _nrow;
    size_t _ncol;
    std::vector<double> _data;
    mat_fmt _fmt{mat_fmt::row_major};
};

// ----------------------------------------------------------------------------

template <typename lhs_t, typename rhs_t>
double mat_op_t<lhs_t, rhs_t>::operator() (size_t i, size_t j) const
{
    double out = 0.0;
    switch (_op) {
        case mat_op_name::add: {
            out = _lhs(i, j) + _rhs(i, j);
            break;
        }
    }
    return out;
}

// ----------------------------------------------------------------------------

template <typename lhs_t, typename rhs_t>
mat_op_t<lhs_t, rhs_t>::mat_op_t (
    const lhs_t& lhs, const rhs_t& rhs, mat_op_name op)
  : _lhs(lhs), _rhs(rhs), _nrow(lhs._nrow), _ncol(lhs._ncol), _op(op)
{
}

// ----------------------------------------------------------------------------

template <typename lhs_t, typename rhs_t>
mat_t::mat_t (const mat_op_t<lhs_t, rhs_t>& op)
{
    _nrow = op._nrow;
    _ncol = op._ncol;
    _data.resize(op._ncol * op._nrow);
    for (size_t i = 0; i < _nrow; ++i)
        for (size_t j = 0; j < _ncol; ++j)
            operator()(i, j) = op(i,j);
}

// ----------------------------------------------------------------------------

template <typename lhs_t, typename rhs_t>
mat_t& mat_t::operator= (const mat_op_t<lhs_t, rhs_t>& op)
{
    for (size_t i = 0; i < _nrow; ++i)
        for (size_t j = 0; j < _ncol; ++j)
            operator()(i, j) = op(i,j);
    return *this;
}

// ----------------------------------------------------------------------------

template <typename lhs_t, typename rhs_t>
mat_op_t<mat_op_t<lhs_t, rhs_t>, mat_t> operator+ (
    const mat_op_t<lhs_t, rhs_t>& lhs, const mat_t& mat)
{
    return mat_op_t<mat_op_t<lhs_t, rhs_t>, mat_t>(lhs, mat, mat_op_name::add);
}

// ----------------------------------------------------------------------------

template <typename lhs_t, typename rhs_t>
mat_op_t<mat_t, mat_op_t<lhs_t, rhs_t>> operator+ (
    const mat_t& mat, const mat_op_t<lhs_t, rhs_t>& rhs)
{
    return mat_op_t<mat_t, mat_op_t<lhs_t, rhs_t>>(mat, rhs, mat_op_name::add);
}

// ----------------------------------------------------------------------------

template <typename llhs_t, typename lrhs_t, typename rlhs_t, typename rrhs_t>
mat_op_t<mat_op_t<llhs_t, lrhs_t>, mat_op_t<rlhs_t, rrhs_t>> operator+ (
    const mat_op_t<llhs_t, lrhs_t>& lhs,
    const mat_op_t<rlhs_t, rrhs_t>& rhs)
{
    return mat_op_t<mat_op_t<llhs_t, lrhs_t>, mat_op_t<rlhs_t, rrhs_t>>(
        lhs, rhs, mat_op_name::add);
}

// ----------------------------------------------------------------------------

mat_op_t<mat_t, mat_t> operator+ (const mat_t& l_mat, const mat_t& r_mat);


} // namespace linalg

#endif // MATRIX_H
