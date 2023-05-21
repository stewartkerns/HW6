#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

fstream openFile();
string getFilepath();
vector<vector<int>> * readFile();

int main() {

    vector<vector<int>> * doubleVector = readFile();

    return 0;
}

string getFilepath(){
    cout << "Please enter a valid filepath for the file you would like to "
            "read: ";
    string filePath;

    getline(cin, filePath);

    return filePath;
}

fstream openFile(){
    fstream inputFile;


    do {
        inputFile.clear();
        inputFile.open(getFilepath());
        if (!inputFile.is_open()){
            cout << "Bad input, please try again." << endl;
        }
    } while (!inputFile.is_open());

    return inputFile;
}

vector<vector<int>> * readFile(){

    fstream file = openFile();
    string line;
    int arrayLine = 0;
    vector<vector<int>> * array = new vector<vector<int>>;
    while (getline(file, line)){
        for (int i = 0; i < line.length(); i++){
            if (line[i] == '0' || line[i] == '1'){
                array->at(arrayLine).push_back(line[i]);
            }
        }
        arrayLine++;
    }
}






