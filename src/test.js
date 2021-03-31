function ColorJS () {
    this._r = this._g = this._b = this._a = 0;
}
Object.defineProperty(ColorJS.prototype, 'r', {
    get: function () { return this._r; }
})
Object.defineProperty(ColorJS.prototype, 'g', {
    get: function () { return this._g; }
})
Object.defineProperty(ColorJS.prototype, 'b', {
    get: function () { return this._b; }
})
Object.defineProperty(ColorJS.prototype, 'a', {
    get: function () { return this._a; }
})

let dynI = 0;
Object.defineProperty(ColorJS.prototype, 'dyn', {
    get: function () { 
        const r = [3,2,0,2][dynI % 4];
        dynI ++;
        if(r == 0) {
            return this._r;
        }else if( r== 1) {
            return this._g + this._r;
        }else if( r== 2){
            return this._b + this._a;
        }else {
            return this._a +  this._g;
        }
    }
})

var cJS = new ColorJS();
cJS._r = cJS._g = cJS._b = 128;
cJS._a = 255;


var c = new ColorNative(128, 128, 128, 255);

ColorNative.prototype.intValueJS = function () {
    return 0x808080FF;
};



function loopJS () {
    for (let i = 0; i < LOOP_TIMES; i++) {
        c.intValueJS();
    }
}
function loopCPP () {
    for (let i = 0; i < LOOP_TIMES; i++) { c.intValueNative(); }
}
function testFn () {
    return c.intValueNative();
}
function loopJSAttr() {
    let s = 0;
    for (let i = 0; i < LOOP_TIMES; i++) { s += cJS.r; }
    return s;
}


function loopJSDynAttr () {
    let s = 0;
    for (let i = 0; i < LOOP_TIMES; i++) { s += cJS.dyn; }
    return s;
}

function loopJSBAttr () {
    let s = 0;
    for (let i = 0; i < LOOP_TIMES; i++) { s += c.g; }
    return s;
}

function loopJSBDynAttr() {
    let s = 0;
    for (let i = 0; i < LOOP_TIMES; i++) { s += c.dyn; }
    return s;
}

function loopJSB_call_2_args() {
    let cc = new ColorNative(2,4,5,10);
    let c1 = new ColorNative(2,4,5,10);
    let c2 = new ColorNative(8,4,5,3);
    for (let i = 0; i < LOOP_TIMES; i++) { 
        cc.add2(c1, c2);
    }
    return cc;
}

function loopJSB_call_2_args_opt() {
    let cc = new ColorNative(2,4,5,10);
    let c1 = new ColorNative(2,4,5,10);
    let c2 = new ColorNative(8,4,5,3);
    for (let i = 0; i < LOOP_TIMES; i++) { 
        cc.add2Opt(c1, c2);
    }
    return cc;
}

function loopJSB_call_3_args() {;
    let cc = new ColorNative(2,4,5,10);
    let c1 = new ColorNative(2,4,5,10);
    let c2 = new ColorNative(8,4,5,3);
    let c3 = new ColorNative(8,4,5,3);
    for (let i = 0; i < LOOP_TIMES; i++) { 
        cc.add3(c1, c2, c3);
    }
    return cc;
}

function loopJSB_call_4_args() {;
    let cc = new ColorNative(2,4,5,10);
    let c1 = new ColorNative(2,4,5,10);
    let c2 = new ColorNative(8,4,5,3);
    let c3 = new ColorNative(8,4,5,3);
    let c4 = new ColorNative(8,4,50,3);
    for (let i = 0; i < LOOP_TIMES; i++) { 
        cc.add4(c1, c2, c3, c4);
    }
    return cc;
}

function loopJSB_call2_1_args() {;
    let cc = new ColorNative(2,4,5,10);
    for (let i = 0; i < LOOP_TIMES; i++) { 
        cc.mul1(10);
    }
    return cc;
}
function loopJSB_call2_2_args() {;
    let cc = new ColorNative(2,4,5,10);
    for (let i = 0; i < LOOP_TIMES; i++) { 
        cc.mul2(10, 8);
    }
    return cc;
}
function loopJSB_call2_3_args() {;
    let cc = new ColorNative(2,4,5,10);
    for (let i = 0; i < LOOP_TIMES; i++) { 
        cc.mul3(3, 9, 3);
    }
    return cc;
}

function loopJSB_call2_4_args() {;
    let cc = new ColorNative(2,4,5,10);
    for (let i = 0; i < LOOP_TIMES; i++) { 
        cc.mul4(3, 9, 3, 3);
    }
    return cc;
}