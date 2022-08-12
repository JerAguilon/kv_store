#pragma once

#include <string>

class Database {
public:
  Database(const std::string &dbname, const std::string &fullpath);


  void setKeyValue(const std::string&, const std::string&);
  std::string getKeyValue(const std::string&) const;

  const std::string &getDirectory() const;

  static Database createEmptyDB(const std::string &dbName);
  static Database loadDB(const std::string &dbName);
  void destroy();


private:
  struct Private; // some helper methods

  const std::string name;
  const std::string fullpath;
};
