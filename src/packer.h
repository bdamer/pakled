#pragma once

#include "binentry.h"

namespace pakled
{
	class Packer
	{
	private:
		const int target_size;
		std::vector<dukat::Rect> free_list; // list of free rects ordered from smallest to greatest
		std::vector<BinEntry> filled_list; // list of filled rects

		// insert free rect preserving ordering of free list.
		void insert_free(const dukat::Rect& e);

	public:
		// Creates a new packer for a square of given size
		Packer(int target_size) : target_size(target_size) { }
		~Packer(void) { }

		// Packs entries. Will return 0 on success, otherwise count of failures.
		int pack(std::vector<BinEntry>& entries);

		void save_atlas(const std::string& filename) const;
		void save_image_map(const std::string& filename, bool show_empty = false);
	};
}