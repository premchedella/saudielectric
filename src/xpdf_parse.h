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
  void ParseSummary();
  Blocks GetBlocks();
  unsigned int GetTotalInvoices();
  Block GetSummary();

 private:    
  void PrintCommands(QString exe_name, QStringList arguments);
  void PreDirCheck();
  void PdftoText(QString out_file);
  void SummarytoText(QString out_file);
  QStringList ReadTextFile(QString file_name);
  QStringList RemoveWhiteSpaces(QStringList data_in);
  QStringList RemoveHeaderFooter(QStringList data_in);  
  Block ConvertData(QStringList data_in);
  Block RemoveSingleValueZero(Block data_in);  
  Blocks GetBlocks(Block data_in);
  Blocks GetBlocksParser1(Block data_in);
  unsigned int GetStartPage();
  Block GetPageData(int page_no);
 
  QString in_file_name_;  
  Blocks data_blocks_;
  unsigned int total_invoices_;
  Block summary_data_;
};

#endif //XPDF_PARSE_H_
