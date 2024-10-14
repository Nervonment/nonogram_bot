#include <chrono>
#include <iostream>

void log(std::ostream& os) {
    std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >(
    	std::chrono::system_clock::now().time_since_epoch()
    );
    os << "[LOG] timestamp: " << ms.count() << std::endl;
}