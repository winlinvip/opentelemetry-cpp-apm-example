# opentelemetry-cpp-apm-example

HelloWorld for https://github.com/open-telemetry/opentelemetry-cpp for [TAPM](https://cloud.tencent.com/product/apm).

## Usage

Please use Ubuntu 20, and install tools:

```bash
sudo apt update -y
sudo apt install -y cmake gdb gcc g++ make autoconf automake libtool
sudo apt install -y libcurl4-openssl-dev
```

Build [protobuf](https://github.com/protocolbuffers/protobuf/blob/main/cmake/README.md):

```bash
git clone --recursive https://github.com/protocolbuffers/protobuf.git
pushd protobuf && cmake . && make -j8 && sudo make install
popd
```

Build [grpc](https://github.com/grpc/grpc/blob/master/BUILDING.md):

```bash
git clone --recursive https://github.com/grpc/grpc.git
mkdir -p grpc/cmake/build && pushd grpc/cmake/build
cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF ../..
make -j8 && sudo make install
popd
```

Build [OpenTelemetry CPP SDK](https://github.com/open-telemetry/opentelemetry-cpp/blob/main/INSTALL.md#building-as-standalone-cmake-project):

```bash
git clone --recursive https://github.com/open-telemetry/opentelemetry-cpp.git
mkdir -p opentelemetry-cpp/build && pushd opentelemetry-cpp/build
cmake -DWITH_OTLP=ON -DWITH_OTLP_GRPC=ON -DCMAKE_CXX_STANDARD=14 \
	-DBUILD_TESTING=OFF -DWITH_EXAMPLES=ON ..
make -j8 && sudo make install
popd
```

> Note: Requires `C++14` for protobuf, although opentelemetry-cpp doesn't require it.

To check the SDK build by running its example:

```bash
./opentelemetry-cpp/build/examples/grpc/server
./opentelemetry-cpp/build/examples/grpc/client
```

Build this HelloWorld example for [TAPM](https://cloud.tencent.com/product/apm):

```bash
git clone https://github.com/winlinvip/opentelemetry-cpp-apm-example.git
mkdir -p opentelemetry-cpp-apm-example/build && pushd opentelemetry-cpp-apm-example/build
cmake .. && make
```

Run by:

```bash
env TOKEN=xxxxxx opentelemetry-cpp-apm-example/build/example_otlp_grpc
```

> Note: Please change the endpoint if not `ap-guangzhou.apm.tencentcs.com:4317`

> Note: Please change the `service.name` to your service name.

> Note: Please use wireshark to capture the packet and decode as HTTP/2, or install plugin [otel-wireshark-plugin](https://github.com/winlinvip/otel-wireshark-plugin#usage).

You could open the [TAPM console](https://console.cloud.tencent.com/apm/monitor/interface?service=srs-apm-sdk) to query the traces.
