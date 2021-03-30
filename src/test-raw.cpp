#include <benchmark/benchmark.h>
#include <math.h>
#include <array>

#include "simple_v8.h"
#include "raw_v8.h"
#include "raw-bindings.h"
#include "color.h"
#include "params.h"

std::shared_ptr<js::JS> jsx;

class UniqueSE {
public:
    UniqueSE() {
        js::JSPlatform::Setup("");
        jsx = js::JS::Instance();
        //jsx->SetupContext();
        v8::Isolate* isolate = jsx->GetIsolate();

        register_all_color(isolate);

        v8::HandleScope scope(isolate);
        v8::Local<v8::Context> context = isolate->GetCurrentContext();
        v8::Local<v8::Value> ret;

        std::string code = readFile("test.js");
        {
            std::stringstream ss;
            ss << "var LOOP_TIMES = " << LOOP_TIMES << ";" << std::endl;
            auto condCode = ss.str();
            jsx->EvalString(condCode.c_str(), ret);
            
        }
        jsx->EvalString(code, ret);


        bindVariable(isolate, context, "testFn", testFn);
        bindVariable(isolate, context, "loopJS", loopJS);
        bindVariable(isolate, context, "loopCPP", loopCPP);


        bindVariable(isolate, context, "loopJSAttr", loopJSAttr);
        bindVariable(isolate, context, "loopJSDynAttr", loopJSDynAttr);
        bindVariable(isolate, context, "loopJSBAttr", loopJSBAttr);
        bindVariable(isolate, context, "loopJSBDynAttr", loopJSBDynAttr);
        bindVariable(isolate, context, "c", varC);

        std::cout << "----!!! LOOP_TIMES " << LOOP_TIMES << " !!!-----" <<  std::endl;

        bindVariable(isolate, context, "loopJSB_call_2_args", loopJSB_call_2_args);
        bindVariable(isolate, context, "loopJSB_call_3_args", loopJSB_call_3_args);
        bindVariable(isolate, context, "loopJSB_call_4_args", loopJSB_call_4_args);

        bindVariable(isolate, context, "loopJSB_call2_1_args", loopJSB_call2_1_args);
        bindVariable(isolate, context, "loopJSB_call2_2_args", loopJSB_call2_2_args);
        bindVariable(isolate, context, "loopJSB_call2_3_args", loopJSB_call2_3_args);
        bindVariable(isolate, context, "loopJSB_call2_4_args", loopJSB_call2_4_args);

    }

    ~UniqueSE() {

    }

    v8::Persistent<v8::Value> testFn;
    v8::Persistent<v8::Value> loopJS;
    v8::Persistent<v8::Value> loopCPP;
    v8::Persistent<v8::Value> loopJSAttr;
    v8::Persistent<v8::Value> loopJSDynAttr;
    v8::Persistent<v8::Value> loopJSBAttr;
    v8::Persistent<v8::Value> loopJSBDynAttr;
    v8::Persistent<v8::Value> varC;

    v8::Persistent<v8::Value> loopJSB_call_2_args;
    v8::Persistent<v8::Value> loopJSB_call_3_args;
    v8::Persistent<v8::Value> loopJSB_call_4_args;


    v8::Persistent<v8::Value> loopJSB_call2_1_args;
    v8::Persistent<v8::Value> loopJSB_call2_2_args;
    v8::Persistent<v8::Value> loopJSB_call2_3_args;
    v8::Persistent<v8::Value> loopJSB_call2_4_args;


private:

    void bindVariable(v8::Isolate *isolate, v8::Local<v8::Context> &context, const std::string_view &name, v8::Persistent<v8::Value> &out) {
        v8::Local<v8::Value> ret;
        v8::Local<v8::String> testFnName = js::toJSString(isolate, name);
        ret = jsx->GetGlobalObject()->GetRealNamedProperty(context, testFnName).ToLocalChecked();
        v8::Local<v8::Function> fn = ret.As<v8::Function>();
        out.Reset(jsx->GetIsolate(), fn);
    }
};

UniqueSE inx;



static void BM_CallEvalCallPureJSFunc(benchmark::State& state) {
    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Function> fn = inx.testFn.Get(isolate).As<v8::Function>();
    for (auto _ : state) {
        //v8::MaybeLocal<v8::Value> result = fn->CallAsFunction(context, v8::Null(isolate), 0, {});
        //uint32_t v = result.ToLocalChecked()->Uint32Value(context).FromJust();
        //assert(v == 0x808080FF);
        v8::Local<v8::Value> ret;
        jsx->EvalString("testFn()", ret);
        uint32_t v = ret->Int32Value(context).FromJust();
        assert(v == 0x808080FF);
        benchmark::DoNotOptimize(v);
    }
}

static void BM_CallBindingJSFunc(benchmark::State& state) {
    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Function> fn = inx.testFn.Get(isolate).As<v8::Function>();
    for (auto _ : state) {
        v8::MaybeLocal<v8::Value> result = fn->CallAsFunction(context, v8::Null(isolate), 0, {});
        uint32_t v = result.ToLocalChecked()->Uint32Value(context).FromJust();
        assert(v == 0x808080FF);
        benchmark::DoNotOptimize(v);
    }
}

static void BM_CallPureCPPFunc(benchmark::State& state) {
    Color* c = new Color{128, 128, 128, 255};
    for (auto _ : state) {
        uint32_t v = c->intValue();
        assert(v == 0x808080FF);
        benchmark::DoNotOptimize(v);
    }
}

static void BM_CallLoopJSFunc(benchmark::State& state) {

    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Function> fn = inx.loopJS.Get(isolate).As<v8::Function>();
    std::array<v8::Local<v8::Value>, 1> args = { v8::Int32::New(isolate, LOOP_TIMES) };
    for (auto _ : state) {
        v8::MaybeLocal<v8::Value> result = fn->CallAsFunction(context, v8::Null(isolate), args.size(), args.data());
        benchmark::DoNotOptimize(result);
    }
}

static void BM_CallLoopCPPFunc(benchmark::State& state) {

    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Function> fn = inx.loopCPP.Get(isolate).As<v8::Function>();
    for (auto _ : state) {
        v8::MaybeLocal<v8::Value> result = fn->CallAsFunction(context, v8::Null(isolate), 0, nullptr);
        benchmark::DoNotOptimize(result);
    }
}

static void BM_CallLoopJS_AttrFunc(benchmark::State& state) {

    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Function> fn = inx.loopJSAttr.Get(isolate).As<v8::Function>();
    for (auto _ : state) {
        v8::MaybeLocal<v8::Value> result = fn->CallAsFunction(context, v8::Null(isolate), 0, nullptr);
        benchmark::DoNotOptimize(result);
        assert(result.ToLocalChecked()->IsNumber());
    }
}

static void BM_CallLoopJS_Dyn_AttrFunc(benchmark::State& state) {

    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Function> fn = inx.loopJSDynAttr.Get(isolate).As<v8::Function>();
    for (auto _ : state) {
        v8::MaybeLocal<v8::Value> result = fn->CallAsFunction(context, v8::Null(isolate), 0, nullptr);
        benchmark::DoNotOptimize(result);
        assert(result.ToLocalChecked()->IsNumber());
    }
}

static void BM_CallLoopJSB_AttrFunc(benchmark::State& state) {

    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Function> fn = inx.loopJSBAttr.Get(isolate).As<v8::Function>();
    for (auto _ : state) {
        v8::MaybeLocal<v8::Value> result = fn->CallAsFunction(context, v8::Null(isolate), 0, nullptr);
        benchmark::DoNotOptimize(result);
        assert(result.ToLocalChecked()->IsNumber());
    }
}

static void BM_CallLoopJSB_Dyn_AttrFunc(benchmark::State& state) {

    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Function> fn = inx.loopJSBDynAttr.Get(isolate).As<v8::Function>();
    for (auto _ : state) {
        v8::MaybeLocal<v8::Value> result = fn->CallAsFunction(context, v8::Null(isolate), 0, nullptr);
        benchmark::DoNotOptimize(result);
        assert(result.ToLocalChecked()->IsNumber());
    }
}

static void BM_AccessJSPropertyInCPP(benchmark::State& state) {

    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Object> obj = inx.varC.Get(isolate).As<v8::Function>();
    
    for (auto _ : state) {
        v8::Local<v8::Value> key = js::toJSString(isolate, "a");
        v8::MaybeLocal<v8::Value> result = obj->Get(context, key);
        benchmark::DoNotOptimize(result);
        auto v = result.ToLocalChecked()->Uint32Value(context).FromJust();
        assert(v == 255);
    }
}

static void BM_AccessJSPropertyInCPPOpt(benchmark::State& state) {

    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Object> obj = inx.varC.Get(isolate).As<v8::Function>();

    v8::Local<v8::Value> key = js::toJSString(isolate, "a");
    v8::MaybeLocal<v8::Value> result;
    for (auto _ : state) {
        result = obj->Get(context, key);
        benchmark::DoNotOptimize(result);
        assert(result.ToLocalChecked()->Int32Value(context).FromJust() == 255);
    }
}

static void BM_CallNatveWith_2_arguments(benchmark::State& state) {

    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Function> fn = inx.loopJSB_call_2_args.Get(isolate).As<v8::Function>();
    for (auto _ : state) {
        v8::MaybeLocal<v8::Value> result = fn->CallAsFunction(context, v8::Null(isolate), 0, nullptr);
        benchmark::DoNotOptimize(result);
        assert(result.ToLocalChecked()->IsObject());
    }
}

static void BM_CallNatveWith_3_arguments(benchmark::State& state) {

    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Function> fn = inx.loopJSB_call_3_args.Get(isolate).As<v8::Function>();
    for (auto _ : state) {
        v8::MaybeLocal<v8::Value> result = fn->CallAsFunction(context, v8::Null(isolate), 0, nullptr);
        benchmark::DoNotOptimize(result);
        assert(result.ToLocalChecked()->IsObject());
    }
}
static void BM_CallNatveWith_4_arguments(benchmark::State& state) {

    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Function> fn = inx.loopJSB_call_4_args.Get(isolate).As<v8::Function>();
    for (auto _ : state) {
        v8::MaybeLocal<v8::Value> result = fn->CallAsFunction(context, v8::Null(isolate), 0, nullptr);
        benchmark::DoNotOptimize(result);
        assert(result.ToLocalChecked()->IsObject());
    }
}

static void BM_CallNatveWith_2_1_arguments(benchmark::State& state) {

    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Function> fn = inx.loopJSB_call2_1_args.Get(isolate).As<v8::Function>();
    for (auto _ : state) {
        v8::MaybeLocal<v8::Value> result = fn->CallAsFunction(context, v8::Null(isolate), 0, nullptr);
        benchmark::DoNotOptimize(result);
        assert(result.ToLocalChecked()->IsObject());
    }
}

static void BM_CallNatveWith_2_2_arguments(benchmark::State& state) {

    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Function> fn = inx.loopJSB_call2_2_args.Get(isolate).As<v8::Function>();
    for (auto _ : state) {
        v8::MaybeLocal<v8::Value> result = fn->CallAsFunction(context, v8::Null(isolate), 0, nullptr);
        benchmark::DoNotOptimize(result);
        assert(result.ToLocalChecked()->IsObject());
    }
}

static void BM_CallNatveWith_2_3_arguments(benchmark::State& state) {

    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Function> fn = inx.loopJSB_call2_3_args.Get(isolate).As<v8::Function>();
    for (auto _ : state) {
        v8::MaybeLocal<v8::Value> result = fn->CallAsFunction(context, v8::Null(isolate), 0, nullptr);
        benchmark::DoNotOptimize(result);
        assert(result.ToLocalChecked()->IsObject());
    }
}

static void BM_CallNatveWith_2_4_arguments(benchmark::State& state) {

    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Function> fn = inx.loopJSB_call2_4_args.Get(isolate).As<v8::Function>();
    for (auto _ : state) {
        v8::MaybeLocal<v8::Value> result = fn->CallAsFunction(context, v8::Null(isolate), 0, nullptr);
        benchmark::DoNotOptimize(result);
        assert(result.ToLocalChecked()->IsObject());
    }
}

static void BM_Empty(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
    }
}



// Register the function as a benchmark
//BENCHMARK(BM_SomeFunction)->Range(8, 8 << 10)->Complexity(benchmark::BigO::oAuto);// ->Iterations(1);
//BENCHMARK(BM_DenseRange)->DenseRange(0, 1024, 128);

BENCHMARK(BM_Empty);
BENCHMARK(BM_CallEvalCallPureJSFunc);
BENCHMARK(BM_CallBindingJSFunc);
BENCHMARK(BM_CallPureCPPFunc);
BENCHMARK(BM_CallLoopCPPFunc);
BENCHMARK(BM_CallLoopJSFunc);

BENCHMARK(BM_CallLoopJS_AttrFunc);
BENCHMARK(BM_CallLoopJS_Dyn_AttrFunc);
BENCHMARK(BM_CallLoopJSB_AttrFunc);
BENCHMARK(BM_CallLoopJSB_Dyn_AttrFunc);

BENCHMARK(BM_AccessJSPropertyInCPP);
BENCHMARK(BM_AccessJSPropertyInCPPOpt);

BENCHMARK(BM_CallNatveWith_2_arguments);
BENCHMARK(BM_CallNatveWith_3_arguments);
BENCHMARK(BM_CallNatveWith_4_arguments);

BENCHMARK(BM_CallNatveWith_2_1_arguments);
BENCHMARK(BM_CallNatveWith_2_2_arguments);
BENCHMARK(BM_CallNatveWith_2_3_arguments);
BENCHMARK(BM_CallNatveWith_2_4_arguments);

BENCHMARK(BM_Empty);

// Run the benchmark
BENCHMARK_MAIN();