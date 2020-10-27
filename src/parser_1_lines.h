#pragma once

#include <iostream>

#include "common_types.h"
#include "account_details.h"

class Parser1Lines
{
 public:
  static void Line1(QStringList data, AccountDetails* acc_details);
  static void Line2(QStringList data, AccountDetails* acc_details);
  static void Line3(QStringList data, AccountDetails* acc_details);
  static void Line4(QStringList data, AccountDetails* acc_details);
  static void Line7(QStringList data, AccountDetails* acc_details);
  static void Line8(QStringList data, AccountDetails* acc_details);
  static void Line9(QStringList data, AccountDetails* acc_details);
};