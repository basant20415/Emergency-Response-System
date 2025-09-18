#ifndef _ECALL_HPP_
#define _ECALL_HPP_
#include "../includes/notificationService.hpp"
#include "../includes/vehicle.hpp"
#include <bits/stdc++.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
extern string l;
class ECALLSystem {
public:
  // ofstream outfile; // Inside a class definition, you can only declare
  // members, not execute code.
  void Data_logging(std::unique_ptr<Vehicle> v);
};

#endif