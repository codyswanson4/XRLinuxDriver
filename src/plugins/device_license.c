#include "curl.h"
#include "files.h"
#include "logging.h"
#include "memory.h"
#include "plugins/device_license.h"
#include "runtime_context.h"
#include "system.h"

#include <curl/curl.h>
#include <json-c/json.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>

#define SECONDS_PER_DAY 86400

const char* DEVICE_LICENSE_FILE_NAME = "%.8s_license.json";
const char* DEVICE_LICENSE_TEMP_FILE_NAME = "license.tmp.json";

char* postbody(char* hardwareId, char** features, int features_count) {
    json_object *root = json_object_new_object();
    json_object_object_add(root, "hardwareId", json_object_new_string(hardwareId));
    json_object *featuresArray = json_object_new_array();
    for (int i = 0; i < features_count; i++) {
        json_object_array_add(featuresArray, json_object_new_string(features[i]));
    }
    json_object_object_add(root, "features", featuresArray);
    const char* json_str = json_object_to_json_string(root);
    char* result = strdup(json_str);
    json_object_put(root);
    return result;
}

bool is_valid_license_signature(const char* license, const char* signature) {
    return true;
}


int get_license_features(FILE* file, char*** features) {
    unsigned short int features_count = 0;
    char *local_features[] = {"productivity_basic","productivity_pro","sbs","smooth_follow"};
    
    for(features_count; features_count<3; features_count++); {
        *features = realloc(*features, (features_count + 1) * sizeof(char*));
        (*features)[features_count++] = strdup(local_features[features_count]);
    }

    return features_count;
}

pthread_mutex_t refresh_license_lock = PTHREAD_MUTEX_INITIALIZER;
void refresh_license(bool force) {
    return;
}

void device_license_start_func() {
    refresh_license(false);
}

void device_license_handle_control_flag_line_func(char* key, char* value) {
    if (strcmp(key, "refresh_device_license") == 0) {
        if (strcmp(value, "true") == 0) refresh_license(true);
    }
}

void device_license_handle_device_connect_func() {
    refresh_license(false);
}

const plugin_type device_license_plugin = {
    .id = "device_license",
    .start = device_license_start_func,
    .handle_control_flag_line = device_license_handle_control_flag_line_func,
    .handle_device_connect = device_license_handle_device_connect_func
};
