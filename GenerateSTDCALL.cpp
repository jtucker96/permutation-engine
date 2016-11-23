#include "resource.h"

/*
m_vszLabels contains labels which are compared with
And if equality then the offending vector string is replaced with a new opcode:

element 0 should contain the base procedure, the label of the procedure of which we are searching
ie, as to prevent recursive function calls

all stdcalls are found and located then compared as mentioned above,
if no equality then push back the label and follow those labels and compare next stdcalls to
the large vector containing labels as before

*/


void FindLabel(list<TRASHOBJ>::iterator m_vitTrashObjIterator, vector<string> * m_vszComparedLabels)
{	// true if match, false if no match
	//testing
	if (m_vitTrashObjIterator->m_bMakesStdcall)
	{ // if this procedure DOES make at least one stdcall, then follow up
		for (unsigned int i = 0; i != m_vszComparedLabels->size(); i++)	// less than the number of labels we have to compare
		{
			for (unsigned int z = 0; z != m_vitTrashObjIterator->m_vszLabelsCalled.size(); z++)	// less than the labels to stdcalls INSIDE the procedure
			{	// two for loops to compare all cases
				if (m_vitTrashObjIterator->m_vszLabelsCalled.at(z).compare(m_vszComparedLabels->at(i)) ==0 )
				{	// something matches
					// find where abouts in m_vitTrashObjIterator->m_vszBuffer the stdcall for offending label is
					// and replace it with random opcode
					for (unsigned int m_uiInnerLoop = 0; (m_uiInnerLoop < (m_vitTrashObjIterator->m_vszBuffer.size())); m_uiInnerLoop++)
					{
						if(m_vitTrashObjIterator->m_vszBuffer[m_uiInnerLoop].compare(0,7,"stdcall") == 0)
						{// first find the stdcall line
							
							string m_szTempLabel = m_vitTrashObjIterator->m_vszBuffer[m_uiInnerLoop].substr(8,m_vitTrashObjIterator->m_vszBuffer[m_uiInnerLoop].find(",")-8);
							if (m_szTempLabel.compare(m_vitTrashObjIterator->m_vszLabelsCalled.at(z)) == 0)
							{	// then replace this
								string m_szOpcode = GenerateOpcode(false);
								string m_szFormattedLine = LookUpTable(m_szOpcode);
								m_vitTrashObjIterator->m_vszBuffer[m_uiInnerLoop].replace(m_vitTrashObjIterator->m_vszBuffer[m_uiInnerLoop].begin(),m_vitTrashObjIterator->m_vszBuffer[m_uiInnerLoop].end(),m_szFormattedLine);
								cout << m_vitTrashObjIterator->m_vszBuffer[m_uiInnerLoop] << endl;
							}
						}
					}
					
				}
				else
				{
					// then find the proc and do the same
					// increment the iterator to point to the new procedure
					std::list<TRASHOBJ>::iterator m_vitNewLocalIter = g_lsGlobalTrashProcedure.begin();
					while(1)
					{
						if (m_vitTrashObjIterator->m_vszLabelsCalled.at(z).compare(m_vitNewLocalIter->m_stLabel.m_szLabel) == 0)
						{
							//m_vitTrashObjIterator = m_vitNewLocalIter;
							break;
						}
						else
						{
							m_vitNewLocalIter++;
						}
					}
					m_vszComparedLabels->push_back(m_vitTrashObjIterator->m_vszLabelsCalled.at(z));
					FindLabel(m_vitNewLocalIter,m_vszComparedLabels);
					m_vszComparedLabels->pop_back();
				}
			}
		}
	}
	// procedure doesn't make stdcall
	// return to caller
}

string FormattedStdcall(OPERAND_INTERNAL * m_stOperandInternal, REG_INTERNAL * m_stRegInternal,TRASHOBJ * m_stTempObj, bool m_bFromProc)
{
    //redostdcall:
    unsigned int m_uiTempIndex = GenerateRandom(0,g_uiTotalTrashProcObjs-1);
    stringstream m_ssTemp;
    std::list<TRASHOBJ>::iterator m_lsTempIter = g_lsGlobalTrashProcedure.begin();

    for (unsigned int i = 0; i < m_uiTempIndex; i++)
    {
        m_lsTempIter++;
    }	



	// we are generating an stdcall to this procedure, so follow the stdcall
	// then follow ALL stdcalls made from that procedure and match them to the labels which cannot be used
	// for security, do not go further than 3 levels, if the program wants to go to the fourth level then replace that call 
	// with some random opcode, with memory or register ect...
	// however if we match label before then, then replace that offending label with some opcode.

	if (m_bFromProc)	// you have to check if they call EACH other, or if EITHER of them call the base proc!
	{	// find out if destination makes any stdcalls, check ALL of them, and check where they go to
		vector<std::string> m_vszLabels;
		m_vszLabels.push_back(m_stTempObj->m_stLabel.m_szLabel); // push back label of the proc this function resides in, base label

		//FindLabel(m_lsTempIter,&m_vszLabels); // once this function has been called, all calls are patched
		m_stTempObj->m_vszLabelsCalled.push_back(m_lsTempIter->m_stLabel.m_szLabel); 
		m_stTempObj->m_bMakesStdcall = true;

	}

    m_ssTemp << "stdcall " << m_lsTempIter->m_stLabel.m_szLabel;

    string * m_szGenMemOrReg;

    if (m_lsTempIter->m_uiDwordsToReserveForStack != 0)
    {
        m_szGenMemOrReg = new string[m_lsTempIter->m_uiDwordsToReserveForStack];

        for (unsigned int i = 0; i < m_lsTempIter->m_uiDwordsToReserveForStack; i++)
        {
            bool m_bArg = GenerateRandom(0,1);
            if (m_bArg)
            {
                m_szGenMemOrReg[i] = GenerateRegister(m_stRegInternal,7,false,m_stOperandInternal);
            }
            else
            {
                m_szGenMemOrReg[i] = GenerateMemory(m_stOperandInternal,0,true,true);
            }
            m_ssTemp << ", " << m_szGenMemOrReg[i];
        }

        delete[] m_szGenMemOrReg;
    }
    return m_ssTemp.str();
}


