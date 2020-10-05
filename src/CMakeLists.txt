target_sources(lazy_mat
    PRIVATE
        main.cpp
        matrix.cpp matrix.hpp
        stor.hpp stor.cpp
        mat_ops.hpp opr_res.hpp
)
target_sources(tests
    PRIVATE
        matrix.cpp matrix.hpp
        stor.hpp stor.cpp
        mat_ops.hpp opr_res.hpp
)
