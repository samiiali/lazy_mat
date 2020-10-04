#include <cstddef> // size_t definition
#include <iostream>
#include <vector>
#include <cassert>
#include "stor.hpp"

#ifndef MATRIX_HPP
#define MATRIX_HPP

namespace linalg
{

// ============================================================================

enum class mat_op_name // matrix operation name
{
    add,
    sub,
    mult,
};

// ============================================================================

// this is a type to carry matrix operation result, hence op_res_t.
// for example when user sets mat3 = mat1 * mat2, we construct a
// op_res_t object from mat1 * mat2 first and then assign it to mat3
// at calculation time.
template <typename lhs_t, typename rhs_t>
class op_res_t
{
public:
    op_res_t (const lhs_t& lhs, const rhs_t& rhs, mat_op_name op);

    double operator() (size_t i, size_t j) const;

    size_t nrow() const { return _nrow; }
    
    size_t ncol() const { return _ncol; }

    const lhs_t& _lhs;
    const rhs_t& _rhs;
    size_t _nrow; // non-const to be init'ed inside ctor
    size_t _ncol; // non-const to be init'ed inside ctor
    const mat_op_name _op;
};

// ============================================================================

// this class interacts with op_res_t. each class that can be an
// operand will have an oprnd_t, to interact with other operands. for example
// mat_t will interact with vec_t in vec14 = mat44 * vec14. the idea is that
// a matrix has an independant existance beyond mat operations, and we want it
// to have an operand instead of being an operand (favor composition
// over inheritance).
class oprnd_t
{
    oprnd_t () {}
};

// ============================================================================

class mat_t
{
public:
    mat_t (stor_fmt fmt = stor_fmt::row_maj);

    mat_t (int nrow, int ncol, stor_fmt fmt = stor_fmt::row_maj);

    mat_t (const mat_t& rhs) = default;

    template <typename lhs_t, typename rhs_t>
    mat_t (const op_res_t<lhs_t, rhs_t>& op);

    mat_t& operator= (const mat_t& rhs) = default;

    mat_t& operator= (mat_t&& rhs);

    template <typename lhs_t, typename rhs_t>
    mat_t& operator= (const op_res_t<lhs_t, rhs_t>& op);

    void assign (const double val);

    friend std::ostream& operator<< (std::ostream& os, const mat_t& mat);

    double& operator() (int i, int j);

    double operator() (int i, int j) const;

    const std::vector<double>& data () const;

    size_t nrow () const { return _stor._dim[0]; }

    size_t ncol () const { return _stor._dim[1]; };

    bool empty () const { return _stor._dim.empty(); }

    stor_t _stor;
};

// ----------------------------------------------------------------------------

template <typename lhs_t, typename rhs_t>
double op_res_t<lhs_t, rhs_t>::operator() (size_t i, size_t j) const
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
            assert(_lhs.ncol() == _rhs.nrow());
            for (size_t k = 0; k < _lhs.ncol(); ++k)
                out += _lhs(i, k) * _rhs(k, j);
            break;
        }
    }
    return out;
}

// ----------------------------------------------------------------------------

template <typename lhs_t, typename rhs_t>
op_res_t<lhs_t, rhs_t>::op_res_t (
    const lhs_t& lhs, const rhs_t& rhs, mat_op_name op)
  : _lhs(lhs), _rhs(rhs), _op(op)
{
    switch (_op) {
        case mat_op_name::add:
        case mat_op_name::sub:
        {
            assert(lhs.nrow() == rhs.nrow() &&
                lhs.ncol() == rhs.ncol());
            _nrow = lhs.nrow();
            _ncol = lhs.ncol();
            break;
        }
        case mat_op_name::mult: {
            assert(lhs.ncol() == rhs.nrow());
            _nrow = lhs.nrow();
            _ncol = rhs.ncol();
            break;
        }
    }
}

// ----------------------------------------------------------------------------

template <typename lhs_t, typename rhs_t>
mat_t::mat_t (const op_res_t<lhs_t, rhs_t>& op)
{
    _stor._dim = {op._nrow, op._ncol};
    _stor._data.resize(op._nrow * op._ncol);
    for (size_t i = 0; i < op._nrow; ++i)
        for (size_t j = 0; j < op._ncol; ++j)
            operator()(i, j) = op(i,j);
}

// ----------------------------------------------------------------------------

template <typename lhs_t, typename rhs_t>
mat_t& mat_t::operator= (const op_res_t<lhs_t, rhs_t>& op)
{
    if (!_stor._dim.empty()) {
        assert(nrow() == op._nrow);
        assert(ncol() == op._ncol);
    } else {
        _stor._dim = {op._nrow, op._ncol};
        _stor._data.resize(op._nrow * op._ncol);
    }
    for (size_t i = 0; i < op._nrow; ++i)
        for (size_t j = 0; j < op._ncol; ++j)
            operator()(i, j) = op(i,j);
    return *this;
}


// including a header file for operator overloading
#include "mat_ops.hpp"


} // namespace linalg

#endif // MATRIX_HPP
