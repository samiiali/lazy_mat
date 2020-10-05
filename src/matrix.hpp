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

// this class interacts with opr_res_t. each class that can be an
// operand will have an oprnd_t, to interact with other operands. for example
// mat_t will interact with vec_t in vec14 = mat44 * vec14. the idea is that
// a matrix has an independant existance beyond mat operations, and we want it
// to have an operand instead of being an operand (favor composition
// over inheritance).
class oprand_t
{
public:
    oprand_t (const mat_t& mat);

    double operator() (size_t i, size_t j) const;

    size_t nrow () const { return _stor._dim[0]; }

    size_t ncol () const { return _stor._dim[1]; };

    const stor_t& _stor;
};

// ============================================================================

class vec_t
{
};

// ============================================================================

class mat_t
{
public:
    mat_t (stor_fmt fmt = stor_fmt::row_maj);

    mat_t (int nrow, int ncol, stor_fmt fmt = stor_fmt::row_maj);

    mat_t (const mat_t& rhs) = default;

    template <typename lhs_t, typename rhs_t>
    mat_t (const opr_res_t<lhs_t, rhs_t>& op);

    mat_t& operator= (const mat_t& rhs) = default;

    mat_t& operator= (mat_t&& rhs); // required for move to self

    template <typename lhs_t, typename rhs_t>
    mat_t& operator= (const opr_res_t<lhs_t, rhs_t>& op);

    void assign (const double val);

    friend std::ostream& operator<< (std::ostream& os, const mat_t& mat);

    double& operator() (int i, int j);

    double operator() (int i, int j) const;

    const std::vector<double>& data () const;

    double data_at (const int idx) const;

    void resize (const int nrow, const int ncol);

    size_t nrow () const { return _stor._dim[0]; }

    size_t ncol () const { return _stor._dim[1]; };

    bool empty () const { return _stor._dim.empty(); }

    stor_t _stor;
};

// ----------------------------------------------------------------------------

template <typename lhs_t, typename rhs_t>
mat_t::mat_t (const opr_res_t<lhs_t, rhs_t>& op)
{
    _stor.resize({op.nrow(), op.ncol()});
    for (size_t i = 0; i < op.nrow(); ++i)
        for (size_t j = 0; j < op.ncol(); ++j)
            operator()(i, j) = op(i,j);
}

// ----------------------------------------------------------------------------

template <typename lhs_t, typename rhs_t>
mat_t& mat_t::operator= (const opr_res_t<lhs_t, rhs_t>& op)
{
    if (!empty()) {
        assert(nrow() == op.nrow());
        assert(ncol() == op.ncol());
    } else {
        _stor.resize({op.nrow(), op.ncol()});
    }
    for (size_t i = 0; i < op.nrow(); ++i)
        for (size_t j = 0; j < op.ncol(); ++j)
            operator()(i, j) = op(i,j);
    return *this;
}


} // namespace linalg


#include "mat_ops.hpp"


#endif // MATRIX_HPP
