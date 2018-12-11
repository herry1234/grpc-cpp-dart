#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>

#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>
#include "pk_ctrl.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using pkcamera::Field;
using pkcamera::CamStatus;
using pkcamera::PkCamera;

class PkCameraImpl final : public PkCamera::Service {
 public:
  explicit PkCameraImpl(const std::string& db) {
      // _currentStatus = "Test";
  }

  Status GetCamStatus(ServerContext* context, const Field* field,
                    CamStatus* status) override {
    status->set_status(0);
    status->set_msg("everything is ok Houston");
    return Status::OK;
  }

 private:

  std::string _currentStatus;
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  PkCameraImpl service("anything");

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}
int main(int argc, char** argv) {

  RunServer();

  return 0;
}