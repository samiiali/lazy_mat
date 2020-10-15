#ifndef STORG_HPP
#define STORG_HPP


#include <cstddef>
#include <vector>
#include <initializer_list>
#include <map>


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
    void set_perm (const std::initializer_list<size_t>& perm);

    void resize (const std::initializer_list<size_t>& dim);

    double& operator() (const std::initializer_list<size_t>& idx);

    double operator() (const std::initializer_list<size_t>& idx) const;

    size_t index (const std::initializer_list<size_t>& idx) const;

    void assign (const double val);

    std::vector<size_t> _dim;
    // we store a permutation for storing data, e.g. which dimension
    // is stored first ...
    std::vector<size_t> _perm;
    std::vector<size_t> _perm_dim;
    std::vector<double> _data;
};

// ============================================================================

class mat_stor_t
{
public:
    mat_stor_t (stor_fmt_t fmt = stor_fmt_t::row_maj);

    mat_stor_t (const mat_stor_t& rhs) = default;

    mat_stor_t& operator= (const mat_stor_t& rhs) = default;

    mat_stor_t& operator= (mat_stor_t&& rhs); // putting this for move to self

    double& operator() (size_t i, size_t j) { return _stor({i, j}); }

    double operator() (size_t i, size_t j) const { return _stor({i, j}); }

    size_t nrow () const { return _stor._dim[0]; }

    size_t ncol () const { return _stor._dim[1]; }

    bool empty () const { return _stor._dim.empty(); }

    const std::vector<double>& data () const { return _stor._data; }

    double data_at (const size_t idx) const { return _stor._data[idx]; }

    double& data_at (const size_t idx) { return _stor._data[idx]; }

    void assign (const double val) { _stor.assign(val); }

    void resize (const size_t nrow, const size_t ncol);

    stor_fmt_t fmt () const { return _fmt; }

    std::initializer_list<size_t> fmt_init_list (const stor_fmt_t fmt);

    stor_fmt_t _fmt;
    stor_t _stor;
};


} // namespace linalg


#endif // STORG_HPP
