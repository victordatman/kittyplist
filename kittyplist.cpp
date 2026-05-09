// import shit that make code workie :D
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <blkid/blkid.h>
#include <iostream> 
#include <fstream>  
#include <string>
#include <sys/statvfs.h>
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]) {
    bool showSmart = false;
    bool showVersi = false;
    bool showHelps = false;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-help") == 0) {
            showHelps = true;
            printf("-help >> Shows this help list.\n");
            printf("-smart >> Shows what said Filesys is for (commonly).\n");
            printf("-version >> Shows the version.\n");
            // piece of shit code to show help
            return 0;
        }
        if (strcmp(argv[i], "-smart") == 0) {
            showSmart = true;
            printf("WARNING: Smart mode may not be accurate!\n");
            // piece of shit code to tell what said filesys is for
        }
        if (strcmp(argv[i], "-version") == 0) {
            showVersi = true;

            printf(R"(⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⣤⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⣴⣿⠟⠛⠛⠛⠿⣿⣿⣿⣿⣶⣤⡀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⣠⣴⣿⡟⠁⢀⣤⣀⠀⠀⠀⠀⠀⠀⠉⠻⣿⣦⠀⠀⠀⠀
⠀⠀⠀⠀⣾⡿⠿⠛⠁⣰⣿⣿⣿⡆⠀⠀⣴⣶⣶⠄⠀⢻⣿⡄⠀⠀⠀
⠀⠀⣾⡿⠁⠀⠀⠀⠀⠻⣿⣿⣿⠃⠀⣼⣿⣿⣿⠀⠀⠀⢿⣷⣄⠀⠀
⠀⣾⣿⠁⠀⣤⣶⡄⠀⠀⠈⠉⠁⠀⠀⠈⠛⠊⠁⠀⠀⠀⠀⠙⢿⣷⠀
⠀⣿⡇⠀⢸⣿⣿⡿⡆⠀⠀⣴⣶⣶⣴⣶⣄⠀⠀⢠⣶⣿⣦⠀⠀⣿⡇
⠀⣿⡇⠀⠀⠛⠙⠉⠀⣰⣿⣿⣿⣿⣿⣿⣿⣇⠀⣿⣿⣿⣿⠀⠀⣿⡇
⠀⣿⣇⠀⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣿⣷⣿⣷⡀⠀⠉⠉⠀⠀⣸⣿⠇
⠀⣿⣿⠀⠀⠀⠀⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⣻⡟⠘
⠀⢹⣿⠀⠀⠀⠀⠀⠉⠛⠉⠁⠉⠁⠙⠻⠿⠟⠀⠀⠀⠀⠀⣾⣿⠁⠀
⠀⠀⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡏⠀⠀
⠀⠀⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡇⠀⠀
⠀⠀⣻⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡇⠀⠀
⠀⠀⢸⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡇⠀⠀)");
            printf("\n");

            printf("--> Kitty Partition List\n");
            printf("----> Version 1.0.4\n");
            printf("------>  Written with C++\n");
            printf("------>  Made for Kitty Terminal (works on any terminal)\n");
            printf("    \n");
            printf("----> Made by V1ct0r\n");
            printf("------> @victorcheeto105 on Discord\n");
            printf("    \n");
            return 0;
            // piece of shit code to tell version
        }
    }

    blkid_cache cache = NULL;
    if (blkid_get_cache(&cache, NULL) < 0) return 1;
    
    blkid_dev_iterate iter = blkid_dev_iterate_begin(cache);
    blkid_dev dev;

    while (blkid_dev_next(iter, &dev) == 0) {
        const char *name = blkid_dev_devname(dev);

        printf("Drive Directory: %s\n", name);
        
        char *type = blkid_get_tag_value(cache, "TYPE", name);
        if (type) {
            printf("  Filesys: %s\n", type);
            if (showSmart && strcmp(type, "ntfs") == 0) {
                printf("  Windows Partition (or msdos)\n");
            }
            if (showSmart && strcmp(type, "vfat") == 0) {
                printf("  UEFI Partition\n");
            }
            if (showSmart && strcmp(type, "btrfs") == 0) {
                printf("  Linux Partition\n");
            }
            if (showSmart && strcmp(type, "ext4") == 0) {
                printf("  Linux Partition (or /boot)\n");
            }
            free(type);
        }

        // fixed shit start (4 hours of troubleshooting)
        bool isMounted = false;
        std::string mountPoint = "";
        std::ifstream mounts("/proc/mounts");
        std::string line;
        
        while (std::getline(mounts, line)) {
            if (line.find(name) != std::string::npos) {
                isMounted = true;
                // i forgor what it do
                size_t firstSpace = line.find(' ');
                size_t secondSpace = line.find(' ', firstSpace + 1);
                mountPoint = line.substr(firstSpace + 1, secondSpace - firstSpace - 1);
                break;
            }
        }
        mounts.close();
        // fixed shit end

        printf("  >>> : %s\n", isMounted ? "MOUNTED" : "UNMOUNTED");

        // get dat space info if its mounted!!!
        if (isMounted) {
            struct statvfs vfs;
            if (statvfs(mountPoint.c_str(), &vfs) == 0) {
                // it workie so don't touchie it!!! >:(
                double total = (double)vfs.f_blocks * vfs.f_frsize / (1024 * 1024 * 1024);
                double freeSpace = (double)vfs.f_bavail * vfs.f_frsize / (1024 * 1024 * 1024);
                printf("  Size: %.2f GB\n", total);
                printf("  FreeSpace: %.2f GB\n", freeSpace);
            }
        } else {
            printf("  Size/FreeSpace: Couldn't access since not mounted (NULL)\n");
        }
        printf("\n");
    }
    
    blkid_dev_iterate_end(iter);
    blkid_put_cache(cache);
    return 0;}