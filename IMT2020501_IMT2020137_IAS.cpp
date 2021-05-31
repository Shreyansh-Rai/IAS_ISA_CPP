#include<bits/stdc++.h>
using namespace std;
#define lli long long int

long int Bin_to_Dec(string str) { //converts a binary string to decimal integer
    long int sum = 0, power = 0;
    for(int i = str.length()-1; i >= 0; i--) {
        if(str[i] == '1') sum += pow(2,power);
        power++;
    }
    return sum;
}
class IAS {
    public:
        int flag=0;
        int jump=0;
        vector<string> memory;
        string MAR, MBR, AC, MQ, IBR, IR; //components of an IAS machine
        int PC;
        IAS(vector<string> mem, int P) //constructor for IAS assigns memory and PC passed values
        {
            memory=mem;
            PC=P;
        }
        
        void LOADMQ(int address) //Load ac value to mq
        {
            AC = MQ;
            cout<<AC<<endl;
        }
        void LOADMQMX(int address) //loads value from memory to mq
        {
            MQ=memory[address];
            cout<<"MQ: "<<memory[address]<<endl;
        }
        void LOADMX(int address) // loads value from memory to ac
        {
            AC=memory[address];
            cout<<"AC: "<<AC<<endl;
        }
        void STORMX(int address) //stores value of ac in memory
        {
            memory[address] = AC;
            cout<<"mem: "<<memory[address]<<endl;
        }
        void LOAD_NEG_MX(int address) //loads the negative of memory into AC
        {
            if(memory[address][0] == '0')
            {
                AC = "1" + memory[address].substr(1,memory[address].size());
            }
            else {
                AC = "0" + memory[address].substr(1,memory[address].size());
            }
        }
        void LOAD_ABS_MX(int address) // loads the absolute value of memory into AC
        {
            AC="0" + memory[address].substr(1,memory[address].length());
        }
        void LOAD_NEG_ABS_MX(int address) //loads the absolue negative value from the memory to ac
        {
            AC="1" + memory[address].substr(1,memory[address].length());
        }  
        void JUMP_LEFT(int address) //jumps to the given address 
        {
            PC = address;
            jump=1;
        }
        void JUMP_RIGHT(int address) {
            PC = address;
            jump=1;
        }
        void JUMP_c_LEFT(int address) //jumps to the given address if negative
        {
            if(AC[0] == '0') {
                PC = address;
                jump=1;
            }
            
        
        }
        void JUMP_c_RIGHT(int address) 
        {
            if(AC[0] == '1') {
                PC = address;
                jump=1;
            }
            
        
        }
        void ADDMX(int address) //adds the value of mem to AC 
        {
            int signAC = 1, signMem = 1;
            if(AC[0] == '1') signAC = -1;
            if(memory[address][0] == '1') signMem = -1;
            int ACval = Bin_to_Dec(AC.substr(1,39)) * signAC;
            int Memval = Bin_to_Dec(memory[address].substr(1,39)) * signMem;
            int sum = ACval + Memval;
            if(sum >= 0) {
                AC = "0" + bitset<39>(sum).to_string();   
            }
            else {
                sum *= -1;
                AC = "1" + bitset<39>(sum).to_string();   
            }
            // cout << sum << endl;
            // cout << AC << endl;
        }
        void ADDABSMX(int address) // adds the absolute value of the memory to ac
        {
            int posflagac=1;
            AC[0]==1 ? posflagac=-1 : posflagac=1;
            int acval= Bin_to_Dec(AC.substr(1,39));
            acval=acval*posflagac;
            int memval= Bin_to_Dec(memory[address].substr(1,memory[address].length()));
            acval+=memval;
            if(acval<0)
            AC= "1"+ bitset<39>(acval).to_string();
            else
            AC= "0"+ bitset<39>(acval).to_string();
            // cout << acval << endl;
        }
        void SUBMX(int address) // subtracts memory value from AC
        {
            int signAC = 1, signMem = 1;
            if(AC[0] == '1') signAC = -1;
            if(memory[address][0] == '1') signMem = -1;
            int ACval = Bin_to_Dec(AC.substr(1,39)) * signAC;
            int Memval = Bin_to_Dec(memory[address].substr(1,39)) * signMem;
            int sub = ACval - Memval;
            if(sub >= 0) {
                AC = "0" + bitset<39>(sub).to_string();   
            }
            else {
                sub *= -1;
                AC = "1" + bitset<39>(sub).to_string();   
            }
        }
        void SUBABSMX(int address) // subtracts the absolute value of memory from the AC
        {
            int posflagac=1;
            AC[0]==1 ? posflagac=-1 : posflagac=1;
            int acval= Bin_to_Dec(AC.substr(1,39));
            acval=acval*posflagac;
            int memval= Bin_to_Dec(memory[address].substr(1,memory[address].length()));
            acval-=memval;
            if(acval<0)
            AC= "1"+ bitset<39>(acval).to_string();
            else
            AC= "0"+ bitset<39>(acval).to_string();
        }
        void DIV(int address) // function for dividing. quotient in MQ and AC has the remainder
        {
            int posflagac=1;
            int posflagmx=1;
            AC[0]==1 ? posflagac=-1 : posflagac=1;
            memory[address][0]==1 ? posflagmx=-1 : posflagmx=1;
            int acval= Bin_to_Dec(AC.substr(1,39));
            cout << acval << endl;
            int memval= Bin_to_Dec(memory[address].substr(1,39));
            int mqval=(acval*posflagac)/(memval*posflagmx);
            acval=(acval*posflagac)%(memval*posflagmx);
            if(acval<0)
            AC= "1"+ bitset<39>(acval).to_string();
            else
            AC= "0"+ bitset<39>(acval).to_string();
            if(mqval<0)
            MQ= "1"+ bitset<39>(mqval).to_string();
            else
            MQ= "0"+ bitset<39>(mqval).to_string();
            // cout << mqval << endl;
            // cout << acval << " " << memval << endl;
            // cout << AC << endl;
            // cout << MQ << endl;
        }
        void MUL(int address) //Multiplying 2 values the most significant bits are filled into the AC first and then into the MQ
        {
            int posflagmq=1;
            int posflagmx=1;
            MQ[0]==1 ? posflagmq=-1 : posflagmq=1;
            memory[address][0]==1 ? posflagmx=-1 : posflagmx=1;
            lli mqval= Bin_to_Dec(MQ.substr(1,39));
            lli memval= Bin_to_Dec(memory[address].substr(1,39));
            lli multval=(mqval*posflagmq)*(memval*posflagmx);
            string final;
            if(multval >= 0) {
                final = bitset<79>(multval).to_string();
                int i;
                for(i = 78; i >= 0; i--) {
                    if(final[i] == '1') break;
                }
                if(79-i > 39) {
                    AC = "0" + final.substr(i,39);
                    MQ = final.substr(i+39, 79-i-38);
                }
                else {
                    AC = "0" + final.substr(40, 39);
                    MQ = "0";
                }
                // cout << i << endl;
            }
            else {
                multval *= -1;
                final = bitset<79>(multval).to_string();
                int i;
                for(i = 78; i >= 0; i--) {
                    if(final[i] == '1') break;
                }
                if(79-i > 39) {
                    AC = "1" + final.substr(i,39);
                    MQ = final.substr(i+39,79-i-38);
                }
                else {
                    AC = "1" + final.substr(40, 39);
                    MQ = "0";
                }
                // cout << i << endl;
            }
            // cout << multval << endl;
            // cout << final << endl;
            // cout << AC << endl;
            // cout << MQ << endl;
        } 
        void LSH()//left shifting the AC value by 1
        {
            int posflagac=1;
            AC[0]==1 ? posflagac=-1 : posflagac=1;
            int acval= Bin_to_Dec(AC.substr(1,39));
            acval*=2;
            if(posflagac==1)
            {
                AC="0"+ bitset<39>(acval).to_string();
            }
            else
            {
                AC="1"+ bitset<39>(acval).to_string();
            }
        }
        void RSH()//right shifting the AC value by 1
        {
            int posflagac=1;
            AC[0]==1 ? posflagac=-1 : posflagac=1;
            int acval= Bin_to_Dec(AC.substr(1,39));
            acval/=2;
            if(posflagac==1)
            {
                AC="0"+ bitset<39>(acval).to_string();
            }
            else
            {
                AC="1"+ bitset<39>(acval).to_string();
        }
    }
};

//TEST function for testing the division method.
// int main() {
//     vector<string> vec = {"0000000000000000000000000000000001000000","0000000000000000000000000000000000010000"};
//     IAS cpu(vec, 1);
//     // cpu.AC = "000000000000000000000000000000000100000";
//     // cpu.MQ = "0000000000000000000000000000000000000010";
//     // cpu.DIV(1);
//     cpu.AC = "000000000000000000000000000000000100000";
//     cpu.MQ = "0100000000000000000000000000000000000000";
//     cpu.MUL(1);
//     // cpu.AC = "000000000000000000000000000000000100000";
//     // cpu.MQ = "0000000000000000000000000000000000000010";
//     // cpu.ADDMX(1);
// }