#include "logging.hpp"

#include "gtest/gtest.h"

/**
 * @brief Tests <code>log()</code> to console
 */
TEST(loggingTest, log_console) {
    std::ostream nullStream(nullptr);
    setLogLevel(VERBOSE);
    EXPECT_EQ(std::cout.rdbuf(), log(VERBOSE).rdbuf());
    EXPECT_EQ(std::cout.rdbuf(), log(INFO).rdbuf());
    EXPECT_EQ(std::cout.rdbuf(), log(WARNING).rdbuf());
    EXPECT_EQ(std::cerr.rdbuf(), log(ERROR).rdbuf());
    setLogLevel(INFO);
    EXPECT_EQ(nullStream.rdbuf(), log(VERBOSE).rdbuf());
    EXPECT_EQ(std::cout.rdbuf(), log(INFO).rdbuf());
    EXPECT_EQ(std::cout.rdbuf(), log(WARNING).rdbuf());
    EXPECT_EQ(std::cerr.rdbuf(), log(ERROR).rdbuf());
    setLogLevel(WARNING);
    EXPECT_EQ(nullStream.rdbuf(), log(VERBOSE).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), log(INFO).rdbuf());
    EXPECT_EQ(std::cout.rdbuf(), log(WARNING).rdbuf());
    EXPECT_EQ(std::cerr.rdbuf(), log(ERROR).rdbuf());
    setLogLevel(ERROR);
    EXPECT_EQ(nullStream.rdbuf(), log(VERBOSE).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), log(INFO).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), log(WARNING).rdbuf());
    EXPECT_EQ(std::cerr.rdbuf(), log(ERROR).rdbuf());
    setLogLevel(NONE);
    EXPECT_EQ(nullStream.rdbuf(), log(VERBOSE).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), log(INFO).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), log(WARNING).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), log(ERROR).rdbuf());
}

/**
 * @brief Tests <code>logIf()</code> to console
 */
TEST(loggingTest, logIf_console) {
    std::ostream nullStream(nullptr);
    setLogLevel(VERBOSE);
    EXPECT_EQ(std::cout.rdbuf(), logIf(VERBOSE, true).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(VERBOSE, false).rdbuf());
    EXPECT_EQ(std::cout.rdbuf(), logIf(INFO, true).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(INFO, false).rdbuf());
    EXPECT_EQ(std::cout.rdbuf(), logIf(WARNING, true).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(WARNING, false).rdbuf());
    EXPECT_EQ(std::cerr.rdbuf(), logIf(ERROR, true).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(ERROR, false).rdbuf());
    setLogLevel(INFO);
    EXPECT_EQ(nullStream.rdbuf(), logIf(VERBOSE, true).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(VERBOSE, false).rdbuf());
    EXPECT_EQ(std::cout.rdbuf(), logIf(INFO, true).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(INFO, false).rdbuf());
    EXPECT_EQ(std::cout.rdbuf(), logIf(WARNING, true).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(WARNING, false).rdbuf());
    EXPECT_EQ(std::cerr.rdbuf(), logIf(ERROR, true).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(ERROR, false).rdbuf());
    setLogLevel(WARNING);
    EXPECT_EQ(nullStream.rdbuf(), logIf(VERBOSE, true).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(VERBOSE, false).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(INFO, true).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(INFO, false).rdbuf());
    EXPECT_EQ(std::cout.rdbuf(), logIf(WARNING, true).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(WARNING, false).rdbuf());
    EXPECT_EQ(std::cerr.rdbuf(), logIf(ERROR, true).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(ERROR, false).rdbuf());
    setLogLevel(ERROR);
    EXPECT_EQ(nullStream.rdbuf(), logIf(VERBOSE, true).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(VERBOSE, false).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(INFO, true).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(INFO, false).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(WARNING, true).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(WARNING, false).rdbuf());
    EXPECT_EQ(std::cerr.rdbuf(), logIf(ERROR, true).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(ERROR, false).rdbuf());
    setLogLevel(NONE);
    EXPECT_EQ(nullStream.rdbuf(), logIf(VERBOSE, true).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(VERBOSE, false).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(INFO, true).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(INFO, false).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(WARNING, true).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(WARNING, false).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(ERROR, true).rdbuf());
    EXPECT_EQ(nullStream.rdbuf(), logIf(ERROR, false).rdbuf());
}

