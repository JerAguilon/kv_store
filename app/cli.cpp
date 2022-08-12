// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#endif

#include <iostream>
#include <stdlib.h>

#include "cxxopts.hpp"

#include "database/Database.h"
#include "database/KVStore.h"
#include "exampleConfig.h"

using namespace std;
using Parsed = cxxopts::ParseResult;

cxxopts::Options options("DB-cli", "CLI for DB");

void printUsage() { 
    // TODO: make descriptive
    cout << "Whoops bad config!"; 
}

int handleCreation(Parsed result) {
    if(result.count("n") == 0) {
        cout << "You must specify a database name with -n <name>" << endl;
        printUsage();
        return 1;
    }
    std::string dbname = result["n"].as<std::string>();
    Database db(KVStore::createEmptyDB(dbname));
    cout << "Database created with name " << dbname << "and directory "
         << db.getDirectory() << endl;
    return 0;
}


int handleDestroy(Parsed result) {
    if(result.count("n") == 0) {
        cout << "You must specify a database name with -n <name>" << endl;
        printUsage();
        return 1;
    }
    std::string dbname = result["n"].as<std::string>();
    Database db(KVStore::loadDB(dbname));
    db.destroy();
    cout << "Database destroyed with name " << dbname << "and directory "
         << db.getDirectory() << endl;
    return 0;
}

int handleSet(Parsed result) {
    if(result.count("n") == 0) {
        cout << "You must specify a database name with -n <name>" << endl;
        printUsage();
        return 1;
    }
    if(result.count("k") == 0) {
        cout << "You must specify a key with -k <key>" << endl;
        printUsage();
        return 1;
    }
    if(result.count("v") == 0) {
        cout << "You must specify a value with -v <value>" << endl;
        printUsage();
        return 1;
    }
    std::string dbname = result["n"].as<std::string>();
    std::string key = result["k"].as<std::string>();
    std::string value = result["v"].as<std::string>();
    Database db(KVStore::loadDB(dbname));
    db.setKeyValue(key, value);
    cout << "K/V set in " << db.getDirectory() << endl;
    return 0;
}

int handleGet(Parsed result) {
    if(result.count("n") == 0) {
        cout << "You must specify a database name with -n <name>" << endl;
        printUsage();
        return 1;
    }
    if(result.count("k") == 0) {
        cout << "You must specify a key with -k <key>" << endl;
        printUsage();
        return 1;
    }
    std::string dbname = result["n"].as<std::string>();
    std::string key = result["k"].as<std::string>();

    Database db(KVStore::loadDB(dbname));
    std::string value = db.getKeyValue(key);

    cout << "Value: " << value << endl;
    return 0;
}
/*
 * Simple main program that demontrates how access
 * CMake definitions (here the version number) from source code.
 */
int main(int argc, char* argv[]) {
  // clang-format off
  options.add_options()
      ("c,create", "Create a DB")
      ("d,destroy", "Destroy a DB")
      ("s,set", "Set a key in a DB")
      ("g,get", "Get a key from a DB")
      ("n,name", "Database name (required)", cxxopts::value<std::string>())
      ("k,key", "Key to set/get", cxxopts::value<std::string>())
      ("v,value", "Value to set", cxxopts::value<std::string>());
  // clang-format on
  auto result = options.parse(argc, argv);

  cout << "Jeremy's KV Store" << PROJECT_VERSION_MAJOR << "."
       << PROJECT_VERSION_MINOR << "." << PROJECT_VERSION_PATCH << "."
       << PROJECT_VERSION_TWEAK << endl;
  if (result.count("c") == 1) {
      return handleCreation(result);
  }
  if (result.count("d") == 1) {
      return handleDestroy(result);
  }
  if (result.count("s") == 1) {
      return handleSet(result);
  }
  if (result.count("g") == 1) {
      return handleGet(result);
  }

  cout << "Invalid options." << endl;
  return 1;
}
