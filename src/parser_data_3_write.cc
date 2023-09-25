#include "parser_data_3_write.h"

#include <QtCore\QDir>
#include <QtCore\QTextStream>

#include "parse_data.h"
#include "parser_3_summary.h"

ParserData3Write::ParserData3Write()
{
  
}

ParserData3Write::~ParserData3Write()
{

}

void ParserData3Write::WriteBiggerData()
{
  std::cout << "Parser Data 3: Write Bigger Data " << std::endl;
  QString file_name = GetFileName() + "_bigger.csv";
  file_name = QDir::toNativeSeparators(file_name);

  std::vector<AccountDetails> data;
  data = ParseData::GetDataInfo(ParseData::AccountTypes::BIGGER);

  QFile csv_file(file_name);

  if (csv_file.open(QFile::WriteOnly | QFile::Truncate))
  {
    QTextStream stream(&csv_file);

    QString row_data;
    row_data = "";

    row_data += "Subscription Number,";  // A
    row_data += "Type Id,";  // B
    row_data += "Type,";  // C
    row_data += "Inovice Number,";  // D
    row_data += "Inovice nDate,";  // E
    row_data += "Meter Number,";  // F
    row_data += "Account Number,";  // G
    row_data += "Reading From (Date),";  // H
    row_data += "Reading To (Date),";  // I
    row_data += "Reading Days,";  // J
    row_data += "Active Power Consumption,";   // K
    row_data += "Multiplication Factor,"; // L
    row_data += "Active Power Cost,"; // M       
    row_data += "Charged ReactivePower Consumption,"; // N
    row_data += "Reactive PowerCost,"; // O
    row_data += "Meter Service,";  // P    
    row_data += "Duration Cost,"; // Q   
    row_data += "Settlement,";  // R     
    row_data += "VAT(15%),";  // S    
    row_data += "Total Cost,"; // T
    row_data += "Total Reactive Power Consumption (UP),"; // U
    row_data += "Allowed Reactive Power Consumption,"; // V
    row_data += "Power Factor,"; // W 
    row_data += "Current Reading,"; // X
    row_data += "Previous Reading,"; // Y
    row_data += "Total Reactive Power Consumption (Down),"; // Z
    row_data += "Reactive Power Multiplication Factor,"; // AA
    row_data += "Reactive Power Previous Reading,"; // AB
    row_data += "Reactive Power Current Reading,"; // AC   
    row_data += "Conversion,"; // AD
    row_data += "Reason,"; // AE    
    row_data += "Other Fees,"; // AF
    row_data += "Taxable Amount,"; // AG
    row_data += "Non Taxable Amount,"; // AH    

    stream << row_data << "\n";

    QString value;
    unsigned int no_parsing_full = 0;

    for (unsigned int index = 0; index < data.size(); index++)
    {
      AccountDetails acc_details = data.at(index);

      row_data.clear();

      row_data = "";
      value = acc_details.subscription_num_;
      row_data += value + ","; // A
      value = acc_details.type_;
      row_data += value + ","; // B
      value = acc_details.sub_type_;
      row_data += value + ","; // C
      value = acc_details.invoice_num_;
      row_data += value + ","; // D
      value = acc_details.invoice_date_;
      row_data += value + ","; // E      
      value = acc_details.electrometer_num_;
      row_data += value + ","; // F
      value = acc_details.account_num_;
      row_data += value + ","; // G
      value = acc_details.reading_from_;
      row_data += value + ","; // H 
      value = acc_details.reading_to_;
      row_data += value + ","; // I           
      value = acc_details.reading_days_;
      row_data += value + ","; // J      
      value = acc_details.power_consumption_;
      row_data += value + ","; // K
      value = acc_details.power_factor_;
      row_data += value + ","; // L        
      value = acc_details.power_consumption_cost_;
      row_data += value + ","; // M      
      value = acc_details.other_pow_cons_;
      row_data += value + ","; // N  
      value = acc_details.other_pow_cons_cost_;
      row_data += value + ","; // O
      value = acc_details.electrometer_fee_;
      row_data += value + ","; // P      
      value = acc_details.total_power_cons_cost_;
      row_data += value + ","; // Q
      value = acc_details.settlement_;
      row_data += value + ","; // R      
      value = acc_details.vat_15_;
      row_data += value + ","; // S            
      value = acc_details.total_cost_;
      row_data += value + ","; // T   
      value = acc_details.total_react_pow_con_;
      row_data += value + ","; // U  
      value = acc_details.allowed_react_pow_con_;
      row_data += value + ","; // V 
      value = acc_details.react_power_factor_;
      row_data += value + ","; // W 
      value = acc_details.sub_curr_reading_;
      row_data += value + ","; // X  
      value = acc_details.sub_prev_reading_;
      row_data += value + ","; // Y  
      value = acc_details.other_total_react_pow_con_;
      row_data += value + ","; // Z       
      value = acc_details.mul_react_power_factor_;
      row_data += value + ","; // AA 
      value = acc_details.reactive_prev_reading_;
      row_data += value + ","; // AB  
      value = acc_details.reactive_curr_reading_;
      row_data += value + ","; // AC
      value = acc_details.parsing_;
      row_data += value + ","; // AD
      value = acc_details.reason_;
      row_data += value + ","; // AE      
      value = acc_details.other_fees_;
      row_data += value + ","; // AF      
      value = acc_details.taxable_amount_;
      row_data += value + ","; // AG
      value = acc_details.non_taxable_amount_;
      row_data += value; // AH      

      stream << row_data << "\n";

      if (acc_details.parsing_ == "Completed")
      {
        no_parsing_full++;
      }
    }

    csv_file.close();

    std::cout << "Total Number Records = " << data.size() << std::endl;
    std::cout << "Total Number of Full Records = " << no_parsing_full <<
      std::endl;
    std::wcout << "Total Number of Partial Records = " <<
      (data.size() - no_parsing_full) << std::endl;
  }
  std::cout << "Saved the data in the " << file_name.toStdString() << "."
      << std::endl << std::endl;
}

void ParserData3Write::WriteSmallerData()
{
  std::cout << "Parser Data 3: Write Smaller Data " << std::endl;
  QString file_name = GetFileName() + "_smaller.csv";
  file_name = QDir::toNativeSeparators(file_name);

  std::vector<AccountDetails> data;
  data = ParseData::GetDataInfo(ParseData::AccountTypes::SMALLER);

  QFile csv_file(file_name);
  if (csv_file.open(QFile::WriteOnly | QFile::Truncate))
  {
    QTextStream stream(&csv_file);

    QString row_data;
    row_data = "";

    row_data += "Subscription Number,";  // A
    row_data += "Type Id,";  // B
    row_data += "Type,";  // C
    row_data += "Inovice Number,";  // D
    row_data += "Inovice Date,";  // E
    row_data += "Meter Number,";  // F
    row_data += "Account Number,";  // G
    row_data += "Reading From (Date),";  // H
    row_data += "Reading To (Date),";  // I
    row_data += "Reading Days,";  // J
    row_data += "Previous Reading,";   //K
    row_data += "Current Reading,";   //L    
    row_data += "Power Consumption,";   // M
    row_data += "Capacity,"; //N 
    row_data += "Multiplication Factor,"; // O
    row_data += "Power Cost,"; // P   
    row_data += "Meter Service,";  // Q     
    row_data += "Duration Cost,"; // R   
    row_data += "Settlement,";  // S  
    row_data += "VAT(15%),";  // T    
    row_data += "Total Cost,"; // U
    row_data += "Conversion,"; // V
    row_data += "Reason,"; // W    
    row_data += "Other Fees,"; // X    
    row_data += "Taxable Amount,"; // Y
    row_data += "Non Taxable Amount"; // Z

    stream << row_data << "\n";

    QString value;
    unsigned int no_parsing_full = 0;

    for (unsigned int index = 0; index < data.size(); index++)
    {
      AccountDetails acc_details = data.at(index);

      row_data.clear();

      row_data = "";

      value = acc_details.subscription_num_;
      row_data += value + ","; // A
      value = acc_details.type_;
      row_data += value + ","; // B
      value = acc_details.sub_type_;
      row_data += value + ","; // C
      value = acc_details.invoice_num_;
      row_data += value + ","; // E
      value = acc_details.invoice_date_;
      row_data += value + ","; // F      
      value = acc_details.electrometer_num_;
      row_data += value + ","; // G
      value = acc_details.account_num_;
      row_data += value + ","; // H
      value = acc_details.reading_from_;
      row_data += value + ","; // I 
      value = acc_details.reading_to_;
      row_data += value + ","; // J           
      value = acc_details.reading_days_;
      row_data += value + ","; // K
      value = acc_details.prev_reading_;
      row_data += value + ","; // L
      value = acc_details.curr_reading_;
      row_data += value + ","; // K
      value = acc_details.power_consumption_;
      row_data += value + ","; // M
      value = acc_details.capacity_;
      row_data += value + ","; // N
      value = acc_details.power_factor_;
      row_data += value + ","; // O        
      value = acc_details.power_consumption_cost_;
      row_data += value + ","; // P  
      value = acc_details.electrometer_fee_;
      row_data += value + ","; // Q      
      value = acc_details.total_power_cons_cost_;
      row_data += value + ","; // R
      value = acc_details.settlement_;
      row_data += value + ","; // S      
      value = acc_details.vat_15_;
      row_data += value + ","; // T
      value = acc_details.total_cost_;
      row_data += value + ","; // U     
      value = acc_details.parsing_;
      row_data += value + ","; // V     
      value = acc_details.reason_;
      row_data += value + ","; // W      
      value = acc_details.other_fees_;
      row_data += value + ","; // X      
      value = acc_details.taxable_amount_;
      row_data += value + ","; // Y
      value = acc_details.non_taxable_amount_;
      row_data += value; // Z

      stream << row_data << "\n";

      if (acc_details.parsing_ == "Completed")
      {
        no_parsing_full++;
      }
    }
    csv_file.close();

    std::cout << "Total Number Records = " << data.size() << std::endl;
    std::cout << "Total Number of Full Records = " << no_parsing_full <<
      std::endl;
    std::wcout << "Total Number of Partial Records = " <<
      (data.size() - no_parsing_full) << std::endl;
  }

  std::cout << "Saved the data in the " << file_name.toStdString() << "."
    << std::endl << std::endl;
}

void ParserData3Write::WriteSummaryData()
{
  std::vector<SummaryData> summray_data = Parser3Summary::GetSummaryData();
  
  if (summray_data.size() > 0)
  {

    QString file_name = GetFileName() + "_summary.csv";
    file_name = QDir::toNativeSeparators(file_name);  

    QFile csv_file(file_name);

    if (csv_file.open(QFile::WriteOnly | QFile::Truncate))
    {
      QTextStream stream(&csv_file);
      stream.setCodec("IBM 866");
    
      QString row_data;
      QString value;
      unsigned int no_parsing_full = 0;

      /* Write header*/
      SummaryData data = summray_data.at(0);
      row_data = "";
      value = data.no_;
      row_data += value + ","; // A
      value = data.v_name_;
      row_data += value + ","; // B
      value = data.name_;
      row_data += value + ","; // C
      value = data.value_;
      row_data += value + ","; // D
      value = data.complete_;
      row_data += value + ","; // E
      value = data.reason_;
      row_data += value; // F

      stream << row_data << "\n";

      for (unsigned int index = 1; index < summray_data.size(); index++)
      {
        unsigned int index_position = 0;
        for (unsigned int i_index = 1; i_index < summray_data.size(); i_index++)
        {
          SummaryData data = summray_data.at(i_index);
          unsigned int i_value = data.no_.toInt();
          if (i_value == index)
          {
            index_position = i_index;
            break;
          }
        }
        SummaryData data = summray_data.at(index_position);

        row_data.clear();

        row_data = "";
        value = data.no_;
        row_data += value + ","; // A
        value = data.v_name_;
        row_data += value + ","; // B
        value = data.name_;
        row_data += value + ","; // C
        value = data.value_;
        row_data += value  + ","; // D
        value = data.complete_;
        row_data += value + ","; // E
        value = data.reason_;
        row_data += value; // F

        stream << row_data << "\n";
      }
      csv_file.close();

    }
    std::cout << "Saved the summary data in the " << file_name.toStdString() << "."
      << std::endl;
  }
}


