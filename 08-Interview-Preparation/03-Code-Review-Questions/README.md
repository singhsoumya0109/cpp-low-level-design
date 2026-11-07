# 03 Code Review & Anti-Pattern Spotting

Analyze realistic C++ code snippets submitted in LLD interviews. Identify bugs, memory leaks, slicing, SOLID violations, and race conditions.

---

## Review Snippet 1: The Memory Leak in Polymorphic Hierarchy

```cpp
// CANDIDATE SUBMISSION
class Shape {
public:
    Shape() = default;
    ~Shape() { std::cout << "~Shape\n"; } // BUG!
    virtual double area() const = 0;
};

class Circle : public Shape {
    int* buffer_;
public:
    Circle(double r) : radius_(r), buffer_(new int[1024]) {}
    ~Circle() {
        delete[] buffer_;
        std::cout << "~Circle\n";
    }
    double area() const override { return 3.14159 * radius_ * radius_; }
private:
    double radius_;
};

void run() {
    Shape* s = new Circle(5.0);
    delete s; // BUG TRIGGERED
}
```

### Review Feedback & Fix:
1. **Critical Defect**: `~Shape()` is non-virtual. Deleting a `Circle` via a `Shape*` invokes only `~Shape()`. `~Circle()` is never called, leaking `buffer_` and causing Undefined Behavior!
2. **Raw Pointer / Delete**: Violates C++ Core Guidelines. Use `std::unique_ptr<Shape>` and `std::vector<int>` instead of raw `new int[]`.
3. **Refactored**:
```cpp
class Shape {
public:
    virtual ~Shape() = default; // Virtual destructor!
    virtual double area() const = 0;
};

class Circle : public Shape {
    double radius_;
    std::vector<int> buffer_; // RAII: zero manual memory management
public:
    Circle(double r) : radius_(r), buffer_(1024) {}
    double area() const override { return 3.141592653589793 * radius_ * radius_; }
};
```

---

## Review Snippet 2: Object Slicing in Collections

```cpp
// CANDIDATE SUBMISSION
class Vehicle {
public:
    virtual void drive() const { std::cout << "Driving generic vehicle\n"; }
};

class SportsCar : public Vehicle {
public:
    void drive() const override { std::cout << "Turbocharged driving!\n"; }
};

class Fleet {
    std::vector<Vehicle> vehicles_; // BUG!
public:
    void addVehicle(Vehicle v) {    // BUG!
        vehicles_.push_back(v);
    }
    void startAll() const {
        for (const auto& v : vehicles_) {
            v.drive(); // Always prints "Driving generic vehicle"
        }
    }
};
```

### Review Feedback & Fix:
1. **Critical Defect**: Object slicing occurs twice—first when passed by value in `addVehicle(Vehicle v)`, and second when stored in `std::vector<Vehicle>`. The derived `SportsCar` portion is sliced off, losing polymorphism.
2. **Refactored**:
```cpp
class Fleet {
    std::vector<std::unique_ptr<Vehicle>> vehicles_;
public:
    void addVehicle(std::unique_ptr<Vehicle> v) {
        vehicles_.push_back(std::move(v));
    }
    void startAll() const {
        for (const auto& v : vehicles_) {
            if (v) v->drive();
        }
    }
};
```
