#include "Parameters_Codes.h"
SSystemGlobalEnvironment* pSSystemGlobalEnvironment;
IGameFramework* pGameFramework;

//bool __fastcall sub_14110F0C0(__int64 a1)
//40 57 48 83 EC 60 48 8B 05 ? ? ? ? 48 8B F9 48 8B 88 ? ? ? ? 
//ЗАГРУКА /СОХРАНЕНИЕ game.cfg

//_QWORD *__fastcall sub_1400C03D0(_QWORD *a1, __int64 a2, __int64 a3, __int64 a4) //ЗАПРОСЫ НА СЕРВ И Т.Д
//void* __fastcall sub_1400C5260(__int64 a1, const void* a2, unsigned __int64 a3) //ЗАГРУЗКА МЕНЮ (GUI)

/*
(*(**(SSystemGlobalEnvironment_141D4CAA0 + 0xF8) + 1136i64)) (*(SSystemGlobalEnvironment_141D4CAA0 + 0xF8), "Dof_FocusRange", v24, 0i64);
gEnv->p3DEngine->SetPostEffectParam (const char* pParam, float fValue, bool bForceValue = false)
*/

//signed __int64 __fastcall sub_141133B70(__int64 a1, __int64 *a2, _BYTE *a3, __int64 a4)
//48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC 60 49 8B E9 
//ИЗМЕНЕНИЕ НАСТРОЕК КОМНАТЫ (gameroom_update_pvp)
/*
		const char** v6 = (const char**)a2;
		const char* v13 = *v6;
		v13 = "e246660c-52cb-4a56-8d25-c0f040d03793";
		ITestKEK* v19;
		ISystem* pSystem = pSSystemGlobalEnvironment->GetISystem();
		pSystem->Get(&v19, "gameroom_update_pvp", 0);
		v19->Get("by_mission_key", 0);
		v19->Get("mission_key", v13);
*/

//void **__fastcall sub_1400B1D00(void **a1, void *a2) -> 29.10 dump - много инфы выходит

//int __fastcall sub_14112C2D0(__int64 a1, __int64 **a2, unsigned int a3, __int64 name_room, __int64 a5, _BYTE *a6, __int64 a7, __int64 mission_key)
//48 89 5C 24 ? 48 89 74 24 ? 55 57 41 56 48 8B EC 48 83 EC 40 48 8B 0A 
//ПРИ СОЗДАНИИ КОМНАТЫ ПОЛУЧАЕТ mission_key и room_name

class WalimemEngine {
public:
	_QWORD dwAddress = 0x140001000;
	_QWORD dwSize = 0x2490000;
	void Get_0()
	{
		//\x88\x45\x48\x48\x8B\xD6, xxxxxx
		_QWORD tmp = FindPattern(
			(char*)"\x88\x45\x48\x48\x8B\xD6",
			"xxxxxx");
		if (tmp) {
			//printf("1: %s\n", tmp + (7 + *(long*)(tmp + 3)));
			//printf("2: %s\n", *(long*)(tmp + 3));
			printf("3: %s\n", *(long*)(tmp));
			printf("4: %s\n", (*(long*)(tmp) / 0x10000));
		}
	}
private:
	bool bCompare(const char* Data, const char* Mask_A, const char* Mask_B)
	{
		for (; *Mask_B; ++Mask_B, ++Data, ++Mask_A) {
			if (*Mask_B == 'x' && *Data != *Mask_A) {
				return 0;
			}
		}

		return (*Mask_B) == 0;
	}
	_QWORD FindPattern(char* Mask_A, const char* Mask_B)
	{
		for (_QWORD i = 0; i < dwSize; i++) {
			if (bCompare((char*)(dwAddress + i), Mask_A, Mask_B)) {
				return dwAddress + i;
			}
		}

		return 0;
	}
};

#pragma region FUNC1
_QWORD adress1 = 0x140E8D390;
#define PRMS __int64 hInternet, LPCSTR lpszUrl,LPCSTR    lpszHeaders,DWORD     dwHeadersLength,DWORD     dwFlags,DWORD_PTR dwContext
#define PRMS_LOCAL  hInternet,  lpszUrl, lpszHeaders, dwHeadersLength, dwFlags, dwContext

typedef char(__stdcall* Test1)(PRMS);
Test1 mTest1;
char __fastcall sub_test_1(PRMS)
{
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
	//SetConsoleCP(CP_UTF8);
	//SetConsoleOutputCP(CP_UTF8);
	printf("HELLO!\n");

	return mTest1(PRMS_LOCAL);
}

/*
* char __fastcall sub_test_1(PRMS)
{
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
	//SetConsoleCP(CP_UTF8);
	//SetConsoleOutputCP(CP_UTF8);
	//sprintf(buffer, "%s\n", a1);
	printf(a1);
	printf("\n");

	if (strstr(a1, "Driver description")) a1 = "Driver description: POSHEL NAHYI SUKA!";
	else if (strstr(a1, "Driver GUID")) a1 = "D3D Adapter: Driver GUID: D7000000-5111-120F-5000E8D5C541A10E1000000000000061C00060";
	else if (strstr(a1, "VendorId")) a1 = "D3D Adapter: VendorId = 0x1000";
	else if (strstr(a1, "DeviceId")) a1 = "D3D Adapter : DeviceId = 0x1CC6";
	else if (strstr(a1, "SubSysId")) a1 = "D3D Adapter : SubSysId = 0x35CCC000";

	return mTest1(PRMS_LOCAL);
}
*/
#pragma endregion

void CREATE_CONSOLE()
{
#pragma region  CREATE_CONSOLE
	int hConHandle = 0;
	HANDLE lStdHandle = 0;
	FILE* fp = 0;
	FILE* fp_2 = 0;

	AllocConsole();
	freopen("CON", "w", stdout);
	freopen("CON", "r", stdin);

	lStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(PtrToUlong(lStdHandle), _O_TEXT);
	fp = _fdopen(hConHandle, "w");
	*stdout = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);
	fp_2 = _fdopen(hConHandle, "r");
	*stdin = *fp_2;
	setvbuf(stdin, NULL, _IONBF, 0);

	SetConsoleTitle("[Console]");
	DeleteMenu(::GetSystemMenu(::GetConsoleWindow(), TRUE), SC_CLOSE, MF_BYCOMMAND);
#pragma endregion
	char text[999];
	setlocale(LC_ALL, "Russian");
	system("color 2");

	while (true) {
		Sleep(1000);
		//system("cls");

		pSSystemGlobalEnvironment = (SSystemGlobalEnvironment*)(*(DWORD64*)(SSystem_Global_Environment));
		if (!pSSystemGlobalEnvironment) continue;

	    pGameFramework = (IGameFramework*)(*(DWORD64*)(IGameFramework_Address));
		if (!pGameFramework) continue;

		//printf("SetGlobalParameter(...)");
		//pSSystemGlobalEnvironment->GetI3DEngine()->SetGlobalParameter(12, Vec3(100, 200, 101));
	}
}

void OneStart()
{
	Sleep(1000);
	while (!SSystemGlobalEnvironment::Singleton() && !SSystemGlobalEnvironment::Singleton()->GetIRenderer()) Sleep(340);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)CREATE_CONSOLE, 0, 0, 0);
	Sleep(1000);
	if (MH_Initialize() != MH_OK)
	{
		random_device rd_lol; mt19937 mersenne_lol(rd_lol());
		MessageBoxA(0, (const char*)"ERROR!", "WTF MAN!", 0);
		return;
	}

	SSystemGlobalEnvironment* pSSystemGlobalEnvironment = (SSystemGlobalEnvironment*)(*(DWORD64*)(SSystem_Global_Environment));
	if (!pSSystemGlobalEnvironment) return;

	//00000001419B44F8		exit	api-ms-win-crt-runtime-l1-1-0
	//00000001419B40D0	6	getsockname	WS2_32
	//00000001419B4000		InternetOpenUrlA	WININET
	if (MH_CreateHookApi(L"WININET", "InternetOpenUrlA", &sub_test_1, (LPVOID*)&mTest1) != MH_OK) {
	//if (MH_CreateHook((DWORD64*)adress1, sub_test_1, (LPVOID*)&mTest1) != MH_OK) {
		printf("error..\n");
		getchar();
		return;
	}
	MH_EnableHook((DWORD64*)adress1);

	while (true) {
		Sleep(5000);
		//system("cls");
		//printf("\nChecking..\n");
		
		SSystemGlobalEnvironment* pSSystemGlobalEnvironment = (SSystemGlobalEnvironment*)(*(DWORD64*)(SSystem_Global_Environment));
		if (!pSSystemGlobalEnvironment) continue;
		//printf_s("[pSSystemGlobalEnvironment: %x]\n", pSSystemGlobalEnvironment);

		IGameFramework* pGameFramework = (IGameFramework*)(*(DWORD64*)(IGameFramework_Address));
		if (!pGameFramework) continue;
		//printf_s("[pGameFramework: %x]\n", pGameFramework);
	}
}

BOOL WINAPI DllMain(HMODULE hDll, DWORD64 dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH && GetModuleHandleA("Game.exe"))
	{
		random_device rd_lol; mt19937 mersenne_lol(rd_lol());
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)OneStart, 0, 0, 0);
		return TRUE;
	}
	return FALSE;
}