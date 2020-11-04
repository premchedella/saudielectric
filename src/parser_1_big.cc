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
  
  // Line Number is 1
  int line_no = 0;
  std::cout << "Parse Line " << line_no + 1 << ":: ";
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line1(line_data, acc_details);
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 1;";
  }

  // Line Number is 2
  line_no++;
  std::cout << "Parse Line " << line_no + 1 << ":: ";
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line2(line_data, acc_details);
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 1;";
  }
  
}
