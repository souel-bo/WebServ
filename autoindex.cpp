#include "includes/AutoIndex.hpp"
#include <iostream>
#include <cstdlib>

int main() {
    // 1. We will test the uploads folder you created earlier
    std::string physicalPath = "./www/admin/uploads"; 
    std::string requestedUri = "/uploads/";

    std::cout << "--- TESTING AUTOINDEX ENGINE ---\n";
    std::cout << "Target Physical Path : " << physicalPath << "\n";
    std::cout << "Target URI           : " << requestedUri << "\n\n";

    // 2. Fire the generator
    std::string htmlOutput = AutoIndex::generate(physicalPath, requestedUri);

    // 3. Analyze the result
    if (htmlOutput.empty()) {
        std::cout << "[RESULT] FAIL: Returned an empty string.\n";
        std::cout << "Reason: opendir() failed. The folder either doesn't exist, or you lack read permissions.\n";
    } else {
        std::cout << "[RESULT] SUCCESS: HTML generated perfectly!\n";
        std::cout << "================ RAW HTML =================\n";
        std::cout << htmlOutput << "\n";
        std::cout << "===========================================\n";
    }

    return 0;
}