#include "AppDelegate.h"
#include<bits/stdc++.h>

#include "texture.h"
int main(int argc, char* argv[]) {
    // Khởi tạo ứng dụng
    AppDelegate app;

    // Thực thi ứng dụng
    if (!app.applicationDidFinishLaunching()) {
        printf("Application did not finish launching.\n");
        return 1;
    }

    return 0;
}

