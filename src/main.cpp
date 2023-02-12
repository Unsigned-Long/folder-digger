//
// Created by csl on 2/12/23.
//

#include "folder_digger.h"

int main() {
    ns_folger::FolderDigger(
            "../..", {"../../cmake-build-debug", "../../cmake-build-release", "../../.idea"}
    ).Save("../../data/file_line_count.json");
    return 0;
}