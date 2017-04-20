/* DO NOT EDIT THIS FILE - it is machine generated */
#include "io_github_vmBoy_Who.h"
#include "antivm.h"
#include "mapinfo.h"
/* Header for class io_github_vmBoy_Who */


/*
 * Class:     io_github_vmBoy_Who
 * Method:    map
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_io_github_vmBoy_Who_map
        (JNIEnv *env, jclass clazz, jint pid) {
    mapinfo *minfo = init_mapinfo(pid);

    mapinfo *minfotmp = minfo;
    if (minfotmp == NULL) {
        LOGE("nil ret");
        return;
    }
    while (minfotmp->next != NULL) {
        LOGD("maps ===%s ", minfo->name);
        filterPackage(minfo->name);
        minfotmp = minfotmp->next;
    }
}

/*
 * Class:     io_github_vmBoy_Who
 * Method:    unlink
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_io_github_vmBoy_Who_unlink(JNIEnv *env, jclass clazz, jstring jpath) {
    const char *nativeString = env->GetStringUTFChars(jpath, 0);
    int ret = unlink(nativeString);
#ifdef VMDEBUG
    LOGE("unlink %d ", ret);
#endif
    env->ReleaseStringUTFChars(jpath, nativeString);
    return ret;
}

char *uid_str(uid_t uid)
{
    static char numstr[10];
    struct passwd *pw_ptr;

    if((pw_ptr = getpwuid(uid)) == NULL){
        sprintf(numstr, "%d", uid);
        return numstr;
    }else
        return pw_ptr->pw_name;
}

/*
 * Class:     io_github_vmBoy_Who
 * Method:    permission
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL
Java_io_github_vmBoy_Who_permission(JNIEnv *env, jclass clazz, jstring jpath) {
    const char *nativeString = env->GetStringUTFChars(jpath, 0);
    struct stat info;
    stat(nativeString, &info);

    struct passwd *pw = getpwuid(info.st_uid);
    struct group *gr = getgrgid(info.st_gid);
#ifdef VMDEBUG
    LOGE("%-8s ", uid_str(info.st_uid));
    LOGE("name %s", pw->pw_name);
    LOGE("name %ld", gr->gr_gid);
    LOGE("mypid %d", getpid());
#endif
    if (strcmp(pw->pw_name, "system") != 0) {
            _exit(1);
    }
    env->ReleaseStringUTFChars(jpath, nativeString);
}


