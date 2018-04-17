#include "account_details.h"

AccountDetails::AccountDetails()
{
  name_ = " ";
  address_ = " ";
  account_num_ = 0;
  subscription_num_ = 0;

  invoice_date_ = " ";
  invoice_num_ = 0;
  reading_from_ = " ";
  reading_to_ = " ";
  reading_days_ = 0;

  prev_reading_ = 0;
  curr_reading_ = 0;

  active_pow_cons_ = 0;
  reactive_pow_cons_ = 0;
  allowed_cons_ = 0;
  total_cons_ = 0;
  factor_ = 0.0f;
  power_factor_ = 0.0f;
  active_pow_cons_cost_ = 0.0f;
  reactive_pow_cons_cost_ = 0.0f;
  settlement_ = 0.0f;
  electrometer_fee_ = 0.0f;
  total_cons_cost_ = 0.0f;
  total_cost_ = 0.0f;

  electrometer_num_ = 0;
  type_ = 0;
  capacity_ = 0;
  block_length_ = 0;
}

AccountDetails::~AccountDetails()
{

}

