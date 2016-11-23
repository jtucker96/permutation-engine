#include "resource.h"


unsigned int							g_uiGlobalRegisterFailCount;
// Generate register, confirm if avaliable


/*	argument input is as follows
	1 - 8-bit register ONLY
	2 - 16-bit register ONLY
	3 - 32-bit register ONLY
	4 - ANY register
*/

extern string GenerateRegister(REG_INTERNAL * m_stRegBits, unsigned int m_uiRegType, bool m_bCanUseSameRegister, OPERAND_INTERNAL * m_stOperandInternal) // Generates a register which is not currently in use to be used by junk gen
{
	g_uiGlobalRegisterFailCount = 0;
redoreg:
	if ((g_uiGlobalRegisterFailCount >= 7) && (m_stOperandInternal->m_uiNumberOfOperands == 0))	
	{					// indicating we came from stdcall generator
			// then we shouldn't generate register
		return "Fail";
	}
	else if(g_uiGlobalRegisterFailCount >= 7)
	{	// indicating we came from line generator
	
	}
    unsigned int m_uiMaxRange = 0;  // is either 5(32-16bit) or 7 (8-bit)
    unsigned int m_uiRegIndex = 0;
    bool		 m_bSixteenOrHigher = false;

    switch (m_uiRegType)
    {
    case 5: // 8 bit register ONLY
    {
		m_stOperandInternal->m_uiTypeOfOperandGenerated = 0;
        m_uiMaxRange = 7;
        m_uiRegIndex = GenerateRandom(0,m_uiMaxRange);	// get last random generation, compare with new generation use with if it can use the same register
        if (!m_bCanUseSameRegister)
        {
            // cant use same register remember

            if ((m_uiRegIndex == m_stRegBits->m_uiSecondaryRegisterIndex) && (m_stOperandInternal->m_uiTypeOfOperandGenerated == 0))
            {
                // then we've generated the same register fuck start again
                unsigned int m_uiGenerated = m_uiRegIndex;
                do
                {
                    m_uiRegIndex = GenerateRandom(0,m_uiMaxRange);
                }	// generate random till we get one that DOESN'T MATCH!
                while (m_uiGenerated == m_uiRegIndex);
            }
        }
        m_stRegBits->m_uiSecondaryRegisterIndex = m_uiRegIndex;

        switch (m_uiRegIndex)
        {
        case 0: // ah
        {

            if (m_stAvaliableReg.AH == false)
            {
                goto redoreg; g_uiGlobalRegisterFailCount++;
            }
            break;
        }
        case 1: // al
        {
            if (m_stAvaliableReg.AL == false)
            {
                goto redoreg; g_uiGlobalRegisterFailCount++;
            }
            break;
        }
        case 2: // bh
        {

            if (m_stAvaliableReg.BH == false)
            {
                goto redoreg; g_uiGlobalRegisterFailCount++;
            }
            break;
        }
        case 3: // bl
        {

            if (m_stAvaliableReg.BL == false)
            {
                goto redoreg; g_uiGlobalRegisterFailCount++;
            }
            break;
        }
        case 4: // ch
        {

            if (m_stAvaliableReg.CH == false)
            {
                goto redoreg; g_uiGlobalRegisterFailCount++;
            }
            break;
        }
        case 5: // cl
        {

            if (m_stAvaliableReg.CL == false)
            {
                goto redoreg; g_uiGlobalRegisterFailCount++;
            }
            break;
        }
        case 6: // dh
        {
            if (m_stAvaliableReg.DH == false)
            {
                goto redoreg; g_uiGlobalRegisterFailCount++;
            }
            break;
        }
        case 7: // dl
        {

            if (m_stAvaliableReg.DL == false)
            {
                goto redoreg; g_uiGlobalRegisterFailCount++;
            }
            break;
        }
        // no default

		}
	m_stRegBits->m_szRegister = m_stEightBitReg.m_szRegArray[m_uiRegIndex];
	break;
    }
    case 6: // 16 bit register ONLY
    {
		m_uiRegIndex = GenerateRandom(0,m_uiMaxRange);
        m_uiMaxRange = 5;
        if (!m_bCanUseSameRegister)
        {
            // cant use same register remember
            if ((m_uiRegIndex == m_stRegBits->m_uiSecondaryRegisterIndex) && (m_stOperandInternal->m_uiTypeOfOperandGenerated == 1))
            {
                // then we've generated the same register fuck start again
				unsigned int m_uiGenerated = m_uiRegIndex;
				do
				{
					m_uiRegIndex = GenerateRandom(0,m_uiMaxRange);
				}	// generate random till we get one that DOESN'T MATCH!
				while (m_uiGenerated == m_uiRegIndex);
			}
        }
		m_stOperandInternal->m_uiTypeOfOperandGenerated = 1;
        m_stRegBits->m_uiSecondaryRegisterIndex = m_uiRegIndex;
        switch (m_uiRegIndex)
        {
			case 0:			// AX
			{
				if (m_stAvaliableReg.AX == false)
				{
					goto redoreg; g_uiGlobalRegisterFailCount++;
				}
				break;
			}
			case 1:			// BX
			{
				if (m_stAvaliableReg.BX == false)
				{
					goto redoreg; g_uiGlobalRegisterFailCount++;
				}
			 break;
			}
			case 2:			// CX
			{
				if (m_stAvaliableReg.CX == false)
				{
					goto redoreg; g_uiGlobalRegisterFailCount++;
				}
				break;
			}
			case 3:			// DX
			{
				if (m_stAvaliableReg.DX == false)
				{
					goto redoreg; g_uiGlobalRegisterFailCount++;
				}
				break;
			}
			case 4:			// DI
			{
				if (m_stAvaliableReg.DI == false)
				{
					goto redoreg; g_uiGlobalRegisterFailCount++;
				}
				break;
			}
        
			case 5:         // SI
			{
				if (m_stAvaliableReg.SI == false)
				{
					goto redoreg; g_uiGlobalRegisterFailCount++;
				}
            
				break;
			}
        }
    m_stRegBits->m_szRegister = m_stSixteenBitReg.m_szRegArray[m_uiRegIndex];
    break;
    }
    case 7: // 32 bit register ONLY
    {
        m_uiMaxRange = 5;
        m_uiRegIndex = GenerateRandom(0,m_uiMaxRange);
        if (!m_bCanUseSameRegister)
        {
            // cant use same register remember

            if ((m_uiRegIndex == m_stRegBits->m_uiSecondaryRegisterIndex) && (m_stOperandInternal->m_uiTypeOfOperandGenerated == 2))
            {
                // then we've generated the same register fuck start again
                unsigned int m_uiGenerated = m_uiRegIndex;
                do
                {
                    m_uiRegIndex = GenerateRandom(0,m_uiMaxRange);
                }	// generate random till we get one that DOESN'T MATCH!
                while (m_uiGenerated == m_uiRegIndex);
            }
        }
        m_stOperandInternal->m_uiTypeOfOperandGenerated = 2;
        m_stRegBits->m_uiSecondaryRegisterIndex = m_uiRegIndex;

        switch (m_uiRegIndex)
        {
			case 0:			// EAX
			{
				if (m_stAvaliableReg.EAX == false)
				{
					goto redoreg; g_uiGlobalRegisterFailCount++;
				}
				break;
			}
			case 1:			// EBX
			{
				if (m_stAvaliableReg.EBX == false)
				{
					goto redoreg; g_uiGlobalRegisterFailCount++;
				}
				break;
			}
            
            case 2:			// ECX
            {
                if (m_stAvaliableReg.ECX == false)
                {
                    goto redoreg; g_uiGlobalRegisterFailCount++;
                }
				break;
            }
            
            case 3:			// EDX
            {
                if (m_stAvaliableReg.EDX == false)
                {
                    goto redoreg; g_uiGlobalRegisterFailCount++;
                }
				break;
            }
            case 4:			// EDI
            {
                if (m_stAvaliableReg.EDI == false)
                {
                    goto redoreg; g_uiGlobalRegisterFailCount++;
                }
				break;
            }
            
            case 5:         // ESI
            {
                if (m_stAvaliableReg.ESI == false)
                {
                    goto redoreg; g_uiGlobalRegisterFailCount++;
                }
				break;
            }
            
        }
        m_stRegBits->m_szRegister = m_stThirtytwoBitReg.m_szRegArray[m_uiRegIndex];
        break;
	}
        case 9:	// 16-bits or higher
            m_bSixteenOrHigher = true;
        case 8: // any register
        case 10:
        {
            /*
            1 - 8-bit reg
            2 - 16-bit reg
            3 - 32-bit reg
            */
            unsigned int m_uiRegChoice;
            if (m_bSixteenOrHigher) // if this is true
            {
                m_uiRegChoice = GenerateRandom(0,1);
            }
            else
            {
                m_uiRegChoice = GenerateRandom(0,2);
            }
            m_stRegBits->m_szRegister = GenerateRegister(m_stRegBits,m_uiRegChoice+5,m_bCanUseSameRegister,m_stOperandInternal);
            break;
        }
    }
	 return m_stRegBits->m_szRegister;
}