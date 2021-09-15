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
    string token = "";

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
    char enter;
    for(int i = 0; i < code.size(); i++)
    {
        opcode = code[i];
        switch (opcode)
		{
        	case ADD:
                cout << "ADD " << code[code[i+1]] << endl;
                //cout << acc << "+" << code[code[i+1]] << endl;
        		acc = acc + code[code[i+1]];
                i++;
                cout << "ACC:" << acc << endl;
                cout << "CONTADOR:" << i+1 << endl;
        		break;
        	case SUB:
                cout << "SUB " << code[code[i+1]] << endl;
                //cout << acc << "-" << code[code[i+1]] << endl;
        		acc = acc - code[code[i+1]];
                i++;
                cout << "ACC:" << acc << endl;
                cout << "CONTADOR:" << i+1 << endl;
        		break;
        	case MUL:
                cout << "MUL " << code[code[i+1]] << endl;
                //cout << acc << "*" << code[code[i+1]] << endl;
        		acc = acc * code[code[i+1]];
                i++;
                cout << "ACC:" << acc << endl;
                cout << "CONTADOR:" << i+1 << endl;
        		break;
        	case DIV:
                cout << "DIV " << code[code[i+1]] << endl;
                //cout << acc << "/" << code[code[i+1]] << "=" << acc / code[code[i+1]] << endl;
        		acc = acc / code[code[i+1]];
                i++;
                cout << "ACC:" << acc << endl;
                cout << "CONTADOR:" << i+1 << endl;
        		break;
        	case JMP:
                cout << "JMP " << code[i+1] << endl;
                //cout << acc << "JMP" << code[i+1] << endl;
        		i = code[i+1]-1;
                cout << "ACC:" << acc << endl;
                cout << "CONTADOR:" << i+1 << endl;
        		break;
        	case JMPN:
                cout << "JMPN " << code[i+1] << endl;
                //cout << acc << "JMPN" << code[i+1] << endl;
                if(acc < 0)
                {
                    i = code[i+1]-1;
                }
                else
                {
                    i++;
                }
                cout << "ACC:" << acc << endl;
                cout << "CONTADOR:" << i+1 << endl;
        		break;
        	case JMPP:
                cout << "JMPP " << code[i+1] << endl;
                //cout << acc << "JMPP" << code[i+1] << endl;
        		if(acc > 0)
                {
                    i = code[i+1]-1;
                }
                else
                {
                    i++;
                }
                cout << "ACC:" << acc << endl;
                cout << "CONTADOR:" << i+1 << endl;
        		break;
        	case JMPZ:
                cout << "JMPZ " << code[i+1] << endl;
                //cout << acc << "JMPZ" << code[i+1] << endl;
        		if(acc == 0)
                {
                    i = code[i+1]-1;
                }
                else
                {
                    i++;
                }
                cout << "ACC:" << acc << endl;
                cout << "CONTADOR:" << i+1 << endl;
        		break;
        	case COPY:
                cout << "COPY " << code[i+1] << "," << code[i+2] << endl;
                //cout << code[code[i+2]] << " COPY " << code[code[i+1]] << endl;
        		code[code[i+2]] = code[code[i+1]];
                i += 2;
                cout << "ACC:" << acc << endl;
                cout << "CONTADOR:" << i+1 << endl;
        		break;
        	case LOAD:
                cout << "LOAD " << code[code[i+1]] << endl;
                //cout << "LOAD" << code[code[i+1]] << endl;
        		acc = code[code[i+1]];
                i++;
                cout << "ACC:" << acc << endl;
                cout << "CONTADOR:" << i+1 << endl;
        		break;
        	case STORE:
                cout << "STORE " << code[code[i+1]] << endl;
                //cout << "STORE" << acc << "em" << code[i+1] << endl;
        		code[code[i+1]] = acc;
                i++;
                cout << "ACC:" << acc << endl;
                cout << "CONTADOR:" << i+1 << endl;
        		break;
        	case INPUT:
                cout << "INPUT " << code[i+1] << endl;
    			cin >> input;
                cin.ignore();
                code[code[i+1]] = input;
                i++;
                cout << "ACC:" << acc << endl;
                cout << "CONTADOR:" << i+1 << endl;
    			break;
			case OUTPUT:
                cout << "OUTPUT " << code[code[i+1]] << endl;
                //cout << "OUTPUT";
    			//cout << code[code[i+1]] << endl;
                i++;
                cout << "ACC:" << acc << endl;
                cout << "CONTADOR:" << i+1 << endl;
                cin.ignore();
    			break;
			case STOP:
                cout << "STOP" << endl;
                cout << "ACC:" << acc << endl;
                cout << "CONTADOR:" << i+1 << endl;
    			break;
			default:
                break;
        }
        if(opcode == STOP)
        {
            break;
        }
        cout << "+++++++++++++++++++++" << endl;
    }

}


int main(int argc, char *argv[])
{
    vector<int> code;

    code = read_code(argv[1]);

    simulator(code);

    return 0;
}