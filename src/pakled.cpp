// pakled.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdafx.h"
#include "packer.h"

using namespace pakled;
using namespace dukat;

void index_folder(const std::string& path, std::vector<std::unique_ptr<ImageEntry>>& entries)
{
    std::cout << "Indexing directory: " << path << std::endl;
    for (const auto& dir_entry : std::filesystem::directory_iterator(path))
    {
        const auto file_path = dir_entry.path().u8string();
        if ("png" != file_extension(file_path))
            continue; // skip everything but png
        auto entry = std::make_unique<ImageEntry>();
        entry->filename = dir_entry.path().filename().u8string();
        entry->surface = Surface::from_file(file_path);
        // std::cout << "File: " << file_path << " [" << entry->surface->get_width() << "x" << entry->surface->get_height() << "]" << std::endl;
        entries.push_back(std::move(entry));
    }
}

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        std::cerr << "Invalid arguments - usage: pakled.exe <atlas size> <input dir> <output name>" << std::endl;
        return 1;
    }

    const auto size = std::stoi(argv[1]);
    const auto input_dir = std::string(argv[2]);
    const auto output_name = std::string(argv[3]);

    std::vector<std::unique_ptr<ImageEntry>> images;
    index_folder(input_dir, images);

    if (images.empty())
    {
        std::cerr << "No images found - quitting..." << std::endl;
        return 2;
    }
    else
    {
        std::cout << "Found " << images.size() << " images. Creating atlas..." << std::endl;
    }

    std::vector<BinEntry> entries;
    for (const auto& img : images)
        entries.push_back(BinEntry{ Rect{ 0, 0, img->surface->get_width(), img->surface->get_height() }, img.get() });

    Packer packer(size);
    packer.pack(entries);
    packer.save_image_map(output_name + ".png");
    packer.save_atlas(output_name + ".map");

    return 0;
}
