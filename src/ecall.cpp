#include "../includes/ecall.hpp"
#include "../includes/notificationService.hpp"
#include "../includes/vehicle.hpp"
#include <bits/stdc++.h>
using namespace std;

void ECALLSystem::Data_logging(unique_ptr<Vehicle> v) {
  aws_service as;
  server_service ss;
  json j;
  j["vehicle id"] = v->id;
  j["vehicle speed"] = v->speed;
  j["vehicle acceleration"] = v->acceleration;
  j["vehicle location"] = v->location;

  auto logger = [](json j) {
    ofstream outfile("/home/ubuntu/Emergency_Call_System/build/accident.json",
                     ios::app);
    outfile << j.dump(4);
    outfile.close();
  };
  logger(j);

  cout << "Emergency call ...";

  thread t1(&aws_service::send,
            &as); // passing class objects as the functions are not static
  thread t2(&server_service::send, &ss);
  t1.join();
  t2.join();
}

// another solution
// outfile.open("accident.json", ios::app);
// outfile << "{\n"
//         << " \"vehicle id\": " << Vehicle::id << ", \n"
//         << " \"vehicle speed\": " << Vehicle::speed << ", \n"
//         << " \"vehicle acceleration\": " << Vehicle::acceleration << ", \n"
//         << " \"vehicle location\": " << Vehicle::location << ", \n"
//         << "}\n";
// outfile.close();
