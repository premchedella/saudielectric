#include "type_5_parser.h"
#include "utilities.h"

#include "common_types.h"
#include "parse_line.h"

Type5Parser::Type5Parser()
{

}

Type5Parser::~Type5Parser()
{

}

void Type5Parser::Parse(Block data_in, AccountDetails* acc_details)
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

void Type5Parser::VatParse(Block data_in, AccountDetails* acc_details)
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
  }    
}

void Type5Parser::ParVatParse(Block data_in, AccountDetails* acc_details)
{
  QStringList line_data;
  QString token;
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
        token = line_data.at(5);
        acc_details->vat_ = Utilities::ConvertEnglish(token);
        line_no++;
      } else if (line_data.size() == 5)
      {
        token = line_data.at(4);
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
  }      
}

void Type5Parser::NonVatParse(Block data_in, AccountDetails* acc_details)
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
  }  
}

