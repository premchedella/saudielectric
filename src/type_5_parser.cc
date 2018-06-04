#include "type_5_parser.h"
#include "utilities.h"

#include "common_types.h"

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
  QString token;
  bool is_parse = true;

  int line_no = 2;
  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2
  line_data = data_in.at(line_no);

  if (line_data.size() > 8)
  {
    // Electrometer Number, Position = 0
    token = line_data.at(0);
    acc_details->electrometer_num_ = Utilities::ConvertEnglish(token);;

    //Type, Position = 1
    token = line_data.at(1);
    int position = token.indexOf("_");
    token = token.mid(position + 1, token.size());
    acc_details->type_ = Utilities::ConvertEnglish(token);;

    //SubType, Position = 1
    token = line_data.at(1);
    position = token.indexOf("_");
    token = token.mid(0, position);
    acc_details->sub_type_ = Utilities::ToType(token);

    //Meter Reading To, Position 2, data is Date and written in string
    token = line_data.at(2);
    token = Utilities::ConvertEnglish(token);
    acc_details->reading_to_ = Utilities::ToDate(token).trimmed();

    //Meter Reading From, Position 3, data is Date and written in string
    token = line_data.at(3);
    token = Utilities::ConvertEnglish(token);
    acc_details->reading_from_ = Utilities::ToDate(token).trimmed();

    //Factor, Position 4
    token = line_data.at(4);
    acc_details->power_factor_ = Utilities::ConvertEnglish(token);;

    //Capacity, Position 5
    token = line_data.at(5);
    acc_details->capacity_ = Utilities::ConvertEnglish(token);

    //Account Number, Position 8
    token = line_data.at(8);
    acc_details->account_num_ = Utilities::ConvertEnglish(token);;

    // HACK: For some cases, the account number is reserved including data
    if (acc_details->account_num_ == "")
    {
      token = line_data.at(6);
      acc_details->account_num_ = Utilities::ConvertEnglish(token);;
    }
  } else
  {
    is_parse = false;
  }

  //Line No.3
  line_no++;
  line_data = data_in.at(line_no);

  if (line_data.size() > 7)
  {
    //Number Days, postion 0 
    token = line_data.at(0);
    acc_details->reading_days_ = Utilities::ConvertEnglish(token);;

    //Current Reading, Position 1 
    token = line_data.at(1);
    acc_details->curr_reading_ = Utilities::ConvertEnglish(token);;

    //Previous Reading, Position 2 
    token = line_data.at(2);
    acc_details->prev_reading_ = Utilities::ConvertEnglish(token);;

    //Power Consumption, Position 5
    token = line_data.at(5);
    acc_details->power_consumption_ = Utilities::ConvertEnglish(token);;

    //Power Consumption Cost, postion 6
    token = line_data.at(6);
    acc_details->power_consumption_cost_ = Utilities::ConvertEnglish(token);;

    //Subscription Number, Postion 7
    token = line_data.at(7);
    acc_details->subscription_num_ = Utilities::ConvertEnglish(token);;
  } else
  {
    is_parse = false;
  }

  //Line 4
  line_no++;
  line_data = data_in.at(line_no);

  if (line_data.size() > 5)
  {
    //Invoice Date, Position 0, data is Date and written in string
    token = line_data.at(0);
    token = Utilities::ConvertEnglish(token);
    acc_details->invoice_date_ = Utilities::ToDate(token);

    //Electrometer Fee, Postion 5
    token = line_data.at(5);
    acc_details->electrometer_fee_ = Utilities::ConvertEnglish(token);;
  } else
  {
    is_parse = false;
  }
  //Line 5
  line_no++;
  line_data = data_in.at(line_no);

  if (line_data.size() > 5)
  {
    //Inovice Number, Position 0
    token = line_data.at(0);
    acc_details->invoice_num_ = Utilities::ConvertEnglish(token);;

    //Total Power Consumption Cost, position 5
    token = line_data.at(5);
    acc_details->total_power_cons_cost_ = Utilities::ConvertEnglish(token);;
  } else
  {
    is_parse = false;
  }

  //Line 6
  line_no++;
  line_data = data_in.at(line_no);

  if (line_data.size() > 1)
  {
    //Settlement, postion 1
    token = line_data.at(1);
    acc_details->settlement_ = Utilities::ConvertEnglish(token);
  } else
  {
    is_parse = false;
  }
  //Line 7
  line_no++;
  line_data = data_in.at(line_no);
  if (line_data.size() > 4)
  {
    //VAT, postion 4 or 5
    if (line_data.size() == 6)
    {
      token = line_data.at(5);
    } else
    {
      token = line_data.at(4);
    }
    acc_details->vat_ = Utilities::ConvertEnglish(token);
  } else
  {
    is_parse = false;
  }

  //Line 8 
  line_no++;
  line_data = data_in.at(line_no);

  if (line_data.size() > 2)
  {
    //Total Cost, postion 2
    token = line_data.at(2);
    acc_details->total_cost_ = Utilities::ConvertEnglish(token);
  } else
  {
    is_parse = false;
  }

  acc_details->parsing_ = "Completed";
  if (!is_parse)
  {
    acc_details->parsing_ = "Partial";
  }
  acc_details->block_length_ = data_in.size();  
}

void Type5Parser::ParVatParse(Block data_in, AccountDetails* acc_details)
{
  QStringList line_data;
  QString token;
  bool is_parse = true;

  int line_no = 2;
  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2
  line_data = data_in.at(line_no);

  if (line_data.size() > 8)
  {
    // Electrometer Number, Position = 0
    token = line_data.at(0);
    acc_details->electrometer_num_ = Utilities::ConvertEnglish(token);

    //Type, Position = 1
    token = line_data.at(1);
    int position = token.indexOf("_");
    token = token.mid(position + 1, token.size());
    acc_details->type_ = Utilities::ConvertEnglish(token);

    //SubType, Position = 1
    token = line_data.at(1);
    position = token.indexOf("_");
    token = token.mid(0, position);
    acc_details->sub_type_ = Utilities::ToType(token);

    //Meter Reading To, Position 2, data is Date and written in string
    token = line_data.at(2);
    token = Utilities::ConvertEnglish(token);
    acc_details->reading_to_ = Utilities::ToDate(token, '.').trimmed();

    //Meter Reading From, Position 3, data is Date and written in string
    token = line_data.at(3);
    token = Utilities::ConvertEnglish(token);
    acc_details->reading_from_ = Utilities::ToDate(token, '.').trimmed();

    //Factor, Position 4
    token = line_data.at(4);
    token = Utilities::ConvertEnglish(token);
    acc_details->power_factor_ = token;

    //Capacity, Position 5
    token = line_data.at(5);
    acc_details->capacity_ = Utilities::ConvertEnglish(token);

    //Account Number, Position 8
    token = line_data.at(8);
    acc_details->account_num_ = Utilities::ConvertEnglish(token);

    // HACK: For some cases, the account number is reserved including data
    if (acc_details->account_num_ == "")
    {
      token = line_data.at(6);
      acc_details->account_num_ = Utilities::ConvertEnglish(token);
    }
  } else
  {
    is_parse = false;
  }

  //Line No.3
  line_no++;
  line_data = data_in.at(line_no);

  if (line_data.size() > 7)
  {
    //Number Days, postion 0 
    token = line_data.at(0);
    acc_details->reading_days_ = Utilities::ConvertEnglish(token);

    //Current Reading, Position 1 
    token = line_data.at(1);
    acc_details->curr_reading_ = Utilities::ConvertEnglish(token);

    //Previous Reading, Position 2 
    token = line_data.at(2);
    acc_details->prev_reading_ = Utilities::ConvertEnglish(token);

    //Power Consumption, Position 5
    token = line_data.at(5);
    acc_details->power_consumption_ = Utilities::ConvertEnglish(token);

    //Power Consumption Cost, postion 6
    token = line_data.at(6);
    acc_details->power_consumption_cost_ = Utilities::ConvertEnglish(token);

    //Subscription Number, Postion 7
    token = line_data.at(7);
    acc_details->subscription_num_ = Utilities::ConvertEnglish(token);
  } else
  {
    is_parse = false;
  }

  //Line 4
  line_no++;
  line_data = data_in.at(line_no);

  if (line_data.size() > 5)
  {
    //Invoice Date, Position 0, data is Date and written in string
    token = line_data.at(0);
    token = Utilities::ConvertEnglish(token);
    acc_details->invoice_date_ = Utilities::ToDate(token, '.');

    //Electrometer Fee, Postion 5
    token = line_data.at(5);
    acc_details->electrometer_fee_ = Utilities::ConvertEnglish(token);
  } else
  {
    is_parse = false;
  }

  //Line 5
  line_no++;
  line_data = data_in.at(line_no);

  if (line_data.size() > 5)
  {
    //Inovice Number, Position 0
    token = line_data.at(0);
    acc_details->invoice_num_ = Utilities::ConvertEnglish(token);

    //Total Power Consumption Cost, position 5
    token = line_data.at(5);
    acc_details->total_power_cons_cost_ = Utilities::ConvertEnglish(token);
  } else
  {
    is_parse = false;
  }

  //Line 6
  line_no++;
  line_data = data_in.at(line_no);

  if (line_data.size() > 1)
  {
    //Settlement, postion 1
    token = line_data.at(1);
    acc_details->settlement_ = Utilities::ConvertEnglish(token);
  } else
  {
    is_parse = false;
  }

  //Line 7
  line_no++;
  line_data = data_in.at(line_no);
  
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
    } else
    {
      is_parse = false;
    }   
  }
  
  //Line 8   
  line_data = data_in.at(line_no);

  if (line_data.size() > 2)
  {
    //Total Cost, postion 2
    token = line_data.at(2);
    acc_details->total_cost_ = Utilities::ConvertEnglish(token);
  } else
  {
    is_parse = false;
  }

  acc_details->parsing_ = "Completed";
  if (!is_parse)
  {
    acc_details->parsing_ = "Partial";
  }
  acc_details->block_length_ = data_in.size();
  
}

void Type5Parser::NonVatParse(Block data_in, AccountDetails* acc_details)
{
  bool is_parse = true;

  QStringList line_data;
  QString token;

  int line_no = 2;
  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2
  line_data = data_in.at(line_no);

  if (line_data.size() > 8)
  {
    // Electrometer Number, Position = 0
    token = line_data.at(0);
    acc_details->electrometer_num_ = Utilities::ConvertEnglish(token);

    //Type, Position = 1
    token = line_data.at(1);
    int position = token.indexOf("_");
    token = token.mid(position + 1, token.size());
    acc_details->type_ = Utilities::ConvertEnglish(token);

    //SubType, Position = 1
    token = line_data.at(1);
    position = token.indexOf("_");
    token = token.mid(0, position);
    acc_details->sub_type_ = Utilities::ToType(token);

    //Meter Reading To, Position 2, data is Date and written in string
    token = line_data.at(2);
    token = Utilities::ConvertEnglish(token);
    acc_details->reading_to_ = Utilities::ToGregorian(
        Utilities::ToDate(token).trimmed());

    //Meter Reading From, Position 3, data is Date and written in string
    token = line_data.at(3);
    token = Utilities::ConvertEnglish(token);
    acc_details->reading_from_ = Utilities::ToGregorian(
        Utilities::ToDate (token).trimmed());

    //Factor, Position 4
    token = line_data.at(4);
    acc_details->power_factor_ = Utilities::ConvertEnglish(token);

    //Capacity, Position 5
    token = line_data.at(5);
    acc_details->capacity_ = Utilities::ConvertEnglish(token);

    //Account Number, Position 8
    token = line_data.at(8);
    acc_details->account_num_ = Utilities::ConvertEnglish(token);

    // HACK: For some cases, the account number is reserved including data
    if (acc_details->account_num_ == "")
    {
      token = line_data.at(6);
      acc_details->account_num_ = Utilities::ConvertEnglish(token);
    }
  } else
  {
    is_parse = false;
  }

  //Line No.3
  line_no++;
  line_data = data_in.at(line_no);

  if (line_data.size() > 7)
  {
    //Number Days, postion 0 
    token = line_data.at(0);
    acc_details->reading_days_ = Utilities::ConvertEnglish(token);

    //Current Reading, Position 1 
    token = line_data.at(1);
    acc_details->curr_reading_ = Utilities::ConvertEnglish(token);

    //Previous Reading, Position 2 
    token = line_data.at(2);
    acc_details->prev_reading_ = Utilities::ConvertEnglish(token);

    //Power Consumption, Position 5
    token = line_data.at(5);
    acc_details->power_consumption_ = Utilities::ConvertEnglish(token);

    //Power Consumption Cost, postion 6
    token = line_data.at(6);
    acc_details->power_consumption_cost_ = Utilities::ConvertEnglish(token);

    //Subscription Number, Postion 7
    token = line_data.at(7);
    acc_details->subscription_num_ = Utilities::ConvertEnglish(token);
  } else
  {
    is_parse = false;
  }

  //Line 4
  line_no++;
  line_data = data_in.at(line_no);

  if (line_data.size() > 5)
  {
    //Invoice Date, Position 0, data is Date and written in string
    token = line_data.at(0);
    token = Utilities::ConvertEnglish(token);
    acc_details->invoice_date_ = Utilities::ToGregorian(
        Utilities::ToDate(token).trimmed());

    //Electrometer Fee, Postion 5
    token = line_data.at(5);
    acc_details->electrometer_fee_ = Utilities::ConvertEnglish(token);
  } else
  {
    is_parse = false;
  }

  //Line 5
  line_no++;
  line_data = data_in.at(line_no);

  if (line_data.size() > 5)
  {
    //Inovice Number, Position 0
    token = line_data.at(0);
    acc_details->invoice_num_ = Utilities::ConvertEnglish(token);

    //Total Power Consumption Cost, position 5
    token = line_data.at(5);
    acc_details->total_power_cons_cost_ = Utilities::ConvertEnglish(token);
  } else
  {
    is_parse = false;
  }

  //Line 6
  line_no++;
  line_data = data_in.at(line_no);

  //Settlement, postion 1
  if (line_data.size() > 1)
  {
    token = line_data.at(1);
    acc_details->settlement_ = Utilities::ConvertEnglish(token);
  } else
  {
    is_parse = false;
  }

  //Line 7 
  line_no++;
  line_data = data_in.at(line_no);

  if (line_data.size() > 2)
  {
    //Total Cost, postion 2
    token = line_data.at(2);
    acc_details->total_cost_ = Utilities::ConvertEnglish(token);
  } else
  {
    is_parse = false;
  }

  acc_details->parsing_ = "Completed";
  if (!is_parse)
  {
    acc_details->parsing_ = "Partial";
  }

  acc_details->block_length_ = data_in.size();  
}

