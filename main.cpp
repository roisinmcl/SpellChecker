#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>

#include "BTree.h"
#include "LinkedList.h"
using namespace std;

int main(int argc, const char * argv[]) {

    bool debug = true;
    if (argc != 4 && debug == false) {
        cout << "Invalid input. Exiting program..." << endl;
        return 0;
    }

    LinkedList lexiconLL;
    LinkedList inputFile;
    LinkedList removalFile;
    BTree<3> lexiconB;
    BTree<9> lexiconBM;

    try {

        // **** Input lexicon file into LinkedList, BTree<3>, and BTree<M> (M = 9) ****
        ifstream inFile(argv[2], ios::in);
        if (!inFile) {
            cout << argv[0] << endl;
            cout << "Input: " << argv[2] << endl;
            string error = "Cannot open file. Exiting program...";
            throw error;
        }

        //cout << "File opened successfully!" << endl;

        while (!inFile.eof()) {
            string str;
            while (inFile >> str) {
                transform(str.begin(), str.end(), str.begin(), ::tolower);

                // Linked list
                Node* n = new Node(str);
                lexiconLL.add(n);

                // BTree
                lexiconB.insert(lexiconB.root, str);

                // BTree of size M
                lexiconBM.insert(lexiconBM.root, str);

            }
        }
        inFile.close();

        // ********* Input input file into LinkedList *********
        ifstream inFile2(argv[1], ios::in);
        if (!inFile2) {
            cout << argv[0] << endl;
            cout << "Input: " << argv[1] << endl;
            string error = "Cannot open file. Exiting program...";
            throw error;
        }

        //cout << "File opened successfully!" << endl;

        while (!inFile2.eof()) {
            string str;
            while (inFile2 >> str) {
                transform(str.begin(), str.end(), str.begin(), ::tolower);
                if (ispunct(str[str.size()-1])) {
                    str = str.substr(0,str.size()-1);
                }

                // Linked list
                Node* n = new Node(str);
                inputFile.add(n);
            }
        }
        inFile2.close();

        // ********* Input removal file into LinkedList *********
        ifstream inFile3(argv[3], ios::in);
        if (!inFile3) {
            cout << argv[0] << endl;
            cout << "Input: " << argv[3] << endl;
            string error = "Cannot open file. Exiting program...";
            throw error;
        }

        //cout << "File opened successfully!" << endl;

        while (!inFile3.eof()) {
            string str;
            while (inFile3 >> str) {
                transform(str.begin(), str.end(), str.begin(), ::tolower);
                if (ispunct(str[str.size()-1])) {
                    str = str.substr(0,str.size()-1);
                }

                // Linked list
                Node* n = new Node(str);
                removalFile.add(n);
            }
        }

        inFile3.close();

    } catch(string error) {
        cout << error << endl;
        return 0;
    }

    // ************** End input *****************

    LinkedList lexiconLL1 = lexiconLL;

    //1. Lexicon stored in Linked List
    clock_t timeBegin1, timeEnd1;
    double totalTime1 = 0.0;
    timeBegin1 = clock();

    int numberMisspelled = 0;
    Node* ptr = inputFile.head;
    while (ptr != NULL) {
        string word = ptr->toString();
        if (! (lexiconLL1.findAndMoveFront(word)) ) {
            numberMisspelled++;
            //cout << "Misspelling: " << word << endl;
        }
        ptr = ptr->next;
    }

    timeEnd1 = clock();
    totalTime1 = (double)(timeEnd1 - timeBegin1)/CLOCKS_PER_SEC;

    string highestFreqWord = "";
    int highestFreqWordCount = 0;
    ptr = lexiconLL1.head;

    while (ptr != NULL) {
        if (ptr->getFrequency() > highestFreqWordCount) {
            highestFreqWord = ptr->getWord();
            highestFreqWordCount = ptr->getFrequency();
        }
        ptr = ptr->next;
    }

    cout << "====================== Output #1 ==========================" << endl;
    cout << "Total number of misspelled words: " << numberMisspelled << endl;
    cout << "Runtime (approx): " << totalTime1<< endl;
    cout << "Most frequently occuring word: " << highestFreqWord << endl;
    cout << "Frequency of most common word: " << highestFreqWordCount << endl;
    cout << "===========================================================" << endl;
    cout << endl;
    cout << endl;



    //2. Lexicon stored in BTree
    clock_t timeBegin2, timeEnd2;
    double totalTime2 = 0.0;
    timeBegin2 = clock();

    int numberMisspelled2 = 0;
    Node* ptr2 = inputFile.head;
    while (ptr2 != NULL) {
        string word = ptr2->toString();
        if (! (lexiconB.search(lexiconB.root, word)) ) {
            numberMisspelled2++;
            //cout << "Misspelling: " << word << endl;
        }
        ptr2 = ptr2->next;
    }

    timeEnd2 = clock();
    totalTime2 = (double)(timeEnd2 - timeBegin2)/CLOCKS_PER_SEC;

    cout << "====================== Output #2 ==========================" << endl;
    cout << "Total number of misspelled words: " << numberMisspelled2 << endl;
    cout << "Runtime (approx): " << totalTime2 << endl;
    cout << "Most frequently occuring word: " << highestFreqWord << endl;
    cout << "Frequency of most common word: " << highestFreqWordCount << endl;
    cout << "===========================================================" << endl;
    cout << endl;
    cout << endl;


    //3. Lexicon stored in BTree (of determined size M)
    clock_t timeBegin3, timeEnd3;
    double totalTime3 = 0.0;
    timeBegin3 = clock();

    int numberMisspelled3 = 0;
    Node* ptr3 = inputFile.head;
    while (ptr3 != NULL) {
        string word = ptr3->toString();
        if (! (lexiconBM.search(lexiconBM.root, word)) ) {
            numberMisspelled3++;
            //cout << "Misspelling: " << word << endl;
        }
        ptr3 = ptr3->next;
    }

    timeEnd3 = clock();
    totalTime3 = (double)(timeEnd3 - timeBegin3)/CLOCKS_PER_SEC;

    cout << "====================== Output #3 ==========================" << endl;
    cout << "Total number of misspelled words: " << numberMisspelled3 << endl;
    cout << "Runtime (approx): " << totalTime3 << endl;
    cout << "Most frequently occuring word: " << highestFreqWord << endl;
    cout << "Frequency of most common word: " << highestFreqWordCount << endl;
    cout << "===========================================================" << endl;
    cout << endl;
    cout << endl;



    cout << "***********************************************************" << endl;
    cout << "****************** Output after Removals ******************" << endl;
    cout << "***********************************************************" << endl;
    cout << endl;
    cout << endl;

    // Remove words in removalFile from lexiconLL, lexiconB, and lexiconBM
    Node* removalPtr = removalFile.head;
    while (removalPtr != NULL) {
        string wordToRemove = removalPtr->getWord();

        // Remove from lexiconLL
        lexiconLL.remove(wordToRemove);

        // Remove from lexiconB
        lexiconB.remove(lexiconB.root, wordToRemove);

        // Remove from lexiconBM
        lexiconBM.remove(lexiconBM.root, wordToRemove);

        removalPtr = removalPtr->next;
    }

    LinkedList lexiconLL2 = lexiconLL;

    //1. Lexicon stored in Linked List
    clock_t timeBegin4, timeEnd4;
    double totalTime4 = 0.0;
    timeBegin4 = clock();

    int numberMisspelled4 = 0;
    Node* ptr4 = inputFile.head;
    while (ptr4 != NULL) {
        string word = ptr4->toString();
        if (! (lexiconLL2.findAndMoveFront(word)) ) {
            numberMisspelled4++;
            //cout << "Misspelling: " << word << endl;
        }
        ptr4 = ptr4->next;
    }

    timeEnd4 = clock();
    totalTime4 = (double)(timeEnd4 - timeBegin4)/CLOCKS_PER_SEC;

    string highestFreqWord2 = "";
    int highestFreqWordCount2 = 0;
    ptr4 = lexiconLL2.head;

    while (ptr4 != NULL) {
        if (ptr4->getFrequency() > highestFreqWordCount2) {
            highestFreqWord2 = ptr4->getWord();
            highestFreqWordCount2 = ptr4->getFrequency();
        }
        ptr4 = ptr4->next;
    }

    cout << "====================== Output #1 ==========================" << endl;
    cout << "Total number of misspelled words: " << numberMisspelled4 << endl;
    cout << "Runtime (approx): " << totalTime4 << endl;
    cout << "Most frequently occuring word: " << highestFreqWord2 << endl;
    cout << "Frequency of most common word: " << highestFreqWordCount2 << endl;
    cout << "===========================================================" << endl;
    cout << endl;
    cout << endl;



    //2. Lexicon stored in BTree
    clock_t timeBegin5, timeEnd5;
    double totalTime5 = 0.0;
    timeBegin5 = clock();

    int numberMisspelled5 = 0;
    Node* ptr5 = inputFile.head;
    while (ptr5 != NULL) {
        string word = ptr5->toString();
        if (! (lexiconB.search(lexiconB.root, word)) ) {
            numberMisspelled5++;
            //cout << "Misspelling: " << word << endl;
        }
        ptr5 = ptr5->next;
    }

    timeEnd5 = clock();
    totalTime5 = (double)(timeEnd5 - timeBegin5)/CLOCKS_PER_SEC;

    cout << "====================== Output #2 ==========================" << endl;
    cout << "Total number of misspelled words: " << numberMisspelled5 << endl;
    cout << "Runtime (approx): " << totalTime5 << endl;
    cout << "Most frequently occuring word: " << highestFreqWord2 << endl;
    cout << "Frequency of most common word: " << highestFreqWordCount2 << endl;
    cout << "===========================================================" << endl;
    cout << endl;
    cout << endl;


    //3. Lexicon stored in BTree (of determined size M)
    clock_t timeBegin6, timeEnd6;
    double totalTime6 = 0.0;
    timeBegin6 = clock();

    int numberMisspelled6 = 0;
    Node* ptr6 = inputFile.head;
    while (ptr6 != NULL) {
        string word = ptr6->toString();
        if (! (lexiconBM.search(lexiconBM.root, word)) ) {
            numberMisspelled6++;
            //cout << "Misspelling: " << word << endl;
        }
        ptr6 = ptr6->next;
    }

    timeEnd6 = clock();
    totalTime6 = (double)(timeEnd6 - timeBegin6)/CLOCKS_PER_SEC;

    cout << "====================== Output #3 ==========================" << endl;
    cout << "Total number of misspelled words: " << numberMisspelled6 << endl;
    cout << "Runtime (approx): " << totalTime6 << endl;
    cout << "Most frequently occuring word: " << highestFreqWord2 << endl;
    cout << "Frequency of most common word: " << highestFreqWordCount2 << endl;
    cout << "===========================================================" << endl;
    cout << endl;
    cout << endl;


    return 0;
}
