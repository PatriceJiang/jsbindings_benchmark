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

        std::cout << " -- bindings" << std::endl;
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

        bindVariable(isolate, context, "loopJS_AOS_sumColor", loopJS_AOS_sumColor);
        bindVariable(isolate, context, "loopJS_Simple_sumColor", loopJS_Simple_sumColor);
        bindVariable(isolate, context, "loopJS_AOS_setColor", loopJS_AOS_setColor);
        bindVariable(isolate, context, "loopJS_Simple_setColor", loopJS_Simple_setColor);

        
        bindVariable(isolate, context, "loopJS_Indirect_AOS_sumColor", loopJS_Indirect_AOS_sumColor);
        bindVariable(isolate, context, "loopJS_Indirect_AOS_sumColor_shuffle", loopJS_Indirect_AOS_sumColor_shuffle);
        bindVariable(isolate, context, "loopJS_Indirect_Simple_sumColor", loopJS_Indirect_Simple_sumColor);

        bindVariable(isolate, context, "loopJS_Indirect_AOS_Scene_sumColor", loopJS_Indirect_AOS_Scene_sumColor);
        bindVariable(isolate, context, "loopJS_Indirect_Simple_Scene_sumColor", loopJS_Indirect_Simple_Scene_sumColor);

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


    v8::Persistent<v8::Value>  loopJS_AOS_sumColor;
    v8::Persistent<v8::Value>  loopJS_Simple_sumColor;
    v8::Persistent<v8::Value>  loopJS_AOS_setColor;
    v8::Persistent<v8::Value>  loopJS_Simple_setColor;

    
    v8::Persistent<v8::Value>  loopJS_Indirect_Simple_sumColor;
    v8::Persistent<v8::Value>  loopJS_Indirect_AOS_sumColor;
    v8::Persistent<v8::Value>  loopJS_Indirect_AOS_sumColor_shuffle;

    
    v8::Persistent<v8::Value>  loopJS_Indirect_AOS_Scene_sumColor;
    v8::Persistent<v8::Value>  loopJS_Indirect_Simple_Scene_sumColor;


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



/**
 * C++ 单次通过 EvalString 调用 纯 JS 函数
 */
static void BM_CallEvalCallPureJSFunc(benchmark::State& state) {
    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Function> fn = inx.testFn.Get(isolate).As<v8::Function>();
    for (auto _ : state) {
        v8::Local<v8::Value> ret;
        jsx->EvalString("testFn()", ret);
        uint32_t v = ret->Int32Value(context).FromJust();
        assert(v == 0x808080FF);
        benchmark::DoNotOptimize(v);
    }
}

/**
 * C++ 单次通过 v8 Handle 调用 纯 JS 函数
 */
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

/**
 * C++ 单次调用 C++ 函数
 */
static void BM_CallPureCPPFunc(benchmark::State& state) {
    Color* c = new Color{128, 128, 128, 255};
    for (auto _ : state) {
        uint32_t v = c->intValue();
        assert(v == 0x808080FF);
        benchmark::DoNotOptimize(v);
    }
}

/**
 *  C++ 调用: JS循环调用 纯 JS 函数
 */
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

/**
 *  C++ 调用: JS循环调用 C++ 函数
 */
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

/**
 *  C++ 调用: JS 循环访问 纯JS 静态属性
 */
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

/**
 *  C++ 调用: JS 循环访问 纯JS 动态属性
 */
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

/**
 *  C++ 调用: JS 循环访问 C++ 属性
 */
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

/**
 *  C++ 调用: JS 循环访问 C++ 动态属性
 */
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

/**
 *  C++ 单次访问纯 JS 对象的属性
 */
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
/**
 *  C++ 单次访问纯 JS 对象的属性(尝试优化)
 */
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
/**
 *  C++ 调用: JS 循环调用 [C++Obj x 2] C++ 函数
 */
static void BM_CallLoopNatveWith_2_arguments(benchmark::State& state) {

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

/**
 *  C++ 调用: JS 循环调用 [C++Obj x 3] C++ 函数
 */
static void BM_CallLoopNatveWith_3_arguments(benchmark::State& state) {

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
/**
 *  C++ 调用: JS 循环调用 [C++Obj x 4] C++ 函数
 */
static void BM_CallLoopNatveWith_4_arguments(benchmark::State& state) {

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


/**
 *  C++ 调用: JS 循环调用 [int x 1] C++ 函数
 */
static void BM_CallLoopNatveWith_2_1_arguments(benchmark::State& state) {

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

/**
 *  C++ 调用: JS 循环调用 [int x 2] C++ 函数
 */
static void BM_CallLoopNatveWith_2_2_arguments(benchmark::State& state) {

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
/**
 *  C++ 调用: JS 循环调用 [int x 3] C++ 函数
 */
static void BM_CallLoopNatveWith_2_3_arguments(benchmark::State& state) {

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
/**
 *  C++ 调用: JS 循环调用 [int x 4] C++ 函数
 */
static void BM_CallLoopNatveWith_2_4_arguments(benchmark::State& state) {

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

static void BM_CallLoopJS_AOS_sumColor(benchmark::State& state) {

    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Function> fn = inx.loopJS_AOS_sumColor.Get(isolate).As<v8::Function>();
    for (auto _ : state) {
        v8::MaybeLocal<v8::Value> result = fn->CallAsFunction(context, v8::Null(isolate), 0, nullptr);
        benchmark::DoNotOptimize(result);
    }
}


static void BM_CallLoopJS_Simple_sumColor(benchmark::State& state) {

    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Function> fn = inx.loopJS_Simple_sumColor.Get(isolate).As<v8::Function>();
    for (auto _ : state) {
        v8::MaybeLocal<v8::Value> result = fn->CallAsFunction(context, v8::Null(isolate), 0, nullptr);
        benchmark::DoNotOptimize(result);
    }
}
static void BM_CallLoopJS_AOS_setColor(benchmark::State& state) {

    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Function> fn = inx.loopJS_AOS_setColor.Get(isolate).As<v8::Function>();
    for (auto _ : state) {
        v8::MaybeLocal<v8::Value> result = fn->CallAsFunction(context, v8::Null(isolate), 0, nullptr);
        benchmark::DoNotOptimize(result);
    }
}

static void BM_CallLoopJS_Simple_setColor(benchmark::State& state) {

    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Function> fn = inx.loopJS_Simple_setColor.Get(isolate).As<v8::Function>();
    for (auto _ : state) {
        v8::MaybeLocal<v8::Value> result = fn->CallAsFunction(context, v8::Null(isolate), 0, nullptr);
        benchmark::DoNotOptimize(result);
    }
}


static void BM_CallLoopJS_Indirect_AOS_sumColor(benchmark::State& state) {

    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Function> fn = inx.loopJS_Indirect_AOS_sumColor.Get(isolate).As<v8::Function>();
    for (auto _ : state) {
        v8::MaybeLocal<v8::Value> result = fn->CallAsFunction(context, v8::Null(isolate), 0, nullptr);
        benchmark::DoNotOptimize(result);
    }
}
static void BM_CallLoopJS_Indirect_AOS_sumColor_shuffle(benchmark::State& state) {

    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Function> fn = inx.loopJS_Indirect_AOS_sumColor_shuffle.Get(isolate).As<v8::Function>();
    for (auto _ : state) {
        v8::MaybeLocal<v8::Value> result = fn->CallAsFunction(context, v8::Null(isolate), 0, nullptr);
        benchmark::DoNotOptimize(result);
    }
}

static void BM_CallLoopJS_Indirect_Simple_sumColor(benchmark::State& state) {

    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Function> fn = inx.loopJS_Indirect_Simple_sumColor.Get(isolate).As<v8::Function>();
    for (auto _ : state) {
        v8::MaybeLocal<v8::Value> result = fn->CallAsFunction(context, v8::Null(isolate), 0, nullptr);
        benchmark::DoNotOptimize(result);
    }
}

static void BM_CallLoopJS_Indirect_AOS_Scene_sumColor(benchmark::State& state) {

    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Function> fn = inx.loopJS_Indirect_AOS_Scene_sumColor.Get(isolate).As<v8::Function>();
    for (auto _ : state) {
        v8::MaybeLocal<v8::Value> result = fn->CallAsFunction(context, v8::Null(isolate), 0, nullptr);
        benchmark::DoNotOptimize(result);
    }
}


static void BM_CallLoopJS_Indirect_Simple_Scene_sumColor(benchmark::State& state) {

    v8::Isolate* isolate = jsx->GetIsolate();
    v8::HandleScope rootScope(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    v8::Local<v8::Function> fn = inx.loopJS_Indirect_Simple_Scene_sumColor.Get(isolate).As<v8::Function>();
    for (auto _ : state) {
        v8::MaybeLocal<v8::Value> result = fn->CallAsFunction(context, v8::Null(isolate), 0, nullptr);
        benchmark::DoNotOptimize(result);
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

BENCHMARK(BM_CallLoopJS_AOS_setColor);
BENCHMARK(BM_CallLoopJS_Simple_setColor);
BENCHMARK(BM_CallLoopJS_AOS_sumColor);
BENCHMARK(BM_CallLoopJS_Simple_sumColor);
BENCHMARK(BM_CallLoopJS_Indirect_AOS_sumColor);
BENCHMARK(BM_CallLoopJS_Indirect_AOS_sumColor_shuffle);
BENCHMARK(BM_CallLoopJS_Indirect_Simple_sumColor);


BENCHMARK(BM_CallLoopJS_Indirect_AOS_Scene_sumColor);
BENCHMARK(BM_CallLoopJS_Indirect_Simple_Scene_sumColor);

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

BENCHMARK(BM_CallLoopNatveWith_2_arguments);
BENCHMARK(BM_CallLoopNatveWith_3_arguments);
BENCHMARK(BM_CallLoopNatveWith_4_arguments);

BENCHMARK(BM_CallLoopNatveWith_2_1_arguments);
BENCHMARK(BM_CallLoopNatveWith_2_2_arguments);
BENCHMARK(BM_CallLoopNatveWith_2_3_arguments);
BENCHMARK(BM_CallLoopNatveWith_2_4_arguments);

BENCHMARK(BM_Empty);

// Run the benchmark
BENCHMARK_MAIN();