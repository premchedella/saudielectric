#include "parse_data.h"

#include <algorithm>    // std::find

#include "utilities.h"
#include "type_1_parser.h"
#include "type_5_parser.h"
#include "type_12_parser.h"

std::vector<AccountDetails> ParseData::account_details_;
std::vector<unsigned int> ParseData::types_;

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

    AccountDetails acc_details;
    acc_details.parsing_ = "Completed";

    QStringList line_data = data_block.at(2);

    try
    {
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

      switch (type)
      {
      case 1:
        ParseType1(data_block, &acc_details);
        break;
      case 5:
        ParseType5(data_block, &acc_details);
        break;
      case 12:
        ParseType12(data_block, &acc_details);
        break;
      default:
        std::cout << "Not a valid Type = " << type << std::endl;
        acc_details.parsing_ = "Partial";
        acc_details.reason_ = "Type is not avaialble.";
      }
      account_details_.push_back(acc_details);
    } catch (...)
    {
      acc_details.parsing_ = "Partial";
      acc_details.reason_ = "Type is not avaialble.";
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

void ParseData::ParseType1(Block data_in, AccountDetails* acc_details)
{  
  Type1Parser type_1_parser;
  type_1_parser.Parse(data_in, acc_details);  
}

void ParseData::ParseType5(Block data_in, AccountDetails* acc_details)
{  
  Type5Parser type_5_parser;
  type_5_parser.Parse(data_in, acc_details); 
}

void ParseData::ParseType12(Block data_in, AccountDetails* acc_details)
{  
  Type12Parser type_12_parser;
  type_12_parser.Parse(data_in, acc_details);  
}
