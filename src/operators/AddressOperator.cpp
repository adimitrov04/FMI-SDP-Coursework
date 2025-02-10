#include "../../include/operators/AddressOperators.h"
#include "../../include/ExpressionInterpreter.h"

Spreadsheet *AddressOperator::connectedSheet = nullptr;
int AddressOperator::currentRow = 0;
int AddressOperator::currentCol = 0;