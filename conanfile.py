from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout
from conan.tools.files import copy

class Recipe(ConanFile):
  name='etk'
  version='0.7.0'
  settings = "os", "compiler", "build_type", "arch"
  package_type='library'

  license = "Apache 2.0"
  author = "Jonas Printzén jonas.printzen@gmail.com"

  settings = "os", "compiler", "build_type", "arch"
  options = {"shared": [True, False], "fPIC": [True, False]}
  default_options = {"shared": False, "fPIC": True}

  exports_sources = (
    'CMakeLists.txt', 'LICENSE', 'README.md', 'cmake/*', 
    'src/*'
  )

  def requirements(self):
    self.tool_requires('cmake/3.29.0')
    self.requires('gtest/1.14.0', visible=False)
    self.requires('grpc/1.54.3', visible=False)

  def layout(self):
      cmake_layout(self)

  def generate(self):
    cmake_deps = CMakeDeps(self)
    cmake_deps.generate()
    cmake_tc = CMakeToolchain(self)
    cmake_tc.generate()

  def build(self):
    cmake = CMake(self)
    cmake.configure()
    cmake.build()

