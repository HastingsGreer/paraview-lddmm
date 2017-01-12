##############################################################################
#
# Library:  ParaviewLDDMM 
#
# Copyright 2010 Kitware Inc. 28 Corporate Drive,
# Clifton Park, NY, 12065, USA.
# All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
##############################################################################

cmake_minimum_required(VERSION 2.8)
 
project(DiscreteGaussianImageFilter)
 
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
if (ITKVtkGlue_LOADED)
  find_package(VTK REQUIRED)
  include(${VTK_USE_FILE})
else()
  find_package(ItkVtkGlue REQUIRED)
  include(${ItkVtkGlue_USE_FILE})
  set(Glue ItkVtkGlue)
endif()

add_library(myFilter vtkImageGaussianSmooth2.cxx)
target_link_libraries(myFilter ${VTK_LIBRARIES})
 
add_executable(itkGaussianEx itkGaussianExample.cxx)
target_link_libraries(itkGaussianEx
  ${Glue}  ${VTK_LIBRARIES} ${ITK_LIBRARIES})

add_executable(itkFilterToVtkOutput itkFilterToVtkOutput.cxx)
target_link_libraries(itkFilterToVtkOutput
  ${Glue}  ${VTK_LIBRARIES} ${ITK_LIBRARIES})

add_executable(vtkGaussianEx MACOSX_BUNDLE vtkGaussianExample.cxx)

target_link_libraries(vtkGaussianEx ${VTK_LIBRARIES} myFilter)

