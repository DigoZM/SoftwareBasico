#include <iostream>
#include <fstream> 
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

#define ADD 1
#define SUB 2
#define MUL 3
#define DIV 4
#define JMP 5
#define JMPN 6
#define JMPP 7
#define JMPZ 8
#define COPY 9
#define LOAD 10
#define STORE 11
#define INPUT 12
#define OUTPUT 13
#define STOP 14
#define CONST 15
#define SPACE 16 

vector<int> read_code(char* fileName)
{
	string myText;
	ifstream MyReadFile(fileName);
    vector<int> code;
    string token;

	while (getline (MyReadFile, myText))
	{
		for (auto x: myText)
		{
            if(x == ' ')
            {
                code.push_back(stoi(token));
                token = "";
            }
            else
            {
                token = token + x;
            }
        }
    }
    return code;
}

void simulator(vector<int> code)
{
    int opcode;
    int acc = 0;
    int temp;
    int input;
    for(int i = 0; i < code.size(); i++)
    {
        opcode = code[i];
        switch (opcode)
		{
        	case ADD:
                //cout << acc << "+" << code[code[i+1]] << endl;
        		acc = acc + code[code[i+1]];
                i++;
        		break;
        	case SUB:
                //cout << acc << "-" << code[code[i+1]] << endl;
        		acc = acc - code[code[i+1]];
                i++;
        		break;
        	case MUL:
                //cout << acc << "*" << code[code[i+1]] << endl;
        		acc = acc * code[code[i+1]];
                i++;
        		break;
        	case DIV:
                //cout << acc << "/" << code[code[i+1]] << "=" << acc / code[code[i+1]] << endl;
        		acc = acc / code[code[i+1]];
                i++;
        		break;
        	case JMP:
                //cout << acc << "JMP" << code[i+1] << endl;
        		i = code[i+1]-1;
        		break;
        	case JMPN:
                //cout << acc << "JMPN" << code[i+1] << endl;
                if(acc < 0)
                {
                    i = code[i+1]-1;
                }
                else
                {
                    i++;
                }
        		break;
        	case JMPP:
                //cout << acc << "JMPP" << code[i+1] << endl;
        		if(acc > 0)
                {
                    i = code[i+1]-1;
                }
                else
                {
                    i++;
                }
        		break;
        	case JMPZ:
                //cout << acc << "JMPZ" << code[i+1] << endl;
        		if(acc == 0)
                {
                    i = code[i+1]-1;
                }
                else
                {
                    i++;
                }
        		break;
        	case COPY:
                //cout << code[code[i+2]] << " COPY " << code[code[i+1]] << endl;
        		code[code[i+2]] = code[code[i+1]];
                i += 2;
        		break;
        	case LOAD:
                //cout << "LOAD" << code[code[i+1]] << endl;
        		acc = code[code[i+1]];
                i++;
        		break;
        	case STORE:
                //cout << "STORE" << acc << "em" << code[i+1] << endl;
        		code[code[i+1]] = acc;
                i++;
        		break;
        	case INPUT:
    			cin >> input;
                code[code[i+1]] = input;
                i++;
    			break;
			case OUTPUT:
                //cout << "OUTPUT";
    			cout << code[code[i+1]] << endl;
                i++;
    			break;
			case STOP:
                //cout << "STOP" << endl;
    			break;
			default:
                break;
        }
        if(opcode == STOP)
        {
            break;
        }
    }

}


int main(int argc, char *argv[])
{
    vector<int> code;

    code = read_code(argv[1]);

    simulator(code);

    return 0;
}