#pragma once

#include <iostream>

#include "common_types.h"
#include "account_details.h"

class Parser1Small
{
public:
  Parser1Small();
  ~Parser1Small();

  void Parse(Block data_in, AccountDetails* acc_details);
};
