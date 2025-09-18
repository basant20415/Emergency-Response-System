#ifndef _Notification_Service_
#define _Notification_Service_
#include "aws.hpp"
#include "server.hpp"
class NotificationService {
public:
  virtual void send() = 0;
  virtual ~NotificationService() = default;
};

class aws_service : public NotificationService {
public:
  void send() override { aws_call(); }
};

class server_service : public NotificationService {
public:
  void send() override { server_call(); }
};
#endif