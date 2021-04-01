let LOOP_TIMES = 10000;





const ColorSize = 4;

let ColorAOS = {
    alloc: function (size) {
        let arr =  new Float32Array(size * ColorSize);
        arr.fill(1);
        return arr;
    },

    getR: function (buffer, idx) {
        let offset = ColorSize * idx;
        return buffer[offset];
    },

    getG: function (buffer, idx) {
        let offset = ColorSize * idx;
        return buffer[offset + 1];
    },
    getB: function (buffer, idx) {
        let offset = ColorSize * idx;
        return buffer[offset + 2];
    },
    getA: function (buffer, idx) {
        let offset = ColorSize * idx;
        return buffer[offset + 3];
    },

    setR: function (buffer, idx, value) {
        let offset = ColorSize * idx;
        buffer[offset] = value;
    },

    setG: function (buffer, idx, value) {
        let offset = ColorSize * idx;
        buffer[offset + 1] = value;
    },
    setB: function (buffer, idx, value) {
        let offset = ColorSize * idx;
        buffer[offset + 2] = value;
    },
    setA: function (buffer, idx, value) {
        let offset = ColorSize * idx;
        buffer[offset + 3] = value;
    },
};

function ColorSimple () {
    this.r = this.g = this.b = this.a = 1;
}

const TEST_ELEMENTS = 1024;
let colorAOS = ColorAOS.alloc(TEST_ELEMENTS);
let colorSimple = [];
for (let i = 0; i < 1024; i++) {
    colorSimple.push(new ColorSimple());
}

function loopJS_AOS_sumColor () {
    let s = 0;
    for (let i = 0; i < LOOP_TIMES; i++) {
        for (let j = 0; j < TEST_ELEMENTS; j++) {
            s += (ColorAOS.getR(colorAOS, j) + 
            ColorAOS.getG(colorAOS, j) + 
            ColorAOS.getB(colorAOS, j) + 
            ColorAOS.getA(colorAOS, j));
        }
        s = 0;
    }
    return s;
}
function loopJS_Simple_sumColor () {
    let s = 0, c;
    for (let i = 0; i < LOOP_TIMES; i++) {
        for (let j = 0; j < TEST_ELEMENTS; j++) {
            c = colorSimple[j];
            s += (c.r + c.g + c.b + c.a);
        }
        s = 0;
    }
    return s;
}

function loopJS_AOS_setColor () {
    for (let i = 0; i < LOOP_TIMES; i++) {
        for (let j = 0; j < TEST_ELEMENTS; j++) {
            ColorAOS.setR(colorAOS, j, 255);
            ColorAOS.setG(colorAOS, j, 0);
            ColorAOS.setB(colorAOS, j, 0);
            ColorAOS.setA(colorAOS, j, 255);
        }
    }
}
function loopJS_Simple_setColor () {
    let c; 
    for (let i = 0; i < LOOP_TIMES; i++) {
        for (let j = 0; j < TEST_ELEMENTS; j++) {
            c = colorSimple[j];
            c.r = 255;
            c.g = 0;
            c.b = 0;
            c.a = 255;
        }
    }
}


/////////////////////node indirection 2///////////////
const NODE_SIZE = 10;
const NODE_COLOR_OFFSET = 2;
let  NodeAOS =  {
    alloc: function(size) {
        return new Float32Array(size * NODE_SIZE);
    },
    getColorID: function(buffer, idx) {
        return buffer[idx * NODE_SIZE + NODE_COLOR_OFFSET];
    },
    setColorID: function(buffer, idx, colorId) {
        buffer[idx *NODE_SIZE + NODE_COLOR_OFFSET] = colorId;
    }
};

function NodeSimple() {
    this.color = null;
}

let nodeAOS = NodeAOS.alloc(TEST_ELEMENTS);
for(let i = 0; i < TEST_ELEMENTS; i++) { 
    NodeAOS.setColorID(nodeAOS, i, i);
}
let nodeSimple = [];
for(let i = 0; i < TEST_ELEMENTS; i++){ 
    let n = new NodeSimple();
    n.color = colorSimple[i];
    nodeSimple.push(n);
}


function loopJS_Indirect_AOS_sumColor () {
    let s = 0, colorID;
    for (let i = 0; i < LOOP_TIMES; i++) {
        for (let nodeId = 0; nodeId < TEST_ELEMENTS; nodeId++) {
            colorID = NodeAOS.getColorID(nodeAOS, nodeId);
            s += (ColorAOS.getR(colorAOS, colorID) + 
            ColorAOS.getG(colorAOS, colorID) + 
            ColorAOS.getB(colorAOS, colorID) + 
            ColorAOS.getA(colorAOS, colorID));
        }
        s = 0;
    }
    return s;
}

function loopJS_Indirect_Simple_sumColor () {
    let s = 0, c;
    for (let i = 0; i < LOOP_TIMES; i++) {
        for (let nodeId = 0; nodeId < TEST_ELEMENTS; nodeId++) {
            c = nodeSimple[nodeId].color;
            s += (c.r + c.g + c.b + c.a);
        }
        s = 0;
    }
    return s;
}

/////////////////////scene indirection 2///////////////


let  ArrayAOS = {
    alloc: function(size) {
        let r =  new Array(size);
        for(let i =0;i < size;i++) {
            r[i] = [];
        }
        return r;
    }
};

function roll(arr, min, max, cntFrom, cntTo) {
    let cnt = Math.floor(Math.random() * (cntTo - cntFrom) + cntFrom);
    for(let i = 0;i < cnt; i++) {
        let v = Math.floor(Math.random() * (max - min) + min);
        while(arr.indexOf(v) !== -1) {
            v = Math.floor(Math.random() * (max - min) + min);
        }
        arr.push(v);
    }
}
let arrayAOS = ArrayAOS.alloc(TEST_ELEMENTS);
const SCENE_SIZE = 20;
const SCENE_NODE_OFFSET = 8;
function SceneAOS() {
    this.childrenID = -1;
}

let sceneAOS = [];
for(let i = 0; i < TEST_ELEMENTS; i++) {
    sceneAOS[i] =new SceneAOS;
    sceneAOS[i].childrenID = i;
    roll(arrayAOS[i], 0, TEST_ELEMENTS, 2, 20);
}

function SceneSimple() {
    this.children = [];
}
let sceneSimple = []; 
for(let i = 0; i < TEST_ELEMENTS; i++) {
    sceneSimple[i] =  new SceneSimple;
    let s = sceneSimple[i];
    let idxArray = arrayAOS[i];
    for(let j = 0; j < idxArray.length; j++) {
        s.children.push(nodeSimple[j]);
    }
}

function loopJS_Indirect_AOS_Scene_sumColor () {
    let s = 0, scene;
    for (let i = 0; i < LOOP_TIMES; i++) {
        for (let sceneId = 0; sceneId < TEST_ELEMENTS; sceneId++) {
            scene = sceneAOS[sceneId];
            let nodeIdx = arrayAOS[scene.childrenID];
            for(let nodeId of nodeIdx) {
                colorID = NodeAOS.getColorID(nodeAOS, nodeId);
                s += (ColorAOS.getR(colorAOS, colorID) + 
                ColorAOS.getG(colorAOS, colorID) + 
                ColorAOS.getB(colorAOS, colorID) + 
                ColorAOS.getA(colorAOS, colorID));
            }
        }
    }
    return s;
}

function loopJS_Indirect_Simple_Scene_sumColor () {
  let s = 0, scene;
  for (let i = 0; i < LOOP_TIMES; i++) {
      for (let sceneId = 0; sceneId < TEST_ELEMENTS; sceneId++) {
          scene = sceneSimple[sceneId];
          for(let node of scene.children) {
              s += (node.color.r  + node.color.g + node.color.b + node.color.a);
          }
      }
  }
  return s;
}


console.log(loopJS_Indirect_AOS_Scene_sumColor());
console.log(loopJS_Indirect_Simple_Scene_sumColor());