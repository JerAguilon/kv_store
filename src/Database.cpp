#include <filesystem>

#include "Database.h"

namespace fs = std::filesystem;

Database::Database(const std::string &dbname, const std::string &fullpath_)
    : name(dbname), fullpath(fullpath_) {}

Database Database::createEmptyDB(const std::string &dbname) {
  // TODO: Make less hacky
  std::string basedir(".db");
  createIfNotExists(basedir);

  std::string dbfolder(basedir + "/" + dbname);
  createIfNotExists(dbfolder);

  return Database(dbname, dbfolder);
}

void Database::createIfNotExists(const std::string &dir) {
  if (!fs::exists(dir)) {
    fs::create_directory(dir);
  }
}

const std::string &Database::getDirectory() const { return fullpath; }
