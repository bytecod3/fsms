#include <iostream>

enum class states{
	state_1 = 0,
	state_2,
	state_3
};

int main(){
	
	states my_state = states::state_2;
	
	printf("Current state: %d\n", my_state);
	
	return 0;
	
}