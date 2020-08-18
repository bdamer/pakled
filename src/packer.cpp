#include "stdafx.h"
#include "packer.h"

using namespace dukat;

namespace pakled
{
	void Packer::insert_free(const dukat::Rect& e)
	{
		for (auto it = free_list.begin(); it != free_list.end(); ++it)
		{
			if (compare(e, *it))
			{
				free_list.insert(it, e);
				return;
			}
		}
		free_list.push_back(e);
	}

	void Packer::pack(std::vector<BinEntry>& entries)
	{
		free_list.clear();
		free_list.push_back(Rect{ 0, 0, target_size, target_size });

		// sort input from smallest to greatest
		std::sort(entries.begin(), entries.end(), std::greater<>());

		for (auto it = entries.begin(); it != entries.end(); ++it)
		{
			const auto entry_width = it->rect.w;
			const auto entry_height = it->rect.h;
			//std::cout << "Finding match for: " << entry_width << "x" << entry_height << std::endl;

			auto dw = 0;
			auto dh = 0;
			auto free_it = free_list.begin();
			while (free_it != free_list.end())
			{
				const auto free_width = free_it->w;
				const auto free_height = free_it->h;
				dw = free_width - entry_width;
				dh = free_height - entry_height;
				if (dw < 0 || dh < 0)
				{
					//std::cout << "Skipping " << free_width << "x" << free_height << std::endl;
					++free_it;
					continue;
				}
				//std::cout << "Put into " << free_width << "x" << free_height << std::endl;
				break;
			}

			if (free_it == free_list.end())
			{
				std::cerr << "WARN: Unable to find match for " << it->img->filename << " [" << it->rect.w << "x" << it->rect.h << "] - skipping..." << std::endl;
				continue;
			}

			// We found a match - move to filled list
			filled_list.push_back(BinEntry{ Rect{ it->rect.x + free_it->x, it->rect.y + free_it->y, it->rect.w, it->rect.h }, it->img });

			// Replace free entry with remainder
			const Rect right{ free_it->x + entry_width, free_it->y, free_it->w - entry_width, free_it->h };
			const Rect bottom{ free_it->x, free_it->y + entry_height, entry_width, free_it->h - entry_height };
			free_list.erase(free_it);

			if (right.w > 0 && right.h > 0)
				insert_free(right);
			if (bottom.w > 0 && bottom.h > 0)
				insert_free(bottom);
		}
	}

	void Packer::save_atlas(const std::string& filename) const
	{
		dukat::TextureAtlas atlas;
		for (const auto& e : filled_list)
		{
			if (e.img != nullptr)
				atlas.add(e.img->filename, e.rect);
		}
		std::cout << "Saving " << atlas.size() << " entries to index map: " << filename << std::endl;
		std::ofstream file(filename);
		if (!file.is_open())
			throw std::runtime_error("Unable to open file for writing.");
		file << atlas;
	}

	void Packer::save_image_map(const std::string& filename, bool show_empty)
	{
		std::cout << "Saving image map to: " << filename << std::endl;
		Surface surface(target_size, target_size, SDL_PIXELFORMAT_RGBA8888);
		surface.fill(0x0);

		for (const auto& e : filled_list)
		{
			// std::cout << "Rect: [" << e.rect.x << ", " << e.rect.y << " - " << e.rect.w << "x" << e.rect.h << "]" << std::endl;
			surface.blt(*e.img->surface, e.rect.x, e.rect.y);
		}

		if (show_empty)
		{
			std::srand(123);
			for (const auto& f : free_list)
			{
				const uint32_t color = (random(0, 255) << 24) | (random(0, 255) << 16) | (random(0, 255) << 8) | (0xff);
				surface.fill_rect(f, color);
			}
		}

		surface.save_to_file(filename);
	}
}