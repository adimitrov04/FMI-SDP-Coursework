cmake_minimum_required(VERSION 3.28)
project(Coursework_SDP_24_25)

set(CMAKE_CXX_STANDARD 17)

add_executable(Coursework_SDP_24_25 main.cpp
        src/Spreadsheet.cpp
        src/CSVFileFunctions.cpp
        src/SpreadsheetIterator.cpp
        include/operators/Operator.h
        include/operators/OperatorSelector.hpp
        include/operators/Brackets.hpp
        include/operators/ArithmeticOperators.hpp
        include/utils/linked_stack.hpp
        include/ExpressionInterpreter.h
        include/operators/AddressOperators.h
        src/operators/AddressOperator.cpp
        src/ExpressionInterpreter.cpp
        include/commands/Command.h
        include/commands/CommandFactory.hpp
        include/commands/PrintCommand.h
        src/commands/Command.cpp
        src/commands/PrintCommand.cpp
        src/commands/SetCommand.cpp
        include/commands/SetCommand.h
        src/commands/LoadCommand.cpp
        include/commands/LoadCommand.h
        src/commands/SaveCommand.cpp
        include/commands/SaveCommand.h
        src/commands/NewCommand.cpp
        include/commands/NewCommand.h
)
