#include <cassert>
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

class Candidate : public IJobSeeker {
    std::string name_;
public:
    std::vector<Job> received_jobs;
    explicit Candidate(std::string name) : name_(std::move(name)) {}
    void on_job_posted(const Job& job) override {
        received_jobs.push_back(job);
    }
};

class JobBoard {
    std::vector<std::shared_ptr<IJobSeeker>> subscribers_;
public:
    void subscribe(std::shared_ptr<IJobSeeker> seeker) {
        subscribers_.push_back(std::move(seeker));
    }

    void post_job(const Job& job) {
        for (const auto& s : subscribers_) {
            s->on_job_posted(job);
        }
    }
};

int main() {
    JobBoard board;
    auto c1 = std::make_shared<Candidate>("Alice");
    auto c2 = std::make_shared<Candidate>("Bob");

    board.subscribe(c1);
    board.subscribe(c2);

    board.post_job({"Senior C++ Engineer", "Google"});

    assert(c1->received_jobs.size() == 1);
    assert(c1->received_jobs[0].title == "Senior C++ Engineer");
    assert(c2->received_jobs.size() == 1);

    std::cout << "Observer solution verified successfully!\n";
    return 0;
}
