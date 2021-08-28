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
#define jmp 5
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

struct SymbolTableElements
{
	string symbol;
	int value;
	bool def;
	int list;
};


// string get_token(string codeLine){
//   string token;

//   for (int i = 0; i < codeLine.sizu; i++)
//   {
//     /* code */
//   }
  
// }

// DEBUG FUNCTIONS

void print_vector(vector<int> v)
{
	for(int i=0; i<v.size(); ++i)
	{
		cout << v[i] << ' ';
	}
	cout << endl << endl;
}

void print_ST(vector<SymbolTableElements> v)
{
	cout << "Symbol Table" << endl;
	for(int i=0; i<v.size(); ++i)
	{
		cout << v[i].symbol << " " << v[i].value << " " << v[i].def << " " << v[i].list << endl;
	}
}

// END OF DEBUG FUNCTIONS

string preprocessing(char* fileName)
{
	string myText;
	ifstream MyReadFile(fileName);
	string codePreprocessed;
	char lastX;
	string line;
	int count = 0;
	bool addChar = true;

	while (getline (MyReadFile, myText))
	{
		line = "";
		count = 0;
		for (auto x: myText)
		{
			addChar = true;
			if(x == '\t')
			{
				x = ' ';
			}
			if(count == 0 && (x == ' ' || x == '\t'))
			{
				addChar = false;
			}
			else
			{
				count++;
			}
			if(x == ' ' && lastX == ' ')
			{
				addChar = false;
			}
			if(addChar)
			{
				line = line + x;
			}

			lastX = x;
		}
		line = line + '\n';
		codePreprocessed = codePreprocessed + line;
	}

	cout << codePreprocessed;
	MyReadFile.close();
	return codePreprocessed;
}

int token_table(string token){
	if(token.compare("ADD") == 0)
	{
		return ADD;
	}
	if (token.compare("SUB") == 0)
	{
		return SUB;
	}
	if (token.compare("MUL") == 0)
	{
		return MUL;
	}
	if (token.compare("DIV") == 0)
	{
		return DIV;
	}
	if (token.compare("jmp") == 0)
	{
		return jmp;
	}
	if (token.compare("JMPN") == 0)
	{
		return JMPN;
	}
	if (token.compare("JMPP") == 0)
	{
		return JMPP;
	}
	if (token.compare("JMPZ") == 0)
	{
		return JMPZ;
	}
	if (token.compare("COPY") == 0)
	{
		return COPY;
	}
	if (token.compare("LOAD") == 0)
	{
		return LOAD;
	}
	if (token.compare("STORE") == 0)
	{
		return STORE;
	}
	if (token.compare("INPUT") == 0)
	{
		return INPUT;
	}
	if (token.compare("OUTPUT") == 0)
	{
		return OUTPUT;
	}
	if (token.compare("STOP") == 0)
	{
		return STOP;
	}
	if (token.compare("CONST") == 0)
	{
		return CONST;
	}
	if (token.compare("SPACE") == 0)
	{
		return SPACE;
	}
	//opcode incorreto
	return -1;
}

void one_pass_algorithm(string codePreprocessed)
{
	string myText;
	int lineCount = 0;
	int posCount = 0;
	string token; 
	vector<int> code;
	int opcode, symbol, aux;
	vector<SymbolTableElements> symbolTable;
	bool opcodeFlag = false;
	bool dataSection = false;
	bool textSection = false;
	bool constFlag = false;
	bool newSymbol = false;
	bool rotFlag = false;
	char lastX = '!'; //any character different
	string symbolFound = "";

	istringstream iss(codePreprocessed);

//fazer uma passagem pra tirar tabulações e espaços


	while (getline (iss, myText)) // Read line by line till it reaches end of file
	{ 
		std::transform(myText.begin(), myText.end(), myText.begin(), ::toupper);
		lineCount++;
		cout << myText << endl;
    	if(myText.compare("SECTION TEXT") == 0)
		{
			cout << "entrei na text section" << '\n' << '\n';
			print_vector(code);
			print_ST(symbolTable);
			textSection = true;
			dataSection = false;
			getline (iss, myText);
			std::transform(myText.begin(), myText.end(), myText.begin(), ::toupper);
			lineCount++;
    	}
		if(myText.compare("SECTION DATA") == 0)
		{
			cout << "entrei na data section" << '\n' << '\n';
			print_vector(code);
			print_ST(symbolTable);
			cout  << endl;
			textSection = false;
			dataSection = true;
			getline (iss, myText);
			std::transform(myText.begin(), myText.end(), myText.begin(), ::toupper);
			lineCount++;
		}
		if(textSection)
		{
			myText = myText + "\n";
			token = "";
			lastX = '!';
			opcodeFlag = false;
        	for (auto x: myText)
			{
				if(lastX == ';')
				{
					break;
				}
        		if(x == ' ' && (lastX == ' ' || lastX == ':'))
				{
            		token = "";
          		}
				else if((x == ' ' || x == '\n') && opcodeFlag == false)
				{
            	//token
            	opcode = token_table(token);
            	switch (opcode)
				{
            		case ADD:
                		code.push_back(ADD);
                		break;
            		case SUB:
                		code.push_back(SUB);
                		break;
            		case MUL:
                		code.push_back(MUL);
                		break;
            		case DIV:
                		code.push_back(DIV);
                		break;
            		case jmp:
                		code.push_back(jmp);
                		break;
            		case JMPN:
                		code.push_back(JMPN);
                		break;
            		case JMPP:
                		code.push_back(JMPP);
                		break;
            		case JMPZ:
                		code.push_back(JMPZ);
                		break;
            		case COPY:
                		code.push_back(COPY);
                		break;
            		case LOAD:
                		code.push_back(LOAD);
                		break;
            		case STORE:
                		code.push_back(STORE);
                		break;
            		case INPUT:
                		code.push_back(INPUT);
                		break;
            		case OUTPUT:
                		code.push_back(OUTPUT);
                		break;
            		case STOP:
                		code.push_back(STOP);
                		break;
            		default:
                		cout << "erro no opcode na linha" << lineCount << endl;
                		cout << token << endl;
                		posCount--;
                		break;
            	}
            	cout << "achei opcode: " << token << endl;
            	token = "";
            	posCount++;
            	opcodeFlag = true;
        		}
				else if(x == ':')
				{
            		//rotulo
            		cout << "achei rotulo: " << token << endl;
            		auto search = find_if(symbolTable.begin(), symbolTable.end(), 
                    	[&token] (SymbolTableElements const& d) { 
                        	return d.symbol == token; 
                    	});
            		if (search != symbolTable.end())
					{
            			cout << "erro rotulo ja definido na linha: " << lineCount << endl;
            		} 
					else
					{
              			SymbolTableElements element = {token, posCount, true, -1};
              			symbolTable.push_back(element);
            		}
            		cout << token << endl;
            		token = "";
          		}
          		else if((x == ' ' || x == '\n' || x == ',') && opcodeFlag == true)
				{
            		//symbol
            		cout << "achei simbolo: " << token << endl;
            		//search for symbol in ST
            		auto search = find_if(symbolTable.begin(), symbolTable.end(), 
                    		[&token] (SymbolTableElements const& d) { 
                        		return d.symbol == token; 
                    	});
            		if (search != symbolTable.end())
					{
              			cout << "simbolo ja definido" << endl;
              			if(search->def) //nao vai mais acontecer
						{
                			cout << "tem posição" << endl;
                			code.push_back(search->value);
                			posCount++;
              			} 
						else
						{
                			cout << "nao tem posição" << endl;
                			int prevPos = search->list;
                			code.push_back(prevPos);
                			search->list = posCount;
                			posCount++;
              			}
            		}
					else
					{
              			cout << "simbolo ainda nao definido" << endl;
              			SymbolTableElements element = {token, -1, false, posCount};
              			symbolTable.push_back(element);
              			code.push_back(-1);
              			posCount++;
            		}
            		token = "";
            		if(opcode != COPY)
					{
            			opcodeFlag = false;
					}
				}
          		else
				{
            		token = token + x;
            		//cout << '\"' <<  token << '\"'<< endl;
          		}
				lastX = x;
          		//cout << "x atual \"" << x getline<< "\""<< endl;
        	}
        	//cout << lineCount << myText << '\n';      
			print_vector(code);
		}
    	if(dataSection)
		{
    		myText = myText + "\n";
    		token = "";
			SymbolTableElements element;
    		for (auto x: myText)
			{
        		if(x == ':')
				{
          			//simbolo
          			cout << "DATA achei simbolo: " << token << endl;
        			// auto search = find_if(symbolTable.begin(), symbolTable.end(), 
        			//              [&token] (SymbolTableElements const& d) { 
        			//                 return d.symbol == token; 
        			//              });
          			// if (search != symbolTable.end())
					// {
            		// 	cout << "simbolo ja definido" << endl;
            		// 	// FAZER ESSA PARTE DE COLOCAR NA TABELA O VALOR E IR PREENCHENDO OS VALORES
            		// 	newSymbol = false;
            		// 	symbolFound = search->symbol;
            		// 	//search->value = posCount;
            		// 	//search->def = true;

          			// }
					// else
            		//	cout << "simbolo nao definido" << endl;
            		element = {token, 0, false, -1};
					symbolFound = token;
            			//symbolTable.push_back(element);
            		//	newSymbol = true;
          			token = "";
        		} 
				else if(x == '\n' && constFlag)
				{
		        	//verificar se token é int
		        	cout << "Valor do const: " << token << endl;
					element.value = stoi(token);
		        	//code.push_back(stoi(token));
		        	constFlag = false;
		        	token = "";
        		}
				else if((x == ' '|| x == '\n') && token != ":" && token != " " )
				{
          			cout << "vendo tipo: \"" << token << "\"" << endl;
          			symbol = token_table(token);
          			switch (symbol)
					{
            			case CONST:
              				constFlag = true;
              				break;
            			case SPACE:
              				element.value = 0;
              				break;
          			}
          			token = "";
        		} 
				if(x == ' ')
				{
          			token = "";
        		}
         		else
				{
          			token = token + x;
        		}
      		}
			auto search = find_if(symbolTable.begin(), symbolTable.end(), 
        	 [&symbolFound] (SymbolTableElements const& d) { 
        	    return d.symbol == symbolFound; 
        	 });
          	if (search != symbolTable.end())
			{
				search->value = element.value;
			}
			else
			{
      			symbolTable.push_back(element);
			}
    	}
	}

	//Pass through symbol table
	cout << " Passar pela ST" << endl;
	print_ST(symbolTable);
	cout << symbolTable.size() << endl;
	for(int i = 0; i < symbolTable.size(); i++)
	{
		cout << " Passar pela ST" << endl;
		if(!symbolTable[i].def)
		{
			cout << symbolTable[i].symbol << endl;
			code.push_back(symbolTable[i].value);
			symbol = symbolTable[i].list;
			symbolTable[i].value = posCount;
			posCount++;
			symbolTable[i].def = true;
			while (symbol != -1){
        		aux = symbol;
        		symbol = code[aux];
        		code[aux] = symbolTable[i].value;
        	}
		}
	}
        		// auto search = find_if(symbolTable.begin(), symbolTable.end(), 
        		//                [&symbolFound] (SymbolTableElements const& d) { 
        		//                   return d.symbol == symbolFound; 
        		//                });
        		// symbol = search->list;
        		// //cout << "vou colocar o " << symbol << " no " << posCount << endl;
        		// while (symbol != -1)
				// {
          		// 	aux = symbol;
          		// 	symbol = code[aux];
          		// 	code[aux] = search->value;
        		// }

  	print_vector(code);
  	print_ST(symbolTable);
  	
}

int main(int argc, char *argv[]) 
{
	string codePreprocessed;
	//pensar em criar a tabela de instruções
	if(argc < 2)
	{
		cout << "Arquivo não repassado na linha de comando" << '\n';
		return 0;
	}
	codePreprocessed = preprocessing(argv[1]);
	one_pass_algorithm(codePreprocessed);
	return 0;
} 