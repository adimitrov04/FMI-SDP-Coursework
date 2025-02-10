#include "../../include/commands/Command.h"
#include "../../include/commands/CommandFactory.hpp"

CommandGenerator::CommandGenerator (const char *setIdentifier, const char *setUsageInfo)
: identifier(setIdentifier)
, usage_info(setUsageInfo)
{
    CommandFactory::GetFactory().RegisterCommand(this);
}