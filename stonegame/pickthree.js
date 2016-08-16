var lowest = 3;
var highest = 18;
var stones;

/*
 * A random number between what.
 */
function randBetween(low, high) {
    var a, b;
    if( high > low ) {
	a = low;
	b = high;
    } else {
	a = high;
	b = low;
    }
    return Math.floor( Math.random() * (b - a + 1) + a);
}

/*
 * Pick three starting numbers
 */
function pickthree(low,high) {
    var a = [];
    var found = 0;
    if( high > low ) {
	a[3] = high - low;
    } else {
	a[3] = low - high;
    }
    /*
     * If there aren't enough integers, fail.
     */
    if ( a[3] < 3 ) {
	a[0] = 0;
	a[1] = 0;
	a[2] = 0;
	return a;
    }
    while( found < 3 ) {
	var dup = 0;
	a[found] = randBetween( low, high );
	for( var i = 0; i < found; ++i ) {
	    if( a[i] == a[found] ) {
		dup = 1;
	    }
	}
	if( dup == 1 ) {
	    continue;
	}
	found++;
    }
    return a;
}

function displayStones() {
    document.getElementById("box1").innerHTML = '<b>' + stones[0] +
	'</b>';
    document.getElementById("box2").innerHTML = '<b>' + stones[1] +
        '</b>';
    document.getElementById("box3").innerHTML = '<b>' + stones[2] +
        '</b>';
    return 0;
}

stones = pickthree( lowest, highest );