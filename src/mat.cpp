#include "mat.hpp"
#include "stor.hpp"

namespace linalg
{

// ----------------------------------------------------------------------------

mat_t::mat_t ()
:   _stor(stor_fmt_t::row_maj)
{
}

// ----------------------------------------------------------------------------

mat_t::mat_t (int nrow, int ncol)
:   _stor(stor_fmt_t::row_maj)
{
    assert(0 < nrow && 0 < ncol);
    _stor.resize(size_t(nrow), size_t(ncol));
}

// ----------------------------------------------------------------------------

double& mat_t::operator() (int row, int col)
{
    assert (0 <= row && 0 <= col);
    return _stor(size_t(row), size_t(col));
}

// ----------------------------------------------------------------------------

double mat_t::operator() (int row, int col) const
{
    assert (0 <= row && 0 <= col);
    return _stor(size_t(row), size_t(col));
}

// ----------------------------------------------------------------------------

void mat_t::resize (const int nrow, const int ncol)
{
    assert(0 < nrow && 0 < ncol);
    _stor.resize(size_t(nrow), size_t(ncol));
}

// ----------------------------------------------------------------------------

double mat_t::data_at (const int idx) const
{
    assert(0 <= idx);
    return _stor.data_at(size_t(idx));
}

// ----------------------------------------------------------------------------

std::ostream& operator<< (std::ostream& os, const mat_t& mat)
{
    if (mat._stor.empty()) {
        os << "\n";
        return os;
    }
    for (size_t i = 0; i < mat._stor.nrow(); ++i) {
        for (size_t j = 0; j < mat._stor.ncol(); ++j) {
            char buf[13];
            snprintf(buf, 13, "%12.4e", mat(i, j));
            os << buf;
        }
        os << "\n";
    }
    return os;
}


} // namespace linalg
