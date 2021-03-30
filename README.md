
测试例说明

| 函数 | 说明 | 
|-------|------|
| `BM_CallEvalCallPureJSFunc` | C++ 单次通过 EvalString 调用 纯 JS 函数 |
| `BM_CallBindingJSFunc` | C++ 单次通过 v8 Handle 调用 纯 JS 函数 |
| `BM_CallPureCPPFunc` |C++ 单次调用 C++ 函数 |
| `BM_CallLoopJSFunc` |  C++ 调用: JS循环调用 纯 JS 函数|
| `BM_CallLoopCPPFunc` | C++ 调用: JS循环调用 C++ 函数|
| `BM_CallLoopJS_AttrFunc` |  C++ 调用: JS 循环访问 纯JS 静态属性|
| `BM_CallLoopJS_Dyn_AttrFunc` |C++ 调用: JS 循环访问 纯JS 动态属性 |
| `BM_CallLoopJSB_AttrFunc` | C++ 调用: JS 循环访问 C++ 属性|
| `BM_CallLoopJSB_Dyn_AttrFunc` | C++ 调用: JS 循环访问 C++ 动态属性|
| `BM_AccessJSPropertyInCPP` | C++ 单次访问纯 JS 对象的属性|
| `BM_AccessJSPropertyInCPPOpt` |C++ 单次访问纯 JS 对象的属性(尝试优化) |
| `BM_CallLoopNatveWith_2_arguments` | C++ 调用: JS 循环调用 [C++Obj x 2] C++ 函数|
| `BM_CallLoopNatveWith_3_arguments` |C++ 调用: JS 循环调用 [C++Obj x 3] C++ 函数 |
| `BM_CallLoopNatveWith_4_arguments` | C++ 调用: JS 循环调用 [C++Obj x 4] C++ 函数 |
| `BM_CallLoopNatveWith_2_1_arguments` |C++ 调用: JS 循环调用 [int x 1] C++ 函数 |
| `BM_CallLoopNatveWith_2_2_arguments` |C++ 调用: JS 循环调用 [int x 2] C++ 函数 |
| `BM_CallLoopNatveWith_2_3_arguments` | C++ 调用: JS 循环调用 [int x 3] C++ 函数 |
| `BM_CallLoopNatveWith_2_4_arguments` | C++ 调用: JS 循环调用 [int x 4] C++ 函数|
