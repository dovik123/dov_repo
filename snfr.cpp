#include <pcap.h>
#include <iostream>
#include <iomanip>

// Callback function invoked by pcap for each captured packet
void packet_handler(u_char* user, const struct pcap_pkthdr* header, const u_char* packet) {
    std::cout << "Packet captured with length: " << header->len << std::endl;

    // Print packet data in hexadecimal format
    for (int i = 0; i < header->len; ++i) {
        std::cout << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(packet[i]) << " ";
        // Print a new line every 16 bytes for better readability
        if ((i + 1) % 16 == 0)
            std::cout << std::endl;
    }
    std::cout << std::endl;  // Separate packets with a newline
}

int main() {
    char errbuf[PCAP_ERRBUF_SIZE];  // Error buffer
    pcap_if_t* alldevs;  // All available devices
    pcap_if_t* device;   // The device we will sniff on
     /// changes
    // Find all network devices
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        std::cerr << "Error finding devices: " << errbuf << std::endl;
        return -1;
    }

    // Select the first device (just for demonstration)
    device = alldevs;
    if (device == NULL) {
        std::cerr << "No devices found." << std::endl;
        return -1;
    }

    // Open the device for sniffing
    pcap_t* handle = pcap_open_live(device->name, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        std::cerr << "Error opening device: " << errbuf << std::endl;
        return -1;
    }

    // Start the packet capture loop
    pcap_loop(handle, 10, packet_handler, NULL);

    // Cleanup
    pcap_freealldevs(alldevs);
    pcap_close(handle);

    return 0;
}
