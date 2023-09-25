#pragma once

#include <iostream>

#include "common_types.h"

class Summary4Data
{
public:
  Summary4Data();
  ~Summary4Data();

  QString no_;  /* Number*/
  QString v_name_; /* Varaiable name*/
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

  void AddSummaryData(QString no, QString v_name, QString name, QString value,
    QString complete, QString reason);
  void ParseLine1(QStringList data);
  void ParseLine2(QStringList data);
  void ParseLine3(QStringList data);
  void ParseLine4(QStringList data);
  void ParseLine12(QStringList data);
  void ParseLine13(QStringList data);
  void ParseLine14(QStringList data);
  void ParseLine15(QStringList data);
  void ParseLine16(QStringList data);
  void ParseLine18(QStringList data);
  void ParseLine20(QStringList data);
  void ParseLine28(QStringList data);
  void ParseLine29(QStringList data);

  void ParseLine1_1(QStringList data);
  void ParseLine2_1(QStringList data);
  void ParseLine3_1(QStringList data);
  void ParseLine4_1(QStringList data);
  void ParseLine10_1(QStringList data);
  void ParseLine11_1(QStringList data);
  void ParseLine12_1(QStringList data);
  void ParseLine13_1(QStringList data);
  void ParseLine14_1(QStringList data);

  static std::vector<Summary4Data> summary_data_;
};



