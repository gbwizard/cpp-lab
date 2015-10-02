/*! \file
 *  \brief   Методы вызова внешнего исполняемого файл
 *  \author  Anatoly Nikiforov
 *  \date    2015-10-01
 *
 */

#pragma once

#include <boost/filesystem/path.hpp>

#include "exceptions.h"

namespace common {
DECLARE_EXCEPTION(ExceptionShell, common::Exception);
/**/ DECLARE_EXCEPTION(ExceptionCannotRunCommand, ExceptionShell);
/**/ DECLARE_EXCEPTION(ExceptionScriptWasKilled, ExceptionShell);
/**/ DECLARE_EXCEPTION(ExceptionScriptFailed, ExceptionShell);

typedef boost::error_info<struct tag_shell_output_info, std::string> shell_output_info;

//! \brief Вызывает внешнюю команду `command'.
std::string Shell(const std::string& command);
}
