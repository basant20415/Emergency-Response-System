#include "../includes/aws.hpp"
#include "../includes/notificationService.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <mqtt/client.h>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>
#include <thread>
using json = nlohmann::json;

json readJsonFile(const std::string &filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file: " + filepath);
  }
  json j;
  file >> j;
  return j;
}

void aws_call() {

  try {
    mqtt::client client(ADDRESS, CLIENTID);

    mqtt::ssl_options ssl_opts;
    ssl_opts.set_trust_store(CA_PATH);
    ssl_opts.set_key_store(CERT_PATH);
    ssl_opts.set_private_key(KEY_PATH);

    mqtt::connect_options conn_opts;
    conn_opts.set_ssl(ssl_opts);
    conn_opts.set_keep_alive_interval(std::chrono::seconds(20));
    conn_opts.set_clean_session(false);

    std::cout << "Connecting to AWS IoT Core..." << std::endl;
    client.connect(conn_opts);

    if (!client.is_connected()) {
      std::cerr << "Client failed to connect!" << std::endl;
      // throw mqtt::exception();
    }

    std::cout << "Connected to AWS IoT Core!" << std::endl;

    json accident_data = readJsonFile(JSON_FILE);

    // Publish JSON as a string
    std::string payload = accident_data.dump();

    mqtt::message_ptr msg = mqtt::make_message(TOPIC, payload, QOS, false);
    client.publish(msg);
    std::cout << "Published current data.\n";

    client.disconnect();
    std::cout << "Disconnected from AWS IoT Core.\n";

  } catch (const mqtt::exception &exc) {
    std::cerr << "MQTT Exception: " << exc.what() << std::endl;
  }

  return;
}