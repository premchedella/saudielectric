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
  QString file_name_;

  void WriteResidential(int type);
  void WriteIndustrial(int type);
};

#endif //CSV_WRITE_H_