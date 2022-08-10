#include "doctest/doctest.h"

#include <string>
#include <filesystem>


#include "KVStore.h"
#include "Database.h"


namespace fs = std::filesystem;

TEST_CASE("Create a new empty DB") {
    std::string dbname("EmptyDB");
    Database db(KVStore::createEmptyDB(dbname));
    auto dir = db.getDirectory();
    // Check that we have a DB Folder set
    CHECK(fs::is_directory(fs::status(dir)));

    // Check empty dir
    const auto& p = fs::directory_iterator(dir);
    CHECK(p == end(p));
}
