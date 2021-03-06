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

struct SymbolTableElements
{
	string symbol;
	int value;
	bool def;
	vector<int> list;
	int line;
	bool isRot;
	int space;
};

struct InstructionTableElements
{
	int opcode;
	int words;
};

vector<InstructionTableElements> InstructionTable;

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
		cout << v[i].symbol << " " << v[i].value << " " << v[i].def << " " << v[i].list[0] << " " << v[i].line << " " << v[i].isRot << " " << v[i].space << endl;
	}
}

// END OF DEBUG FUNCTIONS

void build_instruction_table()
{
	InstructionTable.push_back({ADD, 2});
	InstructionTable.push_back({SUB, 2});
	InstructionTable.push_back({MUL, 2});
	InstructionTable.push_back({DIV, 2});
	InstructionTable.push_back({JMP, 2});
	InstructionTable.push_back({JMPN, 2});
	InstructionTable.push_back({JMPP, 2});
	InstructionTable.push_back({JMPZ, 2});
	InstructionTable.push_back({COPY, 3});
	InstructionTable.push_back({LOAD, 2});
	InstructionTable.push_back({STORE, 2});
	InstructionTable.push_back({INPUT, 2});
	InstructionTable.push_back({OUTPUT, 2});
	InstructionTable.push_back({STOP, 1});
}

void write_file(vector<int> code, vector<int> bitMap, char* bitMapFlag, char* fileName)
{
	ofstream ofile;
	string newFile;
	string name = string(fileName);
	size_t pos = name.find(".");
	newFile = name.substr(0, pos) + ".obj";
	ofile.open(newFile);
	ofile << "H: " << name.substr(0, pos) << endl;
	ofile << "H: " << code.size() << endl;
	ofile << "H: ";
	if(bitMapFlag[0] == '0')
	{
		for (int i = 0; i < bitMap.size(); i++)
		{
			ofile << bitMap[i];
		}
	} else
	{
		for (int i = 0; i < bitMap.size(); i++)
		{
			if(bitMap[i] == 1)
			{
				ofile << i << " ";
			}
		}
	}
	ofile << endl;
	ofile << "T: ";
	for (int i = 0; i < code.size(); i++)
	{
		ofile << code[i] << " ";
	}
	ofile.close();
}

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
			if(x == ';')
			{
				break;
			}
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
			if((x == ' ' || x == '\t') && lastX == ' ')
			{
				addChar = false;
			}
			if(x == ':' && lastX == ' ')
			{
				if(!line.empty())
				line.pop_back();
			}
			if(addChar)
			{
				line = line + x;
			}

			lastX = x;
		}
		if(lastX == ' ' || lastX == '\t')
		{
			if(!line.empty())
				line.pop_back();
		}
		//cout << line << "\"" << endl;
		line = line + '\n';
		codePreprocessed = codePreprocessed + line;
	}

	MyReadFile.close();
	return codePreprocessed;
}

bool valid_token(string token, int lineCount)
{
	bool tokenFlag = true;
	if((token[0] >= '0' && token[0] <= '9') )
	{
		tokenFlag = false;
	}
	std::transform(token.begin(), token.end(), token.begin(), ::toupper);
	for (int i = 0; i < token.size(); i++)
	{
		if((token[i] < 'A' || token[i] > 'Z') && (token[i] < '0' || token[i] > '9') && token[i] != '_')
		{
			tokenFlag = false;
		}
	}
	if(!tokenFlag)
	{
		cout << "LINHA: " << lineCount << " ERRO L??XICO" << endl;
	}
	return tokenFlag;
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
	if (token.compare("JMP") == 0)
	{
		return JMP;
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

vector<int> one_pass_algorithm(string codePreprocessed, char* bitMapFlag, char* fileName)
{
	string myText;
	int lineCount = 0;
	int posCount = 0;
	string token; 
	vector<int> code;
	vector<int> bitMap;
	int opcode = 1;
	int symbol, aux;
	vector<SymbolTableElements> symbolTable;
	int space;
	bool opcodeFlag = false;
	bool dataSection = false;
	bool textSection = false;
	bool constFlag = false;
	bool newSymbol = false;
	bool rotFlag = false;
	bool spaceFlag = false;
	char lastX = '!'; //any character different
	string symbolFound = "";
	int wordsCount = 0;
	int lastLine = 0;

	istringstream iss(codePreprocessed);

	//print_vector(code);
	while (getline (iss, myText)) // Read line by line till it reaches end of file
	{ 
		std::transform(myText.begin(), myText.end(), myText.begin(), ::toupper);
		lineCount++;
		//cout << myText << endl;
    	if(myText.compare("SECTION TEXT") == 0)
		{
			//print_ST(symbolTable);
			textSection = true;
			dataSection = false;
			getline (iss, myText);
			std::transform(myText.begin(), myText.end(), myText.begin(), ::toupper);
			lineCount++;
    	}
		if(myText.compare("SECTION DATA") == 0)
		{
			//print_vector(code);
			//print_ST(symbolTable);
			textSection = false;
			dataSection = true;
			getline (iss, myText);
			std::transform(myText.begin(), myText.end(), myText.begin(), ::toupper);
			lineCount++;
		}
		if(myText != "")
		{
			if(textSection)
			{
				myText = myText + "\n";
				token = "";
				lastX = '!';
				//opcodeFlag = false;
    	    	for (auto x: myText)
				{
					if(lastX == ';')
					{
						break;
					}
					if((x == ' ' ||  x == '\n') && opcodeFlag && !token.empty())
					{
						if(token_table(token) != -1 )
						{
							//???instru????es??? ???com??? ???a??? ???quantidade??? ???de??? ???operando??? ???errada
							cout << "LINHA: " << lastLine << " ERRO SINT??TICO" << endl;
							wordsCount = 0;
							opcodeFlag = false;
						}
					}
    	    		if(x == ' ' && (lastX == ' ' || lastX == ':'))
					{
    	        		token = "";
    	      		}
					else if((x == ' ' || x == '\n') && opcodeFlag == false && !token.empty())
					{
    	        		//token
						if(!valid_token(token, lineCount))
						{
							int wordsCount = 0;
							bool opcodeFlag = false;
							break;
						}
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
    	        			case JMP:
    	            			code.push_back(JMP);
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
								//???instru????es??? ???inv??lidas
    	            			cout << "LINHA: " << lineCount << " ERRO SINTATICO" << endl;
    	            			//cout << "\"" << token << "\"" << endl;
    	            			posCount--;
    	            			break;
    	        		}
    	        		//cout << "achei opcode: " << token << endl;
    	        		token = "";
    	        		posCount++;
						wordsCount++;
    	        		opcodeFlag = true;
						bitMap.push_back(0);
    	    		}
					else if(x == ':')
					{
    	        		//rotulo
						if(!valid_token(token, lineCount))
						{
							wordsCount = 0;
							opcodeFlag = false;
							break;
						}
    	        		//cout << "achei rotulo: " << token << endl;
						if(rotFlag)
						{
							//dois??? ???r??tulos??? ???na??? ???mesma??? ???linha
							cout << "LINHA: " << lineCount << " ERRO SINT??TICO" << endl;
						}
    	        		auto search = find_if(symbolTable.begin(), symbolTable.end(), 
    	                	[&token] (SymbolTableElements const& d) { 
    	                    	return d.symbol == token; 
    	                	});
    	        		if (search != symbolTable.end())
						{
							if(search->def == true)
							{
							//???declara????es??? ???de??? ???r??tulos??? ???repetidos
    	        			cout << "LINHA: " << lineCount << " ERRO SEMANTICO" << endl;
							}
							else
							{
								search->value = posCount;
							// 	search->def = true;
								search->isRot = true;
								for(int i = 0; i < search->list.size(); i++)
								{
									code[search->list[i]] = search->value;
								}
								search->list[0] = -1;
								search->def = true;
							}
    	        		} 
						else
						{
    	          			SymbolTableElements element = {token, posCount, true, {-1}, lineCount, true, 0};
    	          			symbolTable.push_back(element);
    	        		}
    	        		//cout << token << endl;
    	        		token = "";
						rotFlag = true;
    	      		}
    	      		else if((x == ' ' || x == '\n' || x == ',' || x == '+') && opcodeFlag == true && spaceFlag == false)
					{	
    	        		//symbol
						if(!valid_token(token, lineCount))
						{
							int wordsCount = 0;
							bool opcodeFlag = false;
							break;
						}
    	        		//cout << "achei simbolo:" << token << endl;
						if(x == '+')
						{
							spaceFlag = true;
						}
    	        		//search for symbol in ST
    	        		auto search = find_if(symbolTable.begin(), symbolTable.end(), 
    	                		[&token] (SymbolTableElements const& d) { 
    	                    		return d.symbol == token; 
    	                	});
    	        		if (search != symbolTable.end())
						{
    	          			//cout << "simbolo ja definido" << endl;
    	          			if(search->def && search->isRot == true)
							{
    	            			//cout << "tem posi????o" << endl;
    	            			code.push_back(search->value);
    	            			posCount++;
								bitMap.push_back(1);
    	          			} 
							else
							{
								search->list.insert(search->list.begin(), posCount);
								if(!spaceFlag)
								{
									code.push_back(0);
									posCount++;
									bitMap.push_back(1);
								}
								//print_ST(symbolTable);
    	          			}

    	        		}
						else if(!spaceFlag)
						{
    	          			//cout << "simbolo ainda nao definido" << endl;
    	          			SymbolTableElements element = {token, -1, false, {posCount}, lineCount, false, 0};
    	          			symbolTable.push_back(element);
    	          			code.push_back(0);
    	          			posCount++;
							bitMap.push_back(1);
    	        		}
    	        		token = "";
						wordsCount++;

					}
					else if((x == ' ' || x == '\n' || x == ',') && opcodeFlag == true && spaceFlag == true)
					{
						//cout << token << endl;
						code.push_back(stoi(token));
						posCount++;
						bitMap.push_back(1);
						spaceFlag = false;
					}
    	      		else
					{
    	        		token = token + x;
    	        		//cout << '\"' <<  token << '\"'<< endl;
    	      		}
					lastX = x;
    	      		//cout << "x atual \"" << x getline<< "\""<< endl;
    	    	}
				if((wordsCount == InstructionTable[opcode - 1].words) && (opcodeFlag))
				{
					//cout << "Instru????o completa" << endl;
					opcodeFlag = false;
					rotFlag = false;
					wordsCount = 0;     
				}
				//print_vector(code);
				lastLine = lineCount;

			}
    		if(dataSection)
			{
    			myText = myText + "\n";
    			token = "";
				lastX = '!';
				SymbolTableElements element;
    			for (auto x: myText)
				{
					if(lastX == ';')
					{
						break;
					}
    	    		if(x == ':')
					{
    	      			//simbolo
						//cout << token << endl;
						if(token_table(token) != -1 )
						{
							//r??tulo inv??lido
							cout << "LINHA: " << lineCount << " ERRO SINT??TICO" << endl;
						}
						if(!valid_token(token, lineCount))
						{
							int wordsCount = 0;
							bool opcodeFlag = false;
							break;
						}
    	        		element = {token, 0, true, {-1}, lineCount};
						symbolFound = token;
    	      			token = "";
    	    		} 
					else if((x == '\n' || x == ' ') && constFlag)
					{
			        	//verificar se token ?? int
			        	//cout << "Valor do const: " << token << endl;
						//cout << token << endl;
						try{
							    element.value = stoi(token);
							}
							catch(std::exception& e){
							    cout << "LINHA: " << lineCount << " ERRO SINT??TICO" << endl;
							}
			        	code.push_back(stoi(token));
						posCount++;
						bitMap.push_back(0);
			        	constFlag = false;
			        	token = "";
    	    		}
					else if((x == ' '|| x == '\n') && token != ":" && token != " " && spaceFlag == false && !token.empty())
					{
    	      			//cout << "vendo tipo: \"" << token << "\"" << endl;
    	      			symbol = token_table(token);
    	      			switch (symbol)
						{
    	        			case CONST:
    	          				constFlag = true;
								element.value = posCount;
    	          				break;
    	        			case SPACE:
    	          				element.value = posCount;
								spaceFlag = true;
								code.push_back(0);
								posCount++;
								bitMap.push_back(0);
    	          				break;
							default:
								//erro no space/const
								cout << "LINHA: " << lineCount << " ERRO SINT??TICO" << endl;
    	      			}
    	      			token = "";
    	    		} 
					else if((x == ' '|| x == '\n') && token != ":" && token != " " && token != "" && spaceFlag == true)
					{
						cout << "vendo space: \"" << token << "\"" << endl;
						try{
							    element.space = stoi(token);
							}
							catch(std::exception& e){
							    cout << "LINHA: " << lineCount << " ERRO SINT??TICO" << endl;
							}
						for(int i = 0; i < stoi(token) - 1; i++)
						{
							code.push_back(0);
							posCount++;
							bitMap.push_back(0);
						}
						token = "";
						spaceFlag = false;
					}
					if(x == ' ' || x == ':') 
					{
    	      			token = "";
    	    		}
    	     		else
					{
    	      			token = token + x;
    	    		}
					lastX = x;
    	  		}
				auto search = find_if(symbolTable.begin(), symbolTable.end(), 
    	    	 [&symbolFound] (SymbolTableElements const& d) { 
    	    	    return d.symbol == symbolFound; 
    	    	 });
    	      	if (search != symbolTable.end())
				{
					//cout << "achei" << endl;
					search->value = element.value;
					search->def = true;
					search->space = element.space;
				}
				else
				{
					//cout << "n achei:" << symbolFound << "\"" << endl;
    	  			symbolTable.push_back(element);
				}
				spaceFlag = false;
				//print_ST(symbolTable);
    		}
			//print_vector(code);
			lastLine = lineCount;
		}
	}

	for(int i = 0; i < symbolTable.size(); i++)
	{
		//cout << " Passar pela ST" << endl;
		if(symbolTable[i].def)
		{
			if(symbolTable[i].isRot == false)
			{
				//cout << symbolTable[i].symbol << endl;
				//aux = posCount;
				// for (int j = 0; j < symbolTable[i].space + 1; j++)
				// {
				// 	code.push_back(symbolTable[i].value);
				// 	posCount++;
				// 	bitMap.push_back(0);
				// }
				//symbolTable[i].value = aux;
				for (int j = 0; j < symbolTable[i].list.size(); j++)
				{
					if(symbolTable[i].list[j] != -1)
					{
						//cout << symbolTable[i].list[j] << endl;
						code[symbolTable[i].list[j]] = symbolTable[i].value;
						//aux = code[symbolTable[i].list[j]];
						//code[symbolTable[i].list[j]] = symbolTable[i].value + aux;
						//cout << symbolTable[i].list[j] << endl;
					}
				}

			}	
		} else
		{
			//declara????es??? ???de??? ???r??tulos??? ???ausentes
			cout << "LINHA: " << symbolTable[i].line << " ERRO SEM??NTICO" << endl;
		}
	}
  	//print_vector(bitMap);
  	//print_ST(symbolTable);
	write_file(code, bitMap, bitMapFlag, fileName);
	return code;
  	
}

int main(int argc, char *argv[]) 
{
	string codePreprocessed;
	vector<int> code;

	build_instruction_table();
	if(argc < 2)
	{
		cout << "Arquivo n??o repassado na linha de comando" << '\n';
		return 0;
	}
	codePreprocessed = preprocessing(argv[3]);
	code = one_pass_algorithm(codePreprocessed, argv[2], argv[3]);
	

	return 0;
} 