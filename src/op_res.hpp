#ifndef OP_RES_HPP
#define OP_RES_HPP


#include <cstddef> // for size_t


namespace linalg
{

// ============================================================================

enum class mat_op_name // matrix operation name
{
    add,
    sub,
    mult,
};

// ============================================================================

// this is a type to carry matrix operation result, hence op_res_t.
// for example when user sets mat3 = mat1 * mat2, we construct a
// op_res_t object from mat1 * mat2 first and then assign it to mat3
// at calculation time.
template <typename lhs_t, typename rhs_t>
class op_res_t
{
public:
    op_res_t (const lhs_t& lhs, const rhs_t& rhs, mat_op_name op);

    double operator() (size_t i, size_t j) const;

    size_t nrow() const { return _nrow; }
    
    size_t ncol() const { return _ncol; }

    const lhs_t& _lhs;
    const rhs_t& _rhs;
    size_t _nrow; // non-const to be init'ed inside ctor
    size_t _ncol; // non-const to be init'ed inside ctor
    const mat_op_name _op;
};

// ----------------------------------------------------------------------------

template <typename lhs_t, typename rhs_t>
double op_res_t<lhs_t, rhs_t>::operator() (size_t i, size_t j) const
{
    double out = 0.0;
    switch (_op) {
        case mat_op_name::add: {
            out = _lhs(i, j) + _rhs(i, j);
            break;
        }
        case mat_op_name::sub: {
            out = _lhs(i, j) - _rhs(i, j);
            break;
        }
        case mat_op_name::mult: {
            assert(_lhs.ncol() == _rhs.nrow());
            for (size_t k = 0; k < _lhs.ncol(); ++k)
                out += _lhs(i, k) * _rhs(k, j);
            break;
        }
    }
    return out;
}

// ----------------------------------------------------------------------------

template <typename lhs_t, typename rhs_t>
op_res_t<lhs_t, rhs_t>::op_res_t (
    const lhs_t& lhs, const rhs_t& rhs, mat_op_name op)
  : _lhs(lhs), _rhs(rhs), _op(op)
{
    switch (_op) {
        case mat_op_name::add:
        case mat_op_name::sub:
        {
            assert(lhs.nrow() == rhs.nrow() &&
                lhs.ncol() == rhs.ncol());
            _nrow = lhs.nrow();
            _ncol = lhs.ncol();
            break;
        }
        case mat_op_name::mult: {
            assert(lhs.ncol() == rhs.nrow());
            _nrow = lhs.nrow();
            _ncol = rhs.ncol();
            break;
        }
    }
}

}


#endif // OP_RES_HPP
