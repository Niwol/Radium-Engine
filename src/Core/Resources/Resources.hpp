#pragma once
#include <Core/RaCore.hpp>
#include <Core/Utils/StdOptional.hpp>

namespace Ra {
namespace Core {

/** \brief Resources paths, plugins paths and data paths management for Radium.
 *
 *  This namespace contains functions, classes and utilities for resource management.
 *  Resources are :
 *    - configuration file (ui, keymapping, ...)
 *    - default shaders
 *    - ...
 *
 *  This namespace also contains functions allowing to set and access paths to store data
 *  generated by Radium applications, plugins or libraries in a portable way.
 *  If not set, the default data path is the working directory of the application.
 *  For Gui::BaseApplication derived applications, and for plugins, the default data path can be set
 *  using command line parameter and is stored in the application settings.
 *  \see Gui::BaseApplication::BaseApplication
 */
namespace Resources {
using namespace Ra::Core::Utils;
/** \name Resources path functions
 * All paths are made absolute using https://en.cppreference.com/w/cpp/filesystem/canonical
 */
///@{
/// \brief Get the path of Radium internal resources.
///
/// Radium resources are located in the Resources directory, searched from Radium lib location.
/// \return the path to access Radium Resources if found, otherwise !has_value
/// \note the pattern searched is "Resources/Radium" since it's the basic resources dir.
RA_CORE_API optional<std::string> getRadiumResourcesPath();

/// \brief Get the path of Radium embedded plugins.
///
/// Radium embedded plugins are located in the Plugins directory, searched from Radium lib location.
/// \return the path to access Radium Plugins. empty string if not found
/// \note the pattern searched is "Plugins/lib" since it's the basic resources dir.
RA_CORE_API optional<std::string> getRadiumPluginsPath();

/// \brief Get the path of the current executable.
///
/// \return the path prefix to access the current executable (always found)
RA_CORE_API optional<std::string> getBasePath();

/// \brief Search for general resource path.
///
/// Search for an accessible Resources (or pattern if given) directory in the current executable (or
/// symbol if != nullptr) path or its parents.
/// \return the pattern path of the dynamic library or exec that contains the given symbol if found,
/// otherwise !has_value
RA_CORE_API optional<std::string> getResourcesPath( void* symbol               = nullptr,
                                                    const std::string& pattern = "Resources" );

///@}
/** \name Data path functions
 * These functions manage a stack of paths so that applications, libraries or plugins could manage
 * paths to store their generated data in a state stack-based approach.
 */
///@{
/// \brief Get the current data path.
///
/// If an application's data path was not pushed before the call of this function, the default
/// value, corresponding to the current working directory is returned. Otherwise, the last path
/// pushed using a call to pushDataPath() is returned.
RA_CORE_API std::string getDataPath();

/// \brief Push a new data path.
///
/// The pushed data path will be returned by getDataPath until it is popped.
/// \param datapath the data path to set as current
RA_CORE_API void pushDataPath( std::string datapath );

/// \brief Pop the current data path.
///
/// The returned data path is removed from the data path stack and will not be available anymore
/// for getDataPath().
/// \return the popped data path.
RA_CORE_API std::string popDataPath();
///@}

} // namespace Resources
} // namespace Core
} // namespace Ra
