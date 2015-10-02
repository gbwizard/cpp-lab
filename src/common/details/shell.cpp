#include "common/logger.h"
#include "common/shell.h"

namespace common {

// Простенькая обёртка вокруг кода возврата программы.
class ExitCode
{
public:
    explicit ExitCode(const int32_t code)
        : m_code(code)
    {}

    //! \return True, если программа вышла из-за сигнала SIG_KILL
    bool IsKilled() const {
        return WIFSIGNALED(m_code);
    }

    //! \return Беззнаковый код возврата (из [0, 255]) или -1, если программа вышла по сигналу.
    int GetCode() const {
        return IsKilled() ? -1 : WEXITSTATUS(m_code);
    }

    //! \return Сигнал, по которому вышла программа, или -1, если программа завершилась сама.
    int GetSignal() const {
        return IsKilled() ? WTERMSIG(m_code) : -1;
    }

    std::string ToString() const {
        return std::to_string(GetSignal());
    }

private:
    const int32_t m_code;
};

// Обёртка вокруг системного вызова `popen' в стиле RAII.
class PopenWrapper
{
public:
    PopenWrapper(const std::string& command) {
        LOG_DEBUG("PopenWrapper run: " << command);
        if ((command_pipe_ = ::popen(command.c_str(), "r")) == nullptr) {
            BOOST_THROW_EXCEPTION(ExceptionCannotRunCommand("Cannot run command, errno=" + std::to_string(errno)));
        }
    }


    ~PopenWrapper() {
        if (command_pipe_) {
            // Мы в деструкторе, нельзя кидать исключения.
            try {
                Close();
            } catch (const ExceptionShell& ex) {
                LOG_ERROR("Exception while closing pipe: " << ex.what());
            }
        }
    }

    void Close() {
        assert(command_pipe_);
        int result = ::pclose(command_pipe_);
        command_pipe_ = nullptr;

        // В `pclose' вызывается `wait4'; если в последнем произошла какая-то ошибка, то он вернёт -1 и установит errno в ECHILD.
        if (result == -1 && errno == ECHILD) {
            LOG_WARN("PopenWrapper:: pclose failed");
            result = 0;
        }

        ExitCode exit_code(result);

        if (exit_code.IsKilled()) {
            BOOST_THROW_EXCEPTION(ExceptionScriptWasKilled("script was killed by signal " + exit_code.ToString()));
        } else if (exit_code.GetCode()) {
            BOOST_THROW_EXCEPTION(ExceptionScriptFailed("script exited with code " + exit_code.ToString()));
        }
    }

    std::string ReadAllFromPipe() {
        assert(command_pipe_);
        std::string output;
        const size_t kBufSize = 4096;
        char buf[kBufSize] = { 0 };
        int read = 0;

        while ((read = ::fread(buf, sizeof(buf[0]), kBufSize, command_pipe_)) > 0) {
            output.append(buf, buf + read);
        }

        return output;
    }

    FILE* GetFile() {
        return command_pipe_;
    }

private:
    FILE* command_pipe_;
};

std::string Shell(const std::string& command)
{
    // Открываем трубу.
    PopenWrapper pipe(command);
    const auto output = pipe.ReadAllFromPipe();

    try {
        pipe.Close();
    } catch (const ExceptionShell& ex) {
        ex << shell_output_info(output);
        throw;
    }

    return output;
}

} // namespaces
