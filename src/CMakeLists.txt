target_sources(lazy_mat
    PRIVATE
        main.cpp
        mat.cpp mat.hpp
        stor.hpp stor.cpp
        oprand.cpp oprand.hpp
        mat_ops.tpp opr_res.hpp
        vec.hpp vec.cpp
)
target_sources(tests
    PRIVATE
        mat.cpp mat.hpp
        stor.hpp stor.cpp
        oprand.cpp oprand.hpp
        mat_ops.tpp opr_res.hpp
        vec.hpp vec.cpp
)
