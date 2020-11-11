#include "account_details.h"

AccountDetails::AccountDetails()
{
  name_ = " ";
  address_ = " ";

  electrometer_num_ = "";   
  type_ = "";
  sub_type_ = "" ;
  reading_from_ = "";
  reading_to_ = "";
  power_factor_ = "";
  capacity_ = "";
  account_num_ = "";

  reading_days_ = "";
  prev_reading_ = "";
  curr_reading_ = "";
  power_consumption_ = "";
  power_consumption_cost_ = ""; 
  subscription_num_ = "";

  invoice_date_ = "";
  electrometer_fee_ = "";

  invoice_num_ = "";
  total_power_cons_cost_ = "";     

  other_fees_ = "";
  settlement_ = "";                

  vat_ = "";                       
  total_cost_ = "";                
    
  other_prev_reading_ = "";
  other_curr_reading_ = "";
  other_pow_cons_ = "";
  other_pow_cons_cost_ = "";

  //Sub Table
  total_react_pow_con_ = "";  
  allowed_react_pow_con_ = "";
  react_power_factor_ = "";

  sub_curr_reading_ = "";
  sub_prev_reading_ = "";

  other_total_react_pow_con_ = "";
  mul_react_power_factor_ = "";
  reactive_prev_reading_ = "";
  reactive_curr_reading_ = "";

  power_cost_5_ = "";
  power_cost_15_ = "";
  vat_15_ = "";
  taxable_amount_ = "";
  non_taxable_amount_ = "";

  parsing_ = "";
  reason_ = "";  
}

AccountDetails::~AccountDetails()
{

}

