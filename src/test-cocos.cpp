#include "cocos/bindings/jswrapper/SeApi.h"

#include <cassert>
#include <benchmark/benchmark.h>
#include <math.h>

#include "params.h"
#include "bindings.h"
#include <sstream>

bool started = false;


class SeGuard {
public:
    SeGuard() {
        JSBClassType::init();
        auto *js = se::ScriptEngine::getInstance();
        js->addRegisterCallback(register_all_color);
        js->start();

        auto code = readFile("test.js");

        se::AutoHandleScope scope;
        {
            std::stringstream ss; 
            ss << "var LOOP_TIMES = " << LOOP_TIMES << ";" << std::endl;
            auto condCode = ss.str();
            js->evalString(condCode.c_str(), condCode.length(), nullptr);
        }
        js->evalString(code.data(), code.length(), nullptr);


        js->getGlobalObject()->getProperty("testFn", &testFn);
        testFn.toObject()->incRef();

        js->getGlobalObject()->getProperty("loopJS", &loopJS);
        loopJS.toObject()->incRef();

        js->getGlobalObject()->getProperty("loopCPP", &loopCPP);
        loopCPP.toObject()->incRef();

        js->getGlobalObject()->getProperty("loopJSAttr", &loopJSAttr);
        loopJSAttr.toObject()->incRef();

        js->getGlobalObject()->getProperty("loopJSDynAttr", &loopJSDynAttr);
        loopJSDynAttr.toObject()->incRef();


        js->getGlobalObject()->getProperty("loopJSBAttr", &loopJSBAttr);
        loopJSBAttr.toObject()->incRef();

        js->getGlobalObject()->getProperty("loopJSBDynAttr", &loopJSBDynAttr);
        loopJSBDynAttr.toObject()->incRef();

        js->getGlobalObject()->getProperty("c", &varC);
        varC.toObject()->incRef();

        js->getGlobalObject()->getProperty("loopJSB_call_2_args", &loopJSB_call_2_args);
        loopJSB_call_2_args.toObject()->incRef();
        js->getGlobalObject()->getProperty("loopJSB_call_2_args_opt", &loopJSB_call_2_args_opt);
        loopJSB_call_2_args_opt.toObject()->incRef();
        js->getGlobalObject()->getProperty("loopJSB_call_3_args", &loopJSB_call_3_args);
        loopJSB_call_3_args.toObject()->incRef();
        js->getGlobalObject()->getProperty("loopJSB_call_4_args", &loopJSB_call_4_args);
        loopJSB_call_4_args.toObject()->incRef();

        js->getGlobalObject()->getProperty("loopJSB_call2_1_args", &loopJSB_call2_1_args);
        loopJSB_call2_1_args.toObject()->incRef();
        js->getGlobalObject()->getProperty("loopJSB_call2_2_args", &loopJSB_call2_2_args);
        loopJSB_call2_2_args.toObject()->incRef();
        js->getGlobalObject()->getProperty("loopJSB_call2_3_args", &loopJSB_call2_3_args);
        loopJSB_call2_3_args.toObject()->incRef();
        js->getGlobalObject()->getProperty("loopJSB_call2_4_args", &loopJSB_call2_4_args);
        loopJSB_call2_4_args.toObject()->incRef();


        std::cout << "----!!! LOOP_TIMES " << LOOP_TIMES << " !!!-----" <<  std::endl;
    }
    ~SeGuard() {
        //se::ScriptEngine::getInstance()->cleanup();
        JSBClassType::destroy();
    }
    se::Value testFn;
    se::Value loopJS;
    se::Value loopCPP;
    se::Value loopJSAttr;
    se::Value loopJSDynAttr;
    se::Value loopJSBAttr;
    se::Value loopJSBDynAttr;
    se::Value varC;


    se::Value loopJSB_call_2_args;
    se::Value loopJSB_call_2_args_opt;
    se::Value loopJSB_call_3_args;
    se::Value loopJSB_call_4_args;

    se::Value loopJSB_call2_1_args;
    se::Value loopJSB_call2_2_args;
    se::Value loopJSB_call2_3_args;
    se::Value loopJSB_call2_4_args;
};
SeGuard uniqueSE;


static void BM_CallCocosSEFunc(benchmark::State& state) {
    auto* js = se::ScriptEngine::getInstance();
    auto* fn = uniqueSE.testFn.toObject();
    for (auto _ : state) {
        // This code gets timed
        se::AutoHandleScope scope;
        std::vector<se::Value> jsArgs;
        se::Value ret;
        fn->isFunction();
        fn->call(jsArgs, nullptr, &ret);
        uint32_t color = ret.toUint32();
        assert(color == 0x808080FF);
    }
}

static void BM_CallCPPFunc(benchmark::State& state) {
    auto* c = new Color{128,128,128, 255};

    for (auto _ : state) {
        // This code gets timed
        auto color = c->intValue();
        assert(color == 0x808080FF);
    }
}


static void BM_CallLoopJSFunc(benchmark::State& state) {

    se::AutoHandleScope scope;
    std::vector<se::Value> args = {};
    se::Value ret;
    for (auto _ : state) {
        uniqueSE.loopJS.toObject()->call(args, nullptr, &ret);
    }
}

static void BM_CallLoopCPPFunc(benchmark::State& state) {
    se::AutoHandleScope scope;
    std::vector<se::Value> args = {};
    se::Value ret;
    for (auto _ : state) {
        uniqueSE.loopCPP.toObject()->call(args, nullptr, &ret);
    }
}

static void BM_CallLoopJSAttrFunc(benchmark::State& state) {
    se::AutoHandleScope scope;
    std::vector<se::Value> args = {};
    se::Value ret;
    for (auto _ : state) {
        uniqueSE.loopJSAttr.toObject()->call(args, nullptr, &ret);
    }
}

static void BM_CallLoopJSDynAttrFunc(benchmark::State& state) {
    se::AutoHandleScope scope;
    std::vector<se::Value> args = {};
    se::Value ret;
    for (auto _ : state) {
        uniqueSE.loopJSDynAttr.toObject()->call(args, nullptr, &ret);
    }
}

static void BM_CallLoopJSBAttrFunc(benchmark::State& state) {
    se::AutoHandleScope scope;
    std::vector<se::Value> args = {};
    se::Value ret;
    for (auto _ : state) {
        uniqueSE.loopJSBAttr.toObject()->call(args, nullptr, &ret);
    }
}

static void BM_CallLoopJSBDynAttrFunc(benchmark::State& state) {
    se::AutoHandleScope scope;
    std::vector<se::Value> args = {};
    se::Value ret;
    for (auto _ : state) {
        uniqueSE.loopJSBDynAttr.toObject()->call(args, nullptr, &ret);
    }
}


static void BM_AccessJSPropertyInCPP(benchmark::State& state) {
    se::AutoHandleScope scope;
    std::vector<se::Value> args = {};
    se::Value ret;
    for (auto _ : state) {
        uniqueSE.varC.toObject()->getProperty("a", &ret);
        assert(ret.toInt32() == 255);
    }
}

static void BM_AccessJSPropertyInCPPOpt(benchmark::State& state) {
    se::AutoHandleScope scope;
    std::vector<se::Value> args = {};
    se::Value ret;
    se::Object* c = uniqueSE.varC.toObject();
    for (auto _ : state) {
        c->getProperty("a", &ret);
        assert(ret.toInt32() == 255);
        benchmark::DoNotOptimize(ret);
    }
}


static void BM_CallNatveWith_2_arguments(benchmark::State& state) {
    se::AutoHandleScope scope;
    std::vector<se::Value> args = {};
    se::Value ret;
    for (auto _ : state) {
        uniqueSE.loopJSB_call_2_args.toObject()->call(args, nullptr, &ret);
        assert(ret.isObject());
    }
}

static void BM_CallNatveWith_2_arguments_opt(benchmark::State& state) {
    se::AutoHandleScope scope;
    std::vector<se::Value> args = {};
    se::Value ret;
    for (auto _ : state) {
        uniqueSE.loopJSB_call_2_args_opt.toObject()->call(args, nullptr, &ret);
        assert(ret.isObject());
    }
}


static void BM_CallNatveWith_3_arguments(benchmark::State& state) {
    se::AutoHandleScope scope;
    std::vector<se::Value> args = {};
    se::Value ret;
    for (auto _ : state) {
        uniqueSE.loopJSB_call_3_args.toObject()->call(args, nullptr, &ret);
        assert(ret.isObject());
    }
}
static void BM_CallNatveWith_4_arguments(benchmark::State& state) {
    se::AutoHandleScope scope;
    std::vector<se::Value> args = {};
    se::Value ret;
    for (auto _ : state) {
        uniqueSE.loopJSB_call_4_args.toObject()->call(args, nullptr, &ret);
        assert(ret.isObject());
    }
}

static void BM_CallNatveWith_2_1_arguments(benchmark::State& state) {
    se::AutoHandleScope scope;
    std::vector<se::Value> args = {};
    se::Value ret;
    for (auto _ : state) {
        uniqueSE.loopJSB_call2_1_args.toObject()->call(args, nullptr, &ret);
        assert(ret.isObject());
    }
}

static void BM_CallNatveWith_2_2_arguments(benchmark::State& state) {
    se::AutoHandleScope scope;
    std::vector<se::Value> args = {};
    se::Value ret;
    for (auto _ : state) {
        uniqueSE.loopJSB_call2_2_args.toObject()->call(args, nullptr, &ret);
        assert(ret.isObject());
    }
}

static void BM_CallNatveWith_2_3_arguments(benchmark::State& state) {
    se::AutoHandleScope scope;
    std::vector<se::Value> args = {};
    se::Value ret;
    for (auto _ : state) {
        uniqueSE.loopJSB_call2_3_args.toObject()->call(args, nullptr, &ret);
        assert(ret.isObject());
    }
}

static void BM_CallNatveWith_2_4_arguments(benchmark::State& state) {
    se::AutoHandleScope scope;
    std::vector<se::Value> args = {};
    se::Value ret;
    for (auto _ : state) {
        uniqueSE.loopJSB_call2_4_args.toObject()->call(args, nullptr, &ret);
        assert(ret.isObject());
    }
}

static void BM_Empty(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
    }
}

BENCHMARK(BM_Empty);
BENCHMARK(BM_CallCPPFunc);
BENCHMARK(BM_CallCocosSEFunc);
BENCHMARK(BM_CallLoopJSFunc);
BENCHMARK(BM_CallLoopCPPFunc);
BENCHMARK(BM_CallLoopJSAttrFunc);
BENCHMARK(BM_CallLoopJSDynAttrFunc);
BENCHMARK(BM_CallLoopJSBAttrFunc);
BENCHMARK(BM_CallLoopJSBDynAttrFunc);
BENCHMARK(BM_AccessJSPropertyInCPP);
BENCHMARK(BM_AccessJSPropertyInCPPOpt);

BENCHMARK(BM_CallNatveWith_2_arguments);
BENCHMARK(BM_CallNatveWith_2_arguments_opt);
BENCHMARK(BM_CallNatveWith_3_arguments);
BENCHMARK(BM_CallNatveWith_4_arguments);

BENCHMARK(BM_CallNatveWith_2_1_arguments);
BENCHMARK(BM_CallNatveWith_2_2_arguments);
BENCHMARK(BM_CallNatveWith_2_3_arguments);
BENCHMARK(BM_CallNatveWith_2_4_arguments);
// Run the benchmark
BENCHMARK_MAIN();