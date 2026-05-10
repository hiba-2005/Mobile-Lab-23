#include <jni.h>
#include <string>
#include <cstring>
#include <cstdio>
#include <android/log.h>
#include <sys/ptrace.h>

#define TAG "LAB23_SECURITY"

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

static bool checkTracerState() {
    long result = ptrace(PTRACE_TRACEME, 0, 0, 0);

    if (result == -1) {
        LOGE("Controle natif : debug detecte");
        return true;
    }

    LOGI("Controle natif : aucun debug detecte");
    return false;
}

static bool scanMemoryMaps() {
    FILE *file = fopen("/proc/self/maps", "r");

    if (file == nullptr) {
        LOGW("Impossible de lire /proc/self/maps");
        return false;
    }

    char line[512];

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "frida") ||
            strstr(line, "xposed") ||
            strstr(line, "magisk") ||
            strstr(line, "gdb") ||
            strstr(line, "substrate")) {

            LOGE("Element suspect trouve : %s", line);
            fclose(file);
            return true;
        }
    }

    fclose(file);
    LOGI("Aucune librairie suspecte detectee");

    return false;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_example_jnidemo_MainActivity_checkNativeSecurity(
        JNIEnv *env,
        jobject thiz) {

    bool debugDetected = checkTracerState();
    bool suspiciousLib = scanMemoryMaps();

    if (debugDetected || suspiciousLib) {
        LOGE("Etat global : environnement suspect");
        return JNI_TRUE;
    }

    LOGI("Etat global : environnement normal");
    return JNI_FALSE;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jnidemo_MainActivity_getSecureMessage(
        JNIEnv *env,
        jobject thiz) {

    return env->NewStringUTF("JNI sécurisé : Java communique avec C++");
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jnidemo_MainActivity_secureFactorial(
        JNIEnv *env,
        jobject thiz,
        jint number) {

    if (number < 0) {
        return -1;
    }

    long long result = 1;

    for (int i = 1; i <= number; i++) {
        result *= i;
    }

    return static_cast<jint>(result);
}