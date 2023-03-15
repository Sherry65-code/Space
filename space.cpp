#include<iostream>
#include<fstream>
#include<string>
#include<thread>
#include<chrono>
using namespace std;


string wholefile = "";
string filename = "";
int isTimerRunning = 0;
int timerlength = 0;
int isCompiled = 0;
int isDebug = 0;
string strip(const string& str) {
    auto first = str.find_first_not_of(' ');
    auto last = str.find_last_not_of(' ');
    if (first == string::npos || last == string::npos) {
        return "";
    }
    return str.substr(first, last - first + 1);
}
int getFile(string filename)
{
	ifstream inputFile(filename);
	if (inputFile.is_open())
	{
		string line;
		while (getline(inputFile, line))
		{
			wholefile+=line+".";
		}

		inputFile.close();
	}
	else
	{
		return 1;
	}
	return 0;
	
}

void dprint(string str)
{
	if (isDebug == 1)
	{
		cout << str << endl;
	}
	else
	{

	}
}

void compile()
{
	// File code in {wholefile}	
	// First find no. of lines in the file
	int ARRAY_SIZE = 0;
	int pointer = 0;
	if (isDebug == 1)
	{
		cout<<"DEBUG: wholefile<length> = "<<wholefile.length();
	}
	while (pointer < wholefile.length())
	{
		if (wholefile.at(pointer) == '.')
		{
			ARRAY_SIZE++;
		}
		pointer++;
	}
	// remove all lines with whitespaces
	int finalcode[ARRAY_SIZE+1]  = {};
	// find the length of each line and put it in final code
	pointer = 0;
	int pointer2 = 0;
	while (pointer<wholefile.length())
	{
		if (wholefile.at(pointer) == '.')
		{
			pointer2++;
		}
		else if (wholefile.at(pointer) == ' ')
		{
			finalcode[pointer2] +=1;
		}
		else
		{
			
		}
		pointer++;
	}
	// Now we have our code length so lets try to print something
	pointer = 0;
	char ch = 0;
	string code = "";
	int temp = 0;
	while (pointer <= ARRAY_SIZE)
	{
		temp = finalcode[pointer];
		ch = temp;
		if (temp == 34)
		{
			code+= "\\\"";
		}
		else if (temp == 10)
		{
			code+="\\n";
		}
		else if (temp == 0 || ch == '\0')
		{
			
		}
		else if (temp == 32)
		{
			code += " ";
		}
		else
		{
			code = code+""+ch+"";
		}
		if (isDebug == 1)
		{
			cout<<"DEBUG: pointer = "<<pointer<<" & finalcode[pointer] = "<<finalcode[pointer]<<" & code = "<<code;
		}
		pointer++;
	}	
	string fcode = code;
	code = "";
	code = "#include<iostream>\nint main(){\nstd::cout<<\""+fcode+"\"<<std::endl;\n}";

	// Now compile it using the gnu gcc compiler
	ofstream outputFile;
	string outputFileName = "output.cpp";
	outputFile.open(outputFileName);

	if (outputFile.is_open()) {
		outputFile << code;
		outputFile.close();
	}
	else
	{
		cout << "Internal Error!" << endl;
	}
	string filefirstname = "";
	pointer = 0;
	while (pointer<filename.length())
	{
		if (filename.at(pointer) == '.')
		{
			break;
		}
		else
		{
			filefirstname+=filename.at(pointer);
		}
		pointer++;
	}	
	string cmdc = "c++ output.cpp -o "+filefirstname;
	if (system(cmdc.c_str()) == 0)
	{
		cout << "Compiled" << endl;
	}
	else
	{
		cout << "Could Not Compile. :( " << endl;

	}
	isCompiled = 1;

}


int main(int argc, char* argv[])
{	
		if (argv[1] == "-d")
		{
			filename = argv[2];
			isDebug = 1;
		}
		else
		{
	filename = argv[1];
		}
			
		
		if (isDebug == 1)
		{
			cout << "DEBUG: Filename = " << filename<<endl;
		}
	if (filename == "")
	{
		cout << "No filename argument found" << endl;
		return 1;
	}
	if (getFile(filename) == 1)
	{
		cout << "File inputted not found!" << endl;
		return 2;
	}
	else
	{
		cout << "Compiling..."<<endl;
		compile();
	}
	// Compiling Process shown here
	return 0;
}

