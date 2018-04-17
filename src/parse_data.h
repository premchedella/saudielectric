#ifndef PARSE_DATA_H_
#define PARSE_DATA_H_

#include <iostream>

#include "common_types.h"
#include "account_details.h"

class ParseData
{
 public:
   ParseData();
   ~ParseData();

  void FormData(Blocks data);
  static std::vector<unsigned int> GetTypes();
  static std::vector<AccountDetails> GetDataInfo();  
  static std::vector<AccountDetails> GetDataInfo(unsigned int type);

 private:
  void ParseType1(Block data_in);
  void ParseType12(Block data_in);
  void ParseType5(Block data_in);
  static std::vector<AccountDetails> account_details_;
  static std::vector<AccountDetails> type_account_details_;
  static std::vector<unsigned int> types_;
};

#endif //PARSE_DATA_H_

