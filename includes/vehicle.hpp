#ifndef _vehicle_hpp_
#define _vehicle_hpp_
#include <bits/stdc++.h>
using namespace std;
extern string l;
extern int speed_threshold;
extern int accel_threshold;
class Vehicle {

  friend class ECALLSystem;

public:
  Vehicle() { id = counter++; }
  int get_speed() { return speed; }
  int get_acceleration() { return acceleration; }
  string get_location() { return location; }
  void set_speed(int s) { speed = s; }
  void set_location(string s) { location = s; }
  void set_acceleration(int acc) { acceleration = acc; }
  virtual bool detect_accident(int speed, int acceleration,
                               double duration) = 0;
  virtual string vehicle_type() = 0;

  virtual ~Vehicle() = default;

private:
  static int counter;
  int id;
  int speed;
  int acceleration;
  string location;
};

class car : public Vehicle {
public:
  bool detect_accident(int speed, int acceleration, double duration) override {

    return (speed < speed_threshold && acceleration < accel_threshold &&
            duration < 10);
  }
  string vehicle_type() { return "car"; }
};

class truck : public Vehicle {
public:
  bool detect_accident(int speed, int acceleration, double duration) override {

    return (speed < speed_threshold && acceleration < accel_threshold &&
            duration < 10);
  }
  string vehicle_type() { return "truck"; }
};

#endif
