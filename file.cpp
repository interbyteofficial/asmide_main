#include <iostream>
#include <fstream>
#include "file.h"

using namespace std;

File::File()
{

}

void File::write()
{
    ofstream file;
    file.open(name,ios::binary);
    file << buff;
    file.close();
}

void File::open()
{
    ifstream file(name);
    string str((istreambuf_iterator<char>(file)),
    istreambuf_iterator<char>());
}

void File::setbuff(char* buff)
{
    this->buff = buff;
}

void File::setname(char* name){
    this->name = name;
}
