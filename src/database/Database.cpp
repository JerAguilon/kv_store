#include <filesystem>
#include <fstream>

#include "database/Database.h"

namespace fs = std::filesystem;

struct Database::Private {
  // TODO: should this be overridable?
  static constexpr const char* getRootFolder() {
      return ".db/";
  }

  static std::string getDir(const std::string &dbname) {
      return getRootFolder() + dbname;
  }

  static void createIfNotExists(const std::string &dir) {
    if (!fs::exists(dir)) {
      fs::create_directory(dir);
    }
  }

  static void deleteIfExists(const std::string &dir) {
    if (fs::exists(dir)) {
      fs::remove_all(dir);
    }
  }

  static std::string getKeyFile(const Database &self, const std::string &key) {
    return self.fullpath + "/" + key + "_string.kv";
  }
};

Database::Database(const std::string &dbname, const std::string &fullpath_)
    : name(dbname), fullpath(fullpath_) {}

Database Database::createEmptyDB(const std::string &dbname) {
  Private::createIfNotExists(Private::getRootFolder());
  std::string dbfolder = Private::getDir(dbname);
  Private::createIfNotExists(dbfolder);
  return Database(dbname, dbfolder);
}

Database Database::loadDB(const std::string &dbname) {
  std::string dbfolder = Private::getDir(dbname);
  return Database(dbname, dbfolder);
}

void Database::setKeyValue(const std::string &key, const std::string &val) {
  std::ofstream os;
  os.open(Private::getKeyFile(*this, key), std::ios::out | std::ios::trunc);
  os << val;
  os.close();
}

std::string Database::getKeyValue(const std::string &key) const {
  std::ifstream t;
  t.open(Private::getKeyFile(*this, key));
  std::string value;

  t.seekg(0, std::ios::end);
  value.reserve(t.tellg());
  t.seekg(0, std::ios::beg);
  value.assign((std::istreambuf_iterator<char>(t)),
               (std::istreambuf_iterator<char>()));
  t.close();
  return value;
}

const std::string &Database::getDirectory() const { return fullpath; }

void Database::destroy() { Private::deleteIfExists(fullpath); }
