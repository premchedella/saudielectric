#include "parse_data.h"

#include <algorithm>    // std::find

#include "utilities.h"

std::vector<AccountDetails> ParseData::account_details_;
std::vector<unsigned int> ParseData::types_;
std::vector<AccountDetails> ParseData::type_account_details_;

ParseData::ParseData()
{

}

ParseData::~ParseData()
{

}

void ParseData::FormData(Blocks data)
{
  std::cout << "Number of Residential Blocks = " << data.size() << std::endl;
  account_details_.clear();
  types_.clear();
   
  for (unsigned int index = 0; index < data.size(); index++)  
  {    
    QString eng_data;
    unsigned int type;
    Block data_block = data.at(index);

    QStringList line_data = data_block.at(2);
    eng_data = line_data.at(1);
    int position = eng_data.indexOf("_");
    eng_data = eng_data.mid(position + 1, eng_data.size());
    eng_data = Utilities::ConvertEnglish(eng_data);
    type = eng_data.toUInt();   

    std::vector<unsigned int>::iterator it;

    it = std::find(types_.begin(), types_.end(), type);
    if (it == types_.end())
    {
      types_.push_back(type);
    }

    switch (type)
    {
      case 1:
        ParseType1(data_block);        
        break;
      case 5:
        ParseType5(data_block);        
        break;
      case 12:
        ParseType12(data_block);        
        break;
      default:
        std::cout << "Not a valid Type = " << type << std::endl;
    }     
  }
}

std::vector<unsigned int> ParseData::GetTypes()
{
  return types_;
}

std::vector<AccountDetails> ParseData::GetDataInfo()
{
  return account_details_;
}

std::vector<AccountDetails> ParseData::GetDataInfo(unsigned int type)
{
  std::vector<AccountDetails> retval;
  std::vector<unsigned int>::iterator it;
  it = std::find(types_.begin(), types_.end(), type);
  if (it != types_.end())
  {
    //type_account_details_.clear();
    for (unsigned int index = 0; index < account_details_.size(); index++)
    {
      AccountDetails acc_details = account_details_.at(index);
      if (acc_details.type_ == type)
      {
        //type_account_details_.push_back(acc_details);
        retval.push_back(acc_details);
      }
    }
    //return type_account_details_;
  }
  return retval;
}

void ParseData::ParseType1(Block data_in)
{
  if (data_in.size() == 21)
  {
    ParseType12(data_in);
  } else
  {
    AccountDetails acc_details;

    QStringList line_data;
    QString eng_data;

    // Line Number 0 and 1 contains header and there is no use.
    // Line Number is 2
    line_data = data_in.at(2);

    // Electrometer Number, Position = 0
    eng_data = line_data.at(0);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.electrometer_num_ = eng_data.toUInt();

    //Type, Position = 1
    eng_data = line_data.at(1);
    int position = eng_data.indexOf("_");
    eng_data = eng_data.mid(position + 1, eng_data.size());
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.type_ = eng_data.toUInt();

    //Meter Reading To, Position 2, data is Date and written in string
    eng_data = line_data.at(2);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.reading_to_ = eng_data;

    //Meter Reading From, Position 3, data is Date and written in string
    eng_data = line_data.at(3);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.reading_from_ = eng_data;

    //Factor, Position 4
    eng_data = line_data.at(4);
    eng_data = Utilities::ConvertEnglish(eng_data);
    eng_data = Utilities::ToFloat(eng_data);
    acc_details.factor_ = eng_data.toFloat();

    //Capacity, Position 5
    eng_data = line_data.at(5);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.capacity_ = eng_data.toUInt();

    //Account Number, Position 8
    eng_data = line_data.at(8);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.account_num_ = eng_data.toULongLong();
    
    //Line No.3
    line_data = data_in.at(3);

    //Days, postion 0 
    eng_data = line_data.at(0);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.reading_days_ = eng_data.toUInt();

    //Position 1 and 2 requires field name

    //Active Power Consumption, Position 5
    eng_data = line_data.at(5);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.active_pow_cons_ = eng_data.toULongLong();

    //Active Power Consumption Cost, postion 6
    eng_data = line_data.at(6);
    eng_data = Utilities::ConvertEnglish(eng_data);
    eng_data = Utilities::ToFloat(eng_data);
    acc_details.active_pow_cons_cost_ = eng_data.toFloat();

    //Subscription Number, Postion 7
    eng_data = line_data.at(7);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.subscription_num_ = eng_data.toULongLong();
        
    //Line 4
    line_data = data_in.at(4);

    //Invoice Date, Position 0, data is Date and written in string
    eng_data = line_data.at(0);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.invoice_date_ = eng_data;

    //Electrometer Fee, Postion 5
    eng_data = line_data.at(5);
    eng_data = Utilities::ConvertEnglish(eng_data);
    eng_data = Utilities::ToFloat(eng_data);
    acc_details.electrometer_fee_ = eng_data.toFloat();
    
    //Line 5
    line_data = data_in.at(5);

    //Inovice Number, Position 0
    eng_data = line_data.at(0);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.invoice_num_ = eng_data.toULongLong();

    //Total Power Consumption Cost, position 5
    eng_data = line_data.at(5);
    eng_data = Utilities::ConvertEnglish(eng_data);
    eng_data = Utilities::ToFloat(eng_data);
    acc_details.total_cons_cost_ = eng_data.toFloat();

    //Line 6
    line_data = data_in.at(6);

    //Settlement, postion 1
    eng_data = line_data.at(1);
    eng_data = Utilities::ConvertEnglish(eng_data);
    eng_data = Utilities::ToFloat(eng_data);
    acc_details.settlement_ = eng_data.toFloat();

    //Line 7
    line_data = data_in.at(7);

    //Total Cost, postion 2
    eng_data = line_data.at(2);
    eng_data = Utilities::ConvertEnglish(eng_data);
    eng_data = Utilities::ToFloat(eng_data);
    acc_details.total_cost_ = eng_data.toFloat();   
    
    acc_details.block_length_ = data_in.size();

    account_details_.push_back(acc_details);
  }
}

void ParseData::ParseType12(Block data_in)
{
  AccountDetails acc_details;

  QStringList line_data;
  QString eng_data;
  
  // Line Number 0 and 1 contains header and there is no use.
  // Line Number is 2
  line_data = data_in.at(2);

  // Electrometer Number, Position = 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.electrometer_num_ = eng_data.toUInt();

  //Type, Position = 1
  eng_data = line_data.at(1);
  int position = eng_data.indexOf("_");
  eng_data = eng_data.mid(position + 1, eng_data.size());
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.type_ = eng_data.toUInt();

  //Meter Reading To, Position 2, data is Date and written in string
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_to_ = eng_data;


  //Meter Reading From, Position 3, data is Date and written in string
  eng_data = line_data.at(3);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_from_ = eng_data;

  //Factor, Position 4
  eng_data = line_data.at(4);
  eng_data = Utilities::ConvertEnglish(eng_data);
  eng_data = Utilities::ToFloat(eng_data);
  acc_details.factor_ = eng_data.toFloat();

  //Capacity, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.capacity_ = eng_data.toUInt();

  //Account Number, Position 8
  eng_data = line_data.at(8);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.account_num_ = eng_data.toULongLong();


  //Line No.3
  line_data = data_in.at(3);

  //Days, postion 0 
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reading_days_ = eng_data.toUInt();

  //Position 1 and 2 requires field name

  //Active Power Consumption, Position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.active_pow_cons_ = eng_data.toULongLong();

  //Active Power Consumption Cost, postion 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  eng_data = Utilities::ToFloat(eng_data);
  acc_details.active_pow_cons_cost_ = eng_data.toFloat();

  //Subscription Number, Postion 7
  eng_data = line_data.at(7);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.subscription_num_ = eng_data.toULongLong();
  
  //Line 4
  line_data = data_in.at(4);

  //Position 0 and 1 requires field name

  //Reactive Power Consumption, Position 6
  eng_data = line_data.at(6);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.reactive_pow_cons_ = eng_data.toULongLong();

  //Reactive Power Consumption Cost, Position 7
  eng_data = line_data.at(7);
  eng_data = Utilities::ConvertEnglish(eng_data);
  eng_data = Utilities::ToFloat(eng_data);
  acc_details.reactive_pow_cons_cost_ = eng_data.toFloat();

  //Line 5
  line_data = data_in.at(5);

  //Invoice Date, Position 0, data is Date and written in string
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_date_ = eng_data;

  //Electrometer Fee, Postion 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  eng_data = Utilities::ToFloat(eng_data);
  acc_details.electrometer_fee_ = eng_data.toFloat();


  //Line 6
  line_data = data_in.at(6);

  //Inovice Number, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.invoice_num_ = eng_data.toULongLong();

  //Total Power Consumption Cost, position 5
  eng_data = line_data.at(5);
  eng_data = Utilities::ConvertEnglish(eng_data);
  eng_data = Utilities::ToFloat(eng_data);
  acc_details.total_cons_cost_ = eng_data.toFloat();

  //Line 7
  line_data = data_in.at(7);

  //Settlement, postion 1
  eng_data = line_data.at(1);
  eng_data = Utilities::ConvertEnglish(eng_data);
  eng_data = Utilities::ToFloat(eng_data);
  acc_details.settlement_ = eng_data.toFloat();

  //Line 8
  line_data = data_in.at(8);

  //Total Cost, postion 2
  eng_data = line_data.at(2);
  eng_data = Utilities::ConvertEnglish(eng_data);
  eng_data = Utilities::ToFloat(eng_data);
  acc_details.total_cost_ = eng_data.toFloat();

  //Line 10
  line_data = data_in.at(10);
  //Total Consumption, Position 0
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.total_cons_ = eng_data.toULongLong();

  //Allowed Consumption, Position 5
  eng_data = line_data.at(0);
  eng_data = Utilities::ConvertEnglish(eng_data);
  acc_details.allowed_cons_ = eng_data.toULongLong();
  
  //Power factor, Postion 12
  eng_data = Utilities::ConvertEnglish(line_data.at(12));
  eng_data = Utilities::ToFloat(eng_data);
  acc_details.power_factor_ = eng_data.toFloat();


  acc_details.block_length_ = data_in.size();

  account_details_.push_back(acc_details);
}

void ParseData::ParseType5(Block data_in)
{  
  if (data_in.size() == 14)
  {
    ParseType1(data_in);
  } else
  {
  
    AccountDetails acc_details;

    QStringList line_data;
    QString eng_data;

    // Line Number 0 and 1 contains header and there is no use.
    // Line Number is 2
    line_data = data_in.at(2);

    // Electrometer Number, Position = 0
    eng_data = line_data.at(0);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.electrometer_num_ = eng_data.toUInt();

    //Type, Position = 1
    eng_data = line_data.at(1);
    int position = eng_data.indexOf("_");
    eng_data = eng_data.mid(position + 1, eng_data.size());
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.type_ = eng_data.toUInt();

    //Meter Reading To, Position 2, data is Date and written in string
    eng_data = line_data.at(2);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.reading_to_ = eng_data;

    //Meter Reading From, Position 3, data is Date and written in string
    eng_data = line_data.at(3);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.reading_from_ = eng_data;

    //Factor, Position 4
    eng_data = line_data.at(4);
    eng_data = Utilities::ConvertEnglish(eng_data);
    eng_data = Utilities::ToFloat(eng_data);
    acc_details.factor_ = eng_data.toFloat();

    //Capacity, Position 5
    eng_data = line_data.at(5);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.capacity_ = eng_data.toUInt();

    //Account Number, Position 8
    eng_data = line_data.at(8);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.account_num_ = eng_data.toULongLong();

    //Line No.3
    line_data = data_in.at(3);

    //Days, postion 0 
    eng_data = line_data.at(0);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.reading_days_ = eng_data.toUInt();

    //Position 1 and 2 requires field name

    //Active Power Consumption, Position 5
    eng_data = line_data.at(5);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.active_pow_cons_ = eng_data.toULongLong();

    //Active Power Consumption Cost, postion 6
    eng_data = line_data.at(6);
    eng_data = Utilities::ConvertEnglish(eng_data);
    eng_data = Utilities::ToFloat(eng_data);
    acc_details.active_pow_cons_cost_ = eng_data.toFloat();

    //Subscription Number, Postion 7
    eng_data = line_data.at(7);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.subscription_num_ = eng_data.toULongLong();

    //Line 4
    line_data = data_in.at(4);

    //Invoice Date, Position 0, data is Date and written in string
    eng_data = line_data.at(0);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.invoice_date_ = eng_data;

    //Electrometer Fee, Postion 5
    eng_data = line_data.at(5);
    eng_data = Utilities::ConvertEnglish(eng_data);
    eng_data = Utilities::ToFloat(eng_data);
    acc_details.electrometer_fee_ = eng_data.toFloat();


    //Line 5
    line_data = data_in.at(5);

    //Inovice Number, Position 0
    eng_data = line_data.at(0);
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.invoice_num_ = eng_data.toULongLong();

    //Total Power Consumption Cost, position 5
    eng_data = line_data.at(5);
    eng_data = Utilities::ConvertEnglish(eng_data);
    eng_data = Utilities::ToFloat(eng_data);
    acc_details.total_cons_cost_ = eng_data.toFloat();

    //Line 6
    line_data = data_in.at(6);

    //Settlement, postion 1
    eng_data = line_data.at(1);
    eng_data = Utilities::ConvertEnglish(eng_data);
    eng_data = Utilities::ToFloat(eng_data);
    acc_details.settlement_ = eng_data.toFloat();

    //Line 7
    line_data = data_in.at(7);

    //Total Cost, postion 2
    eng_data = line_data.at(2);
    eng_data = Utilities::ConvertEnglish(eng_data);
    eng_data = Utilities::ToFloat(eng_data);
    acc_details.total_cost_ = eng_data.toFloat();

    acc_details.block_length_ = data_in.size();

    account_details_.push_back(acc_details);  
  }
}
