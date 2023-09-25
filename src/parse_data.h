#ifndef PARSE_DATA_H_
#define PARSE_DATA_H_

#include <iostream>

#include "common_types.h"
#include "account_details.h"

class ParseData
{
 public:
  enum AccountTypes
  {
    DEFAULT = 0,
    SMALLER = 1,
    BIGGER = 2
  };

  ParseData();
  ~ParseData();

  void FormData(Blocks data);
  static std::vector<unsigned int> GetTypes();
  static std::vector<AccountDetails> GetDataInfo(ParseData::AccountTypes type = ParseData::AccountTypes::DEFAULT);
  static std::vector<AccountDetails> GetDataInfo(unsigned int type);

 private:
  void ParserType0(Blocks data);
  void ParserType1(Blocks data);
  void ParserType1_5(Blocks data);
  void ParserType2(Blocks data);
  void ParserType3(Blocks data);
  void ParserType4(Blocks data);
  void ParserType1Small(Blocks data);
  void ParserType1Big(Blocks data);
  void ParserType1_5Small(Blocks data);
  void ParserType1_5Big(Blocks data);
  void ParserType2Small(Blocks data);
  void ParserType2Big(Blocks data);

  void ParseType1(Block data_in, AccountDetails* acc_details);
  void ParseType12(Block data_in, AccountDetails* acc_details);
  void ParseType5(Block data_in, AccountDetails* acc_details);

  bool IsBigInvoice(Block data_block);
  
  static std::vector<AccountDetails> account_details_;
  static std::vector<AccountDetails> bigger_account_details_;
  static std::vector<AccountDetails> smaller_account_details_;
  static std::vector<AccountDetails> type_account_details_;
  static std::vector<unsigned int> types_;

};

#endif //PARSE_DATA_H_

