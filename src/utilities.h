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

  enum ParserTypes
  {
    PARSER_TYPE_0 = 0, 
    PARSER_TYPE_1,
    PARSER_TYPE_1_5,  //Mix of Parser 1 and Parser 2
    PARSER_TYPE_2,
    PARSER_TYPE_3 // Generate out files based on the data
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
  static bool IsOtherFees(QStringList data);
  static bool IsOtherFees();
  static void SetParserType(ParserTypes parser_type);
  static ParserTypes GetParserType();  
  static QString ToDateMonth(QString mmddyyyy);
  static bool Is5and15Vat(Block data);
  static bool IsExtraWord();
  static void SetExtraWord(bool flag);
  
 private:
  static VatTypes vat_type_;
  static InputFileTypes file_type_;
  static bool is_other_fees_;
  static ParserTypes parser_type_;
  static QStringList months;
  static bool is_extra_word_;
};

#endif //UTILITIES_H_