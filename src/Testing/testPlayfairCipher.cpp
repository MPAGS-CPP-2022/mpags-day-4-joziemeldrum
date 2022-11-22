//! Unit Tests for MPAGSCipher PlayfairCipher Class
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "CipherMode.hpp"
#include "PlayfairCipher.hpp"


TEST_CASE("Playfair Cipher Encryption", "[playfair]")
{
    PlayfairCipher pc("");
    // for blank key, check encryption works
    // same column -> move down in column 
    REQUIRE(pc.applyCipher("AF", CipherMode::Encrypt) == "FL");
    // same column at bottom -> wraps to top
    REQUIRE(pc.applyCipher("AV", CipherMode::Encrypt) == "FA");
    // same row -> move along in row
    REQUIRE(pc.applyCipher("AB", CipherMode::Encrypt) == "BC");
    // same row at end -> wraps to left
    REQUIRE(pc.applyCipher("AE", CipherMode::Encrypt) == "BA");
    // in box -> swap columns
    REQUIRE(pc.applyCipher("AG", CipherMode::Encrypt) == "BF");

    // J -> I for encrption
    REQUIRE(pc.applyCipher("AJ", CipherMode::Encrypt) == "DF");
    // double letters have X inserted
    REQUIRE(pc.applyCipher("AAB", CipherMode::Encrypt) == "CUBC");
    // odd letter at end has Z added
    REQUIRE(pc.applyCipher("ABC", CipherMode::Encrypt) == "BCEX");

}

TEST_CASE("Playfair Cipher Decryption", "[playfair]")
{
    PlayfairCipher pc("");
    // for blank key, check encryption works
    // same column -> move up in column 
    REQUIRE(pc.applyCipher("FL", CipherMode::Decrypt) == "AF");
    // same column at top -> wraps to bottom
    REQUIRE(pc.applyCipher("AF", CipherMode::Decrypt) == "VA");
    // same row -> move along in row
    REQUIRE(pc.applyCipher("BD", CipherMode::Decrypt) == "AB");
    // same row at end -> wraps to right
    REQUIRE(pc.applyCipher("AB", CipherMode::Decrypt) == "EB");
    // in box -> swap columns
    REQUIRE(pc.applyCipher("AG", CipherMode::Decrypt) == "BF");

    // J skipped
    REQUIRE(pc.applyCipher("AJB", CipherMode::Decrypt) == "EJB");
    // odd letter at end has Z added
    REQUIRE(pc.applyCipher("ABC", CipherMode::Decrypt) == "EBEX");

}

TEST_CASE("key input", "[playfair]")
{
    PlayfairCipher pc("hello.j");
    // double letters removed, j-> i and . ignored
    REQUIRE(pc.applyCipher("HM", CipherMode::Encrypt) == "LG");
} 
