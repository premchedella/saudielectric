#include "parser_4_summary.h"

#include <algorithm>    // std::find

#include "utilities.h"

std::vector<Summary4Data> Parser4Summary::summary_data_;

Summary4Data::Summary4Data()
{  
  name_ = " ";
  value_ = " ";
  complete_ = " ";
  reason_ = " ";
}

Summary4Data::~Summary4Data()
{

}

Parser4Summary::Parser4Summary()
{

}

Parser4Summary::~Parser4Summary()
{
  
}

void Parser4Summary::ParseData(Block data)
{
  std::cout << "Parse 4 Summary Data." << std::endl;
    
  QString name = "Name";  
  QString value = "Value";
  QString complete = "Availablility";
  QString reason = "Reason";
  
  AddSummaryData(name,value, complete, reason);
    
  // Line Number is 2
  int line_no = 1;

  QStringList line_data = data.at(line_no);
  ParseLine1(line_data);

  /* Line No. 3 */
  line_no++;
  line_data = data.at(line_no);
  ParseLine2(line_data);

  /* Line No. 4 */
  line_no++;
  line_data = data.at(line_no);
  ParseLine3(line_data);

  /* Line No. 5 */
  line_no++;
  line_data = data.at(line_no);
  ParseLine4(line_data);
  

  /* Line No. 9 */
  line_no = 10;
  line_data = data.at(line_no);
  ParseLine10(line_data);

  /* Line No. 10 */
  line_no++;
  line_data = data.at(line_no);
  ParseLine11(line_data);

  /* Line No. 11 */
  line_no++;
  line_data = data.at(line_no);
  ParseLine12(line_data);

  /* Line No. 12 */
  line_no++;
  line_data = data.at(line_no);
  ParseLine13(line_data);

  /* Line No. 14 */
  line_no++;
  line_data = data.at(line_no);
  ParseLine14(line_data); 
}


std::vector<Summary4Data> Parser4Summary::GetSummaryData()
{
  return summary_data_;
}

void Parser4Summary::AddSummaryData(QString name, QString value, QString complete,
    QString reason)
{
  Summary4Data summary_data;
  
  summary_data.name_ = name;
  summary_data.value_ = value;
  summary_data.complete_ = complete;
  summary_data.reason_ = reason;

  summary_data_.push_back(summary_data);
}

void Parser4Summary::ParseLine1(QStringList data)
{  
  QString name = "VAT Number";
  QString s_value = " ";
  QString complete = "complete";
  QString reason = " ";


  //Read Position 0
  try
  {
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
  }
  catch (...)
  {
    complete = "Partial";
    reason = "Line 2: VAT Number value not availble.";
  }

  AddSummaryData(name, s_value, complete, reason);
}

void Parser4Summary::ParseLine2(QStringList data)
{ 
  QString name = "Invoice Number";
  QString s_value = " ";
  QString complete = "complete";
  QString reason = " ";

  try
  {
    //Read Position 0
    QString token = data.at(0);
    QString value = Utilities::ConvertEnglish(token);  

    if (value.size() > 0)
    {
      s_value = value;
    } else
    {
      complete = "Partial";
      reason = "Line 3: Invoice Number not availble";
    }
  }
  catch (...)
  {
    complete = "Partial";
    reason = "Line 3: Invoice Number not availble";
  }

  AddSummaryData(name, s_value, complete, reason);

  name = "Collective Account Number";
  s_value = " ";
  complete = "complete";
  reason = " ";

  try
  {
    QString token = data.at(3);
    QString value = Utilities::ConvertEnglish(token);
    
    if (value.size() > 0)
    {
      s_value = value;
    } else
    {
      complete = "Partial";
      reason = "Line 3: Claim Account Number not availble";
    }
  }
  catch (...)
  {
    complete = "Partial";
    reason = "Line 3: Claim Account Number not availble";
  }

  AddSummaryData(name, s_value, complete, reason);
}

void Parser4Summary::ParseLine3(QStringList data)
{  
  QString name = "Invoice Issue Date";
  QString s_value = " ";
  QString complete = "complete";
  QString reason = " ";
  try
  {
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
      reason = "Line 4: Invoice Date, not availble";
    }
  } catch (...)
  {
    complete = "Partial";
    reason = "Line 4: Invoice Date, not availble";
  }
    
  
  AddSummaryData(name, s_value, complete, reason);

  name = "VAT Account";
  s_value = " ";
  complete = "complete";
  reason = " ";

  try
  {
    QString token = data.at(3);
    QString value = Utilities::ConvertEnglish(token);
      
    if (value.size() > 0)
    {
      s_value = value;
    } else
    {
      complete = "Partial";
      reason = "Line 4: VAT Account value not availble";
    }
  }
  catch (...)
  {
    complete = "Partial";
    reason = "Line 4: VAT Account value not availble";
  }  

  AddSummaryData(name, s_value, complete, reason);
}

void Parser4Summary::ParseLine4(QStringList data)
{  
  QString name = "Reading To (Date)";
  QString s_value = " ";
  QString complete = "complete";
  QString reason = " ";

  try
  {
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
      reason = "Line 5: Reading To Date value not availble";
    }
  } catch (...)
  {
    complete = "Partial";
    reason = "Line 5: Reading To Date value not availble";
  }
  AddSummaryData(name, s_value, complete, reason);

  name = "Reading From (Date)";
  s_value = " ";
  complete = "complete";
  reason = " ";

  try
  {
    //Read Position 2
    QString token = data.at(2);
    QString value = Utilities::ConvertEnglish(token);
    value = Utilities::ToDateMonth(value.trimmed());

    if (value.size() > 0)
    {
      s_value = value;
    } else
    {
      complete = "Partial";
      reason = "Line 5: Reading From Date value not availble";
    }
  }
  catch (...)
  {
    complete = "Partial";
    reason = "Line 5: Reading From Date value not availble";
  }
  AddSummaryData(name, s_value, complete, reason);

  name = "Account Number";
  s_value = " ";
  complete = "complete";
  reason = " ";

  try
  {
    //Read Position 2
    QString token = data.at(7);
    QString value = Utilities::ConvertEnglish(token);    

    if (value.size() > 0)
    {
      s_value = value;
    } else
    {
      complete = "Partial";
      reason = "Line 5: Account Number value not availble";
    }
  }
  catch (...)
  {
    complete = "Partial";
    reason = "Line 5: Account Number value not availble";
  }
  AddSummaryData(name, s_value, complete, reason);
}

void Parser4Summary::ParseLine10(QStringList data)
{
  QString name = "Taxable Amount";
  QString s_value = " ";
  QString complete = "complete";
  QString reason = " ";

  try
  {
    //Read Position 0
    QString token = data.at(0);
    QString value = Utilities::ConvertEnglish(token);    

    if (value.size() > 0)
    {
      s_value = value;
    } else
    {
      complete = "Partial";
      reason = "Line 10: Taxable Amount not availble";
    }
  }
  catch (...)
  {
    complete = "Partial";
    reason = "Line 10: Taxable Amount not availble";
  }
  AddSummaryData(name, s_value, complete, reason);
  
  name = "Active Power Consumption Cost";
  s_value = " ";
  complete = "complete";
  reason = " ";

  try
  {
    //Read Position 4
    QString token = data.at(4);
    QString value = Utilities::ConvertEnglish(token);    

    if (value.size() > 0)
    {
      s_value = value;
    } else
    {
      complete = "Partial";
      reason = "Line 10: Active Power Consumption Cost not availble";
    }
  }
  catch (...)
  {
    complete = "Partial";
    reason = "Line 10: Active Power Consumption Cost not availble";
  }
  AddSummaryData(name, s_value, complete, reason);

  name = "Active Power Consumption";
  s_value = " ";
  complete = "complete";
  reason = " ";

  try
  {
    //Read Position 5
    QString token = data.at(5);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() > 0)
    {
      s_value = value;
    } else
    {
      complete = "Partial";
      reason = "Line 10: Active Power Consumption not availble";
    }
  }
  catch (...)
  {
    complete = "Partial";
    reason = "Line 10: Active Power Consumption not availble";
  }
  AddSummaryData(name, s_value, complete, reason);
}

void Parser4Summary::ParseLine11(QStringList data)
{
  QString name = "VAT";
  QString s_value = " ";
  QString complete = "complete";
  QString reason = " ";

  try
  {
    //Read Position 2
    QString token = data.at(2);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() > 0)
    {
      s_value = value;
    } else
    {
      complete = "Partial";
      reason = "Line 11: VAT not availble";
    }
  }
  catch (...)
  {
    complete = "Partial";
    reason = "Line 11: VAT not availble";
  }
  AddSummaryData(name, s_value, complete, reason);

  name = "Reactive Power Consumption Cost";
  s_value = " ";
  complete = "complete";
  reason = " ";

  try
  {
    //Read Position 4
    QString token = data.at(4);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() > 0)
    {
      s_value = value;
} else
    {
      complete = "Partial";
      reason = "Line 11: Reactive Power Consumption Cost not availble";
    }
  }
  catch (...)
  {
    complete = "Partial";
    reason = "Line 11: Reactive Power Consumption Cost not availble";
  }
  AddSummaryData(name, s_value, complete, reason);

  name = "Reactive Power Consumption";
  s_value = " ";
  complete = "complete";
  reason = " ";

  try
  {
    //Read Position 5
    QString token = data.at(5);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() > 0)
    {
      s_value = value;
    } else
    {
      complete = "Partial";
      reason = "Line 11: Reactive Power Consumption not availble";
    }
  }
  catch (...)
  {
    complete = "Partial";
    reason = "Line 11: Reactive Power Consumption not availble";
  }
  AddSummaryData(name, s_value, complete, reason);
}

void Parser4Summary::ParseLine12(QStringList data)
{
  QString name = "Total Cost";
  QString s_value = " ";
  QString complete = "complete";
  QString reason = " ";

  try
  {
    //Read Position 0
    QString token = data.at(0);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() > 0)
    {
      s_value = value;
    } else
    {
      complete = "Partial";
      reason = "Line 12: Total Cost not availble";
    }
  }
  catch (...)
  {
    complete = "Partial";
    reason = "Line 12: Total Cost not availble";
  }
  AddSummaryData(name, s_value, complete, reason);

  name = "Meters Service Cost";
  s_value = " ";
  complete = "complete";
  reason = " ";

  try
  {
    //Read Position 4
    QString token = data.at(4);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() > 0)
    {
      s_value = value;
    } else
    {
      complete = "Partial";
      reason = "Line 12: Meters Service Cost not availble";
    }
  }
  catch (...)
  {
    complete = "Partial";
    reason = "Line 12: Meters Service Cost not availble";
  }
  AddSummaryData(name, s_value, complete, reason);
}

void Parser4Summary::ParseLine13(QStringList data)
{
  QString name = "Non-Taxable Amount";
  QString s_value = " ";
  QString complete = "complete";
  QString reason = " ";

  try
  {
    //Read Position 0
    QString token = data.at(0);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() > 0)
    {
      s_value = value;
    } else
    {
      complete = "Partial";
      reason = "Line 13: Non-Taxable Amount not availble";
    }
  }
  catch (...)
  {
    complete = "Partial";
    reason = "Line 13: Non-Taxable Amount not availble";
  }
  AddSummaryData(name, s_value, complete, reason);

  name = "Other Fees";
  s_value = " ";
  complete = "complete";
  reason = " ";

  try
  {
    //Read Position 5
    QString token = data.at(5);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() > 0)
    {
      s_value = value;
    } else
    {
      complete = "Partial";
      reason = "Line 13: Other Fees not availble";
    }
  }
  catch (...)
  {
    complete = "Partial";
    reason = "Line 13: Other Fees not availble";
  }
  AddSummaryData(name, s_value, complete, reason);
}

void Parser4Summary::ParseLine14(QStringList data)
{
  QString name = "Required Amount";
  QString s_value = " ";
  QString complete = "complete";
  QString reason = " ";

  try
  {
    //Read Position 2
    QString token = data.at(2);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() > 0)
    {
      s_value = value;
    } else
    {
      complete = "Partial";
      reason = "Line 14: Required Amount not availble";
    }
  }
  catch (...)
  {
    complete = "Partial";
    reason = "Line 14: Required Amount not availble";
  }
  AddSummaryData(name, s_value, complete, reason);

  name = "Settlements";
  s_value = " ";
  complete = "complete";
  reason = " ";

  try
  {
    //Read Position 5
    QString token = data.at(5);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() > 0)
    {
      s_value = value;
    } else
    {
      complete = "Partial";
      reason = "Line 14: Settlements not availble";
    }
  }
  catch (...)
  {
    complete = "Partial";
    reason = "Line 14: Settlements not availble";
  }
  AddSummaryData(name, s_value, complete, reason);
}
