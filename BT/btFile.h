#ifndef BTFILE_H
#define BTFILE_H

#include "btCommon.h"

namespace BT
{

BT::composite *loadFile( const char *file) ;
bool saveFile(std::string file, composite* task);
void writeComposite(std::ofstream &myfile, composite* parent, size_t tabs);
node* newTask(node* Parent, std::string line);
node* decodeLine(std::string line);
std::string codeLine(node* task);

}

#endif // BTFILE_H
