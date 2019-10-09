pybind11_add_module(_aabbcc
  aabbcc_py.cpp # Where module is added
  aabb_py.cpp
  node_py.cpp
  tree_py.cpp
  )
target_link_libraries(_aabbcc PRIVATE aabbcc)

install(TARGETS _aabbcc
  DESTINATION ${CMAKE_INSTALL_PYTHONLIBDIR})

# __init__.py file
# install(FILES __init__.py
#   DESTINATION ${CMAKE_INSTALL_PYTHONLIBDIR})
# Copy __init__ at configure time
# file(COPY __init__.py DESTINATION ${CMAKE_BUILD_PYTHONLIBDIR})

# Copy at build time
add_custom_command(
  TARGET _aabbcc
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  $<TARGET_FILE:_aabbcc>
  ${CMAKE_BUILD_PYTHONLIBDIR}/$<TARGET_FILE_NAME:_aabbcc>
  )
