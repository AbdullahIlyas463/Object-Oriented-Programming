#include <iostream>
#include <string>
using namespace std;

int rowCount = 0;
int* colCount;


string** CreateDynamicArray(char* ws) 
{
    string input(ws);

    
    for (char c : input) {
        if (c == '#')
            rowCount++;
    }
    rowCount++; 

    colCount = new int[rowCount];

    int r = 0;
    colCount[r] = 1;

    int len = input.length();
    for (int index = 0; index < len; index++) {
        if (input[index] == ' ')
            (*(colCount + r))++;
        else if (input[index] == '#') {
            r++;
            *(colCount + r) = 1;
        }
    }

    string** arr = new string * [rowCount];
    for (int i = 0; i < rowCount; i++) {
        arr[i] = new string[colCount[i]];
    }

    int i = 0, j = 0;
    string word = "";

    for (char c : input) {
        if (c == ' ' || c == '#') {
            arr[i][j++] = word;
            word = "";
            if (c == '#') {
                i++;
                j = 0;
            }
        }
        else {
            word += c;
        }
    }
    arr[i][j] = word; 

    return arr;
}

int main() {
    char data[] =
        "abandon discontinue vacate#"
        "absent missing unavailable#"
        "cable wire#"
        "calculate compute determine measure#"
        "safety security refuge";

    string** thesaurus = CreateDynamicArray(data);

    cout << "Thesaurus Groups:\n\n";
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount[i]; j++) {
            cout << thesaurus[i][j] << " ";
        }
        cout << endl;
    }


    string query;
    cout << "\nEnter a word: ";
    cin >> query;

    for (int i = 0; i < rowCount; i++) {
        if (thesaurus[i][0] == query) {
            cout << "Last synonym: "
                << thesaurus[i][colCount[i] - 1] << endl;
            break;
        }
    }

    for (int i = 0; i < rowCount; i++) {
        delete[] thesaurus[i];
    }
    delete[] thesaurus;
    delete[] colCount;

    return 0;
}