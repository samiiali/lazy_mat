#include "vec.hpp"
#include "stor.hpp"

namespace linalg

{

// ----------------------------------------------------------------------------

vec_t::vec_t (const vec_type_t vec_type)
:   _type(vec_type)
{
}

// ----------------------------------------------------------------------------

vec_t::vec_t (const int size, vec_type_t vec_type)
:   _type(vec_type)
{
    assert(0 < size);
    assert(vec_type_t::col_vec == vec_type || vec_type_t::row_vec == vec_type);
    if (vec_type_t::col_vec == vec_type)
        _stor.resize(size_t(size), 1);
    else
        _stor.resize(1, size_t(size));
}

// ----------------------------------------------------------------------------

double vec_t::operator() (const int idx) const
{
    assert(0 <= idx);
    return _stor.data_at(size_t(idx));
}

// ----------------------------------------------------------------------------

double& vec_t::operator() (const int idx)
{
    assert(0 <= idx);
    return _stor.data_at(size_t(idx));
}

// ----------------------------------------------------------------------------

double vec_t::data_at (const int idx) const
{
    assert(0 <= idx);
    return _stor.data_at(size_t(idx));
}

// ----------------------------------------------------------------------------

void vec_t::resize (const int size)
{
    resize(size, _type);
}

// ----------------------------------------------------------------------------

void vec_t::resize (const int size, const vec_type_t type)
{
    assert(0 < size);
    assert(vec_type_t::col_vec == type || vec_type_t::row_vec == type);
    if (vec_type_t::col_vec == type)
        _stor.resize(size_t(size), 1);
    else
        _stor.resize(1, size_t(size));
}

// ----------------------------------------------------------------------------

std::ostream& operator<< (std::ostream& os, const vec_t& mat)
{
    if (mat._stor.empty()) {
        os << "\n";
        return os;
    }
    for (size_t i = 0; i < mat._stor.nrow(); ++i) {
        for (size_t j = 0; j < mat._stor.ncol(); ++j) {
            char buf[13];
            snprintf(buf, 13, "%12.4e", mat((i+1) * (j+1) - 1));
            os << buf;
        }
        os << "\n";
    }
    return os;
}


}