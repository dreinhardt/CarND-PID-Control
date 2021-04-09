#include <math.h>
#include <uWS/uWS.h>
#include <iostream>
#include <string>
#include "json.hpp"
#include "PID.h"

// for convenience
using nlohmann::json;
using std::string;
using namespace std;

// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }


const double MAX_SPEED = 80;  // define the wished max speed for the car

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
string hasData(string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != string::npos) {
    return "";
  }
  else if (b1 != string::npos && b2 != string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}

int main() {
  uWS::Hub h;

  PID pid_steer, pid_throttle;
  pid_steer.Init(0.5, 0, 2); // I chose my TAO Coeffs for the steering_angle (steer_value)
  pid_throttle.Init(0.5, 0, 1);   // I chose my TAO Coeffs for the throttle (throttle_value)

  h.onMessage([&pid_steer, &pid_throttle](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, 
                     uWS::OpCode opCode) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event
    if (length && length > 2 && data[0] == '4' && data[1] == '2') {
      auto s = hasData(string(data).substr(0, length));

      if (s != "") {
        auto j = json::parse(s);

        string event = j[0].get<string>();

        if (event == "telemetry") {
          // j[1] is the data JSON object
          double cte = std::stod(j[1]["cte"].get<string>());  // cross track error for steering (staying in the middle of the street)
          double speed = std::stod(j[1]["speed"].get<string>());
          double angle = std::stod(j[1]["steering_angle"].get<string>());
          double steer_value, throttle_value;
          double cte_throttle; // cross track error for velocity (achieving a given mph)
          /**
           * TODO: Calculate steering value here, remember the steering value is [-1, 1].
           * NOTE: Feel free to play around with the throttle and speed.
           *   Maybe use another PID controller to control the speed!
           */
          
          // Calculate Steering Value
            pid_steer.UpdateError(cte);
            steer_value = pid_steer.TotalError();

          // Sanity checks
            steer_value = (steer_value < -1) ? -1 : steer_value;
            steer_value = (steer_value >  1) ?  1 : steer_value;


          // Calculate Trottle Value
            if (fabs(angle)<10){
              cte_throttle = speed - MAX_SPEED;           // we want to drive the maximum adjusted speed
            }else{
              cte_throttle = speed - MAX_SPEED * 0.2;
            }
            cte_throttle = cte_throttle/100;
            pid_throttle.UpdateError(cte_throttle);
            throttle_value = pid_throttle.TotalError();   // arrange, that the car is driving the wished speed

          // Sanity checks
            throttle_value = (throttle_value < -1) ? -1 : throttle_value;
            throttle_value = (throttle_value >  1) ? 1 : throttle_value;


          
          // DEBUG
          cout << "\t\t CTE: " << cte << "\t\t SV: " << steer_value <<  "\t\t Angle: " << deg2rad(angle) << " " << angle << "\t\t CTE_T: " << cte_throttle << "\t\t TV: " << throttle_value << "\t\t Speed: " << speed << endl;

          json msgJson;
          msgJson["steering_angle"] = steer_value;
          msgJson["throttle"] = throttle_value;
          auto msg = "42[\"steer\"," + msgJson.dump() + "]";
          // std::cout << msg << std::endl;
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
        }  // end "telemetry" if
      } else {
        // Manual driving
        string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }  // end websocket message if
  }); // end h.onMessage

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, 
                         char *message, size_t length) {
    ws.close();
    std::cout << "Disconnected" << std::endl;
  });

  int port = 4567;
  if (h.listen(port)) {
    std::cout << "Listening to port " << port << std::endl;
  } else {
    std::cerr << "Failed to listen to port" << std::endl;
    return -1;
  }
  
  h.run();
}