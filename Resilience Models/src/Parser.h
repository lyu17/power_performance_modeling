// Copyright 2012-2013 UT-Battelle, LLC.  See LICENSE.txt for more information.
#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <map>

class ASTAppModel;
class ASTMachModel;

/// Loads a single (app or machine) model, resolving and
/// parsing any imports recursively.
bool LoadAppOrMachineModel(const std::string &fn,
                           ASTAppModel *&app,
                           ASTMachModel *&mach);

/// Loads both an app model and a machine model in either order.
bool LoadAppAndMachineModels(const std::string &fn1,
                             const std::string &fn2,
                             ASTAppModel *&app,
                             ASTMachModel *&mach);


/// Parses a single file, but leaves any imports unresolved.
/// This will successfully parse include directives.
/// This is primarily used for debugging; you should generally
/// use one of the 'Load' routines above instead of calling this,
/// because if we're given file names, we will be able to resolve
/// imports of file names.
bool ParseSingleFile(const std::string &fn,
                     ASTAppModel *&app,
                     ASTMachModel *&mach);

/// Parses a single string, but leaves any imports unresolved.
/// This will fail if it encounters include directives, but is
/// a viable option for self-contained machine and app models.
bool ParseSingleModelString(const std::string &str,
                            ASTAppModel *&app,
                            ASTMachModel *&mach);

// Recursively parses all imported models in an App model.
/// This is primarily used for debugging; you should generally
/// use one of the 'Load' routines above instead of calling this.
bool ResolveImports(ASTAppModel *app, std::string basedir = "");

#endif
