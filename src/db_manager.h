#ifndef DB_MANAGER_H_
#define DB_MANAGER_H_

#include <iostream>
#include <vector>

#include <QtCore\QString>
#include <QtSql\QSqlDatabase>

#include "account_details.h"

class DbManager
{
 public:
   DbManager();
   ~DbManager();
   bool CreateDb(const QString& db_name);
   bool OpenDb(const QString& db_name);
   bool IsDbOpen();
   bool CloseDb();
   bool IsTableExists(const QString& name);\

   bool CreateMainTable(const QString& name);
   bool IsInMainTable(const QString& name, qulonglong number);
   bool InsertMainData(const QString& name, AccountDetails acc_details);
   AccountDetails RetrieveMainData(const QString& name, qulonglong number);

   bool CreateSubTable(const QString& name);
   bool IsInSubTable(const QString& name, qulonglong number);   
   bool InsertSubData(const QString& name, AccountDetails acc_details);
   std::vector<AccountDetails> RetrieveSubData(const QString& name,
      qulonglong number, AccountDetails acc_details);


   bool DeleteTable(const QString& name);


   DbManager(const QString& db_name);
   bool OpenDb(); 
   bool DeleteDb();
   bool ShowTables();
   bool CreateTable(const QString& name);
   
   bool InsertData(const QString& table_name, int id, QString first_name,
      QString last_name);
   bool GetData(int id);
   bool DeleteData(int id);

 private:
   QSqlDatabase db_;
   QString file_name_;
   bool db_open_;
};

#endif  //DB_MANAGER_H_