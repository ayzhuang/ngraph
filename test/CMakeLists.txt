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

add_definitions("-DSERIALIZED_ZOO=\"${CMAKE_CURRENT_SOURCE_DIR}/models\"")
set(NGRAPH_ONNX_NAMESPACE ngraph_onnx)

set(ONNX_LIBRARIES onnx)

if(NOT NGRAPH_UNIT_TEST_ENABLE)
    message(STATUS "unit tests disabled")
    add_subdirectory(util)
    return()
endif()

message(STATUS "unit tests enabled")

if (NGRAPH_MLIR_ENABLE OR NGRAPH_CPU_MLIR_ENABLE)
    add_subdirectory(mlir)
    message(STATUS "MLIR LIT tests enabled")
endif()

if(LINUX)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "4.0.0")
        # gtest has issues with this with v1.8.x
        # gtest issue is supposed to be addressed after v1.8.x
        add_compile_options(-Wno-zero-as-null-pointer-constant)
    endif()
endif()

set(SRC
    algebraic_simplification.cpp
    aligned_buffer.cpp
    all_close_f.cpp
    assertion.cpp
    attributes.cpp
    bfloat16.cpp
    build_graph.cpp
    builder_autobroadcast.cpp
    check.cpp
    constant.cpp
    constant_folding.cpp
    control_dependencies.cpp
    convert_u1_to_string.cpp
    coordinate.cpp
    copy.cpp
    core_fusion.cpp
    cpio.cpp
    cse.cpp
    dyn_elimination.cpp
    element_type.cpp
    eval.cpp
    file_util.cpp
    float16.cpp
    includes.cpp
    input_output_assign.cpp
    intervals.cpp
    main.cpp
    misc.cpp
    ngraph_api.cpp
    node_input_output.cpp
    nop_elimination.cpp
    op.cpp
    op_eval/matmul.cpp
    op_eval/mod.cpp
    op_eval/non_zero.cpp
    op_eval/strided_slice.cpp
    op_is.cpp
    opset1.cpp
    opset_pass/broadcast_opset_pass.cpp
    opset_pass/convolution_opset_pass.cpp
    opset_pass/one_hot_opset_pass.cpp
    opset_pass/gather_opset_pass.cpp
    opset_pass/generate_mask_opset_pass.cpp
    opset_pass/pad_opset_pass.cpp
    opset_pass/poolings_opset_pass.cpp
    opset_pass/reduction_opset_pass.cpp
    opset_pass/reverse_opset_pass.cpp
    opset_pass/select_opset_pass.cpp
    opset_pass/slice_opset_pass.cpp
    opset_pass/softmax_opset_pass.cpp
    opset_pass/topk_opset_pass.cpp
    opset_pass/transpose_opset_pass.cpp
    partial_shape.cpp
    pass.cpp
    pass_liveness.cpp
    pass_manager.cpp
    pass_memory_layout.cpp
    pass_shape_relevance.cpp
    pattern.cpp
    provenance.cpp
    replace_node.cpp
    reshape_elimination.cpp
    reshape_elimination_v1.cpp
    reshape_sinking.cpp
    shape.cpp
    specialize_function.cpp
    tensor.cpp
    type_info.cpp
    type_prop/all.cpp
    type_prop/any.cpp
    type_prop/avg_pool.cpp
    type_prop/batch_mat_mul.cpp
    type_prop/batch_mat_mul_transpose.cpp
    type_prop/batch_norm.cpp
    type_prop/batch_to_space.cpp
    type_prop/binary_elementwise.cpp
    type_prop/broadcast.cpp
    type_prop/bucketize.cpp
    type_prop/clamp.cpp
    type_prop/compat.cpp
    type_prop/concat.cpp
    type_prop/constant.cpp
    type_prop/convert.cpp
    type_prop/convolution.cpp
    type_prop/convolution_bias.cpp
    type_prop/crop_and_resize.cpp
    type_prop/deformable_psroi_pooling.cpp
    type_prop/depth_to_space.cpp
    type_prop/dequantize.cpp
    type_prop/dot.cpp
    type_prop/dyn_broadcast.cpp
    type_prop/dyn_pad.cpp
    type_prop/dyn_replace_slice.cpp
    type_prop/dyn_reshape.cpp
    type_prop/dyn_slice.cpp
    type_prop/strided_slice.cpp
    type_prop/elu.cpp
    type_prop/embeddingbag_offsetssum.cpp
    type_prop/embedding_lookup.cpp
    type_prop/extractimagepatches.cpp
    type_prop/embeddingbag_packedsum.cpp
    type_prop/embedding_segments_sum.cpp
    type_prop/fake_quantize.cpp
    type_prop/gather.cpp
    type_prop/gather_nd.cpp
    type_prop/gather_tree.cpp
    type_prop/gemm.cpp
    type_prop/grn.cpp
    type_prop/group_convolution.cpp
    type_prop/group_convolution_backprop_data.cpp
    type_prop/gru_cell.cpp
    type_prop/hard_sigmoid.cpp
    type_prop/index_reduction.cpp
    type_prop/layer_norm.cpp
    type_prop/lrn.cpp
    type_prop/lstm_cell.cpp
    type_prop/lstm_sequence.cpp
    type_prop/matmul.cpp
    type_prop/max_pool.cpp
    type_prop/mvn.cpp
    type_prop/non_max_suppression.cpp
    type_prop/non_zero.cpp
    type_prop/normalize.cpp
    type_prop/one_hot.cpp
    type_prop/pad.cpp
    type_prop/parameter.cpp
    type_prop/prelu.cpp
    type_prop/proposal.cpp
    type_prop/quantize.cpp
    type_prop/quantized_convolution.cpp
    type_prop/quantized_dot.cpp
    type_prop/random_uniform.cpp
    type_prop/range.cpp
    type_prop/replace_slice.cpp
    type_prop/reshape.cpp
    type_prop/reverse.cpp
    type_prop/reverse_sequence.cpp
    type_prop/roi_align.cpp
    type_prop/rnn_cell.cpp
    type_prop/scale_shift.cpp
    type_prop/scatter_add.cpp
    type_prop/scatter_elements_update.cpp
    type_prop/scatter_nd.cpp
    type_prop/scatter_nd_update.cpp
    type_prop/scatter_update.cpp
    type_prop/select.cpp
    type_prop/shape_of.cpp
    type_prop/shuffle_channels.cpp
    type_prop/slice.cpp
    type_prop/space_to_batch.cpp
    type_prop/space_to_depth.cpp
    type_prop/split.cpp
    type_prop/squared_difference.cpp
    type_prop/squeeze.cpp
    type_prop/sum.cpp
    type_prop/reduce_prod.cpp
    type_prop/reduce_sum.cpp
    type_prop/tile.cpp
    type_prop/top_k.cpp
    type_prop/transpose.cpp
    type_prop/unary_elementwise.cpp
    type_prop/unsqueeze.cpp
    type_prop/variadic_split.cpp
    type_prop_benchmark.cpp
    type_prop_layers.cpp
    util.cpp
    zero_dim_tensor_elimination.cpp
)

if(NGRAPH_INTERPRETER_ENABLE)
    list(APPEND SRC
        concat_fusion.cpp
    )
endif()

# This code generates one source file per header file under ngraph/src where the source file
# has just a single #include statement. This checks that each header in the source tree is
# complete and self-contained so it can be included without requiring any other includes.
set(DIRECTORIES_IGNORED runtime frontend)
set(NGRAPH_MAIN_SRC_DIR "${PROJECT_SOURCE_DIR}/src/ngraph")
file(GLOB_RECURSE LIST_RECURSE
    "${NGRAPH_MAIN_SRC_DIR}/autodiff/*.hpp"
    "${NGRAPH_MAIN_SRC_DIR}/builder/*.hpp"
    "${NGRAPH_MAIN_SRC_DIR}/codegen/*.hpp"
    "${NGRAPH_MAIN_SRC_DIR}/descriptor/*.hpp"
    "${NGRAPH_MAIN_SRC_DIR}/distributed/*.hpp"
    "${NGRAPH_MAIN_SRC_DIR}/op/*.hpp"
    "${NGRAPH_MAIN_SRC_DIR}/pass/*.hpp"
    "${NGRAPH_MAIN_SRC_DIR}/state*.hpp")
file(GLOB LIST
    "${NGRAPH_MAIN_SRC_DIR}/*.hpp"
    "${NGRAPH_MAIN_SRC_DIR}/runtime/*.hpp")
set(NGRAPH_HEADER_LIST ${LIST_RECURSE} ${LIST})
list(APPEND NGRAPH_HEADER_LIST ${LIST})
foreach(HEADER ${NGRAPH_HEADER_LIST})
    file(RELATIVE_PATH OUT_PATH ${NGRAPH_MAIN_SRC_DIR} ${HEADER})
    string(REGEX REPLACE "hpp$" "cpp" OUT_PATH ${OUT_PATH})
    set(OUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/include_test/${OUT_PATH}")
    configure_file("header_standalone.in.cpp" ${OUT_FILE})
    list(APPEND SRC ${OUT_FILE})
endforeach()

if(NGRAPH_JSON_ENABLE)
    list(APPEND SRC core.cpp serialize.cpp)
endif()

if(NOT WIN32 AND NGRAPH_TOOLS_ENABLE)
    list(APPEND SRC tools.cpp)
endif()

set_source_files_properties(includes.cpp PROPERTIES COMPILE_DEFINITIONS
    NGRAPH_INCLUDES="${PROJECT_SOURCE_DIR}/src/ngraph")

if (NGRAPH_INTERPRETER_ENABLE)
    list(APPEND SRC
        backend_debug_api.cpp
        builder.cpp
        backend_api.cpp)
    set(ACTIVE_BACKEND_LIST ${ACTIVE_BACKEND_LIST} INTERPRETER)
endif()

if (NGRAPH_CPU_ENABLE)
    list(APPEND SRC builder_quantization.cpp)
    list(APPEND SRC backend_performance.cpp)
    if (NGRAPH_CPU_CODEGEN_ENABLE)
        list(APPEND SRC cpu_codegen.cpp)
        set(ACTIVE_CPU_BACKEND_LIST ${ACTIVE_CPU_BACKEND_LIST} "CPU:CODEGEN")
    endif()
    if (NGRAPH_CPU_MLIR_ENABLE)
        set(ACTIVE_CPU_BACKEND_LIST ${ACTIVE_CPU_BACKEND_LIST} "CPU:MLIR")
    endif()
    set(ACTIVE_CPU_BACKEND_LIST ${ACTIVE_CPU_BACKEND_LIST} CPU)
    set(ACTIVE_BACKEND_LIST ${ACTIVE_BACKEND_LIST} ${ACTIVE_CPU_BACKEND_LIST})
endif()

if (NGRAPH_MLIR_ENABLE)
    set(ACTIVE_BACKEND_LIST ${ACTIVE_BACKEND_LIST} "MLIR")
endif()

if(NGRAPH_GPU_ENABLE)
    list(APPEND SRC gpu_test.cpp gpu_fusion.cpp)
    set(ACTIVE_BACKEND_LIST ${ACTIVE_BACKEND_LIST} GPU)
endif()

if (NGRAPH_GENERIC_CPU_ENABLE)
    set(ACTIVE_BACKEND_LIST ${ACTIVE_BACKEND_LIST} GCPU)
endif()

if(NGRAPH_EVAL_ENABLE)
    set(ACTIVE_BACKEND_LIST ${ACTIVE_BACKEND_LIST} EVAL)
endif()

add_definitions("-DTEST_FILES=\"${CMAKE_CURRENT_SOURCE_DIR}/files\"")
add_subdirectory(util)

# backend specific test files must meet the following requirements:
# 1) The must be named <name>.in.cpp
# 2) They must be in the `test/backend` directory
# 3) Include "util/test_control.hpp" in your cpp file
# 4) add the line `static string s_manifest = "${MANIFEST}";` to your cpp file
# 5) Use the `NGRAPH_TEST` macro in place of `TEST`.
# All such files are configured via cmake which replaces all instances of cmake variables
# such as ${BACKEND_NAME} with their values, such as CPU, GPU, or INTERPRETER.

set(MULTI_TEST_SRC
    backend/abc.in.cpp
    backend/abs.in.cpp
    backend/acosh.in.cpp
    backend/acos.in.cpp
    backend/add.in.cpp
    backend/aliased_output.in.cpp
    backend/all.in.cpp
    backend/any.in.cpp
    backend/api.in.cpp
    backend/arg_reduce.in.cpp
    backend/asinh.in.cpp
    backend/asin.in.cpp
    backend/atan2.in.cpp
    backend/atanh.in.cpp
    backend/atan.in.cpp
    backend/auto_broadcast.in.cpp
    backend/autodiff.in.cpp
    backend/batch_mat_mul.in.cpp
    backend/batch_norm.in.cpp
    backend/broadcast.in.cpp
    backend/builder_flatten.in.cpp
    backend/builder_reduce_ops_opset1.in.cpp
    backend/ceiling.in.cpp
    backend/clamp.in.cpp
    backend/comparison.in.cpp
    backend/computation_reuse.in.cpp
    backend/concat.in.cpp
    backend/constant.in.cpp
    backend/conv_bias.in.cpp
    backend/convert.in.cpp
    backend/convolution.in.cpp
    backend/convolution_reference.in.cpp
    backend/cosh.in.cpp
    backend/cos.in.cpp
    backend/cross_entropy.in.cpp
    backend/cum_sum.in.cpp
    backend/divide.in.cpp
    backend/dot.in.cpp
    backend/dynamic.in.cpp
    backend/dyn_broadcast.in.cpp
    backend/dyn_replace_slice_reference.in.cpp
    backend/dyn_reshape.in.cpp
    backend/dyn_slice_reference.in.cpp
    backend/elu.in.cpp
    backend/embedding_lookup.in.cpp
    backend/erf.in.cpp
    backend/exp.in.cpp
    backend/fake_quantize.in.cpp
    backend/floor.in.cpp
    backend/function_name.in.cpp
    backend/gather.in.cpp
    backend/gelu.in.cpp
    backend/gemm.in.cpp
    backend/generate_mask.in.cpp
    backend/graph_comparison.in.cpp
    backend/grn.in.cpp
    backend/group_conv.in.cpp
    backend/group_convolution.in.cpp
    backend/gru_cell.in.cpp
    backend/hard_sigmoid.in.cpp
    backend/layer_norm.in.cpp
    backend/logical_and.in.cpp
    backend/logical_or.in.cpp
    backend/logical_xor.in.cpp
    backend/log.in.cpp
    backend/lrn.in.cpp
    backend/lstm_cell.in.cpp
    backend/matmul.in.cpp
    backend/maximum.in.cpp
    backend/max.in.cpp
    backend/minimum.in.cpp
    backend/min.in.cpp
    backend/mlir.in.cpp
    backend/mod.in.cpp
    backend/multiple_backends.in.cpp
    backend/multiple_result.in.cpp
    backend/multiply.in.cpp
    backend/mvn.in.cpp
    backend/negative.in.cpp
    backend/node_name.in.cpp
    backend/non_zero.in.cpp
    backend/normalize.in.cpp
    backend/not.in.cpp
    backend/numeric.in.cpp
    backend/one_hot.in.cpp
    backend/pad.in.cpp
    backend/parameter_as_output.in.cpp
    backend/partial_slice.in.cpp
    backend/pool.in.cpp
    backend/power.in.cpp
    backend/prelu.in.cpp
    backend/product.in.cpp
    backend/quantized_convolution.in.cpp
    backend/quantized_dot.in.cpp
    backend/quantize_dequantize.in.cpp
    backend/random_uniform.in.cpp
    backend/range.in.cpp
    backend/reduce_max.in.cpp
    backend/reduce_mean.in.cpp
    backend/reduce_min.in.cpp
    backend/reduce_prod.in.cpp
    backend/reduce_sum.in.cpp
    backend/relu.in.cpp
    backend/replace_slice.in.cpp
    backend/reshape.in.cpp
    backend/reverse.in.cpp
    backend/reverse_sequence.in.cpp
    backend/rnn_cell.in.cpp
    backend/round.in.cpp
    backend/scale.in.cpp
    backend/scatter.in.cpp
    backend/select.in.cpp
    backend/shape_of.in.cpp
    backend/shuffle_channels.in.cpp
    backend/sigmoid.in.cpp
    backend/sign.in.cpp
    backend/sinh.in.cpp
    backend/sin.in.cpp
    backend/slice.in.cpp
    backend/softmax.in.cpp
    backend/split.in.cpp
    backend/sqrt.in.cpp
    backend/squared_difference.in.cpp
    backend/squeeze.in.cpp
    backend/stack.in.cpp
    backend/strided_slice.in.cpp
    backend/subtract.in.cpp
    backend/sum.in.cpp
    backend/tanh.in.cpp
    backend/tan.in.cpp
    backend/tile.in.cpp
    backend/topk.in.cpp
    backend/transpose.in.cpp
    backend/unhandled_op.in.cpp
    backend/unsqueeze.in.cpp
    backend/validate_call.in.cpp
    backend/zero_sized.in.cpp
)

if (NGRAPH_MLIR_ENABLE OR NGRAPH_CPU_MLIR_ENABLE)
    list(APPEND MULTI_TEST_SRC backend/mlir.in.cpp)
    list(APPEND SRC mlir/ops_test.cpp)
endif()

if(NGRAPH_UNIT_TEST_NUMPY_ENABLE)
    list(APPEND MULTI_TEST_SRC backend/numpy.in.cpp)
endif()

if (NGRAPH_ONNX_IMPORT_ENABLE)
    list(APPEND MULTI_TEST_SRC
            onnx/onnx_import.in.cpp
            onnx/onnx_import_const_folding.in.cpp
            onnx/onnx_import_convpool.in.cpp
            onnx/onnx_import_dyn_shapes.in.cpp
            onnx/onnx_import_library.in.cpp
            onnx/onnx_import_provenance.in.cpp
            onnx/onnx_import_reshape.in.cpp
            onnx/onnx_import_rnn.in.cpp
            onnx/onnx_import_quant.in.cpp)
endif()

foreach(BACKEND_NAME ${ACTIVE_BACKEND_LIST})
    # Some---but not all---autodiff tests go through multiple iterations with
    # different random seeds. On the CPU backend this is currently very slow
    # because the autodiff tests recompile with each iteration. That behavior
    # can be changed, but it's a bit involved, so for the time being we just
    # reduce the number of test iterations on non-INTERPRETER backends.
    if(${BACKEND_NAME} MATCHES ^INTERPRETER$)
        set(TEST_LOOPS 100)
    else()
        set(TEST_LOOPS 2)
    endif()

    string(TOLOWER ${BACKEND_NAME} BACKEND_DIR)
    string(REGEX REPLACE "([a-z0-9]+):(.*)" "\\1" BACKEND_DIR ${BACKEND_DIR})
    if (EXISTS ${PROJECT_SOURCE_DIR}/src/ngraph/runtime/${BACKEND_DIR}/unit_test.manifest)
        set(MANIFEST ${PROJECT_SOURCE_DIR}/src/ngraph/runtime/${BACKEND_DIR}/unit_test.manifest)
    elseif(EXISTS ${PROJECT_SOURCE_DIR}/src/runtime/${BACKEND_DIR}/unit_test.manifest)
        set(MANIFEST ${PROJECT_SOURCE_DIR}/src/runtime/${BACKEND_DIR}/unit_test.manifest)
    endif()

    foreach(TEST_SRC ${MULTI_TEST_SRC})
        string(REPLACE ":" "_" BACKEND_NAME ${BACKEND_NAME})
        string(REPLACE ".in." "_${BACKEND_NAME}." TARGET_NAME ${TEST_SRC})
        configure_file(${TEST_SRC} ${TARGET_NAME})
        set(SRC ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME} ${SRC})
    endforeach()

    message(STATUS "Adding unit test for backend ${BACKEND_NAME}")
endforeach()
# These configured tests are for the CPU backend and its variants
set(CPU_MULTI_SRC
    cpu_fusion.in.cpp
    cpu_core_fusion.in.cpp
    cpu_debugger.in.cpp
    cpu_test.in.cpp
)
foreach(BACKEND_NAME ${ACTIVE_CPU_BACKEND_LIST})
    string(TOLOWER ${BACKEND_NAME} BACKEND_DIR)
    string(REGEX REPLACE ":.*" "" BACKEND_DIR ${BACKEND_DIR})
    set(MANIFEST ${PROJECT_SOURCE_DIR}/src/ngraph/runtime/${BACKEND_DIR}/unit_test.manifest)
    string(REGEX REPLACE "([a-z0-9]+):(.*)" "\\1" BACKEND_DIR ${BACKEND_DIR})
    foreach(TEST_SRC ${CPU_MULTI_SRC})
        string(REPLACE ":" "_" BACKEND_NAME ${BACKEND_NAME})
        string(REPLACE ".in." "_${BACKEND_NAME}." TARGET_NAME ${TEST_SRC})
        configure_file(${TEST_SRC} ${TARGET_NAME})
        set(SRC ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME} ${SRC})
    endforeach()
endforeach()

add_executable(unit-test ${SRC})

target_include_directories(unit-test PRIVATE ".")

add_definitions("-DCURDIR=\"${CMAKE_CURRENT_SOURCE_DIR}\"")
add_definitions("-DJSON_INCLUDES=\"${JSON_INCLUDE_DIR}\"")

if(NGRAPH_ADDRESS_SANITIZER)
    add_compile_options(-g -fsanitize=address -fno-omit-frame-pointer)
endif()

target_link_libraries(unit-test PRIVATE ngraph_test_util)
target_link_libraries(unit-test PRIVATE ngraph libgtest)

if(NGRAPH_UNIT_TEST_NUMPY_ENABLE)
    target_link_libraries(unit-test PRIVATE ngraph pybind11::embed)
    target_compile_definitions(unit-test PRIVATE NGRAPH_UNIT_TEST_NUMPY_ENABLE)
endif()

if (NGRAPH_ONNX_IMPORT_ENABLE)
    target_include_directories(unit-test
        SYSTEM PRIVATE ${ONNX_INCLUDE_DIR} ${ONNX_PROTO_INCLUDE_DIR} ${Protobuf_INCLUDE_DIR})
    target_link_libraries(unit-test PRIVATE ${ONNX_LIBRARIES})
endif()

target_compile_definitions(unit-test PRIVATE NGRAPH_VERSION_LABEL="${NGRAPH_VERSION_LABEL}")
if (NGRAPH_JSON_ENABLE)
    target_link_libraries(unit-test PRIVATE nlohmann_json::nlohmann_json)
endif()
if(NOT WIN32)
    target_link_libraries(unit-test PRIVATE pthread)
endif()
target_link_libraries(unit-test PRIVATE ${CMAKE_DL_LIBS})

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "^(AppleClang)?Clang$")
    target_compile_options(unit-test PRIVATE -Wno-undef -Wno-reserved-id-macro)
endif()

# So many type_prop tests these days that we need to set /bigobj flag for MSVC.
# We should probably split up type_prop.cpp.
if (MSVC)
    target_compile_options(unit-test PRIVATE "/bigobj")
endif()

if (NGRAPH_ONNX_IMPORT_ENABLE)
    target_link_libraries(unit-test PRIVATE onnx_importer)
endif()

if (NGRAPH_CPU_ENABLE)
    # The INTERPRETER backend is required for convolution, and backwards unit tests
    target_link_libraries(unit-test PRIVATE cpu_backend interpreter_backend)
    target_link_libraries(unit-test PRIVATE DNNL::dnnl)
    set_property(SOURCE backend_api.cpp APPEND PROPERTY COMPILE_DEFINITIONS NGRAPH_CPU_ENABLE)
endif()

if (NGRAPH_TOOLS_ENABLE)
    get_property(NBENCH_PATH TARGET nbench PROPERTY BINARY_DIR)
    set(NBENCH "${NBENCH_PATH}/nbench")
    target_compile_definitions(unit-test PRIVATE NBENCH_PATH="${NBENCH}")
    add_dependencies(unit-test nbench)
endif()

if (NGRAPH_TBB_ENABLE)
    target_compile_definitions(unit-test PRIVATE "NGRAPH_TBB_ENABLE")
endif()

if (NGRAPH_INTERPRETER_ENABLE)
    target_compile_definitions(unit-test PRIVATE NGRAPH_INTERPRETER_ENABLE)
    target_link_libraries(unit-test PRIVATE interpreter_backend)
endif()

if (NGRAPH_GENERIC_CPU_ENABLE)
    target_link_libraries(unit-test PRIVATE gcpu_backend)
endif()

if (NGRAPH_EVAL_ENABLE)
    target_compile_definitions(unit-test PRIVATE NGRAPH_EVAL_ENABLE)
    target_link_libraries(unit-test PRIVATE eval_backend)
endif()

if (NGRAPH_GPU_ENABLE)
    target_link_libraries(unit-test PRIVATE gpu_backend)
endif()

if (NGRAPH_NOP_ENABLE)
    target_link_libraries(unit-test PRIVATE nop_backend)
endif()

if (NGRAPH_MLIR_ENABLE OR NGRAPH_CPU_MLIR_ENABLE)
    target_link_libraries(unit-test PRIVATE mlir_backend)
    target_include_directories(unit-test PRIVATE ${CMAKE_BINARY_DIR}/src/contrib/mlir)
    target_compile_definitions(unit-test PRIVATE NGRAPH_MLIR_ENABLE)
endif()

# If all the runtime libraries are installed into one location, that will make life easier.
if (MSVC)
    add_custom_target(unit-test-check
        COMMAND set "PATH=${EXTERNAL_PROJECTS_ROOT}/src/ngraph/Release;${EXTERNAL_PROJECTS_ROOT}/dnnl/lib/;${EXTERNAL_PROJECTS_ROOT}/mkl/src/ext_mkl/lib/;${EXTERNAL_PROJECTS_ROOT}/ext_tbb-prefix/src/ext_tbb/tbb2019_20181203oss/bin/intel64/vc14;%PATH%"
        COMMAND ${PROJECT_BINARY_DIR}/test/unit-test \${ARGS}
        DEPENDS unit-test
    )
else()
    add_custom_target(unit-test-check
        COMMAND ${PROJECT_BINARY_DIR}/test/unit-test --cpath ${EXTERNAL_PROJECTS_ROOT}/src/ngraph/ \${ARGS}
        DEPENDS unit-test
    )
endif()

add_custom_target(ngraph-check
    DEPENDS
    style-check
    unit-test-check
)
