#include<iostream>
#include<string>

using std::string;
using std::getline;
using std::cout;
using std::cin;
using std::endl;

int object_value(const char *n, int &);
int array_value(const char *n, int &);
int number_value(const char *n, int &x);

int main()
{
	int count = 0;
	string input;

	while( getline(cin, input) ) {
		for( int x = 0; input[x] != '\0'; ++x ) {
			if(input[x] == '{' ) {
				count += object_value(input.c_str(), x);
			}
			if(input[x] == '[' ) {
				count += array_value(input.c_str(), x);
			}
			if( (input[x] >= '0' && input[x] <= '9')
				|| input[x] == '-' ) {
				count += number_value(input.c_str(), x);	
			}
		}
		// cout << "The total this string was: " << count << endl;
	}
	cout << "The total was: " << count << endl;
	return 0;
}

/*
 * Return the value of a digit string
 */
int number_value(const char *n, int &x)
{
	int value = 0;
	int digit = 0;
	bool isNeg = false;

	if( n[x] == '-' ) {
		isNeg = true;
		++x;
	}
	for( ; n[x] != '\0'; ++x) {
		if( n[x] >= '0' && n[x] <= '9' ) {
			digit = n[x] - '0';		
			value *= 10;
			if ( isNeg ) {
				value -= digit;
			} else {
				value += digit;
			}
		} else {
			--x;
			break;	// return when not a digit
		}
	}
	return value;
}


/*
 * This will determine the value of objects
 * doesn't check for red (yet)
 */
int object_value(const char *n, int &x)
{
	int value = 0;
	int obj_values = 0;
	int arr_values = 0;
	int notRed = 1;

	++x;
	//	cout << "Decoding object." << endl;

	for(; n[x] != '\0'; ++x) {
		if( n[x] == '}' ) {
			// End of this object
			break;
		}
		if( n[x] == '{' ) {
			// Internal object
			obj_values += object_value( n, x );
			// cout << "Back at: " << x << endl;
		}
		if( n[x] == '[' ) {
			// Internal array
			arr_values += array_value( n, x );
		}	
		if( (n[x] >= '0' && n[x] <= '9') || n[x] == '-' ) {
			value += number_value(n, x);	
		}
		if( n[x] == 'r' ) {
			if(n[x+1] == 'e') {
				if(n[x+2] == 'd') {
					notRed = 0;
				}
			}
		}
	}

	//cout << "Value: " << value << "\nObj_values: "
	//	<< obj_values << "\nArr_values: " << arr_values << endl;

	return notRed*(value + arr_values + obj_values);
}

int array_value(const char *n, int &x)
{
	int value = 0;
	int obj_values = 0;
	int arr_values = 0;

	//	cout << "Decoding array." << endl;
	++x;

	for(; n[x] != '\0'; ++x) {
		if( n[x] == ']' ) {
			// End of this object
			break;
		}
		if( n[x] == '{' ) {
			// Internal object
			obj_values += object_value( n, x );
			//	cout << "Back at: " << x << endl;
		}
		if( n[x] == '[' ) {
			// Internal array
			arr_values += array_value( n, x );
		}	
		if( (n[x] >= '0' && n[x] <= '9') || n[x] == '-' ) {
			value += number_value(n, x);	
		}
	}
	// cout << "Array value: " << value << endl;

	return (value + obj_values + arr_values);
}
