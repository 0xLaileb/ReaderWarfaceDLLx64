class SCVars;
class ISystem;
class IConsole;
class IRenderer;
class ICVar;

template< typename cData >
cData ELEMENT_VTABLE(PVOID64 baseclass, DWORD64 index) { return (*(cData**)baseclass)[index]; }

#define IGameFramework_Address 0x1420E2998 //Failed to create the GameFramework Interface! //ÎÁÍÎÂÈË
#define SSystem_Global_Environment 0x141DD8EE0 //ai_CompatibilityMode //ÎÁÍÎÂÈË
#define pGameCVars (*(SCVars**)0x1420E1CE8) //IsSameTeam->LOBYTE(v11) = sub_14100E5D0(v7, v5, v4);->v6 = *(qword_141ECBDA0...)->0x141ECBDA0 //ÎÁÍÎÂÈË

class SSystemGlobalEnvironment
{
public:
	IRenderer* GetIRenderer() { return (IRenderer*)*(DWORD64*)((DWORD64)this + 0x48); }//-> Draw2DLine
	ISystem* GetISystem() { return (ISystem*)*(DWORD64*)((DWORD64)this + 0xE8); }//-> GetUserName
	IConsole* GetIConsole() { return (IConsole*)*(DWORD64*)((DWORD64)this + 192); }//
	static SSystemGlobalEnvironment* Singleton() { return *(SSystemGlobalEnvironment**)SSystem_Global_Environment; }
};

class IGameFramework
{
public:
	static IGameFramework* GetGameFramework() {
		return *(IGameFramework**)IGameFramework_Address;
	}
};