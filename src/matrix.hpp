#ifndef MATRIX_HPP
#define MATRIX_HPP


#include <cstddef> // size_t definition
#include <iostream>
#include <vector>
#include <cassert>
#include "stor.hpp"
#include "opr_res.hpp"


namespace linalg
{

class mat_t;


// ============================================================================

class vec_t
{
};

// ============================================================================

class mat_t
{
public:
    mat_t (stor_fmt_t fmt = stor_fmt_t::row_maj);

    mat_t (int nrow, int ncol, stor_fmt_t fmt = stor_fmt_t::row_maj);

    template <typename lhs_t, typename rhs_t>
    mat_t (const opr_res_t<lhs_t, rhs_t>& op); // implicit conversion 

    template <typename lhs_t, typename rhs_t>
    mat_t& operator= (const opr_res_t<lhs_t, rhs_t>& op);

    void assign (const double val) { _stor.assign(val); }

    double& operator() (int i, int j);

    double operator() (int i, int j) const;

    const std::vector<double>& data () const { return _stor.data(); }

    double data_at (const int idx) const;

    void resize (const int nrow, const int ncol);

    friend std::ostream& operator<< (std::ostream& os, const mat_t& mat);

    mat_stor_t _stor;
};

// ============================================================================

// this class interacts with opr_res_t. each class that can be an
// operand will have be implicitly convertible to oprnd_t, to interact
// with other operands. for example
// mat_t will interact with vec_t in vec14 = mat44 * vec14. the idea is that
// a matrix has an independant existance beyond mat operations.
class oprand_t
{
public:
    oprand_t (const mat_t& mat) : _stor(mat._stor) {}

    double operator() (size_t i, size_t j) const { return _stor(i, j); }

    size_t nrow () const { return _stor.nrow(); }

    size_t ncol () const { return _stor.ncol(); };

    stor_fmt_t fmt () const { return _stor.fmt(); }

    const mat_stor_t& _stor;
};

// ----------------------------------------------------------------------------

template <typename lhs_t, typename rhs_t>
mat_t::mat_t (const opr_res_t<lhs_t, rhs_t>& op)
:   _stor(op.fmt())
{
    _stor.resize(op.nrow(), op.ncol());
    for (size_t i = 0; i < op.nrow(); ++i)
        for (size_t j = 0; j < op.ncol(); ++j)
            operator()(i, j) = op(i,j);
}

// ----------------------------------------------------------------------------

template <typename lhs_t, typename rhs_t>
mat_t& mat_t::operator= (const opr_res_t<lhs_t, rhs_t>& op)
{
    if (!_stor.empty()) {
        assert(_stor.nrow() == op.nrow());
        assert(_stor.ncol() == op.ncol());
    } else {
        _stor.resize(op.nrow(), op.ncol());
    }
    for (size_t i = 0; i < op.nrow(); ++i)
        for (size_t j = 0; j < op.ncol(); ++j)
            operator()(i, j) = op(i,j);
    return *this;
}


} // namespace linalg


#include "mat_ops.hpp"


#endif // MATRIX_HPP
