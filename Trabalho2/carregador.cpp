#include <iostream>
#include <fstream> 
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

// DEBUG FUNCTIONS

void print_vector(vector<int> v)
{
	for(int i=0; i<v.size(); ++i)
	{
		cout << v[i] << ' ';
	}
	cout << endl << endl;
}

// END OF DEBUG FUNCTIONS


bool is_number(const std::string &s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

void get_info(int argc, char *argv[], vector<string> *filesObj, vector<int> *chunk)
{
	for(int i = 1; i < argc; i++)
	{
		if(!is_number(argv[i]))
		{
			filesObj->push_back(argv[i]);
		} else
		{
			chunk->push_back(stoi(argv[i]));
		}
	}
}

vector<int> program_sizes(vector<string> filesObj)
{
	string myText;
	string fileSize;
	vector<int> programSizes;

	for(int i = 0; i < filesObj.size(); i++)
	{
		ifstream MyReadFile(filesObj[i]);
		getline (MyReadFile, myText);
		getline (MyReadFile, myText);
		fileSize = myText.substr(3, myText.size());
		programSizes.push_back(stoi(fileSize));
		MyReadFile.close();
	}
	return programSizes;
}

vector<int> fit_chunk(vector<int> chunk, vector<int> programSizes)
{
	int fileSize, groupChunk, countChunk;
	bool alocationFlag;
	bool outputFlag = true;
	vector<int> chunkFit;
	vector<int> chunkAdresses;

	for(int i = 0; i < programSizes.size(); i++) 
	{
		fileSize = programSizes[i];
		alocationFlag = false;
		for(int j = 1; j < chunk[0] + 1; j++) //Tries to fit in onlu one chunk
		{
			if(fileSize <= chunk[j])
			{
				cout << "PROG" << i + 1 << " utilizando 1 CHUNK. Endereço inicial: " << chunk[j+chunk[0]] << endl;
				chunk[j] -= fileSize;
				alocationFlag = true;
				chunkFit.push_back(j);
				chunkFit.push_back(-1);
				break;
			}
		}
		if(!alocationFlag)
		{
			groupChunk = 0;
			countChunk = 0;
			chunkAdresses.clear();
			for(int j = 1; j < chunk[0] + 1; j++) //Tries to group chunks to fit file 
			{
				if(chunk[j] != 0)
				{
					groupChunk += chunk[j];
					countChunk++;
					chunkFit.push_back(j);
					chunkAdresses.push_back(chunk[j+chunk[0]]);
					if(fileSize <= groupChunk)
					{
						cout << "PROG" << i + 1 << " utilizando " << countChunk << " CHUNKS. Endereços iniciais: ";
						for(int w = 0; w < chunkAdresses.size(); w++)
						{
							cout << chunkAdresses[w] << " ";
						}
						cout << endl;
						chunk[j] = groupChunk - fileSize;
						chunkFit.push_back(-1);
						for(int w = j-1; w > 0; w--) //clean chunk spaces used
						{
							chunk[w] = 0;
						}
						alocationFlag = true;
						break;
					}
				}
			}
		}
		if(!alocationFlag)
		{
			while(chunkFit.back() != -1)
			{
				chunkFit.pop_back();
			}
			cout << "PROG" << i + 1 << " NAO FOI POSSIVEL ALOCAR" << endl;
			outputFlag = false;
		}
	}
	return chunkFit;
}

void loader(vector<string> filesObj, vector<int> chunk)
{
	vector<int> programSizes;
	vector<int> chunkFit;
	string myText, bitMap, code, opcode, line;
	int instruction, data, dataAdress;
	int space, adress; 
	int count, lineCount;
	int countChunkFit = 0;
	char x;
	bool dataFlag, copyFlag;


	programSizes = program_sizes(filesObj);
	print_vector(programSizes);
	chunkFit = fit_chunk(chunk, programSizes);
	print_vector(chunkFit);

	for(int i = 0; i < filesObj.size(); i++)
	{
		ifstream MyReadFile(filesObj[i]);
		getline (MyReadFile, myText);
		getline (MyReadFile, myText);
		getline (MyReadFile, bitMap);
		getline (MyReadFile, code);

		ofstream ofile;
		string newFile;
		string name = string(filesObj[i]);
		size_t pos = name.find(".");
		newFile = name.substr(0, pos) + ".saida";
		ofile.open(newFile);

		count = 0;
		opcode = "";
		line = "";
		dataFlag = false;
		copyFlag = false;
		space = chunk[chunkFit[countChunkFit]];
		adress = chunk[chunk[0] + chunkFit[countChunkFit]];
		lineCount = adress;

		code = code.substr(3, code.size());
		bitMap = bitMap.substr(3, bitMap.size());
		cout << code << "\"" << endl;
		for (auto x: code)
		{

			if(space == 0)
			{
				countChunkFit++;
				space = chunk[chunkFit[countChunkFit]];
				adress = chunk[chunk[0] + chunkFit[countChunkFit]];
				lineCount = adress;
			}

			if(x != ' ')
			{
				opcode = opcode + x;
			}
			else 
			{
				//cout << adress << " " << opcode << " bit " << bitMap[count] << endl;
				if(bitMap[count] == '0' && !dataFlag)
				{
					instruction = stoi(opcode);
					ofile << lineCount << "\t" << opcode << "\t";
					if(instruction == 14)
					{
						ofile << endl;
						dataFlag = true;
					}
					if(instruction == 9)
					{
						copyFlag = true;
					}
					lineCount++;
				}
				else if(!dataFlag)
				{
					dataAdress = adress + stoi(opcode);
					//line = line + " " + to_string(dataAdress);
					ofile << dataAdress;
					if(copyFlag)
					{
						ofile << "\t";
						copyFlag = false;
					}
					else
					{
						ofile << endl;
					}
					//cout << "File: " << line << endl;
					line = "";
					lineCount++;
				}
				else
				{
					//data = stoi(opcode);
					line = adress + " " + opcode;
					ofile << lineCount << "\t" << opcode << endl;
					//cout << lineCount << " " << data << endl;
					line = "";
					lineCount++;
				}
				opcode = "";
				count++;
				space--;
			}
			
		}
		countChunkFit += 2;

		MyReadFile.close();
	}
}

int main(int argc, char *argv[]) 
{
	string codePreprocessed;
	vector<string> filesObj;
	vector<int> chunk;

	get_info(argc, argv, &filesObj, &chunk);
	// cout<< filesObj[0] << filesObj[1] << endl;
	// print_vector(chunk);

	loader(filesObj, chunk);

	return 0;
} 