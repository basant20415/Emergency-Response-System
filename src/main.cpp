#include "../includes/aws.hpp"
#include "../includes/ecall.hpp"
#include "../includes/notificationService.hpp"
#include "../includes/vehicle.hpp"
#include <bits/stdc++.h>
#include <chrono>
using namespace std;
string l;
bool flag = false;
int speed_threshold = 100;
int accel_threshold = 100;
// definitions of static members
int Vehicle::counter = 0;

void load_accidents() {
  ifstream infile("/home/ubuntu/Emergency_Call_System/build/accident.json");
  json file;
  infile >> file;
  cout << "Past accidents: " << file.dump(4) << endl;
}

int main() {
  system("clear");
  cout << "\t\t\tEmergency Call System";
  auto v = make_unique<car>();
  // Vehicle v;
  ECALLSystem es;
  int s;
  int a;
  string l;
  char c;

  auto last_time = chrono::system_clock::now();
  do {
    cout << "\n\n\t\tEnter the speed : ";
    cin >> s;

    cout << "\n\n\t\tEnter the acceleration : ";
    cin >> a;

    cout << "\n\n\t\tEnter the location : ";
    cin >> l;

    if (s < 0 || a < 0) {
      cout << "\t\t\tinvalid input ...";
      continue;
    }
    v->set_acceleration(a);
    v->set_speed(s);
    v->set_location(l);
    auto current_time = chrono::system_clock::now();
    double duration =
        chrono::duration_cast<chrono::seconds>(current_time - last_time)
            .count();
    if (v->detect_accident(s, a, duration)) {
      cout << "\n\n\t\t🚨 Accident detected. Initiating emergency call...";

      es.Data_logging(move(v));
      /*
       std::move(v)  v is moved into Data_logging.
After that call, v becomes null (empty unique_ptr).
Next iteration of the loop, when you call v->detect_accident(...), you
dereference a null pointer → segmentation fault. so we must create another
object for the next iteration
      */
      v = make_unique<car>();
    }

    last_time = current_time;

    cout << "\n\n\t\t\t\tdo you want to continue Y|N ";
    cin >> c;
  } while (c == 'Y' || c == 'y');
}
