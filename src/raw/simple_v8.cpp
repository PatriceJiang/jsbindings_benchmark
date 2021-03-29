#include "simple_v8.h"
#include <cassert>
#include "libplatform/libplatform.h"

#include "v8_callback.h"

namespace {
    std::shared_ptr<js::JSPlatform> _jsplatform;
    std::shared_ptr<js::JS> _jsjs;
}

namespace js {

void JSPlatform::Setup(const std::string_view & flags) {
    if (!_jsplatform) {
        _jsplatform = std::make_shared<JSPlatform>(flags);
    }
}

std::shared_ptr<JSPlatform> JSPlatform::Instance() {
    assert(_jsplatform);
    return _jsplatform;
}

JSPlatform::JSPlatform(const std::string_view & flags){
    _v8flags = flags;
    //NOTICE: spaces are required between flags
    _v8flags.append(" --expose-gc-as=" "gc");
    //_v8flags.append(" --jitless");
    if (!_v8flags.empty())
    {
        v8::V8::SetFlagsFromString(_v8flags.c_str(), (int)_v8flags.length());
    }
    _platform = v8::platform::NewDefaultPlatform();
    v8::V8::InitializePlatform(_platform.get());
    v8::V8::Initialize();
    
}

JSPlatform::~JSPlatform(){
    //_platform.release();
    v8::V8::Dispose();
    v8::V8::ShutdownPlatform();
}


std::shared_ptr<JS> JS::Instance() {
    if (!_jsjs) {
        _jsjs = std::shared_ptr<JS>(new JS);
    }
    return _jsjs;
}

JS::JS() {
    v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    _isolate = v8::Isolate::New(create_params);
    v8::HandleScope hs(_isolate);
    v8::Local<v8::Context> ctx = v8::Context::New(_isolate);
    _context.Reset(_isolate, ctx);
    _isolate->Enter();
    _context.Get(_isolate)->Enter();
}

void JS::SetupContext() {
    v8::Local<v8::Context> ctx = _context.Get(_isolate);
    //// Enter the context for compiling and running the hello world script.
    v8::Context::Scope context_scope(ctx);
    {
        _isolate->SetPromiseRejectCallback(reject_Promise);
        _isolate->AddMessageListener(message_Callback);
    }

}

JS::~JS() {
    {
        v8::HandleScope sp(_isolate);
        _context.Get(_isolate)->DetachGlobal();
        _context.Get(_isolate)->Exit();
        _context.Reset();
    }
    _isolate->Exit();
}


bool JS::EvalString(const std::string_view& code, v8::Local<v8::Value> &out) {
    v8::EscapableHandleScope scope(_isolate);
    v8::Local<v8::Context> context = _isolate->GetCurrentContext();
    v8::Local<v8::String> source = v8::String::NewFromUtf8(_isolate, code.data(), v8::NewStringType::kNormal)
        .ToLocalChecked();

    v8::Local<v8::Script> script = v8::Script::Compile(context, source).ToLocalChecked();

    v8::TryCatch tryCatch(_isolate);

    v8::MaybeLocal<v8::Value> maybeResult = script->Run(context);

    if (tryCatch.HasCaught()) {
        v8::Local<v8::Value> exception = tryCatch.Exception();
        std::string exceptionStr = fromJSValue(_isolate, exception);
        printf("[try] Exception: %s\n", exceptionStr.c_str());
        v8::Local<v8::StackTrace> stacktracev = tryCatch.Message()->GetStackTrace();
        std::string stackTrace = stackTraceToString(stacktracev);
        printf(" [try] stacktrace: %s\n", stackTrace.c_str());
        return false;
    }

    if (maybeResult.IsEmpty()) {
        printf("[error] %s\n", __FUNCTION__);
        return false;
    }

    v8::Local<v8::Value> result = maybeResult.ToLocalChecked();
    out = scope.Escape(result);
    return true;
}

std::string fromJSValue(v8::Isolate* isolate, v8::Local<v8::Value>& v)
{
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::String> str = v->ToString(context).ToLocalChecked();
    v8::String::Utf8Value value(isolate, str);
    return std::string(*value);
}

v8::Local<v8::String> toJSString(v8::Isolate* isolate, const std::string_view& text)
{
    v8::Local<v8::String> str = v8::String::NewFromUtf8(isolate, text.data(), v8::NewStringType::kNormal, text.size()).ToLocalChecked();
    return str;
}

}