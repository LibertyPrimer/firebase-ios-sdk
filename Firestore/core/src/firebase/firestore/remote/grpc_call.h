/*
 * Copyright 2018 Google
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_REMOTE_GRPC_CALL_H
#define FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_REMOTE_GRPC_CALL_H

#include <memory>
#include <utility>

#include <grpcpp/client_context.h>
#include <grpcpp/generic/generic_stub.h>
#include <grpcpp/support/byte_buffer.h>

#include "Firestore/core/src/firebase/firestore/remote/stream_operation.h"
#include "Firestore/core/src/firebase/firestore/util/status.h"

namespace firebase {
namespace firestore {
namespace remote {

class GrpcCall {
 public:
  GrpcCall(std::unique_ptr<grpc::ClientContext> context,
           std::unique_ptr<grpc::GenericClientAsyncReaderWriter> call)
      : context{std::move(context)}, call{std::move(call)} {
  }

  void StartCall(GrpcOperation* operation);
  void Read(grpc::ByteBuffer* buffer, GrpcOperation* operation);
  void Write(grpc::ByteBuffer* buffer, GrpcOperation* operation);
  void Finish(grpc::Status* status, GrpcOperation* operation);
  void TryCancel();

 private:
  std::unique_ptr<grpc::ClientContext> context_;
  std::unique_ptr<grpc::GenericClientAsyncReaderWriter> call_;
};

}  // namespace remote
}  // namespace firestore
}  // namespace firebase

#endif  // FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_REMOTE_GRPC_CALL_H
