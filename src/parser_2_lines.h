#pragma once

#include <iostream>

#include "common_types.h"
#include "account_details.h"

class Parser2Lines
{
 public:
  static void Line1(QStringList data, AccountDetails* acc_details);
  static void Line2(QStringList data, AccountDetails* acc_details);
  static void Line3(QStringList data, AccountDetails* acc_details);
  static void Line4(QStringList data, AccountDetails* acc_details);
  static void Line7(QStringList data, AccountDetails* acc_details);
  static void Line8(QStringList data, AccountDetails* acc_details);
  static void Line9(QStringList data, AccountDetails* acc_details);
  static void Line10(QStringList data, AccountDetails* acc_details);
  static void Line10Small(QStringList data, AccountDetails* acc_details);
  static void Line11(QStringList data, AccountDetails* acc_details);
  static void Line11Small(QStringList data, AccountDetails* acc_details);
  static void Line11Big(QStringList data, AccountDetails* acc_details);
  static void Line12(QStringList data, AccountDetails* acc_details);
  static void Line12Big(QStringList data, AccountDetails* acc_details);
  static void Line13(QStringList data, AccountDetails* acc_details);  
  static void Line14(QStringList data, AccountDetails* acc_details);
  static void Line9Big(QStringList data, AccountDetails* acc_details);
  static void Line10Big15(QStringList data, AccountDetails* acc_details);
  static void Line11Big15(QStringList data, AccountDetails* acc_details);  
  static void Line16(QStringList data, AccountDetails* acc_details);
  static void Line20(QStringList data, AccountDetails* acc_details);
  static void LineLast(QStringList data, AccountDetails* acc_details);

  static bool Is15VatExtra(QStringList data);
};