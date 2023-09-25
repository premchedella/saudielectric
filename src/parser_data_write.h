#ifndef PARSER_DATA_WRITE_H_
#define PARSER_DATA_WRITE_H_

#include <iostream>
#include <vector>

#include <QtCore\QString>


using namespace std;

class ParserDataWrite
{
 public:
 
   enum ParserDataWriteTypes
   {
     PARSER_DATA_WRITE_BIGGER = 0,
     PARSER_DATA_WRITE_SMALLER,
     PARSER_DATA_WRITE_SUMMARY
   };

  ParserDataWrite();  
  ~ParserDataWrite();
  void SetBaseFileName(QString file_name);
  void Write(ParserDataWriteTypes type);

  QString GetFileName();
  

 private:  
  virtual void WriteBiggerData();
  virtual void WriteSmallerData();
  virtual void WriteSummaryData();

  QString file_name_;  
};

#endif //PARSER_DATA_WRITE_H_