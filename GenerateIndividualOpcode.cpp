#include "resource.h"

// selects which opcode we should use from list
/*
0  - m_opcodeAdding;
1  - m_opcodeBitShift;
2  - m_opcodeConversionArithmetic;
3  - m_opcodeBitwiseLogical;
4  - m_opcodeConditionalJumps;
5  - m_opcodeConversion;
6  - m_opcodeDivision;
7  - m_opcodeLogical;
8  - m_opcodeMultiplying;
9  - m_opcodeRotate;
10 - m_opcodeSubtracting;
11 - m_opcodeTransfer;
*/

std::list<std::vector<std::string>>		    g_lsGlobalOpcodeList;

unsigned int						m_uiNumberOfVectorsInList = 0;

extern void AllocateVectorList()
{
    for (unsigned int i = 0; i < 8; i++)
    {
        g_lsGlobalOpcodeList.push_back(m_opcodeArray[i].m_vszBuffer);
        m_uiNumberOfVectorsInList++;
    }
}

extern inline string GenerateOpcode(bool m_bCreateProc)	// are we coming from proc initializer? Then we should avoid popad
{
redo:
    std::list<vector<string>>::iterator m_lsLocalFileIterator = g_lsGlobalOpcodeList.begin();
    unsigned int m_uiOpcodeFirstIndex;
    unsigned int m_uiOpcodeSecondaryIndex;
    m_uiOpcodeFirstIndex = GenerateRandom(0,m_uiNumberOfVectorsInList-1);	
	string m_szOpcode;
	std::advance(m_lsLocalFileIterator,m_uiOpcodeFirstIndex);								// maybe std::list wasn't the best idea?
	m_uiOpcodeSecondaryIndex = GenerateRandom(0,(m_lsLocalFileIterator->size()  -1));
	m_szOpcode = m_lsLocalFileIterator->at(m_uiOpcodeSecondaryIndex);
	g_uiGeneratedOpcodeIndex[0] = m_uiOpcodeFirstIndex;
	g_uiGeneratedOpcodeIndex[1] = m_uiOpcodeSecondaryIndex;

	if (m_bCreateProc)
	{
		if ((m_uiOpcodeFirstIndex == 4 && m_uiOpcodeSecondaryIndex == 1) || (m_uiOpcodeFirstIndex == 5 && m_uiOpcodeSecondaryIndex == 1) || (m_uiOpcodeFirstIndex == 4 && m_uiOpcodeSecondaryIndex == 0))
		{	// we don't want to push/pop shit while in a procedure or our return values may fuck up
			goto redo;
		}
		else if ((m_uiOpcodeFirstIndex == 4 && m_uiOpcodeSecondaryIndex == 2) || (m_uiOpcodeFirstIndex == 4 && m_uiOpcodeSecondaryIndex == 3) || (m_uiOpcodeFirstIndex == 5 && m_uiOpcodeSecondaryIndex == 0))
		{
			goto redo;
		}
	}

    return m_szOpcode;
}

// popa is case 4,1
// pop is case 5,1