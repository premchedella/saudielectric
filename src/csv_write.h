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

 private:
  void WriteResidential(int type);
  void WriteIndustrial(int type);

  QString file_name_;
};

#endif //CSV_WRITE_H_