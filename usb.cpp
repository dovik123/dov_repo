#include <iostream>
#include <fcntl.h>   // File control definitions
#include <unistd.h>  // UNIX standard function definitions
#include <errno.h>   // Error number definitions
#include <string.h>  // String function definitions

int main() {
    // Specify the USB port to open
    const char* portname = "/dev/tty1";

    // Open the USB port
    int fd = open(portname, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        std::cerr << "Failed to open USB port " << portname << ": " << strerror(errno) << std::endl;
        return 1;
    } else {
        std::cout << "USB port " << portname << " opened successfully." << std::endl;
    }

    // Remember to close the port when done
    close(fd);

    return 0;
}
