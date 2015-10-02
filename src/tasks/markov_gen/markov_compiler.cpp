#include <cstdlib>

#include <boost/program_options.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include "common/logger.h"
#include "common/shell.h"

namespace fs = boost::filesystem;
namespace po = boost::program_options;
namespace logger = boost::log;

int main (int argc, char* argv[]) {
    logger::trivial::severity_level loglevel;
    std::vector<std::string> urls;
    fs::path output_path;
    int32_t order;

    po::options_description options("options");
    options.add_options()
        ("help,h", "display this message")
        ("loglevel,l", po::value<logger::trivial::severity_level>(&loglevel)->default_value(logger::trivial::warning), "global loglevel (trace, debug, info, warning, error or fatal)")
        ("urls,u", po::value<std::vector<std::string>>(&urls)->multitoken()->required(), "list of urls to UTF8 encoded text files")
        ("order,o", po::value<int32_t>(&order)->required(), "order of generated markov chain")
    ;

    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, options), vm);
        po::notify(vm);
    } catch(const po::error& ex) {
        std::cerr << "Failed to parse command line options: " << ex.what() << std::endl;
        std::cout << options << std::endl;
        return EXIT_FAILURE;
    }

    if (vm.count("help")) {
        std::cout << options << std::endl;
        return EXIT_FAILURE;
    }

    // Инициализируем логгирование
    common::InitLogger(loglevel, common::DefaultLogFormat());

    // Читаем файлы по одному
    for (const std::string& url: urls) {
        const std::string text = common::Shell("curl " + url);
    }


    // Обрабатываем, выкидывая лишние символы, приводя к нижнему регистру и обучая марковский генератор

    // Сохраняем коллекцию для марковского генератора

    return EXIT_SUCCESS;
}
