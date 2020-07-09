#include <iostream>
#include <windows.h>

namespace WaterMarkRemover {
	class remove {
	private:
		DWORD val = 0x00000004;
	public:
		void read() {
			DWORD val;
			DWORD dataSize = sizeof(val);
			if (ERROR_SUCCESS == RegGetValueA(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\svsvc", "Start", RRF_RT_DWORD, nullptr, &val, &dataSize)) {
				if (val == 4) {
					std::cout << "Value is already 4 - Patched! :) " << std::endl;
				}
				else if (val == 3) {
					HKEY key;
					if (RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Services\\svsvc"), &key) == ERROR_SUCCESS)
					{
						std::cout << "RegOpenKeyOk - current val=3 - Continue..." << std::endl;
						if (ERROR_SUCCESS == RegSetValueEx(key, TEXT("Start"), 0, REG_DWORD, (const BYTE*)&this->val, sizeof(this->val))) {
							std::cout << "Patch done :)" << std::endl;
						}
						RegCloseKey(key);
					}
					else {
						RegCloseKey(key);
					}
				}
			}
			else {
				std::cout << "Error :(" << std::endl;
			}
		}
	};
}

int main()
{
	std::cout << "Happy Patching :) - Malvads" << std::endl;
	WaterMarkRemover::remove r;
	r.read();
	system("pause");
}