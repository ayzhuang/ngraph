//*****************************************************************************
// Copyright 2017-2019 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//*****************************************************************************

#pragma once

#include <cmath>

#include "ngraph/assertion.hpp"
#include "ngraph/axis_vector.hpp"
#include "ngraph/coordinate_transform.hpp"

namespace ngraph
{
    namespace runtime
    {
        namespace reference
        {
            template <typename T>
            void pad(const T* arg0,
                     const T* arg1,
                     T* out,
                     const Shape& arg0_shape,
                     const Shape& out_shape,
                     const CoordinateDiff& padding_below,
                     const CoordinateDiff& padding_above,
                     const Shape& padding_interior)
            {
                Coordinate input_start(arg0_shape.size(), 0); // start at (0,0,...,0)
                Coordinate input_end =
                    out_shape; // end at (d'0,d'1,...,d'n), the outer corner of the post-padding shape

                Strides input_strides(arg0_shape.size(), 1);

                AxisVector input_axis_order(arg0_shape.size());
                for (size_t i = 0; i < arg0_shape.size(); i++)
                {
                    input_axis_order[i] = i;
                }

                Strides input_dilation(arg0_shape.size());
                for (size_t i = 0; i < arg0_shape.size(); i++)
                {
                    input_dilation[i] = padding_interior[i] + 1;
                }

                CoordinateTransform input_transform(arg0_shape,
                                                    input_start,
                                                    input_end,
                                                    input_strides,
                                                    input_axis_order,
                                                    padding_below,
                                                    padding_above,
                                                    input_dilation);
                CoordinateTransform output_transform(out_shape);

                CoordinateTransform::Iterator output_it = output_transform.begin();

                NGRAPH_ASSERT(shape_size(input_transform.get_target_shape()) ==
                              shape_size(output_transform.get_target_shape()));

                for (const Coordinate& in_coord : input_transform)
                {
                    const Coordinate& out_coord = *output_it;

                    T v = input_transform.has_source_coordinate(in_coord)
                              ? arg0[input_transform.index(in_coord)]
                              : *arg1;

                    out[output_transform.index(out_coord)] = v;

                    ++output_it;
                }
            }
        }
    }
}
