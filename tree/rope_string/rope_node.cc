#include <utility>
#include <string>

namespace algorithms_archive {
namespace tree {
struct RopeNode {
  int weight;
  int length;
  int height;
  std::string data;
  RopeNode *left;
  RopeNode *right;

  RopeNode(std::string data_,
           int weight_,
           int length_,
           RopeNode *left_ = nullptr,
           RopeNode *right_ = nullptr,
           int height_ = 1)
      : data{data_},
        weight{weight_},
        length{length_},
        left{left_},
        right{right_},
        height{height_} {
  }
  RopeNode(std::string &&data_,
           int &&weight_,
           int &&length_,
           RopeNode *&&left_ = nullptr,
           RopeNode *&&right_ = nullptr,
           int &&height_ = 1)
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