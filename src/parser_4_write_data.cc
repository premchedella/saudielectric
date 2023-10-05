#include "parser_4_write_data.h"

#include <QtCore\QDir>
#include <QtCore\QTextStream>

#include "parse_data.h"
#include "parser_4_summary.h"

Parser4WriteData::Parser4WriteData()
{
  
}

Parser4WriteData::~Parser4WriteData()
{
  std::vector<AccountDetails> data;
  data = ParseData::GetCommonData();

  QString file_name = GetFileName() + "_invoices.csv";
  file_name = QDir::toNativeSeparators(file_name);

  QFile csv_file(file_name);

  if (csv_file.open(QFile::WriteOnly | QFile::Truncate))
  {
    QTextStream stream(&csv_file);

    QString row_data;
    row_data = "";

    
    row_data += "Account Number,";  // A
    row_data += "Subscription Number,";  // B
    row_data += "Site Number,";  // C
    row_data += "Address,";  // D
    row_data += "Invoice Date,";  // E
    row_data += "Type,";  // F
    row_data += "Sub Type,";  // G
    row_data += "Invoice Number,";  // H
    row_data += "Reading To (Date),";  // I
    row_data += "Reading From (Date),";  // J
    row_data += "Multiplication Factor,";  // K
    row_data += "Circuit Breaker Capacity,";   // L
    row_data += "Reading Days,"; // M
    row_data += "Meter Number,"; // N       
    row_data += "Power Consumption,"; // O
    row_data += "Current Reading,"; // P
    row_data += "Previous Reading,";  // Q    
    row_data += "Reactive Power Consumption,"; // R   
    row_data += "Reactive Power Current Reading,";  // S     
    row_data += "Reactive Power Previous Reading,";  // T    
    row_data += "Taxable Amount,"; // U
    row_data += "Active Power Consumption Cost,"; // V
    row_data += "VAT,"; // W
    row_data += "Meter Service,"; // X 
    row_data += "Total Cost,"; // Y
    row_data += "Reactive Power Cost,"; // Z
    row_data += "Non Taxable Amount,"; // AA
    row_data += "Other Fees,"; // AB
    row_data += "Settlement,"; // AC
    row_data += "Required Amount,"; // AD   
    row_data += "Total Reactive Power Consumption (UP),"; // AE
    row_data += "Allowed Reactive Power Consumption,"; // AF
    row_data += "Power Factor,"; // AG    
    row_data += "Total Active Power Consumption,"; // AH    
    row_data += "Active Power Consumption Factor,"; // AI    
    row_data += "Active Power Multiplication Factor,"; // AJ    
    row_data += "Active Power Previous Reading,"; // AK    
    row_data += "Active Power Current Reading,"; // AL    
    row_data += "Active Power Circuit Breaker Capacity,"; // AM    
    row_data += "Active Power Meter Number,"; // AN    
    row_data += "Total Reactive Power Consumption (Down),"; // AO    
    row_data += "Reactive Power Consumption Factor,"; // AP 
    row_data += "Reactive Power Multiplication Factor,"; // AQ    
    row_data += "Reactive Power Previous Reading,"; // AR    
    row_data += "Reactive Power Current Reading,"; // AS    
    row_data += "Reactive Power Circuit Breaker Capacity,"; // AT    
    row_data += "Reactive Power Meter Number,"; // AU    
    row_data += "Total Meters Consumption,"; // AV    
    row_data += "Total Meters Consumption Factor,"; // AW    
    row_data += "Total Consumption,"; // AX    
    row_data += "Conversion,"; // AY
    row_data += "Reason"; // AZ    
    

    stream << row_data << "\n";

    QString value;
    unsigned int no_parsing_full = 0;
    unsigned int no_partial = 0;
    unsigned int no_warning = 0;

    for (unsigned int index = 0; index < data.size(); index++)
    {
      AccountDetails acc_details = data.at(index);

      row_data.clear();

      row_data = "";
      value = acc_details.account_num_;
      row_data += value + ","; // A
      value = acc_details.subscription_num_;
      row_data += value + ","; // B
      value = acc_details.site_num_;
      row_data += value + ","; // C
      value = acc_details.address_;
      row_data += value + ","; // D
      value = acc_details.invoice_date_;
      row_data += value + ","; // E
      value = acc_details.type_;
      row_data += value + ","; // F
      value = acc_details.sub_type_;
      row_data += value + ","; // G
      value = acc_details.invoice_num_;
      row_data += value + ","; // H
      value = acc_details.reading_to_;
      row_data += value + ","; // I
      value = acc_details.reading_from_;
      row_data += value + ","; // J
      value = acc_details.power_factor_;
      row_data += value + ","; // K
      value = acc_details.capacity_;
      row_data += value + ","; // L
      value = acc_details.reading_days_;
      row_data += value + ","; // M
      value = acc_details.electrometer_num_;
      row_data += value + ","; // N
      value = acc_details.power_consumption_;
      row_data += value + ","; // O
      value = acc_details.curr_reading_;
      row_data += value + ","; // P
      value = acc_details.prev_reading_;
      row_data += value + ","; // Q
      value = acc_details.other_pow_cons_;
      row_data += value + ","; // R
      value = acc_details.other_curr_reading_;
      row_data += value + ","; // S
      value = acc_details.other_prev_reading_;
      row_data += value + ","; // T
      value = acc_details.total_power_cons_cost_;
      row_data += value + ","; // U
      value = acc_details.power_consumption_cost_;
      row_data += value + ","; // V
      value = acc_details.vat_15_;
      row_data += value + ","; // W
      value = acc_details.electrometer_fee_;
      row_data += value + ","; // X
      value = acc_details.taxable_amount_;
      row_data += value + ","; // Y
      value = acc_details.other_pow_cons_cost_;
      row_data += value + ","; // Z
      value = acc_details.non_taxable_amount_;
      row_data += value + ","; // AA
      value = acc_details.other_fees_;
      row_data += value + ","; // AB
      value = acc_details.settlement_;
      row_data += value + ","; // AC
      value = acc_details.total_cost_;
      row_data += value + ","; // AD
      value = acc_details.total_react_pow_con_;
      row_data += value + ","; // AE
      value = acc_details.allowed_react_pow_con_;
      row_data += value + ","; // AF
      value = acc_details.react_power_factor_;
      row_data += value + ","; // AG
      value = acc_details.total_ap_consumption_;
      row_data += value + ","; // AH
      value = acc_details.ap_consumption_factor_;
      row_data += value + ","; // AI
      value = acc_details.ap_multi_factor_;
      row_data += value + ","; // AJ
      value = acc_details.ap_prev_reading_;
      row_data += value + ","; // AK
      value = acc_details.ap_curr_reading_;
      row_data += value + ","; // AL
      value = acc_details.ap_cb_capacity_;
      row_data += value + ","; // AM
      value = acc_details.ap_meter_number_;
      row_data += value + ","; // AN
      value = acc_details.other_total_react_pow_con_;
      row_data += value + ","; // AO
      value = acc_details.rp_consumption_factor_;
      row_data += value + ","; // AP
      value = acc_details.mul_react_power_factor_;
      row_data += value + ","; // AQ
      value = acc_details.reactive_prev_reading_;
      row_data += value + ","; // AR
      value = acc_details.reactive_curr_reading_;
      row_data += value + ","; // AS
      value = acc_details.rp_cb_capacity_;
      row_data += value + ","; // AT  
      value = acc_details.rp_meter_number_;
      row_data += value + ","; // AU
      value = acc_details.total_meteters_consumption_;
      row_data += value + ","; // AV
      value = acc_details.meteters_consumption_factor_;
      row_data += value + ","; // AW
      value = acc_details.total_consumption_;
      row_data += value + ","; // AX
      value = acc_details.parsing_;
      row_data += value + ","; // AY
      value = acc_details.reason_;
      row_data += value; // AZ 
                    
      if (acc_details.parsing_ == "Completed")
      {
        no_parsing_full++;
      }

      if (acc_details.parsing_ == "Partial")
      {
        no_partial++;
      }

      if (acc_details.parsing_ == "Warning")
      {
        no_warning++;
      }

      stream << row_data << "\n";
    }

    csv_file.close();

    std::cout << "Total Number Records = " << data.size() << std::endl;
    std::cout << "Total Number of Full Records = " << no_parsing_full <<
      std::endl;
    std::wcout << "Total Number of Partial Records = " <<
       no_partial << std::endl;
    std::wcout << "Total Number of Warning Records = " <<
      no_warning << std::endl;
  }

  std::cout << "Saved the data in the " << file_name.toStdString() << "."
    << std::endl;

}

void Parser4WriteData::WriteInvoiceData()
{

}

void Parser4WriteData::WriteBiggerData()
{
  std::cout << "Not required." << std:: endl;  
}

void Parser4WriteData::WriteSmallerData()
{
  std::cout << "Not required." << std::endl;
}

void Parser4WriteData::WriteSummaryData()
{
  std::vector<Summary4Data> summray_data = Parser4Summary::GetSummaryData();
  

  if (summray_data.size() > 0)
  {

    QString file_name = GetFileName() + "_summary.csv";
    file_name = QDir::toNativeSeparators(file_name);  

    QFile csv_file(file_name);

    if (csv_file.open(QFile::WriteOnly | QFile::Truncate))
    {           
      QTextStream stream(&csv_file);

      QString row_data;
      QString value;      

      /* Write header*/
      Summary4Data data = summray_data.at(0);
      
      value = data.name_;
      row_data += value + ","; // A
      value = data.value_;
      row_data += value + ","; // B
      value = data.complete_;
      row_data += value + ","; // C
      value = data.reason_;
      row_data += value; // D

      stream << row_data << "\n";

      for (unsigned int index = 1; index < summray_data.size(); index++)
      {
        data = summray_data.at(index);
        row_data.clear();     
        
        value = data.name_;
        row_data += value + ","; // A
        value = data.value_;
        row_data += value + ","; // B
        value = data.complete_;
        row_data += value + ","; // C
        value = data.reason_;
        row_data += value; // D

        stream << row_data << "\n";
      }
      csv_file.close();

    }
    std::cout << "Saved the summary data in the " << file_name.toStdString() << "."
      << std::endl;
  }
}


