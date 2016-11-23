#include "resource.h"

void GenerateAllProcedures(unsigned int m_uiNumberOfProcedures)
{

    // PROCEDURE CAN ONLY BE CALLED THROUGH STDCALL!!!
    // remember prologue and epilogue for a procedure must be included
    // ie, proc GENERATED LABEL , setup stack frame, destroy stack frame

    // setup procedure
    for (unsigned int m_uiProceduresCreated = 0; m_uiProceduresCreated < m_uiNumberOfProcedures; m_uiProceduresCreated++)
    {
        unsigned int x, y;

        x = GenerateRandom(2, 10);
        y = GenerateRandom(11,51);

        unsigned int m_uiNumberOfLines = GenerateRandom(x,y);
        //shall we setup local stack frame?
        TRASHOBJ				m_toTempObj;

        for (unsigned int i = 0; i < m_uiNumberOfLines; i++)
        {
			beg:
           	OPERANDACCESSLEVELS		m_stOperandAccessLevels;
			REG_INTERNAL			m_stRegInternal;


            m_toTempObj.m_stLabel.m_bJMP = false;
            m_toTempObj.m_stLabel.m_bProc = true;

            string m_szOpcode;
            stringstream m_szFormattedLine;

            if (i==0) // setup proc frame
            {
                m_toTempObj.m_stLabel.m_szLabel = CreateLabel();


				bool m_bLocalStack = GenerateRandom(0,1);
				if (m_bLocalStack)
				{
					m_toTempObj.m_uiDwordsToReserveForStack = GenerateRandom(1,5);
				}
				else
				{
					m_toTempObj.m_uiDwordsToReserveForStack = 0;
				}
                m_szFormattedLine << "proc ";
                m_szFormattedLine << m_toTempObj.m_stLabel.m_szLabel;
                switch (m_toTempObj.m_uiDwordsToReserveForStack)
                {
                case 1:
                    m_szFormattedLine << " , arg1";
                    m_szFormattedLine << "\nsub esp, ";
                    m_szFormattedLine << (m_toTempObj.m_uiDwordsToReserveForStack*4);
                    break;
                case 2:
                    m_szFormattedLine << " ,arg1, arg2";
                    m_szFormattedLine << "\nsub esp, ";
                    m_szFormattedLine << (m_toTempObj.m_uiDwordsToReserveForStack*4);
                    break;
                case 3:
                    m_szFormattedLine << " , arg1, arg2, arg3";
                    m_szFormattedLine << "\nsub esp, ";
                    m_szFormattedLine << (m_toTempObj.m_uiDwordsToReserveForStack*4);
                    break;
                case 4:
                    m_szFormattedLine << " , arg1, arg2, arg3, arg4";
                    m_szFormattedLine << "\nsub esp, ";
                    m_szFormattedLine << (m_toTempObj.m_uiDwordsToReserveForStack*4);
                    break;
                case 5:
                    m_szFormattedLine << " , arg1, arg2, arg3, arg4, arg5";
                    m_szFormattedLine << "\nsub esp, ";
                    m_szFormattedLine << (m_toTempObj.m_uiDwordsToReserveForStack*4);
                    break;
                }
            }
            else if (i+1 == m_uiNumberOfLines)
            {
                m_szFormattedLine << "ret\nendp";
            }
            else
            {

                unsigned int m_uiCreateStdcall = GenerateRandom(1,5);
				if ((m_uiProceduresCreated > 3) && (m_uiCreateStdcall == 5))
                {// generate stdcall

                    m_stOperandAccessLevels.m_uiNumberOfOperands = 0;
                    OPERAND_INTERNAL m_stOperandInternal(&m_stOperandAccessLevels);
                    m_stOperandInternal.m_uiNumberOfOperands = 0;

					m_szFormattedLine << FormattedStdcall(&m_stOperandInternal,&m_stRegInternal,&m_toTempObj,true);
				}
				else
				{
					m_szOpcode = GenerateOpcode(true);
						// don't generate popad
					m_szFormattedLine << LookUpTable(m_szOpcode);
				}
            }
            m_toTempObj.m_vszBuffer.push_back(m_szFormattedLine.str());
            cout << m_szFormattedLine.str() << endl;
        }

        // ensure prologue epilogue is correct
        /*
        stdcall myproc, arg1, arg2, arg3
        .....
        proc myproc, arg1, arg2, arg3
        sub esp, numberofdwords*4
        [code here]
        ret
        endp
        g_vszGlobalTrashJMPLabels
        */

		if (m_toTempObj.m_vszLabelsCalled.size() == 0)
		{
			m_toTempObj.m_bMakesStdcall = false;
		}

        g_lsGlobalTrashProcedure.push_back(m_toTempObj);
		if (g_uiTotalTrashProcObjs == 0)
		{
			g_lsGlobalTrashProcedureIterator = g_lsGlobalTrashProcedure.begin();
		}
        g_uiTotalTrashProcObjs++;
    }

// registers all global procedures
}
