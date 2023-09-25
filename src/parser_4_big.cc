#include "parser_4_big.h"

#include "parser_4_lines.h"
#include "utilities.h"

Parser4Big::Parser4Big()
{

}

Parser4Big::~Parser4Big()
{

}

void Parser4Big::Parse(Block data_in, AccountDetails* acc_details)
{
#if PRINT_FIELD_VALUE
  std::cout << "Block Size = " << data_in.size() << std::endl;
#endif

  QStringList line_data;  
  
  // Line Number is 1
  int line_no = 0;
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif
  try
  {
    line_data = data_in.at(line_no);
    Parser4Lines::Line1(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Account Number Line;";
  }

  // Line Number is 2
  line_no++;
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif
  try
  {
    line_data = data_in.at(line_no);
    Parser4Lines::Line2(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Subscription Number Line;";
  }

  //Line No. 3
  line_no++;
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif
  try
  {
    line_data = data_in.at(line_no);
    Parser4Lines::Line3(line_data, acc_details);
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
    Parser4Lines::Line4(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Invoice Date Line;";
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
    Parser4Lines::Line7(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Reading To Line;";
  }

  //Line No. 8
  line_no++;
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif
  try
  {
    line_data = data_in.at(line_no);
    Parser4Lines::Line8(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Current Reading Line;";
  }

  //Line No. 9
  line_no++;
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif
  try
  {
    line_data = data_in.at(line_no);
    Parser4Lines::Line9Big(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Power Consumtion Line;";
  }

  //Line No. 10
  line_no++;
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif
  try
  {
    line_data = data_in.at(line_no);
    Parser4Lines::Line9(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Duration Cost Line;";
  }

  //Line No. 11
  line_no++;
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif
  try
  {
    line_data = data_in.at(line_no);
    Parser4Lines::Line10(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No VAT 15% Line;";
  }

  line_no++;
  // Line No.12 
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif

  try
  {
    line_data = data_in.at(line_no);
    Parser4Lines::Line11Big(line_data, acc_details);
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Taxable Amount Line;";
  }

      
  line_no++;
  //Line No. 13
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif
  
  try
  {
    line_data = data_in.at(line_no);
    Parser4Lines::Line12Big(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Non Taxable Amount Line;";
  }  
  
  line_no++;
  //Line No. 13
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif
  try
  {
    line_data = data_in.at(line_no);
    Parser4Lines::Line11(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Settlement Line;";
  }  
  
  line_no++;
  //Line No. 14
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif
  try
  {    
    line_data = data_in.at(line_no);
    Parser4Lines::Line14(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Total Cost Line;";
  }

  line_no = 16;  
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif

  try
  {
    line_data = data_in.at(line_no);
    Parser4Lines::Line16(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Total Reactive Power Consumption Line;";
  }

  line_no = 20;    
   
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif
  try
  {
    line_data = data_in.at(line_no);
    Parser4Lines::Line20(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Previous Reading Line;";
  }

  line_no = data_in.size() - 2;
  if (Utilities::IsExtraWord())
    line_no = data_in.size() - 3;
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif

  try
  {
    line_data = data_in.at(line_no);
    Parser4Lines::LineLast(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Last to previous Line;";
  }
}
