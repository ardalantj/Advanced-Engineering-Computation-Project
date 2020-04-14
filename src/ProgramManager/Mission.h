#pragma once
#include <iostream>


class Mission
{
public:

    Mission();
    Mission(const char* fileName);
    ~Mission();

    bool getMap();
    bool getConfig();
    bool createLog();
    void createSearch();
    void startSearch();
    void printSearchResultsToConsole();
    void saveSearchResultsToLog();

  private:
    const char* getAlgoName();

    Map map;
    Config config;
    Search* search;
    Logger* logger;
    const char* fileName;
    Result res;
}
