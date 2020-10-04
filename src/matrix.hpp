#ifndef MATRIX_HPP
#define MATRIX_HPP


#include <cstddef> // size_t definition
#include <iostream>
#include <vector>
#include <cassert>
#include "stor.hpp"
#include "op_res.hpp"
#include "mat_ops.hpp"


namespace linalg
{

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

    mat_t& operator= (mat_t&& rhs); // required for move to self

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


} // namespace linalg


#endif // MATRIX_HPP
