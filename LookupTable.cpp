#include "resource.h"

// Find out which opcode was selected, the class it is under

// http://www.logix.cz/michal/doc/i386/chp02-05.htm
// http://www.penguin.cz/~literakl/intel/intel.html
// http://faydoc.tripod.com/cpu/index_p.htm

extern string LookUpTable(string m_szOpcode)	// is function called to set the reg bits, or as line generator?
{
    // sadly, these values have to be hardcoded
    REG_INTERNAL m_stRegInternal;
    m_stRegInternal.m_uiNumberOfRegistersUsed = 0;
    string m_szFormatted;
    OPERANDACCESSLEVELS m_stOperandAccessLevels;
    /*	List for m_uiOperandArray for set values
    0 = MEM only 8bit
    1 = MEM only 16bit
    2 = MEM only 32bit
    3 = MEM only any size
    4 = MEM only 16 bits or higher

    5 = REG 8-bit only
    6 = REG 16-bit only
    7 = REG 32-bit only
    8 = REG ONLY any size
    9 = REG ONLY 16 bits or higher

    10 = REG/MEM
    11 = small constant value
    12 = REG/MEM/small constant value
    */

    switch (g_uiGeneratedOpcodeIndex[0])
    {
    case 0:	// arithmetic-1
    {
        m_stOperandAccessLevels.m_uiNumberOfOperands = 1;	// only values that need to change
        switch (g_uiGeneratedOpcodeIndex[1])
        {
        case 0:	// div - takes one argument, either a reg/mem
        {
            /*
            m_stOperandAccessLevels.m_uiOperand[0] = 10;			// in case statements

            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
            m_stOperandInternal.m_bCanUseDifferentSizeReg = false;
            m_stOperandInternal.m_bDereference[0] = true;			// we must dereference
            m_szFormatted = GenerateLine(m_szOpcode,&m_stOperandInternal, &m_stRegInternal);
            */
            m_szFormatted = "MOV EAX, 20";
        }
        break;
        case 1: // idiv
        {
            /*
            // signed divide, DIV reg/mem/const
            m_stOperandAccessLevels.m_uiOperand[0] = 10;			// in case statements

            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
            m_stOperandInternal.m_bCanUseDifferentSizeReg = false;
            m_stOperandInternal.m_bDereference[0] = true;			// we must dereference
            m_szFormatted = GenerateLine(m_szOpcode,&m_stOperandInternal, &m_stRegInternal);
            */
            m_szFormatted = "MOV EAX, 20";
        }
        break;
        case 2: // mul [reg/mem]
        {
            // unsigned multiplication
            m_stOperandAccessLevels.m_uiOperand[0] = 10;			// in case statements

            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
            m_stOperandInternal.m_bCanUseDifferentSizeReg = false;
            m_stOperandInternal.m_bDereference[0] = true;			// we must dereference
            m_szFormatted = GenerateLine(m_szOpcode,&m_stOperandInternal, &m_stRegInternal);

        }
        break;
        case 3:	// imul [reg], [reg/mem]
        {
            m_stOperandAccessLevels.m_uiOperand[0] = 8;			// in case statements
            m_stOperandAccessLevels.m_uiOperand[1] = 10;

            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
            m_stOperandInternal.m_bCanUseDifferentSizeReg = false;
            m_stOperandInternal.m_bDereference[0] = true;			// we must dereference
            m_szFormatted = GenerateLine(m_szOpcode,&m_stOperandInternal, &m_stRegInternal);

        }
        break;
        case 4:	// inc
        {
            // however we must dereference!
            m_stOperandAccessLevels.m_uiOperand[0] = 10;			// in case statements

            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
            m_stOperandInternal.m_bCanUseDifferentSizeReg = false;
            m_stOperandInternal.m_bDereference[0] = true;			// we must dereference
            m_szFormatted = GenerateLine(m_szOpcode,&m_stOperandInternal, &m_stRegInternal);

        }
        break;
        case 5:	// dec
        {
            m_stOperandAccessLevels.m_uiOperand[0] = 10;			// in case statements

            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
            m_stOperandInternal.m_bCanUseDifferentSizeReg = false;
            m_stOperandInternal.m_bDereference[0] = true;			// we must dereference
            m_szFormatted = GenerateLine(m_szOpcode,&m_stOperandInternal, &m_stRegInternal);

        }
        break;
        }
        break;
    }
    case 1: // arithmetic-2
    {
        m_stOperandAccessLevels.m_uiNumberOfOperands = 2;	// only values that need to change
        switch (g_uiGeneratedOpcodeIndex[1])
        {
        case 0:	// ADD
        {
            m_stOperandAccessLevels.m_uiOperand[0] = 10;			// in case statements
            m_stOperandAccessLevels.m_uiOperand[1] = 8;

            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
            m_stOperandInternal.m_bCanUseDifferentSizeReg = false;
            m_stOperandInternal.m_bDereference[0] = true;			// we must dereference
            // m_stOperandInternal.m_bDereference[1] = false;
            m_stOperandInternal.m_bCannotBeTwoMemory = true;	// operands cant both be memory

            // if the first operand is dereferenced, then the second MUST NOT be dereferenced

            m_szFormatted = GenerateLine(m_szOpcode,&m_stOperandInternal, &m_stRegInternal);
        }
        break;
        case 1: // ADC
        {
            m_stOperandAccessLevels.m_uiOperand[0] = 10;			// in case statements
            m_stOperandAccessLevels.m_uiOperand[1] = 10;

            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
            m_stOperandInternal.m_bCanUseDifferentSizeReg = false;
            m_stOperandInternal.m_bDereference[0] = true;			// we must dereference
            //m_stOperandInternal.m_bDereference[1] = true;
            m_stOperandInternal.m_bCannotBeTwoMemory = true;	// operands cant both be memory
            m_szFormatted = GenerateLine(m_szOpcode,&m_stOperandInternal, &m_stRegInternal);

        }
        break;
        case 2: // SUB
        {
            m_stOperandAccessLevels.m_uiOperand[0] = 10;			// in case statements
            m_stOperandAccessLevels.m_uiOperand[1] = 10;

            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
            m_stOperandInternal.m_bCanUseDifferentSizeReg = false;
            m_stOperandInternal.m_bDereference[0] = true;			// we must dereference
            m_stOperandInternal.m_bOutOfRange = true;
            // m_stOperandInternal.m_bDereference[1] = true;	for the second argument it is optional


            m_szFormatted = GenerateLine(m_szOpcode,&m_stOperandInternal, &m_stRegInternal);

        }
        break;
        case 3:	// SBB
        {
            m_stOperandAccessLevels.m_uiOperand[0] = 10;			// in case statements
            m_stOperandAccessLevels.m_uiOperand[1] = 10;

            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
            m_stOperandInternal.m_bCanUseDifferentSizeReg = false;
            m_stOperandInternal.m_bDereference[0] = true;			// we must dereference
            m_stOperandInternal.m_bOutOfRange = true;
            m_szFormatted = GenerateLine(m_szOpcode,&m_stOperandInternal, &m_stRegInternal);

        }
        break;
        case 4:	// CMP
        {
            m_stOperandAccessLevels.m_uiOperand[0] = 10;			// in case statements
            m_stOperandAccessLevels.m_uiOperand[1] = 8;

            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
            m_stOperandInternal.m_bCanUseDifferentSizeReg = false;
            m_stOperandInternal.m_bCanUseSameRegister = false;
            m_stOperandInternal.m_bDereference[0] = true;			// we must dereference
            // m_stOperandInternal.m_bDereference[1] = true;	for the second argument it is optional

            m_szFormatted = GenerateLine(m_szOpcode,&m_stOperandInternal, &m_stRegInternal);

        }
        break;
        case 5:	// SAL
        {
            m_stOperandAccessLevels.m_uiOperand[0] = 10;			// in case statements
            m_stOperandAccessLevels.m_uiOperand[1] = 11;

            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
            m_stOperandInternal.m_bCanUseDifferentSizeReg = false;
            m_stOperandInternal.m_bDereference[0] = true;

            m_szFormatted = GenerateLine(m_szOpcode,&m_stOperandInternal, &m_stRegInternal);

        }
        break;
        case 6:	// SAR
        {
            m_stOperandAccessLevels.m_uiOperand[0] = 10;			// in case statements
            m_stOperandAccessLevels.m_uiOperand[1] = 11;

            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
            m_stOperandInternal.m_bCanUseDifferentSizeReg = false;
            m_stOperandInternal.m_bDereference[0] = true;

            m_szFormatted = GenerateLine(m_szOpcode,&m_stOperandInternal, &m_stRegInternal);

        }
        break;
        case 7: // RCL
        {
            m_stOperandAccessLevels.m_uiOperand[0] = 10;			// in case statements
            m_stOperandAccessLevels.m_uiOperand[1] = 11;

            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
            m_stOperandInternal.m_bCanUseDifferentSizeReg = false;
            m_stOperandInternal.m_bDereference[0] = true;

            m_szFormatted = GenerateLine(m_szOpcode,&m_stOperandInternal, &m_stRegInternal);

        }
        break;
        case 8: // RCR
        {
            m_stOperandAccessLevels.m_uiOperand[0] = 10;			// in case statements
            m_stOperandAccessLevels.m_uiOperand[1] = 11;

            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
            m_stOperandInternal.m_bCanUseDifferentSizeReg = false;
            m_stOperandInternal.m_bDereference[0] = true;
            m_szFormatted = GenerateLine(m_szOpcode,&m_stOperandInternal, &m_stRegInternal);

        }
        break;
        case 9:	// ROL
        {
            m_stOperandAccessLevels.m_uiOperand[0] = 10;			// in case statements
            m_stOperandAccessLevels.m_uiOperand[1] = 11;	// constant value

            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
            m_stOperandInternal.m_bCanUseDifferentSizeReg = false;
            m_stOperandInternal.m_bDereference[0] = true;
            m_szFormatted = GenerateLine(m_szOpcode,&m_stOperandInternal, &m_stRegInternal);

        }
        break;
        case 10:	// ROR
        {
            m_stOperandAccessLevels.m_uiOperand[0] = 10;			// in case statements
            m_stOperandAccessLevels.m_uiOperand[1] = 11;

            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
            m_stOperandInternal.m_bCanUseDifferentSizeReg = false;
            m_stOperandInternal.m_bDereference[0] = true;
            m_szFormatted = GenerateLine(m_szOpcode,&m_stOperandInternal, &m_stRegInternal);

        }
        break;
        case 11:	// XADD
        {
            m_stOperandAccessLevels.m_uiOperand[0] = 10;			// in case statements
            m_stOperandAccessLevels.m_uiOperand[1] = 8;

            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
            m_stOperandInternal.m_bCanUseDifferentSizeReg = false;
            m_stOperandInternal.m_bDereference[0] = true;
            m_stOperandInternal.m_bCannotBeTwoMemory = true;	// operands cant both be memory
            m_szFormatted = GenerateLine(m_szOpcode,&m_stOperandInternal, &m_stRegInternal);
        }
        break;
        }
        break;
    }
    case 2:	// Logic-1
    {
        m_stOperandAccessLevels.m_uiNumberOfOperands = 1;
        switch (g_uiGeneratedOpcodeIndex[1])
        {
        case 0:	// NEG
        {
            m_stOperandAccessLevels.m_uiOperand[0] = 10;			// in case statements

            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
            m_stOperandInternal.m_bCanUseDifferentSizeReg = false;
            m_stOperandInternal.m_bDereference[0] = true;
            m_szFormatted = GenerateLine(m_szOpcode,&m_stOperandInternal, &m_stRegInternal);
        }
        break;
        case 1:	// NOT
        {
            m_stOperandAccessLevels.m_uiOperand[0] = 10;			// in case statements

            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
            m_stOperandInternal.m_bCanUseDifferentSizeReg = false;
            m_stOperandInternal.m_bDereference[0] = true;
            m_szFormatted = GenerateLine(m_szOpcode,&m_stOperandInternal, &m_stRegInternal);
        }
        break;

        }
        break;
    }
    case 3:	// Misc
    {
        m_stOperandAccessLevels.m_uiNumberOfOperands = 2; // subject to change
        switch (g_uiGeneratedOpcodeIndex[1])
        {
        case 0:	// LEA
        {
            // LEA cannot be used as LEA EBX, EBX, so disable that register if using through lea, so m_bCanUseSameRegister is false

            m_stOperandAccessLevels.m_uiOperand[0] = 9;			// 16 bit or higher
            m_stOperandAccessLevels.m_uiOperand[1] = 4;			// second should be square bracket memory

            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
            m_stOperandInternal.m_bCanUseDifferentSizeReg = false;
            m_stOperandInternal.m_bCanUseSameRegister = false;
            m_stOperandInternal.m_bDereference[1] = true;
            m_szFormatted = GenerateLine(m_szOpcode,&m_stOperandInternal, &m_stRegInternal);
        }
        break;
        }
        break;
    }
    case 4:	// Transfer-0
    {
        switch (g_uiGeneratedOpcodeIndex[1])
        {
        case 0: // POPF
        {
			  //m_szFormatted = "MOV EAX, 20";

           // m_szFormatted = "POPF";
        }
        break;
        case 1: // POPA
        {
            if (g_uiDwordsTillStackCorrupts < 36)
            {
                // then push instead
                goto pusha;
            }
            m_szFormatted = "POPA";
            g_uiDwordsTillStackCorrupts-=32;

        }
        break;
        case 2:	// PUSHA
        {
pusha:
            m_szFormatted = "PUSHA";

        }
        break;
        case 3:	// PUSHF
        {
            m_szFormatted = "PUSHF";

        }
        break;
        case 4:	// STC
        {
            m_szFormatted = "STC";

        }
        break;
        case 5:	// CLC
        {
            m_szFormatted = "CLC";

        }
        break;
        case 6: // CMC
        {
            m_szFormatted = "CMC";

        }
        break;
        case 7:	// DONT USE STD
        {
            m_szFormatted = "MOV ECX, 30";

        }
        break;
        case 8: // DONT USE CLD
        {
            m_szFormatted = "MOV EDX, 45";

        }
        break;
        case 9:// CBW
        {
            m_szFormatted = "CBW";

        }
        break;
        case 10: // CWD
        {
            m_szFormatted = "CWD";

        }
        break;
        case 11: // CWDE
        {
            m_szFormatted = "CWDE";

        }
        break;
        }
        break;
    }
    case 5:	// Transfer-1
    {
        m_stOperandAccessLevels.m_uiNumberOfOperands = 1;
        switch (g_uiGeneratedOpcodeIndex[1])
        {
        case 0: // PUSH
        {
push:
            // these two instructions HAVE to be 32 - bit if reg generated!
            m_stOperandAccessLevels.m_uiOperand[0] = 7; //9			// in case statements

            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
            m_stOperandInternal.m_bCanUseDifferentSizeReg = false;

            m_szFormatted = GenerateLine(m_szOpcode,&m_stOperandInternal, &m_stRegInternal);
        }
        break;
        case 1: // POP
        {
            if (g_uiDwordsTillStackCorrupts < 4)
            {
                // then push instead
                goto push;
            }
            m_stOperandAccessLevels.m_uiOperand[0] = 7;	//9		// in case statements

            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
            m_stOperandInternal.m_bCanUseDifferentSizeReg = false;
            m_szFormatted = GenerateLine(m_szOpcode,&m_stOperandInternal, &m_stRegInternal);
            //g_uiDwordsTillStackCorrupts--;
        }
        break;
        }
        break;
    }
    case 6:	// Transfer-2
    {
        m_stOperandAccessLevels.m_uiNumberOfOperands = 2;
        switch (g_uiGeneratedOpcodeIndex[1])
        {
        case 0: // MOV
        {
            /*
            mov [asdf], eax
            mov [asdf], dfg
            mov eax, asdf
            mov eax, [asdf]
            */
            // if first argument is dereferenced memory, then second cannot be dereferenced memory

            m_stOperandAccessLevels.m_uiOperand[0] = 10;			// in case statements
            m_stOperandAccessLevels.m_uiOperand[1] = 10;			// in case statements

            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
            m_stOperandInternal.m_bCanUseDifferentSizeReg = false;
            m_stOperandInternal.m_bDereference[0] = true;
            m_stOperandInternal.m_bOutOfRange = true;
            m_szFormatted = GenerateLine(m_szOpcode,&m_stOperandInternal, &m_stRegInternal);
        }
        break;
        case 1: // XCHG
        {
            m_stOperandAccessLevels.m_uiOperand[0] = 10;			// in case statements
            m_stOperandAccessLevels.m_uiOperand[1] = 10;			// in case statements

            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
            m_stOperandInternal.m_bCanUseDifferentSizeReg = false;
            m_stOperandInternal.m_bDereference[0] = true;
            m_stOperandInternal.m_bDereference[1] = true;
            m_stOperandInternal.m_bCannotBeTwoMemory = true;	// operands cant both be memory
            m_stOperandInternal.m_bCanUseSameRegister = false;

            m_szFormatted = GenerateLine(m_szOpcode,&m_stOperandInternal, &m_stRegInternal);

        }
        break;
        }
        break;
    }
    case 7: // ConditionalJumps
    {
        cout << "Skip jump" << endl;
        // we will handle the jumps differently
        /*switch (g_uiGeneratedOpcodeIndex[1])
        	{
        	case 0:	// JA
        		{
        		}
        		break;
        	case 1: // JAE
        		{
        		}
        		break;
        	case 2: // JB
        		{
        		}
        		break;
        	case 3:	// JBE
        		{
        		}
        		break;
        	case 4:	// JC
        		{
        		}
        		break;
        	case 5:	// JE
        		{
        		}
        		break;
        	case 6:	// JG
        		{
        		}
        		break;
        	case 7: // JGE
        		{
        		}
        		break;
        	case 8: // JLE
        		{
        		}
        		break;
        	case 9:	// JNA
        		{
        		}
        		break;
        	case 10:	// JNAE
        		{
        		}
        		break;
        	case 11:	// JNBE
        		{
        		}
        		break;
        	case 12:	// JNC
        		{
        		}
        		break;
        	case 13: // JNE
        		{
        		}
        		break;
        	case 14: // JNG
        		{
        		}
        		break;
        	case 15:	// JNGE
        		{
        		}
        		break;
        	case 16:	// JNL
        		{
        		}
        		break;
        	case 17:	// JNLE
        		{
        		}
        		break;
        	case 18:	// JNO
        		{
        		}
        		break;
        	case 19:	// JNP
        		{
        		}
        		break;
        	case 20:	// JNS
        		{
        		}
        		break;
        	case 21:	// JNZ
        		{
        		}
        		break;
        	case 22:	// JO
        		{
        		}
        		break;
        	case 23:	// JP
        		{
        		}
        		break;
        	case 24:	// JPE
        		{
        		}
        		break;
        	case 25:	// JPO
        		{
        		}
        		break;
        	case 26:	// JS
        		{
        		}
        		break;
        	case 27:	// JZ
        		{
        		}
        		break;
        	case 28:	// JCXZ
        		{
        		}
        		break;
        	}
         break;*/
        break;
    }
    }
return m_szFormatted;
}







string GenerateLine(string m_szOpcode, OPERAND_INTERNAL * m_stOperandInternal, REG_INTERNAL * m_stRegInternal)
{
    stringstream m_ssStringStream;
    m_ssStringStream << m_szOpcode;
    bool m_bGreaterThanSixteen = false;

    unsigned int m_uiNumberOfRegistersGenerated = 0;
    // operand is the arguments AFTER the operation, eg mov eax, ebx, eax and ebx are the two operands, hence this loop will run TWICE

    for (unsigned int i = 0; i < m_stOperandInternal->m_uiNumberOfOperands; i++)
    {
        string m_szGenerated;
        /*	List for m_uiOperandArray for set values
        0 = MEM only 8bit
        1 = MEM only 16bit
        2 = MEM only 32bit
        3 = MEM only any size
        4 = MEM only 16 bits or higher

        5 = REG 8-bit only
        6 = REG 16-bit only
        7 = REG 32-bit only
        8 = REG ONLY any size
        9 = REG ONLY 16 bits or higher

        10 = REG/MEM
        11 = small constant value
        12 = REG/MEM/small constant value
        */

        switch (i)
        {
        case 0:
            m_ssStringStream << " ";
            break;
        default:
            m_ssStringStream << ", ";
        }

        switch (m_stOperandInternal->m_uiOperandArray[i])
        {
            // MEMORY
        case 0: // - 8bit
        case 1: // - 16bit
        case 2: // - 32 bit
        case 3: // - any size!
        case 4: // - 16 bits or higher
        {
            if (m_stOperandInternal->m_bIsDereferenceSet)
            {
                m_szGenerated = GenerateMemory(m_stOperandInternal,i,false,false);

            }
            else
            {
                m_szGenerated = GenerateMemory(m_stOperandInternal,i,true,false);
            }
        }
        break;
        // REGISTERS
        case 5: // REG 8-bit only
        case 6:	// REG 16-BIT
        case 7:	// REG 32-BIT
        {
            m_szGenerated = GenerateRegister(m_stRegInternal,m_stOperandInternal->m_uiOperandArray[i],m_stOperandInternal->m_bCanUseSameRegister,m_stOperandInternal);
        }
        break;

        case 8:	// REG ONLY, any size
        {
            if ((i==0) || (m_stOperandInternal->m_bCanUseDifferentSizeReg==true))// our first time running
            {
                // then a random register is generated
                unsigned int m_uiRandom = GenerateRandom(0,2);
                m_szGenerated = GenerateRegister(m_stRegInternal,m_uiRandom+5,m_stOperandInternal->m_bCanUseSameRegister,m_stOperandInternal);
            }
            else
            {
                // then find which reg was last used, and generate one of same bitsize
                m_szGenerated = GenerateRegister(m_stRegInternal,(m_stOperandInternal->m_uiTypeOfOperandGenerated+5),m_stOperandInternal->m_bCanUseSameRegister,m_stOperandInternal); // 0 = 8 bit
            }
        }
        break;


        case 9:	// 16 bits OR higher
        {
            m_bGreaterThanSixteen = true;
            bool m_bRandom = GenerateRandom(0,1);
            if (m_bRandom)
            {
                // generate 16 bit
                m_szGenerated = GenerateRegister(m_stRegInternal,6,m_stOperandInternal->m_bCanUseSameRegister,m_stOperandInternal);
            }
            else
            {
                // generate 32 bit
                m_szGenerated = GenerateRegister(m_stRegInternal,7,m_stOperandInternal->m_bCanUseSameRegister,m_stOperandInternal);
            }
        }
        break;
        case 10: // ANY REG(of same size) /  OR MEM
        {
            // first check if we MUST generate a register
            // if not, then generate a random, either memory or register

            if ((m_stOperandInternal->m_bCannotBeTwoMemory == true) && (m_stOperandInternal->m_bMemoryGenerated == true))
            {
                // then generate the same bitsized register
                m_szGenerated = GenerateRegister(m_stRegInternal,(m_stOperandInternal->m_uiTypeOfOperandGenerated+5),m_stOperandInternal->m_bCanUseSameRegister,m_stOperandInternal);
            }
            else
            {
                if (((m_stOperandInternal->m_bOutOfRange == true) && i==1) && (m_stOperandInternal->m_uiTypeOfOperandGenerated!=2))
                {
                    // then generate register
                    m_szGenerated = GenerateRegister(m_stRegInternal,(m_stOperandInternal->m_uiTypeOfOperandGenerated+5),m_stOperandInternal->m_bCanUseSameRegister,m_stOperandInternal);
                }
                else
                {
                    bool m_bRandom = GenerateRandom(0,1);
                    if (m_bRandom)
                    {
                        // register
                        if (i==0)
                        {
                            // then generate any random reg
                            unsigned int m_uiRandom = 0;
                            m_uiRandom = GenerateRandom(0,2);
                            m_szGenerated = GenerateRegister(m_stRegInternal,(m_uiRandom+5),m_stOperandInternal->m_bCanUseSameRegister,m_stOperandInternal);
                        }
                        else
                        {
                            m_szGenerated = GenerateRegister(m_stRegInternal,(m_stOperandInternal->m_uiTypeOfOperandGenerated+5),m_stOperandInternal->m_bCanUseSameRegister,m_stOperandInternal);
                        }
                    }
                    else
                    {

                        if (m_stOperandInternal->m_bIsDereferenceSet)
                        {
                            m_szGenerated = GenerateMemory(m_stOperandInternal,i,false,false);
                        }
                        else
                        {
                            m_szGenerated = GenerateMemory(m_stOperandInternal,i,true,false);
                        }
                    }
                }
            }
        }
        break;
        case 11:	// Generate small constant for bitshift
        {
            unsigned int m_uiMaxRange = 0;
            switch (m_stOperandInternal->m_uiTypeOfOperandGenerated)
            {
            case 0:	// generate within 8 bit range
                m_uiMaxRange = 7;
                break;
            case 1:	// generate within 16 bit range
                m_uiMaxRange = 15;
                break;
            case 2:	// generate within 32 bit range
                m_uiMaxRange = 31;
                break;
            }
            m_ssStringStream << GenerateRandom(1,m_uiMaxRange);
        }
        break;

        case 12:
        {
            // reg/mem/small constant value
            unsigned int m_uiGenerated = GenerateRandom(10,11);
            switch (m_uiGenerated)
            {
            case 10:
                m_stOperandInternal->m_uiOperandArray[i] = 10;
                break;
            case 11:
                m_stOperandInternal->m_uiOperandArray[i] = 11;
                break;
            }
            GenerateLine(m_szOpcode, m_stOperandInternal,m_stRegInternal);
        }
        break;

        // new cases in here
        }
        if (m_stOperandInternal->m_uiOperandArray[i] != 11)	// because we already did it!
        {
            m_ssStringStream << m_szGenerated;
        }
    } // end of loop

    return m_ssStringStream.str();
}

OPERAND_INTERNAL::OPERAND_INTERNAL(OPERANDACCESSLEVELS * m_stOperandAccessLevels)
{
    m_uiNumberOfOperands = m_stOperandAccessLevels->m_uiNumberOfOperands;
    m_bIsDereferenceSet = false;
    if (m_uiNumberOfOperands!=0)
    {
        m_uiOperandArray = new unsigned int[m_uiNumberOfOperands];
    }
    for (unsigned int i = 0; i < m_uiNumberOfOperands; i++)
    {
        m_uiOperandArray[i] = m_stOperandAccessLevels->m_uiOperand[i];
    }
    m_bIsDereferenceSet = false;

}

OPERAND_INTERNAL::~OPERAND_INTERNAL()
{
    if (m_uiNumberOfOperands != 0)
    {
        delete[] m_uiOperandArray;
    }

}
