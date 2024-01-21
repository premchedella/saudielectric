#include "parser_4_small.h"

#include "parser_4_lines.h"
#include "utilities.h"

Parser4Small::Parser4Small()
{

}

Parser4Small::~Parser4Small()
{

}

void Parser4Small::Parse(Block data_in, AccountDetails* acc_details)
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
    acc_details->parsing_ = "Warning";
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
    Parser4Lines::Line2(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Subscription Number Line;";
  }
    
  //Line No. 3
  line_no++;
  // Site Number 
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif
  try
  {
    line_data = data_in.at(line_no);
    Parser4Lines::Line3(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Warning";
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
    acc_details->parsing_ = "Warning";
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
    Parser4Lines::Line7(line_data, acc_details);
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
    Parser4Lines::Line8(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Power Consumption;";
  }

  //Line No. 9
  line_no++;
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif
  try
  {
    line_data = data_in.at(line_no);
    Parser4Lines::Line9(line_data, acc_details);
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Duration and Power Cost Line;";
  }

  // Some times settlement is negative other fields changes
  // Handle this

  line_no = 11;
#if PRINT_FIELD_VALUE
  std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif
  try
  {
    line_data = data_in.at(line_no);
    Parser4Lines::Line12(line_data, acc_details);
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Settlement Line;";
  }

  // If the settlement is negative
  if (acc_details->settlement_.toFloat() >= float(0))
  {
  //Line No. 10
    line_no = 9;
  #if PRINT_FIELD_VALUE
    std::cout << "Parse Line " << line_no << ":: ";
  #endif
    try
    {
      line_data = data_in.at(line_no);
      Parser4Lines::Line10(line_data, acc_details);
    }
    catch (...)
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No VAT Line;";
    }

    line_no++;
    // Line No.11 
  #if PRINT_FIELD_VALUE
    std::cout << "Parse Line " << line_no + 1 << ":: ";
  #endif
    try
    {
      line_data = data_in.at(line_no);
      Parser4Lines::Line11Small(line_data, acc_details);
    }
    catch (...)
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Taxable Amount Line;";
    }  
  
    line_no++;
    //Line No. 12
  #if PRINT_FIELD_VALUE
    std::cout << "Parse Line " << line_no + 1 << ":: ";
  #endif
    try
    {
      line_data = data_in.at(line_no);
      Parser4Lines::Line12(line_data, acc_details);
    }
    catch (...)
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Settlement Line;";
    }

    line_no++;
    //Line No. 13
  #if PRINT_FIELD_VALUE
    std::cout << "Parse Line " << line_no + 1 << ":: ";
  #endif
    try
    {
      line_data = data_in.at(line_no);
      Parser4Lines::Line13(line_data, acc_details);
    }
    catch (...)
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Non Taxable Amount Line;";
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
    }
    catch (...)
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Required Amount Line;";
    }
  }
  else
  {
    //std::cout << "Settlement is negative.";
    acc_details->vat_15_ = QString::number(0);
    //Line No. 10
    line_no = 9;

    try
    {
      line_data = data_in.at(line_no);
      Parser4Lines::Line9Small(line_data, acc_details);
    }
    catch (...)
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Taxable amount Line;";
    }

    line_no++;
    try
    {
      line_data = data_in.at(line_no);
      Parser4Lines::Line10Small(line_data, acc_details);
    }
    catch (...)
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Non Taxable amount Line;";
    }

    // Settlement Line and already parsed.
    line_no++;

    //Required Amount Line
    line_no++;
    try
    {
      line_data = data_in.at(line_no);
      Parser4Lines::Line14(line_data, acc_details);
    }
    catch (...)
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Required Amount Line;";
    }
  }

  line_no = 17;
  bool is_multi_meters = false;
  bool is_last_line = false;
  if (line_no < data_in.size())
  {
#if PRINT_FIELD_VALUE
    std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif
    is_last_line = true;
    try
    {
      line_data = data_in.at(line_no);
      if (line_data.size() == 10)
      {
        Parser4Lines::ActivePower(line_data, acc_details);
      } else
      {
        is_multi_meters = true;
      }

    }
    catch (...)
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Active Power Line;";
    }
  }

  
  if (!is_multi_meters)
  {
    line_no = 19;

    if (line_no < data_in.size())
    {
        
    #if PRINT_FIELD_VALUE
        std::cout << "Parse Line " << line_no + 1 << ":: ";
    #endif      

      // Parse Total Meters Consumption Line
      try
      {
        line_data = data_in.at(line_no);
        Parser4Lines::Consumptions(line_data, acc_details);
      }
      catch (...)
      {
        acc_details->parsing_ = "Partial";
        acc_details->reason_ += "No Total Meters Consumption Line;";
      }
    }
  }

  if (is_last_line)
  {
    // Parse Total Consumption Line

    line_no = data_in.size() - 1;

#if PRINT_FIELD_VALUE
    std::cout << "Parse Line " << line_no + 1 << ":: ";
#endif

    try
    {
      line_data = data_in.at(line_no);
      Parser4Lines::LineLast(line_data, acc_details);
    }
    catch (...)
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Total Consumption Line;";
    }
  }
}
