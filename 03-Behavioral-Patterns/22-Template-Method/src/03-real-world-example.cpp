#include <iostream>
#include <string>

// Real-world: Build & Deployment CI/CD Pipeline
class PipelineRunner {
public:
    virtual ~PipelineRunner() = default;

    void run_pipeline(const std::string& commit_hash) {
        checkout_code(commit_hash);
        compile_project();
        run_unit_tests();
        package_artifacts();
        deploy();
    }

private:
    void checkout_code(const std::string& sha) {
        std::cout << "[CI] Checking out commit " << sha << "\n";
    }

protected:
    virtual void compile_project() = 0;
    virtual void run_unit_tests() = 0;
    virtual void package_artifacts() = 0;
    virtual void deploy() {
        std::cout << "[CI] Deploying build container to staging cluster.\n";
    }
};

class CppServicePipeline : public PipelineRunner {
protected:
    void compile_project() override {
        std::cout << "[CI/CD] Compiling C++ with clang++ -std=c++17 -O3\n";
    }
    void run_unit_tests() override {
        std::cout << "[CI/CD] Executing CTest unit test runner... (All passed)\n";
    }
    void package_artifacts() override {
        std::cout << "[CI/CD] Bundling ELF binaries into Docker container.\n";
    }
};

int main() {
    CppServicePipeline pipeline;
    pipeline.run_pipeline("8f41ab9");
    return 0;
}
