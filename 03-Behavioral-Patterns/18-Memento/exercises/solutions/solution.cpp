#include <cassert>
#include <iostream>
#include <vector>
#include <string>

class CanvasSnapshot {
    std::vector<std::string> shapes_;
public:
    explicit CanvasSnapshot(std::vector<std::string> shapes) : shapes_(std::move(shapes)) {}
    const std::vector<std::string>& get_shapes() const { return shapes_; }
};

class Canvas {
    std::vector<std::string> shapes_;
public:
    void add_shape(std::string s) { shapes_.push_back(std::move(s)); }
    CanvasSnapshot save() const { return CanvasSnapshot(shapes_); }
    void restore(const CanvasSnapshot& snapshot) { shapes_ = snapshot.get_shapes(); }
    size_t shape_count() const { return shapes_.size(); }
};

int main() {
    Canvas canvas;
    canvas.add_shape("Circle");
    canvas.add_shape("Square");

    auto snap = canvas.save();

    canvas.add_shape("Triangle");
    assert(canvas.shape_count() == 3);

    canvas.restore(snap);
    assert(canvas.shape_count() == 2);

    std::cout << "Memento solution verified successfully!\n";
    return 0;
}
