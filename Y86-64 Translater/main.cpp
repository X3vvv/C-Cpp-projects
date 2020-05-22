/*
Project: 1411 Assignment2
Name: Xavier Pan
ID: 19083967D
*/

#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
using namespace std;

static int reg[10], mem[16], flag[4], row_number = 0; //flag: 0:CF 1:ZF 2:SF 3:OF; row_number: how many rows in the file
static string S[100];
static int labelFlag[100]; //line with a label will has flag = 1;


struct Instruction
{
	//kw   : instruction
	//paraA: rA
	//paraB: rB
	//paraD: D in "D(rB)" (rmmovq/mrmovq)
	string kw = "", paraA = "", paraB = "", paraD = "", label = "";
	bool whether_jump = false;
};


void Read(char* argv)
{
	/*
	This function read file and store line in string list S.
	*/

	string filename = argv;
	ifstream in(filename);

	int i = 0;
	while (getline(in, S[i]))
	{
		i++;
	}

	row_number = i;

	in.close();
}


void Initialize()
{
	/*
	This function initialize register, memory and flags.
	*/

	for (int i = 0; i < 16; i++)
	{
		if (i < 4) flag[i] = 0;
		if (i < 10) reg[i] = 0;
		mem[i] = 0;
	}
}


bool isLegalChar(char c)
{
	/*
	This function decide whether char c is a number or an alphabet.
	Return true is so, else false.
	ASCII(0-9): 48-57
	ASCII(A-Z): 65-90
	ASCII(a-z): 97-122
	ASCII(-):	45
	*/

	if (47 < c && c < 58 || 64 < c && c < 91 || 96 < c && c < 123 || c == 45)
	{
		return true;
	}
	else
	{
		return false;
	}
}


string get_first_word(string& line)
{
	/*
	This function find the first word(string type) seperated by whitespace in line and shorten the line.
	*/

	int start_index = 0;
	int end_index = line.length(); // in case there's no space in the end of line
	bool f = false;

	for (int i = 0; i < line.length(); i++)
	{
		if (!f && isLegalChar(line[i]))
		{
			start_index = i;
			f = true;
		}
		else if (f && !isLegalChar(line[i]))
		{
			end_index = i;
			break;
		}
	}

	string first_word = line.substr(start_index, end_index - start_index);

	//cut off the used part of line
	line = line.substr(end_index);

	return first_word;
}


bool isHalt(int i)
{
	/*
	This function judge whether S[i] is a Hult instruction.
	*/

	//get the first word in S[i]
	string line = S[i]; //prevent S[i] being modified in get_first_word
	string keyword = get_first_word(line);

	//judge whether keyword) is "halt"
	if (keyword == "halt")
	{
		return true;
	}
	else
	{
		return false;
	}
}


Instruction Parse(int i)
{
	/*
	This function parse the instruction and store the keyword and operators.
	Return a Instruction structure.
	*/

	string line = S[i];
	Instruction T;

	//if the line has no number or alphabet, return empty T.
	//	case 1: line has no numeber or alphabet -> f:true, return empty T
	//	case 2: line has number or alphabet     -> f:false
	bool f = true;
	for (int j = 0; j < line.length(); j++)
	{
		if (isLegalChar(line[j]))
		{
			f = false;
		}
	}
	if (f)
	{
		return T;
	}

	//if the line has a label
	if ((int)line.find(":") != -1) //line with label has a colon
	{
		T.label = get_first_word(line);
		labelFlag[i] = 1;
	}

	T.kw = get_first_word(line);

	//Parse the line(by the type of the instruction)
	if (T.kw[0] == 'j') //je jne jg jl
	{
		T.whether_jump = true;
		T.label = get_first_word(line);
	}
	else if (T.kw[0] == 'm' && T.kw[1] == 'r') //mrmovq D(rB), rA
	{
		T.paraD = get_first_word(line);
		T.paraB = get_first_word(line);
		T.paraA = get_first_word(line);
	}
	else if (T.kw[0] == 'r' && T.kw[1] == 'm') //rmmovq rA, D(rB)
	{
		T.paraA = get_first_word(line);
		T.paraD = get_first_word(line);
		T.paraB = get_first_word(line);
	}
	else //rrmovq irmovq(when paraA represent a constant) addq subq cmpq
	{
		T.paraA = get_first_word(line);
		T.paraB = get_first_word(line);
	}
	return T;
}



int ExecuteJump(Instruction T, int i)
{
	/*
	This function get the current line index(i) and an Instruction struct(T) and return the line index to jump to.

	je		jump to Dest if the previous comparison result is rB==rA
	jne		jump to Dest if the previous comparison result is rB!=rA
	jg		jump to Dest if the previous comparison result is rB>rA
	jl		jump to Dest if the previous comparison result is rB<rA
	*/

	//if it doesn't meet the condition to jump(return original i)
	//flag: 0: CF; 1: ZF; 2: SF; 3: OF.
	if (T.kw == "je") //jump if equal
	{
		if (flag[1] == 0) //if not equal  =>  ZF == 0
		{
			return i;
		}
	}
	else if (T.kw == "jne") //jump if not equal
	{
		if (flag[1] != 0) //if equal  =>  ZF != 0
		{
			return i;
		}
	}
	else if (T.kw == "jg") //jump if greater
	{
		if ((!(flag[2] ^ flag[3]) && !flag[1]) == 0) //if not greater  =>  ~(SF^OF)&~ZF == 0
		{
			return i;
		}
	}
	else if (T.kw == "jl") //jump if less
	{
		if ((flag[2] ^ flag[3]) == 0) //if not less  =>  (SF^OF) == 0
		{
			return i;
		}
	}


	//jump to the target line
	string label = "";
	string line = S[i];

	//case1: jump back
	for (int j = 0; j <= i; j++)
	{
		if (labelFlag[j] == 1)
		{
			line = S[j];

			//This way take less time than Parse(i) every time			
			if (get_first_word(line) == T.label)
			{
				return j;
			}
		}
	}

	//case2: jump forward
	int j = i + 1; //j is the line(in the forward)'s index

	while (j < row_number) //Stop loop when find the line or all lines in the file are read.
	{
		if (isLegalChar(line[0]) && get_first_word(line) == T.label) //label is always at the front of the line
		{
			return j;
		}
		j++;
		line = S[j];
	}

	//init flags
	//only jump instruction will use flags, so flags need and only need to be init after an ExcuteJump.
	for (int j = 0; j < 4; j++)
	{
		flag[j] = 0;
	}

	return i; //if no target label is found, return original i.
}


void update_flags(int result)
{
	/*
	This function update all condition codes(CF, ZF, SF, OF).
	*/

	//CF
	//since all input numbers are signed numbers, CF is meaningless here.


	//ZF
	if (result == 0)
	{
		flag[1] = 1;
	}

	//SF
	if (result < 0)
	{
		flag[2] = 1;
	}

	//OF
	if (result > 127 || result < -128)
	{
		flag[3] = 1;
	}
}


void Execute(Instruction T)
{
	/*
	This function excute the instruction in Instruction struct(T).

	Instructions	Oprands						Meaning
		addq		rA, rB		compute rB+rA, then store the result in rB
		subq 		rA, rB		compute rB¨CrA, then store the result in rB
		cmpq		rA, rB		compare rB and rA, then update condition codes
		rrmovq		rA, rB		move rA to rB
		irmovq		V, rB		move the constant V to rB
		rmmovq		rA, D(rB)	move rA to memory (at the address rB+D)
		mrmovq		D(rB), rA	move memory (at the address rB+D) to rA


	*/

	//ASCII(0) = 48
	if (T.kw == "addq")
	{
		int r1 = (int)T.paraA[1] - 48; //index of register rA
		int r2 = (int)T.paraB[1] - 48; //index of register rB

		reg[r2] = reg[r1] + reg[r2];

		update_flags(reg[r2]);
	}
	else if (T.kw == "subq")
	{
		int r1 = (int)T.paraA[1] - 48; //index of register rA
		int r2 = (int)T.paraB[1] - 48; //index of register rB

		reg[r2] = reg[r2] - reg[r1];

		update_flags(reg[r2]);
	}
	else if (T.kw == "cmpq")
	{
		int r1 = (int)T.paraA[1] - 48; //index of register rA
		int r2 = (int)T.paraB[1] - 48; //index of register rB

		update_flags(reg[r2] - reg[r1]);
	}
	else if (T.kw == "rrmovq")
	{
		int r1 = (int)T.paraA[1] - 48; //index of register rA
		int r2 = (int)T.paraB[1] - 48; //index of register rB

		reg[r2] = reg[r1];
	}
	else if (T.kw == "irmovq")
	{

		int v = stoi(T.paraA); //constant V
		int r2 = (int)T.paraB[1] - 48; //index of register rB

		reg[r2] = v;
	}
	else if (T.kw == "rmmovq")
	{
		int r1 = (int)T.paraA[1] - 48; //index of register rA
		int r2 = (int)T.paraB[1] - 48; //index of register rB
		int d = stoi(T.paraD); //constant D
		int addr = reg[r2] + d; //address of destination memory

		mem[addr] = reg[r1];
	}
	else if (T.kw == "mrmovq")
	{
		int r1 = (int)T.paraA[1] - 48; //index of register rA
		int r2 = (int)T.paraB[1] - 48; //index of register rB
		int d = stoi(T.paraD); //constant D
		int addr = reg[r2] + d; //address of destination memory

		reg[r1] = mem[addr];
	}
}


void Output()
{
	cout << "%r0..7:";
	for (int j = 0; j < 8; j++)
	{
		cout << " " << reg[j];
	}

	cout << endl << "M0..15:";
	for (int j = 0; j < 16; j++)
	{
		cout << " " << mem[j];
	}
}


int main(int argc, char** argv)
{
	Read(argv[1]);//S[i] denotes the ith instruction
	Initialize();//Initialize register, memory and flags

	int i = 0;
	Instruction T;
	while (!isHalt(i))
	{
		// if there's no halt at all (line 100 [i=99] could be a jump instruction)
		if (i > 99)
		{
			break;
		}

		T = Parse(i);
		if (T.whether_jump)
		{
			i = ExecuteJump(T, i);
		}
		else
		{
			Execute(T);
			i++;
		}
		
	}
	Output(); // Print results;
}