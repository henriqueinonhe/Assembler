//#include "catch.hpp"
//#include "command.h"
//#include "parser.h"
//#include <string>

//TEST_CASE("Command")
//{
//    CHECK_NOTHROW(Command());
//    CHECK_NOTHROW(Command("// This file is part of www.nand2tetris.org"));

//    //A-Command
//    //Validation
//    CHECK_NOTHROW(Command("@fe3434asd$.__"));
//    CHECK_NOTHROW(Command("@juggers"));
//    CHECK_NOTHROW(Command("@$sda_.Dsa434dhasdg$.__"));
//    CHECK_NOTHROW(Command("@876"));
//    CHECK_NOTHROW(Command("@0"));
//    CHECK_NOTHROW(Command("@2"));
//    CHECK_NOTHROW(Command("@100"));
//    CHECK_NOTHROW(Command("@3"));

//    CHECK_THROWS(Command("@8abdhhbasd")); //Symbols cannot begin with a number
//    CHECK_THROWS(Command("@7863984yjknajskd")); //Symbols cannot begin with a number
//    CHECK_THROWS(Command("@-786")); //Values cannot be negative

//    //Extracting
//    CHECK(Command("@fe43847_$Sd..:__").symbol() == "fe43847_$Sd..:__");
//    CHECK(Command("@200").symbol() == "200");

//    CHECK_THROWS(Command("@200").comp());
//    CHECK_THROWS(Command("@200").dest());
//    CHECK_THROWS(Command("@200").jump());

//    //C-Command
//    //Validation
//    CHECK_NOTHROW(Command("D =   A"));
//    CHECK_NOTHROW(Command("D=   M"));
//    CHECK_NOTHROW(Command("  D= 0"));
//    CHECK_NOTHROW(Command("D=1   "));
//    CHECK_NOTHROW(Command("D=M+ 1; JNE"));
//    CHECK_NOTHROW(Command("D=D   +1"));
//    CHECK_NOTHROW(Command("D=A +1"));
//    CHECK_NOTHROW(Command("D = !A"));
//    CHECK_NOTHROW(Command("D=!D"));
//    CHECK_NOTHROW(Command("D = -A  ; JLE"));
//    CHECK_NOTHROW(Command("D  =-D;JMP"));
//    CHECK_NOTHROW(Command("A =D"));
//    CHECK_NOTHROW(Command("A =-A;J   G E"));
//    CHECK_NOTHROW(Command("A M D=A // Freggersons"));
//    CHECK_NOTHROW(Command("M = M"));
//    CHECK_NOTHROW(Command("A  = D"));
//    CHECK_NOTHROW(Command("MD = D+A//      DuBAABDASD 8743yiaDSb8as*D  u8 8SDHA D//"));
//    CHECK_NOTHROW(Command("0;JMP"));

//    CHECK_THROWS(Command("A D M=A //Freggersons"));
//    CHECK_THROWS(Command("  =D"));
//    CHECK_THROWS(Command(";"));
//    CHECK_THROWS(Command("D;JUH"));
//    CHECK_THROWS(Command("A=;JMP"));

//    //Extracting
//    CHECK(Command("MD = D+A//DuBAABDASD 8743yiaDSb8as*D  u8 8SDHA D//").dest() == "MD");
//    CHECK(Command("MD = D+A//DuBAABDASD 8743yiaDSb8as*D  u8 8SDHA D//").comp() == "D+A");
//    CHECK(Command("D = -A  ; JLE").jump() == "JLE");
//}
