#include "parser_1_big.h"

#include "parser_1_lines.h"
#include "utilities.h"

Parser1Big::Parser1Big()
{

}

Parser1Big::~Parser1Big()
{

}

void Parser1Big::Parse(Block data_in, AccountDetails* acc_details)
{
  std::cout << "Block Size = " << data_in.size() << std::endl;

  QStringList line_data;
  
}
