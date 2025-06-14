#include "runner/CheckImageMatch.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <filesystem>

using namespace std;
using json = nlohmann::json;
namespace fs = std::filesystem;

namespace runner {

CheckImageMatch::CheckImageMatch(const std::string& name, const BT::NodeConfiguration& config)
    : BT::ConditionNode(name, config) {}

BT::NodeStatus CheckImageMatch::tick() {
    // 가장 최근 JSON 결과를 탐색
    std::string folder = "logs/images/result";
    fs::path latest_file;
    std::time_t latest_time = 0;

    for (const auto& entry : fs::directory_iterator(folder)) {
        if (entry.path().extension() == ".json") {
            auto ftime = fs::last_write_time(entry);
            auto sctp = decltype(ftime)::clock::to_time_t(ftime);
            if (sctp > latest_time) {
                latest_time = sctp;
                latest_file = entry.path();
            }
        }
    }

    if (latest_file.empty()) {
        std::cerr << "[CheckImageMatch] ❌ No JSON result found.\n";
        return BT::NodeStatus::FAILURE;
    }

    std::ifstream f(latest_file);
    if (!f.is_open()) {
        std::cerr << "[CheckImageMatch] ❌ Failed to open: " << latest_file << "\n";
        return BT::NodeStatus::FAILURE;
    }

    json j;
    f >> j;

    bool anomaly = j.value("anomaly", true);
    std::cout << "[CheckImageMatch] Read " << latest_file.filename() << ", anomaly = " << anomaly << "\n";

    return anomaly ? BT::NodeStatus::FAILURE : BT::NodeStatus::SUCCESS;
}

BT::PortsList CheckImageMatch::providedPorts() {
    return {};
}

} // namespace runner
