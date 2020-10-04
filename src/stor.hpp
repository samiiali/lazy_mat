#ifndef STORG_HPP
#define STORG_HPP


#include <cstddef>
#include <vector>
#include <initializer_list>


namespace linalg
{

// ============================================================================

enum class stor_fmt
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
    stor_t (const stor_fmt fmt = stor_fmt::row_maj);

    void resize (const std::initializer_list<size_t>& dim, const stor_fmt fmt);

    void resize (const std::initializer_list<size_t>& dim);

    double& operator() (const std::initializer_list<size_t>& idx);

    double operator() (const std::initializer_list<size_t>& idx) const;

    size_t index (const std::initializer_list<size_t>& idx) const;

    void assign (const double val);

    stor_fmt _fmt;
    std::vector<size_t> _dim;
    std::vector<double> _data;
};


} // namespace linalg


#endif // STORG_HPP
