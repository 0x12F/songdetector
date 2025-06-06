#include "SongDetector.h"
#include <jni.h>
#include <string>
#include <thread>

#include <winrt/Windows.Media.Control.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/base.h>

using namespace winrt;
using namespace Windows::Media::Control;
using namespace Windows::Foundation;

std::string getCurrentMediaInfo() {
    std::string result = "Çalan medya bulunamadı";
    try {
        std::thread t([&result]() {
            try {
                winrt::init_apartment(winrt::apartment_type::multi_threaded);
                auto manager = GlobalSystemMediaTransportControlsSessionManager::RequestAsync().get();
                auto sessions = manager.GetSessions();
                uint32_t count = sessions.Size();
                for (uint32_t i = 0; i < count; ++i) {
                    auto session = sessions.GetAt(i);
                    auto info = session.GetPlaybackInfo();
                    auto status = info.PlaybackStatus();
                    if (status == GlobalSystemMediaTransportControlsSessionPlaybackStatus::Playing) {
                        auto mediaProperties = session.TryGetMediaPropertiesAsync().get();
                        std::wstring title = mediaProperties.Title().c_str();
                        std::wstring artist = mediaProperties.Artist().c_str();
                        std::wstring res = title + L" - " + artist;
                        result = std::string(res.begin(), res.end());
                        return;
                    }
                }
            } catch (...) {

            }
        });
        t.join();
    } catch (...) {

    }
    return result;
}

JNIEXPORT jstring JNICALL Java_me_lyrica_utils_system_NativeMusicInfo_getCurrentSong(JNIEnv *env, jclass) {
    std::string song = getCurrentMediaInfo();
    return env->NewStringUTF(song.c_str());
} 