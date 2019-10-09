#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <sstream>
#include "aabbcc_opaque_types.h"
#include "AABB.h"

namespace py = pybind11;
using namespace aabb;

void init_tree(py::module &m) {
    py::class_<Tree>(m, "Tree")
        .def(py::init())
        .def(py::init<unsigned int, double, unsigned int, bool>())
        .def(py::init<unsigned int, double, unsigned int>()) // Handle the default bool = true
        .def(py::init<unsigned int, double, const std::vector<bool>,
                const std::vector<double>, unsigned int, bool>())
        .def(py::init<unsigned int, double, const std::vector<bool>,
                const std::vector<double>, unsigned int>()) // Handle the default bool = true
        .def("setPeriodicity", &Tree::setPeriodicity)
        .def("setBoxSize", &Tree::setBoxSize)
        .def("insertParticle", py::overload_cast<unsigned int, std::vector<double>&, double>(&Tree::insertParticle))
        .def("insertParticle", py::overload_cast<unsigned int, std::vector<double>&, std::vector<double>&>(&Tree::insertParticle))
        .def("nParticles", &Tree::nParticles)
        .def("removeParticle", &Tree::removeParticle)
        .def("removeAll", &Tree::removeAll)
        .def("updateParticle", py::overload_cast<unsigned int, std::vector<double>&, double, bool>(&Tree::updateParticle), py::arg("particle"), py::arg("position"), py::arg("radius"), py::arg("alwaysReinsert") = false)
        .def("updateParticle", py::overload_cast<unsigned int, std::vector<double>&, std::vector<double>&, bool>(&Tree::updateParticle), py::arg("particle"), py::arg("lowerBound"), py::arg("upperBound"), py::arg("alwaysReinsert") = false)
        .def("query", py::overload_cast<unsigned int>(&Tree::query))
        .def("query", py::overload_cast<unsigned int, const AABB&>(&Tree::query))
        .def("query", py::overload_cast<const AABB&>(&Tree::query))
        .def("getAABB", &Tree::getAABB)
        .def("getHeight", &Tree::getHeight)
        .def("getNodeCount", &Tree::getNodeCount)
        .def("computeMaximumBalance", &Tree::computeMaximumBalance)
        .def("computeSurfaceAreaRatio", &Tree::computeSurfaceAreaRatio)
        .def("validate", &Tree::validate)
        .def("rebuild", &Tree::rebuild)
        .def("__str__", [](const Tree & tree) {
                std::stringstream os;
                print_tree(tree, os);
                return os.str();
          })
        ;
}
