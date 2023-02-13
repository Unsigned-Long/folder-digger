//
// Created by csl on 2/12/23.
//

#include "folder_digger.h"

void digger_lic_calib() {
    auto digger = ns_folger::FolderDigger(
            "/home/csl/ros_ws/LIC-Calib/src",
            {
                    "/home/csl/ros_ws/LIC-Calib/src/lic_calib/thirdparty",
                    "/home/csl/ros_ws/LIC-Calib/src/openmvg_sfm/thirdparty",
                    "/home/csl/ros_ws/LIC-Calib/src/lic_calib/output",
                    "/home/csl/ros_ws/LIC-Calib/src/openmvg_sfm/output"
            }
    ).Save(true, "../../data/lic_calib.json", {
            ".cpp", ".hpp", ".h", ".json", ".yaml", ".xacro", ".txt", ".launch", ".py"
    });
}

void digger_folder_digger() {
    auto digger = ns_folger::FolderDigger(
            "/home/csl/CppWorks/artwork/folder-digger",
            {
                    "/home/csl/CppWorks/artwork/folder-digger/cmake-build-release",
                    "/home/csl/CppWorks/artwork/folder-digger/cmake-build-debug",
                    "/home/csl/CppWorks/artwork/folder-digger/.idea"
            }
    ).Save(true, "../../data/folder_digger.json", {
            ".cpp", ".h", ".json", ".txt", ".py"
    });
}

int main() {
    // digger_lic_calib();
    digger_folder_digger();
    return 0;
}