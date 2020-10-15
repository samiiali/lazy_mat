#include "oprand.hpp"
#include "mat.hpp"
#include "vec.hpp"


namespace linalg
{


oprand_t::oprand_t (const mat_t& mat)
:   _stor(mat._stor)
{
}

// ----------------------------------------------------------------------------

oprand_t::oprand_t (const vec_t& vec)
:   _stor(vec._stor)
{
}

// ----------------------------------------------------------------------------

opr_res_t<oprand_t, oprand_t> operator+ (
    const oprand_t& l_oprand, const oprand_t& r_oprand
) {
    return opr_res_t<oprand_t, oprand_t>(
        l_oprand, r_oprand, mat_op_name::add);
}

// ----------------------------------------------------------------------------

opr_res_t<oprand_t, oprand_t> operator- (
    const oprand_t& l_oprand, const oprand_t& r_oprand
) {
    return opr_res_t<oprand_t, oprand_t>(
        l_oprand, r_oprand, mat_op_name::sub);
}

// ----------------------------------------------------------------------------

opr_res_t<oprand_t, oprand_t> operator* (
    const oprand_t& l_oprand, const oprand_t& r_oprand
) {
    return opr_res_t<oprand_t, oprand_t>(
        l_oprand, r_oprand, mat_op_name::mult);
}


}