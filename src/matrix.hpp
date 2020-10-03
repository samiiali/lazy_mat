#include <cstdio>
#include <iostream>
#include <vector>
#include <cassert>

#ifndef MATRIX_HPP
#define MATRIX_HPP

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
    size_t _nrow; // non-const to be init'ed inside ctor
    size_t _ncol; // non-const to be init'ed inside ctor
    const mat_op_name _op;
};

// ============================================================================

class mat_t
{
public:
    mat_t (mat_fmt fmt = mat_fmt::row_major);

    mat_t (size_t nrow, size_t ncol, mat_fmt fmt = mat_fmt::row_major);

    mat_t (const mat_t& rhs) = default;

    template <typename lhs_t, typename rhs_t>
    mat_t (const mat_op_t<lhs_t, rhs_t>& op);

    mat_t& operator= (const mat_t& rhs);

    mat_t& operator= (mat_t&& rhs);

    template <typename lhs_t, typename rhs_t>
    mat_t& operator= (const mat_op_t<lhs_t, rhs_t>& op);

    void assign (const double val);

    friend std::ostream& operator<< (std::ostream& os, const mat_t& mat);

    double& operator() (size_t i, size_t j);
    double operator() (size_t i, size_t j) const;

    size_t _nrow;
    size_t _ncol;
    std::vector<double> _data;
    mat_fmt _fmt{mat_fmt::row_major};
    bool _size_set;
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
        case mat_op_name::sub: {
            out = _lhs(i, j) - _rhs(i, j);
            break;
        }
        case mat_op_name::mult: {
            assert(_lhs._ncol == _rhs._nrow);
            for (size_t k = 0; k < _lhs._ncol; ++k)
                out += _lhs(i, k) * _rhs(k, j);
            break;
        }
    }
    return out;
}

// ----------------------------------------------------------------------------

template <typename lhs_t, typename rhs_t>
mat_op_t<lhs_t, rhs_t>::mat_op_t (
    const lhs_t& lhs, const rhs_t& rhs, mat_op_name op)
  : _lhs(lhs), _rhs(rhs), _op(op)
{
    switch (_op) {
        case mat_op_name::add: {
            assert(lhs._nrow == rhs._nrow && lhs._ncol == rhs._ncol);
            _nrow = lhs._nrow;
            _ncol = lhs._ncol;
            break;
        }
        case mat_op_name::sub: {
            assert(lhs._nrow == rhs._nrow && lhs._ncol == rhs._ncol);
            _nrow = lhs._nrow;
            _ncol = lhs._ncol;
            break;
        }
        case mat_op_name::mult: {
            assert(lhs._ncol == rhs._nrow);
            _nrow = lhs._nrow;
            _ncol = rhs._ncol;
            break;
        }
    }
}

// ----------------------------------------------------------------------------

template <typename lhs_t, typename rhs_t>
mat_t::mat_t (const mat_op_t<lhs_t, rhs_t>& op)
{
    _nrow = op._nrow;
    _ncol = op._ncol;
    _data.resize(op._ncol * op._nrow);
    _size_set = true;
    for (size_t i = 0; i < _nrow; ++i)
        for (size_t j = 0; j < _ncol; ++j)
            operator()(i, j) = op(i,j);
}

// ----------------------------------------------------------------------------

template <typename lhs_t, typename rhs_t>
mat_t& mat_t::operator= (const mat_op_t<lhs_t, rhs_t>& op)
{
    if (_size_set) {
        assert(this->_nrow == op._nrow && this->_ncol == op._ncol);
    } else {
        _nrow = op._nrow;
        _ncol = op._ncol;
        _data.resize(_nrow * _ncol);
        _size_set = true;
    }
    for (size_t i = 0; i < _nrow; ++i)
        for (size_t j = 0; j < _ncol; ++j)
            operator()(i, j) = op(i,j);
    return *this;
}


// including a header file for operator overloading
#include "mat_ops.hpp"


} // namespace linalg

#endif // MATRIX_HPP
