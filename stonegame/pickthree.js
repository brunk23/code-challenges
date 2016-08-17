var lowest = 3;
var highest = 18;
var stones;
var whoseturn = 0;
var turn = 0;
var p = [];
p[0] = { human: 1,
	 name: "Kevin" };
p[1] = { human: 0,
	 name: "Computer" };

/*
 * A random number between two values inclusive.
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
 * Pick three starting numbers without any duplicates
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

/*
 * This function will display the stone counts.
 */
function displayStones() {
    document.getElementById("box1").innerHTML = '<b>' + stones[0] +
	'</b>';
    document.getElementById("box2").innerHTML = '<b>' + stones[1] +
        '</b>';
    document.getElementById("box3").innerHTML = '<b>' + stones[2] +
        '</b>';
    return 0;
}

/*
 * Button press
 */
function bPress(numb) {
    var x;
    x = document.getElementById("in" + numb).value;
    if( x <= stones[numb] ) {
	stones[numb] -= x;
	displayInfo(numb,x);
	nextTurn();
    }
}

function stoneCount() {
    return (stones[0]+stones[1]+stones[2]);
}

function winner() {
    displayStones();
    displayButtons(p[whoseturn].human);
    document.getElementById("gamesetup").innerHTML = "<h2>" + p[whoseturn].name
	+ " won!</h2>";
}

/*
 * Next Turn
 */
function nextTurn() {
    if ( stoneCount() == 0 ) {
	winner();
    } else {
	turn++;
	whoseturn = (whoseturn + 1) % 2;
	if(p[whoseturn].human == 0) {
	    perfectMove();
	}
	displayButtons();
	displayStones();
	displayPlayer();
    }
}

function displayInfo(n, move) {
    id = "info" + (n+1);
    document.getElementById(id).innerHTML += "<b>Turn " + turn + ": "
	+ p[whoseturn].name + " took " + move + " stones.</b><br>";
}

function displayPlayer() {
    document.getElementById("gamesetup").innerHTML = '<h2>' +
	p[whoseturn].name + "'s Turn</h2>";
}

/*
 *
 */
function displayButtons() {
    if(p[whoseturn].human == 0) {
	// This is a computer, just continue buttons
	document.getElementById("but1").innerHTML = '<button type="button"'
	   + 'onclick="nextTurn()"' + '>CONTINUE</button>';
	document.getElementById("but2").innerHTML = '<button type="button"'
	    + 'onclick="nextTurn()"' + '>CONTINUE</button>';
	document.getElementById("but3").innerHTML = '<button type="button"'
	    + 'onclick="nextTurn()"' + '>CONTINUE</button>';
	return 0;
    }
    if( stones[0] > 0 ) {
	document.getElementById("but1").innerHTML = '<form><input type="number"'
	    + 'min="1" max="' + stones[0] + '" value="1" id="in0">'
	    + '<button type="button"'
	    + 'onclick="bPress(0)"' + '>CONTINUE</button>';
    } else {
	document.getElementById("but1").innerHTML = "";
    }
    if( stones[1] > 0 ) {
	document.getElementById("but2").innerHTML = '<form><input type="number"'
	    + 'min="1" max="' + stones[1] + '" value="1" id="in1">'
	    + '<button type="button"'
	    + 'onclick="bPress(1)"' + '>CONTINUE</button>';
    } else {
	document.getElementById("but2").innerHTML = "";
    }
    if( stones[2] > 0 ) {
	document.getElementById("but3").innerHTML = '<form><input type="number"'
	    + 'min="1" max="' + stones[2] + '" value="1" id="in2">'
	    + '<button type="button"'
	    + 'onclick="bPress(2)"' + '>CONTINUE</button>';
    } else {
	document.getElementById("but3").innerHTML = "";
    }
    return 0;
}

/*
 * COMPUTER PLAYER -- PERFECT
 *
 * This will make the perfect move, if such a move exists.
 * If it can't make a perfect move, it will remove one stone from a
 * random pile.  This is the computer player.
 *
 * We will win the game if stone[0]^stone[1]^stone[2] == 0, so we do
 * our best to make it equal zero at the end of each turn.
 *
 * returns [pile, amount removed]
 */
function perfectMove() {
    var n = 0;
    if( (stones[0] + stones[1] + stones[2]) == 0 ) {
	return [-1,-1];
    }
    if( (stones[0] ^ stones[1] ^ stones[2]) == 0 ) {
	// There is no perfect move
	console.log("I can't move perfectly, so just take one.");
	n = randBetween(0,2);
	while( stones[n] == 0 ) {
	    n = (n+1)%3;
	}
	stones[n]--;
	displayInfo(n, 1);
	return [n, 1];
    }
    for( n = 0; n < 3; ++n ) {
	for( var removed=1; removed <= stones[n]; ++removed ) {
	    var x;
	    if( n == 0 ) {
		x = stones[1] ^ stones[2] ^ (stones[n] - removed);
	    }
	    if( n == 1 ) {
		x = stones[0] ^ stones[2] ^ (stones[n] - removed);
	    }
	    if( n == 2 ) {
		x = stones[1] ^ stones[0] ^ (stones[n] - removed);
	    }
	    if( x == 0 ) {
		stones[n] -= removed;
		displayInfo(n, removed);
		return [n, removed];
	    }
	}
    }
    return [-1, -1];
}

stones = pickthree( lowest, highest );
window.onload = function() {
    whoseturn = randBetween(0,1);
    nextTurn();
}
