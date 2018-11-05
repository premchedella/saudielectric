#ifndef PARSE_LINE_H_
#define PARSE_LINE_H_

#include <iostream>

#include "common_types.h"
#include "account_details.h"

class ParseLine
{
 public:  
  static void Line2(QStringList data, AccountDetails* acc_details);
  static void Line3(QStringList data, AccountDetails* acc_details); 
  static void Line4(QStringList data, AccountDetails* acc_details);
  static void Line4Big(QStringList data, AccountDetails* acc_details);
  static void Line5(QStringList data, AccountDetails* acc_details);
  static void Line6(QStringList data, AccountDetails* acc_details);
  static void Line7(QStringList data, AccountDetails* acc_details);
  static void Line8(QStringList data, AccountDetails* acc_details);
  static void Line11(QStringList data, AccountDetails* acc_details);
  static void Line15(QStringList data, AccountDetails* acc_details);
  static void Line15ParVat(QStringList data, AccountDetails* acc_details);
  static void Line16ParVat(QStringList data, AccountDetails* acc_details);
  static void LineLast2(QStringList data, AccountDetails* acc_details);
};

#endif //PARSE_LINE_H_

