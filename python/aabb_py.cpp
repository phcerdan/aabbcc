#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <sstream>
#include "aabbcc_opaque_types.h"
#include "AABB.h"

namespace py = pybind11;
using namespace aabb;
void init_aabb(py::module &m) {
    py::class_<AABB>(m, "AABB")
        .def(py::init())
        .def(py::init<unsigned int>())
        .def(py::init<const std::vector<double>&, const std::vector<double>&>())
        .def_readwrite("lowerBound", &AABB::lowerBound)
        .def_readwrite("upperBound", &AABB::upperBound)
        .def_readwrite("centre", &AABB::centre)
        .def_readwrite("surfaceArea", &AABB::surfaceArea)
        .def("computeSurfaceArea", &AABB::computeSurfaceArea)
        .def("computeCentre", &AABB::computeCentre)
        .def("merge", &AABB::merge)
        .def("contains", &AABB::contains)
        .def("overlaps", &AABB::overlaps)
        .def("setDimension", &AABB::setDimension)
        .def("__str__", [](const AABB & aabb) {
                std::stringstream os;
                print_aabb(aabb, os);
                return os.str();
          })
        ;
}
