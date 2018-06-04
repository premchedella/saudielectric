#ifndef TYPE_12_PARSER_H_
#define TYPE_12_PARSER_H_

#include <iostream>

#include "common_types.h"
#include "account_details.h"

class Type12Parser
{
 public:
  Type12Parser();
  ~Type12Parser();

  void Parse(Block data_in, AccountDetails* acc_details);

 private:
  void VatParse(Block data_in, AccountDetails* acc_details);
  void ParVatParse(Block data_in, AccountDetails* acc_details);
  void NonVatParse(Block data_in, AccountDetails* acc_details); 
};
#endif // TYPE_12_PARSER_H_
