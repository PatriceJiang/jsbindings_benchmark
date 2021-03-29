/****************************************************************************
 Copyright (c) 2019-2021 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/

#include "bindings.h"
#include "cocos/bindings/manual/jsb_conversions.h"
#include "cocos/bindings/manual/jsb_global.h"

se::Object* __jsb_Color_proto;
se::Class* __jsb_Color_class;



static bool js_Color_intValue(se::State& s)
{
    auto* cobj = SE_THIS_OBJECT<Color>(s);
    SE_PRECONDITION2(cobj, false, "js_Color_stop : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        s.rval().setUint32(cobj->intValue());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_Color_intValue)


static bool js_Color_get_r(se::State& s)
{
    auto* cobj = SE_THIS_OBJECT<Color>(s);
    SE_PRECONDITION2(cobj, false, "js_Color_get_r : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        s.rval().setInt32(cobj->r);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_Color_get_r)
static bool js_Color_get_g(se::State& s)
{
    auto* cobj = SE_THIS_OBJECT<Color>(s);
    SE_PRECONDITION2(cobj, false, "js_Color_get_g : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        s.rval().setInt32(cobj->g);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_Color_get_g)

static bool js_Color_get_b(se::State& s)
{
    auto* cobj = SE_THIS_OBJECT<Color>(s);
    SE_PRECONDITION2(cobj, false, "js_Color_get_b : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        s.rval().setInt32(cobj->b);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_Color_get_b)

static bool js_Color_get_a(se::State& s)
{
    auto* cobj = SE_THIS_OBJECT<Color>(s);
    SE_PRECONDITION2(cobj, false, "js_Color_get_a : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        s.rval().setInt32(cobj->a);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_Color_get_a)


static bool js_Color_get_dyn(se::State& s)
{
    auto* cobj = SE_THIS_OBJECT<Color>(s);
    SE_PRECONDITION2(cobj, false, "js_Color_get_dyn : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        s.rval().setInt32(cobj->dyn());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_Color_get_dyn)

static bool js_Color_set_r(se::State& s)
{
    auto* cobj = SE_THIS_OBJECT<Color>(s);
    SE_PRECONDITION2(cobj, false, "js_Color_set_r : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 1) {
        cobj->r = args[0].toInt8();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_SET(js_Color_set_r)

static bool js_Color_set_g(se::State& s)
{
    auto* cobj = SE_THIS_OBJECT<Color>(s);
    SE_PRECONDITION2(cobj, false, "js_Color_set_g : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 1) {
        cobj->g = args[0].toInt8();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_SET(js_Color_set_g)

static bool js_Color_set_b(se::State& s)
{
    auto* cobj = SE_THIS_OBJECT<Color>(s);
    SE_PRECONDITION2(cobj, false, "js_Color_set_b : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 1) {
        cobj->b = args[0].toInt8();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_SET(js_Color_set_b)


static bool js_Color_set_a(se::State& s)
{
    auto* cobj = SE_THIS_OBJECT<Color>(s);
    SE_PRECONDITION2(cobj, false, "js_Color_set_a : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 1) {
        cobj->a= args[0].toInt8();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_SET(js_Color_set_a)


SE_DECLARE_FINALIZE_FUNC(js_Color_finalize)

static bool js_Color_constructor(se::State& s) // constructor.c
{
    auto* cobj = new Color;
    s.thisObject()->setPrivateData(cobj);

    const auto argc = s.args().size();
    if (argc > 0) {
        cobj->r = s.args()[0].toUint8();
    }
    if (argc > 1) {
        cobj->g = s.args()[1].toUint8();
    }
    if (argc > 2) {
        cobj->b = s.args()[2].toUint8();
    }
    if (argc > 3) {
        cobj->a = s.args()[3].toUint8();
    }
    return true;
}
SE_BIND_CTOR(js_Color_constructor, __jsb_Color_class, js_Color_finalize)



static bool js_Color_add2(se::State& s)
{
    auto* cobj = SE_THIS_OBJECT<Color>(s);
    SE_PRECONDITION2(cobj, false, "js_Color_set_a : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 2) {
        Color* c1, * c2;
        sevalue_to_native(args[0], &c1, nullptr);
        sevalue_to_native(args[1], &c2, nullptr);
        cobj->add2(c1, c2);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_Color_add2)

static bool js_Color_add3(se::State& s)
{
    auto* cobj = SE_THIS_OBJECT<Color>(s);
    SE_PRECONDITION2(cobj, false, "js_Color_set_a : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 3) {
        Color* c1, * c2, *c3;
        sevalue_to_native(args[0], &c1, nullptr);
        sevalue_to_native(args[1], &c2, nullptr);
        sevalue_to_native(args[2], &c3, nullptr);
        cobj->add3(c1, c2, c3);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_Color_add3)
static bool js_Color_add4(se::State& s)
{
    auto* cobj = SE_THIS_OBJECT<Color>(s);
    SE_PRECONDITION2(cobj, false, "js_Color_set_a : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 4) {
        Color* c1, * c2, * c3, *c4;
        sevalue_to_native(args[0], &c1, nullptr);
        sevalue_to_native(args[1], &c2, nullptr);
        sevalue_to_native(args[2], &c3, nullptr);
        sevalue_to_native(args[2], &c4, nullptr);
        cobj->add4(c1, c2, c3, c4);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_Color_add4)




static bool js_Color_add2_opt(se::State& s)
{
    auto* cobj = SE_THIS_OBJECT<Color>(s);
    SE_PRECONDITION2(cobj, false, "js_Color_set_a : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 2) {
        Color* c1 = (Color*)args[0].toObject()->getPrivateData();
        Color* c2 = (Color*)args[1].toObject()->getPrivateData();
        cobj->add2(c1, c2);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_Color_add2_opt)



static bool js_Color_mul1(se::State& s)
{
    auto* cobj = SE_THIS_OBJECT<Color>(s);
    SE_PRECONDITION2(cobj, false, "js_Color_set_a : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 1) {
        int m1;
        sevalue_to_native(args[0], &m1, nullptr);
        cobj->mul1(m1);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_Color_mul1)

static bool js_Color_mul2(se::State& s)
{
    auto* cobj = SE_THIS_OBJECT<Color>(s);
    SE_PRECONDITION2(cobj, false, "js_Color_set_a : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 2) {
        int m1,m2;
        sevalue_to_native(args[0], &m1, nullptr);
        sevalue_to_native(args[0], &m2, nullptr);
        cobj->mul2(m1,m2);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_Color_mul2)


static bool js_Color_mul3(se::State& s)
{
    auto* cobj = SE_THIS_OBJECT<Color>(s);
    SE_PRECONDITION2(cobj, false, "js_Color_set_a : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 3) {
        int m1, m2, m3;
        sevalue_to_native(args[0], &m1, nullptr);
        sevalue_to_native(args[0], &m2, nullptr);
        sevalue_to_native(args[0], &m3, nullptr);
        cobj->mul3(m1, m2, m3);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_Color_mul3)


static bool js_Color_mul4(se::State& s)
{
    auto* cobj = SE_THIS_OBJECT<Color>(s);
    SE_PRECONDITION2(cobj, false, "js_Color_set_a : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 4) {
        int m1, m2, m3, m4;
        sevalue_to_native(args[0], &m1, nullptr);
        sevalue_to_native(args[0], &m2, nullptr);
        sevalue_to_native(args[0], &m3, nullptr);
        sevalue_to_native(args[0], &m4, nullptr);
        cobj->mul4(m1, m2, m3, m4);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_Color_mul4)

static bool js_Color_finalize(se::State& s)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<Color>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<Color>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_Color_finalize)

bool js_register_Color(se::Object* obj)
{
    auto cls = se::Class::create("ColorNative", obj, nullptr, _SE(js_Color_constructor));

    cls->defineProperty("r", _SE(js_Color_get_r), _SE(js_Color_set_r));
    cls->defineProperty("g", _SE(js_Color_get_g), _SE(js_Color_set_g));
    cls->defineProperty("b", _SE(js_Color_get_b), _SE(js_Color_set_b));
    cls->defineProperty("a", _SE(js_Color_get_a), _SE(js_Color_set_a));
    cls->defineProperty("dyn", _SE(js_Color_get_dyn), nullptr);
    cls->defineFunction("intValueNative", _SE(js_Color_intValue));


    cls->defineFunction("add2", _SE(js_Color_add2));
    cls->defineFunction("add2Opt", _SE(js_Color_add2));
    cls->defineFunction("add3", _SE(js_Color_add3));
    cls->defineFunction("add4", _SE(js_Color_add4));

    cls->defineFunction("mul1", _SE(js_Color_mul1));
    cls->defineFunction("mul2", _SE(js_Color_mul2));
    cls->defineFunction("mul3", _SE(js_Color_mul3));
    cls->defineFunction("mul4", _SE(js_Color_mul4));

    cls->install();
    JSBClassType::registerClass<Color>(cls);

    __jsb_Color_proto = cls->getProto();
    __jsb_Color_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

bool register_all_color(se::Object* ns)
{
    js_register_Color(ns);
    return true;
}