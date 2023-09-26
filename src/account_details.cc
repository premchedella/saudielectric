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
  ap_consumption_factor_ = "";
  ap_multi_factor_ = "";
  ap_prev_reading_ = "";
  ap_curr_reading_ = "";
  ap_cb_capacity_ = "";
  ap_meter_number_ = "";
  
  total_meteters_conumption_ = "";
  rp_conumption_ = "";

  rp_consumption_factor_ = "";
  rp_cb_capacity_ = "";
  rp_meter_number_ = "";


  // General
  parsing_ = "";
  reason_ = "";  
}

AccountDetails::~AccountDetails()
{

}


void AccountDetails::Initialize()
{  
  address_ = "NULL";

  electrometer_num_ = "NULL";
  type_ = "NULL";
  sub_type_ = "NULL";
  reading_from_ = "NULL";
  reading_to_ = "NULL";
  power_factor_ = "NULL";
  capacity_ = "NULL";
  account_num_ = "NULL";

  reading_days_ = "NULL";
  prev_reading_ = "NULL";
  curr_reading_ = "NULL";
  power_consumption_ = "NULL";
  power_consumption_cost_ = "NULL";
  subscription_num_ = "NULL";

  invoice_date_ = "NULL";
  electrometer_fee_ = "NULL"; 

  invoice_num_ = "NULL";
  total_power_cons_cost_ = "NULL";

  other_fees_ = "NULL";
  settlement_ = "NULL";

  vat_ = "NULL";
  total_cost_ = "NULL";

  other_prev_reading_ = "NULL";
  other_curr_reading_ = "NULL";
  other_pow_cons_ = "NULL";
  other_pow_cons_cost_ = "NULL";

  //Sub Table
  total_react_pow_con_ = "NULL";
  allowed_react_pow_con_ = "NULL";
  react_power_factor_ = "NULL";

  sub_curr_reading_ = "NULL";
  sub_prev_reading_ = "NULL";

  other_total_react_pow_con_ = "NULL";
  mul_react_power_factor_ = "NULL";
  reactive_prev_reading_ = "NULL";
  reactive_curr_reading_ = "NULL";

  power_cost_5_ = "NULL";
  power_cost_15_ = "NULL";
  vat_15_ = "NULL";
  taxable_amount_ = "NULL";
  non_taxable_amount_ = "NULL";

  // Parser 4
  site_num_ = "";

  total_ap_consumption_ = "NULL";
  ap_consumption_factor_ = "NULL";
  ap_multi_factor_ = "NULL";
  ap_prev_reading_ = "NULL";
  ap_curr_reading_ = "NULL";
  ap_cb_capacity_ = "NULL";
  ap_meter_number_ = "NULL";

  total_meteters_conumption_ = "NULL";
  rp_conumption_ = "NULL";

  rp_consumption_factor_ = "NULL";
  rp_cb_capacity_ = "NULL";
  rp_meter_number_ = "NULL";
}

