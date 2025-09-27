#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>  // For system()

#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>  // Windows: for _getch()
char getChar() {
    return _getch();
}
#else
#include <termios.h>
#include <unistd.h>
// POSIX (Linux/macOS): read one character without waiting for Enter
char getChar() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);           // Get current terminal settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);         // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);  // Apply new settings
    ch = getchar();                           // Read one character
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // Restore old settings
    return ch;
}
#endif

// Cross-platform clear screen
void clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("cls");   // Windows
#else
    std::system("clear"); // Linux/macOS
#endif
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    std::ifstream file(argv[1]);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << argv[1] << "\n";
        return 1;
    }

    std::string line;
    std::cout << "Press Enter to show next line, Space to restart, or Q to quit...\n\n";

    while (true) {
        if (std::getline(file, line)) {
            char ch = getChar();

#if defined(_WIN32) || defined(_WIN64)
            if (ch == '\r') {  // Enter key on Windows
#else
            if (ch == '\n') {  // Enter key on Linux/macOS
#endif
                std::cout << line << std::endl << std::endl;
            } else if (ch == ' ') {
                clearScreen();  // Clear the screen on Space
                file.clear();   // Reset EOF flag
                file.seekg(0);  // Go back to beginning of file
                std::cout << "Restarting from beginning...\n\n";
            } else if (ch == 'q' || ch == 'Q') {
                std::cout << "\nQuitting program...\n";
                break;
            } else {
                std::cout << "Invalid input. Press Enter, Space, or Q.\n";
            }
        } else {
            std::cout << "\nEnd of file reached.\n";
            break;
        }
    }

    return 0;
}