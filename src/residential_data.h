#ifndef RESIDENTIAL_DATA_H_
#define RESIDENTIAL_DATA_H_

#include <iostream>

#include "common_types.h"
#include "account_details.h"

class ResidentialData
{
 public:
   ResidentialData();
   ~ResidentialData();

  void FormData(Blocks data);
  std::vector<AccountDetails> GetDataInfo();


 private:
  std::vector<AccountDetails> account_details_;
};

#endif //RESIDENTIAL_DATA_H_

