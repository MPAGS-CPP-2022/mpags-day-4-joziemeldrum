//! Unit Tests for MPAGSCipher PlayfairCipher Class
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "PlayfairCipher.hpp"

TEST_CASE("Key working", "[playfair]")
{
    PlayfairCipher pc{"hello.world"};
    REQUIRE(pc.getKey() != "HELLOWORLDABCDEFGHIJKLMNOPQRSTUVQXYZ");
}