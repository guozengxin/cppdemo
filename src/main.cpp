#include <stdio.h>
#include "cpp11/cpp11.h"
#include <glog/logging.h>

int main(int argc, char* argv[]) {
    google::InitGoogleLogging(argv[0]);
    test_auto();
    LOG(INFO) << "Test success!";
    LOG(ERROR) << "Test error!";
}
