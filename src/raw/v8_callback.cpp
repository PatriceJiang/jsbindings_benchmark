#include "v8_callback.h"
#include <iostream>
#include <string>
#include <sstream>


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