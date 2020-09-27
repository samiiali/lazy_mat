#include "matrix.hpp"

namespace linalg
{

// ----------------------------------------------------------------------------

mat_t::mat_t (size_t nrow, size_t ncol, mat_fmt fmt)
:   _nrow(nrow), _ncol(ncol), _data(nrow * ncol), _fmt(fmt)
{
}

// ----------------------------------------------------------------------------

double& mat_t::operator() (size_t i, size_t j)
{
    if (_fmt == mat_fmt::row_major)
        return _data[i * _ncol + j];
    else
        return _data[j * _nrow + i];
}

// ----------------------------------------------------------------------------

double mat_t::operator() (size_t i, size_t j) const
{
    if (_fmt == mat_fmt::row_major)
        return _data[i * _ncol + j];
    else
        return _data[j * _nrow + i];
}

// ----------------------------------------------------------------------------

mat_op_t<mat_t, mat_t> operator+ (const mat_t& l_mat, const mat_t& r_mat)
{
    return mat_op_t<mat_t, mat_t>(l_mat, r_mat, mat_op_name::add);
}

// ----------------------------------------------------------------------------

std::ostream& operator<< (std::ostream& os, const mat_t& mat)
{
    for (size_t i = 0; i < mat._nrow; ++i) {
        for (size_t j = 0; j < mat._ncol; ++j) {
            char buf[13];
            snprintf(buf, 13, "%12.4e", mat(i, j));
            os << buf;
        }
        os << "\n";
    }
    return os;
}

// ----------------------------------------------------------------------------

} // namespace linalg
