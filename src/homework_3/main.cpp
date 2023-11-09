#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <filesystem>

namespace {
    const std::string scoreFile = "high_scores.cpp";
    using Scores = std::map<std::string, int>;

    void updateScores(Scores& scores, const std::string& name, int score) {
        auto it = scores.find(name);
        if (it != scores.end()) {
            if (score < it->second) {
                it->second = score;
            }
        } else {
            scores[name] = score;
        }    
    }

    bool isFileGood() {
        if (!std::filesystem::exists(scoreFile)) {
            std::ofstream newFile(scoreFile);
            if (!newFile.is_open()) {
                std::cout << "Cannot create new file " << scoreFile << std::endl;
                return false;
            }
        }
        return true;
    }
    
    void writeFile(const Scores& scores) {
        std::ofstream file(scoreFile, std::ios_base::trunc);
        if (!file.is_open()) {
            std::cout << "Cannot open file for writing " << scoreFile << std::endl;
            return;
        }

        for (const auto& [k, v] : scores) {
            file << k << " " << v << '\n';
        }
    }

    Scores readFile() {
        std::ifstream file(scoreFile);
        if (!file.is_open()) {
            std::cout << "Cannot open file for reading " << scoreFile << std::endl;
            return {};
        }

        Scores scores;
        std::string name;
        int score;
        while (file) {            
            file >> name >> score;
            if (!file) {
                continue;
            }
            updateScores(scores, name, score);
        }

        return scores;
    }

    void addScore(const std::string& name, int score) {        
        if (!isFileGood()) {
            return;
        }
        
        auto scores = readFile();
        updateScores(scores, name, score);
        writeFile(scores);        
    }

    void printScore(const char* prefix = "") {
        std::cout << prefix << "High scores table:" << std::endl;
        for (const auto& [k, v] : readFile()) {
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

    std::srand(std::time(nullptr));
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
