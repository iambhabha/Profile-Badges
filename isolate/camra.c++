#include <iostream>
#include <Windows.h>

bool CheckCameraPermission()
{
    HANDLE hCamera = CreateFile(L"\\\\.\\MyCamera", GENERIC_READ, 0, nullptr, OPEN_EXISTING, 0, nullptr);

    if (hCamera != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hCamera);
        return true; // Camera permission granted
    }

    return false; // Camera permission denied
}

bool RequestCameraPermission()
{
    std::cout << "Camera permission is required. Grant permission? (Y/N): ";
    char response;
    std::cin >> response;

    return (response == 'Y' || response == 'y');
}

int main()
{
    if (!CheckCameraPermission())
    {
        if (RequestCameraPermission())
        {
            // Perform actions when camera permission is granted
            std::cout << "Camera permission granted. Now you can access the camera." << std::endl;
        }
        else
        {
            // Handle when camera permission is denied
            std::cerr << "Camera permission denied. Exiting program." << std::endl;
            return 1;
        }
    }

    // Continue with the rest of your application logic here

    return 0;
}
