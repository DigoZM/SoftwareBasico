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
  int opcode;
  vector<SymbolTableElements> symbolTable;


  while (getline (MyReadFile, myText)) { // Read line by line till it reaches end of file
    std::transform(myText.begin(), myText.end(), myText.begin(), ::tolower);

    lineCount++;

    if(myText.compare("section text") == 0){
      cout << "entrei na text section" << '\n';
      getline (MyReadFile, myText);
      std::transform(myText.begin(), myText.end(), myText.begin(), ::tolower);
      lineCount++;

      while (myText.compare("section data") != 0 && MyReadFile.eof() != true)
      {

        token = "";
        for (auto x: myText){

          if(x == ' '){
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
              case -1:
                cout << "erro no opcode na linha" << lineCount << endl;
                cout << token << endl;
              default:
                break;
            }
            token = "";
            posCount++;
          }
          if(x == ':'){
            //rotulo
            auto search = find_if(symbolTable.begin(), symbolTable.end(), 
                       [&token] (SymbolTableElements const& d) { 
                          return d.symbol == token; 
                       });
            if (search != symbolTable.end()){
              cout << "erro rotulo ja definido" << endl;
            } else {
              SymbolTableElements element = {token, posCount, true, -1};
              symbolTable.push_back(element);
            }
            posCount++;
            cout << token << endl;
            token = "";
          }
          else {
            token = token + x;
            cout << '\"' <<  token << '\"'<< endl;
          }
        }
        
        //cout << lineCount << myText << '\n';
        getline (MyReadFile, myText);
        std::transform(myText.begin(), myText.end(), myText.begin(), ::tolower);
        lineCount++;

      }
      
    }

  }
  print_vector(code);
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