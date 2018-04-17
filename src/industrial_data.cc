#include "industrial_data.h"

#include "utilities.h"

IndustrialData::IndustrialData()
{

}

IndustrialData::~IndustrialData()
{

}

void IndustrialData::FormData(Blocks data)
{
  std::cout << "Number of Industrial Blocks = " << data.size() << std::endl;
  account_details_.clear();
  for (unsigned int index = 0; index < data.size(); index++)
  {
    AccountDetails acc_details;
    QString eng_data;
    //qulonglong longlong_data = eng_data.toULongLong();

    Block data_block = data.at(index);
    QStringList line_data = data_block.at(2);
    eng_data = line_data.at(1);
    int position = eng_data.indexOf("_");
    eng_data = eng_data.mid(position + 1, eng_data.size());
    eng_data = Utilities::ConvertEnglish(eng_data);
    acc_details.type_ = eng_data.toUInt();

    eng_data = Utilities::ConvertEnglish(line_data.at(3));
    acc_details.reading_from_ = eng_data;
    eng_data = Utilities::ConvertEnglish(line_data.at(2));
    acc_details.reading_to_ = eng_data;

    line_data = data_block.at(3);    
    eng_data = Utilities::ConvertEnglish(line_data.at(7));    
    acc_details.subscription_num_ = eng_data.toULongLong();
    eng_data = Utilities::ConvertEnglish(line_data.at(5));
    acc_details.active_pow_cons_ = eng_data.toULongLong();
       
    eng_data = Utilities::ConvertEnglish(line_data.at(6));
    eng_data = Utilities::ToFloat(eng_data);
    acc_details.active_pow_cons_cost_ = eng_data.toFloat();

    line_data = data_block.at(4);
    eng_data = Utilities::ConvertEnglish(line_data.at(6));
    acc_details.reactive_pow_cons_ = eng_data.toULongLong();
          
    eng_data = Utilities::ConvertEnglish(line_data.at(7));
    eng_data = Utilities::ToFloat(eng_data);
    acc_details.reactive_pow_cons_cost_ = eng_data.toFloat();        

    line_data = data_block.at(7);
    eng_data = Utilities::ConvertEnglish(line_data.at(1));
    eng_data = Utilities::ToFloat(eng_data);
    acc_details.settlement_ = eng_data.toFloat();

    line_data = data_block.at(8);
    eng_data = Utilities::ConvertEnglish(line_data.at(1));
    eng_data = Utilities::ToFloat(eng_data);
    acc_details.total_cost_ = eng_data.toFloat();
        
    line_data = data_block.at(10);
    eng_data = Utilities::ConvertEnglish(line_data.at(12));
    eng_data = Utilities::ToFloat(eng_data);
    acc_details.power_factor_ = eng_data.toFloat();
        

    account_details_.push_back(acc_details);
  }
}

std::vector<AccountDetails> IndustrialData::GetDataInfo()
{
  return account_details_;
}