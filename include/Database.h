#pragma once

#include <string>

class Database {
public:
  Database(const std::string &dbname, const std::string &fullpath);

  const std::string &getDirectory() const;

  static Database createEmptyDB(const std::string &dbName);

private:
  const std::string &name;
  const std::string &fullpath;

  static void createIfNotExists(const std::string &dir);
};
