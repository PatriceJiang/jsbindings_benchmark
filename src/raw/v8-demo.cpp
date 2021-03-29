
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <unistd.h>
#include <assert.h>


#include "libplatform/libplatform.h"
#include "v8.h"

#include <vector>
#include <iostream>
#include <sstream>


std::string load_file(const char *path) {
    FILE *fp = fopen(path, "rt");
    fseek(fp, 0, SEEK_END);
    auto size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    std::vector<char> buff(size);
    fread(buff.data(), size, 1, fp);
    fclose(fp);
    return buff.data();
}


void native_Print(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate * isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);
    
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    auto len = args.Length();
    for(auto i = 0; i < len; i++) {
        auto str =args[i]->ToString(context).ToLocalChecked();
        v8::String::Utf8Value utf8(isolate, str);
        std::cout << "[native_print] "<< i << ": " << *utf8 << std::endl;
    }
}

void setTypedArray(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);

    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    auto len = args.Length();
    if (len == 3) {
        v8::Local<v8::Float32Array> buffer = args[0].As<v8::Float32Array>();
        if (buffer.IsEmpty()) {
            std::cout << __FUNCTION__ << " arg type error!" << std::endl;
            return;
        }
        int idx = args[1]->Int32Value(context).FromJust();
        auto & content = buffer->Buffer()->GetContents();

        double value = args[2]->NumberValue(context).FromJust();
        float *ptr = (float*)content.Data();

        std::cout << "old value at " << idx << " is " << *ptr << std::endl;
        ptr[idx] = (float)value;
        std::cout << "new value at " << idx << " is " << value << std::endl;

    } else {
        args.GetReturnValue().SetUndefined();
    }
}


std::string stackTraceToString(v8::Local<v8::StackTrace> stack)
{
    std::string stackStr;
    if (stack.IsEmpty())
        return stackStr;

    char tmp[100] = {0};
    for (int i = 0, e = stack->GetFrameCount(); i < e; ++i)
    {
        v8::Local<v8::StackFrame> frame = stack->GetFrame(v8::Isolate::GetCurrent(), i);
        v8::Local<v8::String> script = frame->GetScriptName();
        std::string scriptName;
        if (!script.IsEmpty())
        {
            scriptName = *v8::String::Utf8Value(v8::Isolate::GetCurrent(), script);
        }

        v8::Local<v8::String> func = frame->GetFunctionName();
        std::string funcName;
        if (!func.IsEmpty())
        {
            funcName = *v8::String::Utf8Value(v8::Isolate::GetCurrent(), func);
        }

        stackStr += "[";
        snprintf(tmp, sizeof(tmp), "%d", i);
        stackStr += tmp;
        stackStr += "]";
        stackStr += (funcName.empty() ? "anonymous" : funcName.c_str());
        stackStr += "@";
        stackStr += (scriptName.empty() ? "(no filename)" : scriptName.c_str());
        stackStr += ":";
        snprintf(tmp, sizeof(tmp), "%d:%d", frame->GetLineNumber(), frame->GetColumn());
        stackStr += tmp;

        if (i < (e-1))
        {
            stackStr += "\n";
        }
    }

    return stackStr;
}

std::string valueToString(v8::Local<v8::Value> value)
{
    if(value.IsEmpty()) {
        return "[empty]";
    }
    v8::String::Utf8Value typestr(v8::Isolate::GetCurrent(), value->TypeOf(v8::Isolate::GetCurrent()));
    v8::String::Utf8Value utf8str(v8::Isolate::GetCurrent(), value);
    
//
//    if(!msg.IsEmpty()) {
//        std::cout << "value is message" << std::endl;
//    }
    
    v8::Local<v8::StackTrace> st = v8::Exception::GetStackTrace(value);
    auto stack = stackTraceToString(st);
    
    std::stringstream ss;
    ss << " <" << *typestr << "> " << *utf8str;
    // ss << "[[stack: " << stack << "]]";
    return ss.str();
}

void reject_Promise(v8::PromiseRejectMessage msg){
    std::cout << "[err]----unhandled Promise----" << std::endl;
    
    v8::HandleScope scope(v8::Isolate::GetCurrent());
    v8::Local<v8::StackTrace> stackTrace = v8::StackTrace::CurrentStackTrace(v8::Isolate::GetCurrent(), 20, v8::StackTrace::kOverview);
    
    auto stackString = stackTraceToString(stackTrace);
    
    auto event = msg.GetEvent();
    std::string eventType;
    
    if(event == v8::kPromiseRejectWithNoHandler) {
        eventType = "0: unhandled rejected promise";
    }else if(event == v8::kPromiseHandlerAddedAfterReject) {
        eventType = "1: handle added after promise rejected";
    }else if(event == v8::kPromiseRejectAfterResolved) {
        eventType = "2: resolve after promise rejected";
    }else if( event == v8::kPromiseResolveAfterResolved) {
        eventType = "3: resolve after promise resolved";
    }
    
    std::cout << "[err] event: {" << eventType <<"}" <<  std::endl;
    std::cout << "[err]  stack: " << stackString << std::endl;
    std::cout << "[err]  value: " << valueToString(msg.GetValue()) << std::endl;
    
}

void message_Callback(v8::Local<v8::Message> message, v8::Local<v8::Value> data)
{
    v8::Local<v8::Context> context = v8::Isolate::GetCurrent()->GetCurrentContext();
    v8::String::Utf8Value  text(v8::Isolate::GetCurrent(), message->Get());
    auto stack = stackTraceToString(message->GetStackTrace());
    std::cout << "[message] " << *text << std::endl << "file: " << valueToString(message->GetScriptResourceName())
            << ":" << message->GetLineNumber(context).ToChecked()
            << ":" << message->GetStartColumn() <<", " << message->GetEndColumn()
        <<   std::endl;
    std::cout << "[stack]" << stack << std::endl;
}

void fatalError(const char* file, const char* message) {
    std::cout << "[FATAL ERROR] " << file << ", " << message << std::endl;
}


////////////////////////////////// binding class ///////////////////////////////

class Entity {
public:
    Entity() = default;
    virtual ~Entity() {
        std::cout << "~Entity" << std::endl;
        //delete _persist;
        _persist.Reset();
    }
    int sum(int n) {
        if (n < 0) return 0;
        int s = 0, i = 0;
        while (i < n) {
            s += (++i);
        }
        return s;
    }
    v8::Persistent<v8::Object> _persist;
};

void weakCallback(const v8::WeakCallbackInfo<void>& info) {
    std::cout << __FUNCTION__ << " finalize " << info.GetParameter() << std::endl;
    Entity *ptr = (Entity*)info.GetParameter();
    delete ptr;
}


void binding_Entity_constructor(const v8::FunctionCallbackInfo<v8::Value>& info) {
    v8::HandleScope scope(info.GetIsolate());
    if (info.IsConstructCall()) {
        Entity* entity = new Entity();
        v8::Local<v8::Object> thisObj = info.Holder();
        thisObj->SetAlignedPointerInInternalField(0, entity);
        //entity->_persist = new v8::Persistent<v8::Object>(info.GetIsolate(), thisObj);
        entity->_persist.Reset(info.GetIsolate(), info.This());
        entity->_persist.SetWeak((void*)entity, weakCallback, v8::WeakCallbackType::kFinalizer);
    }
}

void binding_Entity_sum(const v8::FunctionCallbackInfo<v8::Value>& info) {
    v8::HandleScope scope(info.GetIsolate());
    void *ptr = info.This()->GetAlignedPointerFromInternalField(0);
    Entity* entity = static_cast<Entity*>(ptr);
    v8::Local<v8::Context> context =  info.GetIsolate()->GetCurrentContext();
    if (info.Length() == 1) {
        assert(info[0]->IsNumber());
        int32_t arg0 = info[0]->ToInt32(context).ToLocalChecked()->Int32Value(context).FromJust();
        int ert = entity->sum(arg0);
        v8::Local<v8::Integer> ret = v8::Int32::New(info.GetIsolate(), ert);
        info.GetReturnValue().Set(ret);
    }
    else {
        info.GetReturnValue().Set(v8::Undefined(info.GetIsolate()));
    }
}


////////////////////////////////// end     class ///////////////////////////////


void doInIsolate(int argc, char **argv) {
    // Create a new Isolate and make it the current one.
    v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator =
        v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    v8::Isolate* isolate = v8::Isolate::New(create_params);
    {
        v8::Isolate::Scope isolate_scope(isolate);

        // Create a stack-allocated handle scope.
        v8::HandleScope handle_scope(isolate);

        // Create a new context.
        v8::Local<v8::Context> context = v8::Context::New(isolate);

        // Enter the context for compiling and running the hello world script.
        v8::Context::Scope context_scope(context);
        {
            isolate->SetPromiseRejectCallback(reject_Promise);
            isolate->AddMessageListener(message_Callback);
            // isolate->SetCaptureStackTraceForUncaughtExceptions(true, 20, v8::StackTrace::kOverview);
             //isolate->SetFatalErrorHandler(fatalError);
        }

        v8::Local<v8::Object> globalObj = context->Global();

        {
            v8::Local<v8::String> key = v8::String::NewFromUtf8(isolate, "print").ToLocalChecked();
            v8::Local<v8::Function> print = v8::Function::New(context, native_Print).ToLocalChecked();
            globalObj->Set(context, key, print);
        }
        {
            v8::Local<v8::String> key = v8::String::NewFromUtf8(isolate, "testFloatArray").ToLocalChecked();
            v8::Local<v8::Function> print = v8::Function::New(context, setTypedArray).ToLocalChecked();
            globalObj->Set(context, key, print);
        }

        {
            v8::Local<v8::String> key = v8::String::NewFromUtf8(isolate, "Entity").ToLocalChecked();
            v8::Local<v8::FunctionTemplate> fnTpl = v8::FunctionTemplate::New(isolate, binding_Entity_constructor);
            //v8::Local<v8::ObjectTemplate> fnTplProto = fnTpl->PrototypeTemplate();
            //fnTplProto->SetInternalFieldCount(1);

            fnTpl->InstanceTemplate()->SetInternalFieldCount(1);


            v8::Local<v8::String> method = v8::String::NewFromUtf8(isolate, "sum").ToLocalChecked();

            v8::Local<v8::ObjectTemplate> fnProto = fnTpl->PrototypeTemplate();

            v8::Local<v8::FunctionTemplate> methodSum = v8::FunctionTemplate::New(isolate, binding_Entity_sum);

            fnProto->Set(method, methodSum);

            globalObj->Set(context, key, fnTpl->GetFunction(context).ToLocalChecked()).Check();
        }

        {
            // Create a string containing the JavaScript source code.

            auto content = load_file(argv[1]);


            v8::Local<v8::String> source =
                v8::String::NewFromUtf8(isolate, content.c_str(),
                    v8::NewStringType::kNormal)
                .ToLocalChecked();

            v8::Local<v8::String> url = v8::String::NewFromUtf8(isolate, argv[1]).ToLocalChecked();
            v8::ScriptOrigin origin(url);

            // Compile the source code.
            v8::Local<v8::Script> script =
                v8::Script::Compile(context, source, &origin).ToLocalChecked();

            // Run the script to get the result.
            v8::TryCatch tryBlock(isolate);

            v8::MaybeLocal<v8::Value> maybeResult = script->Run(context);

            if (tryBlock.HasCaught()) {
                v8::Local<v8::Value> exception = tryBlock.Exception();
                std::string exceptionStr = valueToString(exception);
                printf("[try] Exception: %s\n", exceptionStr.c_str());
                v8::Local<v8::StackTrace> stacktracev = tryBlock.Message()->GetStackTrace();
                std::string stackTrace = stackTraceToString(stacktracev);
                printf(" [try] stacktrace: %s\n", stackTrace.c_str());
            }

            if (maybeResult.IsEmpty()) {
                printf("[error] Run() failed: return empty\n");
            }
            else {

                v8::Local<v8::Value> result = maybeResult.ToLocalChecked();

                // Convert the result to an UTF8 string and print it.
                v8::String::Utf8Value utf8(isolate, result);
                printf("%s\n", *utf8);
            }
        }

        context->DetachGlobal();

    }

    // Dispose the isolate and tear down V8.
    isolate->Dispose();
    delete create_params.array_buffer_allocator;
}



int main(int argc, char* argv[]) {
    // Initialize V8.

    std::string flags;
    //NOTICE: spaces are required between flags
    flags.append(" --expose-gc-as=" "gc");
    if (!flags.empty())
    {
        v8::V8::SetFlagsFromString(flags.c_str(), (int)flags.length());
    }


    v8::V8::InitializeICUDefaultLocation(argv[0]);
    v8::V8::InitializeExternalStartupData(argv[0]);
    std::unique_ptr<v8::Platform> platform = v8::platform::NewDefaultPlatform();
    v8::V8::InitializePlatform(platform.get());
    v8::V8::Initialize();
    


    doInIsolate(argc, argv);

    doInIsolate(argc, argv);

    doInIsolate(argc, argv);
  

    v8::V8::Dispose();
    v8::V8::ShutdownPlatform();
    return 0;
}
