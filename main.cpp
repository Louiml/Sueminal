#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <Windows.h>
#include <Lmcons.h>
#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <iphlpapi.h>
#include "Color.h"
#pragma comment(lib, "Ws2_32.lib")

bool file_exists(const std::string &filename) {
    std::ifstream file(filename);
    return file.good();
}

void console() {
    TCHAR username[UNLEN + 1];
    DWORD size = sizeof(username) / sizeof(TCHAR);
    std::string command;
    if (GetUserName(username, &size)) {
        std::cout << Color::BGREEN << "Seuminal@" << username << Color::RESET << ":" << Color::BCYAN << "~" << Color::BGREEN << "$ " << Color::RESET;
        std::cin >> command;
        if (command == "help") {
            std::cout << "Commands:" << std::endl;
            std::cout << "  help - Show this help message" << std::endl;
            std::cout << "  exe <filename> - Open an EXE file format" << std::endl;
            std::cout << "  exit - Quit this terminal" << std::endl;
            std::cout << "  wincmd <command> - Run a normal CMD commands" << std::endl;
            std::cout << "  linkopen <URL> - Open URL with a CLI" << std::endl;
            return console();
        } else if (command == "exe") {
            std::string filename;
            std::cout << "Enter the filename: ";
            std::cin.ignore();
            std::getline(std::cin, filename);

        if (file_exists(filename)) {
            std::cout << "File found. Running the file..." << std::endl;
            std::string command = "\"" + filename + "\"";
            system(command.c_str());
        } else {
            std::cerr << "Error: File not found." << std::endl;
            return console();
        }
        } else if (command == "exit") {
            std::cout << "Bye" << std::endl;
            return exit(0);
        } else if (command == "wincmd") {
            std::string cmd;
            std::cin.ignore();
            std::getline(std::cin, cmd);
            system(cmd.c_str());
            return console();
        } else if (command == "linkopen") {
            std::string url;
            std::cout << "Enter the URL to open: ";
            std::cin.ignore();
            std::getline(std::cin, url);

            HINSTANCE result = ShellExecute(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);

            if ((int)result <= 32) {
                std::cerr << "Error: Failed to open the URL." << std::endl;
            } else {
                std::cout << "URL opened successfully." << std::endl;
            }
            return console();
        } else if (command == "pcinfo") {
            WSADATA wsaData;
            int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

            if (result != 0) {
                std::cerr << "WSAStartup failed: " << result << std::endl;
                console();
            }

            char hostname[256];
            result = gethostname(hostname, sizeof(hostname));

            if (result != 0) {
                std::cerr << "gethostname failed: " << WSAGetLastError() << std::endl;
                WSACleanup();
                console();
            }

            std::cout << "Hostname: " << hostname << std::endl;

            hostent *host = gethostbyname(hostname);


            if (result != 0) {
                std::cerr << "getaddrinfo failed: " << result << std::endl;
                WSACleanup();
                console();
            }

            for (int i = 0; host->h_addr_list[i] != NULL; i++) {
                sockaddr_in sockaddr_ipv4;
                memcpy(&sockaddr_ipv4.sin_addr, host->h_addr_list[i], host->h_length);
                char ipv4_str[INET_ADDRSTRLEN];
                DWORD ipv4_str_len = sizeof(ipv4_str);
                WSAAddressToString(reinterpret_cast<LPSOCKADDR>(&sockaddr_ipv4), sizeof(sockaddr_in), NULL, ipv4_str, &ipv4_str_len);
                std::cout << "IP Address: " << ipv4_str << std::endl;
            }
            
            WSACleanup();
            return console();
        } else {
            std::cout << "Command not found" << std::endl;
            return console();
        }
    } else {
        std::cout << "Sorry but your computer doesn't give us access to your computer name so you can't use Sueminal" << Color::RESET << std::endl;
    }
}

int main() {
    std::cout << Color::BCYAN << R"(
 _____                      _             _ 
/  ___|                    (_)           | |
\ `--. _   _  ___ _ __ ___  _ _ __   __ _| |
 `--. \ | | |/ _ \ '_ ` _ \| | '_ \ / _` | |
/\__/ / |_| |  __/ | | | | | | | | | (_| | |
\____/ \__,_|\___|_| |_| |_|_|_| |_|\__,_|_|
)" << std::endl << Color::RESET;
    console();
    return 0;
}
