#include "type_12_parser.h"
#include "utilities.h"

#include "common_types.h"
#include "parse_line.h"

Type12Parser::Type12Parser()
{

}

Type12Parser::~Type12Parser()
{

}

void Type12Parser::Parse(Block data_in, AccountDetails* acc_details)
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

void Type12Parser::VatParse(Block data_in, AccountDetails* acc_details)
{
  QStringList line_data;    
  
  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2
  unsigned int line_no = 2;
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
    ParseLine::Line4Big(line_data, acc_details);
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
    ParseLine::Line4(line_data, acc_details);
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
    ParseLine::Line5(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 6;";    
  }

  // Line Other Fees
  line_no++;

  try
  {
    line_data = data_in.at(line_no);
    bool is_other_fees = Utilities::IsOtherFees(line_data);
    if (is_other_fees)
    {
      ParseLine::OtherFees(line_data, acc_details);
      line_no++;
    }
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Other Fees Line;";
  }

  //Line -- Settlement
  
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line6(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Settlement Line;";    
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
    acc_details->reason_ += "No VAT Line;";    
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
    acc_details->reason_ += "No Total Line;";    
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
  }

  //Line 35
  line_no = data_in.size() - 2;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::LineLast2(line_data, acc_details);
    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Last Line 2;";    
  }  
  
}

void Type12Parser::ParVatParse(Block data_in, AccountDetails* acc_details)
{
  QStringList line_data;
  QString token;
  

  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2
  unsigned int line_no = 2;
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
    ParseLine::Line4Big(line_data, acc_details);
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
    ParseLine::Line4(line_data, acc_details);    
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
    ParseLine::Line5(line_data, acc_details);    
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
    ParseLine::Line6(line_data, acc_details);
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
    acc_details->vat_ = "0";
    //VAT, postion 4 or 5
    if ((line_data.size() == 6) || (line_data.size() == 5))
    {
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

  //Line 9  
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line8(line_data, acc_details);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Total Amount Line 15;";    
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
  }

  //Line 15
  line_no = line_no + 4;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::Line15ParVat(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 15;";    
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
    acc_details->reason_ += "No Line 16;";    
  }
  
  //Line 35
  line_no = data_in.size() - 2;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::LineLast2(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Last Line 2;";    
  }     
}

void Type12Parser::NonVatParse(Block data_in, AccountDetails* acc_details)
{
  QStringList line_data;    

  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2
  unsigned int line_no = 2;
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
    ParseLine::Line4Big(line_data, acc_details);   
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
    ParseLine::Line4(line_data, acc_details);    
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
    ParseLine::Line5(line_data, acc_details);    
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
    ParseLine::Line6(line_data, acc_details);    
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
  }  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Line 7;";    
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
    acc_details->reason_ += "No Line 10;";    
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
  }

  //Line 35
  line_no = data_in.size() - 2;
  try
  {
    line_data = data_in.at(line_no);
    ParseLine::LineLast2(line_data, acc_details);    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Last Line 2;";    
  }      
}

