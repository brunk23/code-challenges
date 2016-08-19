/*
 * TITLE: Play Stone Game (Nim)
 * AUTHOR: Kevin Brunelle (brunellek _at_ gmail.com)
 * DATE: August 17, 2016
 */

// CONSTANTS
var lowest = 3;
var highest = 15;

// GLOBAL VARIABLES -- BAD FORM
var stones;
var whoseturn;
var turn;
var p;

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
 * This function will handle the button entry.  If the value is not accurate,
 * the program will ignore the input and will not progress to the next turn.
 */
function bPress(numb) {
    var x;
    x = document.getElementById("in" + numb).value;
    x = Math.floor(x);
    if( x <= stones[numb] && x > 0 ) {
	stones[numb] -= x;
	displayInfo(numb,x);
	nextTurn();
    }
}

/*
 * This is used to determine the number of stones remaining. It is useful for checking
 * to make sure the game has not been won.
 */
function stoneCount() {
    return (stones[0]+stones[1]+stones[2]);
}

/*
 * If the game has been won, display the name of the winning player.
 */
function winner() {
    document.getElementById("but1").innerHTML = '<button type="button"'
	+ 'onclick="newGame()"' + '>NEW GAME</button>';
    document.getElementById("but2").innerHTML = '<button type="button"'
	+ 'onclick="newGame()"' + '>NEW GAME</button>';
    document.getElementById("but3").innerHTML = '<button type="button"'
	+ 'onclick="newGame()"' + '>NEW GAME</button>';
    displayStones();
    document.getElementById("gamesetup").innerHTML = "<h2>" + p[whoseturn].name
	+ " won!</h2>";
}

/*
 * This function handles the next turn for both players. It will increment the turn
 * count, check to see if we have a winner, change the player, and update the display.
 * When it is the computer's turn, it will call the function to make the computer play.
 */
function nextTurn() {
    if ( stoneCount() == 0 ) {
	winner();
    } else {
	turn++;
	whoseturn = (whoseturn + 1) % 2;
	if(p[whoseturn].human == 0) {
	    displayStones();
	    perfectMove();
	} else {
	    displayStones();
	}
	displayButtons();
	displayPlayer();
    }
}

/*
 * We want to be able to see which player took which stones last.  We keep
 * a running log of turns.  It might be best to start the information log
 * with the number of stones each pile contained.
 */
function displayInfo(n, move) {
    id = "info" + (n+1);
    document.getElementById(id).innerHTML += "<b>Turn " + turn + ": "
	+ p[whoseturn].name + " took " + move + " stones.</b><br>";
}

/*
 * This is just a function that will show whose turn it is.
 */
function displayPlayer() {
    document.getElementById("gamesetup").innerHTML = '<h1>' +
	p[whoseturn].name + "'s Turn</h1>";
}

/*
 * We want buttons to continue, but we need different ones for the player
 * and he computer.  This function handles that.
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
    if( stoneCount() == 0 ) {
	return [-1,-1];
    }
    if( score(stones[0], stones[1], stones[2]) == 0 ) {
	// There is no perfect move, instead of just removing one stone
	// we remove a random number up to half the pile
	console.log("I can't move perfectly, so just take random.");
	var amount;
	n = randBetween(0,2);
	while( stones[n] == 0 ) {
	    n = (n + 1) % 3;
	}
	if(stones[n] > 1) {
	    amount = randBetween(1, Math.floor( stones[n]/2 ) );
	    stones[n] -= amount;
	} else {
	    amount = 1;
	    stones[n]--;
	}
	displayInfo(n, amount);
	return [n, amount];
    }
    // The following finds the best move. I feel like there is a more
    // optimal way than this brute force method.
    for( n = 0; n < 3; ++n ) {
    	var w = (n + 1) % 3;
    	var z = (n + 2) % 3;
	for( var removed=1; removed <= stones[n]; ++removed ) {
	    if( 0 == score(stones[n]-removed, stones[w], stones[z]) ) {
		stones[n] -= removed;
		displayInfo(n, removed);
		return [n, removed];
	    }
	}
    }
    // There was an optimal move but we did not find it! Error!!!
    return [-1, -1];
}

/*
 * This produces a score for a scenario of piles, it helps
 * the computer make its move. 
 */
function score(a, b, c) {
    return (a ^ b ^ c);
}

/*
 * This will reset the game.
 */
function newGame() {
    p = [];
    p[0] = { human: 1,
	     name: "Student" };
    p[1] = { human: 0,
	     name: "Teacher" };
    stones = pickthree( lowest, highest );
    whoseturn = randBetween(0,1);
    turn = 0;
    document.getElementById("info1").innerHTML += "<b>Start Amount: "
	+ stones[0] + "</b><br>";
    document.getElementById("info2").innerHTML += "<b>Start Amount: "
	+ stones[1] + "</b><br>";
    document.getElementById("info3").innerHTML += "<b>Start Amount: "
	+ stones[2] + "</b><br>";
    nextTurn();
}

/*
 * Initialize and run the game.
 */
window.onload = function() {
    newGame();
}
