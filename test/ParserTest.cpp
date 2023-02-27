#include "RequestParser.h"

#include "gtest/gtest.h"

#include <vector>

void testParser(const std::vector<std::string>& toParse, const std::vector<Homework::Request>& expectedCommands) {
    using namespace Homework;

    std::vector<Request> receivedCommands;

    RequestParser parser;
    parser.onRequestReceived = [&receivedCommands](const Request& command) {
        receivedCommands.push_back(command);
    };

    for (auto& line : toParse) {
        parser.parse(line);
    }
    ASSERT_EQ(expectedCommands.size(), receivedCommands.size());
    for (std::size_t i = 0; i < expectedCommands.size(); ++i) {
        ASSERT_EQ(expectedCommands[i].commandName, receivedCommands[i].commandName);
        ASSERT_EQ(expectedCommands[i].arguments.size(), receivedCommands[i].arguments.size());
        for (std::size_t j = 0; j < expectedCommands[i].arguments.size(); ++j) {
            ASSERT_EQ(expectedCommands[i].arguments[j], receivedCommands[i].arguments[j]);
        }
    }
}

void testParser(const std::string& toParse, const std::vector<Homework::Request>& expectedCommands) {
    std::vector<std::string> lines = { toParse };
    testParser(lines, expectedCommands);
}

TEST(parserTest, singleCommandWithArguments) {
    using namespace Homework;

    Request command;
    command.commandName = "INSERT";
    command.arguments = { "foo", "5", "bar" };

    std::vector<Request> expectedCommands = { command };
    testParser("INSERT foo 5 bar\n", expectedCommands);
}

TEST(parserTest, singleCommandWithoutArguments) {
    using namespace Homework;

    Request command;
    command.commandName = "INTERSECTION";

    std::vector<Request> expectedCommands = { command };
    testParser("INTERSECTION\n", expectedCommands);
}

TEST(parserTest, commandSequence) {
    using namespace Homework;

    Request cmd1;
    cmd1.commandName = "INSERT";
    cmd1.arguments = { "foo", "1", "bar" };
    Request cmd2;
    cmd2.commandName = "INSERT";
    cmd2.arguments = { "a", "2", "1" };
    Request cmd3;
    cmd3.commandName = "TRUNCATE";
    cmd3.arguments = { "b" };

    std::vector<Request> expectedCommands = { cmd1, cmd2, cmd3 };
    testParser("INSERT foo 1 bar\nINSERT a 2 1\nTRUNCATE b\n", expectedCommands);
}

TEST(parserTest, commandSequenceParts) {
    using namespace Homework;

    std::vector<std::string> toParse = { "INS", "ERT foo ", "1 bar\n", "INSERT a 2 1", "\nTRUNCATE b", "\n" };

    Request cmd1;
    cmd1.commandName = "INSERT";
    cmd1.arguments = { "foo", "1", "bar" };
    Request cmd2;
    cmd2.commandName = "INSERT";
    cmd2.arguments = { "a", "2", "1" };
    Request cmd3;
    cmd3.commandName = "TRUNCATE";
    cmd3.arguments = { "b" };

    std::vector<Request> expectedCommands = { cmd1, cmd2, cmd3 };
    testParser("INSERT foo 1 bar\nINSERT a 2 1\nTRUNCATE b\n", expectedCommands);
}
