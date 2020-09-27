function(git_ver git_tag git_branch git_commit_hash)
    if (EXISTS "${CMAKE_SOURCE_DIR}/.git")
        execute_process (
            COMMAND git describe --tags --dirty --always
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE git_tag_
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        set(${git_tag} ${git_tag_} PARENT_SCOPE)
        execute_process (
            COMMAND git rev-parse --abbrev-ref HEAD
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE git_branch_
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        set(${git_branch} ${git_branch_} PARENT_SCOPE)
        execute_process (
            COMMAND git log -1 --format=%h
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE git_commit_hash_
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        set(${git_commit_hash} ${git_commit_hash_} PARENT_SCOPE)
    else (EXISTS "${CMAKE_SOURCE_DIR}/.git")
        set (GIT_TAG "")
        set (GIT_BRANCH "")
        set (GIT_COMMIT_HASH "")
    endif (EXISTS "${CMAKE_SOURCE_DIR}/.git")
endfunction(git_ver)

