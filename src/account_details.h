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

  QString electrometer_num_;   //Electro Meter Number
  QString type_;               // Type
  QString sub_type_;                // Sub Type
  QString reading_from_;            // Reading From, date
  QString reading_to_;              // Reading to, date    
  QString power_factor_;              // Power factor
  QString capacity_;           // Capacity
  QString account_num_;          // Account Number

  QString reading_days_;       // Number of days
  QString prev_reading_;         // Previous Meter Reading (main table)
  QString curr_reading_;         // Current Meter Reading (main table)
  QString power_consumption_;    // Power Consumption (main table)
  QString power_consumption_cost_;    // Power Conmption cost
  QString subscription_num_;     // Subscription Number

  QString invoice_date_;            // Invoice Date
  QString electrometer_fee_;          // Electrometer Fee
     
  QString invoice_num_;          // Invoice Number
  QString total_power_cons_cost_;     // Total Power Conmption cost

  QString other_fees_;    // Other fees

  QString settlement_;                // Settlement

  QString vat_;                       // VAT
  QString total_cost_;                // Total Cost
  
  QString other_prev_reading_;   // Main Table Previous Reading
  QString other_curr_reading_;   // Main Table Current Reading
  QString other_pow_cons_;       // Main Table Power Consumption
  QString other_pow_cons_cost_;   // Main Table Power Consumption Cost

  //Sub Table
  QString total_react_pow_con_;   // Total Reactive Power Consumption
  QString allowed_react_pow_con_; // Allowed Reactive Power Consumption
  QString react_power_factor_;    // Power Factor

  QString sub_curr_reading_;     // Current Reading
  QString sub_prev_reading_;     // Previous Reading

  QString other_total_react_pow_con_;  // Other total Reactive Power Consumption
  QString mul_react_power_factor_;    // Multiplication Factor for Reactive Power
  QString reactive_prev_reading_; // Previous Reading of reactive Power
  QString reactive_curr_reading_; // Current Reading of reactive Power  

  QString power_cost_5_;  //Power Cost for VAT 5%
  QString power_cost_15_; //Power Cost for VAT 15%  
  QString vat_15_;       // 15% VAT 
  QString taxable_amount_;       // Taxable Amount 
  QString non_taxable_amount_;       // Non-Taxable Amount 

  // Parser 4
  QString site_num_; // Site Number  
  QString total_ap_consumption_; // Total Active Power Consumption
  QString ap_consumption_factor_;  // Active Power Consumption factor
  QString ap_multi_factor_; // Active Power Multiplication Factor
  QString ap_prev_reading_; // Active Power Previous Reading
  QString ap_curr_reading_; // Active Power Current Reading
  QString ap_cb_capacity_; // Active Power Circuit Breaker Capacity
  QString ap_meter_number_; // Active Power Meter Number

  QString total_meteters_consumption_; // Total Meters Conumption
  QString meteters_consumption_factor_; // Total Meters Consumption Factor

  QString rp_consumption_factor_;  // Reactive Power Conumption factor
  QString rp_cb_capacity_; // Reactive Power Circuit Breaker Capacity
  QString rp_meter_number_;  // Reactive Meter Nummber

  QString total_consumption_; // Total Consumption

  QString parsing_;   //Parsing is "Complete" or "Partial"
  QString reason_;    // Reason for not Complete. 
  
  void Initialize();
};

#endif //ACCOUNT_DETAILS_H_
