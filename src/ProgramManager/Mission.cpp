#include "mission.h"


Mission::Mission()
{
  logger = NULL;
  search = NULL;
  fileName = NULL;
}

Mission::Mission(const char *fn)
{
  fileName = fn;
  logger = NULL;
  search = NULL;
}

Mission::~Mission()
{
  if(logger != NULL) delete logger;
  if(search != NULL) delete search;
}

bool Mission::getMap()
{
  // implement map.getName function
}

bool Mission::getConfig()
{
  // implement config.getConfig function
}

bool Mission::createLog()
{

}

void Mission::createSearch()
{

}

void Mission::startSearch()
{

}

void printSearchResultsToConsole()
{

}

void saveSearchResultsToLog()
{

}
