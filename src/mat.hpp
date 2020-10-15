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


// ============================================================================

class mat_t
{
public:
    mat_t ();

    mat_t (int nrow, int ncol);

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



#endif // MATRIX_HPP
