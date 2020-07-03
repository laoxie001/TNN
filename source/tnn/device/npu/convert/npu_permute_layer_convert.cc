// Tencent is pleased to support the open source community by making TNN available.
//
// Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include <graph/op/all_ops.h>
#include "graph/attr_value.h"
#include "graph/op/nn_defs.h"
#include "npu_base_layer_convert.h"
#include "npu_utils.h"

namespace TNN_NS {

DECLARE_NPU_LAYER(Permute, LAYER_PERMUTE);

Status NpuPermuteLayer::Convert() {
    auto param = dynamic_cast<PermuteLayerParam *>(param_);
    if (!param) {
        LOGE("Error: Permute param is null\n");
        return Status(TNNERR_LAYER_ERR, "Permute param is null");
    }
    std::vector<int64_t> orders(param->orders.begin(), param->orders.end());
    auto output = std::make_shared<ge::op::Permute>(outputs_[0]);
    output->set_input_x(*input_ops_[0]->GetOperator());
    output->set_attr_order(orders);

    std::shared_ptr<OperatorInfo> output_op = std::make_shared<OperatorInfo>(output);
    output_ops_.push_back(output_op);
    return SetOutputOps();
}

REGISTER_NPU_LAYER(Permute, LAYER_PERMUTE);

}  // namespace TNN_NS
