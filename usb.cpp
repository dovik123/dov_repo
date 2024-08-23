#include <iostream>
#include <fcntl.h>   // File control definitions
#include <unistd.h>  // UNIX standard function definitions
#include <termios.h> // POSIX terminal control definitions
#include <cstring>   // For memset

int main() {
    // Specify the USB port to open
    const char* portname = "/dev/ttyUSB0";

    // Open the USB port
    int fd = open(portname, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        std::cerr << "Failed to open USB port " << portname << std::endl;
        return 1;
    } else {
        std::cout << "USB port " << portname << " opened successfully." << std::endl;
    }

    // Configure the serial port
    struct termios options;
    memset(&options, 0, sizeof(options)); // Clear options
    tcgetattr(fd, &options);  // Get current port attributes

    // Set baud rate to 9600
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);

    // 8N1 mode (8 data bits, no parity, 1 stop bit)
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;

    // Disable hardware flow control
    options.c_cflag &= ~CRTSCTS;

    // Enable the receiver and set local mode
    options.c_cflag |= (CLOCAL | CREAD);

    // Apply the settings to the port
    tcsetattr(fd, TCSANOW, &options);

    // Write data to the port
    const char* data = "Hello, USB!";
    int bytes_written = write(fd, data, strlen(data));
    if (bytes_written == -1) {
        std::cerr << "Failed to write to the USB port." << std::endl;
    } else {
        std::cout << "Data written to USB port: " << data << std::endl;
    }

    // Close the USB port
    close(fd);

    return 0;
}
