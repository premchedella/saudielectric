#pragma once

#include <iostream>

#include "common_types.h"
#include "account_details.h"

class Parser2Big
{
public:
  Parser2Big();
  ~Parser2Big();

  void Parse(Block data_in, AccountDetails* acc_details);
};
