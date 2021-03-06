# ******************************************************************************
# Copyright 2017-2020 Intel Corporation
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
# ******************************************************************************

add_subdirectory(interpreter)
add_subdirectory(eval)

# With CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS, when creating cpu_backend.dll, link reports error: library limit of 65535 objects exceeded
if (NGRAPH_CPU_ENABLE)
    add_subdirectory(cpu)
endif()

if (NGRAPH_GENERIC_CPU_ENABLE)
    add_subdirectory(gcpu)
endif()

if (NGRAPH_MLIR_ENABLE OR NGRAPH_CPU_MLIR_ENABLE)
    add_subdirectory(mlir)
endif()
