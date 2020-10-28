#include "parser_1_small.h"

#include "parser_1_lines.h"
#include "utilities.h"

Parser1Small::Parser1Small()
{

}

Parser1Small::~Parser1Small()
{

}

void Parser1Small::Parse(Block data_in, AccountDetails* acc_details)
{
  std::cout << "Block Size = " << data_in.size() << std::endl;

  QStringList line_data;

  // Line Number is 1
  int line_no = 0;
  std::cout << "Parse Line 1:: ";
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line1(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 1;";
  }

  //Line No. 2
  line_no++;
  std::cout << "Parse Line 2:: ";
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line2(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 2;";
  }

  //Line No. 3
  line_no++;
  std::cout << "Parse Line 3:: ";
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line3(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 3;";
  }

  //Line No. 4
  line_no++;
  std::cout << "Parse Line 4:: ";
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line4(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 4;";
  }

  // Line 5 and 6 contains some table header
  //Line No. 7
  line_no = 6;
  std::cout << "Parse Line 7:: ";
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line7(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 7;";
  }
  
  //Line No. 8
  line_no++;
  std::cout << "Parse Line 8:: ";
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line8(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 8;";
  }

  //Line No. 9
  line_no++;
  std::cout << "Parse Line 9:: ";
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line9(line_data, acc_details);
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 9;";
  }

  //Line No. 10
  line_no++;
  std::cout << "Parse Line 10:: ";
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line10(line_data, acc_details);
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 10;";
  }

  if ((data_in.size() == 21) || (data_in.size() == 23))
  {  
    line_no++;
    //Line No. 10 Extra
    std::cout << "Parse Line 15% VAT Extra:: ";
    try
    {
      line_data = data_in.at(line_no);
      Parser1Lines::Line10_1(line_data, acc_details);
    }
    catch (...)
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Line 15% VAT Extra;";
    }
  }

  line_no++;
  //Line No. 11
  std::cout << "Parse Line 11:: ";  
  try
  {
    line_data = data_in.at(line_no);
    if (data_in.size() == 20)
    {
      Parser1Lines::Line11_1(line_data, acc_details);
    }
    else
    {
      Parser1Lines::Line11(line_data, acc_details);
    }
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 11;";
  }

  line_no++;
  //Line No. 12
  std::cout << "Parse Line 12:: ";
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line12(line_data, acc_details);
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 12;";
  }

  line_no++;
  //Line No. 13
  std::cout << "Parse Line 13:: ";
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line13(line_data, acc_details);
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 12;";
  }

  line_no++;
  //Line No. 14
  std::cout << "Parse Line 14:: ";
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
}
