#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct Job {
    std::string title;
    std::string company;
};

class IJobSeeker {
public:
    virtual ~IJobSeeker() = default;
    virtual void on_job_posted(const Job& job) = 0;
};

// TODO: Implement JobBoard with subscribe(), unsubscribe(), post_job()

int main() {
    std::cout << "Complete the TODOs and test with solutions/solution.cpp\n";
    return 0;
}
