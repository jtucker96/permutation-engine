#include "resource.h"
#include <algorithm>

extern string GenerateMemory(OPERAND_INTERNAL * m_stOperandInternal, unsigned int m_uiOperandIndex, bool m_bDereferenceMem, bool m_bFromStdcall)
{
    unsigned int m_uiMemIndex;
    std::list<VARIABLE>::iterator m_lsVariableIterator;

	if (m_uiOperandIndex != 0)
	{	// then we do same size memory as before with reg/mem
		//m_stOperandInternal->m_uiTypeOfOperandGenerated;	
		do
		{
			m_lsVariableIterator = g_lsGlobalVariable.begin();
			//m_lsVariableIterator++;
			m_uiMemIndex = GenerateRandom(0,g_lsGlobalVariable.size()-1);
			for (unsigned int z = 0; z < m_uiMemIndex; z++)
			{
				// advance our iterator by the generated number
				m_lsVariableIterator++;
			}
		}
		while(( m_lsVariableIterator->m_uiTypeVariable != m_stOperandInternal->m_uiTypeOfOperandGenerated ));
	}
	else
	{	// we can generate any random memory
		m_lsVariableIterator = g_lsGlobalVariable.begin();
		//m_lsVariableIterator++;
		m_uiMemIndex = GenerateRandom(0,g_lsGlobalVariable.size()-1);
		for (unsigned int z = 0; z < m_uiMemIndex; z++)
		{
			// advance our iterator by the generated number
			m_lsVariableIterator++;
		}
	}

	m_stOperandInternal->m_uiTypeOfOperandGenerated = m_lsVariableIterator->m_uiTypeVariable;	// 0 for 8 bit, 1 for 16 bit, 2 for 32 bit

	string m_szTempVariable = m_lsVariableIterator->m_szVariableName;	// to avoid re-updating global list with deferenced variables

	if (m_bDereferenceMem == true)
	{
		if (m_bFromStdcall)
		{
			m_szTempVariable = DereferenceOperand(m_szTempVariable, m_stOperandInternal,true);
		}
		else
		{
			m_szTempVariable = DereferenceOperand(m_szTempVariable, m_stOperandInternal,false);		
		}
		m_stOperandInternal->m_bIsDereferenceSet = true;
	}


    m_stOperandInternal->m_bMemoryGenerated = true;	// true, we used memory for first operand
	m_stOperandInternal->m_uiTypeOfOperandGenerated = m_lsVariableIterator->m_uiTypeVariable;

	return m_szTempVariable;
}


extern inline string DereferenceOperand(string m_szOperand, OPERAND_INTERNAL * m_stOperandInternal, bool m_bFromStdcall)
{
	stringstream m_ssTemp;
	
	if (m_bFromStdcall)
	{
		m_ssTemp << "DWORD ";
	}

    // add square brackets to operand
	m_ssTemp << "[";
	m_ssTemp << m_szOperand;
	m_ssTemp << "]";
	return m_ssTemp.str();
}

