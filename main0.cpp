#include <iostream> 
#include <fstream>

using namespace std;

char tolowerCase(char c){
    if(c >= 'A' && c <= 'Z') {
        c += 32; // +32 would make the uppercase character become lowercase version 
    }
    return c;
}

bool removePunctuation(char c ){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

int findWordIndex(const char words[][100], const char* word, int numOfUniqueWords) {
    for (int i = 0; i < numOfUniqueWords; ++i) {
        int j;
        for (j = 0; words[i][j] != '\0' && word[j] != '\0'; ++j) {
            if (words[i][j] != word[j]) {
                break;
            }
        }

        if (words[i][j] == '\0' && word[j] == '\0') {
            return i;  // Return the index if the word is found
        }
    }
    return -1;  // Return -1 if the word is not found
}

int sortWordAlphabetically(const char* word1, const char* word2, int count1, int count2) {
    if (count1 > count2) {
        return 1;
    } else if (count1 < count2) {
        return -1;
    } else {
        // If counts are the same, compare alphabetically
        int i = 0;
        while (word1[i] != '\0' && word2[i] != '\0') {
            if (word1[i] < word2[i]) {
                return 1;
            } else if (word1[i] > word2[i]) {
                return -1;
            }
            ++i;
        }
        if (word1[i] == '\0' && word2[i] != '\0') {
            return 1;
        } else if (word1[i] != '\0' && word2[i] == '\0') {
            return -1;
        }
        return 0;
    }
}

void wordSort(char words[][100], int *wordCounts, int numOfUniqueWords) {
    bool swapped;
    
    do {
        swapped = false;
        
        for (int i = 0; i < numOfUniqueWords - 1; i++) {
            if (sortWordAlphabetically(words[i], words[i + 1], wordCounts[i], wordCounts[i + 1]) < 0) {
                // Swap words
                char tempWord[100];
                strcpy(tempWord, words[i]);
                strcpy(words[i], words[i + 1]);
                strcpy(words[i + 1], tempWord);

                // Swap counts
                int tempCount = wordCounts[i];
                wordCounts[i] = wordCounts[i + 1];
                wordCounts[i + 1] = tempCount;

                swapped = true;
            }
        }
    } while (swapped);
}

void printWords(const char words[][100], int *wordCounts, int numOfUniqueWords){
    cout << "The first 10 words after sorted: "<< endl;
    for (int i = 0; i < 10; i++) {
        cout << words[i] << ": " << wordCounts[i] << endl;
    }
    cout << endl << "The last 10 words after sorted: "<< endl;
    for (int i = 10; i > 0; --i){
        cout << words[numOfUniqueWords - i] << ": " << wordCounts[numOfUniqueWords - i] << endl;
    }
    cout << endl << "The unique words: " << endl;
    for (int i = 0; i < numOfUniqueWords; ++i){
        if(wordCounts[i] == 1){
            cout << words[i] << endl;
        }
    }
}

void readFile(){
    string fileName;
    ifstream file;
    cout << "Please enter the file name: " ;
    cin >> fileName;
    file.open(fileName); // open the file from the input

    // Declare arrays to store words and their counts
    static const int maxWords = 50000; //Set the maximum number of words is 50000
    char words[maxWords][100];  // set the maximum word length is 99 characters
    int wordCounts[maxWords] = {0};  // Set the counts to 0
    int numOfUniqueWords = 0;  // Current number of unique words
    char c; //declare the character

    if(!file){
        cerr << "Cannot open the file";
    }
    cout << "Successfully open the file" << endl;

    while(file >> words[numOfUniqueWords]){
        int processedIndex = 0;
        for(int i= 0; words[numOfUniqueWords][i] != '\0'; ++i){
            if (removePunctuation(words[numOfUniqueWords][i])){
                words[numOfUniqueWords][processedIndex] = tolowerCase(words[numOfUniqueWords][i]);
                ++processedIndex;
            }
        }
        words[numOfUniqueWords][processedIndex] = '\0';
        if (processedIndex > 0) {
            // Check if the processed word is already in the array
            int index = findWordIndex(words, words[numOfUniqueWords], numOfUniqueWords);

            if (index != -1) {
                // Increment the count for the existing word
                wordCounts[index]++;
            } else {
                // Set the count to 1 for the new word
                wordCounts[numOfUniqueWords] = 1;
                numOfUniqueWords++;
            }
        }
    }
    wordSort(words, wordCounts, numOfUniqueWords);
    printWords(words, wordCounts, numOfUniqueWords);
    file.close();
}
int main(){

    // Read file
    readFile();    
    return 0;
}