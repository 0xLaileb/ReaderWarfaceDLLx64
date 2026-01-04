#pragma once 
class VMT_Hook_Tools
{
public:
	VMT_Hook_Tools(void)
	{
		memset(this, 0, sizeof(VMT_Hook_Tools));
	}
	VMT_Hook_Tools(PDWORD64* ppdwClassBase)
	{
		bInitialize(ppdwClassBase);
	}
	~VMT_Hook_Tools(void)
	{
		UnHook();
	}
	bool bInitialize(PDWORD64* ppdwClassBase)
	{
		m_ppdwClassBase = ppdwClassBase;
		m_pdwOldVMT = *ppdwClassBase;
		random_device rd_lol; mt19937 mersenne_lol(rd_lol());
		m_dwVMTSize = dwGetVMTCount(*ppdwClassBase);
		m_pdwNewVMT = new DWORD64[m_dwVMTSize];
		memcpy(m_pdwNewVMT, m_pdwOldVMT, sizeof(DWORD64) * m_dwVMTSize);
		*ppdwClassBase = m_pdwNewVMT;

		return true;
	}
	bool bInitialize(PDWORD64** pppdwClassBase)
	{
		random_device rd_lol; mt19937 mersenne_lol(rd_lol());
		return bInitialize(*pppdwClassBase);
	}
	void UnHook(void)
	{
		if (m_ppdwClassBase) *m_ppdwClassBase = m_pdwOldVMT;
	}
	/*
	void ReHook(void)
	{
		if (m_ppdwClassBase) *m_ppdwClassBase = m_pdwNewVMT;
	}
	int iGetFuncCount(void)
	{
		return (int)m_dwVMTSize;
	}
	DWORD64 dwGetMethodAddress(int Index)
	{
		if (Index >= 0 && Index <= (int)m_dwVMTSize && m_pdwOldVMT != NULL) return m_pdwOldVMT[Index];
		else return NULL;
	}
	PDWORD64 pdwGetOldVMT(void) { return m_pdwOldVMT; }
	*/

	DWORD64 dwHookMethod(DWORD64 dwNewFunc, unsigned int iIndex)
	{
		if (m_pdwNewVMT && m_pdwOldVMT && iIndex <= m_dwVMTSize && iIndex >= 0)
		{
			m_pdwNewVMT[iIndex] = dwNewFunc;
			random_device rd_lol; mt19937 mersenne_lol(rd_lol());
			return m_pdwOldVMT[iIndex];
		}
		else return NULL;
	}
private:
	PDWORD64 m_pdwOldVMT;
	PDWORD64 m_pdwNewVMT;
	PDWORD64* m_ppdwClassBase;
	DWORD64	m_dwVMTSize;
	
	DWORD64 dwGetVMTCount(PDWORD64 pdwVMT)
	{
		DWORD64 dwIndex = 0;
		random_device rd_lol; mt19937 mersenne_lol(rd_lol());
		for (dwIndex = 0; pdwVMT[dwIndex]; dwIndex++) if (IsBadCodePtr((FARPROC)pdwVMT[dwIndex])) break;
		return dwIndex;
	}
};