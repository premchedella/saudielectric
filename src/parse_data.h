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
  void VatParseType1(Block data_in);
  void VatParseType5(Block data_in);
  void VatParseType12(Block data_in);
  void NonVatParseType1(Block data_in);
  void NonVatParseType5(Block data_in);
  void NonVatParseType12(Block data_in);
  void ParVatParseType1(Block data_in);
  void ParVatParseType5(Block data_in);
  void ParVatParseType12(Block data_in);
  void VatParseType1Small(Block data_in);
  void VatParseType1Large(Block data_in);
  void NonVatParseType1Small(Block data_in);
  void NonVatParseType1Large(Block data_in);
  void ParVatParseType1Small(Block data_in);
  void ParVatParseType1Large(Block data_in);

  static std::vector<AccountDetails> account_details_;
  static std::vector<AccountDetails> type_account_details_;
  static std::vector<unsigned int> types_;
  
};

#endif //PARSE_DATA_H_

