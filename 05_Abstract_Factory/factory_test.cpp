
#include "factory.h"
#include <iostream>
#include <functional>

// 1
enum class PayloadType : uint16_t
{
  VehicleIdRequest = 0x0001,
  RoutingActivationRequest = 0x0005,
  AliveCheckResponse = 0x0008,
  DiagMessage = 0x8001
};

class MessageHandler
{
public:
  virtual void Print() = 0;
  virtual ~MessageHandler() noexcept = default;
};

class VehicleIdRequestHandler : public MessageHandler
{
private:
  void* _opaque;
public:
  VehicleIdRequestHandler(void* ctx) : _opaque(ctx) {}
  void Print() override { std::cout << (char*)_opaque << "Vehicle Id Request Handler" << std::endl; }
};

class RoutingActivationRequestHandler : public MessageHandler
{
private:
  void* _opaque;
public:
  RoutingActivationRequestHandler(void* ctx) : _opaque(ctx) {}
  void Print() override { std::cout << (char*)_opaque << "Routing Activation Request Handler" << std::endl; }
};

class AliveCheckResponseHandler : public MessageHandler
{
private:
  void* _opaque;
public:
  AliveCheckResponseHandler(void* ctx) : _opaque(ctx) {}
  void Print() override { std::cout << (char*)_opaque << "Alive Check Response Handler" << std::endl; }
};

class DiagMessageHandler : public MessageHandler
{
private:
  void* _opaque;
public:
  DiagMessageHandler(void* ctx) : _opaque(ctx) {}
  void Print() override { std::cout << (char*)_opaque << "Diag Message Handler" << std::endl; }
};

// 2
enum class ServiceType : uint8_t
{
  DiagnosticSessionControl = 0x10,
  ECUReset = 0x11,
  SecurityAccess = 0x27
};

class ServiceHandler
{
public:
  virtual std::string GetName() = 0;
  virtual ~ServiceHandler() noexcept = default;
};

class Service10Handler : public ServiceHandler
{
public:
  std::string GetName() override { return "DiagnosticSessionControl"; }
};

class Service11Handler : public ServiceHandler
{
public:
  std::string GetName() override { return "ECUReset"; }
};

class Service27Handler : public ServiceHandler
{
public:
  std::string GetName() override { return "SecurityAccess"; }
};


int main()
{
  char context[] = "This is ";
  
  // 1
  Factory<PayloadType, MessageHandler, MessageHandler*(*)(void*)> payload_factory;

  payload_factory.Register(PayloadType::VehicleIdRequest, [](void* ctx) -> MessageHandler* { return new VehicleIdRequestHandler(ctx); });
  payload_factory.Register(PayloadType::RoutingActivationRequest, [](void* ctx) -> MessageHandler* { return new RoutingActivationRequestHandler(ctx); });
  payload_factory.Register(PayloadType::AliveCheckResponse, [](void* ctx) -> MessageHandler* { return new AliveCheckResponseHandler(ctx); });
  payload_factory.Register(PayloadType::DiagMessage, [](void* ctx) -> MessageHandler* { return new DiagMessageHandler(ctx); });

  MessageHandler* vid_req = payload_factory.CreateObject(PayloadType::VehicleIdRequest, context);
  vid_req->Print();

  for (const auto & elem : payload_factory.Map()) {
    MessageHandler* handler = payload_factory.CreateObject(elem.first, context);
    handler->Print();
  }

  // 2
  Factory<ServiceType, ServiceHandler> service_factory;
  
  service_factory.Register(ServiceType::DiagnosticSessionControl, []() -> ServiceHandler* { return new Service10Handler(); });
  service_factory.Register(ServiceType::ECUReset, []() -> ServiceHandler* { return new Service11Handler(); });
  service_factory.Register(ServiceType::SecurityAccess, []() -> ServiceHandler* { return new Service27Handler(); });

  for (const auto & elem : service_factory.Map()) {
    ServiceHandler* handler = service_factory.CreateObject(elem.first);
    std::cout << handler << ", " << handler->GetName() << std::endl;
  }

  return 0;
}