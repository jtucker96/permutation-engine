#include "resource.h"

void WriteFile()//(BLOCKOBJ m_sectionHeader, BLOCKOBJ m_sectionInclude, BLOCKOBJ m_sectionDataSection, BLOCKOBJ m_sectionTextSection, BLOCKOBJ m_sectionImportSection)
{
	string		m_szConcatenatedBuffer;
	ofstream	m_oOutFile;
	// Header
	for (unsigned int i = 0; i < m_sectionArray[0].m_vszBuffer.size(); i++)
	{
		m_szConcatenatedBuffer += m_sectionArray[0].m_vszBuffer[i];
		m_szConcatenatedBuffer += "\n";	
	}
	// Include
	for (unsigned int i = 0; i < m_sectionArray[1].m_vszBuffer.size(); i++)
	{
		m_szConcatenatedBuffer += m_sectionArray[1].m_vszBuffer[i];
		m_szConcatenatedBuffer += "\n";
	}
	// Data section
	for (unsigned int i = 0; i < m_sectionArray[2].m_vszBuffer.size(); i++)
	{
		m_szConcatenatedBuffer += m_sectionArray[2].m_vszBuffer[i];
		m_szConcatenatedBuffer += "\n";
	}
	// Text Section
	for (unsigned int i = 0; i < m_sectionArray[3].m_vszBuffer.size(); i++)
	{
		m_szConcatenatedBuffer += m_sectionArray[3].m_vszBuffer[i];
		m_szConcatenatedBuffer += "\n";
	}
	// Import section
	for (unsigned int i = 0; i < m_sectionArray[4].m_vszBuffer.size(); i++)
	{
		m_szConcatenatedBuffer += m_sectionArray[4].m_vszBuffer[i];
		m_szConcatenatedBuffer += "\n";
	}
	m_oOutFile.open("Example.txt");

	// prevent errors in assembling
	if (m_szConcatenatedBuffer[m_szConcatenatedBuffer.length()-3] == ',')
	{
		m_szConcatenatedBuffer[m_szConcatenatedBuffer.length()-3] = ' ';
	}
	if (m_szConcatenatedBuffer[m_szConcatenatedBuffer.length()-2] == '\\') // need escape char
	{
		m_szConcatenatedBuffer[m_szConcatenatedBuffer.length()-2] = ' ';
	}
	
	m_oOutFile << m_szConcatenatedBuffer;
	m_oOutFile.close();
}