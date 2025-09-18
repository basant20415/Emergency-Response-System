#ifndef _AWS_HPP_
#define _AWS_HPP_

#define ADDRESS "ssl://abr0s9fb0umjr-ats.iot.us-east-2.amazonaws.com:8883"
#define CLIENTID "car"
#define TOPIC "car/accident"
#define QOS 1

#define CA_PATH "/home/root/main_app/root-ca.pem"
#define CERT_PATH "/home/root/main_app/certificate.pem.crt"
#define KEY_PATH "/home/root/main_app/private.pem.key"

#define JSON_FILE "/home/ubuntu/Emergency_Call_System/build/accident.json"

#include <bits/stdc++.h>
#include <nlohmann/json.hpp>
using namespace std;

nlohmann::json readJsonFile(const std::string &filepath);
bool isNotEmpty(const string &filename);
void storeLocally(const string &payload);
std::string readFile(const std::string &filepath);
void clearFile(const std::string &filepath);
void aws_call();
#endif