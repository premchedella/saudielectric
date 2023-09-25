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

  vat_ = "0.0";                       
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

  power_cost_5_ = "0.0";
  power_cost_15_ = "0.0";
  vat_15_ = "0.0";
  taxable_amount_ = "0.0";
  non_taxable_amount_ = "0.0";

  

  // Parser 4
  site_num_ = "";

  total_ap_consumption_ = "";
  consumption_factor_ = "";
  ap_multi_factor_ = "";
  ap_prev_reading_ = "";
  ap_curr_reading_ = "";
  ap_cb_capacity_ = "";
  ap_meter_number_ = "";
  
  total_meteters_conumption_ = "";
  rp_conumption_ = "";

  parsing_ = "";
  reason_ = "";  
}

AccountDetails::~AccountDetails()
{

}

