#include <bits/stdc++.h>
#include "IAS.cpp"

using namespace std;
int main()
{
    vector<string> memory(1000);
    memory[0] = "0000000000000000000000000000000000001000";   //Initial value to calculate sum of natural number 8
    memory[1] = "0000000000000000000000000000000000000001";   //constant for subtraction
    memory[2] = "0000000000000000000000000000000000000000";   //adding the final answer
    memory[10] = "0000000100000000001000000101000000000000";  //LOADMX(2) , ADDMX(0)
    memory[11] = "0010000100000000001000000001000000000000";  //STORMX(2) , LOADMX(0)
    memory[12] = "0000011000000000000100100001000000000000";  //SUBMX(1) , STORMX(0)
    memory[13] = "0000111100000000101000000000000000000000";  //JUMP+LEFT(10),BREAK
    
                      
    IAS cpu(memory, 10);
    
    string nextins;
    int flag = 0, jump = 0, pc_state;
    string foribr;
    for(int i = 0; ; i++) {
        cpu.MAR = to_string(cpu.PC);
        cpu.MBR = cpu.memory[cpu.PC];
        pc_state = cpu.PC;
        cout << "PC: " << cpu.PC << endl;
        // cout << "PC : " << cpu.PC << endl; 
        jump = 0;
        if(flag == 0 || jump==1) {
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
                }//load MX
            else if(cpu.IR == "00000110") { 
                cpu.SUBMX(Bin_to_Dec(cpu.MAR));
                cout << "SUBMX" << endl;
                } //sub MX
            else if(cpu.IR == "00001111"){
                cpu.JUMP_c_LEFT(10); 
                cout << "JUMP C" << endl;
                flag = 0;
                }//Jump conditional left
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
            else if(cpu.IR=="00000101")
            {
                cpu.ADDMX(Bin_to_Dec(cpu.MAR));
                cout<<"ADDMX"<<endl;
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
            if(jump == 0)
                cpu.PC++;//Next instruction because the IBR is always empty for this case
        }
        else {
            cpu.IR = nextins.substr(0,8);
            cpu.MAR = nextins.substr(8,12);
            cout << "IR : " << cpu.IR << ", MAR : " << cpu.MAR << endl;
            if(cpu.IR == "00000001") {
                cpu.LOADMX(Bin_to_Dec(cpu.MAR)); 
                cout << "LOADMX" << endl;
                }//load MX
            else if(cpu.IR == "00000110") { 
                cpu.SUBMX(Bin_to_Dec(cpu.MAR));
                cout << "SUBMX" << endl;
                } //sub MX
            else if(cpu.IR == "00001111"){
                cpu.JUMP_c_LEFT(10); 
                cout << "JUMP C" << endl;
                if(pc_state != cpu.PC){
                    cout << "Jump occured" << endl;
                    jump = 1;
                }
                }//Jump conditional left
            else if(cpu.IR == "00000000") {
                cout << "BREAK" << endl; //break 
                break;
                }
            else if(cpu.IR=="00000101")
            {
                cpu.ADDMX(Bin_to_Dec(cpu.MAR));
                cout<<"ADDMX"<<endl;
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
            if(flag == 0 && jump == 0)
            {
                nextins = foribr;
                flag = 1;
            }
            else if(flag == 1 && jump == 0) {
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
    cout<<"SUM OF NATURAL NUMBERS : "<<Bin_to_Dec(cpu.memory[2]) << endl;
    return 0;
}

/*
LOADMX(2) , ADDMX(0)
STORMX(2) , LOADMX(0)
SUBMX(1) , STORMX(0)
JUMP+LEFT(10),BREAK
*/