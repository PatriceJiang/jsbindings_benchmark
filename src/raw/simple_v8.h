#pragma once

#include "v8.h"

#include <memory>
#include <string>
#include <string_view>

namespace js {

/**
 * v8 platform
 */
class JSPlatform {
public:
  static void Setup(const std::string_view &flags);
  static std::shared_ptr<JSPlatform> Instance();

  JSPlatform(const std::string_view &ref);
  ~JSPlatform();

private:
  std::string _v8flags;
  std::unique_ptr<v8::Platform> _platform;
};

/**
 *  v8 context
 */
class JS {
public:
  static std::shared_ptr<JS> Instance();
  virtual ~JS();

  v8::Local<v8::Object> GetGlobalObject() {
      return _context.Get(_isolate)->Global();
  }

  inline v8::Isolate* GetIsolate() { return _isolate;  }
  inline v8::Local<v8::Context> GetContext() { return _context.Get(_isolate); }

  bool EvalFile(const std::string_view& path);
  bool EvalString(const std::string_view& script, v8::Local<v8::Value>& ret);

  void SetupContext();

private:

  JS();


  v8::Isolate *_isolate = {};
  v8::Persistent<v8::Context> _context = {};
};

std::string fromJSValue(v8::Isolate *isolate, const v8::Local<v8::Value>& v);
v8::Local<v8::String> toJSString(v8::Isolate* isolate, const std::string_view& text);

} // namespace js