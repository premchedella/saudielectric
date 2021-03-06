#include "csv_write.h"

#include <QtCore\QDir>
#include <QtCore\QTextStream>

#include "parse_data.h"
#include "common_types.h"
#include "utilities.h"

CsvWrite::CsvWrite(QString file_name)
{
  file_name_ = QDir::toNativeSeparators(file_name);
}

CsvWrite::~CsvWrite()
{

}

void CsvWrite::Write(int type)
{
  Utilities::InputFileTypes file_type = Utilities::GetFileType();
  if (file_type == Utilities::InputFileTypes::KAU2_MAIN)       
  {    
    WriteResidential(type);
  } else
  {
    WriteIndustrial(type);
  }  
}

void CsvWrite::Write()
{
  Utilities::ParserTypes parser_type = Utilities::GetParserType();
  if (parser_type == Utilities::ParserTypes::PARSER_TYPE_1)
  {
    Utilities::InputFileTypes file_type = Utilities::GetFileType();
    if (file_type == Utilities::InputFileTypes::KAU2_MAIN)
    {
      Parser1Small();      
    } else
    {      
      Parser1Big();
    }
  }
  
}

void CsvWrite::WriteResidential(int type)
{
  std::vector<AccountDetails> data;
  std::vector<unsigned int> types = ParseData::GetTypes();
  if (type < types.size())
  {
    data = ParseData::GetDataInfo(types.at(type));
  } else
  {
    data = ParseData::GetDataInfo();
  }
  
  QFile csv_file(file_name_);
  if (csv_file.open(QFile::WriteOnly | QFile::Truncate))
  {
    QTextStream stream(&csv_file);

    Utilities::VatTypes vat_type = Utilities::GetVatType();

    QString row_data;
    row_data = "";

    row_data += "\"Subscription\nNumber\",";  // A
    row_data += "\"Type\nId\",";  // B
    row_data += "Type,";  // C
    row_data += "\"Inovice\nNumber\",";  // D
    row_data += "\"Inovice\nDate\",";  // E
    row_data += "\"Meter\nNumber\",";  // F
    row_data += "\"Account\nNumber\",";  // G
    row_data += "\"Reading\nFrom\n(Date)\",";  // H
    row_data += "\"Reading\nTo\n(Date)\",";  // I
    row_data += "\"Reading\nDays\",";  // J
    row_data += "\"Previous\nReading\",";   //K
    row_data += "\"Current\nReading\",";   //L    
    row_data += "\"Power\nConsumption\",";   // M
    row_data += "Capacity,"; //N 
    row_data += "\"Multiplication\nFactor\","; // O
    row_data += "\"Power\nCost\","; // P   
    row_data += "\"Meter\nService\",";  // Q     
    row_data += "\"Duration\nCost\","; // R   
    row_data += "Settlement,";  // S  
    if ((vat_type == Utilities::VatTypes::WITH) ||
      (vat_type == Utilities::VatTypes::PARTIAL))
    {
      row_data += "VAT,";  // T
    }
    row_data += "\"Total\nCost\","; // U
    row_data += "Conversion,"; // V
    row_data += "Reason,"; // W
    if (Utilities::IsOtherFees())
    {
      row_data += "\"Other\nFees\""; // X
    }
    
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
      row_data +=  value + ","; // S

      if ((vat_type == Utilities::VatTypes::WITH) ||
        (vat_type == Utilities::VatTypes::PARTIAL))
      {
        value = acc_details.vat_;
        row_data += value + ","; // T      
      }
      
      value = acc_details.total_cost_;
      row_data += value + ","; // U     
      value = acc_details.parsing_;
      row_data += value + ","; // V     
      value = acc_details.reason_;
      row_data += value + ","; // W

      if (Utilities::IsOtherFees())
      {
        value = acc_details.other_fees_;
        row_data += value; // X
      }

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

  std::cout << "Saved the data in the " << file_name_.toStdString() << "."
    << std::endl << std::endl;
}

void CsvWrite::WriteIndustrial(int type)
{
  std::vector<AccountDetails> data;
  std::vector<unsigned int> types = ParseData::GetTypes();
  if (type < types.size())
  {
    data = ParseData::GetDataInfo(types.at(type));
  } else
  {
    data = ParseData::GetDataInfo();
  }

  QFile csv_file(file_name_);
  if (csv_file.open(QFile::WriteOnly | QFile::Truncate))
  {
    QTextStream stream(&csv_file);
    QString row_data;

    Utilities::VatTypes vat_type = Utilities::GetVatType();

    row_data = "";

    row_data += "\"Subscription\nNumber\",";  // A
    row_data += "\"Type\nId\",";  // B
    row_data += "Type,";  // C
    row_data += "\"Inovice\nNumber\",";  // D
    row_data += "\"Inovice\nDate\",";  // E
    row_data += "\"Meter\nNumber\",";  // F
    row_data += "\"Account\nNumber\",";  // G
    row_data += "\"Reading\nFrom\n(Date)\",";  // H
    row_data += "\"Reading\nTo\n(Date)\",";  // I
    row_data += "\"Reading\nDays\",";  // J
    row_data += "\"Active\nPower\nConsumption\",";   // K
    row_data += "\"Multiplication\nFactor\","; // L
    row_data += "\"Active\nPower\nCost\","; // M       
    row_data += "\"Charged\nReactive\nPower\nConsumption\","; // N
    row_data += "\"Reactive\nPower\nCost\","; // O
    row_data += "\"Meter\nService\",";  // P    
    row_data += "\"Duration\nCost\","; // Q   
    row_data += "Settlement,";  // R 
    if ((vat_type == Utilities::VatTypes::WITH) ||
      (vat_type == Utilities::VatTypes::PARTIAL))
    {
      row_data += "VAT,";  // S
    }
    row_data += "\"Total\nCost\","; // T
    row_data += "\"Total\nReactive\nPower\nConsumption\n(UP)\","; // U
    row_data += "\"Allowed\nReactive\nPower\nConsumption\","; // V
    row_data += "\"Power\nFactor\","; // W 
    row_data += "\"Current\nReading\","; // X
    row_data += "\"Previous\nReading\","; // Y
    row_data += "\"Total\nReactive\nPower\nConsumption\n(Down)\","; // Z
    row_data += "\"Reactive\nPower\nMultiplication\nFactor\","; // AA
    row_data += "\"Reactive\nPower\nPrevious\nReading\","; // AB
    row_data += "\"Reactive\nPower\nCurrent\nReading\","; // AC   
    row_data += "Conversion,"; // AD
    row_data += "Reason,"; // AE
    if (Utilities::IsOtherFees())
    {
      row_data += "\"Other\nFees\""; // AF
    }

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
      if ((vat_type == Utilities::VatTypes::WITH) ||
        (vat_type == Utilities::VatTypes::PARTIAL))
      {
        value = acc_details.vat_;
        row_data += value + ","; // S      
      }
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
      row_data += value + "," ; // AD
      value = acc_details.reason_;
      row_data += value + ","; // AE
      if (Utilities::IsOtherFees())
      {
        value = acc_details.other_fees_;
        row_data += value; // AF
      }
             
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
  
  std::cout << "Saved the data in the " << file_name_.toStdString() << "."
    << std::endl << std::endl;
}

void CsvWrite::Parser1Small()
{
  std::vector<AccountDetails> data;
  std::vector<unsigned int> types = ParseData::GetTypes();
  
  data = ParseData::GetDataInfo();  

  QFile csv_file(file_name_);
  if (csv_file.open(QFile::WriteOnly | QFile::Truncate))
  {
    QTextStream stream(&csv_file);    

    QString row_data;
    row_data = "";

    row_data += "\"Subscription\nNumber\",";  // A
    row_data += "\"Type\nId\",";  // B
    row_data += "Type,";  // C
    row_data += "\"Inovice\nNumber\",";  // D
    row_data += "\"Inovice\nDate\",";  // E
    row_data += "\"Meter\nNumber\",";  // F
    row_data += "\"Account\nNumber\",";  // G
    row_data += "\"Reading\nFrom\n(Date)\",";  // H
    row_data += "\"Reading\nTo\n(Date)\",";  // I
    row_data += "\"Reading\nDays\",";  // J
    row_data += "\"Previous\nReading\",";   //K
    row_data += "\"Current\nReading\",";   //L    
    row_data += "\"Power\nConsumption\",";   // M
    row_data += "Capacity,"; //N 
    row_data += "\"Multiplication\nFactor\","; // O
    row_data += "\"Power\nCost\","; // P   
    row_data += "\"Meter\nService\",";  // Q     
    row_data += "\"Duration\nCost\","; // R   
    row_data += "Settlement,";  // S  
    row_data += "VAT(5%),";  // T    
    row_data += "\"Total\nCost\","; // U
    row_data += "Conversion,"; // V
    row_data += "Reason,"; // W    
    row_data += "\"Other\nFees\","; // X
    row_data += "\"Power\nCost(5%)\","; // Y   
    row_data += "\"Power\nCost(15%)\","; // Z
    row_data += "VAT(15%),"; // AA
    row_data += "\"Taxable\nAmount\","; // AB
    row_data += "\"Non Taxable\nAmount\""; // AC

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
      value = acc_details.vat_;
      row_data += value + ","; // T
      value = acc_details.total_cost_;
      row_data += value + ","; // U     
      value = acc_details.parsing_;
      row_data += value + ","; // V     
      value = acc_details.reason_;
      row_data += value + ","; // W      
      value = acc_details.other_fees_;
      row_data += value + ","; // X
      value = acc_details.power_cost_5_;
      row_data += value + ","; // Y
      value = acc_details.power_cost_15_;
      row_data += value + ","; // Z
      value = acc_details.vat_15_;
      row_data += value + ","; // AA
      value = acc_details.taxable_amount_;
      row_data += value + ","; // AB
      value = acc_details.non_taxable_amount_;
      row_data += value; // AC

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

  std::cout << "Saved the data in the " << file_name_.toStdString() << "."
    << std::endl << std::endl;
}

void CsvWrite::Parser1Big()
{
  std::vector<AccountDetails> data;
  std::vector<unsigned int> types = ParseData::GetTypes();

  data = ParseData::GetDataInfo();

  QFile csv_file(file_name_);
  if (csv_file.open(QFile::WriteOnly | QFile::Truncate))
  {
    QTextStream stream(&csv_file);
    
    QString row_data;
    row_data = "";

    row_data += "\"Subscription\nNumber\",";  // A
    row_data += "\"Type\nId\",";  // B
    row_data += "Type,";  // C
    row_data += "\"Inovice\nNumber\",";  // D
    row_data += "\"Inovice\nDate\",";  // E
    row_data += "\"Meter\nNumber\",";  // F
    row_data += "\"Account\nNumber\",";  // G
    row_data += "\"Reading\nFrom\n(Date)\",";  // H
    row_data += "\"Reading\nTo\n(Date)\",";  // I
    row_data += "\"Reading\nDays\",";  // J
    row_data += "\"Active\nPower\nConsumption\",";   // K
    row_data += "\"Multiplication\nFactor\","; // L
    row_data += "\"Active\nPower\nCost\","; // M       
    row_data += "\"Charged\nReactive\nPower\nConsumption\","; // N
    row_data += "\"Reactive\nPower\nCost\","; // O
    row_data += "\"Meter\nService\",";  // P    
    row_data += "\"Duration\nCost\","; // Q   
    row_data += "Settlement,";  // R     
    row_data += "VAT(5%),";  // S    
    row_data += "\"Total\nCost\","; // T
    row_data += "\"Total\nReactive\nPower\nConsumption\n(UP)\","; // U
    row_data += "\"Allowed\nReactive\nPower\nConsumption\","; // V
    row_data += "\"Power\nFactor\","; // W 
    row_data += "\"Current\nReading\","; // X
    row_data += "\"Previous\nReading\","; // Y
    row_data += "\"Total\nReactive\nPower\nConsumption\n(Down)\","; // Z
    row_data += "\"Reactive\nPower\nMultiplication\nFactor\","; // AA
    row_data += "\"Reactive\nPower\nPrevious\nReading\","; // AB
    row_data += "\"Reactive\nPower\nCurrent\nReading\","; // AC   
    row_data += "Conversion,"; // AD
    row_data += "Reason,"; // AE    
    row_data += "\"Other\nFees\","; // AF
    row_data += "\"Power\nCost(5%)\","; // AG   
    row_data += "\"Power\nCost(15%)\","; // AH
    row_data += "VAT(15%),"; // AI
    row_data += "\"Taxable\nAmount\","; // AJ
    row_data += "\"Non Taxable\nAmount\""; // AK    

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
      value = acc_details.vat_;
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
      value = acc_details.power_cost_5_;
      row_data += value + ","; // AG
      value = acc_details.power_cost_15_;
      row_data += value + ","; // AH
      value = acc_details.vat_15_;
      row_data += value + ","; // AI
      value = acc_details.taxable_amount_;
      row_data += value + ","; // AJ
      value = acc_details.non_taxable_amount_;
      row_data += value; // AK      

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

  std::cout << "Saved the data in the " << file_name_.toStdString() << "."
    << std::endl << std::endl;
}