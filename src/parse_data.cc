#include "parse_data.h"

#include <algorithm>    // std::find

#include "utilities.h"
#include "type_1_parser.h"
#include "type_5_parser.h"
#include "type_12_parser.h"
#include "parser_1_small.h"
#include "parser_1_big.h"
#include "parser_2_small.h"
#include "parser_2_big.h"
#include "parser_4_big.h"
#include "parser_4_small.h"

std::vector<AccountDetails> ParseData::account_details_;
std::vector<AccountDetails> ParseData::bigger_account_details_;
std::vector<AccountDetails> ParseData::smaller_account_details_;
std::vector<unsigned int> ParseData::types_;

ParseData::ParseData()
{

}

ParseData::~ParseData()
{

}

void ParseData::FormData(Blocks data)
{
#if DEBUG  
  std::cout << "Total Number of Blocks = " << data.size() << std::endl;
#endif

  account_details_.clear();
  types_.clear();

  Utilities::ParserTypes parser_type = Utilities::GetParserType();

  switch (parser_type)
  {
    case Utilities::ParserTypes::PARSER_TYPE_0:
      ParserType0(data);
      break;
    case Utilities::ParserTypes::PARSER_TYPE_1:
      ParserType1(data);
      break;
    case Utilities::ParserTypes::PARSER_TYPE_1_5:
      ParserType1_5(data);
      break;
    case Utilities::ParserTypes::PARSER_TYPE_2:
      ParserType2(data);
      break;    
    case Utilities::ParserTypes::PARSER_TYPE_3:
      ParserType3(data);
      break;
    case Utilities::ParserTypes::PARSER_TYPE_4:
      ParserType4(data);
      break;
    default:
      break;
  }  
}

std::vector<unsigned int> ParseData::GetTypes()
{
  return types_;
}

std::vector<AccountDetails> ParseData::GetDataInfo(
  ParseData::AccountTypes type)
{
  if (type == ParseData::AccountTypes::SMALLER)
    return smaller_account_details_;
  else if (type == ParseData::AccountTypes::BIGGER)
    return bigger_account_details_;
  else
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

void ParseData::ParserType0(Blocks data)
{
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
        acc_details.parsing_ = "Partial";
        acc_details.reason_ = "Type is not avaialble.";
      }
      account_details_.push_back(acc_details);
    }
    catch (...)
    {
      acc_details.parsing_ = "Partial";
      acc_details.reason_ = "Type is not avaialble.";
    }
  }
}

void ParseData::ParserType1(Blocks data)
{
  Utilities::InputFileTypes file_type = Utilities::GetFileType();
  if (file_type == Utilities::InputFileTypes::KAU2_MAIN)
  {
    ParserType1Small(data);
  } else
  {
    ParserType1Big(data);
  }
}

void ParseData::ParserType1_5(Blocks data)
{
  Utilities::InputFileTypes file_type = Utilities::GetFileType();
  if (file_type == Utilities::InputFileTypes::KAU2_MAIN)
  {
    ParserType1_5Small(data);
  } else
  {
    ParserType1_5Big(data);
  }
}

void ParseData::ParserType2(Blocks data)
{
  Utilities::InputFileTypes file_type = Utilities::GetFileType();
  if (file_type == Utilities::InputFileTypes::KAU2_MAIN)
  {
    ParserType2Small(data);
  } else
  {
    ParserType2Big(data);
  }
}

void ParseData::ParserType3(Blocks data)
{  
  for (unsigned int index = 0; index < data.size(); index++)
  {    
    // Get the each block data (invoice data)
    Block data_block = data.at(index);
    bool is_big_invoice = IsBigInvoice(data_block);
   
    if (is_big_invoice)
    {
      AccountDetails acc_details;
      acc_details.parsing_ = "Completed";

      Parser2Big parser_2_big;
      parser_2_big.Parse(data_block, &acc_details);

      bigger_account_details_.push_back(acc_details);
    } else
    {
      AccountDetails acc_details;
      acc_details.parsing_ = "Completed";

      Parser2Small parser_2_small;
      parser_2_small.Parse(data_block, &acc_details);

      smaller_account_details_.push_back(acc_details);    
    }    
  }  
}

void ParseData::ParserType4(Blocks data)
{
  for (unsigned int index = 0; index < data.size(); index++)
  {
    // Get the each block data (invoice data)
    Block data_block = data.at(index);

    bool is_big_invoice = IsBigInvoice(data_block);

    if (is_big_invoice)
    {
      AccountDetails acc_details;
      acc_details.parsing_ = "Completed";

      Parser4Big parser_4_big;
      parser_4_big.Parse(data_block, &acc_details);

      bigger_account_details_.push_back(acc_details);
    } else
    {
      AccountDetails acc_details;
      acc_details.parsing_ = "Completed";

      Parser4Small parser_4_small;
      parser_4_small.Parse(data_block, &acc_details);

      smaller_account_details_.push_back(acc_details);
    }
  }
}

void ParseData::ParserType1Small(Blocks data)
{  
  for (unsigned int index = 0; index < data.size(); index++)
  {
    Block data_block = data.at(index);

    AccountDetails acc_details;
    acc_details.parsing_ = "Completed";
    
    Parser1Small parser_1_small;
    parser_1_small.Parse(data_block, &acc_details);

    account_details_.push_back(acc_details);
  }
}

void ParseData::ParserType1Big(Blocks data)
{
  for (unsigned int index = 0; index < data.size(); index++)
  {
    Block data_block = data.at(index);

    AccountDetails acc_details;
    acc_details.parsing_ = "Completed";

    Parser1Big parser_1_big;
    parser_1_big.Parse(data_block, &acc_details);

    account_details_.push_back(acc_details);
  }
}

void ParseData::ParserType1_5Small(Blocks data)
{  
  for (unsigned int index = 0; index < data.size(); index++)
  {
    Block data_block = data.at(index);

    AccountDetails acc_details;
    acc_details.parsing_ = "Completed";    

    if (Utilities::Is5and15Vat(data_block))
    {
      Parser1Small parser_1_small;
      parser_1_small.Parse(data_block, &acc_details);
    } else
    {
      Parser2Small parser_2_small;
      parser_2_small.Parse(data_block, &acc_details);      
    }    

    account_details_.push_back(acc_details);
  }
}

void ParseData::ParserType1_5Big(Blocks data)
{
  for (unsigned int index = 0; index < data.size(); index++)
  {
    Block data_block = data.at(index);

    AccountDetails acc_details;
    acc_details.parsing_ = "Completed";

    if (Utilities::Is5and15Vat(data_block))
    {
      Parser1Big parser_1_big;
      parser_1_big.Parse(data_block, &acc_details);
    } else
    {
      Parser2Big parser_2_big;
      parser_2_big.Parse(data_block, &acc_details);
    }

    account_details_.push_back(acc_details);
  }
}

void ParseData::ParserType2Small(Blocks data)
{  
  for (unsigned int index = 0; index < data.size(); index++)
  {
    Block data_block = data.at(index);

    AccountDetails acc_details;
    acc_details.parsing_ = "Completed";    

    Parser2Small parser_2_small;
    parser_2_small.Parse(data_block, &acc_details);

    account_details_.push_back(acc_details);
  }
}

void ParseData::ParserType2Big(Blocks data)
{  
  for (unsigned int index = 0; index < data.size(); index++)
  {
    Block data_block = data.at(index);    

    AccountDetails acc_details;
    acc_details.parsing_ = "Completed";

    Parser2Big parser_2_big;
    parser_2_big.Parse(data_block, &acc_details);

    account_details_.push_back(acc_details);
  }
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

bool ParseData::IsBigInvoice(Block data_block)
{
  bool is_big_invoice = false;
  int line_no = data_block.size() - 5;

  QString big_invoice_data = QStringLiteral(BIG_INVOICE_CONTAINS);
  QString big_invoice_data_1 = QStringLiteral(BIG_INVOICE_CONTAINS_1);
  QString  line_data = data_block.at(line_no).join(" ");
  bool is_big = line_data.contains(big_invoice_data);

  if (is_big)
  {
    is_big_invoice = true;
  } else
  {
    /* In some cases, there is an extra line.*/
    line_no = data_block.size() - 6;
    line_data = data_block.at(line_no).join(" ");
    is_big = line_data.contains(big_invoice_data);
    if (is_big)
    {
      is_big_invoice = true;
    } else
    {
      /* In some cases, there are two meter readings.*/
      line_no = data_block.size() - 7;
      line_data = data_block.at(line_no).join(" ");
      is_big = line_data.contains(big_invoice_data);
      if (is_big)
      {
        is_big_invoice = true;
      } else
      {
        /* In some cases, there are two meter readings.*/
        line_no = data_block.size() - 8;
        line_data = data_block.at(line_no).join(" ");
        is_big = line_data.contains(big_invoice_data);
        if (is_big)
        {
          is_big_invoice = true;
        } else
        {
          line_no = data_block.size() - 6;
          line_data = data_block.at(line_no).join(" ");
          is_big = line_data.contains(big_invoice_data_1);
          if (is_big)
          {
            is_big_invoice = true;
          }
        }
      }
    }
  }

  return is_big_invoice;
}

#if 0

void ParseData::ParserType1(Blocks data)
{
  std::vector<unsigned int> block_lengths;

  for (unsigned int index = 0; index < data.size(); index++)
  {
    Block data_block = data.at(index);


    std::vector<unsigned int>::iterator it;

    it = std::find(block_lengths.begin(), block_lengths.end(), data_block.size());
    if (it == block_lengths.end())
    {
      block_lengths.push_back(data_block.size());
    } else
    {
      continue;
    }


    AccountDetails acc_details;
    acc_details.parsing_ = "Completed";


    if (data_block.size() <= PARSER_1_SMALLER_LENGTH)
    {
      // Parse Small
      Parser1Small parser_1_small;
      parser_1_small.Parse(data_block, &acc_details);
    } else
    {
      // Parse Large
      Parser1Big parser_1_big;
      parser_1_big.Parse(data_block, &acc_details);
    }

    account_details_.push_back(acc_details);
  }
}

#endif
