#include "db_manager.h"

#include <QtCore\QDir>
#include <QtCore\QFile>
#include <QtCore\QVariant>

#include <QtSql\QsqlQuery>
#include <QtSql\QsqlRecord>


DbManager::DbManager()
{
  db_ = QSqlDatabase::addDatabase("QSQLITE");
}

DbManager::~DbManager()
{
  QSqlDatabase::removeDatabase("QSQLITE");
}

bool DbManager::CreateDb(const QString& db_name)
{
  bool retval = false;
  QString file_name = QDir::toNativeSeparators(db_name);
  if (!QFile::exists(file_name))
  {    
    QFile file (file_name);
    file.open(QIODevice::ReadWrite);
    file.close();
    
    if (QFile::exists(file_name))
    {
      std::cout << "Data Base does not exists. Created." << std::endl;
    } else
    {
      std::cout << "Not able to create the data base file." << std::endl;
    }
  } else
  {
    std::cout << "Data base already exist, no need to create." << std::endl;
  }
  return retval;
}

bool DbManager::OpenDb(const QString& db_name)
{
  db_.setDatabaseName(db_name);
  db_open_ = false;
  if (db_.open())
  {
    db_open_ = true;
  }
  return db_open_;
}

DbManager::DbManager(const QString& file_name)
{
  db_ = QSqlDatabase::addDatabase("QSQLITE");
  file_name_ = QDir::toNativeSeparators(file_name);
  db_.setDatabaseName(file_name);
  db_open_ = false; 
  if (db_.open())
  {
    db_open_ = true;
  }
}

bool DbManager::IsDbOpen()
{
  return db_open_;
}

bool DbManager::CloseDb()
{
  bool retval = false;

  if (db_open_)
  {
    db_.close();
    retval = true;
  }

  return retval;
}

bool DbManager::IsTableExists(const QString& name)
{
  bool retval = false;
  QSqlQuery query;
  QString query_str = "SELECT name FROM sqlite_master WHERE type =:table";
  query.prepare(query_str);
  query.bindValue(":table", "table");
  query.exec();
  int field_no = query.record().indexOf("name");
  while (query.next())
  {
    QString table_name = query.value(field_no).toString();
    if (table_name == name)
    {
      retval = true;
      break;
    }    
  }
  return retval;
}

bool DbManager::CreateMainTable(const QString& name)
{
  bool retval = false;
  if (db_open_)
  {
    QString table_str = "CREATE TABLE IF NOT EXISTS " + name + " (";
    table_str = table_str + "subscriptionnum INTEGER UNIQUE PRIMARY KEY, ";
    table_str = table_str + "type INTEGER, ";
    table_str = table_str + "accnum INTEGER, ";
    table_str = table_str + "electrometernum INTEGER, ";
    table_str = table_str + "capacity INTEGER, ";
    table_str = table_str + "name VARCHAR(128), ";
    table_str = table_str + "address VARCHAR(128) ";
    table_str = table_str + ")";   

    QSqlQuery query;
    query.prepare(table_str);
    retval = query.exec();
  }
  return retval;
}

bool DbManager::IsInMainTable(const QString& name, qulonglong number)
{
  bool retval = false;
  if (db_open_)
  {
    QString search_str = "SELECT * FROM " + name + " ";
    QString val_str = QString("WHERE subscriptionnum = %1").arg(number);
    QString query_str = search_str + val_str;
    QSqlQuery query;
    query.exec(query_str);

    if (query.next())
    {
      retval = true;
    }
  }
  return retval;
}

bool DbManager::InsertMainData(const QString& name, AccountDetails acc_details)
{
  bool retval = false;
  if (db_open_)
  {
    QSqlQuery query;
    QString insert_str = "INSERT INTO " + name + " ";
    QString val_str = QString("VALUES(%1, %2, %3, %4, %5, '%6', '%7')")
      .arg(acc_details.subscription_num_)
      .arg(acc_details.type_)
      .arg(acc_details.account_num_)
      .arg(acc_details.electrometer_num_)
      .arg(acc_details.capacity_)
      .arg(acc_details.name_)
      .arg(acc_details.address_);
    QString query_str = insert_str + val_str;
    retval = query.exec(query_str);
  }
  return retval;
}

AccountDetails DbManager::RetrieveMainData(const QString& name,
  qulonglong number)
{
  AccountDetails acc_details;
  if (db_open_)
  {
    QString search_str = "SELECT * FROM " + name + " ";
    QString val_str = QString("WHERE subscriptionnum = %1").arg(number);
    QString query_str = search_str + val_str;
    QSqlQuery query;
    query.exec(query_str);

    if (query.next())
    {
      acc_details.subscription_num_ = query.value(0).toULongLong();
      acc_details.type_ = query.value(1).toUInt();
      acc_details.account_num_ = query.value(2).toULongLong();
      acc_details.electrometer_num_ = query.value(3).toUInt();
      acc_details.capacity_ = query.value(4).toUInt();
      acc_details.name_ = query.value(5).toString();
      acc_details.address_ = query.value(6).toString();      
    }
  }

  return acc_details;
}


bool DbManager::CreateSubTable(const QString& name)
{
  bool retval = false;
  if (db_open_)
  {
    QString table_str = "CREATE TABLE IF NOT EXISTS " + name + " (";
    table_str = table_str + "invoicenumber INTEGER UNIQUE PRIMARY KEY, ";
    table_str = table_str + "invoicedate VARCHAR(10), ";
    table_str = table_str + "readingfrom VARCHAR(10), ";
    table_str = table_str + "readingto VARCHAR(10), ";
    table_str = table_str + "numdays INTEGER, ";
    table_str = table_str + "prevreading INTEGER, ";
    table_str = table_str + "cureading INTEGER, ";
    table_str = table_str + "actpowcon INTEGER, ";
    table_str = table_str + "actpowconcost REAL, ";
    table_str = table_str + "reactpowcon INTEGER, ";
    table_str = table_str + "reactpowconcost REAL, ";
    table_str = table_str + "allowedcon INTEGER, ";
    table_str = table_str + "factor REAL, ";
    table_str = table_str + "powerfactor REAL, ";
    table_str = table_str + "settlement REAL, ";
    table_str = table_str + "meterfee REAL, ";
    table_str = table_str + "concost REAL, ";
    table_str = table_str + "totalcost REAL, ";
    table_str = table_str + "blocklength INTEGER ";
    table_str = table_str + ")";

    QSqlQuery query;
    query.prepare(table_str);
    retval = query.exec();
  }
  return retval;  
}

bool DbManager::IsInSubTable(const QString& name, qulonglong number)
{
  bool retval = false;
  if (db_open_)
  {
    QString search_str = "SELECT * FROM " + name + " ";
    QString val_str = QString("WHERE invoicenumber = %1").arg(number);
    QString query_str = search_str + val_str;
    QSqlQuery query;
    query.exec(query_str);

    if (query.next())
    {
      retval = true;
    }
  }
  return retval;
}


bool DbManager::InsertSubData(const QString& name, AccountDetails acc_details)
{
  bool retval = false;
  if (db_open_)
  {
    QSqlQuery query;
    QString insert_str = "INSERT INTO " + name + " ";
    QString val_str = QString("VALUES(%1, '%2', '%3', '%4', %5, %6, %7, %8,"
        "%9, %10, %11, %12, %13, %14, %15, %16, %17, %18, %19)")
      .arg(acc_details.invoice_num_)
      .arg(acc_details.invoice_date_)
      .arg(acc_details.reading_from_)
      .arg(acc_details.reading_to_)
      .arg(acc_details.reading_days_)
      .arg(acc_details.prev_reading_)
      .arg(acc_details.curr_reading_)
      .arg(acc_details.active_pow_cons_)
      .arg(acc_details.active_pow_cons_cost_)
      .arg(acc_details.reactive_pow_cons_)
      .arg(acc_details.reactive_pow_cons_cost_)
      .arg(acc_details.allowed_cons_)
      .arg(acc_details.factor_)
      .arg(acc_details.power_factor_)
      .arg(acc_details.settlement_)
      .arg(acc_details.electrometer_fee_)
      .arg(acc_details.total_cons_cost_)
      .arg(acc_details.total_cost_)
      .arg(acc_details.block_length_);
    QString query_str = insert_str + val_str;
    retval = query.exec(query_str);
  }
  return retval;
}

std::vector<AccountDetails> DbManager::RetrieveSubData(const QString& name,
    qulonglong number, AccountDetails acc_details)
{
  std::vector<AccountDetails> sub_details;

  if (db_open_)
  {
    QString search_str = "SELECT * FROM " + name + " ";
        
    QSqlQuery query;
    query.exec(search_str);

    while (query.next())
    {
      AccountDetails sub_acc_details;
      sub_acc_details.subscription_num_ = acc_details.subscription_num_;
      sub_acc_details.type_ = acc_details.type_;
      sub_acc_details.account_num_ = acc_details.account_num_;
      sub_acc_details.electrometer_num_ = acc_details.electrometer_num_;
      sub_acc_details.capacity_ = acc_details.capacity_;
      sub_acc_details.name_  = acc_details.name_;
      sub_acc_details.address_ = acc_details.address_;
      sub_acc_details.invoice_num_ = query.value(0).toULongLong();
      sub_acc_details.invoice_date_ = query.value(1).toString();
      sub_acc_details.reading_from_ = query.value(2).toString();
      sub_acc_details.reading_to_ = query.value(3).toString();
      sub_acc_details.reading_days_ = query.value(4).toUInt();
      sub_acc_details.prev_reading_ = query.value(5).toULongLong();
      sub_acc_details.curr_reading_ = query.value(6).toULongLong();
      sub_acc_details.active_pow_cons_ = query.value(7).toULongLong();
      sub_acc_details.active_pow_cons_cost_ = query.value(8).toFloat();
      sub_acc_details.reactive_pow_cons_ = query.value(9).toULongLong();
      sub_acc_details.reactive_pow_cons_cost_ = query.value(10).toFloat();
      sub_acc_details.allowed_cons_ = query.value(11).toULongLong();
      sub_acc_details.factor_ = query.value(12).toFloat();
      sub_acc_details.power_factor_ = query.value(13).toFloat();
      sub_acc_details.settlement_ = query.value(14).toFloat();
      sub_acc_details.electrometer_fee_ = query.value(15).toFloat();
      sub_acc_details.total_cons_cost_ = query.value(16).toFloat();
      sub_acc_details.total_cost_ = query.value(17).toFloat();
      
      sub_details.push_back(sub_acc_details);
                  
    }
  }

  return sub_details;
}

bool DbManager::DeleteTable(const QString& name)
{
  bool retval = false;
  if (db_open_)
  {
    QSqlQuery query;
    retval = query.exec("DROP TABLE names");
  }
  return retval;
}


bool DbManager::OpenDb()
{
  if (!db_.open())
  {    
    std::cout << "Error: connection with database fail" << std::endl;
  } else
  {
    db_open_ = true;
    std::cout << "Database: connection ok" << std::endl;
  }

  return true;
}

bool DbManager::DeleteDb()
{
  bool retval = false;

  if (db_open_)
  {
    retval = QFile::remove(file_name_);
  }

  return retval;    
}

bool DbManager::ShowTables()
{
  bool retval = false;
  if (db_open_)
  {
    QSqlQuery query;
    retval = query.exec("select name from sqlite_master as tables"
        " where type='table'");
    QSqlRecord rec = query.record();

    int cols = rec.count();
    for (int c = 0; c < cols; c++)
      std::cout << 
          QString("Column %1: %2").arg(c).arg(rec.fieldName(c)).toStdString()
          << std::endl;

    for (int r = 0; query.next(); r++)
    {
      for (int c = 0; c < cols; c++)
      {
        //QString data = QString("Row %1, %2: %3").arg(r).arg(rec.fieldName(c)).arg(query.value(c).toString());
        std::cout << query.value(c).toString().toStdString() << std::endl;
      }
    }
  }
  return retval;
}

bool DbManager::CreateTable(const QString& name)
{  
  bool retval = false;
  if (db_open_)
  {    
    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS names "
        "(id INTEGER UNIQUE PRIMARY KEY, "
        "firstname VARCHAR(30), "
        "lastname VARCHAR(30))");
    retval = query.exec();
  }
  return retval;
}


bool DbManager::InsertData(const QString& table_name, int id, QString first_name,
    QString last_name)
{
  bool retval = false;
  if (db_open_)
  {
    QSqlQuery query;
    retval = query.exec(QString("INSERT INTO names VALUES(%1,'%2','%3')")
      .arg(id).arg(first_name).arg(last_name));
   }
   
   return retval;  
}

bool DbManager::GetData(int id)
{
  bool retval = false;
  if (db_open_)
  {
    QSqlQuery query(QString("SELECT * FROM names WHERE id = %1").arg(id));    
    if (query.next())
    {
      std::cout << query.value(0).toInt() << ", ";
      std::cout << query.value(1).toString().toStdString();
      std::cout << query.value(2).toString().toStdString() << std::endl;   
      retval = true;
    }
  }


  return retval;

}

bool DbManager::DeleteData(int id)
{
  return false;
}

#if 0
QSqlQuery query;
QString tableName = "structure";
QString sqlQuery =
QString("SELECT name FROM sqlite_master WHERE type =:table AND name = '%1' ").arg(name);
query.prepare(sqlQuery);
query.bindValue(":table", "table");
query.exec();
int fieldNo = query.record().indexOf("name");
while (query.next()) {
  QString _name = query.value(fieldNo).toString();
  qDebug() << "Table Name" << _name;
}
#endif


#if 0

#include <QApplication>

#include <QtSql>
#include <QtDebug>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

  db.setDatabaseName("./testdatabase.db");

  if (!db.open())
  {
    qDebug() << db.lastError();
    qFatal("Failed to connect.");
  }

  qDebug("Connected!");

  QSqlQuery qry;

  qry.prepare("CREATE TABLE IF NOT EXISTS names (id INTEGER UNIQUE PRIMARY KEY, firstname VARCHAR(30), lastname VARCHAR(30))");
  if (!qry.exec())
    qDebug() << qry.lastError();
  else
    qDebug() << "Table created!";

  qry.prepare("INSERT INTO names (id, firstname, lastname) VALUES (1, 'John', 'Doe')");
  if (!qry.exec())
    qDebug() << qry.lastError();
  else
    qDebug("Inserted!");

  qry.prepare("INSERT INTO names (id, firstname, lastname) VALUES (2, 'Jane', 'Doe')");
  if (!qry.exec())
    qDebug() << qry.lastError();
  else
    qDebug("Inserted!");

  qry.prepare("INSERT INTO names (id, firstname, lastname) VALUES (3, 'James', 'Doe')");
  if (!qry.exec())
    qDebug() << qry.lastError();
  else
    qDebug("Inserted!");

  qry.prepare("INSERT INTO names (id, firstname, lastname) VALUES (4, 'Judy', 'Doe')");
  if (!qry.exec())
    qDebug() << qry.lastError();
  else
    qDebug("Inserted!");

  qry.prepare("INSERT INTO names (id, firstname, lastname) VALUES (5, 'Richard', 'Roe')");
  if (!qry.exec())
    qDebug() << qry.lastError();
  else
    qDebug("Inserted!");

  qry.prepare("INSERT INTO names (id, firstname, lastname) VALUES (6, 'Jane', 'Roe')");
  if (!qry.exec())
    qDebug() << qry.lastError();
  else
    qDebug("Inserted!");

  qry.prepare("INSERT INTO names (id, firstname, lastname) VALUES (7, 'John', 'Noakes')");
  if (!qry.exec())
    qDebug() << qry.lastError();
  else
    qDebug("Inserted!");

  qry.prepare("INSERT INTO names (id, firstname, lastname) VALUES (8, 'Donna', 'Doe')");
  if (!qry.exec())
    qDebug() << qry.lastError();
  else
    qDebug("Inserted!");

  qry.prepare("INSERT INTO names (id, firstname, lastname) VALUES (9, 'Ralph', 'Roe')");
  if (!qry.exec())
    qDebug() << qry.lastError();
  else
    qDebug("Inserted!");

  qry.prepare("SELECT * FROM names");
  if (!qry.exec())
    qDebug() << qry.lastError();
  else
  {
    qDebug("Selected!");

    QSqlRecord rec = qry.record();

    int cols = rec.count();

    for (int c = 0; c<cols; c++)
      qDebug() << QString("Column %1: %2").arg(c).arg(rec.fieldName(c));

    for (int r = 0; qry.next(); r++)
      for (int c = 0; c<cols; c++)
        qDebug() << QString("Row %1, %2: %3").arg(r).arg(rec.fieldName(c)).arg(qry.value(c).toString());
  }


  qry.prepare("SELECT firstname, lastname FROM names WHERE lastname = 'Roe'");
  if (!qry.exec())
    qDebug() << qry.lastError();
  else
  {
    qDebug("Selected!");

    QSqlRecord rec = qry.record();

    int cols = rec.count();

    for (int c = 0; c<cols; c++)
      qDebug() << QString("Column %1: %2").arg(c).arg(rec.fieldName(c));

    for (int r = 0; qry.next(); r++)
      for (int c = 0; c<cols; c++)
        qDebug() << QString("Row %1, %2: %3").arg(r).arg(rec.fieldName(c)).arg(qry.value(c).toString());
  }


  qry.prepare("SELECT firstname, lastname FROM names WHERE lastname = 'Roe' ORDER BY firstname");
  if (!qry.exec())
    qDebug() << qry.lastError();
  else
  {
    qDebug("Selected!");

    QSqlRecord rec = qry.record();

    int cols = rec.count();

    for (int c = 0; c<cols; c++)
      qDebug() << QString("Column %1: %2").arg(c).arg(rec.fieldName(c));

    for (int r = 0; qry.next(); r++)
      for (int c = 0; c<cols; c++)
        qDebug() << QString("Row %1, %2: %3").arg(r).arg(rec.fieldName(c)).arg(qry.value(c).toString());
  }


  qry.prepare("SELECT lastname, COUNT(*) as 'members' FROM names GROUP BY lastname ORDER BY lastname");
  if (!qry.exec())
    qDebug() << qry.lastError();
  else
  {
    qDebug("Selected!");

    QSqlRecord rec = qry.record();

    int cols = rec.count();

    for (int c = 0; c<cols; c++)
      qDebug() << QString("Column %1: %2").arg(c).arg(rec.fieldName(c));

    for (int r = 0; qry.next(); r++)
      for (int c = 0; c<cols; c++)
        qDebug() << QString("Row %1, %2: %3").arg(r).arg(rec.fieldName(c)).arg(qry.value(c).toString());
  }

  qry.prepare("UPDATE names SET firstname = 'Nisse', lastname = 'Svensson' WHERE id = 7");
  if (!qry.exec())
    qDebug() << qry.lastError();
  else
    qDebug("Updated!");

  qry.prepare("UPDATE names SET lastname = 'Johnson' WHERE firstname = 'Jane'");
  if (!qry.exec())
    qDebug() << qry.lastError();
  else
    qDebug("Updated!");

  qry.prepare("DELETE FROM names WHERE id = 7");
  if (!qry.exec())
    qDebug() << qry.lastError();
  else
    qDebug("Deleted!");

  qry.prepare("DELETE FROM names WHERE lastname = 'Johnson'");
  if (!qry.exec())
    qDebug() << qry.lastError();
  else
    qDebug("Deleted!");


  db.close();

  return 0;
}



#endif


//http://doc.qt.io/qt-5/sql-types.html