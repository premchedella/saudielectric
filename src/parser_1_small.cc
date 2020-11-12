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
#if PRINT_FIELD_VALUE
  std::cout << "Block Size = " << data_in.size() << std::endl;
#endif

  QStringList line_data;
  bool is_15_vat_extra = false;

  // Line Number is 1
  int line_no = 0;
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line1(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Account Number Line;";
  }

  //Line No. 2
  line_no++;
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif

  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line2(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Subscription Number Line;";
  }

  //Line No. 3
  line_no++;
  // Site Number is not required to generate data
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line3(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Site Number Line;";
  }

  //Line No. 4
  line_no++;
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line4(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Invoice Number Line;";
  }

  // Line 5 and 6 contains some table header
  //Line No. 7
  line_no = 6;
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line7(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Meter Number Line;";
  }
  
  //Line No. 8
  line_no++;
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line8(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Readings Data Line;";
  }

  //Line No. 9
  line_no++;
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line9(line_data, acc_details);
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Duration and Power Cost Line;";
  }

  //Line No. 10
  line_no++;
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line10(line_data, acc_details);
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No 5% VAT Line;";
  }

  line_no++;
  // Line No.11 Extra VAT 15%
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif
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
    acc_details->reason_ += "No 15% VAT Line;";
  }
  

  if (is_15_vat_extra)
  {
    line_no++;
#if PRINT_FIELD_VALUE
    std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif
    try
    {
      line_data = data_in.at(line_no);
      Parser1Lines::Line11(line_data, acc_details);
    }
    catch (...)
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Settlement Line;";
    }    
  }
  else
  {
    try
    {
      line_data = data_in.at(line_no);
      Parser1Lines::Line11_1(line_data, acc_details); 
    }
    catch (...)
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Settlement Line;";
    }
  }
  
  line_no++;
  //Line No. 12
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line12(line_data, acc_details);
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Taxable Amount Line;";
  }

  line_no++;
  //Line No. 13
  std::cout << "Parse Line " << line_no + 1 << ":: ";
  try
  {
    line_data = data_in.at(line_no);
    Parser1Lines::Line13(line_data, acc_details);
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Non Taxable Amount Line;";
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
    acc_details->reason_ += "No Total Cost Line;";
  }
}
