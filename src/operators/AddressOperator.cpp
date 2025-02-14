#include "../../include/operators/AddressOperators.h"
#include "../../include/utils/ExpressionInterpreter.h"

Spreadsheet *AddressOperator::connectedSheet = nullptr;
int AddressOperator::currentRow = 0;
int AddressOperator::currentCol = 0;