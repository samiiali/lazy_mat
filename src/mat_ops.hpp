// ----------------------------------------------------------------------------
// overloading + for mat_op + mat
template <typename lhs_t, typename rhs_t>
mat_op_t<mat_op_t<lhs_t, rhs_t>, mat_t> operator+ (
    const mat_op_t<lhs_t, rhs_t>& lhs, const mat_t& mat)
{
    return mat_op_t<mat_op_t<lhs_t, rhs_t>, mat_t>(lhs, mat, mat_op_name::add);
}

// ----------------------------------------------------------------------------
// overloading + for mat + mat_op
template <typename lhs_t, typename rhs_t>
mat_op_t<mat_t, mat_op_t<lhs_t, rhs_t>> operator+ (
    const mat_t& mat, const mat_op_t<lhs_t, rhs_t>& rhs)
{
    return mat_op_t<mat_t, mat_op_t<lhs_t, rhs_t>>(mat, rhs, mat_op_name::add);
}

// ----------------------------------------------------------------------------
// overloading + for mat_op + mat_op
template <typename llhs_t, typename lrhs_t, typename rlhs_t, typename rrhs_t>
mat_op_t<mat_op_t<llhs_t, lrhs_t>, mat_op_t<rlhs_t, rrhs_t>> operator+ (
    const mat_op_t<llhs_t, lrhs_t>& lhs,
    const mat_op_t<rlhs_t, rrhs_t>& rhs)
{
    return mat_op_t<mat_op_t<llhs_t, lrhs_t>, mat_op_t<rlhs_t, rrhs_t>>(
        lhs, rhs, mat_op_name::add);
}

// ----------------------------------------------------------------------------

mat_op_t<mat_t, mat_t> operator+ (const mat_t& l_mat, const mat_t& r_mat);

// ----------------------------------------------------------------------------
// overloading + for mat_op - mat
template <typename lhs_t, typename rhs_t>
mat_op_t<mat_op_t<lhs_t, rhs_t>, mat_t> operator- (
    const mat_op_t<lhs_t, rhs_t>& lhs, const mat_t& mat)
{
    return mat_op_t<mat_op_t<lhs_t, rhs_t>, mat_t>(lhs, mat, mat_op_name::sub);
}

// ----------------------------------------------------------------------------
// overloading + for mat - mat_op
template <typename lhs_t, typename rhs_t>
mat_op_t<mat_t, mat_op_t<lhs_t, rhs_t>> operator- (
    const mat_t& mat, const mat_op_t<lhs_t, rhs_t>& rhs)
{
    return mat_op_t<mat_t, mat_op_t<lhs_t, rhs_t>>(mat, rhs, mat_op_name::sub);
}

// ----------------------------------------------------------------------------
// overloading + for mat_op - mat_op
template <typename llhs_t, typename lrhs_t, typename rlhs_t, typename rrhs_t>
mat_op_t<mat_op_t<llhs_t, lrhs_t>, mat_op_t<rlhs_t, rrhs_t>> operator- (
    const mat_op_t<llhs_t, lrhs_t>& lhs,
    const mat_op_t<rlhs_t, rrhs_t>& rhs)
{
    return mat_op_t<mat_op_t<llhs_t, lrhs_t>, mat_op_t<rlhs_t, rrhs_t>>(
        lhs, rhs, mat_op_name::sub);
}

// ----------------------------------------------------------------------------

mat_op_t<mat_t, mat_t> operator- (const mat_t& l_mat, const mat_t& r_mat);

// ----------------------------------------------------------------------------
// overloading * for mat_op * mat
template <typename lhs_t, typename rhs_t>
mat_op_t<mat_op_t<lhs_t, rhs_t>, mat_t> operator* (
    const mat_op_t<lhs_t, rhs_t>& lhs, const mat_t& mat)
{
    return mat_op_t<mat_op_t<lhs_t, rhs_t>, mat_t>(
        lhs, mat, mat_op_name::mult);
}

// ----------------------------------------------------------------------------
// overloading + for mat + mat_op
template <typename lhs_t, typename rhs_t>
mat_op_t<mat_t, mat_op_t<lhs_t, rhs_t>> operator* (
    const mat_t& mat, const mat_op_t<lhs_t, rhs_t>& rhs)
{
    return mat_op_t<mat_t, mat_op_t<lhs_t, rhs_t>>(
        mat, rhs, mat_op_name::mult);
}

// ----------------------------------------------------------------------------
// overloading + for mat_op + mat_op
template <typename llhs_t, typename lrhs_t, typename rlhs_t, typename rrhs_t>
mat_op_t<mat_op_t<llhs_t, lrhs_t>, mat_op_t<rlhs_t, rrhs_t>> operator* (
    const mat_op_t<llhs_t, lrhs_t>& lhs,
    const mat_op_t<rlhs_t, rrhs_t>& rhs)
{
    return mat_op_t<mat_op_t<llhs_t, lrhs_t>, mat_op_t<rlhs_t, rrhs_t>>(
        lhs, rhs, mat_op_name::mult);
}

// ----------------------------------------------------------------------------

mat_op_t<mat_t, mat_t> operator* (const mat_t& l_mat, const mat_t& r_mat);

// #endif
