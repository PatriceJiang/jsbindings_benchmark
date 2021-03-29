#pragma once

#include "v8.h"

std::string stackTraceToString(v8::Local<v8::StackTrace> stack);
void reject_Promise(v8::PromiseRejectMessage msg);
void message_Callback(v8::Local<v8::Message> message, v8::Local<v8::Value> data);