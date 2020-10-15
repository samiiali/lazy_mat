#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "cstddef"
#include "stor.hpp"


namespace linalg
{


class mat_t;
class vec_t;

// ============================================================================

// this class interacts with opr_res_t. each class that can be an
// operand will have be implicitly convertible to oprnd_t, to interact
// with other operands. for example
// mat_t will interact with vec_t in vec14 = mat44 * vec14. the idea is that
// a matrix has an independant existance beyond mat operations.
class oprand_t
{
public:
    oprand_t (const mat_t& mat);
    
    oprand_t (const vec_t& vec);

    double operator() (size_t i, size_t j) const { return _stor(i, j); }

    size_t nrow () const { return _stor.nrow(); }

    size_t ncol () const { return _stor.ncol(); };

    stor_fmt_t fmt () const { return _stor.fmt(); }

    const mat_stor_t& _stor;
};


} //namespace linalg


#endif // OPERAND_HPP