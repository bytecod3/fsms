#include <iostream>
#include <typeinfo>

enum class states{
	state_0 = 0,
	state_1,
	state_2
};

void runState0();
void runState1();
void runState2();

void runState0(){
  printf(" running state 0: \n");
}

void runState1(){
  printf(" running state 1: \n");
}

void runState2(){
  printf(" running state 2: \n");
}

typedef void(*stateFunction)();

// function pointers
constexpr stateFunction state_functions[]{
	runState0,
	runState1,
	runState2,
	nullptr
};

int main(){
	
	states my_state = states::state_1;
	
	//std::cout<<typeid(my_state).name()<<std::endl;
	
	state_functions[(int)my_state]();
	
	
	//printf("Current state: %d\n", my_state);
	//printf("returned state: %d\n", ret);
	
	return 0;
	
}