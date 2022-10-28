#include <stdio.h>

#include "opentelemetry/exporters/otlp/otlp_grpc_exporter_factory.h"
#include "opentelemetry/sdk/trace/simple_processor_factory.h"
#include "opentelemetry/sdk/trace/tracer_provider_factory.h"
#include "opentelemetry/trace/provider.h"

namespace trace     = opentelemetry::trace;
namespace nostd     = opentelemetry::nostd;
namespace trace_sdk = opentelemetry::sdk::trace;
namespace otlp      = opentelemetry::exporter::otlp;

void InitTracer()
{
  opentelemetry::exporter::otlp::OtlpGrpcExporterOptions opts;
  opts.endpoint = "ap-guangzhou.apm.tencentcs.com:4317";
  if (!getenv("TOKEN")) {
    printf("No env TOKEN\n"); exit(-1);
  }
  printf("APM endpoint=%s, TOKEN=%dB\n", opts.endpoint.c_str(), (int)strlen(getenv("TOKEN")));

  // Create OTLP exporter instance
  auto exporter  = otlp::OtlpGrpcExporterFactory::Create(opts);
  auto processor = trace_sdk::SimpleSpanProcessorFactory::Create(std::move(exporter));
  std::shared_ptr<opentelemetry::trace::TracerProvider> provider =
      trace_sdk::TracerProviderFactory::Create(
          std::move(processor),
          opentelemetry::sdk::resource::Resource::Create({
              {"service.name", "srs-apm-sdk"},
              {"token", getenv("TOKEN")},
          })
      );

  // Set the global trace provider
  trace::Provider::SetTracerProvider(provider);
}

namespace
{
nostd::shared_ptr<trace::Tracer> get_tracer()
{
  auto provider = trace::Provider::GetTracerProvider();
  return provider->GetTracer("app", OPENTELEMETRY_SDK_VERSION);
}
}

int main(int argc, char *argv[])
{
  InitTracer();

  // See https://github.com/open-telemetry/opentelemetry-cpp-contrib/blob/main/instrumentation/nginx/src/otel_ngx_module.cpp
  trace::StartSpanOptions startOpts;
  startOpts.kind = trace::SpanKind::kServer;
  auto span = get_tracer()->StartSpan("main", startOpts);

  startOpts.parent = span->GetContext();
  auto scoped_span = trace::Scope(get_tracer()->StartSpan("sub", startOpts));

  return 0;
}

