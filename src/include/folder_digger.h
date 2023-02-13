//
// Created by csl on 2/12/23.
//

#ifndef FOLDER_DIGGER_FOLDER_DIGGER_H
#define FOLDER_DIGGER_FOLDER_DIGGER_H

#include "map"
#include "vector"
#include "filesystem"
#include "set"
#include "artwork/logger/logger.h"
#include "cereal/types/map.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/types/set.hpp"
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include "cereal/types/base_class.hpp"

namespace ns_folger {
    class FolderDigger {
    private:
        std::string _tarPath;
        std::set<std::string> _excludePath;
        std::map<std::string, std::vector<std::string>> _files;

    public:
        explicit FolderDigger(const std::string &targetPath, const std::set<std::string> &excludePathSet = {});

        [[nodiscard]]  std::map<std::string, std::vector<std::string>>
        GetFiles(const std::set<std::string> &excludeFileType = {}) const;

        [[nodiscard]]  std::map<std::string, std::size_t>
        GetFileTypeCount(const std::set<std::string> &excludeFileType = {}) const;

        [[nodiscard]]  std::map<std::string, std::size_t>
        GetFileLineCount(const std::set<std::string> &excludeFileType = {}) const;

        [[nodiscard]]  std::map<std::string, std::vector<std::string>>
        GetFiles(bool, const std::set<std::string> &includeFileType = {}) const;

        [[nodiscard]]  std::map<std::string, std::size_t>
        GetFileTypeCount(bool, const std::set<std::string> &includeFileType = {}) const;

        [[nodiscard]]  std::map<std::string, std::size_t>
        GetFileLineCount(bool, const std::set<std::string> &includeFileType = {}) const;

        [[nodiscard]] const FolderDigger &
        Save(const std::string &filename, const std::set<std::string> &excludeFileType = {}) const;

        [[nodiscard]] const FolderDigger &
        Save(bool, const std::string &filename, const std::set<std::string> &includeFileType = {}) const;

        [[nodiscard]] static FolderDigger Load(const std::string &filename);

    protected:
        void Initialization();

        static std::size_t FileLineCount(const std::string &filename);
    };
}


#endif //FOLDER_DIGGER_FOLDER_DIGGER_H
