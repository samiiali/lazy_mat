#include <vector>
#include <map>
#include <cstddef>
#include <cassert>
#include <iostream>
#include <initializer_list>
#include "cstdio"
#include "stor.hpp"

namespace linalg
{

// ----------------------------------------------------------------------------

void stor_t::set_perm (const std::initializer_list<size_t>& perm)
{
    _perm = perm;
}

// ----------------------------------------------------------------------------

void stor_t::resize (const std::initializer_list<size_t>& dim)
{
    // in case this function is called before setting matrix permutation
    // we assign row major permutation by default
    if (_perm.empty()) {
        _perm.resize(dim.size());
        for (size_t i1 = 0; i1 < dim.size(); ++i1)
            _perm[i1] = dim.size() - i1 - 1;
    }
    //
    assert(_perm.size() == dim.size());
    _dim = dim;
    _perm_dim.resize(dim.size());
    _perm_dim[_perm[0]] = 1;
    size_t data_size = _dim[0];
    for (size_t i1 = 1; i1 < dim.size(); ++i1) {
        _perm_dim[_perm[i1]] = _perm_dim[_perm[i1-1]] * _dim[_perm[i1-1]];
        data_size *= _dim[i1];
    }
    _data.resize(data_size);
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
    auto idx_i = indices.begin();
    for (size_t i1 = 0; i1 < _dim.size(); ++i1) {
        assert(*idx_i < _dim[i1]);
        idx += *(idx_i++) * _perm_dim[i1];
    }
    assert(idx < _data.size());
    return idx;
}

// ----------------------------------------------------------------------------

void stor_t::assign (const double val)
{
    _data.assign(_data.size(), val);
}

// ----------------------------------------------------------------------------

mat_stor_t::mat_stor_t (stor_fmt_t fmt)
:   _fmt(fmt)
{
    assert(fmt == stor_fmt_t::col_maj || fmt == stor_fmt_t::row_maj);
    if (fmt == stor_fmt_t::row_maj)
        _stor.set_perm({1,0});
    else
        _stor.set_perm({0,1});
}

// ----------------------------------------------------------------------------

void mat_stor_t::resize (const size_t nrow, const size_t ncol)
{
    _stor.resize({nrow, ncol});
}

// ----------------------------------------------------------------------------

mat_stor_t& mat_stor_t::operator= (mat_stor_t&& rhs)
{
    if (&rhs == this)
        return *this;
    _stor = std::move(rhs._stor);
    return *this;
}


}