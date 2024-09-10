#include <iostream>
#include <cstdlib>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

void convertPngAndJpgToWebp(const std::string& filePath) {

    std::string outputFilePath = filePath.substr(0, filePath.find_last_of(".")) + ".webp";
    std::string command = "cwebp -q 100 \"" + filePath + "\" -o \"" + outputFilePath + "\"";

    std::cout << "Executing command: " << command << std::endl;

    int result =std::system(command.c_str());

    if (result == 0){
        std::cout << "Conversion successfully completed. File saved as: " << outputFilePath << std::endl;
    }
    else{
    std::cerr << "Error occurred during conversion" << std::endl;
    }
}

void processFilesInAllDirectory(const std::string& directoryPath) {
    for (const auto& entry : fs::recursive_directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().string();
            std::string extension = entry.path().extension().string();

            if (extension == ".png" || extension == ".jpg" || extension == ".jpeg") {
                convertPngAndJpgToWebp(filePath);
            } else {
                std::cout << "Skipping a file: " << filePath << " (unsupported extension)"<< std::endl;
            }
        }
    }
}

void processFilesInDirectory() {
    std::string directoryPath = fs::current_path().string();

    char cORs;

    std::cout << "Do you want to convert files only in the current folder [c] or also in subfolders [s]?" << std::endl;
    std::cout << "Enter 'c' or 's' and press enter:" << std::endl;

    std::cin >> cORs;

    if (cORs == 's') {
        processFilesInAllDirectory(directoryPath);
    } else if (cORs == 'c') {
        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            if (entry.is_regular_file()) {
                std::string filePath = entry.path().string();
                std::string extension = entry.path().extension().string();

                if (extension == ".png" || extension == ".jpg" || extension == ".jpeg") {
                    convertPngAndJpgToWebp(filePath);
                } else {
                    std::cout << "Skipping a file: " << filePath << " (unsupported extension)" << std::endl;
                }
            }
        }
    } else {
        std::cout << "Invalid option. Please enter 'c' or 's'." << std::endl;
    }
}

int main(){

processFilesInDirectory();

    return 0;
}