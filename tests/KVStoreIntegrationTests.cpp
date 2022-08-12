#include "doctest/doctest.h"

#include <filesystem>
#include <string>

#include "database/Database.h"
#include "database/KVStore.h"

namespace fs = std::filesystem;

TEST_CASE("Create a new empty DB") {
  std::string dbname("EmptyDB");
  Database db(KVStore::createEmptyDB(dbname));
  auto dir = db.getDirectory();

  SUBCASE("New DB") {
    // Check that we have a DB Folder set
    CHECK(fs::is_directory(fs::status(dir)));

    // Check empty dir
    const auto &p = fs::directory_iterator(dir);
    CHECK(p == end(p));
    db.destroy();
    CHECK(!fs::exists(fs::status(db.getDirectory())));
  }

  SUBCASE("Load an existing database") {
    Database db2(KVStore::loadDB(dbname));
    auto dir2 = db2.getDirectory();
    // Check that both dirs are the same
    CHECK(dir == dir2);

    // Check that we have a DB Folder set
    CHECK(fs::is_directory(fs::status(dir2)));

    // Check empty dir
    const auto &p = fs::directory_iterator(dir2);
    CHECK(p == end(p));

    db.destroy();
    CHECK(!fs::exists(fs::status(dir2)));
  }

  SUBCASE("Simple insert") {
    auto key = "key";
    auto val = std::string("a value");
    db.setKeyValue(key, val);
    auto outVal = db.getKeyValue(key);
    CHECK(val == outVal);
    db.destroy();
    CHECK(!fs::exists(fs::status(db.getDirectory())));
  }
}
