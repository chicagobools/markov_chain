#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <utility>
#include <ctime>
#include <cstdlib>
#include <cstdio>
 
using namespace std;
typedef pair<string, string> Tuple;

class Table{
  friend class Chain;
public:
  void insertWord(Tuple key, string tail);
  void populateTable();
  string getRandElm(Tuple first);
  Tuple getRandKey();
  void readFile(string file);
  Table();
private:
  int randNum(int lo, int hi){return rand() % hi + lo;}
  Tuple makeTuple(string a, string b);
  vector<string> text;
  map<Tuple , vector<string> > data;
  map<Tuple , vector<string> >::iterator it;  
};
 
class Chain{
public:
  Chain();
  void setChainSize(int size);
  void generateText();
  void toString();
  void toString(string fileName);
private:
  Table t;
  map<string, vector<string> >::iterator it;  
  int CHAIN_SIZE;
  vector<string> wordChain;
};
 
void act(std::string filename){
  Chain sentence;
  sentence.generateText();

  sentence.toString(filename);
}

//////// MAIN ////////
 
int main(){
  srand(time(NULL));

  //filename goes here
  act(filename);
}
 
/////// END MAIN ///////
 
Chain::Chain(){
  CHAIN_SIZE = 50;
  t.readFile("harry_potter.txt");
  t.populateTable();
}

void Table::readFile(string file){
  ifstream fin;
  fin.open(file.c_str());
  string word;
 
  if(fin.fail()){
    exit(0);
  }
 
  while(fin >> word){
    text.push_back(word);
  }
  fin.close();
}
 
void Table::populateTable(){
  for(int i = 0; i < text.size() - 3; i++){
    insertWord(makeTuple(text[i], text[i+1]), text[i+2]);
  }
}

void Table::insertWord(Tuple key, string tail){
  if(data.count(key) > 0){
    data[key].push_back(tail);
    return;
  }
 
  vector<string> tempVec;
  tempVec.push_back(tail);
  pair<Tuple, vector<string> > tempPair;
  tempPair = make_pair(key, tempVec);
  data.insert(tempPair);
}

Tuple Table::makeTuple(string a, string b){
  Tuple temp;
  temp = make_pair (a, b);
  return temp;
}

void Chain::generateText(){
  Tuple start = t.getRandKey();
  Tuple previous;

  wordChain.push_back(start.first);
  wordChain.push_back(start.second);
 
  for(int i = 0; i < CHAIN_SIZE; i++){
    previous = start;
    string follow = t.getRandElm(start);
    Tuple state = t.makeTuple(previous.second, follow);
    wordChain.push_back(follow);
    start = state;
  }
}

void Chain::toString(string fileName){
  ofstream fout;
  fout.open(fileName.c_str());

  fout << wordChain[0];
  for(int i = 1; i < wordChain.size(); i++){
    fout << " " << wordChain[i];
  }
  fout << ".\n";
  fout.close();
}

void Chain::toString(){
  cout << wordChain[0];
  for(int i = 1; i < wordChain.size(); i++){
    cout << " " << wordChain[i];
  }
  cout << ".\n";
}
 
Tuple Table::getRandKey(){
  int size = data.size();
  int randNum = rand() % size;
  it = data.begin();
  advance (it, randNum);
  return it->first;
}
 
Table::Table(){
  it = data.begin();
}
  
string Table::getRandElm(Tuple first){
  int rand = randNum(0, data[first].size());
  return data[first][rand];
}
