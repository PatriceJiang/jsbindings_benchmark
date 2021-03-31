#include "raw-bindings.h"
#include "color.h"
#include "simple_v8.h"
#include <iostream>

void js_weakCallback(const v8::WeakCallbackInfo<void>& info) {
    auto* ptr = (Color*)info.GetParameter();
    delete ptr;
}

void js_Color_constructor(const v8::FunctionCallbackInfo<v8::Value>& info) {
    v8::Isolate* isolate = info.GetIsolate();
    v8::HandleScope scope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    if (info.IsConstructCall()) {
        auto* color = new Color();
        v8::Local<v8::Object> thisObj = info.This();
        thisObj->SetAlignedPointerInInternalField(0, color);
        //entity->_persist = new v8::Persistent<v8::Object>(info.GetIsolate(), thisObj);
        const auto argc = info.Length();
        if (argc > 0) {
            color->r = info[0]->Int32Value(context).FromJust();
        }
        if (argc > 1) {
            color->g = info[1]->Int32Value(context).FromJust();
        }
        if (argc > 2) {
            color->b = info[2]->Int32Value(context).FromJust();
        }
        if (argc > 3) {
            color->a = info[3]->Int32Value(context).FromJust();
        }
    }
}

void js_Color_intValue(const v8::FunctionCallbackInfo<v8::Value>& info) {
    v8::HandleScope scope(info.GetIsolate());
    void* ptr = info.This()->GetAlignedPointerFromInternalField(0);
    Color* color = static_cast<Color*>(ptr);
    v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
    if (info.Length() == 0) {
        uint32_t ert = color->intValue();
        v8::Local<v8::Integer> ret = v8::Int32::New(info.GetIsolate(), ert);
        info.GetReturnValue().Set(ret);
    }
    else {
        info.GetReturnValue().Set(v8::Undefined(info.GetIsolate()));
    }
}

void js_Color_add2(const v8::FunctionCallbackInfo<v8::Value>& info) {
    v8::HandleScope scope(info.GetIsolate());
    void* ptr = info.This()->GetAlignedPointerFromInternalField(0);
    Color* color = static_cast<Color*>(ptr);
    v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
    if (info.Length() == 2) {
        Color * arg0 = (Color*)info[0].As<v8::Object>()->GetAlignedPointerFromInternalField(0);
        Color* arg1 = (Color*)info[1].As<v8::Object>()->GetAlignedPointerFromInternalField(0);
        color->add2(arg0, arg1);
        info.GetReturnValue().Set(v8::Undefined(info.GetIsolate()));
    }
    else {
        info.GetReturnValue().Set(v8::Undefined(info.GetIsolate()));
    }
}


void js_Color_add3(const v8::FunctionCallbackInfo<v8::Value>& info) {
    v8::HandleScope scope(info.GetIsolate());
    void* ptr = info.This()->GetAlignedPointerFromInternalField(0);
    Color* color = static_cast<Color*>(ptr);
    v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
    if (info.Length() == 3) {
        Color* arg0 = (Color*)info[0].As<v8::Object>()->GetAlignedPointerFromInternalField(0);
        Color* arg1 = (Color*)info[1].As<v8::Object>()->GetAlignedPointerFromInternalField(0);
        Color* arg2 = (Color*)info[2].As<v8::Object>()->GetAlignedPointerFromInternalField(0);
        color->add3(arg0, arg1, arg2);
        info.GetReturnValue().Set(v8::Undefined(info.GetIsolate()));
    }
    else {
        info.GetReturnValue().Set(v8::Undefined(info.GetIsolate()));
    }
}
void js_Color_add4(const v8::FunctionCallbackInfo<v8::Value>& info) {
    v8::HandleScope scope(info.GetIsolate());
    void* ptr = info.This()->GetAlignedPointerFromInternalField(0);
    Color* color = static_cast<Color*>(ptr);
    v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
    if (info.Length() == 4) {
        Color* arg0 = (Color*)info[0].As<v8::Object>()->GetAlignedPointerFromInternalField(0);
        Color* arg1 = (Color*)info[1].As<v8::Object>()->GetAlignedPointerFromInternalField(0);
        Color* arg2 = (Color*)info[2].As<v8::Object>()->GetAlignedPointerFromInternalField(0);
        Color* arg4 = (Color*)info[3].As<v8::Object>()->GetAlignedPointerFromInternalField(0);
        color->add4(arg0, arg1, arg2, arg4);
        info.GetReturnValue().Set(v8::Undefined(info.GetIsolate()));
    }
    else {
        info.GetReturnValue().Set(v8::Undefined(info.GetIsolate()));
    }
}

void js_Color_mul1(const v8::FunctionCallbackInfo<v8::Value>& info) {
    v8::HandleScope scope(info.GetIsolate());
    void* ptr = info.This()->GetAlignedPointerFromInternalField(0);
    Color* color = static_cast<Color*>(ptr);
    v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
    if (info.Length() == 1) {
        color->mul1(info[0]->Int32Value(context).FromJust());
        info.GetReturnValue().Set(v8::Undefined(info.GetIsolate()));
    }
    else {
        info.GetReturnValue().Set(v8::Undefined(info.GetIsolate()));
    }
}
void js_Color_mul2(const v8::FunctionCallbackInfo<v8::Value>& info) {
    v8::HandleScope scope(info.GetIsolate());
    void* ptr = info.This()->GetAlignedPointerFromInternalField(0);
    Color* color = static_cast<Color*>(ptr);
    v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
    if (info.Length() == 2) {
        color->mul2(info[0]->Int32Value(context).FromJust(),
            info[1]->Int32Value(context).FromJust());
        info.GetReturnValue().Set(v8::Undefined(info.GetIsolate()));
    }
    else {
        info.GetReturnValue().Set(v8::Undefined(info.GetIsolate()));
    }
}
void js_Color_mul3(const v8::FunctionCallbackInfo<v8::Value>& info) {
    v8::HandleScope scope(info.GetIsolate());
    void* ptr = info.This()->GetAlignedPointerFromInternalField(0);
    Color* color = static_cast<Color*>(ptr);
    v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
    if (info.Length() == 3) {
        color->mul3(info[0]->Int32Value(context).FromJust(),
            info[1]->Int32Value(context).FromJust(),
            info[2]->Int32Value(context).FromJust());
        info.GetReturnValue().Set(v8::Undefined(info.GetIsolate()));
    }
    else {
        info.GetReturnValue().Set(v8::Undefined(info.GetIsolate()));
    }
}

void js_Color_mul4(const v8::FunctionCallbackInfo<v8::Value>& info) {
    v8::HandleScope scope(info.GetIsolate());
    void* ptr = info.This()->GetAlignedPointerFromInternalField(0);
    Color* color = static_cast<Color*>(ptr);
    v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
    if (info.Length() == 4) {
        color->mul4(info[0]->Int32Value(context).FromJust(),
            info[1]->Int32Value(context).FromJust(),
            info[2]->Int32Value(context).FromJust(),
            info[3]->Int32Value(context).FromJust());
        info.GetReturnValue().Set(v8::Undefined(info.GetIsolate()));
    }
    else {
        info.GetReturnValue().Set(v8::Undefined(info.GetIsolate()));
    }
}

static void js_Color_get_r(v8::Local<v8::String> property,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
    v8::Local<v8::Object> thisObj = info.This();
    Color* c = (Color*)thisObj->GetAlignedPointerFromInternalField(0);
    info.GetReturnValue().Set(v8::Int32::New(info.GetIsolate(), c->r));
}

static void js_Color_set_r(v8::Local<v8::String> property,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<void>& info) {
    v8::Local<v8::Object> thisObj = info.This();
    Color* c = (Color*)thisObj->GetAlignedPointerFromInternalField(0);
    int32_t r = value->Int32Value(info.GetIsolate()->GetCurrentContext()).FromJust();
    c->r = (uint8_t)r;
}

static void js_Color_get_g(v8::Local<v8::String> property,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
    v8::Local<v8::Object> thisObj = info.This();
    Color* c = (Color*)thisObj->GetAlignedPointerFromInternalField(0);
    info.GetReturnValue().Set(v8::Int32::New(info.GetIsolate(), c->g));
}

static void js_Color_set_g(v8::Local<v8::String> property,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<void>& info) {
    v8::Local<v8::Object> thisObj = info.This();
    Color* c = (Color*)thisObj->GetAlignedPointerFromInternalField(0);
    int32_t g = value->Int32Value(info.GetIsolate()->GetCurrentContext()).FromJust();
    c->g = (uint8_t)g;
}

static void js_Color_get_b(v8::Local<v8::String> property,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
    v8::Local<v8::Object> thisObj = info.This();
    Color* c = (Color*)thisObj->GetAlignedPointerFromInternalField(0);
    info.GetReturnValue().Set(v8::Int32::New(info.GetIsolate(), c->b));
}

static void js_Color_set_b(v8::Local<v8::String> property,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<void>& info) {
    v8::Local<v8::Object> thisObj = info.This();
    Color* c = (Color*)thisObj->GetAlignedPointerFromInternalField(0);
    int32_t b = value->Int32Value(info.GetIsolate()->GetCurrentContext()).FromJust();
    c->b = (uint8_t)b;
}

static void js_Color_get_a(v8::Local<v8::String> property,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
    v8::Local<v8::Object> thisObj = info.This();
    Color* c = (Color*)thisObj->GetAlignedPointerFromInternalField(0);
    info.GetReturnValue().Set(v8::Int32::New(info.GetIsolate(), c->a));
}

static void js_Color_set_a(v8::Local<v8::String> property,
    v8::Local<v8::Value> value,
    const v8::PropertyCallbackInfo<void>& info) {
    v8::Local<v8::Object> thisObj = info.This();
    Color* c = (Color*)thisObj->GetAlignedPointerFromInternalField(0);
    int32_t a = value->Int32Value(info.GetIsolate()->GetCurrentContext()).FromJust();
    c->a = (uint8_t)a;
}

static void js_Color_get_dyn(v8::Local<v8::String> property,
    const v8::PropertyCallbackInfo<v8::Value>& info) {
    v8::Local<v8::Object> thisObj = info.This();
    Color* c = (Color*)thisObj->GetAlignedPointerFromInternalField(0);
    info.GetReturnValue().Set(v8::Int32::New(info.GetIsolate(), c->dyn()));
}

static void consoleLog(const v8::FunctionCallbackInfo<v8::Value>& info) {
    v8::HandleScope scope(info.GetIsolate());
    void* ptr = info.This()->GetAlignedPointerFromInternalField(0);
    Color* color = static_cast<Color*>(ptr);
    v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
    std::cout << "console.log: ";
    for (int i = 0; i < info.Length(); i++) {
        std::cout << js::fromJSValue(info.GetIsolate(), info[i]) << " "; 
    }
    std::cout << std::endl;
}
static void consoleWarn(const v8::FunctionCallbackInfo<v8::Value>& info) {
    v8::HandleScope scope(info.GetIsolate());
    void* ptr = info.This()->GetAlignedPointerFromInternalField(0);
    Color* color = static_cast<Color*>(ptr);
    v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
    std::cout << "console.warn: ";
    for (int i = 0; i < info.Length(); i++) {
        std::cout << js::fromJSValue(info.GetIsolate(), info[i]) << " ";
    }
    std::cout << std::endl;
}
static void consoleError(const v8::FunctionCallbackInfo<v8::Value>& info) {
    v8::HandleScope scope(info.GetIsolate());
    void* ptr = info.This()->GetAlignedPointerFromInternalField(0);
    Color* color = static_cast<Color*>(ptr);
    v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
    std::cout << "console.error: ";
    for (int i = 0; i < info.Length(); i++) {
        std::cout << js::fromJSValue(info.GetIsolate(), info[i]) << " ";
    }
    std::cout << std::endl;
}static void consoleDebug(const v8::FunctionCallbackInfo<v8::Value>& info) {
    v8::HandleScope scope(info.GetIsolate());
    void* ptr = info.This()->GetAlignedPointerFromInternalField(0);
    Color* color = static_cast<Color*>(ptr);
    v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
    std::cout << "console.debug: ";
    for (int i = 0; i < info.Length(); i++) {
        std::cout << js::fromJSValue(info.GetIsolate(), info[i]) << " ";
    }
    std::cout << std::endl;
}
static void consoleInfo(const v8::FunctionCallbackInfo<v8::Value>& info) {
    v8::HandleScope scope(info.GetIsolate());
    void* ptr = info.This()->GetAlignedPointerFromInternalField(0);
    Color* color = static_cast<Color*>(ptr);
    v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
    std::cout << "console.info: ";
    for (int i = 0; i < info.Length(); i++) {
        std::cout << js::fromJSValue(info.GetIsolate(), info[i]) << " ";
    }
    std::cout << std::endl;
}

void register_all_color(v8::Isolate *isolate) {

    v8::HandleScope scope(isolate);

    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Object> globalObj = context->Global();

    v8::Local<v8::String> colorClassName = v8::String::NewFromUtf8(isolate, "ColorNative").ToLocalChecked();
    v8::Local<v8::FunctionTemplate> fnTpl = v8::FunctionTemplate::New(isolate, js_Color_constructor);

    fnTpl->InstanceTemplate()->SetInternalFieldCount(1);
    v8::Local<v8::ObjectTemplate> fnProto = fnTpl->PrototypeTemplate();

    v8::Local<v8::String> r = js::toJSString(isolate, "r");
    fnProto->SetAccessor(r, js_Color_get_r, js_Color_set_r);

    v8::Local<v8::String> g = js::toJSString(isolate, "g");
    fnProto->SetAccessor(g, js_Color_get_g, js_Color_set_g);

    v8::Local<v8::String> b = js::toJSString(isolate, "b");
    fnProto->SetAccessor(b, js_Color_get_b, js_Color_set_b);

    v8::Local<v8::String> a = js::toJSString(isolate, "a");
    fnProto->SetAccessor(a, js_Color_get_a, js_Color_set_a);


    v8::Local<v8::String> dyn = js::toJSString(isolate, "dyn");
    fnProto->SetAccessor(dyn, js_Color_get_dyn, nullptr);

#define BIND_FUNC(name, fn) do { \
        v8::Local<v8::FunctionTemplate> intValueFn = v8::FunctionTemplate::New(isolate, fn); \
            v8::Local<v8::String> intValue = js::toJSString(isolate, name ); \
        fnProto->Set(intValue, intValueFn); \
    } while (false)

    //v8::Local<v8::FunctionTemplate> intValueFn = v8::FunctionTemplate::New(isolate, js_Color_intValue);
    //v8::Local<v8::String> intValue = js::toJSString(isolate, "intValueNative");
    //fnProto->Set(intValue, intValueFn);

    BIND_FUNC("intValueNative", js_Color_intValue);
    BIND_FUNC("add2", js_Color_add2);
    BIND_FUNC("add3", js_Color_add3);
    BIND_FUNC("add4", js_Color_add4);

    BIND_FUNC("mul1", js_Color_mul1);
    BIND_FUNC("mul2", js_Color_mul2);
    BIND_FUNC("mul3", js_Color_mul3);
    BIND_FUNC("mul4", js_Color_mul4);

    globalObj->Set(context, colorClassName, fnTpl->GetFunction(context).ToLocalChecked()).Check();

    auto maybeConsole = globalObj->Get(context, js::toJSString(isolate, "console"));
    if (!maybeConsole.IsEmpty()) {
        auto consoleObject = maybeConsole.ToLocalChecked().As<v8::Object>();
        consoleObject->Set(context, js::toJSString(isolate, "log"), v8::FunctionTemplate::New(isolate, consoleLog)->GetFunction(context).ToLocalChecked());
        consoleObject->Set(context, js::toJSString(isolate, "warn"), v8::FunctionTemplate::New(isolate, consoleWarn)->GetFunction(context).ToLocalChecked());
        consoleObject->Set(context, js::toJSString(isolate, "error"), v8::FunctionTemplate::New(isolate, consoleError)->GetFunction(context).ToLocalChecked());
        consoleObject->Set(context, js::toJSString(isolate, "debug"), v8::FunctionTemplate::New(isolate, consoleDebug)->GetFunction(context).ToLocalChecked());
        consoleObject->Set(context, js::toJSString(isolate, "info"), v8::FunctionTemplate::New(isolate, consoleInfo)->GetFunction(context).ToLocalChecked());
    }
}