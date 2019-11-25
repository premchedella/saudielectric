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

  QString parsing_;   //Parsing is "Complete" or "Partial"
  QString reason_;    // Reason for not Complete.  
};

#endif //ACCOUNT_DETAILS_H_
