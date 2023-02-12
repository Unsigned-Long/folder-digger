//
// Created by csl on 2/12/23.
//

#include "folder_digger.h"

int main() {
    auto digger = ns_folger::FolderDigger(
            "../..", {"../../cmake-build-debug", "../../cmake-build-release", "../../.idea", "../../.git"}
    ).Save("../../data/file_line_count.json");
    return 0;
}