#include <iostream>
#include <fstream> 
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

#define add 1
#define sub 2
#define mul 3
#define div 4
#define jmp 5
#define jmpn 6
#define jmpp 7
#define jmpz 8
#define copy 9
#define load 10
#define store 11
#define input 12
#define output 13
#define stop 14
#define constData 15
#define space 16 

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

void print_vector(vector<int> v){
  for(int i=0; i<v.size(); ++i){
    cout << v[i] << ' ';
  }
  cout << endl;
}

void print_ST(vector<SymbolTableElements> v){
  cout << "Symbol Table" << endl;
  for(int i=0; i<v.size(); ++i){
    cout << v[i].symbol << " " << v[i].value << " " << v[i].def << " " << v[i].list << endl;
  }
}

// END OF DEBUG FUNCTIONS

int token_table(string token){
  if(token.compare("add") == 0){
    return add;
  }
  if (token.compare("sub") == 0)
  {
    return sub;
  }
  if (token.compare("mul") == 0)
  {
    return mul;
  }
  if (token.compare("div") == 0)
  {
    return div;
  }
  if (token.compare("jmp") == 0)
  {
    return jmp;
  }
  if (token.compare("jmpn") == 0)
  {
    return jmpn;
  }
  if (token.compare("jmpp") == 0)
  {
    return jmpp;
  }
  if (token.compare("jmpz") == 0)
  {
    return jmpz;
  }
  if (token.compare("copy") == 0)
  {
    return copy;
  }
  if (token.compare("load") == 0)
  {
    return load;
  }
  if (token.compare("store") == 0)
  {
    return store;
  }
  if (token.compare("input") == 0)
  {
    return input;
  }
  if (token.compare("output") == 0)
  {
    return output;
  }
  if (token.compare("stop") == 0)
  {
    return stop;
  }
  if (token.compare("const") == 0){
    return constData;
  }
  if (token.compare("space") == 0){
    return space;
  }
  //opcode incorreto
  return -1;
}


void one_pass_algorithm(char* fileName){
  string myText;
  ifstream MyReadFile(fileName);
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

//fazer uma passagem pra tirar tabulações e espaços


  while (getline (MyReadFile, myText)) { // Read line by line till it reaches end of file
    std::transform(myText.begin(), myText.end(), myText.begin(), ::tolower);

    lineCount++;
    cout << myText << endl;
    if(myText.compare("section text") == 0){
      cout << "entrei na text section" << '\n' << '\n';
      print_vector(code);
      print_ST(symbolTable);
      textSection = true;
      dataSection = false;
      getline (MyReadFile, myText);
      std::transform(myText.begin(), myText.end(), myText.begin(), ::tolower);
      lineCount++;
    }
    if(myText.compare("section data") == 0){
      cout << "entrei na data section" << '\n' << '\n';
      print_vector(code);
      print_ST(symbolTable);
      cout  << endl;
      textSection = false;
      dataSection = true;
      getline (MyReadFile, myText);
      std::transform(myText.begin(), myText.end(), myText.begin(), ::tolower);
      lineCount++;
    }

    if(textSection){
        myText = myText + "\n";
        token = "";
        lastX = '!';
				opcodeFlag = false;
        for (auto x: myText){

					if(lastX == ';'){
						break;
					}

          if(x == ' ' && (lastX == ' ' || lastX == ':')){
            token = "";
          }
          else if((x == ' ' || x == '\n') && opcodeFlag == false){
            //token
            opcode = token_table(token);
            switch (opcode){
              case add:
                code.push_back(add);
                break;
              case sub:
                code.push_back(sub);
                break;
              case mul:
                code.push_back(mul);
                break;
              case div:
                code.push_back(div);
                break;
              case jmp:
                code.push_back(jmp);
                break;
              case jmpn:
                code.push_back(jmpn);
                break;
              case jmpp:
                code.push_back(jmpp);
                break;
              case jmpz:
                code.push_back(jmpz);
                break;
              case copy:
                code.push_back(copy);
                break;
              case load:
                code.push_back(load);
                break;
              case store:
                code.push_back(store);
                break;
              case input:
                code.push_back(input);
                break;
              case output:
                code.push_back(output);
                break;
              case stop:
                code.push_back(stop);
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
          else if(x == ':'){
            //rotulo
            cout << "achei rotulo: " << token << endl;
            auto search = find_if(symbolTable.begin(), symbolTable.end(), 
                       [&token] (SymbolTableElements const& d) { 
                          return d.symbol == token; 
                       });
            if (search != symbolTable.end()){
              cout << "erro rotulo ja definido na linha: " << lineCount << endl;
            } else {
              SymbolTableElements element = {token, posCount, true, -1};
              symbolTable.push_back(element);
            }
            cout << token << endl;
            token = "";
          }
          else if((x == ' ' || x == '\n' || x == ',') && opcodeFlag == true){
            cout << "achei simbolo: " << token << endl;
            //symbol
            //search for symbol in ST
            auto search = find_if(symbolTable.begin(), symbolTable.end(), 
                       [&token] (SymbolTableElements const& d) { 
                          return d.symbol == token; 
                       });
            if (search != symbolTable.end()){
              cout << "simbolo ja definido" << endl;
              if(search->def){
                cout << "tem posição" << endl;
                code.push_back(search->value);
                posCount++;
              } else {
                cout << "nao tem posição" << endl;
                int prevPos = search->list;
                code.push_back(prevPos);
                search->list = posCount;
                posCount++;
              }
            } else {
              cout << "simbolo ainda nao definido" << endl;
              SymbolTableElements element = {token, -1, false, posCount};
              symbolTable.push_back(element);
              code.push_back(-1);
              posCount++;
            }
            token = "";
            if(opcode != copy){
            	opcodeFlag = false;
						}

          }
          else {
            token = token + x;
            //cout << '\"' <<  token << '\"'<< endl;
          }
          lastX = x;
          //cout << "x atual \"" << x << "\""<< endl;
        }
        
        //cout << lineCount << myText << '\n';      
    }
    
    if(dataSection){
      myText = myText + "\n";
      token = "";
      for (auto x: myText){
        if(x == ':'){
          //simbolo
          cout << "DATA achei simbolo: " << token << endl;
          auto search = find_if(symbolTable.begin(), symbolTable.end(), 
                       [&token] (SymbolTableElements const& d) { 
                          return d.symbol == token; 
                       });
          if (search != symbolTable.end()){
            cout << "simbolo ja definido" << endl;
            // FAZER ESSA PARTE DE COLOCAR NA TABELA O VALOR E IR PREENCHENDO OS VALORES
            newSymbol = false;
            symbolFound = search->symbol;
            search->value = posCount;
            search->def = true;

          } else {
            cout << "simbolo nao definido" << endl;
            SymbolTableElements element = {token, posCount, true, -1};
            symbolTable.push_back(element);
            newSymbol = true;
          }
          token = "";
        } else if(x == '\n' && constFlag){
          //verificar se token é int
          cout << "Valor do const: " << token << endl;
          code.push_back(stoi(token));
          posCount++;
          constFlag = false;
          token = "";
        } else if((x == ' '|| x == '\n') && token != ":" && token != " " ){
          cout << "vendo tipo: \"" << token << "\"" << endl;
          symbol = token_table(token);
          switch (symbol){
            case constData:
              constFlag = true;
              break;
            case space:
              code.push_back(00);
              posCount++;
              break;
          }
          token = "";
        } if(x == ' '){
          token = "";
        }
         else {
          token = token + x;
        }
      }
      if(!newSymbol){
        //print_ST(symbolTable);
        auto search = find_if(symbolTable.begin(), symbolTable.end(), 
                       [&symbolFound] (SymbolTableElements const& d) { 
                          return d.symbol == symbolFound; 
                       });
        symbol = search->list;
        //cout << "vou colocar o " << symbol << " no " << posCount << endl;
        while (symbol != -1){
          aux = symbol;
          symbol = code[aux];
          code[aux] = search->value;
        }
        newSymbol = false;
      }
    }

  }
  print_vector(code);
  print_ST(symbolTable);
  MyReadFile.close();
}

int main(int argc, char *argv[]) {

  if(argc < 2){
    cout << "Arquivo não repassado na linha de comando" << '\n';
    return 0;
  }

  one_pass_algorithm(argv[1]);
    
  return 0;
} 