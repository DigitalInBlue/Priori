# Try to find Priori headers and libraries.
#
# Usage of this module as follows:
#
#     find_package(Priori)
#
# Variables used by this module, they can change the default behaviour and need
# to be set before calling find_package:
#
#  PRIORI_PREFIX         Set this variable to the root installation of
#                        priori if the module has problems finding the
#                        proper installation path.
#
# Note that you can set the PRIORI_PREFIX variable as environment variable.
#
# Variables defined by this module:
#
#  PRIORI_FOUND              System has the Priori library and headers
#  PRIORI_LIBRARIES          The Priori library
#  PRIORI_INCLUDE_DIRS       The location of Priori headers

if(NOT PRIORI_PREFIX)
	set(PRIORI_PREFIX $ENV{PRIORI_PREFIX})
endif()

set(PRIORI_HINTS ${PRIORI_PREFIX} $ENV{PRIORI_PREFIX})
find_path(PRIORI_ROOT
  NAMES include/priori/Priori.h
	HINTS "${PRIORI_HINTS}"
)

find_library(PRIORI_LIBRARIES
    NAMES libpriori.so
    HINTS ${PRIORI_ROOT}/lib ${PRIORI_ROOT}/lib64 
)

find_path(PRIORI_INCLUDE_DIRS
    NAMES priori/Priori.h
    HINTS ${PRIORI_ROOT}/include
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PRIORI DEFAULT_MSG
    PRIORI_LIBRARIES
    PRIORI_INCLUDE_DIRS
)

mark_as_advanced(
    PRIORI_LIBRARIES
    PRIORI_INCLUDE_DIRS
    PRIORI_ROOT
)
