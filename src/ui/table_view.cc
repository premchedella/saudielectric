#include "table_view.h"

#include <QtWidgets\QHeaderView>



TableView::TableView(QWidget *parent)
{
  this->setParent(parent);
  type_ = 0;
  is_all_ = false;
  data_table_ = new QTableWidget(this);
  data_table_->setVisible(false);

  sub_table_ = new QTableWidget(this);
  sub_table_->setVisible(false);

  sub_table_->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  sub_table_->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
  table_view_type_ = TABLE_VIEW_NONE;
}

TableView::~TableView()
{

}

void TableView::SetType(unsigned int type, bool is_all)
{  
  type_ = type;
  is_all_ = is_all;

  std::vector<AccountDetails> data;
  QStringList header;

  if (is_all_)  //All the type blocks
  {
    data = ParseData::GetDataInfo();
    data_table_->setColumnCount(2);
    header << "Type";
    header << "Subscription Number";
    data_table_->setColumnWidth(0, 60);
    data_table_->setColumnWidth(1, 180);
  } else
  {
    data_table_->setColumnCount(1);
    header << "Subscription Number";
    data = ParseData::GetDataInfo(type_);
    data_table_->setColumnWidth(0, 180);
  }

  data_table_->setHorizontalHeaderLabels(header);
  data_table_->setRowCount(data.size());
    
  for (unsigned int counter = 0; counter < data.size(); counter++)
  {
    AccountDetails acc_details = data.at(counter);
    if (is_all_)  //All the type blocks
    {
      QTableWidgetItem* item = new QTableWidgetItem();
      item->setText(QString::number(acc_details.type_));
      data_table_->setItem(counter, 0, item);
    }

    QTableWidgetItem* item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.subscription_num_));
    if (is_all_)
    {
      data_table_->setItem(counter, 1, item);
    } else
    {
      data_table_->setItem(counter, 0, item);
    }
  }

  data_table_->setVisible(true);
  data_table_->update();
  table_view_type_ = TABLE_VIEW_MAIN;
  this->update();
}

void TableView::UpdateSubGroup(std::vector<AccountDetails> data)
{
  QStringList header;
   
  header << "Subscription\nNumber";
  header << "Type";
  header << "Account\n Number"; 
  header << "Electrometer\nNumber";
  header << "Capacity";
  header << "Name";
  header << "Address";
  
  data_table_->setRowCount(1);
  data_table_->setColumnCount(7);
  data_table_->setHorizontalHeaderLabels(header);

  data_table_->setColumnWidth(0, 180);
  data_table_->setColumnWidth(1, 50);
  data_table_->setColumnWidth(2, 180);
  data_table_->setColumnWidth(3, 180);
  data_table_->setColumnWidth(4, 80);
  data_table_->setColumnWidth(5, 150);
  data_table_->setColumnWidth(6, 150);


  AccountDetails acc_details = data.at(0);

  QTableWidgetItem* item = new QTableWidgetItem();
  item->setText(QString::number(acc_details.subscription_num_));
  data_table_->setItem(0, 0, item);

  item = new QTableWidgetItem();
  item->setText(QString::number(acc_details.type_));
  data_table_->setItem(0, 1, item);

  item = new QTableWidgetItem();
  item->setText(QString::number(acc_details.account_num_));
  data_table_->setItem(0, 2, item);

  item = new QTableWidgetItem();
  item->setText(QString::number(acc_details.electrometer_num_));
  data_table_->setItem(0, 3, item);

  item = new QTableWidgetItem();
  item->setText(QString::number(acc_details.capacity_));
  data_table_->setItem(0, 4, item);

  item = new QTableWidgetItem();
  item->setText(acc_details.name_);
  data_table_->setItem(0, 5, item);

  item = new QTableWidgetItem();  
  item->setText(acc_details.address_);
  data_table_->setItem(0, 6, item);

  data_table_->setVisible(true);
  data_table_->update();

  header.clear();
  header << "Innovice\nNumber";
  header << "Innovice\nDate";  
  header << "Reading\nFrom";
  header << "Reading\nTo";
  header << "Reading\nDays";
  header << "Previous\nReading";
  header << "Current\nReading";
  header << "Active Power\nConsumption";
  header << "Active Power\nConsumption Cost";
  header << "Reactive Power\nConsumption";
  header << "ReActive Power\nConsumption Cost";
  header << "Allowed\nConsumption";
  header << "Factor";
  header << "Power\nFactor";
  header << "Settlement";
  header << "Meter Fee";
  header << "Total Consumption\nCost";
  header << "Total Cost";

  sub_table_->setRowCount(data.size());
  sub_table_->setColumnCount(18);
  sub_table_->setHorizontalHeaderLabels(header);

  sub_table_->setColumnWidth(0, 150);
  sub_table_->setColumnWidth(1, 120);
  sub_table_->setColumnWidth(2, 120);
  sub_table_->setColumnWidth(3, 120);
  sub_table_->setColumnWidth(4, 80);
  sub_table_->setColumnWidth(5, 120);
  sub_table_->setColumnWidth(6, 120);
  sub_table_->setColumnWidth(7, 120);
  sub_table_->setColumnWidth(8, 150);
  sub_table_->setColumnWidth(9, 120);
  sub_table_->setColumnWidth(10, 150);
  sub_table_->setColumnWidth(11, 110);
  sub_table_->setColumnWidth(12, 90);
  sub_table_->setColumnWidth(13, 80);
  sub_table_->setColumnWidth(14, 100);
  sub_table_->setColumnWidth(15, 100);
  sub_table_->setColumnWidth(16, 130);
  sub_table_->setColumnWidth(17, 100);
    
  for (unsigned int counter = 0; counter < data.size(); counter++)
  {
    AccountDetails acc_details = data.at(counter);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.invoice_num_));
    sub_table_->setItem(counter, 0, item);

    item = new QTableWidgetItem();
    item->setText(acc_details.invoice_date_);
    sub_table_->setItem(counter, 1, item);

    item = new QTableWidgetItem();
    item->setText(acc_details.reading_from_);
    sub_table_->setItem(counter, 2, item);

    item = new QTableWidgetItem();
    item->setText(acc_details.reading_to_);
    sub_table_->setItem(counter, 3, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.reading_days_));
    sub_table_->setItem(counter, 4, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.prev_reading_));
    sub_table_->setItem(counter, 5, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.curr_reading_));
    sub_table_->setItem(counter, 6, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.active_pow_cons_));
    sub_table_->setItem(counter, 7, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.active_pow_cons_cost_, 'f', 2));
    sub_table_->setItem(counter, 8, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.reactive_pow_cons_));
    sub_table_->setItem(counter, 9, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.reactive_pow_cons_cost_, 'f', 2));
    sub_table_->setItem(counter, 10, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.allowed_cons_));
    sub_table_->setItem(counter, 11, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.factor_, 'f', 2));
    sub_table_->setItem(counter, 12, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.power_factor_, 'f', 2));
    sub_table_->setItem(counter, 13, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.settlement_, 'f', 2));
    sub_table_->setItem(counter, 14, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.electrometer_fee_, 'f', 2));
    sub_table_->setItem(counter, 15, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.total_cons_cost_, 'f', 2));
    sub_table_->setItem(counter, 16, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.total_cost_, 'f', 2));
    sub_table_->setItem(counter, 17, item);
  }

  sub_table_->setVisible(true);
  sub_table_->update();
  
  table_view_type_ = TABLE_VIEW_SUB;
  this->update();
}

void TableView::paintEvent(QPaintEvent *event)
{
  if (table_view_type_ == TABLE_VIEW_MAIN)
  {
    data_table_->setGeometry(0, 0, this->width(), this->height());
    data_table_->update();
  } else if (table_view_type_ == TABLE_VIEW_SUB)
  {
    data_table_->setGeometry(0, 0, this->width(), 90);
    data_table_->update();
    QRect widget_geometry = sub_table_->geometry();
    widget_geometry.setWidth(this->width());
    widget_geometry.setY(100);
    widget_geometry.setHeight(this->height() - 100);
    sub_table_->setGeometry(widget_geometry);
    sub_table_->update();
  }
}