#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

bool isDebug = false;

string strip(const string& str) {
    auto first = str.find_first_not_of(' ');
    auto last = str.find_last_not_of(' ');
    if (first == string::npos || last == string::npos) {
        return "";
    }
    return str.substr(first, last - first + 1);
}

vector<int> getFile(const string& filename) {
    vector<int> codeLengths;
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            codeLengths.push_back(strip(line).length());
        }
    }
    return codeLengths;
}

string generateOutputCode(const vector<int>& codeLengths) {
    string code;
    for (int length : codeLengths) {
        char ch = static_cast<char>(length);
        if (ch == '\"') {
            code += "\\\"";
        } else if (ch == '\n') {
            code += "\\n";
        } else if (ch != '\0') {
            code += ch;
        }
    }
    return "#include<iostream>\nint main(){\nstd::cout<<\"" + code + "\"<<std::endl;\n}";
}

bool compile(const string& filename, const string& code) {
    ofstream outputFile("output.cpp");
    if (!outputFile.is_open()) {
        cerr << "Internal Error!" << endl;
        return false;
    }
    outputFile << code;
    outputFile.close();

    string outputFileName = filename.substr(0, filename.find_last_of('.')) + ".out";
    string cmdc = "c++ output.cpp -o " + outputFileName;
    return system(cmdc.c_str()) == 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "No filename argument found" << endl;
        return 1;
    }

    if (string(argv[1]) == "-d") {
        if (argc < 3) {
            cerr << "No filename argument found after debug flag" << endl;
            return 1;
        }
        isDebug = true;
        argv++;
    }

    string filename = argv[1];
    if (isDebug) {
        cout << "DEBUG: Filename = " << filename << endl;
    }

    vector<int> codeLengths = getFile(filename);
    if (codeLengths.empty()) {
        cerr << "File inputted not found or empty!" << endl;
        return 2;
    }

    string outputCode = generateOutputCode(codeLengths);
    cout << "Compiling..." << endl;
    if (compile(filename, outputCode)) {
        cout << "Compiled" << endl;
    } else {
        cerr << "Could Not Compile. :(" << endl;
    }
    return 0;
}
