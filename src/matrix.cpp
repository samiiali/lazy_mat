#include "matrix.hpp"
#include "stor.hpp"

namespace linalg
{

// ----------------------------------------------------------------------------

oprand_t::oprand_t (const mat_t& mat)
:   _stor(mat._stor)
{
}

// ----------------------------------------------------------------------------

double oprand_t::operator() (size_t row, size_t col) const
{
    return _stor({row, col});
}

// ----------------------------------------------------------------------------

mat_t::mat_t (stor_fmt fmt) 
:   _stor(fmt)
{
}

// ----------------------------------------------------------------------------

mat_t::mat_t (int nrow, int ncol, stor_fmt fmt)
{
    assert(0 < nrow && 0 < ncol);
    _stor.resize({size_t(nrow), size_t(ncol)}, fmt);
}

// ----------------------------------------------------------------------------

mat_t& mat_t::operator= (mat_t&& rhs)
{
    if (&rhs == this)
        return *this;
    _stor = std::move(rhs._stor);
    return *this;
}

// ----------------------------------------------------------------------------

double& mat_t::operator() (int row, int col)
{
    assert (0 <= row && 0 <= col);
    return _stor({size_t(row), size_t(col)});
}

// ----------------------------------------------------------------------------

double mat_t::operator() (int row, int col) const
{
    assert (0 <= row && 0 <= col);
    return _stor({size_t(row), size_t(col)});
}

// ----------------------------------------------------------------------------

void mat_t::assign (const double val)
{
    _stor.assign(val);
}

// ----------------------------------------------------------------------------

void mat_t::resize (const int nrow, const int ncol)
{
    assert(0 < nrow && 0 < ncol);
    _stor.resize({size_t(nrow), size_t(ncol)});
}

// ----------------------------------------------------------------------------

const std::vector<double>& mat_t::data () const
{
    return _stor._data;
}

// ----------------------------------------------------------------------------

double mat_t::data_at (const int idx) const
{
    return _stor._data[idx];
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

// ----------------------------------------------------------------------------

opr_res_t<oprand_t, oprand_t> operator+ (
    const oprand_t& l_oprand, const oprand_t& r_oprand
) {
    return opr_res_t<oprand_t, oprand_t>(
        l_oprand, r_oprand, mat_op_name::add);
}

// ----------------------------------------------------------------------------

opr_res_t<oprand_t, oprand_t> operator- (
    const oprand_t& l_oprand, const oprand_t& r_oprand
) {
    return opr_res_t<oprand_t, oprand_t>(
        l_oprand, r_oprand, mat_op_name::sub);
}

// ----------------------------------------------------------------------------

opr_res_t<oprand_t, oprand_t> operator* (
    const oprand_t& l_oprand, const oprand_t& r_oprand
) {
    return opr_res_t<oprand_t, oprand_t>(
        l_oprand, r_oprand, mat_op_name::mult);
}


} // namespace linalg
