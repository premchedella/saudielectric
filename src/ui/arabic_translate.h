#ifndef MVESFM_H
#define MVESFM_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTableWidget>
#include <QtWidgets\QScrollArea>
#include <QtWidgets\QMessageBox>

#include "ui_arabictranslate.h"
#include "../common_types.h"

class ArabicTranslate : public QMainWindow
{
  Q_OBJECT

 public:
   ArabicTranslate(QWidget *parent = 0);
   ~ArabicTranslate();

 public slots:
  void FileOpen(); 
  void FileSaveCsv();
  void FileExit();

 protected:
  void paintEvent(QPaintEvent *event);
  void resizeEvent(QResizeEvent* event);  

 private:
  void Init();
  void InitUi();
  void ConnectSignals();
  void Resize();
    
  void InitDataTable();
  void UpdateDataTable();
  
  Ui::ArabicTranslateClass ui_; 
  QTableWidget* data_table_; 
  QMessageBox*  message_box_;  

  //Menu elements
  bool is_file_save_;     
};
#endif // MVESFM_H
