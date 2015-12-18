// Problem 1
// Write three functions that compute the sum of the numbers
// in a given list using a for-loop, a while-loop, and recursion.

function sumListfor(list) {
    var sum = 0;
    for(var i=0; i<list.length; i++) {
	sum+=list[i];
    }
    return sum;
}

function sumListwhile(list) {
    var sum = 0;
    var i = 0;
    while ( i < list.length) {
	sum+=list[i];
	i++;
    }
    return sum;
}

function sumListrecursion(list, sum) {
    if(sum === undefined ) {
	sum = 0;
    }
    if(list.length > 0) {
	sum=sumListrecursion(list.splice(1),sum+list[0]);
    }
    return sum;
}

// Problem 2

// Write a function that combines two lists by alternatingly
// taking elements. For example: given the two lists [a, b, c]
// and [1, 2, 3], the function should return [a, 1, b, 2, c, 3].

function mixLists(a,b) {
    var maxLength = 0;
    var newArray = [];
    if (a.length > b.length) {
	maxLength = a.length;
    } else {
	maxLength = b.length;
    }
    for(var i = 0; i<maxLength; i++) {
	if(i < a.length) {
	    newArray.push(a[i]);
	}
	if(i < b.length) {
	    newArray.push(b[i]);
	}
    }
    return newArray;
}

// Problem 3
// Write a function that computes the list of the first 100
// Fibonacci numbers. By definition, the first two numbers in
// the Fibonacci sequence are 0 and 1, and each subsequent
// number is the sum of the previous two. As an example, here
//are the first 10 Fibonnaci numbers:
// 0, 1, 1, 2, 3, 5, 8, 13, 21, and 34.

// broken... over maxInt
function fibb() {
    var list = [0,1];
    for( i = 2; i < 100; i++) {
	list[i] = list[i-1] + list[i-2];
    }
    return list;
}

/* Solution in DC that doesn't have same problems
#!/usr/bin/dc
0 sa    # first fibb
1 sb    # second fibb
100 sc  # counter

[lad n  # load a leave copy on stack and print
[
]n
lbdsa   # load b, store in a leave copy on stack
+sb     # add a+b and store in b
lc1-dsc # decrement counter
0<x     # loop if larger than 0
]dsxx   # start program
*/

// Problem 4
// Write a function that given a list of non negative integers, arranges them such that they form the largest possible number. For example, given [50, 2, 1, 9], the largest formed number is 95021.

function largestNumber(list) {
    var weights = [];
    var sorted = [];
    var newnumber = "";
    for(var i = 0; i < list.length; i++) {
	weights[i]=list[i];
	while(weights[i]>=10) {
	    weights[i] /= 10;
	}
    }
    sorted = weights.slice(0);
    sorted = sorted.reverse(sorted.sort());
    for(i=0; i<sorted.length; i++) {
	newnumber += list.splice(weights.indexOf(sorted[i]),1).toString();
    }
    return newnumber;
}

function betterLargest(list) {
    var compare = [];
    for(var i = 0; i<list.length; i++) {
	
    }
}


// Problem 5

// Write a program that outputs all possibilities to put + or - or nothing between the numbers 1, 2, ..., 9 (in this order) such that the result is always 100. For example: 1 + 2 + 34 – 5 + 67 – 8 + 9 = 100.
