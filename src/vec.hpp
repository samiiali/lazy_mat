#ifndef VEC_HPP
#define VEC_HPP


#include <cstddef> // size_t definition
#include <iostream>
#include <vector>
#include <cassert>
#include "stor.hpp"
#include "opr_res.hpp"


namespace linalg
{


enum class vec_type_t
{
    row_vec,
    col_vec,
};


// ============================================================================

class vec_t
{
public:
    vec_t (const vec_type_t vec_type = vec_type_t::col_vec);

    vec_t (const int size, vec_type_t vec_type = vec_type_t::col_vec);

    template <typename lhs_t, typename rhs_t>
    vec_t (const opr_res_t<lhs_t, rhs_t>& op); // implicit conversion 

    template <typename lhs_t, typename rhs_t>
    vec_t& operator= (const opr_res_t<lhs_t, rhs_t>& op);

    void assign (const double val) { _stor.assign(val); }

    double& operator() (int i);

    double operator() (int i) const;

    const std::vector<double>& data () const { return _stor.data(); }

    double data_at (const int idx) const;

    void resize (const int size);

    void resize (const int size, const vec_type_t type);

    friend std::ostream& operator<< (std::ostream& os, const vec_t& vec);

    mat_stor_t _stor;
    vec_type_t _type;
};

// ----------------------------------------------------------------------------

template <typename lhs_t, typename rhs_t>
vec_t::vec_t (const opr_res_t<lhs_t, rhs_t>& op)
{
    assert(op.nrow() == 1 || op.ncol() == 1);
    _stor.resize(op.nrow(), op.ncol());
    for (size_t i = 0; i < op.nrow(); ++i)
        for (size_t j = 0; j < op.ncol(); ++j)
            operator()((i+1) * (j+1) - 1) = op(i,j);
}

// ----------------------------------------------------------------------------

template <typename lhs_t, typename rhs_t>
vec_t& vec_t::operator= (const opr_res_t<lhs_t, rhs_t>& op)
{
    if (!_stor.empty()) {
        assert(_stor.nrow() == op.nrow());
        assert(_stor.ncol() == op.ncol());
    } else {
        assert(op.nrow() == 1 || op.ncol() == 1);
        _stor.resize(op.nrow(), op.ncol());
    }
    for (size_t i = 0; i < op.nrow(); ++i)
        for (size_t j = 0; j < op.ncol(); ++j)
            operator()((i+1) * (j+1) - 1) = op(i,j);
    return *this;
}


} // namespace linalg



#endif // VEC_HPP
