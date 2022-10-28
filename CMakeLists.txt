cmake_minimum_required(VERSION 3.1)

project(opentelemetry-cpp-apm-example)

# See https://github.com/open-telemetry/opentelemetry-cpp/blob/main/INSTALL.md#incorporating-into-an-existing-cmake-project
# See https://github.com/open-telemetry/opentelemetry-cpp-contrib/blob/main/instrumentation/nginx/CMakeLists.txt
find_package(opentelemetry-cpp CONFIG REQUIRED)
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
# For WITH_OTLP_HTTP
find_package(CURL)
# For not WITH_API_ONLY
find_package(nlohmann_json)

add_executable(example_otlp_grpc grpc_main.cc)
target_include_directories(example_otlp_grpc PRIVATE ${OPENTELEMETRY_CPP_INCLUDE_DIRS})
target_link_libraries(example_otlp_grpc PRIVATE ${OPENTELEMETRY_CPP_LIBRARIES})

