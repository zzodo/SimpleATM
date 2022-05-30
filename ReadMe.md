# SimpleATM Example in C++

## Problem Statement
Write code for a simple ATM. It doesn't need any UI (either graphical or console), but a controller should be implemented and tested.  

### Requirements
At least the following flow should be implemented:
```
Insert Card => PIN number => Select Account => See Balance/Deposit/Withdraw
```
For simplification, there are only 1 dollar bills in this world, no cents. Thus account balance can be represented in integer.  

Your code doesn't need to integrate with a real bank system, but keep in mind that we may want to integrate it with a real bank system in the future. 

It doesn't have to integrate with a real cash bin in the ATM, but keep in mind that we'd want to integrate with that in the future.  
And even if we integrate it with them, we'd like to test our code.  

Implementing bank integration and ATM hardware like cash bin and card reader is not a scope of this task,
but testing the controller part (not including bank system, cash bin etc) is within the scope.  

A bank API wouldn't give the ATM the PIN number, but it can tell you if the PIN number is correct or not.  

Based on your work, another engineer should be able to implement the user interface.  
You don't need to implement any REST API, RPC, network communication etc, but just functions/classes/methods, etc.

You can simplify some complex real world problems if you think it's not worth illustrating in the project.


### How to submit
Please upload the code for this project to GitHub or anywhere, and post a link to your repository below.  
Please attach the instruction to clone your project, build and run tests in README.md file in the root directory of the repository.

---

## Building SimpleATM Example

### Tested Environment
This software is developed and tested in Ubuntu 18.04 LTS with gcc(ver 7.5.0) and CMake(ver 7.5.0).

### Build SimpleATM Example
Clone this repository
```
git clone https://github.com/zzodo/SimpleATM.git
```
You can build the library object file and executable software by using CMake
```
cd SimpleATM
mkdir build && cd build
cmake ..
make
```
Then `libSimpleATM.so` and `SimpleATM_example` are generated, and you can test SimpleATM controller by executing the example.
```
./SimpleATM_example
```

## Testing SimpleATM Example
### Quick Explanation
__Files & Directories__
- __include__: a directory that includes header files (.h) for designed classes.
- __src__: a directory that includes cpp files for designed classes and its member functions.
- __CMakeLists.txt__: CMake file to build the software.
- __example.cpp__: a cpp file to generate SimpleATM_example executable.

__Classes__
- __Account__: contains `bank name`, `user name`, `account number` and `balance`.
- __Card__: contains  `bank name`, `user name`, `card number` and `expiration date`.
- __Bank__: has information about `accounts`, `cards (with pin)` and `card-to-account connection`.
- __Atm__: includes the implemented SimpleATM controller.

### Example Dataset and Test Cases
The built `SimpleATM_example` provides a quick example dataset regarding information about accounts, cards and bank systems.  
The example dataset is given as below:

|Bank|User|Card|PIN|Account|
|-|------|----------------|------|----------|
|A|Thomas|0000111122223333|123456|1111111111|
|A|Lewis|0000111122224444|111111|2222222222|
|A|Lewis|0000111122224444|111111|3333333333|
|A|David|0000111122225555|102030|4444444444|
|A|David|0000111122226666|102030|4444444444|
|A|John|0000111133336666|246800|5555555555|
|B|John|0000111144446666|246800|6666666666|

If you look at the dataset details, you may notice that the test can be conducted all the cases listed below:
- __Case 1__: single card + single account (Thomas)
- __Case 2__: single card + multiple accounts (Lewis)
- __Case 3__: multiple cards + single account (David)
- __Case 4__: single card + single account in different bank systems (John)

Hope you enjoy!
