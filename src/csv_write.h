#ifndef CSV_WRITE_H_
#define CSV_WRITE_H_

#include <iostream>
#include <vector>

#include <QtCore\QString>

#include "account_details.h"

using namespace std;

class CsvWrite
{
 public:
  CsvWrite();
  CsvWrite(QString file_name);
  ~CsvWrite();
  void Write(int type);
  void Write();
  void SetBaseFileName(QString file_name);  

 private:
  void WriteResidential(int type);
  void WriteIndustrial(int type);
  void WriteParser1();
  void WriteParser1_5();
  void WriteParser2();
  void Parser1Small();
  void Parser1Big();  
  void Parser2Big(std::vector<AccountDetails> data, QString file_name);
  void Parser2Small(std::vector<AccountDetails> data, QString file_name);
  void WriteParser3();
  void WriteParser4();

  QString file_name_;
  QString base_file_name_;
};

#endif //CSV_WRITE_H_