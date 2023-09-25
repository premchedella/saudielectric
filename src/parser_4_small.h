#pragma once

#include <iostream>

#include "common_types.h"
#include "account_details.h"

class Parser4Small
{
public:
  Parser4Small();
  ~Parser4Small();

  void Parse(Block data_in, AccountDetails* acc_details);
};
