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
  bool is_15_vat_extra = false;
  
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

  //Line No. 3
  line_no++;
  std::cout << "Parse Line " << line_no + 1 << ":: ";
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line3(line_data, acc_details);
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 3;";
  }
  

  //Line No. 4
  line_no++;
  std::cout << "Parse Line " << line_no + 1 << ":: ";
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line4(line_data, acc_details);
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 4;";
  }

  // Line 5 and 6 contains some table header
  //Line No. 7
  line_no = 6;
  std::cout << "Parse Line " << line_no + 1 << ":: ";
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line7(line_data, acc_details);
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 7;";
  }

  //Line No. 8
  line_no++;
  std::cout << "Parse Line " << line_no + 1 << ":: ";
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line8(line_data, acc_details);
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 8;";
  }

  //Line No. 9
  line_no++;
  std::cout << "Parse Line " << line_no + 1 << ":: ";
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line9Big(line_data, acc_details);
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 9;";
  }

  //Line No. 10
  line_no++;
  std::cout << "Parse Line " << line_no + 1 << ":: ";
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line9(line_data, acc_details);
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 10;";
  }

  //Line No. 11
  line_no++;
  std::cout << "Parse Line " << line_no + 1 << ":: ";
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line10(line_data, acc_details);
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 11;";
  }

  line_no++;
  // Line No.12 Extra VAT 15%
  std::cout << "Parse Line " << line_no + 1 << ":: ";
  try
  {
    line_data = data_in.at(line_no);
    if (Parser1Lines::Is15VatExtra(line_data))
    {
      is_15_vat_extra = true;
    }

    if (is_15_vat_extra)
    {
      Parser1Lines::Line10_1(line_data, acc_details);
    }
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 12;";
  }

  try
  {
    if (is_15_vat_extra)
    {
      line_no++;
      std::cout << "Parse Line " << line_no + 1 << ":: ";
      line_data = data_in.at(line_no);
      Parser1Lines::Line11(line_data, acc_details);
    } else
    {
      line_data = data_in.at(line_no);
      Parser1Lines::Line11Big(line_data, acc_details);
    }
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 12;";
  }

  line_no++;
  //Line No. 13
  std::cout << "Parse Line " << line_no + 1 << ":: ";
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line12Big(line_data, acc_details);
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 13;";
  }

  line_no++;
  //Line No. 14
  std::cout << "Parse Line " << line_no + 1 << ":: ";
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line13Big(line_data, acc_details);
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 12;";
  }

  line_no++;
  //Line No. 14
  std::cout << "Parse Line " << line_no + 1 << ":: ";
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line14(line_data, acc_details);
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 12;";
  }

  line_no = 16;
  std::cout << "Parse Line " << line_no + 1 << ":: ";

  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line16(line_data, acc_details);
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 16;";
  }

  line_no = 20;
  std::cout << "Parse Line " << line_no + 1 << ":: ";

  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line20(line_data, acc_details);
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 20;";
  }

}
