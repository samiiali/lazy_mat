#include <cstddef>
#include <vector>

#ifndef STORG_HPP
#define STORG_HPP

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

    stor_t (const std::vector<int>& dim, const stor_fmt fmt);

    double& operator() (const std::vector<int>& idx);
    double operator() (const std::vector<int>& idx) const;

    void assign (const double val);

    std::vector<size_t> _dim;
    stor_fmt _fmt;
    std::vector<double> _data;
};


} // namespace linalg


#endif // STORG_HPP