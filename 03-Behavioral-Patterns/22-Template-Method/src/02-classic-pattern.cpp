#include <iostream>
#include <string>

// Classic Template Method: Skeleton defined in base class method.
class ReportGenerator {
public:
    virtual ~ReportGenerator() = default;

    // The Template Method: final prevents subclasses from altering algorithm flow
    void generate_report() {
        connect_db();
        fetch_data();
        format_body();
        save_output();
        if (requires_signature()) {
            apply_digital_signature();
        }
    }

private:
    void connect_db() { std::cout << "[Step 1] Connecting to database...\n"; }
    void fetch_data() { std::cout << "[Step 2] Fetching dataset records...\n"; }
    void save_output() { std::cout << "[Step 4] Saving generated report to storage...\n"; }

protected:
    virtual void format_body() = 0; // Pure virtual hook
    virtual bool requires_signature() const { return false; } // Optional hook
    virtual void apply_digital_signature() {
        std::cout << "[Step 5] Applying cryptographic digital signature.\n";
    }
};

class PDFReport : public ReportGenerator {
protected:
    void format_body() override {
        std::cout << "[Step 3] Rendering vector graphics and tabular PDF layout.\n";
    }
    bool requires_signature() const override { return true; }
};

class CSVReport : public ReportGenerator {
protected:
    void format_body() override {
        std::cout << "[Step 3] Exporting plain RFC-4180 CSV rows.\n";
    }
};

int main() {
    std::cout << "--- Generating PDF Report ---\n";
    PDFReport pdf;
    pdf.generate_report();

    std::cout << "\n--- Generating CSV Report ---\n";
    CSVReport csv;
    csv.generate_report();
    return 0;
}
