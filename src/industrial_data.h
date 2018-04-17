#ifndef INDUSTRIAL_DATA_H_
#define INDUSTRIAL_DATA_H_

#include <iostream>

#include "common_types.h"
#include "account_details.h"

class IndustrialData
{
 public:
  IndustrialData();
  ~IndustrialData();

  void FormData(Blocks data);
  std::vector<AccountDetails> GetDataInfo();


 private:
  std::vector<AccountDetails> account_details_;
};

#endif //INDUSTRIAL_DATA_H_

