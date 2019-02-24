#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include <boost/filesystem/path.hpp>

namespace bfs = boost::filesystem;

struct Event {
    std::string group;
    std::string name;
};

const bfs::path kRootPath = "/sys/kernel/debug/tracing";
const bfs::path kAvailableEventsPath = kRootPath / "available_events";

int main(int argc, char* argv[]) {
    // Open file with available events
    std::ifstream ifs(kAvailableEventsPath.string());
    if (! ifs) {
        std::cerr << "FAILED: can't open available events " << kAvailableEventsPath << std::endl;
        return EXIT_FAILURE;
    }

    // Read and parse available events
    const char kNameDelim = ':';
    std::vector<Event> available_events;
    std::string line;
    while (std::getline(ifs, line)) {
        std::string::size_type delim_pos = line.find(kNameDelim);
        if (delim_pos == std::string::npos) {
            std::cerr << "WARN: can't find ':' in group:name '" << line << "'" << std::endl;
            continue;
        }

        Event event;
        event.group = line.substr(0, delim_pos);
        event.name = line.substr(delim_pos + 1);
        available_events.push_back(std::move(event));
    }

    // Print discovered events
    std::cout << "=======================================================" << std::endl;
    std::cout << "Found events:" << std::endl;
    std::cout << "=======================================================" << std::endl;
    for (const Event& ev : available_events) {
        std::cout << "group: " << ev.group << " name: " << ev.name << std::endl;
    }
    std::cout << "=======================================================" << std::endl;
    std::cout << "Total: " << available_events.size() << std::endl;
    std::cout << "=======================================================" << std::endl;
}
