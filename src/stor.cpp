#include <vector>
#include <cstddef>
#include <cassert>
#include <initializer_list>
#include "cstdio"
#include "stor.hpp"

namespace linalg
{

// ----------------------------------------------------------------------------

stor_t::stor_t (const stor_fmt fmt)
:   _fmt(fmt)
{
}

// ----------------------------------------------------------------------------

void stor_t::resize (
    const std::initializer_list<size_t>& dim,
    const stor_fmt fmt
) {
    _dim = dim;
    _fmt = fmt;
    size_t data_size = 1;
    for (size_t i1 = 0; i1 < dim.size(); ++i1)
        data_size *= _dim[i1];
    if (data_size != _data.size())
        _data.resize(data_size);
}

// ----------------------------------------------------------------------------

void stor_t::resize (const std::initializer_list<size_t>& dim)
{
    resize(dim, _fmt);
}

// ----------------------------------------------------------------------------

double& stor_t::operator() (const std::initializer_list<size_t>& indices)
{
    return _data[index(indices)];
}

// ----------------------------------------------------------------------------

double stor_t::operator() (const std::initializer_list<size_t>& indices) const
{
    return _data[index(indices)];
}

// ----------------------------------------------------------------------------

size_t stor_t::index (const std::initializer_list<size_t>& indices) const
{
    assert(_dim.size() == indices.size());
    size_t idx = 0;
    if (_fmt == stor_fmt::col_maj) {
        auto fwd = indices.begin();
        size_t n_idx = 1;
        for (size_t i_dim : _dim) {
            idx += *fwd * n_idx;
            assert(*(fwd++) < i_dim);
            n_idx *= i_dim;
        }
    }
    if (_fmt == stor_fmt::row_maj) {
        auto bck = indices.end();
        size_t n_idx = 1;
        for (int i1 = _dim.size() - 1; i1 >= 0; --i1) {
            assert(*(--bck) < _dim[i1]);
            idx += *bck * n_idx;
            n_idx *= _dim[i1];
        }
    }
    return idx;
}

// ----------------------------------------------------------------------------

void stor_t::assign (const double val)
{
    _data.assign(_data.size(), val);
}



}