#include <iostream>

// Naive Approach: Duplicating the overall algorithm skeleton across subclasses
class PDFReportGenerator {
public:
    void generate() {
        std::cout << "[Init] Connecting to database...\n";
        std::cout << "[Fetch] Fetching records...\n";
        std::cout << "[PDF] Formatting rows into PDF grid...\n"; // Specific step
        std::cout << "[Close] Saving to disk and closing connection.\n";
    }
};

class CSVReportGenerator {
public:
    void generate() {
        std::cout << "[Init] Connecting to database...\n";
        std::cout << "[Fetch] Fetching records...\n";
        std::cout << "[CSV] Formatting rows into comma-separated text...\n"; // Specific step
        std::cout << "[Close] Saving to disk and closing connection.\n";
    }
};

int main() {
    PDFReportGenerator pdf;
    pdf.generate();

    CSVReportGenerator csv;
    csv.generate();
    return 0;
}
