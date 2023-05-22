#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

fstream openFile();
string getFilepath();
vector<vector<int>> * readFile();
bool checkDigraph(vector<vector<int>> *);
void writeToFile(vector<vector<int>> *);

int main() {

    vector<vector<int>> * array = readFile();

    writeToFile(array);

    system("cd C:\\Users\\Stewart\\Desktop\\CPSC5031\\HW6\\cmake-build-debug");
    system("dot -Tpng myfile.dot -o myfile.png");
    system("start myfile.png");
    delete array;

    return 0;
}

string getFilepath(){
    cout << "Please enter a valid filepath for the file you would like to "
            "read: ";
    string filePath;

    //todo reenable this
//    getline(cin, filePath);

    filePath = "C:\\Users\\Stewart\\Desktop\\CPSC5031\\HW6\\cmake-build-debug"
               "\\adj4.txt";
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
    vector<int> lineNums;
    vector<vector<int>> * array = new vector<vector<int>>;
    while (getline(file, line)){

        for (int i = 0; i < line.length(); i++){
            if (line[i] == '0' || line[i] == '1'){
                lineNums.push_back(line[i] - '0');
            }
        }
        array->push_back(lineNums);
        lineNums.erase(lineNums.cbegin(), lineNums.cend());
    }
    file.close();
    return array;
}

bool checkDigraph(vector<vector<int>> * array){

    for (int i = 0; i < (array->size()); i++){
        for(int j = 0; j < array->at(i).size(); j++){
            if (array->at(i).at(j) == 1 && array->at(j).at(i) == 0){
                return true;
            }
        }
    }
    return false;
}

string getLabel (int);

void writeToFile(vector<vector<int>> * array){
    ofstream outFile("myfile.dot");
    //65
    if (!outFile.is_open()){
        cout << "File didn't open" << endl;
    }
    bool digraph = checkDigraph(array);
    if (digraph){
        outFile << "di";
    }
    outFile << "graph{" << endl;
    string label;
    for (int i = 0; i < array->size(); i++){
        label = getLabel(i);
        outFile << label << endl;

        for (int j = 0; j < array->at(i).size(); j++){
            if (array->at(i).at(j) == 1){
                if (digraph){
                    outFile << "\t" << label << "->" << getLabel(j) << endl;
                }
                else{
                    outFile << "\t" << label << "--" <<getLabel(j) << endl;
                    array->at(j).at(i) = 0;
                }
            }
        }
    }
    outFile << "}" << endl;
    outFile.close();
}

string getLabel(int number){

    char label = 'A';
    const int MAX_LETTERS = 26;
    string labelWord;

    if ( number > MAX_LETTERS){
        labelWord = label + to_string(number - MAX_LETTERS - 1);
    }
    else{
        labelWord = (char)(label + number);
    }
    return labelWord;
}





