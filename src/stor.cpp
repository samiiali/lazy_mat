#include <vector>
#include <cstddef>
#include <cassert>
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

stor_t::stor_t (const std::vector<int>& dim, const stor_fmt fmt)
:   _dim(dim.size()), _fmt(fmt)
{
    size_t data_size = 1;
    for (size_t i1 = 0; i1 < dim.size(); ++i1) {
        assert(dim[i1] > 0);
        _dim[i1] = dim[i1];
        data_size *= _dim[i1];
    }
    _data.resize(data_size);
}

// ----------------------------------------------------------------------------

double& stor_t::operator() (const std::vector<int>& idx)
{
    assert(
        !_dim.empty() && 0 <= idx[0] && 0 <= idx[1] &&
        idx[0] < (int)_dim[0] && idx[1] < (int)_dim[1]);
    if (_fmt == stor_fmt::row_maj)
        return _data[idx[0] * _dim[1] + idx[1]];
    else
        return _data[idx[1] * _dim[0] + idx[0]];
}

// ----------------------------------------------------------------------------

double stor_t::operator() (const std::vector<int>& idx) const
{
    assert(
        !_dim.empty() && 0 <= idx[0] && 0 <= idx[1] &&
        idx[0] < (int)_dim[0] && idx[1] < (int)_dim[1]);
    if (_fmt == stor_fmt::row_maj)
        return _data[idx[0] * _dim[1] + idx[1]];
    else
        return _data[idx[1] * _dim[0] + idx[0]];
}

// ----------------------------------------------------------------------------

void stor_t::assign (const double val)
{
    _data.assign(_data.size(), val);
}



}