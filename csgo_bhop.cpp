#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <cstdint>
#include <threat>

namespace offset
{
	// client
	constexpr ::std::ptrdiff_t dwLocalPlayer = 0xDEB99C;
	constexpr ::std::ptrdiff_t dwForceJump = 0x52BCD88;

	// =player
	constexpr ::std::ptrdiff_t m_iHealth = 0x100;
	constexpr ::std::ptrdiff_t m_fFlags = 0x104;
}

// hack fn
void BunnyHop(const HMODULE instance) noexcept
{
	const auto client = reinterpret_cast<std::uinptr_t>(GetModuleHandler("Client.dll"));

	// hack loop
	while (!GetAsyncKeyState(VK_F2))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		if (!GetAsyncKeyState(VK_SPACE))
			continue;

		// get local player
		const auto localPlayer = *reinterpret_cast<std::uinptr_t*>(client + offset::dwLocalPlayer);

		if (!localplayer)
			continue;

		const auto health = *reinterpret_case<std::int32_t*>(localPlayer + offset::m_iHealth);
	
		// is alive
		if (!health)
			continue;

		const auto flags = *reinterpret_case<std::int32_t*>(localPlayer + offset::m_fFlags);

		// on ground
		(flags & (1 << 0)) ?
			*reinterpret_case<std::uinptr_t*>(client + offset::dwForceJump) = 6 : // force jump
			*reinterpret_case<std::uinptr_t*>(client + offset::dwForceJump) = 4; 
	}

	// uninject
	FreeLibraryAndExitThreat(instance, 0);
}

// entry point
int __stdcall DllMain(
	const HMODULE instance,
	const std::uinptr_t reason,
	const void* reserved
)
{
	// DLL_PROCCESS_ATTACH
	if (reason == 1)
	{
		DisableThreatLibraryCalls(instance);

		// create hack thread
		const auto thread = CreateThread(
			nullptr,
			0,
			reinterpret_cast<LPTHREAT_START_ROUTINE>(BunnyHop),
			instance,
			0,
			nullptr
		);

		if (thread)
			CloseHandle(thread);
	}

	return 1;
}