#pragma once
#include <experimental/filesystem>
#include <memory>


namespace Tools {
    template<typename D, typename B>
    inline std::unique_ptr<D> static_cast_unique_ptr(std::unique_ptr<B>& base)
    {
        return std::unique_ptr<D>(static_cast<D*>(base.release()));
    }

    template<typename D, typename B>
    inline std::unique_ptr<D> static_cast_unique_ptr(std::unique_ptr<B>&& base)
    {
        return std::unique_ptr<D>(static_cast<D*>(base.release()));
    }


    inline std::vector<std::string> getPathListOfDirectory4(std::string directory)
    {
        std::vector<std::string> list;
        auto p = std::experimental::filesystem::path(directory.c_str());
        for(auto dirEntry: std::experimental::filesystem::directory_iterator(p))
        {
            if(std::experimental::filesystem::is_directory(dirEntry.path()) == false)
            {
                list.push_back(dirEntry.path().string());
            }
        }
        std::sort(list.begin(), list.end());
        return list;
    }
};
