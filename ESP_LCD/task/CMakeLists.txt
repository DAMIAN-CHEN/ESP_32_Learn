# See the build system documentation in IDF programming guide
# for more information about component CMakeLists.txt files.


set(src_dirs
            ".")

set(include_dirs
            ".")

set(requires
            driver)

idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs} REQUIRES ${requires})

#idf_component_register(
#    SRCS i2c_task.c         # list the source files of this component
#    INCLUDE_DIRS        "."# optional, add here public include directories
#    PRIV_INCLUDE_DIRS   ../components# optional, add here private include directories
#)
