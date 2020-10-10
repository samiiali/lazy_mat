#ifndef STORG_HPP
#define STORG_HPP


#include <cstddef>
#include <vector>
#include <initializer_list>


namespace linalg
{

// ============================================================================

enum class stor_fmt_t
{
    row_maj,
    col_maj,
};

// ============================================================================

// this is a general storage class, for a matrix or a verctor, or god
// knows, someday for a tensor !
class stor_t
{
public:
    stor_t (const stor_fmt_t fmt);

    void resize (const std::initializer_list<size_t>& dim);

    double& operator() (const std::initializer_list<size_t>& idx);

    double operator() (const std::initializer_list<size_t>& idx) const;

    size_t index (const std::initializer_list<size_t>& idx) const;

    void assign (const double val);

    stor_fmt_t _fmt;
    std::vector<size_t> _dim;
    std::vector<double> _data;
};

// ============================================================================

class mat_stor_t
{
public:
    mat_stor_t (stor_fmt_t fmt);

    double& operator() (size_t i, size_t j) { return _stor({i, j}); }

    double operator() (size_t i, size_t j) const { return _stor({i, j}); }

    size_t nrow () const { return _stor._dim[0]; }

    size_t ncol () const { return _stor._dim[1]; }

    bool empty () const { return _stor._dim.empty(); }

    const std::vector<double>& data () const { return _stor._data; }

    double data_at (const size_t idx) const {return _stor._data[idx]; }

    void assign (const double val) { _stor.assign(val); }

    void resize (const size_t nrow, const size_t ncol);

    stor_fmt_t fmt () const { return _stor._fmt; }

    stor_t _stor;
};


} // namespace linalg


#endif // STORG_HPP
