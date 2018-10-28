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
  void Generate(const QString file_name);
  void GenerateBlocks(const QString file_name);
  void GenerateExcel(const QString file_name);
  void GeneratePdftoExcel(const QString file_name);
  unsigned int GetBlockLength();
  Blocks GetBlocks();
  unsigned int GetTotalInvoices();

 private:
  
  typedef std::vector<Block*> PBlocks;
  typedef std::vector<int> Positions;
  
  void WriteExcel(const QString file_name, QStringList data);
  void WriteExcel(const QString file_name, std::vector<QStringList> data);
  void LineSplit(QString data, QStringList& words);
  void CopyWords(QStringList src, QStringList& dest, Positions src_pos,
      Positions dest_pos);
  std::vector<QStringList> GetHeader();
  bool DeleteDir(QString dir_name);
  void GenerateTextFile(QString exe_name, QString input_file, QString output_file);
  void PrintCommands(QString exe_name, QStringList arguments);
  void PreDirCheck();
  void PdftoText(QString out_file);

  QStringList ReadTextFile(QString file_name);
  QStringList RemoveWhiteSpaces(QStringList data_in);
  QStringList RemoveHeaderFooter(QStringList data_in);  
  Block ConvertData(QStringList data_in);
  Block RemoveSingleValueZero(Block data_in);
  void GenerateBlockLength(Block data_in);
  Block RemoveHardles(Block data_in);
  Block RemoveIndustryHardles(Block data_in);
  Blocks GetBlocks(Block data_in);

  QString in_file_name_;
  unsigned int block_length_;
  Blocks data_blocks_;
  unsigned int total_invoices_;
};

#endif //XPDF_PARSE_H_
