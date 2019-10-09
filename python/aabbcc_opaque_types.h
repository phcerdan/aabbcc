#ifndef AABBCC_OPAQUE_TYPES_H
#define AABBCC_OPAQUE_TYPES_H

#include <pybind11/stl_bind.h>
PYBIND11_MAKE_OPAQUE(std::vector<bool>);
PYBIND11_MAKE_OPAQUE(std::vector<unsigned int>);
PYBIND11_MAKE_OPAQUE(std::vector<double>);

#endif
