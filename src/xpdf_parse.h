#ifndef XPDF_PARSE_H_
#define XPDF_PARSE_H_

#include <iostream>
#include <QtCore\QObject>

#include "common_types.h"

class XPdfParse : public QObject
{
  Q_OBJECT

 public:

  XPdfParse(const QString file_name);
  ~XPdfParse();

  void Parse();    
  Blocks GetBlocks();
  unsigned int GetTotalInvoices();

 private:    
  void PrintCommands(QString exe_name, QStringList arguments);
  void PreDirCheck();
  void PdftoText(QString out_file);
  QStringList ReadTextFile(QString file_name);
  QStringList RemoveWhiteSpaces(QStringList data_in);
  QStringList RemoveHeaderFooter(QStringList data_in);  
  Block ConvertData(QStringList data_in);
  Block RemoveSingleValueZero(Block data_in);  
  Blocks GetBlocks(Block data_in);

  QString in_file_name_;  
  Blocks data_blocks_;
  unsigned int total_invoices_;
};

#endif //XPDF_PARSE_H_
