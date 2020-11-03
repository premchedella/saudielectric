#pragma once

#include <iostream>

#include "common_types.h"
#include "account_details.h"

class Parser1Big
{
public:
  Parser1Big();
  ~Parser1Big();

  void Parse(Block data_in, AccountDetails* acc_details);
};
