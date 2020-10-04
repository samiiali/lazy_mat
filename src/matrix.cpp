#include "matrix.hpp"

namespace linalg
{

// ----------------------------------------------------------------------------

mat_t::mat_t (stor_fmt fmt) 
:   _stor(fmt)
{
}

// ----------------------------------------------------------------------------

mat_t::mat_t (int nrow, int ncol, stor_fmt fmt)
:   _stor({nrow, ncol}, fmt)
{
}

// ----------------------------------------------------------------------------

mat_t& mat_t::operator= (mat_t&& rhs)
{
    if (&rhs == this)
        return *this;
    if (!empty()) {
        assert(nrow() == rhs.nrow() && ncol() == rhs.ncol());
        _stor = std::move(rhs._stor);
    } else {
        _stor = std::move(rhs._stor);
    }
    return *this;
}

// ----------------------------------------------------------------------------

double& mat_t::operator() (int i, int j)
{
    return _stor({i,j});
}

// ----------------------------------------------------------------------------

double mat_t::operator() (int i, int j) const
{
    return _stor({i,j});
}

// ----------------------------------------------------------------------------

void mat_t::assign (const double val)
{
    _stor.assign(val);
}

// ----------------------------------------------------------------------------

const std::vector<double>& mat_t::data () const
{
    return _stor._data;
}

// ----------------------------------------------------------------------------

op_res_t<mat_t, mat_t> operator+ (const mat_t& l_mat, const mat_t& r_mat)
{
    return op_res_t<mat_t, mat_t>(l_mat, r_mat, mat_op_name::add);
}

// ----------------------------------------------------------------------------

op_res_t<mat_t, mat_t> operator- (const mat_t& l_mat, const mat_t& r_mat)
{
    return op_res_t<mat_t, mat_t>(l_mat, r_mat, mat_op_name::sub);
}

// ----------------------------------------------------------------------------

op_res_t<mat_t, mat_t> operator* (const mat_t& l_mat, const mat_t& r_mat)
{
    return op_res_t<mat_t, mat_t>(l_mat, r_mat, mat_op_name::mult);
}

// ----------------------------------------------------------------------------

std::ostream& operator<< (std::ostream& os, const mat_t& mat)
{
    if (mat.empty()) {
        os << "\n";
        return os;
    }
    for (size_t i = 0; i < mat.nrow(); ++i) {
        for (size_t j = 0; j < mat.ncol(); ++j) {
            char buf[13];
            snprintf(buf, 13, "%12.4e", mat(i, j));
            os << buf;
        }
        os << "\n";
    }
    return os;
}


} // namespace linalg
