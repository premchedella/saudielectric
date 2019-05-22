#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <iostream>

#include <QtCore\QString>

#include "common_types.h"

class Utilities
{
 public:
  enum VatTypes
  {
    WITH_OUT = 0,
    WITH = 1,
    PARTIAL = 2
  };

  enum InputFileTypes
  {
    KAU1_MAIN = 0,
    KAU1_BRANCH,
    KAU2_MAIN
  };

  static QString ConvertEnglish(QString arabic);  
  static QString ToFloat(QString arabic);
  static QString ToDate(QString mmddyyy); 
  static QString ToDate(QString mmddyyy, QChar sep);
  static QString ToGregorian(QString arabic);
  static QString ToDot(QString value);
  static QString ToType(QString arabic);
  static void SetVatType(VatTypes type);
  static VatTypes GetVatType();
  static void SetFileType(InputFileTypes type);
  static InputFileTypes GetFileType();
  static Line Convert(QStringList data);

 private:
  static VatTypes vat_type_;
  static InputFileTypes file_type_;
};

#endif //UTILITIES_H_