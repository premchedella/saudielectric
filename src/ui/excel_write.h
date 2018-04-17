#ifndef EXCEL_WRITE_H_
#define EXCEL_WRITE_H_

#include <iostream>

#include <QtCore\QString>

class ExcelWrite
{
 public:
  ExcelWrite(QString file_name);

  ~ExcelWrite();

  void Write(int type);
  void WriteBlocks();

 private:
  QString file_name_;
};

#endif //EXCEL_WRITE_H_