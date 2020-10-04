target_sources(lazy_mat
    PRIVATE
        matrix.cpp matrix.hpp mat_ops.hpp main.cpp stor.cpp stor.hpp
)
target_sources(tests
    PRIVATE
        matrix.cpp matrix.hpp mat_ops.hpp stor.hpp stor.cpp
)
