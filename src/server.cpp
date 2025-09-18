#include "../includes/server.hpp"
#include "../includes/notificationService.hpp"
#include "../includes/vehicle.hpp"
#include <arpa/inet.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#define JSON_FILE "/home/ubuntu/Emergency_Call_System/build/accident.json"

using json = nlohmann::json;

std::string getLastLocation(const std::string &filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    return "unknown";
  }

  std::string content((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());

  std::string objStr;
  int braceCount = 0;
  nlohmann::json lastObj;

  for (char c : content) {
    objStr += c;
    if (c == '{')
      braceCount++;
    else if (c == '}')
      braceCount--;

    if (braceCount == 0 && !objStr.empty()) {
      try {
        lastObj = nlohmann::json::parse(objStr); // overwrite each time
      } catch (...) {
        // ignore parse errors
      }
      objStr.clear();
    }
  }

  if (!lastObj.empty() && lastObj.contains("vehicle location")) {
    return lastObj["vehicle location"].get<std::string>();
  }
  return "unknown";
}

int server_call() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("Socket creation failed");
    return 1;
  }

  sockaddr_in server_addr{};
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(5000); // Flask default port
  inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

  if (connect(sock, (sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("Connection failed");
    return 1;
  }
  std::string location = getLastLocation(JSON_FILE);

  // Put it in the body
  std::string body = "data=🚨 Accident detected with location: " + location;

  //   std::string body = "data= Accident detected with location :" + ;
  std::string request = "POST /receive HTTP/1.1\r\n"
                        "Host: 127.0.0.1:5000\r\n"
                        "Content-Type: application/x-www-form-urlencoded\r\n"
                        "Content-Length: " +
                        std::to_string(body.size()) +
                        "\r\n"
                        "\r\n" +
                        body;

  send(sock, request.c_str(), request.size(), 0);

  char buffer[4096] = {0};
  recv(sock, buffer, sizeof(buffer), 0);
  std::cout << "Response:\n" << buffer << std::endl;

  close(sock);
  return 0;
}
