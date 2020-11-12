#ifndef CSV_WRITE_H_
#define CSV_WRITE_H_

#include <iostream>

#include <QtCore\QString>

class CsvWrite
{
 public:
   CsvWrite(QString file_name);
   ~CsvWrite();
  void Write(int type);
  void Write();

 private:
  void WriteResidential(int type);
  void WriteIndustrial(int type);
  void Parser1Small();
  void Parser1Big();

  QString file_name_;
};

#endif //CSV_WRITE_H_