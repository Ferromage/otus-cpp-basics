#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <filesystem>

namespace {
    const std::string scoreFile = "high_scores.cpp";

    void addScore(const std::string& userName, int userScore) {
        if (!std::filesystem::exists(scoreFile)) {
            std::ofstream newFile(scoreFile);
            if (!newFile.is_open()) {
                std::cout << "Cannot create new file " << scoreFile << std::endl;
                return;
            }
        }
        
        std::fstream file(scoreFile, std::ios_base::in);
        if (!file) {
            std::cout << "Cannot open file for reading (1) " << scoreFile << std::endl;
            return;
        }

        std::map<std::string, int> nameToScore;
        std::string name;
        int score;
        while (file) {            
            file >> name >> score;
            if (!file) {
                continue;
            }

            if (nameToScore.count(name)) {
                if (score < nameToScore[name]) {
                    nameToScore[name] = score;
                }
            } else {
                nameToScore[name] = score;
            }
        }

        if (nameToScore.count(userName)) {
            if (userScore < nameToScore[userName]) {
                nameToScore[userName] = userScore;
            }
        } else {
            nameToScore[userName] = userScore;
        }

        file.close();
        file.open(scoreFile, std::ios_base::out | std::ios_base::trunc);
        if (!file.is_open()) {
            std::cout << "Cannot open file for writing" << scoreFile << std::endl;
            return;
        }

        for (const auto& [k, v] : nameToScore) {
            file << k << " " << v << '\n';
        }
    }

    void printScore(const char* prefix = "") {
        std::ifstream ifs(scoreFile);
        if (!ifs.is_open()) {
            std::cout << "Cannot open file for reading (2) " << scoreFile << std::endl;
            return;
        }

        std::string name;
        int score;
        std::map<std::string, int> nameToScore;
        while (ifs) {
            ifs >> name >> score;
            if (!ifs) {
                continue;
            }
            
            if (nameToScore.count(name)) {
                if (score < nameToScore[name]) {
                    nameToScore[name] = score;
                }
            } else {
                nameToScore[name] = score;
            }
        }

        std::cout << prefix << "High scores table:" << std::endl;
        for (const auto &[k, v] : nameToScore) {
            std::cout << k << " " << v << std::endl;
        }
    }

    int getMaxNumber(int argc, char** argv) {
        using namespace std::literals::string_literals;
        constexpr int defaultMax = 100;

        if (argc > 2) {
            try {
                if (std::string(argv[1]) == "-max"s) {                
                    const auto num = std::stoi(argv[2]);
                    return num > 0 ? num : defaultMax;                
                } else if (std::string(argv[1]) == "-level"s) {
                    const auto level = std::stoi(argv[2]);
                    if (level == 1) {
                        return 10;
                    } else if (level == 2) {
                        return 50;
                    } else if (level == 3) {
                        return 100;
                    }
                }
            } catch (std::exception&) {}            
        }
        
        return defaultMax;
    }
}

int main(int argc, char** argv) {
    using std::cout;
    using std::cin;
    using std::endl;
    using std::string;
    using namespace std::literals::string_literals;
    
    if (argc > 1 && string(argv[1]) == "-table"s) {
        printScore();
        return 0;
    }

    cout << "Hi! Enter your name, please:" << endl;
    string userName;
    cin >> userName;

    std:srand(std::time(nullptr));
    const int magicNumber = std::rand() % getMaxNumber(argc, argv);
    cout << "Enter your guess:" << endl;

    int attempts = 1;
    string userNumberStr;
    while (true) {
        cin >> userNumberStr;
        if (!cin) {
            cout << "Not a number!" << endl;
            cin.clear();
            continue;
        }

        int userNumber;
        try {
            userNumber = stoi(userNumberStr);
        } catch(std::exception&) {
            cout << "Exception. Not a number!" << endl;
            cin.clear();
            continue;
        }

        if (userNumber > magicNumber) {
            cout << "greater than " << userNumber << endl;
        } else if (userNumber < magicNumber) {
            cout << "less than " << userNumber << endl;
        } else {
            cout << "you win! attempts = " << attempts << endl;
            break;
        }
        
        attempts++;
    };
      
    addScore(userName, attempts);
    printScore("\n");
    
    return 0;
}
