#include "parser_1_lines.h"

#include "utilities.h"

void Parser1Lines::Line1(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);
  //Account Number, Position 6 
  try
  {
    QString token = line_data.at(6);
    QString value = Utilities::ConvertEnglish(token);
    
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
}

void Parser1Lines::Line3(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);
  // TODO: Need to get the name of the field
  //Data, position 6
  try
  {
    QString token = line_data.at(6);
    QString value = Utilities::ConvertEnglish(token);
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Subscription Number;";
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
    QString date = Utilities::ToDate(token).trimmed();    

    if (date.size() > 0)
    {
      acc_details->invoice_date_ = date;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Invoice Date;";
    }
  }
  catch (...)
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
  }
  catch (...)
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
  }
  catch (...)
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
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Invoice Number;";
  }
}

void Parser1Lines::Line7(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);
 
  // Current Reading, Position 0 
  try
  {
    QString token = line_data.at(0);
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

  // Previous Reading, Position 1 
  try
  {
    QString token = line_data.at(1);
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
  }
  catch (...)
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
}

void Parser1Lines::Line9(QStringList data, AccountDetails* acc_details)
{
  Line line_data = Utilities::Convert(data);

  // TODO: Position 0

  try
  {
    QString token = line_data.at(0);
    QString value = Utilities::ConvertEnglish(token);

    /*if (value.size() > 0)
    {
      acc_details->power_consumption_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Power Consumption;";
    }*/
  } catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Power Consumption;";
  }

  // Position 4
  // TODO:

  try
  {
    QString token = line_data.at(4);
    QString value = Utilities::ConvertEnglish(token);

    /*if (value.size() > 0)
    {
      acc_details->power_consumption_ = value;
    } else
    {
      acc_details->parsing_ = "Partial";
      acc_details->reason_ += "No Power Consumption;";
    }*/
  }
  catch (...)
  {
    acc_details->parsing_ = "Partial";
    acc_details->reason_ += "Not Power Consumption;";
  }
}