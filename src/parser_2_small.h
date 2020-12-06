#pragma once

#include <iostream>

#include "common_types.h"
#include "account_details.h"

class Parser2Small
{
public:
  Parser2Small();
  ~Parser2Small();

  void Parse(Block data_in, AccountDetails* acc_details);
};
