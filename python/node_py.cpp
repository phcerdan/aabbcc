#include <pybind11/pybind11.h>
#include <sstream>
#include "aabbcc_opaque_types.h"
#include "AABB.h"

namespace py = pybind11;
using namespace aabb;

void init_node(py::module &m) {
    py::class_<Node>(m, "Node")
        .def(py::init())
        .def_readwrite("aabb", &Node::aabb)
        .def_readwrite("parent", &Node::parent)
        .def_readwrite("next", &Node::next)
        .def_readwrite("left", &Node::left)
        .def_readwrite("right", &Node::right)
        .def_readwrite("height", &Node::height)
        .def_readwrite("particle", &Node::particle)
        .def("isLeaf", &Node::isLeaf)
        .def("__str__", [](const Node & node) {
                std::stringstream os;
                print_node(node, os);
                return os.str();
          })
        ;
}
