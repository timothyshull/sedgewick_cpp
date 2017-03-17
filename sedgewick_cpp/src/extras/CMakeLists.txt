project(collected_extras)

# for Timsort _tmp file
include_directories(/usr/local/var/pyenv/versions/3.6.0/Python.framework/Versions/3.6/include/python3.6m)

add_executable(bucket_sort_main bucket_sort_main.cpp Bucket_sort.h)