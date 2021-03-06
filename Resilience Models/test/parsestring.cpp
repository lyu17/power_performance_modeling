// Copyright 2012-2013 UT-Battelle, LLC.  See LICENSE.txt for more information.
#include <iostream>
#include <deque>
#include <cstdio>
#include <map>

#include "ASTAppModel.h"
#include "ASTMachModel.h"
#include "Parser.h"

using namespace std;

bool CheckAppParsing()
{
  try {
      const char *appmodel =
          "model simple\n"
          "{\n"
          "    param value = 1\n"
          "    kernel main\n"
          "    {\n"
          "        execute { flops [20] loads [10] }\n"
          "    }\n"
          "}\n";
    ASTAppModel *app = NULL;
    ASTMachModel *mach = NULL;

    bool success = ParseSingleModelString(appmodel, app, mach);
    if (!success)
    {
        THROW(TestError, "Errors encountered during parsing.  Aborting.");
    }
    if (mach || !app)
    {
        THROW(TestError, "Expected an app model, not a machine model.");
    }
    cout << "\n----- Parsed Application Model -----\n";
    app->Print(cout);
  }
  catch (const AspenException &exc)
  {
    cerr << exc.PrettyString() << endl;
    return false;
  }
  return true;
}

bool CheckMachParsing()
{
  try {
      const char *machmodel =
          "core mycore {\n"
          "    resource flops(num) [num / tera]\n"
          "}\n"
          "\n"
          "memory mymem {\n"
          "    resource loads(bytes) [70*nano + bytes/(32*giga)]\n"
          "    resource stores(bytes) [70*nano + bytes/(32*giga)]\n"
          "    conflict loads, stores\n"
          "}\n"
          "\n"
          "cache mycache {\n"
          "    capacity [16*kilo]\n"
          "}\n"
          "\n"
          "link mybus {\n"
          "    resource intracomm(bytes) [bytes/(12*giga)]\n"
          "}\n"
          "\n"
          "socket mysocket {\n"
          "    [1] mycore cores\n"
          "    mymem memory\n"
          "    private mycache cache\n"
          "    linked with mybus\n"
          "}\n"
          "\n"
          "node mynode {\n"
          "    [1] mysocket sockets\n"
          "}\n"
          "\n"
          "machine simple {\n"
          "    [1] mynode nodes\n"
          "}\n";
    ASTAppModel *app = NULL;
    ASTMachModel *mach = NULL;

    bool success = ParseSingleModelString(machmodel, app, mach);
    if (!success)
    {
        THROW(TestError, "Errors encountered during parsing.  Aborting.");
    }
    if (app || !mach)
    {
        THROW(TestError, "Expected an app model, not a machine model.");
    }
    cout << "\n----- Parsed Machine Model -----\n";
    mach->Print(cout);
  }
  catch (const AspenException &exc)
  {
    cerr << exc.PrettyString() << endl;
    return false;
  }
  return true;
}

int main(int argc, char **argv)
{
    bool success = CheckAppParsing() && CheckMachParsing();
    return (!success);
}
