#include <Windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>

class MicrophoneController
{
public:
    MicrophoneController()
    {
        CoInitialize(nullptr);
    }

    ~MicrophoneController()
    {
        CoUninitialize();
    }

    void ToggleMicrophone(bool enable)
    {
        IMMDeviceEnumerator *enumerator = nullptr;
        HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void **)&enumerator);
        if (SUCCEEDED(hr))
        {
            IMMDevice *defaultDevice = nullptr;
            hr = enumerator->GetDefaultAudioEndpoint(eCapture, eConsole, &defaultDevice);
            enumerator->Release();

            if (SUCCEEDED(hr))
            {
                IAudioEndpointVolume *endpointVolume = nullptr;
                hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, nullptr, (void **)&endpointVolume);
                defaultDevice->Release();

                if (SUCCEEDED(hr))
                {
                    hr = endpointVolume->SetMute(enable, nullptr);
                    endpointVolume->Release();
                }
            }
        }
    }
};

int main()
{
    // Example: Toggle microphone on
    {
        MicrophoneController controller;
        controller.ToggleMicrophone(true);
    }

    // Example: Toggle microphone off
    {
        MicrophoneController controller;
        controller.ToggleMicrophone(false);
    }

    return 0;
}
