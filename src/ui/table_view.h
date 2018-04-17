#ifndef TABLE_VIEW_H_
#define TABLE_VIEW_H_

#include <iostream>

#include <QtWidgets\QTableWidget>

#include "../parse_data.h"

class TableView : public QWidget
{
  Q_OBJECT

 public:
  TableView(QWidget *parent = 0);
  ~TableView();

  void SetType(unsigned int type, bool is_all = false);
  void UpdateSubGroup(std::vector<AccountDetails> data);

 protected:
  void paintEvent(QPaintEvent *event);

 private:
  enum ViewTypes {
    TABLE_VIEW_NONE = 0,
    TABLE_VIEW_MAIN = 1,
    TABLE_VIEW_SUB = 2
  };

  unsigned int type_;
  bool is_all_;
  QTableWidget* data_table_;
  QTableWidget* sub_table_;
  ViewTypes table_view_type_;
};
#endif //TABLE_VIEW_H_
