#include "matrix.hpp"

namespace linalg
{

// ----------------------------------------------------------------------------

mat_t::mat_t () : size_set(false)
{
}

// ----------------------------------------------------------------------------

mat_t::mat_t (size_t nrow, size_t ncol, mat_fmt fmt)
:   _nrow(nrow), _ncol(ncol), _data(nrow * ncol), _fmt(fmt), size_set(true)
{
}

// ----------------------------------------------------------------------------

mat_t& mat_t::operator= (const mat_t& rhs)
{
    if (&rhs == this)
        return *this;
    if (size_set) {
        assert(_nrow == rhs._nrow && _ncol == rhs._ncol);
        _fmt = rhs._fmt;
        _data = rhs._data;
    } else {
        _nrow = rhs._nrow;
        _ncol = rhs._ncol;
        _fmt = rhs._fmt;
        _data = rhs._data;
        size_set = true;
    }
    return *this;
}

// ----------------------------------------------------------------------------

mat_t& mat_t::operator= (mat_t&& rhs)
{
    if (&rhs == this)
        return *this;
    if (size_set) {
        assert(_nrow == rhs._nrow && _ncol == rhs._ncol);
        _fmt = rhs._fmt;
        _data = std::move(rhs._data);
    } else {
        _nrow = rhs._nrow;
        _ncol = rhs._ncol;
        _fmt = rhs._fmt;
        _data = std::move(rhs._data);
        size_set = true;
    }
    return *this;
}

// ----------------------------------------------------------------------------

double& mat_t::operator() (size_t i, size_t j)
{
    assert(size_set);
    if (_fmt == mat_fmt::row_major)
        return _data[i * _ncol + j];
    else
        return _data[j * _nrow + i];
}

// ----------------------------------------------------------------------------

double mat_t::operator() (size_t i, size_t j) const
{
    assert(size_set);
    if (_fmt == mat_fmt::row_major)
        return _data[i * _ncol + j];
    else
        return _data[j * _nrow + i];
}

// ----------------------------------------------------------------------------

void mat_t::assign (const double val)
{
    _data.assign(_data.size(), val);
}

// ----------------------------------------------------------------------------

mat_op_t<mat_t, mat_t> operator+ (const mat_t& l_mat, const mat_t& r_mat)
{
    return mat_op_t<mat_t, mat_t>(l_mat, r_mat, mat_op_name::add);
}

// ----------------------------------------------------------------------------

mat_op_t<mat_t, mat_t> operator- (const mat_t& l_mat, const mat_t& r_mat)
{
    return mat_op_t<mat_t, mat_t>(l_mat, r_mat, mat_op_name::sub);
}

// ----------------------------------------------------------------------------

mat_op_t<mat_t, mat_t> operator* (const mat_t& l_mat, const mat_t& r_mat)
{
    return mat_op_t<mat_t, mat_t>(l_mat, r_mat, mat_op_name::mult);
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


} // namespace linalg
