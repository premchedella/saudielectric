#ifndef TYPE_1_PARSER_H_
#define TYPE_1_PARSER_H_

#include <iostream>

#include "common_types.h"
#include "account_details.h"

class Type1Parser
{
 public:
  Type1Parser();
  ~Type1Parser();

  void Parse(Block data_in, AccountDetails* acc_details);

 private:
  void VatParse(Block data_in, AccountDetails* acc_details);
  void ParVatParse(Block data_in, AccountDetails* acc_details);
  void NonVatParse(Block data_in, AccountDetails* acc_details);

  void VatParseSmall(Block data_in, AccountDetails* acc_details);
  void VatParseLarge(Block data_in, AccountDetails* acc_details);

  void ParVatParseSmall(Block data_in, AccountDetails* acc_details);
  void ParVatParseLarge(Block data_in, AccountDetails* acc_details);
  
  void NonVatParseSmall(Block data_in, AccountDetails* acc_details);
  void NonVatParseLarge(Block data_in, AccountDetails* acc_details);  
};
#endif // TYPE_1_PARSER_H_
