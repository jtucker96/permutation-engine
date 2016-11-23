#include <iostream>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <random>
#include <iostream>
#include <list>
#include <sstream>

using namespace std;

	const  string g_szTemplatePath =			"C:\\PermutativeAssembler\\PermutativeAssembler\\Template\\";		// C:\Permutative assembler\PermutativeAssembler\Template
	const  string g_szOpcodePath =				"C:\\PermutativeAssembler\\PermutativeAssembler\\Block algorithms\\Trash\\Ops\\";

	// ------------------------------------------------------------------------------------------
	//								ALL STRUCTURES
	//-------------------------------------------------------------------------------------------

struct TEXTFILENAMES
{
	string g_aszTextFiles[5]; // 0 : data.txt, 1 : Entry.txt, 2 : Header.txt, 3 : Import.txt, 4 : Include.txt, 5 : Text.txt
	TEXTFILENAMES() 
	{
		g_aszTextFiles[0] = g_szTemplatePath;
		g_aszTextFiles[0] += "Header.txt"; 
		g_aszTextFiles[1] = g_szTemplatePath;
		g_aszTextFiles[1] += "Include.txt"; 
		g_aszTextFiles[2] = g_szTemplatePath;
		g_aszTextFiles[2] += "Entry.txt"; 
		g_aszTextFiles[3] = g_szTemplatePath;
		g_aszTextFiles[3] += "Data.txt"; 
		g_aszTextFiles[4] = g_szTemplatePath;
		g_aszTextFiles[4] += "Text.txt"; 
		g_aszTextFiles[5] = g_szTemplatePath;
		g_aszTextFiles[5] += "Import.txt"; 
	}
};

struct EXTRACTDECRYPT
{
	bool m_bExtractPath;
	bool m_bExtractData;
	bool m_bDecryptData;
	bool m_bDecryptPath;
	bool m_bCompleted;
};


struct REG_INTERNAL
{
	unsigned int						m_uiNumberOfRegistersUsed;  // number of registers in the used register vector
	string								m_szRegister;			// Two possible registers generated from output
	//unsigned int						m_uiRegisterIndex;		// identifies bits of which register was used last
	unsigned int						m_uiSecondaryRegisterIndex;		// Secondary index, used as compareson, and shows what register was generated last!
};

struct INSTRUCTIONSCOMPLETED
{
	EXTRACTDECRYPT m_stExtractDecrypt;
};

struct OPERANDACCESSLEVELS
{
	unsigned int m_uiNumberOfOperands;
	unsigned int m_uiOperand[3];
};

	// ------------------------------------------------------------------------------------------
	//								ALL CLASSES
	//-------------------------------------------------------------------------------------------

/*
class GLOBALVARIABLESUSED
{
	std::vector <std::string>			m_vszGlobalVariablesUsed;			// the strings of global variables in output program 
	std::vector <std::string>::iterator m_vszGlobalVariablesUsedIterator;	// the iterator
	std::vector <bool>					m_vbGlobalVariablesAvaliable;		// parallel vector to the global variable vector
	std::vector <bool>::iterator		m_vbGlobalVariablesAvaliableIterator;// indicating the variables which are
																			// and are not currently in use by main
	unsigned int						m_uiGlobalVariablesCount;		// program!

	GLOBALVARIABLESUSED::GLOBALVARIABLESUSED(unsigned int m_uiCount);	// each string offset is hardcoded
	// v
};
*/

class BASEBLOCK
{
public:
	vector <string> m_vszBuffer;
};

class BLOCKOBJ: public BASEBLOCK
{
public:
	BLOCKOBJ::BLOCKOBJ(string m_lpBufferArg);  // Constructor, set buffer internally
	//vector <string> m_vszBuffer;
									   // all inherited classes have access to this classes protected parameters
	bool		 m_bCompleted;						   // Has this block been completed?
	bool	     m_bJunkSwitch;						   // Temporary switch generated from random generator
	unsigned int m_uiJunkRounds;			   // How many rounds of junk have been added to this block?
};

class AVALIABLEOPERANDS
{
public:
	bool		 m_bAddition;
	bool		 m_bSubtraction;
	bool		 m_bDivision;
	bool		 m_bMultiplication;
};

class THIRTYTWO_BITREG
{
	public:
	THIRTYTWO_BITREG::THIRTYTWO_BITREG();
	string		 m_szRegArray[6];
};
class SIXTEEN_BITREG
{
	public:
	SIXTEEN_BITREG::SIXTEEN_BITREG();
	string		 m_szRegArray[6];
};
class EIGHT_BITREG
{
	public:
	EIGHT_BITREG::EIGHT_BITREG();
	string		 m_szRegArray[8];
};

class AVALIABLEREG	// global struct of the registers avaliable to use safely by the junk generator
{					// currently only in 32-bit mode (may expand)
					// initially true unless altered
public:
	unsigned int EAX; // can only be 0, 1, or 2
	unsigned int EBX; // 2 = Avaliable
	unsigned int ECX; // 1 = In use by JUNK, so it ok to use lower two 8 bit segments
	unsigned int EDX; // 0 = In use by PROGRAM - DO NOT USE
	bool		 ESI;
	bool		 EDI;
	
	unsigned int AX;
	unsigned int BX;
	unsigned int CX;
	unsigned int DX;
	unsigned int SI;
	unsigned int DI;

	bool		 AH;
	bool		 AL;
	bool		 BH;
	bool		 BL;
	bool		 CH;
	bool		 CL;
	bool		 DH;
	bool		 DL;
	
	AVALIABLEREG::AVALIABLEREG();
};

class LABEL
{
public:
	string m_szLabel;
	bool m_bJMP;
	bool m_bProc; // called through stdcall
};

class TRASHOBJ : public BASEBLOCK
{	// can be partially filled out, then put into global list
public:	// contains trash buffer as well!
	AVALIABLEREG	m_stAvaliableReg;
	LABEL			m_stLabel;
	unsigned int	m_uiDwordsToReserveForStack;// used to setup local stack frame!
	vector<string>	m_vszLabelsCalled;	// the calls that this trashobj makes via stdcall
	bool			m_bMakesStdcall;
};	// m_vszLabelsCalled is the main thing that needs to be fixed up


class VARIABLE
{
public:
	bool		 m_bVariableInUse;	// is the variable critical / in use by the actual program?
	bool		 m_bJunkVariable;	// is the variable a junk variable, or must we check it everytime it is access
	unsigned int m_uiTypeVariable;	// 0 = byte, 1 = word, 2 = dword, 
	string		 m_szVariableName;	// the name of the variable
	string		 m_szVariableDeclaration;	// formatted string of how the variable is declared
};

class API_CALL
{
public:
	unsigned int m_uiOperandsRequired;

};

class OPERAND_INTERNAL
{
public:
	unsigned int					    m_uiNumberOfOperands;
	unsigned int						m_uiTypeOfOperandGenerated;		// 0 - 8bit, 1 - 16 bit, 2 - 32bit

	unsigned int *						m_uiOperandArray;
	bool								m_bCanUseDifferentSizeReg;	// can this operation use different sized registers?
	bool								m_bCanUseSameRegister;		// can this op use the same register? ie mov ebx, ebx
	bool								m_bDereference[2];				// a flag for memory, whether we should add square brackets to argument!
	bool								m_bCannotBeTwoMemory;	// there cannot be two memory operands
	bool								m_bMemoryGenerated;		
	bool								m_bIsDereferenceSet;
	bool								m_bRegisterGenerated;		// set if first operand is memory/reg
	bool								m_bOutOfRange;	// if we use two mem of dw db will there be error?

	OPERAND_INTERNAL::OPERAND_INTERNAL(OPERANDACCESSLEVELS*);
	OPERAND_INTERNAL::~OPERAND_INTERNAL();
};

			/*	List for m_uiOperandArray for set values
			0 = REG only (memory address) eg eax
			1 = MEM only (dereferenced) eg [m_hello]
			2 = MEM only (memory address)  m_hello
			3 = REG 8-bit only
			4 = REG 16-bit only
			5 = REG 32-but only
			6 = REG/MEM
			7 = 16bit or higher
			*/

	// ------------------------------------------------------------------------------------------
	//								All GLOBAL VARIABLES
	//-----------------------------------------------------------------------------------------------

	extern std::list<TRASHOBJ>					g_lsGlobalTrashProcedure;
	extern std::list<TRASHOBJ>::iterator		g_lsGlobalTrashProcedureIterator;
	extern std::list<TRASHOBJ>					g_lsGlobalTrashJMP;
	extern std::list<TRASHOBJ>::iterator		g_lsGlobalTrashJMPIterator;
    extern std::list<TRASHOBJ>					g_lsGlobalTrashDirectInsert;
    extern std::list<TRASHOBJ>::iterator		g_lsGlobalTrashDirectInsertIterator;

	extern std::list<API_CALL>					g_lsGlobalAPICall;
	extern std::list<API_CALL>::iterator		g_lsGlobalAPICallIterator;

	extern std::list<VARIABLE>					g_lsGlobalVariable;
	extern std::list<VARIABLE>::iterator		g_lsGlobalVariableIterator;

	extern std::vector<string>					g_vszActualCode;
	extern std::vector <string>					g_vszGeneratedLabels;		// labels generated previously by program, used as a check
	extern std::vector <string>					g_vszGlobalTrashJMPLabels;	// where code can randomly jump - fucking powerful feature

	extern bool									g_bShouldJMP;				// should the code jmp to a random label
	extern unsigned int							g_uiLevelsIntoTrash;		// how many "levels" from actual code, how many procedures in are we? 
	extern BLOCKOBJ								m_sectionArray[5];			// The FASM total file section array
	extern BLOCKOBJ								m_opcodeArray[8];
	extern AVALIABLEREG							m_stAvaliableReg;			// Registers avaliable

	extern EIGHT_BITREG							m_stEightBitReg;
	extern SIXTEEN_BITREG						m_stSixteenBitReg;
	extern THIRTYTWO_BITREG						m_stThirtytwoBitReg;


	extern unsigned int							g_uiTotalTrashObjs;			// Generated at start of program, how many trash objs to create
	extern unsigned int							g_uiTotalTrashProcObjs;		// how many of each?
	extern unsigned int							g_uiTotalTrashDirectInsertObjs;	
	extern unsigned int							g_uiTotalTrashJMPObjs;
	extern unsigned int							g_uiTotalAPICalls;

	extern unsigned int							g_uiDwordsTillStackCorrupts;

	extern unsigned int							g_uiGeneratedOpcodeIndex[2];


	extern unsigned int							g_uiGlobalRegisterFailCount;



	// ------------------------------------------------------------------------------------------
	//								ALL FUNCTIONS
	//-------------------------------------------------------------------------------------------

	void										WriteFile();
	extern string								GenerateRegister(REG_INTERNAL*, unsigned int m_uiRegType, bool m_bCanUseSameRegister,OPERAND_INTERNAL * m_stOperandInternal);			// Generates a register which is not currently in use to be used
	extern string								GenerateLabel(unsigned int Len);	// Generates a random label for use in either jumps or procedures
	extern inline unsigned int					GenerateRandom(unsigned int Min, unsigned int Max);	// generates a random number
	extern void									AllocateVectorList();				// done once in program, loads opcodes
	extern inline string						GenerateOpcode(bool m_bFromProc);					// Generates opcodes
	extern void									ProcessTrash();
	extern string								LookUpTable(string m_szOpcode);	// Function sole purpose is to generate A VALID line from input (mainly in junkcode generation)
	extern inline string						DereferenceOperand(string m_szOperand,OPERAND_INTERNAL * m_stOperandInternal, bool m_bFromStdcall);
	string										GenerateLine(string m_szOpcode, OPERAND_INTERNAL*, REG_INTERNAL *);
	void										RepeatReg(REG_INTERNAL * m_stRegBits, unsigned int m_uiRegType);
	extern void									InitiateVariableList();
	extern string								GenerateVariable();
	extern string								CreateLabel();
	extern string								GenerateMemory(OPERAND_INTERNAL * m_stOperandInternal, unsigned int m_uiOperandIndex, bool m_bDereferenceMem, bool m_bFromStdcall);

	extern void									JMPStdcall();
	extern string								FormattedStdcall(OPERAND_INTERNAL * m_stOperandInternal, REG_INTERNAL * m_stRegInternal,TRASHOBJ *,  bool m_bFromProc);
	extern void									GenerateAllProcedures(unsigned int m_uiNumberOfProcedures);