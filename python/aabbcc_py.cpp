/*
  Copyright (c) 2009 Erin Catto http://www.box2d.org
  Copyright (c) 2016-2018 Lester Hedges <lester.hedges+aabbcc@gmail.com>

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.

  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.

  3. This notice may not be removed or altered from any source distribution.

  This code was adapted from parts of the Box2D Physics Engine,
  http://www.box2d.org
*/

#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>
#include "aabbcc_opaque_types.h"
namespace py = pybind11;

void init_aabb(py::module &);
void init_node(py::module &);
void init_tree(py::module &);

PYBIND11_MODULE(_aabbcc, m) {
    m.doc() = "aabbcc, AABB hierarchical tree";
    py::bind_vector<std::vector<bool>>(m, "VectorBool");
    py::bind_vector<std::vector<unsigned int>>(m, "VectorUnsignedInt");
    py::bind_vector<std::vector<double>>(m, "VectorDouble");
    init_aabb(m);
    init_node(m);
    init_tree(m);
}
