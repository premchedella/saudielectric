#pragma once

#include <iostream>

#include "common_types.h"

class Summary4Data
{
public:
  Summary4Data();
  ~Summary4Data();
    
  QString name_;
  QString value_;
  QString complete_;
  QString reason_;
};

class Parser4Summary
{
 public: 

   Parser4Summary();
  ~Parser4Summary();

  void ParseData(Block data);  
  static std::vector<Summary4Data> GetSummaryData();
  
 private:

  void AddSummaryData(QString name, QString value, QString complete, QString reason);
  void ParseLine1(QStringList data);
  void ParseLine2(QStringList data);
  void ParseLine3(QStringList data);
  void ParseLine4(QStringList data);
  void ParseLine10(QStringList data);
  void ParseLine11(QStringList data);
  void ParseLine12(QStringList data);
  void ParseLine13(QStringList data);
  void ParseLine14(QStringList data);
  
  static std::vector<Summary4Data> summary_data_;
};



