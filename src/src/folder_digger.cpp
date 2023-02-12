//
// Created by csl on 2/12/23.
//

#include "folder_digger.h"
#include "algorithm"
#include "fstream"

namespace ns_folger {
    FolderDigger::FolderDigger(const std::string &targetPath, const std::set<std::string> &excludePathSet)
            : _tarPath(std::filesystem::canonical(targetPath).string()), _excludePath(), _files() {
        std::transform(
                excludePathSet.cbegin(), excludePathSet.cend(), std::inserter(_excludePath, _excludePath.begin()),
                [](const std::string &path) { return std::filesystem::canonical(path); }
        );
        Initialization();
    }

    void FolderDigger::Initialization() {
        for (auto &entry: std::filesystem::recursive_directory_iterator(_tarPath)) {
            if (!std::filesystem::is_regular_file(entry)) { continue; }
            auto iter = std::find_if(
                    _excludePath.begin(), _excludePath.end(), [&entry](const std::filesystem::path &path) {
                        const auto str1 = path.string();
                        const auto str2 = entry.path().string();
                        return str1.size() <= str2.size() && str2.substr(0, str1.size()) == str1;
                    }
            );
            if (iter != _excludePath.cend()) { continue; }
            _files[std::filesystem::path(entry).extension()].push_back(entry.path().string());
        }
    }

    std::map<std::string, std::vector<std::string>>
    FolderDigger::GetFiles(const std::set<std::string> &excludeFileType) const {
        std::map<std::string, std::vector<std::string>> files = _files;
        for (const auto &item: excludeFileType) { files.erase(item); }
        return files;
    }

    std::map<std::string, std::size_t>
    FolderDigger::GetFileTypeCount(const std::set<std::string> &excludeFileType) const {
        std::map<std::string, std::size_t> types;
        std::transform(
                _files.cbegin(), _files.cend(), std::inserter(types, types.begin()),
                [](const std::pair<std::string, std::vector<std::string>> &p) {
                    return std::pair{p.first, p.second.size()};
                }
        );
        for (const auto &item: excludeFileType) { types.erase(item); }
        return types;
    }

    std::map<std::string, std::size_t>
    FolderDigger::GetFileLineCount(const std::set<std::string> &excludeFileType) const {
        std::map<std::string, std::size_t> types;
        std::transform(
                _files.cbegin(), _files.cend(), std::inserter(types, types.begin()),
                [&](const std::pair<std::string, std::vector<std::string>> &p) {
                    std::size_t lines = 0;
                    for (const auto &item: p.second) { lines += FileLineCount(item); }
                    return std::pair{p.first, lines};
                }
        );
        for (const auto &item: excludeFileType) { types.erase(item); }
        return types;
    }

    std::size_t FolderDigger::FileLineCount(const std::string &filename) {
        std::ifstream file(filename);
        std::size_t line = 0;
        std::string str;
        while (std::getline(file, str)) { ++line; }
        file.close();
        return line;
    }

    const FolderDigger &
    FolderDigger::Save(const std::string &filename, const std::set<std::string> &excludeFileType) const {
        const auto files = GetFiles(excludeFileType);
        const auto fileTypeCount = GetFileTypeCount(excludeFileType);
        const auto fileLineCount = GetFileLineCount(excludeFileType);
        std::ofstream file(filename);
        cereal::JSONOutputArchive archive(file);
        archive(
                cereal::make_nvp("target_path", _tarPath),
                cereal::make_nvp("exclude_path", _excludePath),
                cereal::make_nvp("files", files),
                cereal::make_nvp("file_type_count", fileTypeCount),
                cereal::make_nvp("file_line_count", fileLineCount)
        );
        return *this;
    }

    FolderDigger FolderDigger::Load(const std::string &filename) {
        std::ifstream file(filename);
        cereal::JSONInputArchive archive(file);
        std::string tarPath;
        std::set<std::string> excludePath;
        archive(
                cereal::make_nvp("target_path", tarPath),
                cereal::make_nvp("exclude_path", excludePath)
        );
        return FolderDigger(tarPath, excludePath);
    }

}