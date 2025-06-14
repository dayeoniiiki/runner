#pragma once

#include <behaviortree_cpp_v3/condition_node.h>
#include <string>

namespace runner {

class CheckImageMatch : public BT::ConditionNode {
public:
    CheckImageMatch(const std::string& name, const BT::NodeConfiguration& config);
    BT::NodeStatus tick() override;

    static BT::PortsList providedPorts();
};

} // namespace runner
