#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    // Check if filename is provided
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    
    // Check if file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << argv[1] << "\n";
        return 1;
    }

    std::string line;
    std::cout << "Press Enter to display each line...\n\n";

    // Loop through the file line by line
    while (std::getline(file, line)) {
        std::cin.get();  // Wait for Enter key
        std::cout << line << std::endl;
    }

    std::cout << "\n\nEnd of file reached.\n";
    return 0;
}
