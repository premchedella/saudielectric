#ifndef PARSER_DATA_3_WRITE_H_
#define PARSER_DATA_3_WRITE_H_

#include <iostream>
#include <vector>

#include <QtCore\QString>

#include "parser_data_write.h"
#include "parse_summary.h"

using namespace std;

class ParserData3Write: public ParserDataWrite

{
 public:  

  ParserData3Write();
  ~ParserData3Write();  
  

 private:  
  virtual void WriteBiggerData();
  virtual void WriteSmallerData();
  virtual void WriteSummaryData();
  
};

#endif //PARSER_DATA_3_WRITE_H_