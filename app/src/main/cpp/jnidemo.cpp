#include <jni.h>
#include <string>
#include <algorithm>
#include <climits>
#include <android/log.h>

#define TAG "JNI_LAB"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

// Message natif
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jnidemo_MainActivity_getNativeMessage(
        JNIEnv *env,
        jobject thiz) {

    LOGI("Message envoye depuis C++");

    return env->NewStringUTF(
            "Bienvenue dans le laboratoire JNI Android");
}

// Factoriel
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jnidemo_MainActivity_calculateFactorial(
        JNIEnv *env,
        jobject thiz,
        jint number) {

    if (number < 0) {
        LOGE("Nombre negatif");
        return -1;
    }

    long long result = 1;

    for (int i = 1; i <= number; i++) {

        result *= i;

        if (result > INT_MAX) {
            LOGE("Overflow detecte");
            return -2;
        }
    }

    LOGI("Factoriel calcule");

    return static_cast<jint>(result);
}

// Inversion texte
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jnidemo_MainActivity_mirrorText(
        JNIEnv *env,
        jobject thiz,
        jstring text) {

    if (text == nullptr) {
        return env->NewStringUTF("Texte invalide");
    }

    const char *chars =
            env->GetStringUTFChars(text, nullptr);

    std::string nativeText(chars);

    env->ReleaseStringUTFChars(text, chars);

    std::reverse(
            nativeText.begin(),
            nativeText.end());

    return env->NewStringUTF(nativeText.c_str());
}

// Somme tableau
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jnidemo_MainActivity_calculateArrayTotal(
        JNIEnv *env,
        jobject thiz,
        jintArray values) {

    if (values == nullptr) {
        return -1;
    }

    jsize size =
            env->GetArrayLength(values);

    jint *elements =
            env->GetIntArrayElements(values, nullptr);

    long long total = 0;

    for (int i = 0; i < size; i++) {
        total += elements[i];
    }

    env->ReleaseIntArrayElements(
            values,
            elements,
            0);

    return static_cast<jint>(total);
}