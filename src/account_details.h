#ifndef ACCOUNT_DETAILS_H_
#define ACCOUNT_DETAILS_H_

#include <iostream>

#include <QtCore\QString>

class AccountDetails
{
 public:
  AccountDetails();
  ~AccountDetails();

  QString name_;
  QString address_;
  qulonglong account_num_;

  qulonglong subscription_num_;

  QString invoice_date_;
  qulonglong invoice_num_;
  QString reading_from_;
  QString reading_to_;
  unsigned int reading_days_;

  qulonglong prev_reading_;
  qulonglong curr_reading_;

  qulonglong active_pow_cons_;
  qulonglong reactive_pow_cons_;
  qulonglong allowed_cons_;
  qulonglong total_cons_;
  float factor_;
  float power_factor_;
  float active_pow_cons_cost_;
  float reactive_pow_cons_cost_;
  float settlement_;
  float electrometer_fee_;
  float total_cons_cost_;
  float total_cost_;

  unsigned int electrometer_num_;
  unsigned int type_;
  unsigned int capacity_;
  unsigned int block_length_;
};

#endif //ACCOUNT_DETAILS_H_
