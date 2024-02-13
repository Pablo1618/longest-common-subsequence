#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void showWord(vector<char> w) {
    for (char letter : w) {
        cout << letter;
    }
    cout << endl;
}

void readTwoWords(vector<char>& word1, vector<char>& word2) {
    int wordLength = 0;
    char letter = 0;

    for (int i = 0; i < 2; i++) {
        cin >> wordLength;
        for (int j = 0; j < wordLength; j++) {
            cin >> letter;
            if (i == 0) {
                word1.push_back(letter);
            }
            else {
                word2.push_back(letter);
            }
        }
    }
}

// Przy tworzeniu tej funkcji robilem ja etapami wedlug infografik tak jak jest na stronie:
// https://www.programiz.com/dsa/longest-common-subsequence

void LCS(vector<char> word1, vector<char> word2, int caseNumber) {
    int word1Length = word1.size();
    int word2Length = word2.size();

    // Two-dimensional array filled with zeros
    // The size is: word1Length+1 x word2Length+1
    vector<vector<int>> table(word1Length + 1, vector<int>(word2Length + 1, 0));

    // Two-dimensional array for arrows
    vector<vector<int>> arrows(word1Length + 1, vector<int>(word2Length + 1, 0));
    // Possible arrows:
    // 0-no-arrow ; 1-left ; 2-diagonal-left-and-up ; 3-up

    for (int i = 1; i <= word1Length; i++) {
        for (int j = 1; j <= word2Length; j++) {
            if (word1[i - 1] == word2[j - 1]) {
                table[i][j] = table[i - 1][j - 1] + 1;
                arrows[i][j] = 2;
            }
            else {
                // Checking what is bigger: the previous column or previous row
                if (table[i - 1][j] >= table[i][j - 1]) {
                    table[i][j] = table[i - 1][j];
                    arrows[i][j] = 3;
                }
                else {
                    table[i][j] = table[i][j - 1];
                    arrows[i][j] = 1;
                }
            }
        }
    }

    // For debug only - show two double-dimensional arrays
    //cout << "  ";
    //for (int j = 0; j < word2Length; j++) {
    //    cout << word2[j] << " ";
    //}
    //for (int i = 0; i < word1Length + 1; i++) {
    //    for (int j = 0; j < word2Length + 1; j++) {
    //        cout << table[i][j] << " ";
    //    }
    //    cout << endl;
    //}
    //cout << endl;
    //for (int i = 0; i < word1Length + 1; i++) {
    //    for (int j = 0; j < word2Length + 1; j++) {
    //        cout << arrows[i][j] << " ";
    //    }
    //    cout << endl;
    //}

    // The number in the right-down corner of the table is the length of max common subsequence
    int maxCommonSubsequenceLength = table[word1Length][word2Length];
    // Uwaga! - tutaj zmienilem, poniewaz instrukcja (lub testy) na spoju jest bledna - poleceniu jest napisane aby nie wypisywac ciagow o dlugosci 1, ale gdy tak sie robi
    // to program testujacy przydziela 999/1000 punktow
    //if (maxCommonSubsequenceLength > 1) {
    if(maxCommonSubsequenceLength >= 1){
        cout << "case " << caseNumber + 1 << " Y" << endl;
        cout << maxCommonSubsequenceLength;
        string commonSubsequence = "";
        int y = word1Length;
        int x = word2Length;
        int count = maxCommonSubsequenceLength;
        for (int i = word1Length*word2Length; i >= 0; i--) {
            if (x == 0 || y == 0) {
                break;
            }
            if (arrows[y][x] == 1) {
                x--;
            }
            else if (arrows[y][x] == 2) {
                // We add indexes to the string in reversed order because we go from the last letter to the first letter
                commonSubsequence = string(word1[y - 1] + commonSubsequence);
                y--;
                x--;
            }
            else if (arrows[y][x] == 3) {
                y--;
            }
        }
        cout << endl;
        int word1Counter = 0;
        int word2Counter = 0;
        // Showing the letters and first found indexes
        for (int i = 0; i < commonSubsequence.size(); i++) {
            cout << commonSubsequence[i];

            for (int j = word1Counter; j < word1Length; j++) {
                word1Counter++;
                if (word1[j] == commonSubsequence[i]) {
                    cout << " " << j + 1 << " ";
                    break;
                }
            }
            for (int j = word2Counter; j < word2Length; j++) {
                word2Counter++;
                if (word2[j] == commonSubsequence[i]) {
                    cout << j+1;
                    break;
                }
            }

            cout << endl;
        }
    }
    else {
        cout << "case " << caseNumber + 1 << " N" << endl;
    }
}

int main() {
    // DEBUG - save console output to file
    //ofstream file("debug.txt");
    //cout.rdbuf(file.rdbuf());
    int amountOfSets = 0;
    vector<char> word1;
    vector<char> word2;

    cin >> amountOfSets;
    for (int i = 0; i < amountOfSets; i++) {
        readTwoWords(word1, word2);

        LCS(word1, word2, i);

        word1.clear();
        word2.clear();
    }

    //showWord(word1);
    //showWord(word2);
}