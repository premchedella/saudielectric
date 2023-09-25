#include "parser_3_summary.h"

#include <algorithm>    // std::find

#include "utilities.h"


std::vector<SummaryData> Parser3Summary::summary_data_;

SummaryData::SummaryData()
{
  no_ = " ";
  v_name_ = " ";
  name_ = " ";
  value_ = " ";
  complete_ = " ";
  reason_ = " ";
}

SummaryData::~SummaryData()
{

}

Parser3Summary::Parser3Summary()
{

}

Parser3Summary::~Parser3Summary()
{
  
}

void Parser3Summary::ParseData(Block data)
{  
  std::cout << "Parse Summary Data." << std::endl;
    

  QString no = "#";
  QString v_name = "Variable Name";
  QString name = "English Name";
  QString s_value = "Value";
  QString complete = "Availablility";
  QString reason = "Reason";
  
  AddSummaryData(no, v_name, name, s_value, complete, reason);

  /*for (unsigned int index = 0; index < data.size(); index++)
  {
    QStringList line_data = data.at(index);
  }*/

  // Line Number is 2
  int line_no = 1;

  QStringList line_data = data.at(line_no);
  ParseLine1(line_data);

  /* Line No. 3 */
  line_no = 2;
  line_data = data.at(line_no);
  ParseLine2(line_data);

  /* Line No. 4 */
  line_no = 3;
  line_data = data.at(line_no);
  ParseLine3(line_data);

  /* Line No. 5 */
  line_no = 4;
  line_data = data.at(line_no);
  ParseLine4(line_data);
  

  /* Line No. 13 */
  line_no = 12;
  line_data = data.at(line_no);
  ParseLine12(line_data);

  /* Line No. 13 */
  line_no = 13;
  line_data = data.at(line_no);
  ParseLine13(line_data);

  /* Line No. 14 */
  line_no = 14;
  line_data = data.at(line_no);
  ParseLine14(line_data);

  /* Line No. 15 */
  line_no = 15;
  line_data = data.at(line_no);
  ParseLine15(line_data);

  /* Line No. 16 */
  line_no = 16;
  line_data = data.at(line_no);
  ParseLine16(line_data);

 // Not required the following
 # if 0  
  /* Line No. 18 */
  line_no = 18;
  line_data = data.at(line_no);
  ParseLine18(line_data);

  /* Line No. 20 */
  line_no = 20;
  line_data = data.at(line_no);
  ParseLine20(line_data);

  /* Line No. 28 */
  line_no = 28;
  line_data = data.at(line_no);
  ParseLine28(line_data);

  /* Line No. 29 */
  line_no = 29;
  line_data = data.at(line_no);
  ParseLine29(line_data);
#endif

}


std::vector<SummaryData> Parser3Summary::GetSummaryData()
{
  return summary_data_;
}

void Parser3Summary::AddSummaryData(QString no, QString v_name, QString name,
      QString value, QString complete, QString reason)
{
  SummaryData summary_data;
  summary_data.no_ = no;
  summary_data.v_name_ = v_name;
  summary_data.name_ = name;
  summary_data.value_ = value;
  summary_data.complete_ = complete;
  summary_data.reason_ = reason;

  summary_data_.push_back(summary_data);
}

void Parser3Summary::ParseLine1(QStringList data)
{
  QString no = "6";
  QString v_name = "vat_number";
  QString name = "VAT Number";
  QString s_value = " ";
  QString complete = "complete";
  QString reason = " ";

  //Read Position 0
  QString token = data.at(0);
  QString value = Utilities::ConvertEnglish(token);

  if (value.size() > 0)
  {
    s_value = value;
  } else
  {
    complete = "Partial";
    reason = "Line 2: VAT Number value not availble.";
  }

  AddSummaryData(no, v_name, name, s_value, complete, reason);
}

void Parser3Summary::ParseLine2(QStringList data)
{ 
  QString no = "4";
  QString v_name = "invoice_issue_date";
  QString name = "Invoice Issue Date";
  QString s_value = " ";
  QString complete = "complete";
  QString reason = " ";

  //Read Position 0
  QString token = data.at(0);
  QString value = Utilities::ConvertEnglish(token);
  value = Utilities::ToDateMonth(value.trimmed());

  if (value.size() > 0)
  {
    s_value = value;
  } else
  {
    complete = "Partial";
    reason = "Line 3: Invoice Issue Date value not availble";
  }

  AddSummaryData(no, v_name, name, s_value, complete, reason);

  token = data.at(3);
  value = Utilities::ConvertEnglish(token);

  no = "1";
  v_name = "claim_number";
  name = "Claim Number";
  s_value = " ";
  complete = "complete";
  reason = " ";

  if (value.size() > 0)
  {
    s_value = value;
  } else
  {
    complete = "Partial";
    reason = "Line 3: Claim Number value not availble";
  }

  AddSummaryData(no, v_name, name, s_value, complete, reason);
}

void Parser3Summary::ParseLine3(QStringList data)
{
  QString no = "5";
  QString v_name = "invoice_period";
  QString name = "Invoice Period";
  QString s_value = " ";
  QString complete = "complete";
  QString reason = " ";

  //Read Position 0
  QString token = data.at(0);
  QString month = token;
  QString a_value = token.toUtf8();
  int i_month = Utilities::GetMonthNumber(token);

  if (i_month == 0)
  {
    complete = "Partial";
    reason = "Line 4: Invoice Period Month value, not availble";
  }
    
  //Read Position 1
  token = data.at(1);
  QString value = Utilities::ConvertEnglish(token);  

  if (value.size() > 0)
  {    
    s_value = value;
    s_value = QString::number(i_month) + " " + s_value;    
  } else
  {
    complete = "Partial";
    reason = "Line 4: Invoice Period value not availble";
  }

  AddSummaryData(no, v_name, name, s_value, complete, reason);

  token = data.at(5);
  value = Utilities::ConvertEnglish(token);

  no = "2";
  v_name = "claim_account";
  name = "Claim Account";
  s_value = " ";
  complete = "complete";
  reason = " ";

  if (value.size() > 0)
  {
    s_value = value;
  } else
  {
    complete = "Partial";
    reason = "Line 4: Claim Account value not availble";
  }

  AddSummaryData(no, v_name, name, s_value, complete, reason);
}

void Parser3Summary::ParseLine4(QStringList data)
{  
  QString no = "3";
  QString v_name = "circle_code";
  QString name = "Circle Code";
  QString s_value = " ";
  QString complete = "complete";
  QString reason = " ";

  //Read Position 2
  QString token = data.at(2);
  QString value = Utilities::ConvertEnglish(token);
    
  if (value.size() > 0)
  {
    s_value = value;
  } else
  {
    complete = "Partial";
    reason = "Line 5: Circle Code value not availble";
  }
  AddSummaryData(no, v_name, name, s_value, complete, reason);
}

void Parser3Summary::ParseLine12(QStringList data)
{
  //Read Position 0
  QString token = data.at(0);
  QString value = Utilities::ConvertEnglish(token);

  QString no = "14";
  QString v_name = "taxable_amount";
  QString name = "Taxable Amount";
  QString s_value = " ";
  QString complete = "complete";
  QString reason = " ";
  
  if (value.size() > 0)
  {
    s_value = value;
  } else
  {
    complete = "Partial";
    reason = "Line 13: Taxable Amount value not availble";
  }  
  AddSummaryData(no, v_name, name, s_value, complete, reason);

  //Read Position 4
  token = data.at(4);
  value = Utilities::ConvertEnglish(token);

  no = "8";
  v_name = "active_power_consumption_cost";
  name = "Active Power Consumption Cost";
  s_value = " ";
  complete = "complete";
  reason = " ";

  if (value.size() > 0)
  {
    s_value = value;
  } else
  {
    complete = "Partial";
    reason = "Line 13: Active Power Consumption Cost value not availble";
  }

  AddSummaryData(no, v_name, name, s_value, complete, reason);

  token = data.at(5);
  value = Utilities::ConvertEnglish(token);

  no = "7";
  v_name = "power_consumption";
  name = "Power Consumption";
  s_value = " ";
  complete = "complete";
  reason = " ";

  if (value.size() > 0)
  {
    s_value = value;
  } else
  {
    complete = "Partial";
    reason = "Line 13: Power Consumption value not availble";
  }

  AddSummaryData(no, v_name, name, s_value, complete, reason);
}

void Parser3Summary::ParseLine13(QStringList data)
{
  //Read Position 2
  QString token = data.at(2);
  QString value = Utilities::ConvertEnglish(token);

  QString no = "15";
  QString v_name = "vat";
  QString name = "VAT";
  QString s_value = " ";
  QString complete = "complete";
  QString reason = " ";

  if (value.size() > 0)
  {
    s_value = value;
  } else
  {
    complete = "Partial";
    reason = "Line 14: VAT value not availble";
  }

  AddSummaryData(no,v_name, name, s_value, complete, reason);

  # if 0 // Not required
  //Read Position 4
  token = data.at(4);
  value = Utilities::ConvertEnglish(token);

  name = "Name 12";
  s_value = " ";
  complete = "complete";
  reason = " ";

  if (value.size() > 0)
  {
    s_value = value + "%";
  } else
  {
    complete = "Partial";
    reason = "Line 14: Position 5 value not availble";
  }

  AddSummaryData(no, v_name, name, s_value, complete, reason);
#endif

  //Read Position 5
  token = data.at(5);
  value = Utilities::ConvertEnglish(token);

  no = "10";
  v_name = "reactive_power_consumption_cost";
  name = "Reactive Power Consumption Cost";
  s_value = " ";
  complete = "complete";
  reason = " ";

  if (value.size() > 0)
  {
    s_value = value;
  } else
  {
    complete = "Partial";
    reason = "Line 14: Reactive Power Consumption Cost value not availble";
  }

  AddSummaryData(no, v_name, name, s_value, complete, reason);

  //Read Position 6
  token = data.at(6);
  value = Utilities::ConvertEnglish(token);

  no = "9";
  v_name = "reactive_power_consumption";
  name = "Reactive Power Consumption";
  s_value = " ";
  complete = "complete";
  reason = " ";

  if (value.size() > 0)
  {
    s_value = value;
  } else
  {
    complete = "Partial";
    reason = "Line 14: Reactive Power Consumption value not availble";
  }
  AddSummaryData(no, v_name, name, s_value, complete, reason);
}

void Parser3Summary::ParseLine14(QStringList data)
{
  //Read Position 0
  QString token = data.at(0);
  QString value = Utilities::ConvertEnglish(token);

  QString no = "16";
  QString v_name = "cost";
  QString name = "Cost";
  QString s_value = " ";
  QString complete = "complete";
  QString reason = " ";

  if (value.size() > 0)
  {
    s_value = value;
  } else
  {
    complete = "Partial";
    reason = "Line 15: Cost value not availble";
  }
  AddSummaryData(no, v_name, name, s_value, complete, reason);

  //Read Position 4
  token = data.at(4);
  value = Utilities::ConvertEnglish(token);

  no = "11";
  v_name = "meter_service_cost";
  name = "Meter Service Cost";
  s_value = " ";
  complete = "complete";
  reason = " ";

  if (value.size() > 0)
  {
    s_value = value;
  } else
  {
    complete = "Partial";
    reason = "Line 15: Meter Service Cost value not availble";
  }
  AddSummaryData(no, v_name, name, s_value, complete, reason);
}

void Parser3Summary::ParseLine15(QStringList data)
{
  //Read Position 0
  QString token = data.at(0);
  QString value = Utilities::ConvertEnglish(token);

  QString no = "17";
  QString v_name = "non_taxable_amount";
  QString name = "Non Taxable Amount";
  QString s_value = " ";
  QString complete = "complete";
  QString reason = " ";

  if (value.size() > 0)
  {
    s_value = value;
  } else
  {
    complete = "Partial";
    reason = "Line 16: Non Taxable Amount value not availble";
  }
  AddSummaryData(no, v_name, name, s_value, complete, reason);

  //Read Position 5
  token = data.at(5);
  value = Utilities::ConvertEnglish(token);

  no = "12";
  v_name = "other_fees";
  name = "Other Fees";
  s_value = " ";
  complete = "complete";
  reason = " ";

  if (value.size() > 0)
  {
    s_value = value;
  } else
  {
    complete = "Partial";
    reason = "Line 16: Other Fees value not availble";
  }
  AddSummaryData(no, v_name, name, s_value, complete, reason);
}

void Parser3Summary::ParseLine16(QStringList data)
{
  //Read Position 2
  QString token = data.at(2);
  QString value = Utilities::ConvertEnglish(token);

  QString no = "18";
  QString v_name = "required_amount";
  QString name = "Required Amount";
  QString s_value = " ";
  QString complete = "complete";
  QString reason = " ";

  if (value.size() > 0)
  {
    s_value = value;
  } else
  {
    complete = "Partial";
    reason = "Line 17: Required Amount value not availble";
  }
  AddSummaryData(no, v_name, name, s_value, complete, reason);

  //Read Position 5
  token = data.at(5);
  value = Utilities::ConvertEnglish(token);

  no = "13";
  v_name = "settlements";
  name = "Settlements";
  s_value = " ";
  complete = "complete";
  reason = " ";

  if (value.size() > 0)
  {
    s_value = value;
  } else
  {
    complete = "Partial";
    reason = "Line 17: Settlements value not availble";
  }
  AddSummaryData(no, v_name, name, s_value, complete, reason);
}

void Parser3Summary::ParseLine18(QStringList data)
{
  //Read Position 17
  QString token = data.at(17);
  QString value = token.left(2) + Utilities::ConvertEnglish(token);

  QString no = "#";
  QString v_name = "Variable Name";
  QString name = "Name 21";
  QString s_value = " ";
  QString complete = "complete";
  QString reason = " ";

  if (value.size() > 0)
  {
    s_value = value;
  } else
  {
    complete = "Partial";
    reason = "Line 19: Position 18 value not availble";
  }
  AddSummaryData(no, v_name, name, s_value, complete, reason);
}

void Parser3Summary::ParseLine20(QStringList data)
{
  //Read Position 0
  QString token = data.at(0);
  QString value = token.left(token.size() -2);

  QString no = "#";
  QString v_name = "Variable Name";
  QString name = "Name 22";
  QString s_value = " ";
  QString complete = "complete";
  QString reason = " ";

  if (value.size() > 0)
  {
    s_value = value;
  } else
  {
    complete = "Partial";
    reason = "Line 21: Position 1 value not availble";
  }
  AddSummaryData(no, v_name, name, s_value, complete, reason);

  //Read Position 1
  token = data.at(1);
  value = token;

  name = "Name 23";
  s_value = " ";
  complete = "complete";
  reason = " ";

  if (value.size() > 0)
  {
    s_value = value;
  } else
  {
    complete = "Partial";
    reason = "Line 21: Position 2 value not availble";
  }
  AddSummaryData(no, v_name, name, s_value, complete, reason);
}

void Parser3Summary::ParseLine28(QStringList data)
{
  //Read Position 0
  QString token = data.at(0);
  QString value = Utilities::ConvertEnglish(token);

  QString no = "#";
  QString v_name = "Variable Name";
  QString name = "Name 24";
  QString s_value = " ";
  QString complete = "complete";
  QString reason = " ";

  if (value.size() > 0)
  {
    s_value = value;
  } else
  {
    complete = "Partial";
    reason = "Line 29: Position 1 value not availble";
  }
  AddSummaryData(no, v_name, name, s_value, complete, reason);

  //Read Position 2
  token = data.at(2);
  value = Utilities::ConvertEnglish(token);

  name = "Name 25";
  s_value = " ";
  complete = "complete";
  reason = " ";

  if (value.size() > 0)
  {
    s_value = value;
  } else
  {
    complete = "Partial";
    reason = "Line 29: Position 3 value not availble";
  }
  AddSummaryData(no, v_name, name, s_value, complete, reason);
}

void Parser3Summary::ParseLine29(QStringList data)
{
  //Read Position 0
  QString token = data.at(0);
  QString value = Utilities::ConvertEnglish(token);

  QString no = "#";
  QString v_name = "Variable Name";
  QString name = "Name 26";
  QString s_value = " ";
  QString complete = "complete";
  QString reason = " ";

  if (value.size() > 0)
  {
    s_value = value;
  } else
  {
    complete = "Partial";
    reason = "Line 30: Position 1 value not availble";
  }
  AddSummaryData(no, v_name, name, s_value, complete, reason);

  //Read Position 2
  token = data.at(2);
  value = Utilities::ConvertEnglish(token);

  name = "Name 27";
  s_value = " ";
  complete = "complete";
  reason = " ";

  if (value.size() > 0)
  {
    s_value = value;
  } else
  {
    complete = "Partial";
    reason = "Line 31: Position 3 value not availble";
  }
  AddSummaryData(no, v_name, name, s_value, complete, reason);
}


