#pragma once

#include <iostream>

#include "common_types.h"
#include "account_details.h"

class Parser4Big
{
public:
  Parser4Big();
  ~Parser4Big();

  void Parse(Block data_in, AccountDetails* acc_details);
};
