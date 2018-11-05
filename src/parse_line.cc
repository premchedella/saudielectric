#include "parse_line.h"

#include "utilities.h"
#include "common_types.h"

void ParseLine::Line2(QStringList data_line, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data_line);

  // Electrometer Number, Position = 0  
  try
  {
    QString token = line_data.at(0);
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->electrometer_num_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Electro Meter Number;";
      std::cout << "Electrometer Number, not valid." << std::endl;
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Electro Meter Number;";
    std::cout << "Electrometer Number is not available." << std::endl;
  }

  //Type, Position = 1
  try
  {
    QString token = line_data.at(1);
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
      std::cout << "Type, not valid." << std::endl;
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";    
    acc_details->reason_ += "Not Type;";
    std::cout << "Type is not available." << std::endl;
  }

  //SubType, Position = 1
  try
  {
    QString token = line_data.at(1);
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
      std::cout << "Sub Type, not valid." << std::endl;
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial"; 
    acc_details->reason_ += "Not Sub-Type;";
    std::cout << "Sub Type is not available." << std::endl;
  }

  //Meter Reading To, Position 2, data is Date and written in string
  try
  {
    QString token = line_data.at(2);
    token = Utilities::ConvertEnglish(token);
    QString value;
        
    Utilities::VatTypes vat_type = Utilities::GetVatType();

    if (vat_type == Utilities::VatTypes::WITH)
    {
      value = Utilities::ToDate(token).trimmed();
    } else if (vat_type == Utilities::VatTypes::PARTIAL)
    {
      value = Utilities::ToDate(token, '.').trimmed();
    } else if (vat_type == Utilities::VatTypes::WITH_OUT)
    {
      value = Utilities::ToGregorian(Utilities::ToDate(token).trimmed());
    }
    
    if (value.size() > 0)
    {
      acc_details->reading_to_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "Not Meter Reading To;";
      std::cout << "Meter Reading To, not valid." << std::endl;
    }    
  } catch (...)
  {
    acc_details->parsing_ = "Partial"; 
    acc_details->reason_ += "No Meter Reading To;";
    std::cout << "Meter Reading To is not available." << std::endl;
  }

  //Meter Reading From, Position 3, data is Date and written in string
  try
  {
    QString token = line_data.at(3);
    token = Utilities::ConvertEnglish(token);
    QString value;

    Utilities::VatTypes vat_type = Utilities::GetVatType();

    if (vat_type == Utilities::VatTypes::WITH)
    {
      value = Utilities::ToDate(token).trimmed();
    } else if (vat_type == Utilities::VatTypes::PARTIAL)
    {
      value = Utilities::ToDate(token, '.').trimmed();
    } else if (vat_type == Utilities::VatTypes::WITH_OUT)
    {
      value = Utilities::ToGregorian(Utilities::ToDate(token).trimmed());
    }

    if (value.size() > 0)
    {
      acc_details->reading_from_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "Not Meter Reading From;";
      std::cout << "Meter Reading From, not valid." << std::endl;
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Meter Reading From;";
    std::cout << "Meter Reading From is not available." << std::endl;
  }

  //Factor, Position 4
  try
  {
    QString token = line_data.at(4);    
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->power_factor_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "Not Power Factor;";
      std::cout << "Power Factor, not valid." << std::endl;
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Power Factor;";
    std::cout << "Factor is not available." << std::endl;
  }

  //Capacity, Position 5
  try
  {
    QString token = line_data.at(5);    
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->capacity_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "Not Capacity;";
      std::cout << "Capacity, not valid." << std::endl;
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "No Capacity;";
    std::cout << "Capacity is not available." << std::endl;
  }

  //Account Number, Position 6 or 8
  try
  {
    QString token = line_data.at(8);
    acc_details->account_num_ = Utilities::ConvertEnglish(token);
    // HACK: For some cases, the account number is reserved including data
    if (acc_details->account_num_ == "")
    {
      token = line_data.at(6);
      acc_details->account_num_ = Utilities::ConvertEnglish(token);
    }
    if (acc_details->account_num_.size() == 0)
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Account Number;";
      std::cout << "Account Number, not valid." << std::endl;
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Account Number;";
    std::cout << "Account Number is not available." << std::endl;
  }
}

void ParseLine::Line3(QStringList data_line, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data_line);
  //Number Days, postion 0 
  try
  {    
    QString token = line_data.at(0);    
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->reading_days_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Number of days;";
      std::cout << "Number of days, not valid." << std::endl;
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Number of Days;";
    std::cout << "Number of Days is not available." << std::endl;
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
      std::cout << "Current Reading, not valid." << std::endl;
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Current Reading;";
    std::cout << "Current Reading is not available." << std::endl;
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
      std::cout << "Previous Reading, not valid." << std::endl;
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Previous Reading;";
    std::cout << "Previous Reading is not available." << std::endl;
  }

  //Power Consumption, Position 5
  try
  {
    QString token = line_data.at(5);
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->power_consumption_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Power Consumption;";
      std::cout << "Power Consumption, not valid." << std::endl;      
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Power Consumption;";
    std::cout << "Power Consumption is not available." << std::endl;
  }

  //Power Consumption Cost, postion 6
  try
  {
    QString token = line_data.at(6);
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->power_consumption_cost_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Power Consumption Cost;";
      std::cout << "Power Consumption Cost, not valid." << std::endl;
    }
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Power Consumption Cost;";
    std::cout << "Power Consumption Cost is not available." << std::endl;
  }

  //Subscription Number, Postion 7
  try
  {    
    QString token = line_data.at(7);
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->subscription_num_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Subscription Number;";
      std::cout << "Subscription Number, not valid." << std::endl;      
    }
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Subscription Number;";
    std::cout << "Subscription Number is not available." << std::endl;
  }
}

void ParseLine::Line4(QStringList data_line, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data_line);

  //Invoice Date, Position 0, data is Date and written in string
  try
  {
    QString token = line_data.at(0);
    token = Utilities::ConvertEnglish(token);
    QString value;   

    Utilities::VatTypes vat_type = Utilities::GetVatType();

    if (vat_type == Utilities::VatTypes::WITH)
    {
      value = Utilities::ToDate(token).trimmed();
    } else if (vat_type == Utilities::VatTypes::PARTIAL)
    {
      value = Utilities::ToDate(token, '.').trimmed();
    } else if (vat_type == Utilities::VatTypes::WITH_OUT)
    {
      value = Utilities::ToGregorian(Utilities::ToDate(token).trimmed());
    }    
        
    if (value.size() > 0)
    {
      acc_details->invoice_date_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Invoice Date;";
      std::cout << "Invoice Date, not valid." << std::endl;
    }
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Invoice Date;";
    std::cout << "Invoice Date is not available." << std::endl;
  }

  //Electrometer Fee, Postion 5
  try
  {
    QString token = line_data.at(5);
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->electrometer_fee_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Electro Meter Fee;";
      std::cout << "Electrometer Fee, not valid." << std::endl;
    }    
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Electro Meter Fee;";
    std::cout << "Electrometer Fee is not available." << std::endl;
  }
}

void ParseLine::Line4Big(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);

  //Other Current Reading, Position 0
  try
  {    
    QString token = line_data.at(0);
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->other_curr_reading_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Other Current Reading;";
      std::cout << "Other Current Reading, not valid." << std::endl;
    }
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Other Current Reading;";
    std::cout << "Other Current Reading is not available." << std::endl;
  }
  
  //Other Previous Reading, Position 1 
  try  
  {
    QString token = line_data.at(1);
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->other_prev_reading_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Other Previous Reading;";
      std::cout << "Other Previous Reading, not valid." << std::endl;
    }
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Other Previous Reading;";
    std::cout << "Other Previous Reading is not available." << std::endl;
  }

  //Reactive Power Consumption, Position 6
  try
  {
    QString token = line_data.at(6);
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->other_pow_cons_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Other Power Consumption;";
      std::cout << "Other Power Consumption, not valid." << std::endl;
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Other Power Consumption;";
    std::cout << "Other Power Consumption is not available." << std::endl;
  }

  //Reactive Power Consumption Cost, Position 7
  try
  {
    QString token = line_data.at(7);
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->other_pow_cons_cost_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Other Power Consumption cost;";
      std::cout << "Other Power Consumption Cost, not valid." << std::endl;
    }
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Other Power Consumption cost;";
    std::cout << "Other Power Consumption Cost is not available." << std::endl;
  }
}

void ParseLine::Line5(QStringList data_line, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data_line);

  //Inovice Number, Position 0
  try
  {
    QString token = line_data.at(0);
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->invoice_num_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Invoice Number;";
      std::cout << "Invoice Number, not valid." << std::endl;
    }
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Invoice Number;";
    std::cout << "Invoice Number is not available." << std::endl;
  }

  //Total Power Consumption Cost, position 5
  try
  {
    QString token = line_data.at(5);
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->total_power_cons_cost_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Total Power Consumption Cost;";
      std::cout << "Total Power Consumption Cost, not valid." << std::endl;
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Total Power Consumption Cost;";
    std::cout << "Total Power Consumption cost is not available." << std::endl;
  }
}

void ParseLine::Line6(QStringList data_line, AccountDetails* acc_details)
{  
  Line line_data = Utilities::Convert(data_line);

  //Settlement, postion 1
  try
  {
    QString token = line_data.at(1);
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->settlement_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Settlement;";
      std::cout << "Settlement, not valid." << std::endl;
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Settlement;";
    std::cout << "Settlement is not available." << std::endl;
  }
}

void ParseLine::Line7(QStringList data_line, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data_line);

  //VAT, postion 4 or 5
  try
  {
    QString token;
    if (line_data.size() == 6)
    {
      token = line_data.at(5);
      acc_details->vat_ = Utilities::ConvertEnglish(token);
    } else
    {
      try
      {
        token = line_data.at(4);
        acc_details->vat_ = Utilities::ConvertEnglish(token);
      }
      catch (...)
      {
        acc_details->parsing_ = "Partial";        
        std::cout << "No VAT" << std::endl;
      }
    }
    
    if (acc_details->vat_.size() == 0)
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No VAT;";
      std::cout << "VAT, not valid." << std::endl;
    }
        
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not VAT;";
    std::cout << "VAT is not available." << std::endl;
  }
}

void ParseLine::Line8(QStringList data_line, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data_line);

  //Total Cost, postion 2
  try
  {
    QString token = line_data.at(2);
    QString value = Utilities::ConvertEnglish(token);
    if (value.size() > 0)
    {
      acc_details->total_cost_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Total Cost;";
      std::cout << "Total Cost, not valid." << std::endl;
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Total Cost;";
    std::cout << "Total Cost is not available." << std::endl;
  }
}

void ParseLine::Line11(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);

  //Total Consumption, Position 0
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
      std::cout << "Total Reactive Consumption, not valid." << std::endl;
    }
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Total Reactive Consumption;";
    std::cout << "Total Reactive Consumption is not available." << std::endl;
  }
    
  //Allowed Consumption, Position 5
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
      acc_details->reason_ += "No Allowed Consumption;";
      std::cout << "Allowed Consumption, not valid." << std::endl;
    }
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Allowed Consumption;";
    std::cout << "Allowed Consumption is not available." << std::endl;
  }

  //Power factor, Postion 12
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
      acc_details->reason_ += "No Power Factor;";
      std::cout << "Power Factor, not valid." << std::endl;
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Power Factor;";
    std::cout << "Power Factor is not available." << std::endl;
  }
}

void ParseLine::Line15(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);
  
  //Sub Previous Reading, Position 3
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
      acc_details->reason_ += "No Sub Previous Reading;";
      std::cout << "Sub Prev Reading, not valid." << std::endl;
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Sub Previous Reading;";
    std::cout << "Sub Prev Reading is not avaialble." << std::endl;
  }

  //Sub Current Reading, Position 5
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
      acc_details->reason_ += "No Sub Current Reading;";
      std::cout << "Sub Current Reading, not valid." << std::endl;
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Sub Current Reading;";
    std::cout << "Sub Current Reading is not avaialble." << std::endl;
  }
}

void ParseLine::Line15ParVat(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);

  //Sub Previous Reading, Position 3
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
      acc_details->reason_ += "No Sub Previous Reading;";
      std::cout << "Sub Prev Reading, not valid." << std::endl;
    }
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Sub Previous Reading;";
    std::cout << "Sub Prev Reading is not avaialble." << std::endl;
  }
}

void ParseLine::Line16ParVat(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);

  //Sub Current Reading, Position 5
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
      acc_details->reason_ += "No Sub Current Reading;";
      std::cout << "Sub Current Reading, not valid." << std::endl;
    }
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Sub Current Reading;";
    std::cout << "Sub Current Reading is not avaialble." << std::endl;
  }
}

void ParseLine::LineLast2(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);
  //Total Reactive Power Consumption, Position 0
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
      std::cout << "Total Reactive Power Consumtpion, not valid." << std::endl;
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Total Reactive Power Consumption;";
    std::cout << "Total Reactive Power Consumtpion not available." << std::endl;
  }

  //Multiplication Factor for Reactive Power, Position 2
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
      std::cout << "Factor for Reactive Power, not valid." << std::endl;
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Factor for Reactive Power;";
    std::cout << "Factor for Reactive Power not available." << std::endl;
  }

  //Previous Reactive Power Meter Reading, Position 4
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
      std::cout << "Reacive Previous Meter Reading, not valid." << std::endl;
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Reactive Previous Meter Reading;";
    std::cout << "Reacive Previous Meter Reading not available." << std::endl;
  }

  //Current Reactive Power Meter Reading, Position 6
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
      acc_details->reason_ += "No Reactive Current Meter Reading;";
      std::cout << "Reacive Current Meter Reading not available." << std::endl;
    }
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Reactive Current Meter Reading;";
    std::cout << "Reacive Current Meter Reading not available." << std::endl;
  }
}
