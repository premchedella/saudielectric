#include "excel_write.h"

#include <ActiveQt/QAxWidget>
#include <ActiveQt/QAxObject>

#include <QtCore\QDir>

#include "../parse_data.h"

ExcelWrite::ExcelWrite(QString file_name)
{
  file_name_ = QDir::toNativeSeparators(file_name);
}

ExcelWrite::~ExcelWrite()
{

}

void ExcelWrite::Write(int type)
{
  QAxObject* excel = new QAxObject("Excel.Application");  

  //workbooks pointer
  QAxObject* workbooks = excel->querySubObject("WorkBooks");
  workbooks->dynamicCall("Add"); // Add new workbook
  QAxObject* workbook = excel->querySubObject("ActiveWorkBook");
  QAxObject* sheets = workbook->querySubObject("WorkSheets");

  QStringList row_values;
  row_values << "Subscription Number";
  row_values << "Type";  
  row_values << "Account Number";  
  row_values << "Electro Meter Number";
  row_values << "Invoice Date";
  row_values << "Invoice Number";
  row_values << "Reading From";
  row_values << "Reading To";
  row_values << "Reading Days";
  row_values << "Previous Reading";
  row_values << "Current Reading";
  row_values << "Active Power Consumption";
  row_values << "Reactive Power Consumption";
  row_values << "Allowed Consumption";
  row_values << "Total Consumption";
  row_values << "Capacity";
  row_values << "Factor";
  row_values << "Power Factor";
  row_values << "Active Power Consumption";
  row_values << "Reactive Power Consumption";
  row_values << "Settlement";
  row_values << "Electrometer Fee";
  row_values << "Total Consumption Cost";
  row_values << "Total Cost";
  row_values << "Name";
  row_values << "Address";

    //Get the First Sheet 
  QAxObject* sheet = sheets->querySubObject("Item( int )", 1);

  //Write the header

  QVariant var_row_data(row_values);
  QAxObject *range = sheet->querySubObject("Range(A1, Z1)");
  range->dynamicCall("setValue(const QVariant&)", var_row_data);

  std::vector<AccountDetails> data;
  std::vector<unsigned int> types = ParseData::GetTypes();
  if (type < types.size())
  {
    data = ParseData::GetDataInfo(types.at(type));
  } else
  {
    data = ParseData::GetDataInfo();
  }

  for (unsigned int index = 0; index < data.size(); index++)
  {
    row_values.clear();
    AccountDetails acc_details = data.at(index);

    QString range = "Range(A" + QString::number(index + 2) + ", Z"
        + QString::number(index + 2) + ")";
    QAxObject* range1 = sheet->querySubObject(range.toStdString().c_str());
    /*
    row_values << QString::number(acc_details.subscription_num_);
    row_values << QString::number(acc_details.type_);
    row_values << QString::number(acc_details.account_num_);
    row_values << QString::number(acc_details.electrometer_num_);
    row_values << acc_details.invoice_date_;
    row_values << QString::number(acc_details.invoice_num_);
    row_values << acc_details.reading_from_;
    row_values << acc_details.reading_to_;
    row_values << QString::number(acc_details.reading_days_);
    row_values << QString::number(acc_details.prev_reading_);
    row_values << QString::number(acc_details.curr_reading_);

    */
    /*
    row_values << QString::number(acc_details.active_pow_cons_);
    row_values << QString::number(acc_details.reactive_pow_cons_);
    row_values << QString::number(acc_details.allowed_cons_);
    row_values << QString::number(acc_details.total_cons_);
    row_values << QString::number(acc_details.capacity_);
    row_values << QString::number(acc_details.factor_, 'f', 2);
    row_values << QString::number(acc_details.power_factor_, 'f', 2);
    row_values << QString::number(acc_details.active_pow_cons_cost_, 'f', 2);
    row_values << QString::number(acc_details.reactive_pow_cons_cost_, 'f', 2);
    row_values << QString::number(acc_details.settlement_, 'f', 2);
    row_values << QString::number(acc_details.electrometer_fee_, 'f', 2);
    row_values << QString::number(acc_details.total_cons_cost_, 'f', 2);
    row_values << QString::number(acc_details.total_cost_, 'f', 2);
*/
    row_values << acc_details.name_;
    row_values << acc_details.address_;    
    var_row_data = QVariant(row_values);        
    range1->dynamicCall("setValue(const QVariant&)", var_row_data);     
  }
      
  workbook->dynamicCall("SaveAs(QString&)", file_name_);
  workbook->dynamicCall("Close (Boolean)", false);
  excel->dynamicCall("Quit()");

  std::cout << "Saved the data in the " << file_name_.toStdString() << "."
      << std::endl;
}

void ExcelWrite::WriteBlocks()
{

}



/* Displays the number in a format */
/*QString number_format = "###";

QAxObject* range1 = sheet->querySubObject("Range(A2, A23)");
range1->dynamicCall("SetNumberFormat(const QString&)", number_format);*/


//Following is the code to display the values in the corresponding data
// types, but the values displayed with E.
/*
QVariantList var_row_values;
var_row_values << QVariant(acc_details.subscription_num_);
var_row_values << QVariant(acc_details.type_);
QString range = "Range(A" + QString::number(index + 2) + ", B"
+ QString::number(index + 2) + ")";
QAxObject* range1 = sheet->querySubObject(range.toStdString().c_str());
range1->dynamicCall("setValue(const QVariant&)", QVariant(var_row_values));

*/
/*
https://msdn.microsoft.com/en-us/VBA/Excel-VBA/articles/range-numberformat-property-excel#example
*/