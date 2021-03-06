﻿#include "parser_1_lines.h"

#include "utilities.h"
#include "common_types.h"


void Parser1Lines::Line1(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);
  // Account Number, Position 1 or 4 or 5 or 6 
  
  try
  {
    QString token = line_data.at(1);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() == 0)
    {
      token = line_data.at(4);
      value = Utilities::ConvertEnglish(token);
    }
    
    if (value.size() == 0)
    {
      token = line_data.at(5);
      value = Utilities::ConvertEnglish(token);
    }

    if (value.size() == 0)
    {
      token = line_data.at(6);
      value = Utilities::ConvertEnglish(token);
    }

    if (value.size() > 0)
    {
      acc_details->account_num_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Account Number;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Account Number;";
  }

#if PRINT_FIELD_VALUE
  std::cout << "Account Number: " << 
      acc_details->account_num_.toStdString() << std::endl;
#endif
}

void Parser1Lines::Line2(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);

  //Subscription Number, Position 1 
  try
  {
    QString token = line_data.at(1);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() > 0)
    {
      acc_details->subscription_num_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Subscription Number;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Subscription Number;";
  }
  
#if PRINT_FIELD_VALUE
  std::cout << "Subscription Number: " << 
      acc_details->subscription_num_.toStdString() << std::endl;
#endif
}

void Parser1Lines::Line3(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);
  // TODO: Need to get the name of the field -- Site Number
  // Data, position 4 or 6 or 7 or 9 or 10
  try
  {
    QString token = line_data.at(4);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() == 0)
    {
      token = line_data.at(6);
      value = Utilities::ConvertEnglish(token);
    }

    if (value.size() == 0)
    {
      token = line_data.at(7);
      value = Utilities::ConvertEnglish(token);
    }
    
    if (value.size() == 0)
    {
      token = line_data.at(9);
      value = Utilities::ConvertEnglish(token);
    }

    if (value.size() == 0)
    {
      token = line_data.at(10);
      value = Utilities::ConvertEnglish(token);
    }

      

#if PRINT_FIELD_VALUE
    std::cout << "New Field, Site Number: " <<
      value.toStdString() << std::endl;
#endif
  } catch (...)
  {
    std::cout << "Not a Site Number." << std::endl;
  }
}

void Parser1Lines::Line4(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);

  //Invoice Date, Position 0 
  try
  {
    QString token = line_data.at(0);
    token = Utilities::ConvertEnglish(token);   
    QString date = Utilities::ToDateMonth(token.trimmed());

    if (date.size() > 0)
    {
      acc_details->invoice_date_ = date;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Invoice Date;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Invoice Date;";
  }

  //Type, Position 3
  try
  {
    QString token = line_data.at(3);
    int position = token.indexOf("_");
    token = token.mid(position + 1, token.size());
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->type_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Type;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Type;";
  }

  //SubType, Position 3
  try
  {
    QString token = line_data.at(3);
    int position = token.indexOf("_");
    token = token.mid(0, position);
    QString value = Utilities::ToType(token);
    if (value.size() > 0)
    {
      acc_details->sub_type_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Sub-Type;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Sub-Type;";
  }

  //Invoice Number, Position 5 
  try
  {
    QString token = line_data.at(5);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() > 0)
    {
      acc_details->invoice_num_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Invoice Number;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Invoice Number;";
  }

#if PRINT_FIELD_VALUE
  std::cout << "Invoice Date: " <<
      acc_details->invoice_date_.toStdString() << ", ";
  std::cout << "Type: " <<
      acc_details->type_.toStdString() << ", ";
  std::cout << "Sub Type: " <<
      acc_details->sub_type_.toStdString() << ", ";
  std::cout << "Invoice Number: " <<
      acc_details->invoice_num_.toStdString() << std::endl;
#endif
}

void Parser1Lines::Line7(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);
 
  // Current Reading, Position 0 
  try
  {
    QString token = line_data.at(0);
    token = Utilities::ConvertEnglish(token);    
    QString date = Utilities::ToDateMonth(token.trimmed());

    if (date.size() > 0)
    {
      acc_details->reading_to_ = date;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Meter Reading To;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Meter Reading To;";
  }

  // Previous Reading, Position 1 
  try
  {
    QString token = line_data.at(1);
    token = Utilities::ConvertEnglish(token);
    QString date = Utilities::ToDateMonth(token.trimmed());

    if (date.size() > 0)
    {
      acc_details->reading_from_ = date;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Meter Reading From;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Meter Reading From;";
  }

  // Multiplication Factor, Position 2
  try
  {
    QString token = line_data.at(2);
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->power_factor_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Power Factor;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Power Factor;";
  }

  // Capacity, Position 3
  try
  {
    QString token = line_data.at(3);
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->capacity_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "Not Capacity;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Capacity;";
  }

  // Number of Days, Position 4
  try
  {
    QString token = line_data.at(4);
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->reading_days_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Number of days;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Number of Days;";
  }

  // Meter Number, Position 5
  try
  {
    QString token = line_data.at(5);
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->electrometer_num_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Electro Meter Number;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Electro Meter Number;";
  }

#if PRINT_FIELD_VALUE
  std::cout << "Reading To: " <<
    acc_details->reading_to_.toStdString() << ", ";
  std::cout << "Reading From: " <<
    acc_details->reading_from_.toStdString() << ", ";
  std::cout << "Power Factor: " <<
    acc_details->power_factor_.toStdString() << ", ";
  std::cout << "Capactiy: " <<
    acc_details->capacity_.toStdString() << ", ";
  std::cout << "Number of Days: " <<
    acc_details->reading_days_.toStdString() << ", ";
  std::cout << "Meter Number: " <<
    acc_details->electrometer_num_.toStdString() << std::endl;
#endif
}

void Parser1Lines::Line8(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);

  //Power Consumption, Position 0
  try
  {
    QString token = line_data.at(0);
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->power_consumption_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Power Consumption;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Power Consumption;";
  }

  //Current Reading, Position 1 
  try
  {
    QString token = line_data.at(1);
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->curr_reading_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Current Reading;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Current Reading;";
  }

  //Previous Reading, Position 2 
  try
  {
    QString token = line_data.at(2);
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->prev_reading_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Previous Reading;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Previous Reading;";
  } 
  
#if PRINT_FIELD_VALUE
  std::cout << "Current Reading: " <<
    acc_details->curr_reading_.toStdString() << ", ";
  std::cout << "Previous Reading: " <<
    acc_details->prev_reading_.toStdString() << ", ";
  std::cout << "Power Consumption: " <<
    acc_details->power_consumption_.toStdString() << std::endl;
#endif
}

void Parser1Lines::Line9(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);

  // Position 0 - Duration Cost

  try
  {
    QString token = line_data.at(0);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() > 0)
    {
      acc_details->total_power_cons_cost_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Durartion Cost;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Duration Cost;";
  }

  // Position 4 - Power Cost

  try
  {
    QString token = line_data.at(4);
    QString value = Utilities::ConvertEnglish(token);
    
    if (value.size() > 0)
    {
      acc_details->power_consumption_cost_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Power Cost;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Power Cost;";
  }

#if PRINT_FIELD_VALUE
  std::cout << "Duration Cost: " <<
      acc_details->total_power_cons_cost_.toStdString() << ", ";
  std::cout << "Power Cost: " <<
      acc_details->power_consumption_cost_.toStdString() << std::endl;
#endif
}

void Parser1Lines::Line10(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);

  if (line_data.size() == 15)
  {
    // Position 0 - Power Cost 5%
    try
    {
      QString token = line_data.at(0);
      QString value = Utilities::ConvertEnglish(token);
      if (value.size() > 0)
      {
        acc_details->power_cost_5_ = value;
      } else
      {
        acc_details->parsing_ = "Partial";
        acc_details->reason_ += "No Power Cost (5%);";
      }    
    } catch (...)
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "Not Power Cost (5%);";
    }

    // Position 6 - VAT 5%
    try
    {
      QString token = line_data.at(6);
      QString value = Utilities::ConvertEnglish(token);

      if (value.size() > 0)
      {
        acc_details->vat_ = value;
      } else
      {
        acc_details->parsing_ = "Partial";
        acc_details->reason_ += "No VAT (5%);";
      }
    } catch (...)
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "Not Power Cost (5%);";
    }
    
    // Position 12 - Meter Service
    try
    {
      QString token = line_data.at(12);
      QString value = Utilities::ConvertEnglish(token);

      if (value.size() > 0)
      {
        acc_details->electrometer_fee_ = value;
      } else
      {
        acc_details->parsing_ = "Partial";
        acc_details->reason_ += "No Meter Service;";
      }
    } catch (...)
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "Not Meter Service;";
    }    
  } else
  {
    // Position 0 - VAT 5%
    try
    {
      QString token = line_data.at(0);
      QString value = Utilities::ConvertEnglish(token);

      if (value.size() > 0)
      {
        acc_details->vat_ = value;
      } else
      {
        acc_details->parsing_ = "Partial";
        acc_details->reason_ += "No VAT (5%);";
      }
    }
    catch (...)
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "Not Power Cost (5%);";
    }

    // Position 6 - Meter Service
    try
    {
      QString token = line_data.at(6);
      QString value = Utilities::ConvertEnglish(token);

      if (value.size() > 0)
      {
        acc_details->electrometer_fee_ = value;
      } else
      {
        acc_details->parsing_ = "Partial";
        acc_details->reason_ += "No Meter Service;";
      }
    } catch (...)
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "Not Meter Service;";
    }
  }

#if PRINT_FIELD_VALUE
  std::cout << "Power Cost(5%): "
      << acc_details->power_cost_5_.toStdString() << ", ";
  std::cout << "VAT(5%): " << acc_details->vat_.toStdString() << ", ";
  std::cout << "Meter Service: " <<
      acc_details->electrometer_fee_.toStdString() << std::endl;
#endif
}

void Parser1Lines::Line10Small(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);

  // Position 0 - Power Cost (15%)
  try
  {
    QString token = line_data.at(0);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() > 0)
    {
      acc_details->power_cost_15_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Powr Cost(15%);";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Powr Cost(15%);";
  }

  // Position 6 - VAT (15%)
  try
  {
    QString token = line_data.at(6);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() > 0)
    {
      acc_details->vat_15_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No VAT(15%);";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not VAT(15%);";
  }

  // Position 12 - Other Fees (15%)
  try
  {
    QString token = line_data.at(12);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() > 0)
    {
      acc_details->other_fees_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Other Fees;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Other Fees;";
  }
  
#if PRINT_FIELD_VALUE
  std::cout << "Power Cost(15%): " <<
      acc_details->power_cost_15_.toStdString() << ", ";  
  std::cout << "VAT(15%): " <<
      acc_details->vat_15_.toStdString() << ", ";  
  std::cout << "Other Fee: " <<
      acc_details->other_fees_.toStdString() << std::endl;
#endif
}

void Parser1Lines::Line11(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);
  // Position 0 - Settlement

  try
  {
    QString token = line_data.at(0);
    QString value = Utilities::ConvertEnglish(token);    
    if (value.size() > 0)
    {
      acc_details->settlement_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Settlement;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Settlement;";
  }

#if PRINT_FIELD_VALUE
  std::cout << "Settlement: " <<
    acc_details->settlement_.toStdString() << std::endl;
#endif
}

void Parser1Lines::Line11Small(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);
  // Position 0 - Settlement

  try
  {
    QString token = line_data.at(0);
    QString value = Utilities::ConvertEnglish(token);
    
    if (value.size() > 0)
    {
      acc_details->settlement_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Settlement;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Settlement;";
  }

  // Position 4 - Other Fees
  try
  {
    QString token = line_data.at(4);
    QString value = Utilities::ConvertEnglish(token);
    
    if (value.size() > 0)
    {
      acc_details->other_fees_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Other Fees;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Other Fees;";
  }

#if PRINT_FIELD_VALUE
  std::cout << "Settlement: " <<
      acc_details->settlement_.toStdString() << ", ";
  std::cout << "Other Fees: " <<
     acc_details->other_fees_.toStdString() << std::endl;
#endif
}

void Parser1Lines::Line11Big(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);
  // Position 0 - Taxable Amount

  try
  {
    QString token = line_data.at(0);
    QString value = Utilities::ConvertEnglish(token);
    
    if (value.size() > 0)
    {
      acc_details->taxable_amount_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Taxable Amount;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Taxable Amount;";
  }
  
  try
  {
    QString token = line_data.at(4);
    QString value = Utilities::ConvertEnglish(token);    
    
    if (value.size() > 0)
    {
      acc_details->other_pow_cons_cost_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Reactive Power Cost;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Reactive Power Cost;";
  }  

#if PRINT_FIELD_VALUE
    std::cout << "Taxable Amount: " <<
        acc_details->taxable_amount_.toStdString() << ", ";
    std::cout << "Reactive Power Cost: " <<
        acc_details->other_pow_cons_cost_.toStdString() << std::endl;
#endif
}

void Parser1Lines::Line12(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);
  // Position 0 - Taxable Amount
  try
  {
    QString token = line_data.at(0);
    QString value = Utilities::ConvertEnglish(token);
    
    if (value.size() > 0)
    {
      acc_details->taxable_amount_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Taxable Amount;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Taxable Amount;";
  }

#if PRINT_FIELD_VALUE
  std::cout << "Amount Includes Tax: " <<
      acc_details->taxable_amount_.toStdString() << std::endl;
#endif
}

void Parser1Lines::Line12Big(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);

  //Position 0 - Non Taxable Amount

  try
  {
    QString token = line_data.at(0);
    QString value = Utilities::ConvertEnglish(token);    

    if (value.size() > 0)
    {
      acc_details->non_taxable_amount_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Non Taxable Amount;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Non Taxable Amount;";
  }

  //Position 5 - Other Fees

  try
  {
    QString token = line_data.at(5);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() > 0)
    {
      acc_details->other_fees_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Other Fees;";
    }    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Other Fees;";
  }

#if PRINT_FIELD_VALUE
  std::cout << "Non Taxable Amount: " <<
    acc_details->non_taxable_amount_.toStdString() << ", ";
  std::cout << "Other Fees: " <<
    acc_details->other_fees_.toStdString() << std::endl;
#endif
}


void Parser1Lines::Line13(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);
  // Position 0 - Non Taxable Amount
  try
  {
    QString token = line_data.at(0);
    QString value = Utilities::ConvertEnglish(token);    
    if (value.size() > 0)
    {
      acc_details->non_taxable_amount_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Non Taxable Amount;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Non Taxable Amount;";
  }

#if PRINT_FIELD_VALUE
  std::cout << "Non Taxable Amount: " <<
      acc_details->non_taxable_amount_.toStdString() << std::endl;
#endif
}

void Parser1Lines::Line14(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);
  // Position 0 - Total Clost
  try
  {
    QString token = line_data.at(0);
    QString value = Utilities::ConvertEnglish(token);
    
    if (value.size() > 0)
    {
      acc_details->total_cost_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Total Cost;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Total Cost;";
  }

#if PRINT_FIELD_VALUE
  std::cout << "Total Cost: " <<
    acc_details->total_cost_.toStdString() << std::endl;
#endif
}

void Parser1Lines::Line9Big(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);
  //Passive Power Consumption, Position 0
  
  try
  {
    QString token = line_data.at(0);
    QString value = Utilities::ConvertEnglish(token);
    
    if (value.size() > 0)
    {
      acc_details->other_pow_cons_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Other Power Consumption;";
    }    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Other Power Consumption;";
  }

  //Current Reading, Position 1 
  try
  {
    QString token = line_data.at(1);
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->other_curr_reading_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Other Current Reading;";
    }    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Other Current Reading;";
  }

  //Previous Reading, Position 2 
  try
  {
    QString token = line_data.at(2);
    QString value = Utilities::ConvertEnglish(token);
    
    if (value.size() > 0)
    {
      acc_details->other_prev_reading_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Other Previous Reading;";
    }    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Other Previous Reading;";
  }

#if PRINT_FIELD_VALUE
  std::cout << "Other Power Consumption = " << 
      acc_details->other_pow_cons_.toStdString() << ",";
  std::cout << "Current Reading = " << 
      acc_details->other_curr_reading_.toStdString() << ",";
  std::cout << "Previous Reading = " << 
      acc_details->other_prev_reading_.toStdString() << std::endl;
#endif  
}

void Parser1Lines::Line10Big15(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);

  // Position 0 - Power Cost (15%)
  try
  {
    QString token = line_data.at(0);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() > 0)
    {
      acc_details->power_cost_15_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Powr Cost(15%);";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Powr Cost(15%);";
  }

  // Position 6 - VAT (15%)
  try
  {
    QString token = line_data.at(6);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() > 0)
    {
      acc_details->vat_15_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No VAT(15%);";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not VAT(15%);";
  }

  try
  {
    QString token = line_data.at(12);
    QString value = Utilities::ConvertEnglish(token);
    
    if (value.size() > 0)
    {
      acc_details->other_pow_cons_cost_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Reactive Power Cost;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Reactive Power Cost;";
  }

#if PRINT_FIELD_VALUE
  std::cout << "Power Cost(15%): " <<
      acc_details->power_cost_15_.toStdString() << ", ";
  std::cout << "VAT(15%): " <<
      acc_details->vat_15_.toStdString() << ", ";
  std::cout << "Reactive Power Cost: " <<
      acc_details->other_pow_cons_cost_.toStdString() << std::endl;
#endif  
}

void Parser1Lines::Line11Big15(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);
  //Position 0 - Amount Includes Tax

  // Position 0 - Taxable Amount
  try
  {
    QString token = line_data.at(0);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() > 0)
    {
      acc_details->taxable_amount_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Taxable Amount;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Taxable Amount;";
  }


  
  //Position 4 - Other Fees
  try
  {
    QString token = line_data.at(4);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() > 0)
    {
      acc_details->other_fees_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Other Fees;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Other Fees;";
  }

#if PRINT_FIELD_VALUE
  std::cout << "New Field, Amount Includes Tax: " <<
      acc_details->taxable_amount_.toStdString() << ", ";
  std::cout << "Other Fees: " <<
      acc_details->other_fees_.toStdString() << std::endl;
#endif
}

void Parser1Lines::Line16(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);
  // Position 0 - Total Reactive Power Consumption

  try
  {
    QString token = line_data.at(0);
    QString value = Utilities::ConvertEnglish(token);    

    if (value.size() > 0)
    {
      acc_details->total_react_pow_con_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Total Reactive Consumption;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Total Reactive Consumption;";
  }

  //Position 5 - Allowed Reactive Power Consumption

  try
  {
    QString token = line_data.at(5);
    QString value = Utilities::ConvertEnglish(token);
    
    if (value.size() > 0)
    {
      acc_details->allowed_react_pow_con_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Allowed Reactive Power Consumption;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Allowed Reactive Power Consumption;";
  }

  //Position 12 - Power Factor

  try
  {
    QString token = line_data.at(12);
    QString value = Utilities::ConvertEnglish(token);
    
    if (value.size() > 0)
    {
      acc_details->react_power_factor_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Reactive Power Factor;";
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Reactive Power Factor;";
  }

#if PRINT_FIELD_VALUE
  std::cout << "Total Reactive Power Consumption = " <<
      acc_details->total_react_pow_con_.toStdString() << ", ";
  std::cout << "Allowed Reactive Power Consumption = " <<
    acc_details->allowed_react_pow_con_.toStdString() << ", ";
  std::cout << "Reactive Power Factor = " << 
    acc_details->react_power_factor_.toStdString() << std::endl;
#endif
}

void Parser1Lines::Line20(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);
  //Position 4 - Previous Reading

  try
  {
    QString token = line_data.at(4);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() > 0)
    {
      acc_details->sub_prev_reading_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Previous Reading;";
    }    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Previous Reading;";
  }

  //Position 6 - Current Reading

  try
  {
    QString token = line_data.at(6);
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->sub_curr_reading_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Previous Reading;";
    }    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Current Reading;";
  }

#if PRINT_FIELD_VALUE
  std::cout << "Previous Reading = " << 
      acc_details->sub_prev_reading_.toStdString() << ", ";
  std::cout << "Current Reading = " << 
      acc_details->sub_curr_reading_.toStdString() << std::endl;
#endif
}

void Parser1Lines::LineLast(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);
  //Position 0 - Reactive Power Total Consumption

  try
  {
    QString token = line_data.at(0);
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->other_total_react_pow_con_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Total Reactive Power Consumption;";
    }   
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Total Reactive Power Consumption;";
  }

  //Position 2 - Reactive Power  Multiplication Factor

  try
  {
    QString token = line_data.at(2);
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->mul_react_power_factor_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Factor for Reactive Power;";
    }    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Factor for Reactive Power;";
  }

  // Position 4 - Reactive Power Previous Reading 

  try
  {
    QString token = line_data.at(4);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() > 0)
    {
      acc_details->reactive_prev_reading_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Reactive Previous Meter Reading;";
    }    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Reactive Previous Meter Reading;";
  }

  // Position 6 - Reactive Power Current Reading 

  try
  {
    QString token = line_data.at(6);
    QString value = Utilities::ConvertEnglish(token);

    if (value.size() > 0)
    {
      acc_details->reactive_curr_reading_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Reactive Previous Meter Reading;";
    }    
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Reactive Previous Meter Reading;";
  }

#if PRINT_FIELD_VALUE
  std::cout << "Reactive Power: ";
  std::cout << "Total Consumption = " << 
      acc_details->other_total_react_pow_con_.toStdString() << ", ";
  std::cout << "Multiplication Factor = " << 
      acc_details->mul_react_power_factor_.toStdString() << ", ";
  std::cout << "Previous Reading = " << 
      acc_details->reactive_prev_reading_.toStdString() << ", ";
  std::cout << "Current Reading = " << 
      acc_details->reactive_curr_reading_.toStdString() << std::endl;
#endif
}

bool Parser1Lines::Is15VatExtra(QStringList data)
{
  bool is_flag = false;
  Line line_data = Utilities::Convert(data);

  QString extra_1 = QStringLiteral(u")(%");
  QString extra_2 = QStringLiteral(u"١٥");
  if (line_data.size() >=10 )
  {
    if ((line_data[10] == extra_1) && (line_data[11] == extra_2))
    {
      is_flag = true;
    }
  }  

  return is_flag;
}