#pragma once

#include <iostream>
#include <vector>

#include <QtCore\QString>

#include "parser_data_write.h"

using namespace std;

class Parser4WriteData: public ParserDataWrite

{
 public:  

  Parser4WriteData();
  ~Parser4WriteData();
  void WriteInvoiceData();  
  

 private:  
  virtual void WriteBiggerData();
  virtual void WriteSmallerData();
  virtual void WriteSummaryData();
  
};
