// pass in registers (read from location of registers...) which MUST NOT be modified, for example the
// destination register for a mov command cannot be a passed register

// this also means specific operations cannot be generated, for example -
// if EDX is passed,

#include "resource.h"

const char m_chSet[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";

unsigned int							g_uiDwordsTillStackCorrupts;


/*
	EAX - AX - AH/AL
	EBX - BX - BH/BL
	ECX - CX - CH/CL
	EDX - DX - DH/DL
	Meaning, if a 32-bit register is unavaliable to use, then don't use 16/8 bit components
*/


// 1 - will we use API or opcode (arithmetic)?

// 2 - Generate which opcode we shall use from list
// 3 - assuming opcode, how many registers do we need, is the opcode specific to registers? (div)
// 4 - are these registers avaliable? YES then set up, NO then restart

// if after second attempt then still fail, carry on with legit code, attemp at later stage.


extern string CreateLabel()
{
    // referring to above instructions...
    unsigned int m_uiLabelLength = GenerateRandom(6,14);
    string m_szLabel = GenerateLabel(m_uiLabelLength);
    g_vszGlobalTrashJMPLabels.push_back(m_szLabel);
    // fill in details about the label

    // maybe add something to check that the label doesn't already exist...?
    return m_szLabel;
}

extern string GenerateLabel(unsigned int m_uiLabelLength)
{
    string m_szTemp;
    for (unsigned int i = 0; i < m_uiLabelLength; i++)
    {
        m_szTemp += m_chSet[GenerateRandom(0,51)];
    }
    return m_szTemp;	// this will return a valid label to insert into code
}

extern void ProcessTrash()			// generate all the trash
{
    // create trash objects and
    g_uiTotalTrashObjs = GenerateRandom(70,120);
    unsigned int m_uiProcObjs = GenerateRandom(120,200);
    g_uiTotalTrashObjs += m_uiProcObjs;

    GenerateAllProcedures(m_uiProcObjs);	// generates all the procedures

    bool m_bDirectInsertion = true;
    for (unsigned int m_uiCompletedRounds = 0; m_uiCompletedRounds < g_uiTotalTrashObjs; m_uiCompletedRounds++)
    {
        // do this each time  for however many trash objects desired!
        // insertion directly, or be called?
        m_bDirectInsertion = GenerateRandom(0,1);
        TRASHOBJ			 m_toTempObj;
        REG_INTERNAL		 m_stRegInternal;
        unsigned int m_uiOpcodeLines, x, y;

        x = GenerateRandom(2, 10);
        y = GenerateRandom(11,44);

        m_uiOpcodeLines = GenerateRandom(x,y);
        unsigned int m_uiNumbRegisters = 0;

        if (m_bDirectInsertion)					// if true, then do not generate procedure
        {
            //  directly insert into code
            // all internal string formatting is done by callee

            // now generate code buffer!
            for (unsigned int i = 0; i < m_uiOpcodeLines; i++)
            {
                string m_szFormattedLine;
                string m_szOpcode;
                bool   m_bRegGenerated = true;

                // identify arguments of the opcode generated, if register is one of them
                // shall we generate a register, or use

                unsigned int m_uiCreateStdcall = GenerateRandom(1,8);

                if ((m_uiCreateStdcall == 8))
                {
                    // generate stdcall
                    OPERANDACCESSLEVELS m_stOperandAccessLevels;
                    m_stOperandAccessLevels.m_uiNumberOfOperands = 0;
                    OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
                    m_stOperandInternal.m_uiNumberOfOperands = 0;

                    m_szFormattedLine = FormattedStdcall(&m_stOperandInternal,&m_stRegInternal,&m_toTempObj,false);
                }
                else
                {
                    // normal way
                    m_szOpcode = GenerateOpcode(false);
                    m_szFormattedLine = LookUpTable(m_szOpcode);
                }

                m_toTempObj.m_vszBuffer.push_back(m_szFormattedLine);
                cout << m_szFormattedLine << endl;
            }
            g_lsGlobalTrashDirectInsert.push_back(m_toTempObj);
            g_uiTotalTrashDirectInsertObjs++;
        }

        else
        {
            // generate JMP
            bool m_bJMP;

            m_toTempObj.m_stLabel.m_szLabel = CreateLabel();
            // Procedure or JMP?
            m_bJMP = GenerateRandom(0,1);

            if (m_bJMP)	// so if we do select to JMP, then label must be placed in code where to jmp back to!
            {
                // setup jmp
                m_toTempObj.m_stLabel.m_bJMP = true;
                m_toTempObj.m_stLabel.m_bProc = false;
                // ensure code can jmp back at the end of jmp segment
                string m_szRestoreJMP = CreateLabel(); // write this to original

                for (unsigned int i = 0; i < m_uiOpcodeLines; i++)
                {

                    string m_szOpcode;
                    stringstream m_szFormattedLine;

                    if (i == 0) // first time running..
                    {
                        m_szFormattedLine << m_toTempObj.m_stLabel.m_szLabel;
                        m_szFormattedLine << ":";
                    }
                    else if (i+1 == m_uiOpcodeLines)
                    {
                        // program is about to exit, jmp back!
                        /* m_szFormattedLine << "JMP ";
                         m_szFormattedLine << m_szRestoreJMP;
                        */
                    }
                    else
                    {
                        // from here
                        unsigned int m_uiCreateStdcall = GenerateRandom(1,8);

                        if ((m_uiCreateStdcall == 8))
                        {
                            // generate stdcall
                            OPERANDACCESSLEVELS m_stOperandAccessLevels;
                            m_stOperandAccessLevels.m_uiNumberOfOperands = 0;
                            OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
                            m_stOperandInternal.m_uiNumberOfOperands = 0;

                            m_szFormattedLine << FormattedStdcall(&m_stOperandInternal,&m_stRegInternal,&m_toTempObj,false);
                        }
                        else
                        {
                            // normal way
                            m_szOpcode = GenerateOpcode(false);
                            m_szFormattedLine << LookUpTable(m_szOpcode);
                        }
                        // to here

                    }



                    // identify arguments of the opcode generated, if register is one of them
                    // shall we generate a register, or use
                    m_toTempObj.m_vszBuffer.push_back(m_szFormattedLine.str());
                    cout << m_szFormattedLine.str() << endl;
                }
                g_lsGlobalTrashJMP.push_back(m_toTempObj);
                g_uiTotalTrashJMPObjs++;
            }

            // for loop ends here
        }
    }

}