#pragma once


#include "Database.h"

#include <unordered_map>
#include <string>

class KVStore {
    public:
        KVStore() = default;
        void put(int, int);
        int get(int);

        static Database createEmptyDB(const std::string& dbname);

    private:
        std::unordered_map<int, int> map;
};

#ifdef ENABLE_DOCTEST_IN_LIBRARY
#include "doctest/doctest.h"
TEST_CASE("we can have tests written here, to test impl. details")
{
    CHECK(true);
}
#endif
