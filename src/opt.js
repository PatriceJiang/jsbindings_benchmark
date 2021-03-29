var k = 1e+6;
var started = new Date();
while (k--) {
  var result = add(2, 3);
  console.assert(result === 5);
}
var finished = new Date();
console.log('1m adds took', finished - started + 'ms');
// 1m adds took 312ms


function add(a, b){
    return a + b;
}