#include "stdafx.h"
#include "CppUnitTest.h"

#include "basic.h"

#include "CommandTokenizer.h"
#include "TokenizerLibrary.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DoLahTest {
    TEST_CLASS(Tokenize) {
public:
    TEST_METHOD(findCommandTest) {
        CommandTokenizer ct;
        std::string input = "add #cs2103 #homework on 30th Sep";
        std::string expected = (std::string) "{ add }";

        std::vector<std::string> obj = ct.findCommand(TokenizerLibrary::explode(input, " "));
        Assert::AreEqual(expected, TokenizerLibrary::vectorToString(obj));
    }

    TEST_METHOD(findTagsTest) {
        CommandTokenizer ct;
        std::string input = "add #cs2103 #homework on 30th Sep";
        std::string expected = (std::string) "{ homework, cs2103 }";

        std::vector<std::string> obj = ct.findTags(TokenizerLibrary::explode(input, " "));
        Assert::AreEqual(expected, TokenizerLibrary::vectorToString(obj));
    }

    TEST_METHOD(findDescriptionTest) {
        CommandTokenizer ct;
        std::string input = "add #cs2103 #homework on 30th Sep";
        std::string expected = (std::string) "{ #cs2103 #homework on 30th Sep }";

        std::vector<std::string> obj = ct.findDescription(TokenizerLibrary::explode(input, " "));
        Assert::AreEqual(expected, TokenizerLibrary::vectorToString(obj));
    }

    //TEST_METHOD(findDateTest) {
    //    CommandTokenizer ct;
    //    std::string input = "add #cs2103 #homework on 17th of March";
    //    std::string expected = (std::string) "{ 17-03-2016 }";
    //    

    //    DateTimeToken* obj = ct.findDate(TokenizerLibrary::explode(input, " "));
    //    Assert::AreEqual(expected, TokenizerLibrary::vectorToString(obj->getData()));
    //}

    };
}

