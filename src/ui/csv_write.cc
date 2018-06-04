#include "csv_write.h"

#include <QtCore\QDir>
#include <QtCore\QTextStream>

#include "../parse_data.h"
#include "../common_types.h"
#include "../utilities.h"

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
    row_data += "Conversion"; // V
    
    stream << row_data << "\n";

    QString value;

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
      row_data += value; // V     

      stream << row_data << "\n";
    }
    csv_file.close();
  }

  std::cout << "Saved the data in the " << file_name_.toStdString() << "."
    << std::endl;
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
    row_data += "Conversion"; // AD

    stream << row_data << "\n";

    QString value;
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
      row_data += value; // AC
             
      stream << row_data << "\n";
    }

    csv_file.close();
  }
  
  std::cout << "Saved the data in the " << file_name_.toStdString() << "."
    << std::endl;
}

#if 0 // old

QFile csv_file(file_name_);
if (csv_file.open(QFile::WriteOnly | QFile::Truncate))
{
  QTextStream stream(&csv_file);
  QString row_data;

  row_data = "Electrometer Number,";
  row_data = row_data + "Type,";
  row_data = row_data + "Reading To,";
  row_data = row_data + "Reading From,";
  row_data = row_data + "Power Factor,";
  row_data = row_data + "Capactiy,";
  row_data = row_data + "Account Number,";
  row_data = row_data + "Number of Days,";
  row_data = row_data + "Current Meter Reading,";
  row_data = row_data + "Previous Meter Reading,";
  row_data = row_data + "Power Consumption,";
  row_data = row_data + "Power Consumption Cost,";
  row_data = row_data + "Subsciption Number,";
  row_data = row_data + "Innvoice Date,";
  row_data = row_data + "Electrometer Fee,";
  row_data = row_data + "Innvoice Number,";
  row_data = row_data + "Total Power Cosumption Cost,";
  row_data = row_data + "Settlement,";
  row_data = row_data + "VAT,";
  row_data = row_data + "Total Cost";

  stream << row_data << "\n";

  for (unsigned int index = 0; index < data.size(); index++)
  {
    AccountDetails acc_details = data.at(index);

    row_data.clear();

    row_data = row_data + QString::number(acc_details.electrometer_num_) + ",";
    row_data = row_data + QString::number(acc_details.type_) + ",";
    row_data = row_data + acc_details.reading_to_ + ",";
    row_data = row_data + acc_details.reading_from_ + ",";
    //row_data = row_data + QString::number(acc_details.factor_, 'f', 2) + ",";
    row_data = row_data + QString::number(acc_details.capacity_) + ",";
    row_data = row_data + QString::number(acc_details.account_num_) + ",";
    row_data = row_data + QString::number(acc_details.reading_days_) + ",";
    row_data = row_data + QString::number(acc_details.curr_reading_) + ",";
    row_data = row_data + QString::number(acc_details.prev_reading_) + ",";
    //row_data = row_data + QString::number(acc_details.active_pow_cons_) + ",";
    // row_data = row_data +
    //  QString::number(acc_details.active_pow_cons_cost_, 'f', 2) + ",";
    row_data = row_data + QString::number(acc_details.subscription_num_) + ",";
    row_data = row_data + acc_details.invoice_date_ + ",";
    row_data = row_data +
      QString::number(acc_details.electrometer_fee_, 'f', 2) + ",";
    row_data = row_data + QString::number(acc_details.invoice_num_) + ",";
    //row_data = row_data + 
    //    QString::number(acc_details.total_cons_cost_, 'f', 2) + ",";
    row_data = row_data + QString::number(acc_details.settlement_, 'f', 2) + ",";
    row_data = row_data + QString::number(acc_details.vat_, 'f', 2) + ",";
    row_data = row_data + QString::number(acc_details.total_cost_, 'f', 2);

    stream << row_data << "\n";
  }
  csv_file.close();
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
    QString row_data;

    row_data = "Previous Reading,";   //A
    row_data += "Current Reading,";  // B
    row_data += " ,";  //C
    row_data += " ,"; // D
    row_data += " ,"; // E
    row_data += " ,";  // F
    row_data += " ,";  // G
    row_data += "Power Consumption,";   // H
    row_data += " ,"; // I
    row_data += " ,";  // J
    row_data += " Settlement,";  // K
    row_data += " ,"; // L
    row_data += "Duration Cost,"; // M   
    row_data += "Meter Service,";  // N 
    row_data += " ,"; // O
    row_data += "VAT,";  // P
    row_data += " ,"; // Q
    row_data += " ,";  // R
    row_data += " ,"; // S
    row_data += " ,"; // T
    row_data += " ,"; // U
    row_data += " ,"; // V
    row_data += "Power Cost,"; // W
    row_data += " ,"; // X
    row_data += "Total Cost,"; // Y
    row_data += "Multiplication Factor"; // Z
    stream << row_data << "\n";

    for (unsigned int index = 0; index < data.size(); index++)
    {
      AccountDetails acc_details = data.at(index);

      row_data.clear();

      row_data = QString::number(acc_details.prev_reading_) + ","; // A
      row_data += QString::number(acc_details.curr_reading_) + ","; // B
      row_data += ","; // C
      row_data += ","; // D
      row_data += ","; // E
      row_data += ","; // F
      row_data += ","; // G
      row_data += QString::number(acc_details.power_consumption_) + ","; // H
      row_data += ","; // I
      row_data += ","; // J
      row_data += QString::number(acc_details.settlement_, 'f', 2) + ","; // K
      row_data += ","; // L
      row_data +=
        QString::number(acc_details.total_power_cons_cost_, 'f', 2) + ","; // M
      row_data +=
        QString::number(acc_details.electrometer_fee_, 'f', 2) + ","; // N
      row_data += ","; // O
      row_data += QString::number(acc_details.vat_, 'f', 2) + ","; // P
      row_data += " ,"; // Q
      row_data += " ,";  // R
      row_data += " ,"; // S
      row_data += " ,"; // T
      row_data += " ,"; // U
      row_data += " ,"; // V
      row_data +=
        QString::number(acc_details.power_consumption_cost_, 'f', 2) + ","; // W
      row_data += " ,"; // X
      row_data += QString::number(acc_details.total_cost_, 'f', 2) + ","; // Y
      row_data += QString::number(acc_details.power_factor_, 'f', 2); // Z  

      stream << row_data << "\n";
    }
    csv_file.close();
  }

  std::cout << "Saved the data in the " << file_name_.toStdString() << "."
    << std::endl;
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

    row_data = "";
    row_data += "Current Reading,";   //A    
    row_data += "Previous Reading,";  // B
    row_data += " ,";  //C
    row_data += "Charged Reactive Power Consumption,"; // D
    row_data += "Reactive Power Cost,"; // E
    row_data += "Meter Service,";  // F
    row_data += "Duration Cost,";  // G
    row_data += "Active Power Cost,";   // H
    row_data += " ,"; // I
    row_data += "Multiplication Factor for reactive Power,";  // J
    row_data += "Total Cost,";  // K
    row_data += "Current Reading for Reactive Power ,"; // L
    row_data += "VAT,"; // M   
    row_data += "Total reactive Power Cosumption,";  // N 
    row_data += " ,"; // O
    row_data += "Previous Reading for reactive Power,";  // P
    row_data += "Power Factor,"; // Q
    row_data += "Settlement,";  // R
    row_data += " ,"; // S
    row_data += "Allowed Reactive Power Consumption,"; // T
    row_data += "Total Reactive Power Consumption,"; // U
    row_data += " ,"; // V
    row_data += " ,"; // W
    row_data += " ,"; // X
    row_data += "Active Power Consumption,"; // Y
    row_data += "Multiplication Factor"; // Z
    stream << row_data << "\n";
    QString value;
    for (unsigned int index = 0; index < data.size(); index++)
    {
      AccountDetails acc_details = data.at(index);

      row_data.clear();

      row_data = "";
      value = QString::number(acc_details.sub_curr_reading_);
      row_data += value + ","; // A
      value = QString::number(acc_details.sub_prev_reading_);
      row_data += value + ","; // B
      row_data += ","; // C
      value = QString::number(acc_details.other_pow_cons_);
      row_data += value + ","; // D  
      value = QString::number(acc_details.other_pow_cons_cost_, 'f', 2);
      row_data += value + ","; // E
      value = QString::number(acc_details.electrometer_fee_, 'f', 2);
      row_data += value + ","; // F   
      value = QString::number(acc_details.total_power_cons_cost_, 'f', 2);
      row_data += value + ","; // G
      value = QString::number(acc_details.power_consumption_cost_, 'f', 2);
      row_data += value + ","; // H
      row_data += ","; // I
      value = QString::number(acc_details.mul_react_power_factor_, 'f', 2);
      row_data += ","; // J
      value = QString::number(acc_details.total_cost_, 'f', 2);
      row_data += value + ","; // K
      value = QString::number(acc_details.reactive_curr_reading_);
      row_data += value + ","; // L
      value = QString::number(acc_details.vat_, 'f', 2);
      row_data += value + ","; // M
      value = QString::number(acc_details.other_total_react_pow_con_);
      row_data += value + ","; // N
      row_data += ","; // O
      value = QString::number(acc_details.reactive_prev_reading_);
      row_data += value + ","; // P
      value = QString::number(acc_details.react_power_factor_, 'f', 2);
      row_data += value + " ,"; // Q
      value = QString::number(acc_details.settlement_, 'f', 2);
      row_data += value + " ,";  // R
      row_data += " ,"; // S
      value = QString::number(acc_details.allowed_react_pow_con_);
      row_data += value + " ,"; // T
      value = QString::number(acc_details.total_react_pow_con_);
      row_data += value + " ,"; // U
      row_data += " ,"; // V
      row_data += " ,"; // W
      row_data += " ,"; // X
      value = QString::number(acc_details.power_consumption_);
      row_data += value + ","; // Y
      value = QString::number(acc_details.power_factor_, 'f', 2);
      row_data += value; // Z  

      stream << row_data << "\n";
    }
    csv_file.close();
  }

  std::cout << "Saved the data in the " << file_name_.toStdString() << "."
    << std::endl;
}

row_data += QStringLiteral("\"Innovice\nNumber\",");
#endif
