#ifndef MAT_OPS_HPP
#define MAT_OPS_HPP


#include "opr_res.hpp"


namespace linalg
{

class oprand_t;

// ----------------------------------------------------------------------------

opr_res_t<oprand_t, oprand_t> operator+ (
    const oprand_t& l_oprand, const oprand_t& r_oprand);

// ----------------------------------------------------------------------------
// overloading + for mat_op + oprand
template <typename lhs_t, typename rhs_t>
opr_res_t<opr_res_t<lhs_t, rhs_t>, oprand_t> operator+ (
    const opr_res_t<lhs_t, rhs_t>& lhs, const oprand_t& oprand)
{
    return opr_res_t<opr_res_t<lhs_t, rhs_t>, oprand_t>(
        lhs, oprand, mat_op_name::add);
}

// ----------------------------------------------------------------------------
// overloading + for oprand + mat_op
template <typename lhs_t, typename rhs_t>
opr_res_t<oprand_t, opr_res_t<lhs_t, rhs_t>> operator+ (
    const oprand_t& oprand, const opr_res_t<lhs_t, rhs_t>& rhs)
{
    return opr_res_t<oprand_t, opr_res_t<lhs_t, rhs_t>>(
        oprand, rhs, mat_op_name::add);
}

// ----------------------------------------------------------------------------
// overloading + for mat_op + mat_op
template <typename llhs_t, typename lrhs_t, typename rlhs_t, typename rrhs_t>
opr_res_t<opr_res_t<llhs_t, lrhs_t>, opr_res_t<rlhs_t, rrhs_t>> operator+ (
    const opr_res_t<llhs_t, lrhs_t>& lhs,
    const opr_res_t<rlhs_t, rrhs_t>& rhs)
{
    return opr_res_t<opr_res_t<llhs_t, lrhs_t>, opr_res_t<rlhs_t, rrhs_t>>(
        lhs, rhs, mat_op_name::add);
}

// ----------------------------------------------------------------------------

opr_res_t<oprand_t, oprand_t> operator- (
    const oprand_t& l_oprand, const oprand_t& r_oprand);

// ----------------------------------------------------------------------------
// overloading + for mat_op - oprand
template <typename lhs_t, typename rhs_t>
opr_res_t<opr_res_t<lhs_t, rhs_t>, oprand_t> operator- (
    const opr_res_t<lhs_t, rhs_t>& lhs, const oprand_t& oprand)
{
    return opr_res_t<opr_res_t<lhs_t, rhs_t>, oprand_t>(
        lhs, oprand, mat_op_name::sub);
}

// ----------------------------------------------------------------------------
// overloading + for oprand - mat_op
template <typename lhs_t, typename rhs_t>
opr_res_t<oprand_t, opr_res_t<lhs_t, rhs_t>> operator- (
    const oprand_t& oprand, const opr_res_t<lhs_t, rhs_t>& rhs)
{
    return opr_res_t<oprand_t, opr_res_t<lhs_t, rhs_t>>(oprand, rhs, mat_op_name::sub);
}

// ----------------------------------------------------------------------------
// overloading + for mat_op - mat_op
template <typename llhs_t, typename lrhs_t, typename rlhs_t, typename rrhs_t>
opr_res_t<opr_res_t<llhs_t, lrhs_t>, opr_res_t<rlhs_t, rrhs_t>> operator- (
    const opr_res_t<llhs_t, lrhs_t>& lhs,
    const opr_res_t<rlhs_t, rrhs_t>& rhs)
{
    return opr_res_t<opr_res_t<llhs_t, lrhs_t>, opr_res_t<rlhs_t, rrhs_t>>(
        lhs, rhs, mat_op_name::sub);
}

// ----------------------------------------------------------------------------

opr_res_t<oprand_t, oprand_t> operator* (
    const oprand_t& l_oprand, const oprand_t& r_oprand);

// ----------------------------------------------------------------------------
// overloading * for mat_op * oprand
template <typename lhs_t, typename rhs_t>
opr_res_t<opr_res_t<lhs_t, rhs_t>, oprand_t> operator* (
    const opr_res_t<lhs_t, rhs_t>& lhs, const oprand_t& oprand)
{
    return opr_res_t<opr_res_t<lhs_t, rhs_t>, oprand_t>(
        lhs, oprand, mat_op_name::mult);
}

// ----------------------------------------------------------------------------
// overloading + for oprand + mat_op
template <typename lhs_t, typename rhs_t>
opr_res_t<oprand_t, opr_res_t<lhs_t, rhs_t>> operator* (
    const oprand_t& oprand, const opr_res_t<lhs_t, rhs_t>& rhs)
{
    return opr_res_t<oprand_t, opr_res_t<lhs_t, rhs_t>>(
        oprand, rhs, mat_op_name::mult);
}

// ----------------------------------------------------------------------------
// overloading + for mat_op + mat_op
template <typename llhs_t, typename lrhs_t, typename rlhs_t, typename rrhs_t>
opr_res_t<opr_res_t<llhs_t, lrhs_t>, opr_res_t<rlhs_t, rrhs_t>> operator* (
    const opr_res_t<llhs_t, lrhs_t>& lhs,
    const opr_res_t<rlhs_t, rrhs_t>& rhs)
{
    return opr_res_t<opr_res_t<llhs_t, lrhs_t>, opr_res_t<rlhs_t, rrhs_t>>(
        lhs, rhs, mat_op_name::mult);
}


}

#endif // MAT_OPS_HPP
