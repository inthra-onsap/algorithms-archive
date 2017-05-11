#include <utility>
#include <string>

namespace algorithms_archive {
namespace tree {
struct RopeNode {
  uint64_t weight;
  uint64_t length;
  uint64_t height;
  std::string data;
  RopeNode *left;
  RopeNode *right;

  RopeNode(std::string data_,
           uint64_t weight_,
           uint64_t length_,
           RopeNode *left_ = nullptr,
           RopeNode *right_ = nullptr,
           uint64_t height_ = 1)
      : data{data_},
        weight{weight_},
        length{length_},
        left{left_},
        right{right_},
        height{height_} {
  }
  RopeNode(std::string &&data_,
           uint64_t &&weight_,
           uint64_t &&length_,
           RopeNode *&&left_ = nullptr,
           RopeNode *&&right_ = nullptr,
           uint64_t &&height_ = 1)
      : data{std::move(data_)},
        weight{std::move(weight_)},
        length{std::move(length_)},
        left{std::move(left_)},
        right{std::move(right_)},
        height{std::move(height_)} {
  }
};
} // namespace tree
} // namespace algorithms_archive