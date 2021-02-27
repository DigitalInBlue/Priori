#
# Priori Bemchmark
#
# Copyright 2014-2021 John Farrier
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

project(priori-benchmark)

add_executable(${PROJECT_NAME})

find_package(celero CONFIG REQUIRED)

target_sources(${PROJECT_NAME} PRIVATE
	benchmark.cpp
)

PrioriSetDefaultCompilerOptions()

target_link_libraries(${PROJECT_NAME}
	celero
	priori
)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
  ${CMAKE_SOURCE_DIR}/include
)

if(PRIORI_ENABLE_FOLDERS)
	set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "priori")
endif()
