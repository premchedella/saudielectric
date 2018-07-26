#include "parse_data.h"

#include <algorithm>    // std::find

#include "utilities.h"
#include "type_1_parser.h"
#include "type_5_parser.h"
#include "type_12_parser.h"

std::vector<AccountDetails> ParseData::account_details_;
std::vector<unsigned int> ParseData::types_;
std::vector<AccountDetails> ParseData::type_account_details_;

ParseData::ParseData()
{

}

ParseData::~ParseData()
{

}

void ParseData::FormData(Blocks data)
{
  std::cout << "Number of Residential Blocks = " << data.size() << std::endl;
  account_details_.clear();
  types_.clear();
   
  for (unsigned int index = 0; index < data.size(); index++)  
  {    
    QString eng_data;
    unsigned int type;
    Block data_block = data.at(index);

    QStringList line_data = data_block.at(2);
    eng_data = line_data.at(1);
    int position = eng_data.indexOf("_");
    eng_data = eng_data.mid(position + 1, eng_data.size());
    eng_data = Utilities::ConvertEnglish(eng_data);
    type = eng_data.toUInt();   

    std::vector<unsigned int>::iterator it;
    
    it = std::find(types_.begin(), types_.end(), type);
    if (it == types_.end())
    {
      types_.push_back(type);
    }

    if (index == 2109)
    {
      std::cout << "Temp" << std::endl;
    }
    
    switch (type)
    {
      case 1:
        ParseType1(data_block);        
        break;
      case 5:
        ParseType5(data_block);        
        break;
      case 12:
        ParseType12(data_block);        
        break;
      default:
        std::cout << "Not a valid Type = " << type << std::endl;
    }     
  }
}

std::vector<unsigned int> ParseData::GetTypes()
{
  return types_;
}

std::vector<AccountDetails> ParseData::GetDataInfo()
{
  return account_details_;
}

std::vector<AccountDetails> ParseData::GetDataInfo(unsigned int type)
{
  std::vector<AccountDetails> retval;
  std::vector<unsigned int>::iterator it;
  it = std::find(types_.begin(), types_.end(), type);
  if (it != types_.end())
  {    
    for (unsigned int index = 0; index < account_details_.size(); index++)
    {
      AccountDetails acc_details = account_details_.at(index);
      if (acc_details.type_.toInt() == type)
      {        
        retval.push_back(acc_details);
      }
    }    
  }
  return retval;
}

void ParseData::ParseType1(Block data_in)
{
  AccountDetails acc_details;
  Type1Parser type_1_parser;

  type_1_parser.Parse(data_in, &acc_details);
  account_details_.push_back(acc_details);

  /*Utilities::VatTypes vat_type = Utilities::GetVatType();

  if (vat_type == Utilities::VatTypes::WITH)
  {
    VatParseType1(data_in);
  } else if (vat_type == Utilities::VatTypes::WITH_OUT)
  {
    NonVatParseType1(data_in);
  } else if (vat_type == Utilities::VatTypes::PARTIAL)
  {
    ParVatParseType1(data_in);
  }*/
}

void ParseData::ParseType5(Block data_in)
{
  AccountDetails acc_details;
  Type5Parser type_5_parser;

  type_5_parser.Parse(data_in, &acc_details);
  account_details_.push_back(acc_details);

  /*Utilities::VatTypes vat_type = Utilities::GetVatType();
  
  if (vat_type == Utilities::VatTypes::WITH)
  {
    VatParseType5(data_in);
  } else if (vat_type == Utilities::VatTypes::WITH_OUT)
  {
    NonVatParseType5(data_in);
  } else if (vat_type == Utilities::VatTypes::PARTIAL)
  {
    ParVatParseType5(data_in);
  }*/
}

void ParseData::ParseType12(Block data_in)
{
  AccountDetails acc_details;
  Type12Parser type_12_parser;

  type_12_parser.Parse(data_in, &acc_details);
  account_details_.push_back(acc_details);

  
  /*Utilities::VatTypes vat_type = Utilities::GetVatType();

  if(vat_type == Utilities::VatTypes::WITH)
  {
    VatParseType12(data_in);
  } else if (vat_type == Utilities::VatTypes::WITH_OUT)
  {
    NonVatParseType12(data_in);
  } else if (vat_type == Utilities::VatTypes::PARTIAL)
  {
    ParVatParseType12(data_in);
  }*/
}

void ParseData::VatParseType1(Block data_in)
{
  Utilities::InputFileTypes file_type = Utilities::GetFileType();
  if (file_type == Utilities::InputFileTypes::KAU1_MAIN)
  {
    VatParseType1Large(data_in);
  } else
  {
    VatParseType1Small(data_in);
  }  
}

void ParseData::VatParseType5(Block data_in)
{
  VatParseType1Small(data_in);
}

void ParseData::VatParseType12(Block data_in)
{
  AccountDetails acc_details;
  QStringList line_data;
  QString eng_data;

  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2
  unsigned int line_no = 2;
  line_data = data_in.at(line_no);

  // Electrometer Number, Position = 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.electrometer_num_ = eng_data;

  //Type, Position = 1
  eng_data = line_data.at(1);
  int position = eng_data.indexOf("_");
  eng_data = eng_data.mid(position + 1, eng_data.size());
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.type_ = eng_data;

  //SubType, Position = 1
  eng_data = line_data.at(1);
  position = eng_data.indexOf("_");
  eng_data = eng_data.mid(0, position);
  acc_details.sub_type_ = Utilities::ToType(eng_data);

  //Meter Reading To, Position 2, data is Date and written in string
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_to_ = Utilities::ToDate(eng_data).trimmed();

  //Meter Reading From, Position 3, data is Date and written in string
  eng_data = line_data.at(3);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_from_ = Utilities::ToDate(eng_data).trimmed();

  //Factor, Position 4
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_factor_ = eng_data;

  //Capacity, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.capacity_ = eng_data;

  //Account Number, Position 8
  eng_data = line_data.at(8);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.account_num_ = eng_data;

  // HACK: For some cases, the account number is reserved including data
  if (acc_details.account_num_ == 0)
  {
    eng_data = line_data.at(6);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.account_num_ = eng_data;
  }

  //Line No.3
  line_no++;
  line_data = data_in.at(line_no);

  //Days, postion 0 
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_days_ = eng_data;

  //Current Reading, Position 1  
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.curr_reading_ = eng_data;

  //Previous Reading, Position 2 
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.prev_reading_ = eng_data;

  //Active Power Consumption, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_consumption_ = eng_data;

  //Active Power Consumption Cost, postion 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_consumption_cost_ = eng_data;

  //Subscription Number, Postion 7
  eng_data = line_data.at(7);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.subscription_num_ = eng_data;

  //Line 4
  line_no++;
  line_data = data_in.at(line_no);

  //TODO: Give a name, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_curr_reading_ = eng_data;

  //TODO: Give a name, Position 1 
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_prev_reading_ = eng_data;

  //Reactive Power Consumption, Position 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_pow_cons_ = eng_data;

  //Reactive Power Consumption Cost, Position 7
  eng_data = line_data.at(7);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_pow_cons_cost_ = eng_data;

  //Line 5
  line_no++;
  line_data = data_in.at(line_no);

  //Invoice Date, Position 0, data is Date and written in string
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_date_ = Utilities::ToDate(eng_data).trimmed();

  //Electrometer Fee, Postion 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.electrometer_fee_ = eng_data;

  //Line 6
  line_no++;
  line_data = data_in.at(line_no);

  //Inovice Number, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_num_ = eng_data;

  //Total Power Consumption Cost, position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_power_cons_cost_ = eng_data;

  //Line 7
  line_no++;
  line_data = data_in.at(line_no);

  //Settlement, postion 1
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.settlement_ = eng_data;

  //Line 8
  line_no++;  
  line_data = data_in.at(line_no);
  //VAT, postion 4 or 5
  if (line_data.size() == 6)
  {
    eng_data = line_data.at(5);
  } else
  {
    eng_data = line_data.at(4);
  }
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.vat_ = eng_data;  

  //Line 9  
  line_no++;
  line_data = data_in.at(line_no);

  //Total Cost, postion 2
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_cost_ = eng_data;

  //Line 11
  line_no = line_no + 2;
  line_data = data_in.at(line_no);
  //Total Consumption, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_react_pow_con_ = eng_data;

  //Allowed Consumption, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.allowed_react_pow_con_ = eng_data;

  //Power factor, Postion 12
  eng_data = line_data.at(12);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.react_power_factor_ = eng_data;

  //Line 15
  line_no = line_no + 4;
  line_data = data_in.at(line_no);
  //Previous Reading, Position 3
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.sub_prev_reading_ = eng_data;

  //TODO: New Current Reading, Position 5
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.sub_curr_reading_ = eng_data;
  
  //Line 35
  line_no = data_in.size() - 2;
  line_data = data_in.at(line_no);

  //Total Reactive Power Consumption, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_total_react_pow_con_ = eng_data;

  //Multiplication Factor for Reactive Power, Position 2
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.mul_react_power_factor_ = eng_data;

  //Previous Reactive Power Meter Reading, Position 4
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reactive_prev_reading_ = eng_data;

  //Current Reactive Power Meter Reading, Position 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reactive_curr_reading_ = eng_data;

  acc_details.block_length_ = data_in.size();

  account_details_.push_back(acc_details);
}

void ParseData::NonVatParseType1(Block data_in)
{
  Utilities::InputFileTypes file_type = Utilities::GetFileType();
  if (file_type == Utilities::InputFileTypes::KAU1_MAIN)
  {
    NonVatParseType1Large(data_in);
  } else
  {
    NonVatParseType1Small(data_in);
  }
}

void ParseData::NonVatParseType5(Block data_in)
{
  NonVatParseType1Small(data_in);
}

void ParseData::NonVatParseType12(Block data_in)
{
  AccountDetails acc_details;
  QStringList line_data;
  QString eng_data;

  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2
  unsigned int line_no = 2;
  line_data = data_in.at(line_no);

  // Electrometer Number, Position = 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.electrometer_num_ = eng_data;

  //Type, Position = 1
  eng_data = line_data.at(1);
  int position = eng_data.indexOf("_");
  eng_data = eng_data.mid(position + 1, eng_data.size());
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.type_ = eng_data;

  //SubType, Position = 1
  eng_data = line_data.at(1);
  position = eng_data.indexOf("_");
  eng_data = eng_data.mid(0, position);
  acc_details.sub_type_ = Utilities::ToType(eng_data);

  //Meter Reading To, Position 2, data is Date and written in string
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_to_ = Utilities::ToDate(eng_data).trimmed();

  //Meter Reading From, Position 3, data is Date and written in string
  eng_data = line_data.at(3);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_from_ = Utilities::ToDate(eng_data).trimmed();

  //Factor, Position 4
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_factor_ = eng_data;

  //Capacity, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.capacity_ = eng_data;

  //Account Number, Position 8
  eng_data = line_data.at(8);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.account_num_ = eng_data;

  // HACK: For some cases, the account number is reserved including data
  if (acc_details.account_num_ == 0)
  {
    eng_data = line_data.at(6);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.account_num_ = eng_data;
  }

  //Line No.3
  line_no++;
  line_data = data_in.at(line_no);

  //Days, postion 0 
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_days_ = eng_data;

  //Current Reading, Position 1  
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.curr_reading_ = eng_data;

  //Previous Reading, Position 2 
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.prev_reading_ = eng_data;

  //Active Power Consumption, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_consumption_ = eng_data;

  //Active Power Consumption Cost, postion 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_consumption_cost_ = eng_data;

  //Subscription Number, Postion 7
  eng_data = line_data.at(7);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.subscription_num_ = eng_data;

  //Line 4
  line_no++;
  line_data = data_in.at(line_no);

  //TODO: Give a name, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_curr_reading_ = eng_data;

  //TODO: Give a name, Position 1 
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_prev_reading_ = eng_data;

  //Reactive Power Consumption, Position 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_pow_cons_ = eng_data;

  //Reactive Power Consumption Cost, Position 7
  eng_data = line_data.at(7);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_pow_cons_cost_ = eng_data;

  //Line 5
  line_no++;
  line_data = data_in.at(line_no);

  //Invoice Date, Position 0, data is Date and written in string
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_date_ = Utilities::ToDate(eng_data).trimmed();

  //Electrometer Fee, Postion 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.electrometer_fee_ = eng_data;

  //Line 6
  line_no++;
  line_data = data_in.at(line_no);

  //Inovice Number, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_num_ = eng_data;

  //Total Power Consumption Cost, position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_power_cons_cost_ = eng_data;

  //Line 7
  line_no++;
  line_data = data_in.at(line_no);

  //Settlement, postion 1
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.settlement_ = eng_data;

  //Line 8
  line_no++;
  line_data = data_in.at(line_no);
  //Total Cost, postion 2
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_cost_ = eng_data;

  //Line 11
  line_no = line_no + 2;
  line_data = data_in.at(line_no);
  //Total Consumption, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_react_pow_con_ = eng_data;

  //Allowed Consumption, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.allowed_react_pow_con_ = eng_data;

  //Power factor, Postion 12
  eng_data = line_data.at(12);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.react_power_factor_ = eng_data;

  //Line 15
  line_no = line_no + 4;
  line_data = data_in.at(line_no);
  //Previous Reading, Position 3
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.sub_prev_reading_ = eng_data;

  //TODO: New Current Reading, Position 5
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.sub_curr_reading_ = eng_data;

  //Line 35
  line_no = data_in.size() - 2;
  line_data = data_in.at(line_no);

  //Total Reactive Power Consumption, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_total_react_pow_con_ = eng_data;

  //Multiplication Factor for Reactive Power, Position 2
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.mul_react_power_factor_ = eng_data;

  //Previous Reactive Power Meter Reading, Position 4
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reactive_prev_reading_ = eng_data;

  //Current Reactive Power Meter Reading, Position 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reactive_curr_reading_ = eng_data;

  acc_details.block_length_ = data_in.size();

  account_details_.push_back(acc_details);

}

void ParseData::ParVatParseType1(Block data_in)
{
  Utilities::InputFileTypes file_type = Utilities::GetFileType();
  if (file_type == Utilities::InputFileTypes::KAU1_MAIN)
  {
    ParVatParseType1Large(data_in);
  } else
  {
    ParVatParseType1Small(data_in);
  }
}

void ParseData::ParVatParseType5(Block data_in)
{
  ParVatParseType1Small(data_in);
}

void ParseData::ParVatParseType12(Block data_in)
{
  AccountDetails acc_details;
  QStringList line_data;
  QString eng_data;

  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2
  unsigned int line_no = 2;
  line_data = data_in.at(line_no);

  // Electrometer Number, Position = 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.electrometer_num_ = eng_data;

  //Type, Position = 1
  eng_data = line_data.at(1);
  int position = eng_data.indexOf("_");
  eng_data = eng_data.mid(position + 1, eng_data.size());
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.type_ = eng_data;

  //SubType, Position = 1
  eng_data = line_data.at(1);
  position = eng_data.indexOf("_");
  eng_data = eng_data.mid(0, position);
  acc_details.sub_type_ = Utilities::ToType(eng_data);

  //Meter Reading To, Position 2, data is Date and written in string
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_to_ = Utilities::ToDate(eng_data).trimmed();

  //Meter Reading From, Position 3, data is Date and written in string
  eng_data = line_data.at(3);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_from_ = Utilities::ToDate(eng_data).trimmed();

  //Factor, Position 4
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_factor_ = eng_data;

  //Capacity, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.capacity_ = eng_data;

  //Account Number, Position 8
  eng_data = line_data.at(8);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.account_num_ = eng_data;

  // HACK: For some cases, the account number is reserved including data
  if (acc_details.account_num_ == 0)
  {
    eng_data = line_data.at(6);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.account_num_ = eng_data;
  }

  //Line No.3
  line_no++;
  line_data = data_in.at(line_no);

  //Days, postion 0 
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_days_ = eng_data;

  //Current Reading, Position 1  
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.curr_reading_ = eng_data;

  //Previous Reading, Position 2 
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.prev_reading_ = eng_data;

  //Active Power Consumption, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_consumption_ = eng_data;

  //Active Power Consumption Cost, postion 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_consumption_cost_ = eng_data;

  //Subscription Number, Postion 7
  eng_data = line_data.at(7);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.subscription_num_ = eng_data;

  //Line 4
  line_no++;
  line_data = data_in.at(line_no);

  //TODO: Give a name, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_curr_reading_ = eng_data;

  //TODO: Give a name, Position 1 
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_prev_reading_ = eng_data;

  //Reactive Power Consumption, Position 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_pow_cons_ = eng_data;

  //Reactive Power Consumption Cost, Position 7
  eng_data = line_data.at(7);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_pow_cons_cost_ = eng_data;

  //Line 5
  line_no++;
  line_data = data_in.at(line_no);

  //Invoice Date, Position 0, data is Date and written in string
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_date_ = Utilities::ToDate(eng_data).trimmed();

  //Electrometer Fee, Postion 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.electrometer_fee_ = eng_data;

  //Line 6
  line_no++;
  line_data = data_in.at(line_no);

  //Inovice Number, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_num_ = eng_data;

  //Total Power Consumption Cost, position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_power_cons_cost_ = eng_data;

  //Line 7
  line_no++;
  line_data = data_in.at(line_no);

  //Settlement, postion 1
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.settlement_ = eng_data;

  //Line 8
  line_no++;
  line_data = data_in.at(line_no);
    //VAT, postion 4 or 5
  if ((line_data.size() == 6) || (line_data.size() == 5))
  {
    if (line_data.size() == 6)
    {
      eng_data = line_data.at(5);
    } else
    {
      eng_data = line_data.at(4);
    }
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.vat_ = eng_data;
    line_no++;
  }

  //Line 9  
  line_data = data_in.at(line_no);

  //Total Cost, postion 2
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_cost_ = eng_data;

  //Line 11
  line_no = line_no + 2;
  line_data = data_in.at(line_no);
  //Total Consumption, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_react_pow_con_ = eng_data;

  //Allowed Consumption, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.allowed_react_pow_con_ = eng_data;

  //Power factor, Postion 12
  eng_data = line_data.at(12);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.react_power_factor_ = eng_data;

  //Line 15
  line_no = line_no + 4;
  line_data = data_in.at(line_no);
  //Previous Reading, Position 4
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.sub_prev_reading_ = eng_data;

  //TODO: New Current Reading, Position 6  
  line_no++;
  line_data = data_in.at(line_no);  
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.sub_curr_reading_ = eng_data;
  
  //Line 35
  line_no = data_in.size() - 2;
  line_data = data_in.at(line_no);

  //Total Reactive Power Consumption, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_total_react_pow_con_ = eng_data;

  //Multiplication Factor for Reactive Power, Position 2
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.mul_react_power_factor_ = eng_data;

  //Previous Reactive Power Meter Reading, Position 4
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reactive_prev_reading_ = eng_data;

  //Current Reactive Power Meter Reading, Position 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reactive_curr_reading_ = eng_data;

  acc_details.block_length_ = data_in.size();

  account_details_.push_back(acc_details);
}

void ParseData::VatParseType1Small(Block data_in)
{
  AccountDetails acc_details;

  QStringList line_data;
  QString eng_data;

  int line_no = 2;
  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2
  line_data = data_in.at(line_no);

  // Electrometer Number, Position = 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.electrometer_num_ = eng_data;

  //Type, Position = 1
  eng_data = line_data.at(1);
  int position = eng_data.indexOf("_");
  eng_data = eng_data.mid(position + 1, eng_data.size());
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.type_ = eng_data;

  //SubType, Position = 1
  eng_data = line_data.at(1);
  position = eng_data.indexOf("_");
  eng_data = eng_data.mid(0, position);
  acc_details.sub_type_ = Utilities::ToType(eng_data);

  //Meter Reading To, Position 2, data is Date and written in string
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_to_ = Utilities::ToDate(eng_data).trimmed();

  //Meter Reading From, Position 3, data is Date and written in string
  eng_data = line_data.at(3);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_from_ = Utilities::ToDate(eng_data).trimmed();

  //Factor, Position 4
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_factor_ = eng_data;

  //Capacity, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.capacity_ = eng_data;

  //Account Number, Position 8
  eng_data = line_data.at(8);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.account_num_ = eng_data;

  // HACK: For some cases, the account number is reserved including data
  if (acc_details.account_num_ == 0)
  {
    eng_data = line_data.at(6);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.account_num_ = eng_data;
  }

  //Line No.3
  line_no++;
  line_data = data_in.at(line_no);

  //Number Days, postion 0 
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_days_ = eng_data;

  //Current Reading, Position 1 
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.curr_reading_ = eng_data;

  //Previous Reading, Position 2 
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.prev_reading_ = eng_data;

  //Power Consumption, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_consumption_ = eng_data;

  //Power Consumption Cost, postion 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_consumption_cost_ = eng_data;

  //Subscription Number, Postion 7
  eng_data = line_data.at(7);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.subscription_num_ = eng_data;

  //Line 4
  line_no++;
  line_data = data_in.at(line_no);

  //Invoice Date, Position 0, data is Date and written in string
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_date_ = Utilities::ToDate(eng_data);

  //Electrometer Fee, Postion 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.electrometer_fee_ = eng_data;

  //Line 5
  line_no++;
  line_data = data_in.at(line_no);

  //Inovice Number, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_num_ = eng_data;

  //Total Power Consumption Cost, position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_power_cons_cost_ = eng_data;

  //Line 6
  line_no++;
  line_data = data_in.at(line_no);

  //Settlement, postion 1
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.settlement_ = eng_data;

  //Line 7
  line_no++;
  line_data = data_in.at(line_no);
  
  //VAT, postion 4 or 5
  if (line_data.size() == 6)
  {
    eng_data = line_data.at(5);
  } else
  {
    eng_data = line_data.at(4);
  }
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.vat_ = eng_data;

  //Line 8 
  line_no++;
  line_data = data_in.at(line_no);

  //Total Cost, postion 2
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_cost_ = eng_data;

  acc_details.block_length_ = data_in.size();

  account_details_.push_back(acc_details);
}

void ParseData::VatParseType1Large(Block data_in)
{
  AccountDetails acc_details;

  QStringList line_data;
  QString eng_data;

  int line_no = 2;
  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2
  line_data = data_in.at(line_no);

  // Electrometer Number, Position = 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.electrometer_num_ = eng_data;

  //Type, Position = 1
  eng_data = line_data.at(1);
  int position = eng_data.indexOf("_");
  eng_data = eng_data.mid(position + 1, eng_data.size());
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.type_ = eng_data;

  //SubType, Position = 1
  eng_data = line_data.at(1);
  position = eng_data.indexOf("_");
  eng_data = eng_data.mid(0, position);
  acc_details.sub_type_ = Utilities::ToType(eng_data);

  //Meter Reading To, Position 2, data is Date and written in string
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_to_ = Utilities::ToDate(eng_data).trimmed();

  //Meter Reading From, Position 3, data is Date and written in string
  eng_data = line_data.at(3);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_from_ = Utilities::ToDate(eng_data).trimmed();

  //Factor, Position 4
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_factor_ = eng_data;

  //Capacity, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.capacity_ = eng_data;

  //Account Number, Position 8
  eng_data = line_data.at(8);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.account_num_ = eng_data;

  // HACK: For some cases, the account number is reserved including data
  if (acc_details.account_num_ == 0)
  {
    eng_data = line_data.at(6);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.account_num_ = eng_data;
  }

  //Line No.3
  line_no++;
  line_data = data_in.at(line_no);

  //Number Days, postion 0 
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_days_ = eng_data;

  //Current Reading, Position 1 
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.curr_reading_ = eng_data;

  //Previous Reading, Position 2 
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.prev_reading_ = eng_data;

  //Power Consumption, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_consumption_ = eng_data;

  //Power Consumption Cost, postion 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_consumption_cost_ = eng_data;

  //Subscription Number, Postion 7
  eng_data = line_data.at(7);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.subscription_num_ = eng_data;

  //Line 4
  line_no++;
  line_data = data_in.at(line_no);

  //TODO: Give a name, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_curr_reading_ = eng_data;

  //TODO: Give a name, Position 1 
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_prev_reading_ = eng_data;

  //Reactive Power Consumption, Position 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_pow_cons_ = eng_data;

  //Reactive Power Consumption Cost, Position 7
  eng_data = line_data.at(7);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_pow_cons_cost_ = eng_data;
  
  //Line 5
  line_no++;
  line_data = data_in.at(line_no);

  //Invoice Date, Position 0, data is Date and written in string
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_date_ = Utilities::ToDate(eng_data);

  //Electrometer Fee, Postion 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.electrometer_fee_ = eng_data;

  //Line 6
  line_no++;
  line_data = data_in.at(line_no);

  //Inovice Number, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_num_ = eng_data;

  //Total Power Consumption Cost, position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_power_cons_cost_ = eng_data;

  //Line 7
  line_no++;
  line_data = data_in.at(line_no);

  //Settlement, postion 1
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.settlement_ = eng_data;

  //Line 8
  line_no++;  
  line_data = data_in.at(line_no);       
  //VAT, postion 4 or 5
  if (line_data.size() == 6)
  {
    eng_data = line_data.at(5);
  } else
  {
    eng_data = line_data.at(4);
  }
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.vat_ = eng_data;

  //Line 9
  line_no++;
  line_data = data_in.at(line_no);

  //Total Cost, postion 2
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_cost_ = eng_data;
    
  //Line 11
  line_no = line_no + 2;    
  line_data = data_in.at(line_no);
  //Total Consumption, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_react_pow_con_ = eng_data;

  //Allowed Consumption, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.allowed_react_pow_con_ = eng_data;

  //Power factor, Postion 12
  eng_data = line_data.at(12);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.react_power_factor_ = eng_data;
    
  //Line 15
  line_no = line_no + 4;    
  line_data = data_in.at(line_no);
  //Previous Reading, Position 3
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.sub_prev_reading_ = eng_data;

  //TODO: New Current Reading, Position 5
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.sub_curr_reading_ = eng_data;
  
    // Line
  line_no = data_in.size() - 2;    
  line_data = data_in.at(line_no);

  //Total Reactive Power Consumption, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_total_react_pow_con_ = eng_data;

  //Multiplication Factor for Reactive Power, Position 2
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.mul_react_power_factor_ = eng_data;

  //Previous Reactive Power Meter Reading, Position 4
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reactive_prev_reading_ = eng_data;

  //Current Reactive Power Meter Reading, Position 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reactive_curr_reading_ = eng_data;    

  acc_details.block_length_ = data_in.size();

  account_details_.push_back(acc_details);
}

void ParseData::NonVatParseType1Small(Block data_in)
{
  AccountDetails acc_details;

  QStringList line_data;
  QString eng_data;

  int line_no = 2;
  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2
  line_data = data_in.at(line_no);

  // Electrometer Number, Position = 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.electrometer_num_ = eng_data;

  //Type, Position = 1
  eng_data = line_data.at(1);
  int position = eng_data.indexOf("_");
  eng_data = eng_data.mid(position + 1, eng_data.size());
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.type_ = eng_data;

  //SubType, Position = 1
  eng_data = line_data.at(1);
  position = eng_data.indexOf("_");
  eng_data = eng_data.mid(0, position);
  acc_details.sub_type_ = Utilities::ToType(eng_data);

  //Meter Reading To, Position 2, data is Date and written in string
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_to_ = Utilities::ToDate(eng_data).trimmed();

  //Meter Reading From, Position 3, data is Date and written in string
  eng_data = line_data.at(3);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_from_ = Utilities::ToDate(eng_data).trimmed();

  //Factor, Position 4
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_factor_ = eng_data;

  //Capacity, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.capacity_ = eng_data;

  //Account Number, Position 8
  eng_data = line_data.at(8);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.account_num_ = eng_data;

  // HACK: For some cases, the account number is reserved including data
  if (acc_details.account_num_ == 0)
  {
    eng_data = line_data.at(6);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.account_num_ = eng_data;
  }

  //Line No.3
  line_no++;
  line_data = data_in.at(line_no);

  //Number Days, postion 0 
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_days_ = eng_data;

  //Current Reading, Position 1 
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.curr_reading_ = eng_data;

  //Previous Reading, Position 2 
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.prev_reading_ = eng_data;

  //Power Consumption, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_consumption_ = eng_data;

  //Power Consumption Cost, postion 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_consumption_cost_ = eng_data;

  //Subscription Number, Postion 7
  eng_data = line_data.at(7);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.subscription_num_ = eng_data;

  //Line 4
  line_no++;
  line_data = data_in.at(line_no);

  //Invoice Date, Position 0, data is Date and written in string
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_date_ = Utilities::ToDate(eng_data);

  //Electrometer Fee, Postion 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.electrometer_fee_ = eng_data;

  //Line 5
  line_no++;
  line_data = data_in.at(line_no);

  //Inovice Number, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_num_ = eng_data;

  //Total Power Consumption Cost, position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_power_cons_cost_ = eng_data;

  //Line 6
  line_no++;
  line_data = data_in.at(line_no);

  //Settlement, postion 1
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.settlement_ = eng_data;

  //Line 7 
  line_no++;
  line_data = data_in.at(line_no);

  //Total Cost, postion 2
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_cost_ = eng_data;

  acc_details.block_length_ = data_in.size();

  account_details_.push_back(acc_details);
}

void ParseData::NonVatParseType1Large(Block data_in)
{
  AccountDetails acc_details;

  QStringList line_data;
  QString eng_data;

  int line_no = 2;
  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2
  line_data = data_in.at(line_no);

  // Electrometer Number, Position = 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.electrometer_num_ = eng_data;

  //Type, Position = 1
  eng_data = line_data.at(1);
  int position = eng_data.indexOf("_");
  eng_data = eng_data.mid(position + 1, eng_data.size());
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.type_ = eng_data;

  //SubType, Position = 1
  eng_data = line_data.at(1);
  position = eng_data.indexOf("_");
  eng_data = eng_data.mid(0, position);
  acc_details.sub_type_ = Utilities::ToType(eng_data);

  //Meter Reading To, Position 2, data is Date and written in string
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_to_ = Utilities::ToDate(eng_data).trimmed();

  //Meter Reading From, Position 3, data is Date and written in string
  eng_data = line_data.at(3);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_from_ = Utilities::ToDate(eng_data).trimmed();

  //Factor, Position 4
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_factor_ = eng_data;

  //Capacity, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.capacity_ = eng_data;

  //Account Number, Position 8
  eng_data = line_data.at(8);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.account_num_ = eng_data;

  // HACK: For some cases, the account number is reserved including data
  if (acc_details.account_num_ == 0)
  {
    eng_data = line_data.at(6);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.account_num_ = eng_data;
  }

  //Line No.3
  line_no++;
  line_data = data_in.at(line_no);

  //Number Days, postion 0 
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_days_ = eng_data;

  //Current Reading, Position 1 
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.curr_reading_ = eng_data;

  //Previous Reading, Position 2 
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.prev_reading_ = eng_data;

  //Power Consumption, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_consumption_ = eng_data;

  //Power Consumption Cost, postion 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_consumption_cost_ = eng_data;

  //Subscription Number, Postion 7
  eng_data = line_data.at(7);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.subscription_num_ = eng_data;

  //Line 4
  line_no++;
  line_data = data_in.at(line_no);

  //TODO: Give a name, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_curr_reading_ = eng_data;

  //TODO: Give a name, Position 1 
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_prev_reading_ = eng_data;

  //Reactive Power Consumption, Position 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_pow_cons_ = eng_data;

  //Reactive Power Consumption Cost, Position 7
  eng_data = line_data.at(7);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_pow_cons_cost_ = eng_data;

  //Line 5
  line_no++;
  line_data = data_in.at(line_no);

  //Invoice Date, Position 0, data is Date and written in string
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_date_ = Utilities::ToDate(eng_data);

  //Electrometer Fee, Postion 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.electrometer_fee_ = eng_data;

  //Line 6
  line_no++;
  line_data = data_in.at(line_no);

  //Inovice Number, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_num_ = eng_data;

  //Total Power Consumption Cost, position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_power_cons_cost_ = eng_data;

  //Line 7
  line_no++;
  line_data = data_in.at(line_no);

  //Settlement, postion 1
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.settlement_ = eng_data;
  
  //Line 8
  line_no++;
  line_data = data_in.at(line_no);

  //Total Cost, postion 2
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_cost_ = eng_data;

  //Line 10
  line_no = line_no + 2;
  line_data = data_in.at(line_no);
  //Total Consumption, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_react_pow_con_ = eng_data;

  //Allowed Consumption, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.allowed_react_pow_con_ = eng_data;

  //Power factor, Postion 12
  eng_data = line_data.at(12);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.react_power_factor_ = eng_data;

  //Line 14
  line_no = line_no + 4;
  line_data = data_in.at(line_no);
  //Previous Reading, Position 3
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.sub_prev_reading_ = eng_data;

  //TODO: New Current Reading, Position 5
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.sub_curr_reading_ = eng_data;

  // Line
  line_no = data_in.size() - 2;
  line_data = data_in.at(line_no);

  //Total Reactive Power Consumption, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_total_react_pow_con_ = eng_data;

  //Multiplication Factor for Reactive Power, Position 2
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.mul_react_power_factor_ = eng_data;

  //Previous Reactive Power Meter Reading, Position 4
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reactive_prev_reading_ = eng_data;

  //Current Reactive Power Meter Reading, Position 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reactive_curr_reading_ = eng_data;

  acc_details.block_length_ = data_in.size();

  account_details_.push_back(acc_details);
}

void ParseData::ParVatParseType1Small(Block data_in)
{
  AccountDetails acc_details;

  QStringList line_data;
  QString eng_data;

  int line_no = 2;
  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2
  line_data = data_in.at(line_no);

  // Electrometer Number, Position = 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.electrometer_num_ = eng_data;

  //Type, Position = 1
  eng_data = line_data.at(1);
  int position = eng_data.indexOf("_");
  eng_data = eng_data.mid(position + 1, eng_data.size());
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.type_ = eng_data;

  //SubType, Position = 1
  eng_data = line_data.at(1);
  position = eng_data.indexOf("_");
  eng_data = eng_data.mid(0, position);
  acc_details.sub_type_ = Utilities::ToType(eng_data);

  //Meter Reading To, Position 2, data is Date and written in string
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_to_ = Utilities::ToDate(eng_data).trimmed();

  //Meter Reading From, Position 3, data is Date and written in string
  eng_data = line_data.at(3);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_from_ = Utilities::ToDate(eng_data).trimmed();

  //Factor, Position 4
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_factor_ = eng_data;

  //Capacity, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.capacity_ = eng_data;

  //Account Number, Position 8
  eng_data = line_data.at(8);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.account_num_ = eng_data;

  // HACK: For some cases, the account number is reserved including data
  if (acc_details.account_num_ == 0)
  {
    eng_data = line_data.at(6);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.account_num_ = eng_data;
  }

  //Line No.3
  line_no++;
  line_data = data_in.at(line_no);

  //Number Days, postion 0 
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_days_ = eng_data;

  //Current Reading, Position 1 
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.curr_reading_ = eng_data;

  //Previous Reading, Position 2 
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.prev_reading_ = eng_data;

  //Power Consumption, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_consumption_ = eng_data;

  //Power Consumption Cost, postion 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_consumption_cost_ = eng_data;

  //Subscription Number, Postion 7
  eng_data = line_data.at(7);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.subscription_num_ = eng_data;

  //Line 4
  line_no++;
  line_data = data_in.at(line_no);

  //Invoice Date, Position 0, data is Date and written in string
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_date_ = Utilities::ToDate(eng_data);

  //Electrometer Fee, Postion 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.electrometer_fee_ = eng_data;

  //Line 5
  line_no++;
  line_data = data_in.at(line_no);

  //Inovice Number, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_num_ = eng_data;

  //Total Power Consumption Cost, position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_power_cons_cost_ = eng_data;

  //Line 6
  line_no++;
  line_data = data_in.at(line_no);

  //Settlement, postion 1
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.settlement_ = eng_data;

  //Line 7
  line_no++;
  line_data = data_in.at(line_no);
  if ((line_data.size() == 6) || (line_data.size() == 5))
  {
    //VAT, postion 4 or 5
    if (line_data.size() == 6)
    {
      eng_data = line_data.at(5);
    } else
    {
      eng_data = line_data.at(4);
    }
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.vat_ = eng_data;
    line_no++;
  }

  //Line 8   
  line_data = data_in.at(line_no);

  //Total Cost, postion 2
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_cost_ = eng_data;

  acc_details.block_length_ = data_in.size();

  account_details_.push_back(acc_details);
}

void ParseData::ParVatParseType1Large(Block data_in)
{
  AccountDetails acc_details;

  QStringList line_data;
  QString eng_data;

  int line_no = 2;
  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2
  line_data = data_in.at(line_no);

  // Electrometer Number, Position = 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.electrometer_num_ = eng_data;

  //Type, Position = 1
  eng_data = line_data.at(1);
  int position = eng_data.indexOf("_");
  eng_data = eng_data.mid(position + 1, eng_data.size());
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.type_ = eng_data;

  //SubType, Position = 1
  eng_data = line_data.at(1);
  position = eng_data.indexOf("_");
  eng_data = eng_data.mid(0, position);
  acc_details.sub_type_ = Utilities::ToType(eng_data);

  //Meter Reading To, Position 2, data is Date and written in string
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_to_ = Utilities::ToDate(eng_data).trimmed();

  //Meter Reading From, Position 3, data is Date and written in string
  eng_data = line_data.at(3);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_from_ = Utilities::ToDate(eng_data).trimmed();

  //Factor, Position 4
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_factor_ = eng_data;

  //Capacity, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.capacity_ = eng_data;

  //Account Number, Position 8
  eng_data = line_data.at(8);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.account_num_ = eng_data;

  // HACK: For some cases, the account number is reserved including data
  if (acc_details.account_num_ == 0)
  {
    eng_data = line_data.at(6);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.account_num_ = eng_data;
  }

  //Line No.3
  line_no++;
  line_data = data_in.at(line_no);

  //Number Days, postion 0 
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_days_ = eng_data;

  //Current Reading, Position 1 
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.curr_reading_ = eng_data;

  //Previous Reading, Position 2 
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.prev_reading_ = eng_data;

  //Power Consumption, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_consumption_ = eng_data;

  //Power Consumption Cost, postion 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_consumption_cost_ = eng_data;

  //Subscription Number, Postion 7
  eng_data = line_data.at(7);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.subscription_num_ = eng_data;

  //Line 4
  line_no++;
  line_data = data_in.at(line_no);

  //TODO: Give a name, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_curr_reading_ = eng_data;

  //TODO: Give a name, Position 1 
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_prev_reading_ = eng_data;

  //Reactive Power Consumption, Position 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_pow_cons_ = eng_data;

  //Reactive Power Consumption Cost, Position 7
  eng_data = line_data.at(7);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_pow_cons_cost_ = eng_data;

  //Line 5
  line_no++;
  line_data = data_in.at(line_no);

  //Invoice Date, Position 0, data is Date and written in string
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_date_ = Utilities::ToDate(eng_data);

  //Electrometer Fee, Postion 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.electrometer_fee_ = eng_data;

  //Line 6
  line_no++;
  line_data = data_in.at(line_no);

  //Inovice Number, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_num_ = eng_data;

  //Total Power Consumption Cost, position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_power_cons_cost_ = eng_data;

  //Line 7
  line_no++;
  line_data = data_in.at(line_no);

  //Settlement, postion 1
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.settlement_ = eng_data;

  //Line 7
  line_no++;
  line_data = data_in.at(line_no);
  if ((line_data.size() == 6) || (line_data.size() == 5))
  {
    //VAT, postion 4 or 5
    if (line_data.size() == 6)
    {
      eng_data = line_data.at(5);
    } else
    {
      eng_data = line_data.at(4);
    }
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.vat_ = eng_data;
    line_no++;
  }

  //Line 8  
  line_data = data_in.at(line_no);

  //Total Cost, postion 2
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_cost_ = eng_data;

  //Line 10
  line_no = line_no + 2;
  line_data = data_in.at(line_no);
  //Total Consumption, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_react_pow_con_ = eng_data;

  //Allowed Consumption, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.allowed_react_pow_con_ = eng_data;

  //Power factor, Postion 12
  eng_data = line_data.at(12);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.react_power_factor_ = eng_data;

  //Line 14
  line_no = line_no + 4;
  line_data = data_in.at(line_no);
  //Previous Reading, Position 4
  
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.sub_prev_reading_ = eng_data;
  
  //TODO: New Current Reading, Position 6
  line_no++;
  line_data = data_in.at(line_no);
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.sub_curr_reading_ = eng_data;

  // Line
  line_no = data_in.size() - 2;
  line_data = data_in.at(line_no);

  //Total Reactive Power Consumption, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_total_react_pow_con_ = eng_data;

  //Multiplication Factor for Reactive Power, Position 2
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.mul_react_power_factor_ = eng_data;

  //Previous Reactive Power Meter Reading, Position 4
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reactive_prev_reading_ = eng_data;

  //Current Reactive Power Meter Reading, Position 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reactive_curr_reading_ = eng_data;

  acc_details.block_length_ = data_in.size();

  account_details_.push_back(acc_details);
}


#if 0
void ParseData::ParseType1(Block data_in)
{
  Utilities::VatTypes vat_type = Utilities::GetVatType();
  Utilities::InputFileTypes file_type = Utilities::GetFileType(); 

  AccountDetails acc_details;

  QStringList line_data;
  QString eng_data;

  int line_no = 2;
  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2
  line_data = data_in.at(line_no);

  // Electrometer Number, Position = 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.electrometer_num_ = eng_data;

  //Type, Position = 1
  eng_data = line_data.at(1);
  int position = eng_data.indexOf("_");
  eng_data = eng_data.mid(position + 1, eng_data.size());
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.type_ = eng_data;

  //SubType, Position = 1
  eng_data = line_data.at(1);
  position = eng_data.indexOf("_");
  eng_data = eng_data.mid(0, position);
  acc_details.sub_type_ = Utilities::ToType(eng_data);

  //Meter Reading To, Position 2, data is Date and written in string
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_to_ = Utilities::ToDate(eng_data).trimmed();

  //Meter Reading From, Position 3, data is Date and written in string
  eng_data = line_data.at(3);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_from_ = Utilities::ToDate(eng_data).trimmed();

  //Factor, Position 4
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_factor_ = eng_data;

  //Capacity, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.capacity_ = eng_data;

  //Account Number, Position 8
  eng_data = line_data.at(8);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.account_num_ = eng_data;

  // HACK: For some cases, the account number is reserved including data
  if (acc_details.account_num_ == 0)
  {
    eng_data = line_data.at(6);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.account_num_ = eng_data;
  }

  //Line No.3
  line_no++;
  line_data = data_in.at(line_no);

  //Number Days, postion 0 
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_days_ = eng_data;

  //Current Reading, Position 1 
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.curr_reading_ = eng_data;

  //Previous Reading, Position 2 
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.prev_reading_ = eng_data;

  //Power Consumption, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_consumption_ = eng_data;

  //Power Consumption Cost, postion 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_consumption_cost_ = eng_data;

  //Subscription Number, Postion 7
  eng_data = line_data.at(7);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.subscription_num_ = eng_data;

  if (file_type == Utilities::InputFileTypes::KAU1_MAIN)
  {
    //Line 4
    line_no++;
    line_data = data_in.at(line_no);

    //TODO: Give a name, Position 0
    eng_data = line_data.at(0);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.other_curr_reading_ = eng_data;

    //TODO: Give a name, Position 1 
    eng_data = line_data.at(1);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.other_prev_reading_ = eng_data;

    //Reactive Power Consumption, Position 6
    eng_data = line_data.at(6);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.other_pow_cons_ = eng_data;

    //Reactive Power Consumption Cost, Position 7
    eng_data = line_data.at(7);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.other_pow_cons_cost_ = eng_data;
  }

  //Line 4
  line_no++;
  line_data = data_in.at(line_no);

  //Invoice Date, Position 0, data is Date and written in string
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_date_ = Utilities::ToDate(eng_data);

  //Electrometer Fee, Postion 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.electrometer_fee_ = eng_data;

  //Line 5
  line_no++;
  line_data = data_in.at(line_no);

  //Inovice Number, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_num_ = eng_data;

  //Total Power Consumption Cost, position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_power_cons_cost_ = eng_data;

  //Line 6
  line_no++;
  line_data = data_in.at(line_no);

  //Settlement, postion 1
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.settlement_ = eng_data;

  //Line 7
  line_no++;

   
  if ((vat_type == Utilities::VatTypes::WITH) ||
    (vat_type == Utilities::VatTypes::PARTIAL))
  {     
    line_data = data_in.at(line_no);

    if ((file_type == Utilities::InputFileTypes::KAU2_MAIN) &&
        (line_data.size() != 7))
    {
      
    } else 
    {

      //VAT, postion 4 or 5
      if (line_data.size() == 6)
      {
        eng_data = line_data.at(5);
      } else
      {
        eng_data = line_data.at(4);
      }
      eng_data = Utilities::ConvertEnglish(eng_data);
      acc_details.vat_ = eng_data;
      line_no++;
    }
  } 

  //Line 8 or Line 7 in the case of non-VAT
  line_data = data_in.at(line_no);

  //Total Cost, postion 2
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_cost_ = eng_data;

  if (file_type == Utilities::InputFileTypes::KAU1_MAIN)
  {
    //Line 11
    line_no = line_no + 2;
    if (data_in.size() > line_no)
    {  
      line_data = data_in.at(line_no);
      //Total Consumption, Position 0
      eng_data = line_data.at(0);
      eng_data = Utilities::ConvertEnglish(eng_data);
      acc_details.total_react_pow_con_ = eng_data;

      //Allowed Consumption, Position 5
      eng_data = line_data.at(5);
      eng_data = Utilities::ConvertEnglish(eng_data);
      acc_details.allowed_react_pow_con_ = eng_data;

      //Power factor, Postion 12
      eng_data = line_data.at(12);
      eng_data = Utilities::ConvertEnglish(eng_data);
      acc_details.react_power_factor_ = eng_data;
    }

    //Line 15
    line_no = line_no + 4;
    if (data_in.size() > line_no)
    {
      line_data = data_in.at(line_no);
      //Previous Reading, Position 3
      eng_data = line_data.at(4);
      eng_data = Utilities::ConvertEnglish(eng_data);
      acc_details.sub_prev_reading_ = eng_data;

      //TODO: New Current Reading, Position 5
      eng_data = line_data.at(6);
      eng_data = Utilities::ConvertEnglish(eng_data);
      acc_details.sub_curr_reading_ = eng_data;

      if (vat_type == Utilities::VatTypes::PARTIAL)
      {
        line_no++;
        line_data = data_in.at(line_no);
        //TODO: New Current Reading, Position 5
        eng_data = line_data.at(6);
        eng_data = Utilities::ConvertEnglish(eng_data);
        acc_details.sub_curr_reading_ = eng_data;
      }
    }

    // Line
  
    line_no = data_in.size() - 2;
    if (data_in.size() > line_no)
    {
      line_data = data_in.at(line_no);

      //Total Reactive Power Consumption, Position 0
      eng_data = line_data.at(0);
      eng_data = Utilities::ConvertEnglish(eng_data);
      acc_details.other_total_react_pow_con_ = eng_data;

      //Multiplication Factor for Reactive Power, Position 2
      eng_data = line_data.at(2);
      eng_data = Utilities::ConvertEnglish(eng_data);
      acc_details.mul_react_power_factor_ = eng_data;

      //Previous Reactive Power Meter Reading, Position 4
      eng_data = line_data.at(4);
      eng_data = Utilities::ConvertEnglish(eng_data);
      acc_details.reactive_prev_reading_ = eng_data;

      //Current Reactive Power Meter Reading, Position 6
      eng_data = line_data.at(6);
      eng_data = Utilities::ConvertEnglish(eng_data);
      acc_details.reactive_curr_reading_ = eng_data;
    }
  }

  acc_details.block_length_ = data_in.size();

  account_details_.push_back(acc_details);
}

void ParseData::ParseType5(Block data_in)
{
  Utilities::VatTypes vat_type = Utilities::GetVatType();
  AccountDetails acc_details;

  QStringList line_data;
  QString eng_data;

  int line_no = 2;
  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2
  line_data = data_in.at(line_no);

  // Electrometer Number, Position = 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.electrometer_num_ = eng_data;

  //Type, Position = 1
  eng_data = line_data.at(1);
  int position = eng_data.indexOf("_");
  eng_data = eng_data.mid(position + 1, eng_data.size());
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.type_ = eng_data;

  //SubType, Position = 1
  eng_data = line_data.at(1);
  position = eng_data.indexOf("_");
  eng_data = eng_data.mid(0, position);
  acc_details.sub_type_ = Utilities::ToType(eng_data);

  //Meter Reading To, Position 2, data is Date and written in string
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_to_ = Utilities::ToDate(eng_data).trimmed();

  //Meter Reading From, Position 3, data is Date and written in string
  eng_data = line_data.at(3);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_from_ = Utilities::ToDate(eng_data).trimmed();

  //Factor, Position 4
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_factor_ = eng_data;

  //Capacity, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.capacity_ = eng_data;

  //Account Number, Position 8
  eng_data = line_data.at(8);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.account_num_ = eng_data;

  // HACK: For some cases, the account number is reserved including data
  if (acc_details.account_num_ == 0)
  {
    eng_data = line_data.at(6);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.account_num_ = eng_data;
  }

  //Line No.3
  line_no++;
  line_data = data_in.at(line_no);

  //Number Days, postion 0 
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_days_ = eng_data;

  //Current Reading, Position 1 
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.curr_reading_ = eng_data;

  //Previous Reading, Position 2 
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.prev_reading_ = eng_data;

  //Power Consumption, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_consumption_ = eng_data;

  //Power Consumption Cost, postion 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_consumption_cost_ = eng_data;

  //Subscription Number, Postion 7
  eng_data = line_data.at(7);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.subscription_num_ = eng_data;

  //Line 4
  line_no++;
  line_data = data_in.at(line_no);

  //Invoice Date, Position 0, data is Date and written in string
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_date_ = Utilities::ToDate(eng_data);

  //Electrometer Fee, Postion 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.electrometer_fee_ = eng_data;

  //Line 5
  line_no++;
  line_data = data_in.at(line_no);

  //Inovice Number, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_num_ = eng_data;

  //Total Power Consumption Cost, position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_power_cons_cost_ = eng_data;

  //Line 6
  line_no++;
  line_data = data_in.at(line_no);

  //Settlement, postion 1
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.settlement_ = eng_data;

  //Line 7
  line_no++;

  if ((vat_type == Utilities::VatTypes::WITH) ||
    (vat_type == Utilities::VatTypes::PARTIAL))
  {
    line_data = data_in.at(line_no);

    //VAT, postion 4 or 5
    if (line_data.size() == 6)
    {
      eng_data = line_data.at(5);
    } else
    {
      eng_data = line_data.at(4);
    }
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.vat_ = eng_data;
    line_no++;
  } 

  //Line 8 or Line 7 in the case of non-VAT
  line_data = data_in.at(line_no);

  //Total Cost, postion 2
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_cost_ = eng_data;

  acc_details.block_length_ = data_in.size();

  account_details_.push_back(acc_details);
}

void ParseData::ParseType12(Block data_in)
{
  Utilities::VatTypes vat_type = Utilities::GetVatType();
  Utilities::InputFileTypes file_type = Utilities::GetFileType();
  AccountDetails acc_details;
  QStringList line_data;
  QString eng_data;

  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2
  unsigned int line_no = 2;
  line_data = data_in.at(line_no);

  // Electrometer Number, Position = 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.electrometer_num_ = eng_data;

  //Type, Position = 1
  eng_data = line_data.at(1);
  int position = eng_data.indexOf("_");
  eng_data = eng_data.mid(position + 1, eng_data.size());
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.type_ = eng_data;

  //SubType, Position = 1
  eng_data = line_data.at(1);
  position = eng_data.indexOf("_");
  eng_data = eng_data.mid(0, position);
  acc_details.sub_type_ = Utilities::ToType(eng_data);

  //Meter Reading To, Position 2, data is Date and written in string
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_to_ = Utilities::ToDate(eng_data).trimmed(); 

  //Meter Reading From, Position 3, data is Date and written in string
  eng_data = line_data.at(3);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_from_ = Utilities::ToDate(eng_data).trimmed();

  //Factor, Position 4
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);  
  acc_details.power_factor_ = eng_data;

  //Capacity, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.capacity_ = eng_data;

  //Account Number, Position 8
  eng_data = line_data.at(8);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.account_num_ = eng_data;

  // HACK: For some cases, the account number is reserved including data
  if (acc_details.account_num_ == 0)
  {
    eng_data = line_data.at(6);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.account_num_ = eng_data;
  }

  //Line No.3
  line_no++;
  line_data = data_in.at(line_no);

  //Days, postion 0 
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_days_ = eng_data;

  //Current Reading, Position 1  
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.curr_reading_ = eng_data;

  //Previous Reading, Position 2 
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.prev_reading_ = eng_data;

  //Active Power Consumption, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_consumption_ = eng_data;

  //Active Power Consumption Cost, postion 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);   
  acc_details.power_consumption_cost_ = eng_data;

  //Subscription Number, Postion 7
  eng_data = line_data.at(7);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.subscription_num_ = eng_data;

  //Line 4
  line_no++;
  line_data = data_in.at(line_no);

  //TODO: Give a name, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_curr_reading_ = eng_data;

  //TODO: Give a name, Position 1 
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_prev_reading_ = eng_data;

  //Reactive Power Consumption, Position 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_pow_cons_ = eng_data;

  //Reactive Power Consumption Cost, Position 7
  eng_data = line_data.at(7);
  eng_data = Utilities::ConvertEnglish(eng_data);   
  acc_details.other_pow_cons_cost_ = eng_data;

  //Line 5
  line_no++;
  line_data = data_in.at(line_no);

  //Invoice Date, Position 0, data is Date and written in string
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_date_ = Utilities::ToDate(eng_data).trimmed();

  //Electrometer Fee, Postion 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);   
  acc_details.electrometer_fee_ = eng_data;

  //Line 6
  line_no++;
  line_data = data_in.at(line_no);

  //Inovice Number, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_num_ = eng_data;

  //Total Power Consumption Cost, position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);    
  acc_details.total_power_cons_cost_ = eng_data;

  //Line 7
  line_no++;
  line_data = data_in.at(line_no);

  //Settlement, postion 1
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);    
  acc_details.settlement_ = eng_data;

  //Line 8
  line_no++;

  if ((vat_type == Utilities::VatTypes::WITH) ||
    (vat_type == Utilities::VatTypes::PARTIAL))
  {   
    line_data = data_in.at(line_no);    
    //VAT, postion 4 or 5
    if (line_data.size() == 6)
    {
      eng_data = line_data.at(5);
    } else
    {
      eng_data = line_data.at(4);
    }
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.vat_ = eng_data;
    line_no++;        
  }

  //Line 9  
  line_data = data_in.at(line_no);

  //Total Cost, postion 2
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);  
  acc_details.total_cost_ = eng_data;

  //Line 11
  line_no = line_no + 2;
  line_data = data_in.at(line_no);
  //Total Consumption, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);  
  acc_details.total_react_pow_con_ = eng_data;

  //Allowed Consumption, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.allowed_react_pow_con_ = eng_data;

  //Power factor, Postion 12
  eng_data = line_data.at(12);
  eng_data = Utilities::ConvertEnglish(eng_data);  
  acc_details.react_power_factor_ = eng_data;

  //Line 15
  line_no = line_no + 4;
  line_data = data_in.at(line_no);
  //Previous Reading, Position 3
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.sub_prev_reading_ = eng_data;

  //TODO: New Current Reading, Position 5
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.sub_curr_reading_ = eng_data;

  if (vat_type == Utilities::VatTypes::PARTIAL)
  {
    line_no++;
    line_data = data_in.at(line_no);    
    //TODO: New Current Reading, Position 5
    eng_data = line_data.at(6);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.sub_curr_reading_ = eng_data;
  }

  //Line 35
  line_no = data_in.size() - 2;
  line_data = data_in.at(line_no);

  //Total Reactive Power Consumption, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_total_react_pow_con_ = eng_data;

  //Multiplication Factor for Reactive Power, Position 2
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);  
  acc_details.mul_react_power_factor_ = eng_data;

  //Previous Reactive Power Meter Reading, Position 4
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reactive_prev_reading_ = eng_data;

  //Current Reactive Power Meter Reading, Position 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reactive_curr_reading_ = eng_data;

  acc_details.block_length_ = data_in.size();

  account_details_.push_back(acc_details);
}
#endif

#if 0

void ParseData::ParseType1(Block data_in)
{    
  Utilities::VatTypes vat_type = Utilities::GetVatType();
  bool type_1_vat = ((vat_type == Utilities::VatTypes::WITH) &&
      (data_in.size() == TYPE_1_BLOCK_LENGTH_VAT));
  bool type_1_non_vat = ((vat_type == Utilities::VatTypes::WITH_OUT) &&
      (data_in.size() == TYPE_1_BLOCK_LENGTH_NON_VAT));
  bool type_1_par_vat = ((vat_type == Utilities::VatTypes::PARTIAL) &&
      (data_in.size() == TYPE_1_BLOCK_LENGTH_PARTIAL_VAT));

  if ((type_1_vat) || (type_1_non_vat) || (type_1_par_vat))
  {
    ParseType12(data_in);
  } else 
  {
    AccountDetails acc_details;

    QStringList line_data;
    QString eng_data;

    int line_no = 2;
    // Line Number 0 and 1 contains header and there is no use.
    // Line Number is 2
    line_data = data_in.at(line_no);

    // Electrometer Number, Position = 0
    eng_data = line_data.at(0);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.electrometer_num_ = eng_data;

    //Type, Position = 1
    eng_data = line_data.at(1);
    int position = eng_data.indexOf("_");
    eng_data = eng_data.mid(position + 1, eng_data.size());
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.type_ = eng_data;

    //SubType, Position = 1
    eng_data = line_data.at(1);
    position = eng_data.indexOf("_");
    eng_data = eng_data.mid(0, position);
    acc_details.sub_type_ = Utilities::ToType(eng_data);

    //Meter Reading To, Position 2, data is Date and written in string
    eng_data = line_data.at(2);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.reading_to_ = Utilities::ToDate(eng_data).trimmed();

    //Meter Reading From, Position 3, data is Date and written in string
    eng_data = line_data.at(3);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.reading_from_ = Utilities::ToDate(eng_data).trimmed();

    //Factor, Position 4
    eng_data = line_data.at(4);
    eng_data = Utilities::ConvertEnglish(eng_data);    
    acc_details.power_factor_ = eng_data;

    //Capacity, Position 5
    eng_data = line_data.at(5);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.capacity_ = eng_data;

    //Account Number, Position 8
    eng_data = line_data.at(8);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.account_num_ = eng_data;

    // HACK: For some cases, the account number is reserved including data
    if (acc_details.account_num_ == 0)
    {
      eng_data = line_data.at(6);
      eng_data = Utilities::ConvertEnglish(eng_data);
      acc_details.account_num_ = eng_data;
    }
    
    //Line No.3
    line_no = 3;
    line_data = data_in.at(line_no);

    //Number Days, postion 0 
    eng_data = line_data.at(0);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.reading_days_ = eng_data;

    //Current Reading, Position 1 
    eng_data = line_data.at(1);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.curr_reading_ = eng_data;

    //Previous Reading, Position 2 
    eng_data = line_data.at(2);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.prev_reading_ = eng_data;

    //Power Consumption, Position 5
    eng_data = line_data.at(5);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.power_consumption_ = eng_data;

    //Power Consumption Cost, postion 6
    eng_data = line_data.at(6);
    eng_data = Utilities::ConvertEnglish(eng_data);    
    acc_details.power_consumption_cost_ = eng_data;

    //Subscription Number, Postion 7
    eng_data = line_data.at(7);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.subscription_num_ = eng_data;
        
    //Line 4
    line_no = 4;
    line_data = data_in.at(line_no);

    //Invoice Date, Position 0, data is Date and written in string
    eng_data = line_data.at(0);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.invoice_date_ = Utilities::ToDate(eng_data);

    //Electrometer Fee, Postion 5
    eng_data = line_data.at(5);
    eng_data = Utilities::ConvertEnglish(eng_data);    
    acc_details.electrometer_fee_ = eng_data;
    
    //Line 5
    line_no = 5;
    line_data = data_in.at(line_no);

    //Inovice Number, Position 0
    eng_data = line_data.at(0);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.invoice_num_ = eng_data;

    //Total Power Consumption Cost, position 5
    eng_data = line_data.at(5);
    eng_data = Utilities::ConvertEnglish(eng_data);    
    acc_details.total_power_cons_cost_ = eng_data;

    //Line 6
    line_no = 6;
    line_data = data_in.at(line_no);

    //Settlement, postion 1
    eng_data = line_data.at(1);
    eng_data = Utilities::ConvertEnglish(eng_data);    
    acc_details.settlement_ = eng_data;

    if ((vat_type == Utilities::VatTypes::WITH) || 
      (vat_type == Utilities::VatTypes::PARTIAL))
    {
      //Line 7
      line_no = 7;
      line_data = data_in.at(line_no);

    
      //VAT, postion 4 or 5
      if (line_data.size() == 6)
      {
        eng_data = line_data.at(5);
      } else
      {
        eng_data = line_data.at(4);
      }
      eng_data = Utilities::ConvertEnglish(eng_data);    
      acc_details.vat_ = eng_data;
      line_no = 8;
    } else
    {
      line_no = 7;
    }

    //Line 8
    
    line_data = data_in.at(line_no);

    //Total Cost, postion 2
    eng_data = line_data.at(2);
    eng_data = Utilities::ConvertEnglish(eng_data);    
    acc_details.total_cost_ = eng_data;
           
    acc_details.block_length_ = data_in.size();

    account_details_.push_back(acc_details);
  }
}

void ParseData::ParseType12(Block data_in)
{
  Utilities::VatTypes vat_type = Utilities::GetVatType();
  AccountDetails acc_details;
  QStringList line_data;
  QString eng_data;
  
  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2
  unsigned int line_no = 2;
  line_data = data_in.at(line_no);

  // Electrometer Number, Position = 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.electrometer_num_ = eng_data;

  //Type, Position = 1
  eng_data = line_data.at(1);
  int position = eng_data.indexOf("_");
  eng_data = eng_data.mid(position + 1, eng_data.size());
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.type_ = eng_data;

  //SubType, Position = 1
  eng_data = line_data.at(1);
  position = eng_data.indexOf("_");
  eng_data = eng_data.mid(0, position);
  acc_details.sub_type_ = Utilities::ToType(eng_data);

  //Meter Reading To, Position 2, data is Date and written in string
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_to_ = Utilities::ToDate(eng_data).trimmed(); 
  
  //Meter Reading From, Position 3, data is Date and written in string
  eng_data = line_data.at(3);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_from_ = Utilities::ToDate(eng_data).trimmed();

  //Factor, Position 4
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);  
  acc_details.power_factor_ = eng_data;

  //Capacity, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.capacity_ = eng_data;

  //Account Number, Position 8
  eng_data = line_data.at(8);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.account_num_ = eng_data;

  // HACK: For some cases, the account number is reserved including data
  if (acc_details.account_num_ == 0)
  {
    eng_data = line_data.at(6);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.account_num_ = eng_data;
  }
  
  //Line No.3
  line_no = 3;
  line_data = data_in.at(line_no);

  //Days, postion 0 
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_days_ = eng_data;

  //Current Reading, Position 1  
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.curr_reading_ = eng_data;

  //Previous Reading, Position 2 
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.prev_reading_ = eng_data;

  //Active Power Consumption, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.power_consumption_ = eng_data;

  //Active Power Consumption Cost, postion 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);   
  acc_details.power_consumption_cost_ = eng_data;

  //Subscription Number, Postion 7
  eng_data = line_data.at(7);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.subscription_num_ = eng_data;
  
  //Line 4
  line_no = 4;
  line_data = data_in.at(line_no);

  //TODO: Give a name, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_curr_reading_ = eng_data;

  //TODO: Give a name, Position 1 
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_prev_reading_ = eng_data;
  
  //Reactive Power Consumption, Position 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_pow_cons_ = eng_data;

  //Reactive Power Consumption Cost, Position 7
  eng_data = line_data.at(7);
  eng_data = Utilities::ConvertEnglish(eng_data);   
  acc_details.other_pow_cons_cost_ = eng_data;

  //Line 5
  line_no = 5;
  line_data = data_in.at(line_no);

  //Invoice Date, Position 0, data is Date and written in string
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_date_ = Utilities::ToDate(eng_data).trimmed();

  //Electrometer Fee, Postion 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);   
  acc_details.electrometer_fee_ = eng_data;
  
  //Line 6
  line_no = 6;
  line_data = data_in.at(line_no);

  //Inovice Number, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_num_ = eng_data;

  //Total Power Consumption Cost, position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);    
  acc_details.total_power_cons_cost_ = eng_data;

  //Line 7
  line_no = 7;
  line_data = data_in.at(line_no);

  //Settlement, postion 1
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);    
  acc_details.settlement_ = eng_data;

  if ((vat_type == Utilities::VatTypes::WITH) ||
    (vat_type == Utilities::VatTypes::PARTIAL))
  {   
    //Line 8
    line_no = 8;
    line_data = data_in.at(line_no);

    //VAT, postion 2
    eng_data = line_data.at(4);
    eng_data = Utilities::ConvertEnglish(eng_data);    
    acc_details.vat_ = eng_data;
    line_no = 9;
  } else 
  {
    //Line 8
    line_no = 8;
  }

  //Line 9  
  line_data = data_in.at(line_no);

  //Total Cost, postion 2
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);  
  acc_details.total_cost_ = eng_data;

  //Line 11
  line_no = line_no + 2;
  line_data = data_in.at(line_no);
  //Total Consumption, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);  
  acc_details.total_react_pow_con_ = eng_data;

  //Allowed Consumption, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.allowed_react_pow_con_ = eng_data;
  
  //Power factor, Postion 12
  eng_data = line_data.at(12);
  eng_data = Utilities::ConvertEnglish(eng_data);  
  acc_details.react_power_factor_ = eng_data;

  //Line 15
  line_no = line_no + 4;
  line_data = data_in.at(line_no);
  //Previous Reading, Position 3
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.sub_prev_reading_ = eng_data;

  //TODO: New Current Reading, Position 5
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.sub_curr_reading_ = eng_data;

  if (vat_type == Utilities::VatTypes::PARTIAL)
  {
    line_no++;
    line_data = data_in.at(line_no);    
    //TODO: New Current Reading, Position 5
    eng_data = line_data.at(6);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.sub_curr_reading_ = eng_data;
  }

  //Line 35
  line_no = data_in.size() - 2;
  line_data = data_in.at(line_no);

  //Total Reactive Power Consumption, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.other_total_react_pow_con_ = eng_data;

  //Multiplication Factor for Reactive Power, Position 2
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);  
  acc_details.mul_react_power_factor_ = eng_data;

  //Previous Reactive Power Meter Reading, Position 4
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reactive_prev_reading_ = eng_data;

  //Current Reactive Power Meter Reading, Position 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reactive_curr_reading_ = eng_data;
    
  acc_details.block_length_ = data_in.size();

  account_details_.push_back(acc_details);
}

void ParseData::ParseType5(Block data_in)
{ 
  Utilities::VatTypes vat_type = Utilities::GetVatType();
  unsigned int  block_size = data_in.size();
    
  bool type_5_vat = ((vat_type == Utilities::VatTypes::WITH) &&
    (block_size == TYPE_5_BLOCK_LENGTH_VAT));
  bool type_5_non_vat = ((vat_type == Utilities::VatTypes::WITH_OUT) &&
    (block_size == TYPE_5_BLOCK_LENGTH_NON_VAT));
  bool type_5_par_vat = ((vat_type == Utilities::VatTypes::PARTIAL) &&
    (block_size == TYPE_5_BLOCK_LENGTH_PARTIAL_VAT));
  bool type_5_non_vat_an = ((vat_type == Utilities::VatTypes::WITH_OUT) &&
    (block_size == TYPE_5_BLOCK_LENGTH_NON_VAT_ANOTHER));



  if ((type_5_vat) || (type_5_non_vat) || (type_5_par_vat) || (type_5_non_vat_an))
  { 
    ParseType1(data_in);
  } else
  {
#if 0  
    AccountDetails acc_details;

    QStringList line_data;
    QString eng_data;

    // Line Number 0 and 1 contains header and there is no use.
    // Line Number is 2
    line_data = data_in.at(2);

    // Electrometer Number, Position = 0
    eng_data = line_data.at(0);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.electrometer_num_ = eng_data.toUInt();

    //Type, Position = 1
    eng_data = line_data.at(1);
    int position = eng_data.indexOf("_");
    eng_data = eng_data.mid(position + 1, eng_data.size());
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.type_ = eng_data.toUInt();

    //Meter Reading To, Position 2, data is Date and written in string
    eng_data = line_data.at(2);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.reading_to_ = eng_data;

    //Meter Reading From, Position 3, data is Date and written in string
    eng_data = line_data.at(3);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.reading_from_ = eng_data;

    //Factor, Position 4
    eng_data = line_data.at(4);
    eng_data = Utilities::ConvertEnglish(eng_data);    
    acc_details.factor_ = eng_data.toFloat();

    //Capacity, Position 5
    eng_data = line_data.at(5);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.capacity_ = eng_data.toUInt();

    //Account Number, Position 8
    eng_data = line_data.at(8);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.account_num_ = eng_data.toULongLong();

    //Line No.3
    line_data = data_in.at(3);

    //Days, postion 0 
    eng_data = line_data.at(0);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.reading_days_ = eng_data.toUInt();

    //Current Reading, Position 1 
    eng_data = line_data.at(1);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.curr_reading_ = eng_data.toFloat();
    
    //Previous Reading, Position 2 
    eng_data = line_data.at(2);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.prev_reading_ = eng_data.toFloat();

    //Active Power Consumption, Position 5
    eng_data = line_data.at(5);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.active_pow_cons_ = eng_data.toFloat();

    //Active Power Consumption Cost, postion 6
    eng_data = line_data.at(6);
    eng_data = Utilities::ConvertEnglish(eng_data);    
    acc_details.active_pow_cons_cost_ = eng_data.toFloat();

    //Subscription Number, Postion 7
    eng_data = line_data.at(7);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.subscription_num_ = eng_data.toULongLong();

    //Line 4
    line_data = data_in.at(4);

    //Invoice Date, Position 0, data is Date and written in string
    eng_data = line_data.at(0);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.invoice_date_ = eng_data;

    //Electrometer Fee, Postion 5
    eng_data = line_data.at(5);
    eng_data = Utilities::ConvertEnglish(eng_data);   
    acc_details.electrometer_fee_ = eng_data.toFloat();


    //Line 5
    line_data = data_in.at(5);

    //Inovice Number, Position 0
    eng_data = line_data.at(0);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.invoice_num_ = eng_data.toULongLong();

    //Total Power Consumption Cost, position 5
    eng_data = line_data.at(5);
    eng_data = Utilities::ConvertEnglish(eng_data);    
    acc_details.total_cons_cost_ = eng_data.toFloat();

    //Line 6
    line_data = data_in.at(6);

    //Settlement, postion 1
    eng_data = line_data.at(1);
    eng_data = Utilities::ConvertEnglish(eng_data);    
    acc_details.settlement_ = eng_data.toFloat();

    //Line 7
    line_data = data_in.at(7);

    //VAT, postion 4
    eng_data = line_data.at(4);
    eng_data = Utilities::ConvertEnglish(eng_data);
    eng_data = Utilities::ToFloat(eng_data);
    acc_details.vat_ = eng_data.toFloat();

    //Line 8
    line_data = data_in.at(8);

    //Total Cost, postion 2
    eng_data = line_data.at(2);
    eng_data = Utilities::ConvertEnglish(eng_data);
    eng_data = Utilities::ToFloat(eng_data);
    acc_details.total_cost_ = eng_data.toFloat();

    acc_details.block_length_ = data_in.size();

    account_details_.push_back(acc_details);  
#endif
  }
}
#endif