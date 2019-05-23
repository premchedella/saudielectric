#include "type_1_parser.h"

#include "utilities.h"
#include "common_types.h"
#include "parse_line.h"

Type1Parser::Type1Parser()
{

}

Type1Parser::~Type1Parser()
{

}

void Type1Parser::Parse(Block data_in, AccountDetails* acc_details)
{  
  Utilities::VatTypes vat_type = Utilities::GetVatType();

  if (vat_type == Utilities::VatTypes::WITH)
  {
    VatParse(data_in, acc_details);
  } else if (vat_type == Utilities::VatTypes::PARTIAL)
  {
    ParVatParse(data_in, acc_details);
  } else if (vat_type == Utilities::VatTypes::WITH_OUT)
  {
    NonVatParse(data_in, acc_details);
  } 
}

void Type1Parser::VatParse(Block data_in, AccountDetails* acc_details)
{
  Utilities::InputFileTypes file_type = Utilities::GetFileType();
  if (file_type == Utilities::InputFileTypes::KAU2_MAIN)
  {
    VatParseSmall(data_in, acc_details);
  } else
  {
    VatParseLarge(data_in, acc_details);
  }
}

void Type1Parser::ParVatParse(Block data_in, AccountDetails* acc_details)
{
  Utilities::InputFileTypes file_type = Utilities::GetFileType();
  if (file_type == Utilities::InputFileTypes::KAU2_MAIN)
  {
    ParVatParseSmall(data_in, acc_details);
  } else
  {
    ParVatParseLarge(data_in, acc_details);
  }
}

void Type1Parser::NonVatParse(Block data_in, AccountDetails* acc_details)
{
  Utilities::InputFileTypes file_type = Utilities::GetFileType();
  if (file_type == Utilities::InputFileTypes::KAU2_MAIN)
  {
    NonVatParseSmall(data_in, acc_details);    
  } else
  {
    NonVatParseLarge(data_in, acc_details);
  }
}

void Type1Parser::VatParseSmall(Block data_in, AccountDetails* acc_details)
{
  QStringList line_data;  
  int line_no = 2;
  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2
    
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line2(line_data, acc_details);    
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 2;";
    std::cout << "Line 2 is not available." << std::endl;
  }

  //Line No.3
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line3(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 3;";
    std::cout << "Line 3 is not available." << std::endl;
  }

  //Line 4
  line_no++;
  try 
  {
    line_data = data_in.at(line_no);
    ParseLine::Line4(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 4;";
    std::cout << "Line 4 is not available." << std::endl;
  }

  //Line 5
  line_no++;
  try 
  {
    line_data = data_in.at(line_no);
    ParseLine::Line5(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 5;";
    std::cout << "Line 5 is not available." << std::endl;
  }

  //Line 6
  line_no++;
  try 
  {
    line_data = data_in.at(line_no);
    /* Some of the files contains extra line which is not intended.
     Remove that line.  Moved this to xpdf_parse.cc file.*/

    /*QString start = QStringLiteral(START_BLOCK_WORD);
    if (start == line_data.at(0))
    {
      line_no++;
      line_data = data_in.at(line_no);
    }*/
    ParseLine::Line6(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 6;";
    std::cout << "Line 6 is not available." << std::endl;
  }

  //Line 7
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line7(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 7;";
    std::cout << "Line 7 is not available." << std::endl;
  }

  //Line 8 
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line8(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 8;";
    std::cout << "Line 8 is not available." << std::endl;
  } 
 
  acc_details->block_length_ = data_in.size();
}

void Type1Parser::VatParseLarge(Block data_in, AccountDetails* acc_details)
{
  QStringList line_data;    
  
  int line_no = 2;
  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2

  try 
  {
    line_data = data_in.at(line_no);
    ParseLine::Line2(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 2;";
    std::cout << "Line 2 is not available." << std::endl;
  }

  //Line No.3
  line_no++;
  try
  {    
    line_data = data_in.at(line_no);
    ParseLine::Line3(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 3;";
    std::cout << "Line 3 is not available." << std::endl;
  }

  //Line 4
  line_no++;
  try
  {
    line_data = data_in.at(line_no);        
    ParseLine::Line4Big(line_data, acc_details);
    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 4;";
    std::cout << "Line 4 is not available." << std::endl;
  }

  //Line 5
  line_no++;
  try 
  {
    line_data = data_in.at(line_no);
    ParseLine::Line4(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 5;";
    std::cout << "Line 5 is not available." << std::endl;
  }

  //Line 6
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line5(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 6;";
    std::cout << "Line 6 is not available." << std::endl;
  }

  //Line 7
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line6(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 7;";
    std::cout << "Line 7 is not available." << std::endl;
  }

  //Line 8
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line7(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 8;";
    std::cout << "Line 8 is not available." << std::endl;
  }

  //Line 9
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line8(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 9;";
    std::cout << "Line 9 is not available." << std::endl;
  }

  //Line 11
  line_no = line_no + 2;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line11(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 11;";
    std::cout << "Line 11 is not available." << std::endl;
  }

  //Line 15
  line_no = line_no + 4;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line15(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 15;";
    std::cout << "Line 15 is not available." << std::endl;
  }

  // Line
  line_no = data_in.size() - 2;
  try 
  {
    line_data = data_in.at(line_no);
    ParseLine::LineLast2(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Last Line 2;";
    std::cout << "Last 2nd line 8 is not available." << std::endl;
  }    
  
  acc_details->block_length_ = data_in.size();
}

void Type1Parser::ParVatParseSmall(Block data_in, AccountDetails* acc_details)
{
  QStringList line_data;
  
  int line_no = 2;
  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2

  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line2(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 2;";
    std::cout << "Line 2 is not available." << std::endl;
  }

  //Line No.3
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line3(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 3;";
    std::cout << "Line 3 is not available." << std::endl;
  }

  //Line 4
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line4(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 4;";
    std::cout << "Line 4 is not available." << std::endl;
  }

  //Line 5
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line5(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 5;";
    std::cout << "Line 5 is not available." << std::endl;
  }

  //Line 6
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line6(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 6;";
    std::cout << "Line 6 is not available." << std::endl;
  }

  //Line 7
  line_no++;
  try
  {
    line_data = data_in.at(line_no);  
    acc_details->vat_ = "0";
    if ((line_data.size() == 6) || (line_data.size() == 5))
    {      
      //VAT, postion 4 or 5
      if (line_data.size() == 6)
      {
        QString token = line_data.at(5);
        acc_details->vat_ = Utilities::ConvertEnglish(token);
        line_no++;
      } else if (line_data.size() == 5)
      {
        QString token = line_data.at(4);
        acc_details->vat_ = Utilities::ConvertEnglish(token);
        line_no++;
      } 
    }
  } catch (...)
  {
      
  }

  //Line 8   
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line8(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line Total Amount;";
    std::cout << "Total Amount Line is not available." << std::endl;
  }   
  
  acc_details->block_length_ = data_in.size();
}

void Type1Parser::ParVatParseLarge(Block data_in, AccountDetails* acc_details)
{
  QStringList line_data;

  int line_no = 2;
  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2

  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line2(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 2;";
    std::cout << "Line 2 is not available." << std::endl;
  }
  //Line No.3
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line3(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 3;";
    std::cout << "Line 3 is not available." << std::endl;
  }

  //Line 4
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line4Big(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 4;";
    std::cout << "Line 4 is not available." << std::endl;
  }

  //Line 5
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line4(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 5;";
    std::cout << "Line 5 is not available." << std::endl;
  }

  //Line 6
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line5(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 6;";
    std::cout << "Line 6 is not available." << std::endl;
  }

  //Line 7
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line6(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 7;";
    std::cout << "Line 7 is not available." << std::endl;
  }

  //Line 7
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    acc_details->vat_ = "0";
    if ((line_data.size() == 6) || (line_data.size() == 5))
    {
      //VAT, postion 4 or 5
      if (line_data.size() == 6)
      {
        QString token = line_data.at(5);
        acc_details->vat_ = Utilities::ConvertEnglish(token);
        line_no++;
      } else if (line_data.size() == 5)
      {
        QString token = line_data.at(4);
        acc_details->vat_ = Utilities::ConvertEnglish(token);
        line_no++;
      }    
    }
  } catch (...)
  {
   
  }

  //Line 8  
  try 
  {
    line_data = data_in.at(line_no);
    ParseLine::Line8(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line Total Amount;";
    std::cout << "Total Amount Line is not available." << std::endl;
  }

  //Line 10
  line_no = line_no + 2;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line11(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 11;";
    std::cout << "Line 11 is not available." << std::endl;
  }

  //Line 14
  line_no = line_no + 4;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line15ParVat(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 11;";
    std::cout << "Line 14 is not available." << std::endl;
  }

  //New Current Reading, Position 6
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line16ParVat(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 11;";
    std::cout << "Line 14 is not available." << std::endl;
  }

  // Line
  line_no = data_in.size() - 2;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::LineLast2(line_data, acc_details);   
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Last Line 2;";
    std::cout << "Last Line 2 is not available." << std::endl;
  }
    
  acc_details->block_length_ = data_in.size();
}

void Type1Parser::NonVatParseSmall(Block data_in, AccountDetails* acc_details)
{   
  QStringList line_data;
  
  int line_no = 2;
  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line2(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 2;";
    std::cout << "Line 2 is not available." << std::endl;
  }

  //Line No.3
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line3(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 3;";
    std::cout << "Line 3 is not available." << std::endl;
  }

  //Line 4
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line4(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 4;";
    std::cout << "Line 4 is not available." << std::endl;
  }

  //Line 5
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line5(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 5;";
    std::cout << "Line 5 is not available." << std::endl;
  }

  //Line 6
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line6(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 6;";
    std::cout << "Line 6 is not available." << std::endl;
  }

  //Line 7 
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line8(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 7;";
    std::cout << "Line 7 is not available." << std::endl;
  }

  acc_details->block_length_ = data_in.size();
}

void Type1Parser::NonVatParseLarge(Block data_in, AccountDetails* acc_details)
{
  QStringList line_data;  
  int line_no = 2;

  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line2(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 2;";
    std::cout << "Line 2 is not available." << std::endl;
  }

  //Line No.3
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line3(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 3;";
    std::cout << "Line 3 is not available." << std::endl;
  }

  //Line 4
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line4Big(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 4;";
    std::cout << "Line 4 is not available." << std::endl;
  }

  //Line 5
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line4(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 5;";
    std::cout << "Line 5 is not available." << std::endl;
  }
  
  //Line 6
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line5(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 6;";
    std::cout << "Line 6 is not available." << std::endl;
  }

  //Line 7
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line6(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 7;";
    std::cout << "Line 7 is not available." << std::endl;
  }

  //Line 8
  line_no++;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line8(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 8;";
    std::cout << "Line 8 is not available." << std::endl;
  }

  //Line 10
  line_no = line_no + 2;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line11(line_data, acc_details);   
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 8;";
    std::cout << "Line 8 is not available." << std::endl;
  }

  //Line 14
  line_no = line_no + 4;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line15(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 14;";
    std::cout << "Line 14 is not available." << std::endl;
  }

  // Line
  line_no = data_in.size() - 2;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::LineLast2(line_data, acc_details);
    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Last Line 2;";
    std::cout << "Last Line 2 is not available." << std::endl;
  }
  
  acc_details->block_length_ = data_in.size();
}
