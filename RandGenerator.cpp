#include "resource.h"


// just generate a random number from inputs

extern inline unsigned int GenerateRandom(unsigned int m_uiMinimum, unsigned int m_uiMaximum)
{
	std::random_device		   m_sDev;
	//std::default_random_engine m_sRandEngine{m_sDev()};
	std::mt19937 m_sGen(m_sDev());
	std::uniform_int_distribution<> m_rDis(m_uiMinimum, m_uiMaximum);

	return m_rDis(m_sGen);
}

