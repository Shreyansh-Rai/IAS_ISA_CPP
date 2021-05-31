#include <bits/stdc++.h>
#include "IAS.cpp"

using namespace std;
int main()
{
    vector<string> memory(1000);
    memory[0] = "0000000000000000000000000000000000000101";   //Initial value to calculate factorial: 4
    memory[1] = "0000000000000000000000000000000000000001";   //Values of the facotrial will be stored here as they are calculated
    memory[2] = "0000000000000000000000000000000000000001";   //Constant value 1 to be used for subtraction
    memory[10] = "0000000100000000000000000110000000000010";  //LOAD MX[0], SUB M[2]
    memory[11] = "0000111100000000110000000000000000000000";  //JUMP + LEFT(12), BREAK(0000000)
    memory[12] = "0000100100000000000000100001000000000000";  //LOADMQMX M[0] , STOR M[0]
    memory[13] = "0000101100000000000100100001000000000001";  //MUL M[1] , STOR M[1]
    memory[14] = "                    00001101000000001010";  //NULL ,JUMP LEFT M[10]               
    IAS cpu(memory, 10);
    int flag = 0, jump = 0, pc_state;
    string nextins;
    string foribr;
    for(int i = 0; ; i++) {
        cpu.MAR = to_string(cpu.PC);
        cpu.MBR = cpu.memory[cpu.PC];
        pc_state = cpu.PC;
        cout << "PC: " << cpu.PC << endl;
        // cout << "PC : " << cpu.PC << endl; 
        jump = 0;
        if(flag == 0) {
            foribr = cpu.MBR.substr(20,20);
            nextins= cpu.MBR.substr(0,20);
        }
        if(nextins == "                    ") {
            nextins = foribr;
            cpu.IR=nextins.substr(0,8);
            cpu.MAR=nextins.substr(8,12);
            cout<< "IR : " << cpu.IR << ", MAR : " <<cpu.MAR<<endl; 
            if(cpu.IR == "00000001") {
                cpu.LOADMX(Bin_to_Dec(cpu.MAR)); 
                cout << "LOADMX" << endl;
                }
            else if(cpu.IR == "00000110") { 
                cpu.SUBMX(Bin_to_Dec(cpu.MAR));
                cout << "SUBMX" << endl;
                } 
            else if(cpu.IR == "00001111"){
                cpu.JUMP_c_LEFT(12); 
                cout << "JUMP C" << endl;
                flag = 0;
                }
            else if(cpu.IR == "00000000") {
                cout << "BREAK" << endl; //break  
                break;
                }
            else if(cpu.IR == "00001001"){
                cpu.LOADMQMX(Bin_to_Dec(cpu.MAR));
                cout << "LOADMQMX" << endl;
                }
            else if(cpu.IR == "00100001"){
                cpu.STORMX(Bin_to_Dec(cpu.MAR)); 
                cout << "STORMX" << endl;
                }
            else if(cpu.IR == "00001011") {
                cpu.MUL(Bin_to_Dec(cpu.MAR));
                cout << "MUL" << endl;
            }   
            else if(cpu.IR == "00001101" ){
                cpu.JUMP_LEFT(10);
                flag = 0;
                jump = 1;
                cout << "JUMP_LEFT" << endl;
                }
            if(jump == 0)//only increment pc if there was no jump otherwise the PC is changed in the jump statement
                cpu.PC++;//Next instruction because the IBR is always empty for this case
        }
        else {
            cpu.IR = nextins.substr(0,8);
            cpu.MAR = nextins.substr(8,12);
            cout << "IR : " << cpu.IR << ", MAR : " << cpu.MAR << endl;
            if(cpu.IR == "00000001") {
                cpu.LOADMX(Bin_to_Dec(cpu.MAR)); 
                cout << "LOADMX" << endl;
                }
            else if(cpu.IR == "00000110") { 
                cpu.SUBMX(Bin_to_Dec(cpu.MAR));
                cout << "SUBMX" << endl;
                } 
            else if(cpu.IR == "00001111"){
                cpu.JUMP_c_LEFT(12); 
                cout << "JUMP C" << endl;
                if(pc_state != cpu.PC){ //incase the local PC is different from the pc value in the IAS then the jump has occured make jump 1
                    cout << "Jump occured" << endl;
                    jump = 1;
                }
                }//Jump condition
            else if(cpu.IR == "00000000") {
                cout << "BREAK" << endl; //break 
                break;
                }
            else if(cpu.IR == "00001001"){
                cpu.LOADMQMX(Bin_to_Dec(cpu.MAR));
                cout << "LOADMQMX" << endl;
                }
            else if(cpu.IR == "00100001"){
                cpu.STORMX(Bin_to_Dec(cpu.MAR)); 
                cout << "STORMX" << endl;
                }   
            else if(cpu.IR == "00001011") {
                cpu.MUL(Bin_to_Dec(cpu.MAR));
                cout << "MUL" << endl;
            }
            else if(cpu.IR == "00001101" ){
                cpu.JUMP_LEFT(10); 
                flag = 0;
                jump = 1;
                cout << "JUMP_LEFT" << endl;
                }
            if(flag == 0 && jump == 0)//incase there was no jump and there is another instruction in the ibr
            {
                nextins = foribr;
                flag = 1;
            }
            else if(flag == 1 && jump == 0) { //incase the ibr is empty and there is no jump command
                cpu.PC++;
                flag = 0;
            }
        }
        cout << "AC: " << Bin_to_Dec(cpu.AC) << ", MQ: " << Bin_to_Dec(cpu.MQ) << endl; 
        cout << Bin_to_Dec(cpu.memory[0]) << endl;
        cout << Bin_to_Dec(cpu.memory[1]) << endl;
        cout << Bin_to_Dec(cpu.memory[2]) << endl;
        // cout << "Flag: " << flag << endl;
        // cout << Bin_to_Dec(memory[1]) << "    " << Bin_to_Dec(memory[0]) << endl;
    }
    cout<<"FACTORIAL : "<<Bin_to_Dec(cpu.memory[1]) << endl;
    return 0;
}

/*
LOADMX M[0]
SUB M[2]
JUMP_c_LEFT //JUMPS TO FACT LOOP IF NON NEGATIVE VAL OF AC ELSE BREAKS
    //FACT CALC
    LOADMQMX M[0] //MQ = 4
    STOR M[0] //M[0] = 3
    MUL M[1] //AC = MQ*M[1]
    STOR M[1]
    JUMP_LEFT //BACK TO TOP

PC = 10 //starting point

M[0] = 4 // COUNTER
M[1] = 1 // FACTORIAL KEEPS CHANGING
M[2] = 1 // COMPARISION AND SUBTRACTION STAYS CONSTANT
10- LOAD MX[0], SUB M[2]
11- JUMP + LEFT(12), BREAK(0000000)
12- LOADMQMX M[0] , STOR M[0]
13- MUL M[1] , STOR M[1]
14- NULL ,JUMP LEFT M[10]

*/